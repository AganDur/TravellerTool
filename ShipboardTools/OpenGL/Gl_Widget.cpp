#include "Gl_Widget.h"

#include <QTimer>
#include <QPainter>
#include <QPaintEvent>

GL_Widget::GL_Widget(QWidget *parent) : QOpenGLWidget{parent} {
    elapsed_time = 0;
    setFixedSize(200, 200); //TODO: TEMPORARY
    setAutoFillBackground(false);
}

void GL_Widget::animate(){
    elapsed_time = (elapsed_time + qobject_cast<QTimer*>(sender())->interval()) % 1000;
    update();
}

void GL_Widget::paintEvent(QPaintEvent *event){
    QPainter painter;
    painter.begin(this);
    painter.setRenderHint(QPainter::Antialiasing);

    // Call Helper Paint
    // PAINT DIRECTLY INSTEAD
    painter.fillRect(event->rect(), QBrush(QColor(64,32,64)));
    painter.translate(100,100);
    painter.save();

    QLinearGradient gradient(QPointF(50,-20), QPointF(80,20));
    gradient.setColorAt(0.0, Qt::white);
    gradient.setColorAt(1.0, QColor(0xa6, 0xce, 0x39));

    painter.setBrush(QBrush(gradient));

    QPen circleP = QPen(Qt::black);
    circleP.setWidth(1);
    QFont text;
    text.setPixelSize(50);

    painter.setPen(circleP);
    painter.rotate(elapsed_time * 0.030);

    qreal r = elapsed_time / 1000.0;
    for(int i=0; i<30; ++i){
        painter.rotate(30);
        qreal factor = (i+r) / 30;
        qreal rad = 0 + 120 * factor;
        qreal circleRad = 1 + factor * 20;
        painter.drawEllipse(QRectF(rad, -circleRad, circleRad*2, circleRad*2));
    }
    painter.restore();
    painter.setPen(QPen(Qt::black));
    painter.setFont(text);
    painter.drawText(QRect(-50, -50, 100, 100), Qt::AlignCenter, QStringLiteral("Qt"));

    painter.end();
}
