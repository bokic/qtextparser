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

    QString name;
    QString description;
    QString version;
    QString emptySegmentsLanguage;
    Qt::CaseSensitivity caseSensitivity = Qt::CaseSensitive;
    QStringList defaultExtensions;
    QVector<QTextParserLanguageDefinitionToken> tokens;
    QVector<int> startsWith;

    QStringList tokenNames;
};
