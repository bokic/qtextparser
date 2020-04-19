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


#include <QTextParser/QTextParser>

#include <QStringList>
#include <QTextStream>
#include <QFileInfo>
#include <QVector>
#include <QRegExp>
#include <QDebug>
#include <QFile>
#include <QDir>

#include <climits>


/* token_new:
 * Name
 * StartString
 * EndString
 * TokenString
 * OnlyStartTag(bool)Y
 * MultiLine(bool)Y
 * IgnoreParentTokenEndString(bool)Y
 * IgnoreIfOnlyOneChild(bool)Y
 * SearchEndStringLast(bool)Y
 ? ImmediateStartString(bool)
 ? CanHaveTextInside(bool)
 ? ChildrenStripWhitespaceFromName(bool)
 ** nested_tokens
 *** names
 ** merge_children */

static QVector<QTextParserLanguageDefinition> languageDefinitions;


QTextParserElements QTextParser::parseFile(const QString &fileName)
{
    QTextParserElements ret;
    QFileInfo finfo(fileName);

    QFile file(fileName);
    if (file.open(QIODevice::ReadOnly))
    {
        QTextStream ts;
        QTextParserLines fileLines;

        ts.setDevice(&file);
        ts.setCodec("UTF-8");
        ts.setAutoDetectUnicode(true);

        while(!ts.atEnd())
        {
            QTextParserLine line;
            line.text = ts.readLine();
            line.type = QTextParserLine::QTextParserLineTypeCRLFEndLine;
            fileLines.append(line);
        }

        file.close();

        QString fileExtension = finfo.suffix();

        //setTextTypeByFileExtension(fileExtension);

        ret = parseTextLines(fileLines);
    }

    return ret;
}

QTextParserElements QTextParser::parseText(const QString &text, const QString &fileExt)
{
    QTextParserElements ret;
    QTextParserLines fileLines;

    //setTextTypeByFileExtension(fileExt);

    for(const QString &curline: text.split(QRegExp("(\r\n|\n\r|\r|\n)")))
    {
        QTextParserLine line;
        line.text = curline;
        line.type = QTextParserLine::QTextParserLineTypeCRLFEndLine;
        fileLines.append(line);
    }

    fileLines.last().type = QTextParserLine::QTextParserLineTypeNoEndLine;

    ret = parseTextLines(fileLines);

    return ret;
}

QTextParserElements QTextParser::parseTextLines(const QTextParserLines &lines)
{
    QTextParserElements ret;

    this->lines = lines;

    if (lines.count() <= 0)
    {
        return ret;
    }

    int cur_lines = 0;
    int cur_column = 0;

    int end_lines = lines.count() - 1;

    while(true)
    {
        if (!findFirstElement(lines, cur_lines, cur_column, language.startsWith, -1))
        {
            break;
        }

        int end_column = lines.at(cur_lines).text.length();

        QTextParserElement token = parseElement(lines, language.startsWith, cur_lines, cur_column, end_lines, end_column);

        ret.append(token);

        if (token.m_Type < 0)
        {
            break;
        }
    }

    return ret;
}

QTextParserLanguageDefinition QTextParser::getLanguage() const
{
    return language;
}

QTextParserElement QTextParser::parseElement(const QTextParserLines &lines, const QVector<int> &tokens, int &start_line, int &start_column, int end_line, int end_column, int end_token)
{
    QTextParserElement ret;
    bool found;

    const int orig_start_line = start_line;
    const int orig_start_column = start_column;

    found = findFirstElement(lines, start_line, start_column, tokens, end_token);

    if ((found == false)||(start_line > end_line)||((start_line == end_line)&&(start_column >= end_column)))
    {
        return ret;
    }

    const QVector<QTextParserLanguageDefinitionToken> &tokenList = language.tokens;

    if (end_token >= 0)
    {
        if (tokenList[end_token].searchEndStringLast == false)
        {
            const QRegExp &reg = tokenList[end_token].endString;
            int index = reg.indexIn(lines.at(start_line).text, start_column);

            if (index == start_column)
            {
                return ret;
            }
        }
    }

    for(const int &nToken: tokens)
    {
        const QTextParserLanguageDefinitionToken &token = tokenList.at(nToken);

        if ((!token.startString.isEmpty())&&(!token.endString.isEmpty())&&(token.tokenString.isEmpty()))
        {
            const QRegExp &reg = token.startString;
            int index = reg.indexIn(lines.at(start_line).text, start_column);

            if (index == start_column)
            {
                if (token.immediateStartString)
                {
                    ret.m_StartLine = orig_start_line;
                    ret.m_StartColumn = orig_start_column;
                }
                else
                {
                    ret.m_StartLine = start_line;
                    ret.m_StartColumn = start_column;
                }

                start_column += reg.cap().length();

                if (token.onlyStartTag == true)
                {
                    ret.m_EndLine = start_line;
                    ret.m_EndColumn = start_column;
                }

                while(1)
                {
                    QTextParserElement child;

                    while(1)
                    {
                        if (start_line >= lines.count())
                        {
                            start_line = lines.count() - 1;
                            return QTextParserElement();
                        }

                        child = parseElement(lines, token.nestedTokens, start_line, start_column, end_line, end_column, nToken);

                        if (child.m_Type == -1)
                        {
                            break;
                        }

                        ret.m_ChildElements.append(child);
                    }

                    if ((token.multiLine == false)||(child.m_Type == -1))
                    {
                        break;
                    }

                    const QRegExp &reg = token.endString;
                    int index = reg.indexIn(lines.at(start_line).text, start_column);

                    if (index == start_column)
                    {
                        break;
                    }

                    start_line++;
                    start_column = 0;
                }

                /*if (token.excludeTopLevelChild)
                {
                    QVector<QTextParserElement> oldChildrens = ret.m_ChildElements;

                    ret.m_ChildElements.clear();

                    for(QTextParserElement oldChild: oldChildrens)
                    {
                        for(QTextParserElement oldGrandChild: oldChild.m_ChildElements)
                        {
                            ret.m_ChildElements.append(oldGrandChild);
                        }
                    }
                }
                else*/ if (token.ignoreIfOnlyOneChild)
                {
                    if (ret.m_ChildElements.count() == 1)
                    {
                        ret.m_ChildElements = ret.m_ChildElements.at(0).m_ChildElements;
                    }
                }

                const QRegExp &reg = token.endString;
                int index = reg.indexIn(lines.at(start_line).text, start_column);

                if (index == start_column)
                {
                    if (token.onlyStartTag == false)
                    {
                        start_column += reg.cap().count();
                        ret.m_EndLine = start_line;
                        ret.m_EndColumn = start_column;
                    }

                    ret.m_Type = nToken;
                }
                else
                {
                    ret.m_Text = "End segment NOT found!";
                    ret.m_Type = -1;
                }
                break;
            }
        }
        else if ((token.startString.isEmpty())&&(token.endString.isEmpty())&&(token.tokenString.isEmpty())&&(token.nestedTokens.count() > 0)&&(end_token >= 0))
        {
            if (token.immediateStartString)
            {
                ret.m_StartLine = orig_start_line;
                ret.m_StartColumn = orig_start_column;
            }
            else
            {
                ret.m_StartLine = start_line;
                ret.m_StartColumn = start_column;
            }

            while(1)
            {
                QTextParserElement child = parseElement(lines, token.nestedTokens, start_line, start_column, end_line, end_column, end_token);

                if (child.m_Type == -1)
                {
                    break;
                }

                ret.m_ChildElements.append(child);
            }

            const QRegExp &reg = token.endString;
            int index = reg.indexIn(lines.at(start_line).text, start_column);

            if (index == start_column)
            {
                start_column += reg.cap().count();

                ret.m_EndLine = start_line;
                ret.m_EndColumn = start_column;
                ret.m_Type = nToken;
                if (token.ignoreIfOnlyOneChild)
                {
                    if (ret.m_ChildElements.count() == 1)
                    {
                        ret = ret.m_ChildElements.at(0);
                    }
                }
                break;
            }
            else
            {
                ret.m_Text = "End segment NOT found!";
                ret.m_Type = -1;
            }
        }
        else if ((token.startString.isEmpty())&&(token.endString.isEmpty())&&(!token.tokenString.isEmpty())&&(token.nestedTokens.count() == 0))
        {
            const QRegExp &reg = token.tokenString;
            int index = reg.indexIn(lines.at(start_line).text, start_column);

            if (index == start_column)
            {
                if (token.immediateStartString)
                {
                    ret.m_StartLine = orig_start_line;
                    ret.m_StartColumn = orig_start_column;
                }
                else
                {
                    ret.m_StartLine = start_line;
                    ret.m_StartColumn = start_column;
                }
                ret.m_Text = reg.cap();

                start_column += reg.cap().count();

                ret.m_EndLine = start_line;
                ret.m_EndColumn = start_column;
                ret.m_Type = nToken;
                break;
            }
        }
        else
        {
            qDebug() << "Invalid nested tokens coombination.";
        }
    }

    if (end_token >= 0)
    {
        if (tokenList[end_token].searchEndStringLast == true)
        {
            const QRegExp &reg = tokenList[end_token].endString;
            int index = reg.indexIn(lines.at(start_line).text, start_column);

            if (index == start_column)
            {
                return ret;
            }
        }
    }

    return ret;
}

bool QTextParser::findFirstElement(const QTextParserLines &lines, int &cur_line, int &cur_column, const QVector<int> &tokens, int end_token)
{
    for(int line = cur_line; line < lines.count(); line++)
    {
        bool found;
        int col;

        if (line == cur_line)
        {
            col = cur_column;
        }
        else
        {
            col = 0;
        }

        found = findFirstElement(lines.at(line).text, col, tokens, end_token);

        if (found)
        {
            cur_line = line;
            cur_column = col;

            return true;
        }
    }

    return false;
}

bool QTextParser::findFirstElement(const QString &line, int &cur_column, const QVector<int> &tokens, int end_token)
{
    bool ret = false;

    int closest_index = INT_MAX;

    if (end_token >= 0)
    {
        while(true)
        {
            if (language.tokens.count() <= end_token)
            {
                qDebug() << "tokens.key count("<< language.tokens.count() << ") is too low. At least" << (end_token + 1) << "needed. File:" << __FILE__ << ", line:" << __LINE__;

                break;
            }

            const QRegExp &reg = language.tokens.at(end_token).endString;
            int index = reg.indexIn(line, cur_column);

            if (index < 0)
            {
                break;
            }

            closest_index = index;
            ret = true;

            break;
        }
    }

    for (int c = 0; c < tokens.count(); c++)
    {
        int nToken = tokens.at(c);
        const QTextParserLanguageDefinitionToken &token = language.tokens.at(nToken);

        if ((nToken < 0)||(nToken >= language.tokens.count()))
        {
            qDebug() << "Token out of range(" << nToken << "). File:" << __FILE__ << ", line:" << __LINE__;
            continue;
        }

        if (!token.tokenString.isEmpty())
        {
            const QRegExp &reg = token.tokenString;
            int index = reg.indexIn(line, cur_column);

            if ((index > -1)&&(index < closest_index))
            {
                closest_index = index;
                ret = true;

                if (closest_index == cur_column)
                {
                    break;
                }
            }
        }
        else if (!token.startString.isEmpty())
        {
            const QRegExp &reg = token.startString;
            int index = reg.indexIn(line, cur_column);

            if ((index > -1)&&(index < closest_index))
            {
                closest_index = index;
                ret = true;

                if (closest_index == cur_column)
                {
                    break;
                }
            }
        }
        else if (token.nestedTokens.count() > 0)
        {
            int tmp_col = cur_column;

            if (findFirstElement(line, tmp_col, token.nestedTokens, -1))
            {
                if ((tmp_col > -1)&&(tmp_col < closest_index))
                {
                    closest_index = tmp_col;
                    ret = true;

                    if (closest_index == cur_column)
                    {
                        break;
                    }
                }
            }
        }
        else
        {
            qDebug() << "Parser error. Token(" << nToken << ") has empty tokenString and startString. File:" << __FILE__ << ", line:" << __LINE__;
            continue;
        }
    }

    if (ret)
    {
        cur_column = closest_index;
    }

    return ret;
}
