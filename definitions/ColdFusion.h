// Generated with qtextparser generator(0.9-4-ge3b7e3a) @ 2020-04-20T17:59:03

#pragma once

#include <QTextParser/QTextParserLanguageDefinition>


namespace QTextParserXmlLanguageDefinition {
    QTextParserLanguageDefinition CFML_QTextParserLanguageDefinition {
        .name = "CFML",
        .description = "ColdFusion markup language",
        .version = "0.1",
        .emptySegmentsLanguage = "HTML",
        .caseSensitivity = Qt::CaseInsensitive,
        .defaultExtensions = {"cfm", "cfc"},
        .tokens = {
            {
                .name = "CFMLStartTag",
                .startString = QRegExp(R"()", Qt::CaseInsensitive),
                .endString = QRegExp(R"()", Qt::CaseInsensitive),
                .tokenString = QRegExp(R"(<(cf\s*\w+)\s*)", Qt::CaseInsensitive),
                .mergeChildrenStripWhitespaceFromName = true,
                .canHaveTextInside = false,
                .searchEndStringLast = false,
                .immediateStartString = false,
                .onlyStartTag = false,
                .ignoreIfOnlyOneChild = false,
                .ignoreParentTokenEndString = false,
                .multiLine = false,
                .childrenStripWhitespaceFromName = false,
                .closeToken = -1,
                .nestedTokens = {},
                .pushAndContinueWithTokens = {},
                .mergeChildren = {
                    {
                        .name = "cfoutput",
                        .fromToken = "cfoutput_StartTag",
                        .isNameRegex = false,
                    },
                    {
                        .name = "cfquery",
                        .fromToken = "cfquery_StartTag",
                        .isNameRegex = false,
                    },
                    {
                        .name = "cfscript",
                        .fromToken = "cfscript_StartTag",
                        .isNameRegex = false,
                    },
                    {
                        .name = "^cf_",
                        .fromToken = "CustomStartTag",
                        .isNameRegex = true,
                    },
                    {
                        .name = "",
                        .fromToken = "CfStandardStartTag",
                        .isNameRegex = false,
                    },
                },
            },
            {
                .name = "CFMLEndTag",
                .startString = QRegExp(R"(<\/(cf\s*\w+)\s*>)", Qt::CaseInsensitive),
                .endString = QRegExp(R"()", Qt::CaseInsensitive),
                .tokenString = QRegExp(R"()", Qt::CaseInsensitive),
                .mergeChildrenStripWhitespaceFromName = false,
                .canHaveTextInside = false,
                .searchEndStringLast = false,
                .immediateStartString = false,
                .onlyStartTag = false,
                .ignoreIfOnlyOneChild = false,
                .ignoreParentTokenEndString = false,
                .multiLine = false,
                .childrenStripWhitespaceFromName = false,
                .closeToken = -1,
                .nestedTokens = {},
                .pushAndContinueWithTokens = {},
                .mergeChildren = {
                },
            },
            {
                .name = "CFMLComment",
                .startString = QRegExp(R"(<!---)", Qt::CaseInsensitive),
                .endString = QRegExp(R"(--->)", Qt::CaseInsensitive),
                .tokenString = QRegExp(R"()", Qt::CaseInsensitive),
                .mergeChildrenStripWhitespaceFromName = false,
                .canHaveTextInside = true,
                .searchEndStringLast = false,
                .immediateStartString = false,
                .onlyStartTag = false,
                .ignoreIfOnlyOneChild = false,
                .ignoreParentTokenEndString = false,
                .multiLine = false,
                .childrenStripWhitespaceFromName = false,
                .closeToken = -1,
                .nestedTokens = {2},
                .pushAndContinueWithTokens = {},
                .mergeChildren = {
                },
            },
            {
                .name = "cfoutput_StartTag",
                .startString = QRegExp(R"(<(cf\s*output)\s*)", Qt::CaseInsensitive),
                .endString = QRegExp(R"(\/?>)", Qt::CaseInsensitive),
                .tokenString = QRegExp(R"()", Qt::CaseInsensitive),
                .mergeChildrenStripWhitespaceFromName = false,
                .canHaveTextInside = false,
                .searchEndStringLast = false,
                .immediateStartString = false,
                .onlyStartTag = false,
                .ignoreIfOnlyOneChild = false,
                .ignoreParentTokenEndString = false,
                .multiLine = false,
                .childrenStripWhitespaceFromName = false,
                .closeToken = -1,
                .nestedTokens = {8},
                .pushAndContinueWithTokens = {0, 1, 2, 19, 20},
                .mergeChildren = {
                },
            },
            {
                .name = "cfquery_StartTag",
                .startString = QRegExp(R"(<(cf\s*query)\s*)", Qt::CaseInsensitive),
                .endString = QRegExp(R"(\/?>)", Qt::CaseInsensitive),
                .tokenString = QRegExp(R"()", Qt::CaseInsensitive),
                .mergeChildrenStripWhitespaceFromName = false,
                .canHaveTextInside = false,
                .searchEndStringLast = false,
                .immediateStartString = false,
                .onlyStartTag = false,
                .ignoreIfOnlyOneChild = false,
                .ignoreParentTokenEndString = false,
                .multiLine = false,
                .childrenStripWhitespaceFromName = false,
                .closeToken = -1,
                .nestedTokens = {8},
                .pushAndContinueWithTokens = {0, 1, 2, 19, 20},
                .mergeChildren = {
                },
            },
            {
                .name = "cfscript_StartTag",
                .startString = QRegExp(R"(<(cf\s*script)\s*)", Qt::CaseInsensitive),
                .endString = QRegExp(R"(\/?>)", Qt::CaseInsensitive),
                .tokenString = QRegExp(R"()", Qt::CaseInsensitive),
                .mergeChildrenStripWhitespaceFromName = false,
                .canHaveTextInside = false,
                .searchEndStringLast = false,
                .immediateStartString = false,
                .onlyStartTag = false,
                .ignoreIfOnlyOneChild = false,
                .ignoreParentTokenEndString = false,
                .multiLine = false,
                .childrenStripWhitespaceFromName = false,
                .closeToken = -1,
                .nestedTokens = {8},
                .pushAndContinueWithTokens = {9},
                .mergeChildren = {
                },
            },
            {
                .name = "CustomStartTag",
                .startString = QRegExp(R"(<(cf_\w+)\s*)", Qt::CaseInsensitive),
                .endString = QRegExp(R"(\/?>)", Qt::CaseInsensitive),
                .tokenString = QRegExp(R"()", Qt::CaseInsensitive),
                .mergeChildrenStripWhitespaceFromName = false,
                .canHaveTextInside = false,
                .searchEndStringLast = false,
                .immediateStartString = false,
                .onlyStartTag = false,
                .ignoreIfOnlyOneChild = false,
                .ignoreParentTokenEndString = false,
                .multiLine = false,
                .childrenStripWhitespaceFromName = false,
                .closeToken = -1,
                .nestedTokens = {8},
                .pushAndContinueWithTokens = {0, 1, 2, 19, 20},
                .mergeChildren = {
                },
            },
            {
                .name = "CfStandardStartTag",
                .startString = QRegExp(R"(<(cf\w+)\s*)", Qt::CaseInsensitive),
                .endString = QRegExp(R"(\/?>)", Qt::CaseInsensitive),
                .tokenString = QRegExp(R"()", Qt::CaseInsensitive),
                .mergeChildrenStripWhitespaceFromName = false,
                .canHaveTextInside = false,
                .searchEndStringLast = false,
                .immediateStartString = false,
                .onlyStartTag = false,
                .ignoreIfOnlyOneChild = false,
                .ignoreParentTokenEndString = false,
                .multiLine = false,
                .childrenStripWhitespaceFromName = false,
                .closeToken = -1,
                .nestedTokens = {8},
                .pushAndContinueWithTokens = {0, 1, 2},
                .mergeChildren = {
                },
            },
            {
                .name = "Expression",
                .startString = QRegExp(R"()", Qt::CaseInsensitive),
                .endString = QRegExp(R"()", Qt::CaseInsensitive),
                .tokenString = QRegExp(R"()", Qt::CaseInsensitive),
                .mergeChildrenStripWhitespaceFromName = false,
                .canHaveTextInside = false,
                .searchEndStringLast = false,
                .immediateStartString = false,
                .onlyStartTag = false,
                .ignoreIfOnlyOneChild = true,
                .ignoreParentTokenEndString = false,
                .multiLine = false,
                .childrenStripWhitespaceFromName = false,
                .closeToken = -1,
                .nestedTokens = {15, 16, 21, 22, 23, 24, 25, 26, 27, 28, 29, 11, 12},
                .pushAndContinueWithTokens = {},
                .mergeChildren = {
                },
            },
            {
                .name = "ScriptExpression",
                .startString = QRegExp(R"()", Qt::CaseInsensitive),
                .endString = QRegExp(R"()", Qt::CaseInsensitive),
                .tokenString = QRegExp(R"()", Qt::CaseInsensitive),
                .mergeChildrenStripWhitespaceFromName = false,
                .canHaveTextInside = false,
                .searchEndStringLast = false,
                .immediateStartString = false,
                .onlyStartTag = false,
                .ignoreIfOnlyOneChild = true,
                .ignoreParentTokenEndString = false,
                .multiLine = false,
                .childrenStripWhitespaceFromName = false,
                .closeToken = -1,
                .nestedTokens = {15, 16, 21, 13, 14, 10, 22, 23, 24, 25, 26, 27, 28, 29, 11, 12},
                .pushAndContinueWithTokens = {},
                .mergeChildren = {
                },
            },
            {
                .name = "CodeBlock",
                .startString = QRegExp(R"(\{)", Qt::CaseInsensitive),
                .endString = QRegExp(R"(\})", Qt::CaseInsensitive),
                .tokenString = QRegExp(R"()", Qt::CaseInsensitive),
                .mergeChildrenStripWhitespaceFromName = false,
                .canHaveTextInside = false,
                .searchEndStringLast = false,
                .immediateStartString = false,
                .onlyStartTag = false,
                .ignoreIfOnlyOneChild = false,
                .ignoreParentTokenEndString = false,
                .multiLine = false,
                .childrenStripWhitespaceFromName = false,
                .closeToken = -1,
                .nestedTokens = {9},
                .pushAndContinueWithTokens = {},
                .mergeChildren = {
                },
            },
            {
                .name = "SubExpression",
                .startString = QRegExp(R"(()", Qt::CaseInsensitive),
                .endString = QRegExp(R"())", Qt::CaseInsensitive),
                .tokenString = QRegExp(R"()", Qt::CaseInsensitive),
                .mergeChildrenStripWhitespaceFromName = false,
                .canHaveTextInside = false,
                .searchEndStringLast = false,
                .immediateStartString = false,
                .onlyStartTag = false,
                .ignoreIfOnlyOneChild = false,
                .ignoreParentTokenEndString = false,
                .multiLine = false,
                .childrenStripWhitespaceFromName = false,
                .closeToken = -1,
                .nestedTokens = {8},
                .pushAndContinueWithTokens = {},
                .mergeChildren = {
                },
            },
            {
                .name = "VariableIndex",
                .startString = QRegExp(R"(\[)", Qt::CaseInsensitive),
                .endString = QRegExp(R"(\])", Qt::CaseInsensitive),
                .tokenString = QRegExp(R"()", Qt::CaseInsensitive),
                .mergeChildrenStripWhitespaceFromName = false,
                .canHaveTextInside = false,
                .searchEndStringLast = false,
                .immediateStartString = false,
                .onlyStartTag = false,
                .ignoreIfOnlyOneChild = false,
                .ignoreParentTokenEndString = false,
                .multiLine = false,
                .childrenStripWhitespaceFromName = false,
                .closeToken = -1,
                .nestedTokens = {8},
                .pushAndContinueWithTokens = {},
                .mergeChildren = {
                },
            },
            {
                .name = "ScriptBlockComment",
                .startString = QRegExp(R"(\/\*)", Qt::CaseInsensitive),
                .endString = QRegExp(R"(\*\/)", Qt::CaseInsensitive),
                .tokenString = QRegExp(R"()", Qt::CaseInsensitive),
                .mergeChildrenStripWhitespaceFromName = false,
                .canHaveTextInside = true,
                .searchEndStringLast = false,
                .immediateStartString = false,
                .onlyStartTag = false,
                .ignoreIfOnlyOneChild = false,
                .ignoreParentTokenEndString = false,
                .multiLine = false,
                .childrenStripWhitespaceFromName = false,
                .closeToken = -1,
                .nestedTokens = {13},
                .pushAndContinueWithTokens = {},
                .mergeChildren = {
                },
            },
            {
                .name = "ScriptLineComment",
                .startString = QRegExp(R"()", Qt::CaseInsensitive),
                .endString = QRegExp(R"()", Qt::CaseInsensitive),
                .tokenString = QRegExp(R"(//.*)", Qt::CaseInsensitive),
                .mergeChildrenStripWhitespaceFromName = false,
                .canHaveTextInside = true,
                .searchEndStringLast = false,
                .immediateStartString = false,
                .onlyStartTag = false,
                .ignoreIfOnlyOneChild = false,
                .ignoreParentTokenEndString = false,
                .multiLine = false,
                .childrenStripWhitespaceFromName = false,
                .closeToken = -1,
                .nestedTokens = {},
                .pushAndContinueWithTokens = {},
                .mergeChildren = {
                },
            },
            {
                .name = "SingleQuoteString",
                .startString = QRegExp(R"(')", Qt::CaseInsensitive),
                .endString = QRegExp(R"(')", Qt::CaseInsensitive),
                .tokenString = QRegExp(R"()", Qt::CaseInsensitive),
                .mergeChildrenStripWhitespaceFromName = false,
                .canHaveTextInside = false,
                .searchEndStringLast = true,
                .immediateStartString = false,
                .onlyStartTag = false,
                .ignoreIfOnlyOneChild = false,
                .ignoreParentTokenEndString = true,
                .multiLine = false,
                .childrenStripWhitespaceFromName = false,
                .closeToken = -1,
                .nestedTokens = {19, 20, 17},
                .pushAndContinueWithTokens = {},
                .mergeChildren = {
                },
            },
            {
                .name = "DoubleQuoteString",
                .startString = QRegExp(R"(")", Qt::CaseInsensitive),
                .endString = QRegExp(R"(")", Qt::CaseInsensitive),
                .tokenString = QRegExp(R"()", Qt::CaseInsensitive),
                .mergeChildrenStripWhitespaceFromName = false,
                .canHaveTextInside = false,
                .searchEndStringLast = true,
                .immediateStartString = false,
                .onlyStartTag = false,
                .ignoreIfOnlyOneChild = false,
                .ignoreParentTokenEndString = true,
                .multiLine = false,
                .childrenStripWhitespaceFromName = false,
                .closeToken = -1,
                .nestedTokens = {19, 20, 18},
                .pushAndContinueWithTokens = {},
                .mergeChildren = {
                },
            },
            {
                .name = "SingleQuoteCharacter",
                .startString = QRegExp(R"()", Qt::CaseInsensitive),
                .endString = QRegExp(R"()", Qt::CaseInsensitive),
                .tokenString = QRegExp(R"('')", Qt::CaseInsensitive),
                .mergeChildrenStripWhitespaceFromName = false,
                .canHaveTextInside = false,
                .searchEndStringLast = false,
                .immediateStartString = false,
                .onlyStartTag = false,
                .ignoreIfOnlyOneChild = false,
                .ignoreParentTokenEndString = false,
                .multiLine = false,
                .childrenStripWhitespaceFromName = false,
                .closeToken = -1,
                .nestedTokens = {},
                .pushAndContinueWithTokens = {},
                .mergeChildren = {
                },
            },
            {
                .name = "DoubleQuoteCharacter",
                .startString = QRegExp(R"()", Qt::CaseInsensitive),
                .endString = QRegExp(R"()", Qt::CaseInsensitive),
                .tokenString = QRegExp(R"("")", Qt::CaseInsensitive),
                .mergeChildrenStripWhitespaceFromName = false,
                .canHaveTextInside = false,
                .searchEndStringLast = false,
                .immediateStartString = false,
                .onlyStartTag = false,
                .ignoreIfOnlyOneChild = false,
                .ignoreParentTokenEndString = false,
                .multiLine = false,
                .childrenStripWhitespaceFromName = false,
                .closeToken = -1,
                .nestedTokens = {},
                .pushAndContinueWithTokens = {},
                .mergeChildren = {
                },
            },
            {
                .name = "SharpCharacter",
                .startString = QRegExp(R"()", Qt::CaseInsensitive),
                .endString = QRegExp(R"()", Qt::CaseInsensitive),
                .tokenString = QRegExp(R"(##)", Qt::CaseInsensitive),
                .mergeChildrenStripWhitespaceFromName = false,
                .canHaveTextInside = false,
                .searchEndStringLast = false,
                .immediateStartString = false,
                .onlyStartTag = false,
                .ignoreIfOnlyOneChild = false,
                .ignoreParentTokenEndString = false,
                .multiLine = false,
                .childrenStripWhitespaceFromName = false,
                .closeToken = -1,
                .nestedTokens = {},
                .pushAndContinueWithTokens = {},
                .mergeChildren = {
                },
            },
            {
                .name = "SharpExpression",
                .startString = QRegExp(R"(#)", Qt::CaseInsensitive),
                .endString = QRegExp(R"(#)", Qt::CaseInsensitive),
                .tokenString = QRegExp(R"()", Qt::CaseInsensitive),
                .mergeChildrenStripWhitespaceFromName = false,
                .canHaveTextInside = false,
                .searchEndStringLast = false,
                .immediateStartString = false,
                .onlyStartTag = false,
                .ignoreIfOnlyOneChild = false,
                .ignoreParentTokenEndString = false,
                .multiLine = false,
                .childrenStripWhitespaceFromName = false,
                .closeToken = -1,
                .nestedTokens = {8},
                .pushAndContinueWithTokens = {},
                .mergeChildren = {
                },
            },
            {
                .name = "Separator",
                .startString = QRegExp(R"()", Qt::CaseInsensitive),
                .endString = QRegExp(R"()", Qt::CaseInsensitive),
                .tokenString = QRegExp(R"(,)", Qt::CaseInsensitive),
                .mergeChildrenStripWhitespaceFromName = false,
                .canHaveTextInside = false,
                .searchEndStringLast = false,
                .immediateStartString = false,
                .onlyStartTag = false,
                .ignoreIfOnlyOneChild = false,
                .ignoreParentTokenEndString = false,
                .multiLine = false,
                .childrenStripWhitespaceFromName = false,
                .closeToken = -1,
                .nestedTokens = {},
                .pushAndContinueWithTokens = {},
                .mergeChildren = {
                },
            },
            {
                .name = "ExpressionEnd",
                .startString = QRegExp(R"()", Qt::CaseInsensitive),
                .endString = QRegExp(R"()", Qt::CaseInsensitive),
                .tokenString = QRegExp(R"(;)", Qt::CaseInsensitive),
                .mergeChildrenStripWhitespaceFromName = false,
                .canHaveTextInside = false,
                .searchEndStringLast = false,
                .immediateStartString = false,
                .onlyStartTag = false,
                .ignoreIfOnlyOneChild = false,
                .ignoreParentTokenEndString = false,
                .multiLine = false,
                .childrenStripWhitespaceFromName = false,
                .closeToken = -1,
                .nestedTokens = {},
                .pushAndContinueWithTokens = {},
                .mergeChildren = {
                },
            },
            {
                .name = "Number",
                .startString = QRegExp(R"()", Qt::CaseInsensitive),
                .endString = QRegExp(R"()", Qt::CaseInsensitive),
                .tokenString = QRegExp(R"([-+]?[0-9]*\.?[0-9]+)", Qt::CaseInsensitive),
                .mergeChildrenStripWhitespaceFromName = false,
                .canHaveTextInside = false,
                .searchEndStringLast = false,
                .immediateStartString = false,
                .onlyStartTag = false,
                .ignoreIfOnlyOneChild = false,
                .ignoreParentTokenEndString = false,
                .multiLine = false,
                .childrenStripWhitespaceFromName = false,
                .closeToken = -1,
                .nestedTokens = {},
                .pushAndContinueWithTokens = {},
                .mergeChildren = {
                },
            },
            {
                .name = "Boolean",
                .startString = QRegExp(R"()", Qt::CaseInsensitive),
                .endString = QRegExp(R"()", Qt::CaseInsensitive),
                .tokenString = QRegExp(R"((\btrue\b|\bfalse\b|\byes\b|\bno\b))", Qt::CaseInsensitive),
                .mergeChildrenStripWhitespaceFromName = false,
                .canHaveTextInside = false,
                .searchEndStringLast = false,
                .immediateStartString = false,
                .onlyStartTag = false,
                .ignoreIfOnlyOneChild = false,
                .ignoreParentTokenEndString = false,
                .multiLine = false,
                .childrenStripWhitespaceFromName = false,
                .closeToken = -1,
                .nestedTokens = {},
                .pushAndContinueWithTokens = {},
                .mergeChildren = {
                },
            },
            {
                .name = "Operator",
                .startString = QRegExp(R"()", Qt::CaseInsensitive),
                .endString = QRegExp(R"()", Qt::CaseInsensitive),
                .tokenString = QRegExp(R"((\bgreater\s+than\s+or\s+equal\s+to\b|\bless\s+than\s+or\s+equal\s+to\b|\bdoes\s+not\s+contain\b|\bgreater\s+than\b|\bnot\s+equal\b|\bless\s+than\b|\bcontains\b|\bis\s+not\b|\bequal\b|\+\+|\bmod\b|\bnot\b|\band\b|\bxor\b|\beqv\b|\bgte\b|\blte\b|\bimp\b|\bneq\b|\bis\b|\bor\b|\bgt\b|\bge\b|\blt\b|\ble\b|--|\+|\*|\\|\^|&&|\|\|\beq\b|\?|-|/|&|%|:|!|=))", Qt::CaseInsensitive),
                .mergeChildrenStripWhitespaceFromName = false,
                .canHaveTextInside = false,
                .searchEndStringLast = false,
                .immediateStartString = false,
                .onlyStartTag = false,
                .ignoreIfOnlyOneChild = false,
                .ignoreParentTokenEndString = false,
                .multiLine = false,
                .childrenStripWhitespaceFromName = false,
                .closeToken = -1,
                .nestedTokens = {},
                .pushAndContinueWithTokens = {},
                .mergeChildren = {
                },
            },
            {
                .name = "ObjectAccess",
                .startString = QRegExp(R"()", Qt::CaseInsensitive),
                .endString = QRegExp(R"()", Qt::CaseInsensitive),
                .tokenString = QRegExp(R"(\.)", Qt::CaseInsensitive),
                .mergeChildrenStripWhitespaceFromName = false,
                .canHaveTextInside = false,
                .searchEndStringLast = false,
                .immediateStartString = false,
                .onlyStartTag = false,
                .ignoreIfOnlyOneChild = false,
                .ignoreParentTokenEndString = false,
                .multiLine = false,
                .childrenStripWhitespaceFromName = false,
                .closeToken = -1,
                .nestedTokens = {},
                .pushAndContinueWithTokens = {},
                .mergeChildren = {
                },
            },
            {
                .name = "Keyword",
                .startString = QRegExp(R"()", Qt::CaseInsensitive),
                .endString = QRegExp(R"()", Qt::CaseInsensitive),
                .tokenString = QRegExp(R"((\bvar\b|\bfunction\b|\bthis\b|try\b|\bcatch\b|\bif\b|\bthen\b|\belse\b))", Qt::CaseInsensitive),
                .mergeChildrenStripWhitespaceFromName = false,
                .canHaveTextInside = false,
                .searchEndStringLast = false,
                .immediateStartString = false,
                .onlyStartTag = false,
                .ignoreIfOnlyOneChild = false,
                .ignoreParentTokenEndString = false,
                .multiLine = false,
                .childrenStripWhitespaceFromName = false,
                .closeToken = -1,
                .nestedTokens = {},
                .pushAndContinueWithTokens = {},
                .mergeChildren = {
                },
            },
            {
                .name = "Function",
                .startString = QRegExp(R"([a-z_]+[a-z0-9_]*[ \t]*\()", Qt::CaseInsensitive),
                .endString = QRegExp(R"(\))", Qt::CaseInsensitive),
                .tokenString = QRegExp(R"()", Qt::CaseInsensitive),
                .mergeChildrenStripWhitespaceFromName = false,
                .canHaveTextInside = false,
                .searchEndStringLast = false,
                .immediateStartString = false,
                .onlyStartTag = false,
                .ignoreIfOnlyOneChild = false,
                .ignoreParentTokenEndString = false,
                .multiLine = false,
                .childrenStripWhitespaceFromName = false,
                .closeToken = -1,
                .nestedTokens = {8},
                .pushAndContinueWithTokens = {},
                .mergeChildren = {
                },
            },
            {
                .name = "Variable",
                .startString = QRegExp(R"()", Qt::CaseInsensitive),
                .endString = QRegExp(R"()", Qt::CaseInsensitive),
                .tokenString = QRegExp(R"([a-z_]+[a-z0-9_]*)", Qt::CaseInsensitive),
                .mergeChildrenStripWhitespaceFromName = false,
                .canHaveTextInside = false,
                .searchEndStringLast = false,
                .immediateStartString = false,
                .onlyStartTag = false,
                .ignoreIfOnlyOneChild = false,
                .ignoreParentTokenEndString = false,
                .multiLine = false,
                .childrenStripWhitespaceFromName = false,
                .closeToken = -1,
                .nestedTokens = {},
                .pushAndContinueWithTokens = {},
                .mergeChildren = {
                },
            },
        },
        .startsWith = {0, 1, 2}
    };
}