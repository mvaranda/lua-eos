#include "clabel.h"
#include <QMouseEvent>

ClickableLabel::ClickableLabel(QWidget* parent, Qt::WindowFlags f)
    : QLabel(parent) {
    
}

ClickableLabel::~ClickableLabel() {}

void ClickableLabel::mousePressEvent(QMouseEvent* event) {
    mousePressed(event->x(), event->y());
}

void ClickableLabel::mouseReleaseEvent(QMouseEvent* event) {
    mouseReleased(event->x(), event->y());
}

