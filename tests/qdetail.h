#pragma once

#include <QTextParser/QTextParser>
#include <QTreeWidgetItem>
#include <QDialog>
#include <QColor>
#include <QList>

namespace Ui
{
class QDetail;
}

class QDetail : public QDialog
{
    Q_OBJECT

public:
    explicit QDetail(QWidget *parent = nullptr);
    virtual ~QDetail();

    void setFileForParsing(const QString &file);

private slots:
    void on_parser_treeWidget_currentItemChanged(QTreeWidgetItem *current, QTreeWidgetItem *previous);

private:
    Ui::QDetail *ui;

    void addSubTrees(const QTextParserElement &element, QTreeWidgetItem *widgetItem);
    void recolor();
    int getTextPos(int line, int column);
    void colorElement(const QTextParserElement &element);

    QTextParser m_Parser;
    QStringList m_FileLines;

    QTextParserElements elements;
    QList<QColor> m_ElementTextColors;
    QList<QColor> m_ElementBackgroundColors;
    QString m_selectedItemString;
};
