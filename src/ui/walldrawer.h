#ifndef WALLDRAWER_H
#define WALLDRAWER_H

#include <QFrame>

namespace Ui {
class Walldrawer;
}

class Walldrawer : public QFrame
{
    Q_OBJECT

public:
    explicit Walldrawer(QWidget *parent = 0);
    ~Walldrawer();

private:
    Ui::Walldrawer *ui;
};

#endif // WALLDRAWER_H
