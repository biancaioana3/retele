#ifndef MYFTP_BI_TREEWIDGET_H
#define MYFTP_BI_TREEWIDGET_H


#include <QWidget>
#include <QPushButton>
#include <QTreeWidget>

class TreeWidget : public QWidget{

    Q_OBJECT

public:

    TreeWidget(QWidget * parent = nullptr);
    ~TreeWidget() override;
    void populateTree(QStringList &filenames);
    void connectTree();

private:

    QLayout * mainLayout;
    QLayout * treeLayout;
    QLayout * buttonLayout;

    QTreeWidget * tree;
    QPushButton * uploadButton;
    QPushButton * downloadButton;
    QPushButton * getFilesButton;

    QStringList path_list;

    QTreeWidgetItem * lastItemClicked;
    QTreeWidgetItem * rootItem;

public slots:
    void request_tree();
    void request_download();
    void request_upload();

};


#endif //MYFTP_BI_TREEWIDGET_H
