#pragma once

#include "qtextparserlanguagedefinitiontoken.h"
#include <QStringList>
#include <QVector>
#include <QString>


class QTextParserLanguageDefinition
{
public:
    QTextParserLanguageDefinition() = default;
    QTextParserLanguageDefinition(const QTextParserLanguageDefinition &other) = default;

    inline QTextParserLanguageDefinition &operator=(QTextParserLanguageDefinition &&other) = default;
    inline QTextParserLanguageDefinition &operator=(const QTextParserLanguageDefinition &other) = default;

    QString languageName;
    Qt::CaseSensitivity caseSensitivity;
    QStringList defaultExtensions;
    QVector<QTextParserLanguageDefinitionToken> tokens;
    QVector<QString> tokenNames;
    QVector<int> startsWith;
};
