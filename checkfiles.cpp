#include "checkfiles.h"
#include "./ui_checkfiles.h"
#include <QCoreApplication>




CheckFiles::CheckFiles(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::CheckFiles)
{
    ui->setupUi(this);
}

CheckFiles::~CheckFiles()
{
    delete ui;
}
