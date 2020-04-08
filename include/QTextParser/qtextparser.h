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
#include "qtextparserlanguagedefinition.h"

#include <QStringList>
#include <QString>
#include <QVector>
#include <QRegExp>


class QTextParserElement
{
public:
    QTextParserElement() = default;
    QTextParserElement(const QTextParserElement &other) = default;

    inline QTextParserElement &operator=(QTextParserElement &&other) = default;
    inline QTextParserElement &operator=(const QTextParserElement &other) = default;

    inline QString asString() const {
        return QString("%1(%2) => %3:%4 - %5:%6").arg(
                    m_Text,
                    QString::number(m_Type),
                    QString::number(m_StartLine),
                    QString::number(m_StartColumn),
                    QString::number(m_EndLine),
                    QString::number(m_EndColumn));
    }

    int m_Type = -1;
    QString m_Text;
    int m_StartLine = -1;
    int m_StartColumn = -1;
    int m_EndLine = -1;
    int m_EndColumn = -1;
    QVector<QTextParserElement> m_ChildElements;
};
typedef QVector<QTextParserElement> QTextParserElements;


class QTextParserLine
{
public:
    enum QTextParserLineType
    {
        QTextParserLineTypeNoEndLine,
        QTextParserLineTypeCREndLine,
        QTextParserLineTypeLFEndLine,
        QTextParserLineTypeCRLFEndLine,
        QTextParserLineTypeLFCREndLine
    };

    QTextParserLine() = default;
    QTextParserLine(const QTextParserLine &other) = default;

    inline QTextParserLine &operator=(QTextParserLine &&other) = default;
    inline QTextParserLine &operator=(const QTextParserLine &other) = default;

    QString text;
    QTextParserLineType type;
};

typedef QVector<QTextParserLine> QTextParserLines;

class QTextParser
{
public:
    QTextParser() = default;
    QTextParser(const QTextParser &other) = default;

    inline QTextParser &operator=(QTextParser &&other) = default;
    inline QTextParser &operator=(const QTextParser &other) = default;

    static void loadParserDefinitionsFromDir(const QString &dir);
    void setTextTypeByFileExtension(const QString &fileExt);
    void setTextTypeByLanguageName(const QString &langName);
    QTextParserElements parseFile(const QString &fileName);
    QTextParserElements parseText(const QString &text, const QString &fileExt);
    QTextParserElements parseTextLines(const QTextParserLines &lines);
    QTextParserLanguageDefinition getLanguage() const;

protected:
    QTextParserElement parseElement(const QTextParserLines &lines, const QVector<int> &tokens, int &start_line, int &start_column, int end_line, int end_column, int end_token = -1);
    bool findFirstElement(const QTextParserLines &lines, int &cur_line, int &cur_column, const QVector<int> &tokens, int end_token);
    bool findFirstElement(const QString &line, int &cur_column, const QVector<int> &tokens, int end_token);
    QTextParserLanguageDefinition language;
    QTextParserLines lines;
};
