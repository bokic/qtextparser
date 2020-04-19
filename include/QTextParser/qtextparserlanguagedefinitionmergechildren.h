#pragma once

#include <QString>


class QTextParserLanguageDefinitionMergeChildren {
public:
    QTextParserLanguageDefinitionMergeChildren() = default;
    QTextParserLanguageDefinitionMergeChildren(const QTextParserLanguageDefinitionMergeChildren &other) = default;

    inline QTextParserLanguageDefinitionMergeChildren &operator=(QTextParserLanguageDefinitionMergeChildren &&other) = default;
    inline QTextParserLanguageDefinitionMergeChildren &operator=(const QTextParserLanguageDefinitionMergeChildren &other) = default;

    QString name;
    QString fromToken;
    bool isNameRegex = false;
};
