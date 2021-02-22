#ifndef CLICKABLELABEL_H
#define CLICKABLELABEL_H

#include <QLabel>
#include <QWidget>
#include <Qt>

class ClickableLabel : public QLabel { 
    Q_OBJECT 

public:
    explicit ClickableLabel(QWidget* parent = Q_NULLPTR, Qt::WindowFlags f = Qt::WindowFlags());
    ~ClickableLabel();

signals:
    void clicked();
    void mousePressed(int x, int y);
    void mouseReleased(int x, int y);

protected:
    void mousePressEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);

};

#endif // CLICKABLELABEL_H

