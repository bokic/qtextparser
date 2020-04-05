#include "main.h"
#include <QTextParser/QTextParser>
#include <QTest>


static QFileInfoList files;
static int totalElements = 0;

void TestCases::initTestCase()
{
    QTextParser::loadParserDefinitionsFromDir("../definitions");

    QDir d;
    d.setFilter(QDir::Files | QDir::AllDirs | QDir::NoDotAndDotDot);
    d.setSorting(QDir::DirsFirst | QDir::Name);
    QStringList filters;
    filters << "*.cfm" << "*.cfc";
    d.setNameFilters(filters);
    files = d.entryInfoList();
}

void TestCases::parseFiles()
{
    QTextParserElements elements;
    QTextParser parser;

    QBENCHMARK
    {
        for(const auto &fileinfo: files)
        {
            elements = parser.parseFile(fileinfo.filePath());
            totalElements += elements.count();
        }
    }
}

void TestCases::cleanupTestCase()
{
    qDebug() << "Total Elements:" << totalElements;
}

QTEST_MAIN(TestCases)
