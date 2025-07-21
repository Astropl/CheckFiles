#ifndef CHECKFILES_H
#define CHECKFILES_H
#include <QFileSystemWatcher>
#include <QString>
#include <QDir>
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class CheckFiles;
}
QT_END_NAMESPACE

class CheckFiles : public QMainWindow
{
    Q_OBJECT

public:
    CheckFiles(QWidget *parent = nullptr);
    ~CheckFiles();

private slots:
    void chooseSourceDir();
    void chooseTargetDir();
    void startMonitoring();
    void onDirectoryChanged(const QString& path);

private:
    void syncFile(const QString& path);
    void log(const QString& message);

    //Ui::MainWindow *ui;
    QFileSystemWatcher watcher;
    QString sourceDir;
    QString targetDir;


private:
    Ui::CheckFiles *ui;
};
#endif // CHECKFILES_H
