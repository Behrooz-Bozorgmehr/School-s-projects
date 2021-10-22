#include "man.h"

Man::Man(int rad, QColor col)
{
    //initialize attributs
    radius = rad;
    color = col;
    x = 0;
    y = 0;
    id = 0;
    defaultCenter = QPoint(400,400);
    cPoint = QPoint(400,400);
    position = false;
    strID="";
}
Man::~Man()
{

}
int Man::getR()
{
    return radius;
}
int Man::getX()
{
    return x;
}
int Man::getY()
{
    return y;
}
QPoint Man::getCenter()
{
    return cPoint;
}
void Man::setCenter(int x, int y)
{
    this->x = x;
    this->y = y;
    cPoint = QPoint(x,y);
}
void Man::setCenter(QPoint p)
{
    cPoint = p;
    this->x = cPoint.x();
    this->y = cPoint.y();
}
void Man::draw(QPainter *ptr)
{  
   ptr->setPen(QPen(color,1));
   ptr->setBrush(color);
   ptr->drawEllipse(cPoint,radius,radius);
}
// position of the man in a table of men
void Man::setID(int x)
{
    id = x;
}

int Man::getID()
{
    return id;
}
//to check if the score achieved (three men on the same line)
//is result of a new move or an old move, a false shows that score is already counted
bool Man::changePosition()
{
    return position;
}
void Man::setPosition(bool x)
{
    position = x;
}
// gives the code of each point to the man on each move
void Man::setStrID(QString pt)
{
    strID = pt;
}
QString Man::getStrID()
{
    return strID;
}


QColor Man::getColor()
{
    return color;

}
