#include <QVBoxLayout>
#include <QFileDialog>
#include <QMessageBox>
#include <iostream>
#include <sstream>
#include "TreeWidget.h"

TreeWidget::TreeWidget(QWidget *parent) : QWidget(parent) {
    mainLayout = new QVBoxLayout();
    treeLayout = new QVBoxLayout();
    buttonLayout = new QHBoxLayout();

    tree = new QTreeWidget(this);
    uploadButton = new QPushButton(this);
    downloadButton = new QPushButton(this);
    getFilesButton = new QPushButton(this);

    mainLayout->setAlignment(Qt::AlignCenter);
    setLayout(mainLayout);

    mainLayout->addItem(treeLayout);
    mainLayout->addItem(buttonLayout);

    treeLayout->addWidget(tree);
    buttonLayout->addWidget(uploadButton);
    buttonLayout->addWidget(downloadButton);
    buttonLayout->addWidget(getFilesButton);

    uploadButton->setText("Upload file");
    downloadButton->setText("Download file");
    getFilesButton->setText("Sync");


    connect(getFilesButton, SIGNAL(clicked()), this, SLOT(request_tree()));
    connect(tree, &QTreeWidget::itemClicked, this, [this] { this->lastItemClicked = this->tree->currentItem(); });
    connect(downloadButton, SIGNAL(clicked()), this, SLOT(request_download()));
    connect(uploadButton, SIGNAL(clicked()), this, SLOT(request_upload()));
}

TreeWidget::~TreeWidget() {
    buttonLayout->removeWidget(downloadButton);
    buttonLayout->removeWidget(uploadButton);

    mainLayout->removeItem(buttonLayout);
    mainLayout->removeWidget(tree);

    delete uploadButton;
    delete downloadButton;
    delete buttonLayout;
    delete tree;
    delete mainLayout;
}


#include "../common/functions.h"
#include "MainWindow.h"

void TreeWidget::request_tree() {
    auto parent = dynamic_cast<MainWindow *>(this->parent());

    std::string user = parent->username;

    write_message(parent->s, "REQ_TREE");
    write_message(parent->s, parent->username);

    string server_response;
    read_message(parent->s, server_response);

    if (server_response != "RESP_PATHS") {
        return;
    }

    read_message(parent->s, server_response);

    stringstream ss(server_response);
    string path;
    path_list.clear();
    while (ss >> path) {
        path_list.push_back(QString::fromStdString(path));
    }

    populateTree(path_list);

}

void TreeWidget::populateTree(QStringList &fileNames) {
    tree->clear();
    QTreeWidgetItem *topLevelItem = nullptr;

            foreach(const QString &filename, fileNames) {
            QStringList splitFileName = filename.split('/');

            if (tree->findItems(splitFileName[0], Qt::MatchFixedString).isEmpty()) {
                topLevelItem = new QTreeWidgetItem;
                topLevelItem->setText(0, splitFileName[0]);
                tree->addTopLevelItem(topLevelItem);
            }

            QTreeWidgetItem *parentItem = topLevelItem;

            for (int i = 1; i < splitFileName.size() - 1; i++) {
                bool dirExists = false;

                for (int j = 0; j < parentItem->childCount(); j++) {

                    if (splitFileName[i] == parentItem->child(j)->text(0)) {
                        dirExists = true;
                        parentItem = parentItem->child(j);
                    }
                }
                if (!dirExists) {
                    parentItem = new QTreeWidgetItem(parentItem);
                    parentItem->setText(0, splitFileName[i]);
                    parentItem->setText(1, filename);
                }
            }
            QTreeWidgetItem *childItem = new QTreeWidgetItem(parentItem);
            childItem->setText(0, splitFileName.last());
            childItem->setText(1, filename);

        }
}

#include "../common/functions.h"

void TreeWidget::request_download() {
    auto parent = dynamic_cast<MainWindow *>(this->parent());
    auto item = this->tree->currentItem();

    if (item == nullptr)
        return;

    // trimitem un mesaj de request de domwnload
    // apoi trimitem path-ul fisierului pe care vrem sa il descarcam
    write_message(parent->s, "REQ_DOWNLOAD");
    write_message(parent->s, item->text(1).toStdString());

    string resp;

    // verificam daca s-a inceput transferul
    read_message(parent->s, resp);
    if (resp == "INIT_SEND") {
        receive_file(parent->s, "../client/" + item->text(1).toStdString());
    }
    QMessageBox::information(this, "Download Status", "Download finished");
}

void TreeWidget::connectTree() {
    connect(downloadButton, SIGNAL(tree->itemClicked()), this, SLOT(request_download(tree->currentItem())));
}

void TreeWidget::request_upload() {
    auto parent = dynamic_cast<MainWindow *>(this->parent());
    auto path = QFileDialog::getOpenFileName(this, "Select file", "/home");
    string resp;

    write_message(parent->s, "REQ_UPLOAD");
    write_message(parent->s, parent->username);
    write_message(parent->s, path.toStdString());

    send_file(parent->s, path.toStdString());
    write_message(parent->s, "FIN_SEND");

    read_message(parent->s, resp);
    if(resp == "FIN_GET")
        QMessageBox::information(this, "Upload Status", "Upload finished");
}
