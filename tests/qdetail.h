#pragma once

#include <QTextParser/QTextParser>
#include <QTreeWidgetItem>
#include <QDialog>
#include <QVector>
#include <QColor>

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
    QVector<QColor> m_ElementTextColors;
    QVector<QColor> m_ElementBackgroundColors;
    QString m_selectedItemString;
};
