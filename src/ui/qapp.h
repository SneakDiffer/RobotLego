#ifndef QAPP_H
#define QAPP_H

#include <QMainWindow>

namespace Ui {
class QApp;
}

class QApp : public QMainWindow
{
    Q_OBJECT

public:
    explicit QApp(QWidget *parent = 0);
    ~QApp();

private:
    Ui::QApp *ui;
};

#endif // QAPP_H
