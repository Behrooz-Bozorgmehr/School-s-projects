#ifndef MAN_H
#define MAN_H
#include "window.h"
#include <QColor>
#include <QWidget>
#include <QPoint>
#include <QPainter>

class Window;
class Man :public QWidget
{
public:
    Man(int rad, QColor col);
    ~Man();
    void draw(QPoint centre);
    int getR();
    int getX();
    int getY();
    QColor getColor();
    QPoint getCenter();
    void setCenter(int x, int y);
    void setCenter(QPoint p);
    void draw(QPainter *ptr);
    void setID(int x);
    int getID();
    bool changePosition();
    void setPosition(bool x);
    void setStrID(QString pt);
    QString getStrID();
    QPoint defaultCenter;


private:
    int radius;
    int x,y;
    int id;
    QColor color;
    QPoint cPoint;
//    Window *win;
    bool position;
    QString strID;
};

#endif // MAN_H
