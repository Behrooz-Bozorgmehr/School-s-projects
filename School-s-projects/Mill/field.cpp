#include "field.h"
#include "window.h"



Field::Field(int x, int y, int width,int piece,Window* win):QWidget(win)
{   //initialize attributs
    // to keep have equal divisions
    delta = width/6;

    //external lines
    extWidth = delta *6;
    extHeigth = extWidth;
    x1 = x;
    y1 = y;
    x7 = x1 +extWidth;
    y7 = y1 +extHeigth;
    //middle lines
    x2 = x1 + delta;
    y2 = y1 + delta;
    midWidth = extWidth - (2*delta);
    midHeigth = extHeigth - (2*delta);
    x6 = x2 + midWidth;
    y6 = y2 + midHeigth;
    //internal lines
    x3= x1+2*delta;
    y3 = y1+2*delta;
    intWidth = extWidth-(4*delta);
    intHeigth = extHeigth-(4*delta);
    x5 = x3 + intWidth;
    y5 = y3 + intHeigth;
    //bisect lines
    //for vetical bisect it is the x-coordinate that change
    //for horizontal it is the y-coordinate that change
    x4 = (x7+x1)/2;
    y4 = (y1+y7)/2;

    center =QPoint(extWidth/2,extHeigth/2);
    this->pcsTotal = piece;
    this->win = win;

    // distance between code-line and the board
    xEdge = 40;
    yEdge = 10;

    setup();
}

void Field::setup()
{
    // extern lines & points
    lH1 = QLine(x1,y1,x7,y1);
    lH7 = QLine(x1,y7,x7,y7);
    lV1 = QLine(x1,y1,x1,y7);
    lV7 = QLine(x7,y1,x7,y7);
    a1 = QPoint(x1,y1);
    a7 = QPoint(x7,y1);
    g1 = QPoint(x1,y7);
    g7 = QPoint(x7,y7);

    //middle lines & points
    lH2 = QLine(x2,y2,x6,y2);
    lH6 = QLine(x2,y6,x6,y6);
    lV2 = QLine(x2,y2,x2,y6);
    lV6 = QLine(x6,y2,x6,y6);
    b2 = QPoint(x2,y2);
    b6 = QPoint(x6,y2);
    f2 = QPoint(x2,y6);
    f6 = QPoint(x6,y6);

    //internal lines & points
    lH3 = QLine(x3,y3,x5,y3);
    lH5 = QLine(x3,y5,x5,y5);
    lV3 = QLine(x3,y3,x3,y5);
    lV5 = QLine(x5,y3,x5,y5);
    c3 = QPoint(x3,y3);
    c5 = QPoint(x5,y3);
    e3 = QPoint(x3,y5);
    e5 = QPoint(x5,y5);

    //six small lines, for 3 men's mill all six are used, for others only 2 are used
    lH4L = QLine(x1,y4,x3,y4);
    lH4R = QLine(x5,y4,x7,y4);
    lH4M = QLine(x3,y4,x5,y4);
    lV4U = QLine(x4,y1,x4,y3);
    lV4D = QLine(x4,y5,x4,y7);
    lV4M = QLine(x4,y3,x4,y7);
    d1 = QPoint(x1,y4);
    d2 = QPoint(x2,y4);
    d3 = QPoint(x3,y4);
    d4= QPoint(x4,y4);      // only in 3 mens
    d5 = QPoint(x5,y4);
    d6 = QPoint(x6,y4);
    d7 = QPoint(x7,y4);
    a4 = QPoint(x4,y1);
    b4 = QPoint((x2+x6)/2,y2);
    c4 = QPoint((x3+x5)/2,y3);
    g4 = QPoint(x4,y7);
    f4 = QPoint((x2+x6)/2,y6);
    e4 = QPoint((x3+x5)/2,y5);

    // diagonal lines for 12 men's mill
    lD1 = QLine(x1,y1,x3,y3);
    lD2 = QLine(x7,y1,x5,y3);
    lD3 = QLine(x1,y7,x3,y5);
    lD4 = QLine(x7,y7,x5,y5);

    // Coding point of the gameboard -
    lblH1 = new QLabel("A",win);
    lblH1->setVisible(false);
    lblH1->setGeometry(lH1.x1()-xEdge,lH1.y1()-yEdge,20,20);
    lblH2 = new QLabel("B",win);
    lblH2->setVisible(false);
    lblH2->setGeometry(lH1.x1()-xEdge,lH2.y1()-yEdge,20,20);
    lblH3 = new QLabel("C",win);
    lblH3->setVisible(false);
    lblH3->setGeometry(lH1.x1()-xEdge,lH3.y1()-yEdge,20,20);
    lblH4 = new QLabel("D",win);
    lblH4->setVisible(false);
    lblH4->setGeometry(lH1.x1()-xEdge,lH4L.y1()-yEdge,20,20);
    lblH5 = new QLabel("E",win);
    lblH5->setVisible(false);
    lblH5->setGeometry(lH1.x1()-xEdge,lH5.y1()-yEdge,20,20);
    lblH6 = new QLabel("F",win);
    lblH6->setVisible(false);
    lblH6->setGeometry(lH1.x1()-xEdge,lH6.y1()-yEdge,20,20);
    lblH7 = new QLabel("G",win);
    lblH7->setVisible(false);
    lblH7->setGeometry(lH1.x1()-xEdge,lH7.y1()-yEdge,20,20);

    lblV1 = new QLabel("1",win);
    lblV1->setVisible(false);
    lblV1->setGeometry(lV1.x1(),lV1.y2()+xEdge,20,20);
    lblV2 = new QLabel("2",win);
    lblV2->setVisible(false);
    lblV2->setGeometry(lV2.x1(),lV1.y2()+xEdge,20,20);
    lblV3 = new QLabel("3",win);
    lblV3->setVisible(false);
    lblV3->setGeometry(lV3.x1(),lV1.y2()+xEdge,20,20);
    lblV4 = new QLabel("4",win);
    lblV4->setVisible(false);
    lblV4->setGeometry(lV4D.x1(),lV1.y2()+xEdge,20,20);
    lblV5 = new QLabel("5",win);
    lblV5->setVisible(false);
    lblV5->setGeometry(lV5.x1(),lV1.y2()+xEdge,20,20);
    lblV6 = new QLabel("6",win);
    lblV6->setVisible(false);
    lblV6->setGeometry(lV6.x1(),lV1.y2()+xEdge,20,20);
    lblV7 = new QLabel("7",win);
    lblV7->setVisible(false);
    lblV7->setGeometry(lV7.x1(),lV1.y2()+xEdge,20,20);

    // tables of points next to a point : n = next to , a1 = point a1
    na1.insert(d1); na1.insert(a4);
    nd1.insert(a1); nd1.insert(g1); nd1.insert(d2);
    ng1.insert(d1); ng1.insert(g4);
    nb2.insert(d2); nb2.insert(b4);
    nd2.insert(d1); nd2.insert(b2); nd2.insert(f2); nd2.insert(d3);
    nf2.insert(d2); nf2.insert(f4);
    nc3.insert(d3); nc3.insert(c4);
    nd3.insert(d2); nd3.insert(c3); nd3.insert(e3);
    ne3.insert(d3); ne3.insert(e4);
    na4.insert(a1); na4.insert(b4); na4.insert(a7);
    nb4.insert(b2); nb4.insert(a4); nb4.insert(b6); nb4.insert(c4);
    nc4.insert(c3); nc4.insert(b4); nc4.insert(c5);
    ne4.insert(e3); ne4.insert(f4); ne4.insert(e5);
    nf4.insert(f2); nf4.insert(e4); nf4.insert(f6); nf4.insert(g4);
    ng4.insert(g1); ng4.insert(f4); ng4.insert(g7);
    nc5.insert(c4); nc5.insert(d5);
    nd5.insert(c5); nd5.insert(d6); nd5.insert(e5);
    ne5.insert(e4); ne5.insert(d5);
    nb6.insert(b4); nb6.insert(d6);
    nd6.insert(d5); nd6.insert(b6); nd6.insert(d7); nd6.insert(f6);
    nf6.insert(f4); nf6.insert(d6);
    na7.insert(a4); na7.insert(d7);
    nd7.insert(d6); nd7.insert(a7); nd7.insert(g7);
    ng7.insert(g4); ng7.insert(d7);

}

// gives coordinate of the point for a given code.
QPoint Field::getPoint(QString pt)
{
    if(pt.toLower()=="a1")
        return a1;
    else if(pt.toLower()=="a4")
        return a4;
    else if(pt.toLower()=="a7")
        return a7;
    else if(pt.toLower()=="b2")
        return b2;
    else if(pt.toLower()=="b4")
        return b4;
    else if(pt.toLower()=="b6")
        return b6;
    else if(pt.toLower()=="c3")
        return c3;
    else if(pt.toLower()=="c4")
        return c4;
   else if(pt.toLower()=="c5")
        return c5;
    else if(pt.toLower()=="d1")
        return d1;
    else if(pt.toLower()=="d2")
        return d2;
    else if(pt.toLower()=="d3")
        return d3;
    else if(pt.toLower()=="d5")
        return d5;
    else if(pt.toLower()=="d6")
        return d6;
    else if(pt.toLower()=="d7")
        return d7;
    else if(pt.toLower()=="e3")
        return e3;
    else if(pt.toLower()=="e4")
        return e4;
    else if(pt.toLower()=="e5")
        return e5;
    else if(pt.toLower()=="f2")
        return f2;
    else if(pt.toLower()=="f4")
        return f4;
    else if(pt.toLower()=="f6")
        return f6;
   else if(pt.toLower()=="g1")
        return g1;
    else if(pt.toLower()=="g4")
        return g4;
    else if(pt.toLower()=="g7")
        return g7;
    else
    {   //in case the given code is not part of the board,
        //return center point of the board, the logic then knows that the
        // point is not in the board and it will take the right decision
        QPoint p = QPoint(400,400);
        return p;
    }
}

int Field::getPcs()
{
    return pcsTotal;
}

void Field::setPiece(int pcs)
{
    pcsTotal = pcs;
}
//Draw the board
void Field::draw(QPainter *ptr)
{

       ptr->setPen(QPen(Qt::black, 2));
     // QRadioButton: "if" defines type of the board & No. of men
    if ( pcsTotal ==3)
    {   //draw lines of the board
        ptr->drawLine(lH1);
        ptr->drawLine(lH4R); //right-side horizontal bisect line
        ptr->drawLine(lH4M); //connection of two horizontal bisect lines
        ptr->drawLine(lH4L); //left-side horizontal bisect line
        ptr->drawLine(lH7);

        ptr->drawLine(lV1);
        ptr->drawLine(lV4U);//right-side vertical bisect line
        ptr->drawLine(lV4M);//connection of two vertical bisect lines
        ptr->drawLine(lV4D);//left-side vertical bisect line
        ptr->drawLine(lV7);

        // draw small circls at corners and intersection points
        ptr->setPen(QPen(Qt::gray, 8));
        ptr->drawEllipse(a1,4,4);
        ptr->drawEllipse(a4,4,4);
        ptr->drawEllipse(a7,4,4);

        ptr->drawEllipse(d1,4,4);
        ptr->drawEllipse(d4,4,4);
        ptr->drawEllipse(d7,4,4);

        ptr->drawEllipse(g1,4,4);
        ptr->drawEllipse(g4,4,4);
        ptr->drawEllipse(g7,4,4);
    }
    if ( pcsTotal ==6)
    {   //draw lines of the board
        ptr->drawLine(lH1);
        ptr->drawLine(lH3);
        ptr->drawLine(lH4R); //right-side horizontal bisect line
        ptr->drawLine(lH4L); //left-side horizontal bisect line
        ptr->drawLine(lH5);
        ptr->drawLine(lH7);

        ptr->drawLine(lV1);
        ptr->drawLine(lV3);
        ptr->drawLine(lV4U);//upside vertical bisect line
        ptr->drawLine(lV4D);//downside vertical bisect line
        ptr->drawLine(lV5);
        ptr->drawLine(lV7);

        // draw small circls at corners and intersection points
        ptr->setPen(QPen(Qt::gray, 8));
        ptr->drawEllipse(a1,4,4);
        ptr->drawEllipse(a4,4,4);
        ptr->drawEllipse(a7,4,4);

        ptr->drawEllipse(c3,4,4);
        ptr->drawEllipse(c4,4,4);
        ptr->drawEllipse(c5,4,4);
        ptr->drawEllipse(d1,4,4);

        ptr->drawEllipse(d3,4,4);
        ptr->drawEllipse(d5,4,4);

        ptr->drawEllipse(d7,4,4);
        ptr->drawEllipse(e3,4,4);
        ptr->drawEllipse(e4,4,4);
        ptr->drawEllipse(e5,4,4);

        ptr->drawEllipse(g1,4,4);
        ptr->drawEllipse(g4,4,4);
        ptr->drawEllipse(g7,4,4);


    }
    // for 9 and 12 men board the difference is the diagonal lines of the board
    if(pcsTotal ==12)
    {   //draw diagonal lines of the board
        ptr->drawLine(lD1);
        ptr->drawLine(lD2);
        ptr->drawLine(lD3);
        ptr->drawLine(lD4);
    }
    if(pcsTotal >6)
    {   ptr->drawLine(lH1);
        ptr->drawLine(lH2);
        ptr->drawLine(lH3);
        ptr->drawLine(lH4R); //right-side horizontal bisect line
        ptr->drawLine(lH4L); //left-side horizontal bisect line
        ptr->drawLine(lH5);
        ptr->drawLine(lH6);
        ptr->drawLine(lH7);

        ptr->drawLine(lV1);
        ptr->drawLine(lV2);
        ptr->drawLine(lV3);
        ptr->drawLine(lV4U);//upside vertical bisect line
        ptr->drawLine(lV4D);//downside vertical bisect line
        ptr->drawLine(lV5);
        ptr->drawLine(lV6);
        ptr->drawLine(lV7);

        // draw small circls at corners and intersection points
        ptr->setPen(QPen(Qt::black, 8));
        ptr->drawEllipse(a1,4,4);
        ptr->drawEllipse(a4,4,4);
        ptr->drawEllipse(a7,4,4);
        ptr->drawEllipse(b2,4,4);
        ptr->drawEllipse(b4,4,4);
        ptr->drawEllipse(b6,4,4);
        ptr->drawEllipse(c3,4,4);
        ptr->drawEllipse(c4,4,4);
        ptr->drawEllipse(c5,4,4);
        ptr->drawEllipse(d1,4,4);
        ptr->drawEllipse(d2,4,4);
        ptr->drawEllipse(d3,4,4);
        ptr->drawEllipse(d5,4,4);
        ptr->drawEllipse(d6,4,4);
        ptr->drawEllipse(d7,4,4);
        ptr->drawEllipse(e3,4,4);
        ptr->drawEllipse(e4,4,4);
        ptr->drawEllipse(e5,4,4);
        ptr->drawEllipse(f2,4,4);
        ptr->drawEllipse(f4,4,4);
        ptr->drawEllipse(f6,4,4);
        ptr->drawEllipse(g1,4,4);
        ptr->drawEllipse(g4,4,4);
        ptr->drawEllipse(g7,4,4);
    }

    //show the write code
    if(pcsTotal>6)
       {   lblH1->setText("A");
           lblH1->setVisible(true);
           lblH2->setText("B");
           lblH2->setVisible(true);
           lblH3->setText("C");
           lblH3->setVisible(true);
           lblH4->setText("D");
           lblH4->setVisible(true);
           lblH5->setText("E");
           lblH5->setVisible(true);
           lblH6->setText("F");
           lblH6->setVisible(true);
           lblH7->setText("G");
           lblH7->setVisible(true);

           lblV1->setText("1");
           lblV1->setVisible(true);
           lblV2->setText("2");
           lblV2->setVisible(true);
           lblV3->setText("3");
           lblV3->setVisible(true);
           lblV4->setText("4");
           lblV4->setVisible(true);
           lblV5->setText("5");
           lblV5->setVisible(true);
           lblV6->setText("6");
           lblV6->setVisible(true);
           lblV7->setText("7");
           lblV7->setVisible(true);
       }
       if(pcsTotal==6)
       {   lblH1->setVisible(true);
           lblH2->setVisible(false);
           lblH3->setText("B");
           lblH3->setVisible(true);
           lblH4->setText("C");
           lblH4->setVisible(true);
           lblH5->setText("D");
           lblH5->setVisible(true);
           lblH6->setVisible(false);
           lblH7->setText("E");
           lblH7->setVisible(true);

           lblV1->setVisible(true);
           lblV2->setVisible(false);
           lblV3->setText("2");
           lblV3->setVisible(true);
           lblV4->setText("3");
           lblV4->setVisible(true);
           lblV5->setText("4");
           lblV5->setVisible(true);
           lblV6->setVisible(false);
           lblV7->setText("5");
           lblV7->setVisible(true);
       }
       if(pcsTotal==3)
       {   lblH1->setVisible(true);
           lblH2->setVisible(false);
           lblH3->setVisible(false);
           lblH4->setText("B");
           lblH4->setVisible(true);
           lblH5->setVisible(false);
           lblH6->setVisible(false);
           lblH7->setText("C");
           lblH7->setVisible(true);

           lblV1->setVisible(true);
           lblV2->setVisible(false);
           lblV3->setVisible(false);
           lblV4->setText("2");
           lblV4->setVisible(true);
           lblV5->setVisible(false);
           lblV6->setVisible(false);
           lblV7->setText("3");
           lblV7->setVisible(true);
       }
}

bool Field::isNeighbor(const QPoint p1, const QPoint p2)
{
    QPoint pt;

    if(p1 == a1)
         return na1.contains(p2)? true:false;
    if(p1 == d1)
         return nd1.contains(p2)? true:false;
    if(p1 == g1)
         return ng1.contains(p2)? true:false;
    if(p1 == b2)
         return nb2.contains(p2)? true:false;
    if(p1 == d2)
         return nd2.contains(p2)? true:false;
    if(p1 == f2)
         return nf2.contains(p2)? true:false;
    if(p1 == c3)
         return nc3.contains(p2)? true:false;
    if(p1 == d3)
         return nd3.contains(p2)? true:false;
    if(p1 == e3)
         return ne3.contains(p2)? true:false;
    if(p1 == a4)
         return na4.contains(p2)? true:false;
    if(p1 == b4)
         return nb4.contains(p2)? true:false;
    if(p1 == c4)
         return nc4.contains(p2)? true:false;
    if(p1 == e4)
         return ne4.contains(p2)? true:false;
    if(p1 == f4)
         return nf4.contains(p2)? true:false;
    if(p1 == g4)
         return ng4.contains(p2)? true:false;
    if(p1 == c5)
         return nc5.contains(p2)? true:false;
    if(p1 == d5)
         return nd5.contains(p2)? true:false;
    if(p1 == e5)
         return ne5.contains(p2)? true:false;
    if(p1 == b6)
         return nb6.contains(p2)? true:false;
    if(p1 == d6)
         return nd6.contains(p2)? true:false;
    if(p1 == f6)
         return nf6.contains(p2)? true:false;
    if(p1 == a7)
         return na7.contains(p2)? true:false;
    if(p1 == d7)
         return nd7.contains(p2)? true:false;
    if(p1 == g7)
         return ng7.contains(p2)? true:false;


    else
    {
        qDebug()<<"Point 1 is not part of the board";
        return false;
    }

}

inline uint qHash (const QPoint &key)
{
    return qHash (QPair<int,int>(key.x(),key.y()));
}


