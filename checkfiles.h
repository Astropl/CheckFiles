#ifndef CHECKFILES_H
#define CHECKFILES_H

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

private:
    Ui::CheckFiles *ui;
};
#endif // CHECKFILES_H
