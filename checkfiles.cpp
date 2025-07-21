#include "checkfiles.h"
#include "./ui_checkfiles.h"
#include <QCoreApplication>
//#include "mainwindow.h"
//#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QFileInfo>
#include <QFile>



CheckFiles::CheckFiles(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::CheckFiles)
{
    ui->setupUi(this);

    connect(ui->btnChooseSource, &QPushButton::clicked, this, &CheckFiles::chooseSourceDir);
    connect(ui->btnChooseTarget, &QPushButton::clicked, this, &CheckFiles::chooseTargetDir);
    connect(ui->btnStart, &QPushButton::clicked, this, &CheckFiles::startMonitoring);//CheckFiles::on_btnStop_clicked()
    connect(ui->btnStop, &QPushButton::clicked,this, &CheckFiles::on_btnStop_clicked);
    ui->btnStop->setEnabled(false);

}

CheckFiles::~CheckFiles()
{
    delete ui;
}

void CheckFiles::chooseSourceDir() {
    sourceDir = QFileDialog::getExistingDirectory(this, "Wybierz folder źródłowy");
    ui->lineSource->setText(sourceDir);
    //todo: dodac do DB
}

void CheckFiles::chooseTargetDir() {
    targetDir = QFileDialog::getExistingDirectory(this, "Wybierz folder docelowy");
    ui->lineTarget->setText(targetDir);
    //todo: dodac do DB
}

void CheckFiles::startMonitoring() {
    if (sourceDir.isEmpty() || targetDir.isEmpty()) {
        log("Wybierz oba foldery najpierw!");


        return;
    }

    watcher.addPath(sourceDir);
    connect(&watcher, &QFileSystemWatcher::directoryChanged, this, &CheckFiles::onDirectoryChanged);
    log("Monitoring rozpoczęty...");
    ui->btnStart->setEnabled(false);
    ui->btnStop->setEnabled(true);
}

void CheckFiles::onDirectoryChanged(const QString& path) {
    QDir dir(sourceDir);
    QFileInfoList files = dir.entryInfoList(QDir::Files);
    for (const QFileInfo& file : files)
        syncFile(file.filePath());
}

void CheckFiles::syncFile(const QString& path) {
    QFileInfo fi(path);
    QString destPath = targetDir + "/" + fi.fileName();
    if (QFile::exists(path)) {
        QFile::remove(destPath);
        if (QFile::copy(path, destPath)) {
            log("Skopiowano: " + fi.fileName());
        } else {
            log("Błąd kopiowania: " + fi.fileName());
        }
    }
}

void CheckFiles::log(const QString& message) {
    ui->logBox->appendPlainText(QTime::currentTime().toString() + " - " + message);
}

void CheckFiles::on_btnStop_clicked()
{
    //todo: rozszerszzyc to działanie
    ui->btnStart->setEnabled(true);
    ui->btnStop->setEnabled(false);
    watcher.disconnect();
    log("Monitoring zakończony...");
}

