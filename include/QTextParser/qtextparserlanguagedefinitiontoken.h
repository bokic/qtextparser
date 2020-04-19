#pragma once

/****************************************************************************
**
** Author: Boris Barbulovski(bbarbulovski@gmail.com)
**
** This file is part of the QTextParser(https://github.com/bokic/qtextparser) library.
**
** $QT_BEGIN_LICENSE:LGPL$
**
** GNU General Public License Usage
** This file may be used under the terms of the GNU
** General Public License version 3.0 as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU General Public License version 3.0 requirements will be
** met: http://www.gnu.org/copyleft/gpl.html.
**
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "qtextparserlanguagedefinitionmergechildren.h"
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
    bool mergeChildrenStripWhitespaceFromName = false;
    bool canHaveTextInside = false;
    bool searchEndStringLast = false;
    bool immediateStartString = false;
    bool onlyStartTag = false;
    bool ignoreIfOnlyOneChild = false;
    bool ignoreParentTokenEndString = false;
    bool multiLine = false;
    bool childrenStripWhitespaceFromName = false;
    int closeToken = -1;
    QVector<int> nestedTokens;
    QVector<int> pushAndContinueWithTokens;
    QVector<QTextParserLanguageDefinitionMergeChildren> mergeChildren;
};
