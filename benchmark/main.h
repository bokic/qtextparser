#pragma once
#include <QObject>
#include <QVector>


class TestCases : public QObject
{
    Q_OBJECT
private slots:
    void initTestCase();
    void benchmarkLoadFromXML();
    void parseFiles();
    void cleanupTestCase();

private:
    QVector<int> m_TotalElements;
};
