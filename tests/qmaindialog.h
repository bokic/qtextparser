#pragma once

#include <QListWidgetItem>
#include <QDialog>
#include <QString>
#include <QHash>

#include "ui_qmaindialog.h"

class QMainDialog : public QDialog
{
    Q_OBJECT

public:
    QMainDialog(QWidget *parent = nullptr, Qt::WindowFlags flags = nullptr);

private:
    void parseDir(const QString &dir);

private slots:
    void on_listWidget_itemDoubleClicked(QListWidgetItem *item);
    void on_pushButton_clicked();

private:
    QHash<QString, int> m_tagsHash;
    QHash<QString, int> m_functionsHash;
    Ui::QMainDialog ui;
};
