#pragma once
#include <QObject>


class TestCases : public QObject
{
    Q_OBJECT
private slots:
    void initTestCase();
    void parseFiles();
    void cleanupTestCase();
};
