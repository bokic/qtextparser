#pragma once

#include "qtextparserlanguagedefinition.h"
#include <QVector>
#include <QDir>


QVector<QTextParserLanguageDefinition> loadDefinitionsFromDir(const QDir &dir);
