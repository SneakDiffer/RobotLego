#include <math.h>
#include <iostream>

#include <QDrag>
#include <QBitmap>
#include <QMimeData>
#include <QApplication>
#include <QGraphicsItem>
#include <QGraphicsView>
#include <QGraphicsSceneMouseEvent>

#include "ui/qapp.h"

class ColorItem : public QGraphicsItem
{
public:
    ColorItem();

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

private:
    QColor color;
};


ColorItem::ColorItem()
    : color(qrand() % 256, qrand() % 256, qrand() % 256)
{
    setToolTip(QString("QColor(%1, %2, %3)\n%4")
              .arg(color.red()).arg(color.green()).arg(color.blue())
              .arg("Click and drag this color onto the robot!"));
    setCursor(Qt::OpenHandCursor);
    setAcceptedMouseButtons(Qt::LeftButton);
}

QRectF ColorItem::boundingRect() const
{
    return QRectF(-15.5, -15.5, 34, 34);
}

void ColorItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    painter->setPen(Qt::NoPen);
    painter->setBrush(Qt::darkGray);
    painter->drawEllipse(-12, -12, 30, 30);
    painter->setPen(QPen(Qt::black, 1));
    painter->setBrush(QBrush(color));
    painter->drawEllipse(-15, -15, 30, 30);
}

void ColorItem::mousePressEvent(QGraphicsSceneMouseEvent *)
{
    setCursor(Qt::ClosedHandCursor);
}

void ColorItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *)
{
    setCursor(Qt::OpenHandCursor);
}

void ColorItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if (QLineF(event->screenPos(), event->buttonDownScreenPos(Qt::LeftButton))
        .length() < QApplication::startDragDistance()) {
        return;
    }

    QDrag *drag = new QDrag(event->widget());
    QMimeData *mime = new QMimeData;
    drag->setMimeData(mime);
    static int n = 0;

    if (n++ > 2 && (qrand() % 3) == 0) {
        QImage image(":/images/head.png");
        mime->setImageData(image);

        drag->setPixmap(QPixmap::fromImage(image).scaled(30, 40));
        drag->setHotSpot(QPoint(15, 30));
    } else {
        mime->setColorData(color);
        mime->setText(QString("#%1%2%3")
                      .arg(color.red(), 2, 16, QLatin1Char('0'))
                      .arg(color.green(), 2, 16, QLatin1Char('0'))
                      .arg(color.blue(), 2, 16, QLatin1Char('0')));

        QPixmap pixmap(34, 34);
        pixmap.fill(Qt::white);

        QPainter painter(&pixmap);
        painter.translate(15, 15);
        painter.setRenderHint(QPainter::Antialiasing);
        paint(&painter, 0, 0);
        painter.end();

        pixmap.setMask(pixmap.createHeuristicMask());

        drag->setPixmap(pixmap);
        drag->setHotSpot(QPoint(15, 20));
    }
}

/////////////////////////////////////////////////////////////////////////////

int main(int argc, char *argv[])
{
    // instanciate application window
    QApplication a(argc, argv);
    QApp w;
    w.show();


    // create a dummy map

    // create the QGraphicsScene accordingly
    QGraphicsScene wallscene;

    for (int i = 0; i < 10; ++i) {
        ColorItem *item = new ColorItem;
        item->setPos(::sin((i * 6.28) / 10.0) * 150, ::cos((i * 6.28) / 10.0) * 150);

         wallscene.addItem(item);
    }

    // find the QGraphicsView
    QGraphicsView* walldrawer = nullptr;
    walldrawer = w.findChild<QGraphicsView*>("graphicsView");

    if (walldrawer == nullptr)
        std::cout << "blast" << std::endl;

    walldrawer->setScene(&wallscene);
    walldrawer->setRenderHint(QPainter::Antialiasing);
    walldrawer->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
    walldrawer->setBackgroundBrush(QColor(230, 200, 167));
    walldrawer->setWindowTitle("Drag and Drop Robot");

    return a.exec();
}
