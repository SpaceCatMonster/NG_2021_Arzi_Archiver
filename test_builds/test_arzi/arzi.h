#ifndef ARZI_H
#define ARZI_H

#include <QMainWindow>

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
private:
    Ui::arzi *ui;
};
#endif // ARZI_H
