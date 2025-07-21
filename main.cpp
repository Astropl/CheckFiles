#include "checkfiles.h"

#include <QApplication>

#include <QCoreApplication>
#include <QFileSystemWatcher>
#include <QDir>
#include <QFileInfo>
#include <QDebug>
#include <QFile>
#include <QTimer>
#include <QDateTime>

QString watchDir = "C:/Users/pmartys/Documents/test";
QString syncDir  = "C:/Users/pmartys/Documents/TestBackup";
void syncFile(const QString& filePath);

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QFileSystemWatcher watcher;

    // Dodajemy katalog do nasłuchu
    watcher.addPath(watchDir);
    qDebug() << "Nasłuchuję katalog:" << watchDir;

    QObject::connect(&watcher, &QFileSystemWatcher::directoryChanged,
                     [&](const QString &path) {
                         qDebug() << "Zmieniono katalog:" << path;

                         QDir dir(watchDir);
                         QFileInfoList files = dir.entryInfoList(QDir::Files);

                         for (const QFileInfo& file : files) {
                             syncFile(file.filePath());
                         }
                     });

    // Możesz też nasłuchiwać konkretnych plików:
    // watcher.addPath("C:/do_nasluchu/test.txt");






    CheckFiles w;
    w.show();
    return a.exec();
}
void syncFile(const QString& filePath) {
    QFileInfo fileInfo(filePath);
    QString fileName = fileInfo.fileName();
    QString destPath = syncDir + "/" + fileName;

    if (QFile::exists(filePath)) {
        if (QFile::copy(filePath, destPath)) {
            qDebug() << "Skopiowano plik:" << filePath << "->" << destPath;
        } else {
            QFile::remove(destPath); // usuń stary i spróbuj jeszcze raz
            if (QFile::copy(filePath, destPath))
                qDebug() << "Zastąpiono plik:" << destPath;
            else
                qDebug() << "Błąd kopiowania:" << filePath;
        }
    }
    if (QFile::exists(destPath)) {
        if (QFile::copy(destPath, filePath)) {
            qDebug() << "Re: Skopiowano plik:" << destPath << "->" << filePath;
        } else {
            QFile::remove(filePath); // usuń stary i spróbuj jeszcze raz
            if (QFile::copy(destPath, filePath))
                qDebug() << "Re: Zastąpiono plik:" << filePath;
            else
                qDebug() << "Re: Błąd kopiowania:" << destPath;
        }
    }
}
