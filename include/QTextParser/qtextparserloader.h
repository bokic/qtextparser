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

#include "qtextparserlanguagedefinition.h"
#include <QException>
#include <QVector>
#include <QDir>

namespace QTextParserLoader {
    QVector<QTextParserLanguageDefinition> loadDefinitionsFromDir(const QDir &dir);
    QTextParserLanguageDefinition loadDefinitionFromXmlFile(const QString &filepath);

    class QTextParserLoaderException: public QException {
    public:
        QTextParserLoaderException(const QString &error): m_error(error) {}
#if __cplusplus >= 201103L
        QTextParserLoaderException(const QTextParserLoaderException&) = default;
        QTextParserLoaderException& operator=(const QTextParserLoaderException&) = default;
        QTextParserLoaderException& operator=(QTextParserLoaderException&&) = default;
        QTextParserLoaderException(QTextParserLoaderException&&) = default;
#endif
        void raise() const override { throw *this; }
        QTextParserLoaderException *clone() const override { return new QTextParserLoaderException(*this); }
        virtual const char *what() const _GLIBCXX_TXN_SAFE_DYN _GLIBCXX_NOTHROW override { return m_error.toUtf8().constData(); }

    private:
        QString m_error;
    };
}
