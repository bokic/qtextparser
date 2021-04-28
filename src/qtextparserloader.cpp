#include <QTextParser/QTextParserLoader>
#include <QDomDocument>
#include <QException>


namespace QTextParserLoader
{

    QVector<QTextParserLanguageDefinition> loadDefinitionsFromDir(const QDir &dir)
    {
        QVector<QTextParserLanguageDefinition> ret;

        QFileInfoList xmlFiles = dir.entryInfoList(QStringList() << "*.xml");

        for(const auto &xmlFile: xmlFiles)
        {
            ret.append(loadDefinitionFromXmlFile(xmlFile.filePath()));
        }

        return ret;
    }

    QTextParserLanguageDefinition loadDefinitionFromXmlFile(const QString &filepath)
    {
        QTextParserLanguageDefinition ret;
        QStringList tokens;
        QDomDocument doc;

        QFile file(filepath);

        file.open(QIODevice::ReadOnly);

        doc.setContent(&file);

        if (doc.childNodes().count() == 1)
        {
            QDomNode language_node = doc.childNodes().at(0);

            if ((language_node.nodeType() == QDomNode::ElementNode)&&(language_node.nodeName() == "language"))
            {
                QDomNode tokens_node = language_node.childNodes().at(0);

                QString languageName = language_node.attributes().namedItem("Name").nodeValue();
                QString languageDescription = language_node.attributes().namedItem("Description").nodeValue();
                QString languageVersion = language_node.attributes().namedItem("Version").nodeValue();
                QString languageEmptySegmentsLanguage = language_node.attributes().namedItem("EmptySegmentsLanguage").nodeValue();
                QString languageCaseSensitivity = language_node.attributes().namedItem("CaseSensitivity").nodeValue();
                QString languageDefaultExtensions = language_node.attributes().namedItem("DefaultFileExtensions").nodeValue();
                QString languageStartsWith = language_node.attributes().namedItem("StartsWith").nodeValue();

                ret.name = languageName;
                ret.description = languageDescription;
                ret.version = languageVersion;
                ret.emptySegmentsLanguage = languageEmptySegmentsLanguage;
                ret.caseSensitivity = languageCaseSensitivity.compare("true", Qt::CaseInsensitive) == 0? Qt::CaseSensitive: Qt::CaseInsensitive;

                auto defExtensions = languageDefaultExtensions.split(',');
                for(const auto &defaultExtension: qAsConst(defExtensions))
                {
                    ret.defaultExtensions.append(defaultExtension.trimmed());
                }

                // Insert tokens.
                for(int c = 0; c < language_node.childNodes().length(); c++)
                {
                    const auto &tokens_node = language_node.childNodes().at(c);

                    if ((tokens_node.nodeType() == QDomNode::ElementNode)&&(tokens_node.nodeName() == "tokens"))
                    {
                        // Add tokens.
                        for(int c = 0; c < tokens_node.childNodes().length(); c++)
                        {
                            const auto &token_node = tokens_node.childNodes().at(c);

                            if ((token_node.nodeType() == QDomNode::ElementNode)&&(token_node.nodeName() == "token"))
                            {
                                QString name = token_node.attributes().namedItem("Name").nodeValue().trimmed();

                                if (tokens.contains(name))
                                {
                                    throw QTextParserLoaderException(QObject::tr("Duplicate token name(%1)").arg(name));
                                }

                                tokens.append(name);
                            }
                        }

                        for(int c = 0; c < tokens_node.childNodes().length(); c++)
                        {
                            const auto &token_node = tokens_node.childNodes().at(c);

                            if ((token_node.nodeType() == QDomNode::ElementNode)&&(token_node.nodeName() == "token"))
                            {
                                QTextParserLanguageDefinitionToken newToken;

                                newToken.name = token_node.attributes().namedItem("Name").nodeValue().trimmed();
                                newToken.startString = QRegExp(token_node.attributes().namedItem("StartString").nodeValue());
                                newToken.endString = QRegExp(token_node.attributes().namedItem("EndString").nodeValue());
                                newToken.tokenString = QRegExp(token_node.attributes().namedItem("TokenString").nodeValue());

                                newToken.canHaveTextInside = token_node.attributes().namedItem("CanHaveTextInside").nodeValue().trimmed().compare("true", Qt::CaseInsensitive) == 0? true: false;
                                newToken.searchEndStringLast = token_node.attributes().namedItem("SearchEndStringLast").nodeValue().trimmed().compare("true", Qt::CaseInsensitive) == 0? true: false;
                                newToken.immediateStartString = token_node.attributes().namedItem("ImmediateStartString").nodeValue().trimmed().compare("true", Qt::CaseInsensitive) == 0? true: false;
                                newToken.onlyStartTag = token_node.attributes().namedItem("OnlyStartTag").nodeValue().trimmed().compare("true", Qt::CaseInsensitive) == 0? true: false;
                                newToken.ignoreIfOnlyOneChild = token_node.attributes().namedItem("IgnoreIfOnlyOneChild").nodeValue().trimmed().compare("true", Qt::CaseInsensitive) == 0? true: false;
                                newToken.ignoreParentTokenEndString = token_node.attributes().namedItem("IgnoreParentTokenEndString").nodeValue().trimmed().compare("true", Qt::CaseInsensitive) == 0? true: false;
                                newToken.multiLine = token_node.attributes().namedItem("Name").nodeValue().trimmed().compare("true", Qt::CaseInsensitive) == 0? true: false;
                                newToken.childrenStripWhitespaceFromName = token_node.attributes().namedItem("childrenStripWhitespaceFromName").nodeValue().trimmed().compare("true", Qt::CaseInsensitive) == 0? true: false;

                                newToken.closeToken = tokens.indexOf(token_node.attributes().namedItem("closeToken").nodeValue().trimmed());

                                if (token_node.firstChildElement("nested_tokens").isElement())
                                {
                                    const auto &nested_tokens_node = token_node.firstChildElement("nested_tokens");
                                    const auto &nested_tokens = nested_tokens_node.attribute("names").split(',');
                                    for(const auto &nested_token: nested_tokens)
                                    {
                                        int nestedTokenIdx = tokens.indexOf(nested_token.trimmed());

                                        if (nestedTokenIdx < 0)
                                        {
                                            throw QTextParserLoaderException(QObject::tr("Invalid nested token name(%1)").arg(nested_token));
                                        }

                                        newToken.nestedTokens.append(nestedTokenIdx);
                                    }
                                }

                                if (token_node.firstChildElement("push_and_continue_with_tokens").isElement())
                                {
                                    const auto &push_and_continue_with_tokens_node = token_node.firstChildElement("push_and_continue_with_tokens");
                                    const auto &push_and_continue_with_tokens = push_and_continue_with_tokens_node.attribute("names").split(',');
                                    for(const auto &push_and_continue_with_token: push_and_continue_with_tokens)
                                    {
                                        int push_and_continue_with_tokenIdx = tokens.indexOf(push_and_continue_with_token.trimmed());

                                        if (push_and_continue_with_tokenIdx < 0)
                                        {
                                            throw QTextParserLoaderException(QObject::tr("Invalid push_and_continue_with_tokenIdx token name(%1)").arg(push_and_continue_with_token));
                                        }

                                        newToken.pushAndContinueWithTokens.append(push_and_continue_with_tokenIdx);
                                    }
                                }

                                if (token_node.firstChildElement("merge_children").isElement())
                                {
                                    const auto &mergeChildren_node = token_node.firstChildElement("merge_children");

                                    newToken.mergeChildrenStripWhitespaceFromName = mergeChildren_node.attributes().namedItem("StripWhitespaceFromName").nodeValue().trimmed().compare("true", Qt::CaseInsensitive) == 0? true: false;

                                    for(int c = 0; c < mergeChildren_node.childNodes().length(); c++)
                                    {
                                        const auto & mergeChildrenItem_node = mergeChildren_node.childNodes().at(c);
                                        if ((mergeChildrenItem_node.nodeType() == QDomNode::ElementNode)&&(mergeChildrenItem_node.nodeName() == "children"))
                                        {
                                            QTextParserLanguageDefinitionMergeChildren item;

                                            item.name = mergeChildrenItem_node.attributes().namedItem("Name").nodeValue().trimmed();
                                            item.fromToken = mergeChildrenItem_node.attributes().namedItem("FromToken").nodeValue().trimmed();
                                            item.isNameRegex = mergeChildrenItem_node.attributes().namedItem("IsNameRegex").nodeValue().trimmed().compare("true", Qt::CaseInsensitive) == 0? true: false;

                                            newToken.mergeChildren.append(item);
                                        }
                                    }
                                }

                                ret.tokens.append(newToken);
                                ret.tokenNames.append(newToken.name);
                            }
                        }
                    }
                }

                auto startTokens = languageStartsWith.split(',');
                for(const QString &startToken: qAsConst(startTokens))
                {
                    int tokenIndex = ret.tokenNames.indexOf(startToken);

                    if (tokenIndex < 0)
                    {
                        throw QTextParserLoaderException(QObject::tr("Invalid start token(%1): %2").arg(filepath, startToken));
                    }

                    ret.startsWith.append(tokenIndex);
                }
            }
        }

        return ret;
    }
}
