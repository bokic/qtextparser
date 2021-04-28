#include <QTextParser/QTextParserLanguageDefinition>
#include <QTextParser/QTextParserLoader>
#include <QTextStream>
#include <QDateTime>
#include <QFileInfo>
#include <QFile>



QTextStream &cout()
{
    static QTextStream ret(stdout);
    return ret;
}

int main(int argc, char *argv[])
{
    QTextParserLanguageDefinition languageDef;
    QString languageSensitivity;
    QString outFilePath;
    QString inFilePath;
    QString outText;
    QFile outFile;

    if (argc != 2)
    {
        cout() << "Usage generator <language_definition.xml>" << Qt::endl;
        return 1;
    }

    inFilePath = QString::fromUtf8(argv[1]);
    languageDef = QTextParserLoader::loadDefinitionFromXmlFile(inFilePath);

    QFileInfo outFileInfo(inFilePath);
    outFilePath = outFileInfo.absolutePath() + QDir::separator() + outFileInfo.completeBaseName() + ".h";

    outFile.setFileName(outFilePath);
    if (outFile.open(QIODevice::WriteOnly | QIODevice::Truncate) == false) // QIODevice::NewOnly
    {
        cout() << "Can't open output file for writing \"" << outFilePath << "\"\nError: " << outFile.errorString() + "\n";
        return 1;
    }

    QTextStream outStream(&outFile);
    outStream.setCodec("UTF-8");

    outStream << "// Generated with qtextparser generator(" << PROJECT_GIT_VERSION << ") @ " << QDateTime::currentDateTime().toString(Qt::ISODate) << Qt::endl;
    outStream << Qt::endl;

    outStream << "#pragma once" << Qt::endl;
    outStream << Qt::endl;

    outStream << "#include <QTextParser/QTextParserLanguageDefinition>" << Qt::endl;
    outStream << Qt::endl;
    outStream << Qt::endl;

    outStream << "namespace QTextParserXmlLanguageDefinition {"<< Qt::endl;

    outStream << "    QTextParserLanguageDefinition " << languageDef.name << "_QTextParserLanguageDefinition {" << Qt::endl;

    QString defaultExtensions;
    for(int c = 0; c < languageDef.defaultExtensions.length(); c++)
    {
        if (c > 0)
        {
            defaultExtensions.append(", ");
        }
        defaultExtensions.append("\"" + languageDef.defaultExtensions[c] + "\"");
    }

    QString startsWith;
    for(int c = 0; c < languageDef.startsWith.length(); c++)
    {
        if (c > 0)
        {
            startsWith.append(", ");
        }
        startsWith.append(QString::number(languageDef.startsWith[c]));
    }

    languageSensitivity = languageDef.caseSensitivity? "Qt::CaseSensitive": "Qt::CaseInsensitive";

    outStream << "        .name = \"" << languageDef.name << "\"," << Qt::endl;
    outStream << "        .description = \"" << languageDef.description << "\"," << Qt::endl;
    outStream << "        .version = \"" << languageDef.version << "\"," << Qt::endl;
    outStream << "        .emptySegmentsLanguage = \"" << languageDef.emptySegmentsLanguage << "\"," << Qt::endl;
    outStream << "        .caseSensitivity = " << languageSensitivity << "," << Qt::endl;
    outStream << "        .defaultExtensions = {" << defaultExtensions << "}," << Qt::endl;
    outStream << "        .tokens = {" << Qt::endl;

    for(const auto token: languageDef.tokens)
    {
        QString nestedTokens;
        QString pushAndContinueWithTokens;
        QString mergeChildren;

        outStream << "            {" << Qt::endl;

        outStream << "                .name = \"" << token.name << "\"," << Qt::endl;

        outStream << "                .startString = QRegExp(R\"(" << token.startString.pattern() << ")\", " << languageSensitivity << ")," << Qt::endl;
        outStream << "                .endString = QRegExp(R\"(" << token.endString.pattern() << ")\", " << languageSensitivity << ")," << Qt::endl;
        outStream << "                .tokenString = QRegExp(R\"(" << token.tokenString.pattern() << ")\", " << languageSensitivity << ")," << Qt::endl;

        outStream << "                .mergeChildrenStripWhitespaceFromName = " << (token.mergeChildrenStripWhitespaceFromName? "true": "false") << "," << Qt::endl;
        outStream << "                .canHaveTextInside = " << (token.canHaveTextInside? "true": "false") << "," << Qt::endl;
        outStream << "                .searchEndStringLast = " << (token.searchEndStringLast? "true": "false") << "," << Qt::endl;
        outStream << "                .immediateStartString = " << (token.immediateStartString? "true": "false") << "," << Qt::endl;
        outStream << "                .onlyStartTag = " << (token.onlyStartTag? "true": "false") << "," << Qt::endl;
        outStream << "                .ignoreIfOnlyOneChild = " << (token.ignoreIfOnlyOneChild? "true": "false") << "," << Qt::endl;
        outStream << "                .ignoreParentTokenEndString = " << (token.ignoreParentTokenEndString? "true": "false") << "," << Qt::endl;
        outStream << "                .multiLine = " << (token.multiLine? "true": "false") << "," << Qt::endl;
        outStream << "                .childrenStripWhitespaceFromName = " << (token.childrenStripWhitespaceFromName? "true": "false") << "," << Qt::endl;

        outStream << "                .closeToken = " << QString::number(token.closeToken) << "," << Qt::endl;

        for(int c = 0; c < token.nestedTokens.count(); c++)
        {
            if (c > 0)
            {
                nestedTokens.append(", ");
            }
            nestedTokens.append(QString::number(token.nestedTokens[c]));
        }
        outStream << "                .nestedTokens = {" << nestedTokens << "}," << Qt::endl;

        for(int c = 0; c < token.pushAndContinueWithTokens.count(); c++)
        {
            if (c > 0)
            {
                pushAndContinueWithTokens.append(", ");
            }
            pushAndContinueWithTokens.append(QString::number(token.pushAndContinueWithTokens[c]));
        }
        outStream << "                .pushAndContinueWithTokens = {" << pushAndContinueWithTokens << "}," << Qt::endl;

        outStream << "                .mergeChildren = {" << Qt::endl;
        for(int c = 0; c < token.mergeChildren.count(); c++)
        {
            const auto &child = token.mergeChildren.at(c);

            outStream << "                    {" << Qt::endl;
            outStream << "                        .name = \"" << child.name << "\"," << Qt::endl;
            outStream << "                        .fromToken = \"" << child.fromToken << "\"," << Qt::endl;
            outStream << "                        .isNameRegex = " << (child.isNameRegex? "true": "false") << "," << Qt::endl;
            outStream << "                    }," << Qt::endl;
        }
        outStream << "                }," << Qt::endl;
        outStream << "            }," << Qt::endl;
    }

    outStream << "        }," << Qt::endl;
    outStream << "        .startsWith = {" << startsWith << "}" << Qt::endl;
    outStream << "    };"<< Qt::endl;

    outStream << "}"<< Qt::endl;

    QRegExp tt("", Qt::CaseSensitive, QRegExp::RegExp);

    return 0;
}
