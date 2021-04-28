#include "qmaindialog.h"
#include <QTextParser/QTextParser>
#include "qdetail.h"

#include <QListWidgetItem>
#include <QFileInfoList>
#include <QFileDialog>
#include <QColor>
#include <QDir>

QMainDialog::QMainDialog()
    : QDialog()
{
    ui.setupUi(this);
    setWindowFlags(windowFlags() | Qt::WindowMinMaxButtonsHint);

    //QTextParser::loadParserDefinitionsFromDir("../definitions");
}

void QMainDialog::parseDir(const QString &dir)
{
    QDir d(dir);

    d.setFilter(QDir::Files | QDir::AllDirs | QDir::NoDotAndDotDot);
    d.setSorting(QDir::DirsFirst | QDir::Name);
    QStringList filters;
    filters << "*.cfm" << "*.cfc";
    d.setNameFilters(filters);
    QFileInfoList files = d.entryInfoList();

    for (const auto &fileinfo: files)
    {
        if (fileinfo.isDir() == true)
        {
            parseDir(fileinfo.absoluteFilePath());
        }
        else
        {
            QString itemFileName = QDir::toNativeSeparators(fileinfo.filePath());
            QListWidgetItem *lastItem = new QListWidgetItem(itemFileName);
            lastItem->setData(Qt::UserRole, fileinfo.filePath());
            QTextParser parser;

            setWindowTitle("Processing - " + fileinfo.fileName());
            qApp->processEvents();

            parser.parseFile(fileinfo.absoluteFilePath());

            ui.listWidget->addItem(lastItem);

             qApp->processEvents();
        }
    }

    setWindowTitle("QTextParser test");
}

void QMainDialog::on_pushButton_clicked()
{
    QFileDialog dialog(this);
    QStringList keys;

    dialog.setFileMode(QFileDialog::Directory);
    dialog.setOption(QFileDialog::ShowDirsOnly);

    if (dialog.exec() != QDialog::Accepted)
    {
        return;
    }

    ui.listWidget->clear();
    m_tagsHash.clear();
    m_functionsHash.clear();

    parseDir(dialog.directory().absolutePath());

    ui.listWidget->addItem(new QListWidgetItem("-------------------- CF Tags stats -------------------------"));

    keys = m_tagsHash.keys();
    keys.sort();

    for (const QString &key: qAsConst(keys))
    {
        ui.listWidget->addItem(new QListWidgetItem(key + " = " + QString::number(m_tagsHash[key])));
    }

    ui.listWidget->addItem(new QListWidgetItem("-------------------- CF Functions stats -------------------------"));

    keys = m_functionsHash.keys();
    keys.sort();

    for (const QString &key: qAsConst(keys))
    {
        ui.listWidget->addItem(new QListWidgetItem(key + " = " + QString::number(m_functionsHash[key])));
    }

    ui.listWidget->scrollToBottom();
}

void QMainDialog::on_listWidget_itemDoubleClicked(QListWidgetItem *item)
{
    QString file;

    file = item->data(Qt::UserRole).toString();


    if (file.isEmpty())
        return;

    QDetail detailForm(this);

    detailForm.setFileForParsing(file);
    detailForm.setModal(true);

    detailForm.exec();
}
