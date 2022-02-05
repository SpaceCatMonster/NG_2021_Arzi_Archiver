#ifndef ARZI_H
#define ARZI_H

#include <QMainWindow>
#include <QFileDialog>
#include <QDir>


QT_BEGIN_NAMESPACE
namespace Ui { class arzi; }
QT_END_NAMESPACE

class arzi : public QMainWindow
{
    Q_OBJECT

public:
    arzi(QWidget *parent = nullptr);
    ~arzi();


private slots:
        void gotopage();
        void back();

        void addfiles();
        void choosefolder();
        void start_arch();
        void compress(QString ZipFile);

        void findarch();
        void choosedir();
        void start_unzip();
        void decompress(QString ZipFile);

        void choosearch();
        void openarc();
        void open(QString ZipFile);

private:
    Ui::arzi *ui;
};
#endif // ARZI_H
