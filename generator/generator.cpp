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
        cout() << "Usage generator <language_definition.xml>" << endl;
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

    outStream << "// Generated with qtextparser generator(" << PROJECT_GIT_VERSION << ") @ " << QDateTime::currentDateTime().toString(Qt::ISODate) << endl;
    outStream << endl;

    outStream << "#pragma once" << endl;
    outStream << endl;

    outStream << "#include <QTextParser/QTextParserLanguageDefinition>" << endl;
    outStream << endl;
    outStream << endl;

    outStream << "namespace QTextParserXmlLanguageDefinition {"<< endl;

    outStream << "    QTextParserLanguageDefinition " << languageDef.name << "_QTextParserLanguageDefinition {" << endl;

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

    outStream << "        .name = \"" << languageDef.name << "\"," << endl;
    outStream << "        .description = \"" << languageDef.description << "\"," << endl;
    outStream << "        .version = \"" << languageDef.version << "\"," << endl;
    outStream << "        .emptySegmentsLanguage = \"" << languageDef.emptySegmentsLanguage << "\"," << endl;
    outStream << "        .caseSensitivity = " << languageSensitivity << "," << endl;
    outStream << "        .defaultExtensions = {" << defaultExtensions << "}," << endl;
    outStream << "        .tokens = {" << endl;

    for(const auto token: languageDef.tokens)
    {
        QString nestedTokens;
        QString pushAndContinueWithTokens;
        QString mergeChildren;

        outStream << "            {" << endl;

        outStream << "                .name = \"" << token.name << "\"," << endl;

        outStream << "                .startString = QRegExp(R\"(" << token.startString.pattern() << ")\", " << languageSensitivity << ")," << endl;
        outStream << "                .endString = QRegExp(R\"(" << token.endString.pattern() << ")\", " << languageSensitivity << ")," << endl;
        outStream << "                .tokenString = QRegExp(R\"(" << token.tokenString.pattern() << ")\", " << languageSensitivity << ")," << endl;

        outStream << "                .mergeChildrenStripWhitespaceFromName = " << (token.mergeChildrenStripWhitespaceFromName? "true": "false") << "," << endl;
        outStream << "                .canHaveTextInside = " << (token.canHaveTextInside? "true": "false") << "," << endl;
        outStream << "                .searchEndStringLast = " << (token.searchEndStringLast? "true": "false") << "," << endl;
        outStream << "                .immediateStartString = " << (token.immediateStartString? "true": "false") << "," << endl;
        outStream << "                .onlyStartTag = " << (token.onlyStartTag? "true": "false") << "," << endl;
        outStream << "                .ignoreIfOnlyOneChild = " << (token.ignoreIfOnlyOneChild? "true": "false") << "," << endl;
        outStream << "                .ignoreParentTokenEndString = " << (token.ignoreParentTokenEndString? "true": "false") << "," << endl;
        outStream << "                .multiLine = " << (token.multiLine? "true": "false") << "," << endl;
        outStream << "                .childrenStripWhitespaceFromName = " << (token.childrenStripWhitespaceFromName? "true": "false") << "," << endl;

        outStream << "                .closeToken = " << QString::number(token.closeToken) << "," << endl;

        for(int c = 0; c < token.nestedTokens.count(); c++)
        {
            if (c > 0)
            {
                nestedTokens.append(", ");
            }
            nestedTokens.append(QString::number(token.nestedTokens[c]));
        }
        outStream << "                .nestedTokens = {" << nestedTokens << "}," << endl;

        for(int c = 0; c < token.pushAndContinueWithTokens.count(); c++)
        {
            if (c > 0)
            {
                pushAndContinueWithTokens.append(", ");
            }
            pushAndContinueWithTokens.append(QString::number(token.pushAndContinueWithTokens[c]));
        }
        outStream << "                .pushAndContinueWithTokens = {" << pushAndContinueWithTokens << "}," << endl;

        outStream << "                .mergeChildren = {" << endl;
        for(int c = 0; c < token.mergeChildren.count(); c++)
        {
            const auto &child = token.mergeChildren.at(c);

            outStream << "                    {" << endl;
            outStream << "                        .name = \"" << child.name << "\"," << endl;
            outStream << "                        .fromToken = \"" << child.fromToken << "\"," << endl;
            outStream << "                        .isNameRegex = " << (child.isNameRegex? "true": "false") << "," << endl;
            outStream << "                    }," << endl;
        }
        outStream << "                }," << endl;
        outStream << "            }," << endl;
    }

    outStream << "        }," << endl;
    outStream << "        .startsWith = {" << startsWith << "}" << endl;
    outStream << "    };"<< endl;

    outStream << "}"<< endl;

    QRegExp tt("", Qt::CaseSensitive, QRegExp::RegExp);

    return 0;
}
