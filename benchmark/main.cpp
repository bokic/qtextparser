#include "main.h"
#include <QTextParser/QTextParserLoader>
#include <QTextParser/QTextParser>
#include <QTest>


static QFileInfoList files;
static int totalElements = 0;
static int totalIterations = 0;

void TestCases::initTestCase()
{
    QDir d;
    d.setFilter(QDir::Files | QDir::AllDirs | QDir::NoDotAndDotDot);
    d.setSorting(QDir::DirsFirst | QDir::Name);
    QStringList filters;
    filters << "*.cfm" << "*.cfc";
    d.setNameFilters(filters);
    files = d.entryInfoList();

    qDebug() << "Number of files:" << files.count();
}

void TestCases::benchmarkLoadFromXML()
{
    QTextParserLanguageDefinition CFMLlanguageDefinition;

    QBENCHMARK
    {
        CFMLlanguageDefinition = QTextParserLoader::loadDefinitionFromXmlFile("../definitions/ColdFusion.xml");
    }
}

void TestCases::parseFiles()
{
    QTextParserLanguageDefinition CFMLlanguageDefinition;
    QTextParserElements elements;
    QTextParser parser;

    CFMLlanguageDefinition = QTextParserLoader::loadDefinitionFromXmlFile("../definitions/ColdFusion.xml");

    parser.setLanguage(CFMLlanguageDefinition);

    QBENCHMARK
    {
        for(const auto &fileinfo: qAsConst(files))
        {
            if (parser.parseFile(fileinfo.filePath()))
            {
                totalElements += parser.parserElements().count();
            }
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
