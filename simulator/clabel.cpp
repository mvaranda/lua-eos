#include "clabel.h"
#include <QMouseEvent>

ClickableLabel::ClickableLabel(QWidget* parent, Qt::WindowFlags f)
    : QLabel(parent) {
    
}

ClickableLabel::~ClickableLabel() {}

void ClickableLabel::mousePressEvent(QMouseEvent* event) {
    //int x =  event->x();
    printf("press x = %d, y = %d\n",event->pos().rx(), event->pos().ry());
    emit clicked();
}

void ClickableLabel::mouseReleaseEvent(QMouseEvent* event) {
    printf("release x = %d, y = %d\n", event->x(), event->y());
    emit clicked();
}

