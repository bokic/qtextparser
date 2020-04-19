#include "main.h"
#include <QTextParser/QTextParserLoader>
#include <QTextParser/QTextParser>
#include <QTest>


static QFileInfoList files;
static int totalElements = 0;
static int totalIterations = 0;

void TestCases::initTestCase()
{
    QTextParserLoader::loadDefinitionsFromDir(QDir("../definitions"));

    QDir d;
    d.setFilter(QDir::Files | QDir::AllDirs | QDir::NoDotAndDotDot);
    d.setSorting(QDir::DirsFirst | QDir::Name);
    QStringList filters;
    filters << "*.cfm" << "*.cfc";
    d.setNameFilters(filters);
    files = d.entryInfoList();

    qDebug() << "Number of files:" << files.count();
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

        totalIterations++;
    }
}

void TestCases::cleanupTestCase()
{
    qDebug() << "Total Elements:" << totalElements;
    qDebug() << "Total Iterations:" << totalIterations;
    qDebug() << "Elements per iteration:" << totalElements / totalIterations;
}

QTEST_MAIN(TestCases)
