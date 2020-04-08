#pragma once

#include <QString>
#include <QRegExp>
#include <QVector>


class QTextParserLanguageDefinitionToken
{
public:
    QTextParserLanguageDefinitionToken() = default;
    QTextParserLanguageDefinitionToken(const QTextParserLanguageDefinitionToken &other) = default;

    inline QTextParserLanguageDefinitionToken &operator=(QTextParserLanguageDefinitionToken &&other) = default;
    inline QTextParserLanguageDefinitionToken &operator=(const QTextParserLanguageDefinitionToken &other) = default;

    QString name;
    QRegExp startString;
    QRegExp endString;
    QRegExp tokenString;
    bool searchEndStringLast;
    bool immediateStartString;
    bool onlyStartTag;
    bool excludeTopLevelChild;
    bool IgnoreIfOnlyOneChild;
    bool MultiLine;
    QVector<int> nestedTokens;
};
