#ifndef FIELD_H
#define FIELD_H
//#include "window.h"
#include <QWidget>
#include <QLabel>
#include <QPoint>
#include <QSet>


class Window;
class Field : public QWidget, public QLine, public QPoint
{
    Q_OBJECT
public:
    Field(int x, int y, int width,int pcs,Window* win);
    void setup();
   // QLine getLine(QString pt);
    QPoint getPoint(QString pt);
    int getPcs();
    void setPiece(int pcs);
    void draw(QPainter *p);
    bool isNeighbor(QPoint p1, QPoint p2);



private:
    int x1,y1,x2,y2,x3,y3,x4,y4,x5,y5,x6,y6,x7,y7; // coordinates of 1st point of lines
    int delta ;                                    // distance between lines
    int extWidth;
    int midWidth;
    int intWidth;
    int extHeigth;
    int midHeigth;
    int intHeigth;
    // lines, "H" = horizonal, "V"= vertical, and "D"= diagonal,
    //"1"=highest/most left line, "7"=lowest/most right line
    QLine lH1,lH2,lH3,lH4R,lH4M,lH4L,lH5,lH6,lH7,lV1,lV2,lV3,lV4U,lV4M,lV4D,lV5,lV6,lV7,lD1,lD2,lD3,lD4;
    QLabel *lblH1,*lblH2,*lblH3,*lblH4,*lblH5,*lblH6,*lblH7,*lblV1,*lblV2,*lblV3,*lblV4,*lblV5,*lblV6,*lblV7;
    //end points and middle points of lines,
    //"a1"= highest & most left corner, "g7"= lowest & most right corner
    //"*4" and "d*" show the mid-points of horizontal and vertical lines respectively
    QPoint a1,a4,a7,b2,b4,b6,c3,c4,c5,d1,d2,d3,d4,d5,d6,d7,e3,e4,e5,f2,f4,f6,g1,g4,g7,center;
    Window* win;
    int pcsTotal;

    // distance of codes from exterieur of the board
    int xEdge = 40;
    int yEdge = 10;
    // points neighbors, exemple: "na1" is the point and ... are inserted as its neighbors
    QSet<QPoint> na1 ;
    QSet<QPoint> nd1 ;
    QSet<QPoint> ng1 ;
    QSet<QPoint> nb2 ;
    QSet<QPoint> nd2 ;
    QSet<QPoint> nf2 ;
    QSet<QPoint> nc3 ;
    QSet<QPoint> nd3 ;
    QSet<QPoint> ne3 ;
    QSet<QPoint> na4 ;
    QSet<QPoint> nb4 ;
    QSet<QPoint> nc4 ;
    QSet<QPoint> ne4 ;
    QSet<QPoint> nf4 ;
    QSet<QPoint> ng4 ;
    QSet<QPoint> nc5 ;
    QSet<QPoint> nd5 ;
    QSet<QPoint> ne5 ;
    QSet<QPoint> nb6 ;
    QSet<QPoint> nd6 ;
    QSet<QPoint> nf6 ;
    QSet<QPoint> na7 ;
    QSet<QPoint> nd7 ;
    QSet<QPoint> ng7 ;



};

#endif // FIELD_H
