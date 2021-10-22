#include "controller.h"
#include <QLineEdit>

Controller::Controller()
{   //initialize attributs
    placeCounter =0;
    deleteCounter1 =0;
    deleteCounter2 =0;
    pcsTotal = MAXPCS;
    pcsPlaced = 0;
    player =1;
    gain = false;
    man1Counter =-1;
    man2Counter =-1;
    input = nullptr;
    win = nullptr;
    fld = nullptr;
    pointToDelete ="";
    man1 = (Man**)new Man *[pcsTotal];
    man2 = (Man**)new Man *[pcsTotal];
    for (int i=0;i < pcsTotal; i++)
    {   QColor col1(Qt::red);
        QColor col2(Qt::blue);
        man1[i] = new Man(15,col1);
        man2[i] = new Man(15,col2 );
    }

}

Controller::~Controller()
{

}

void Controller::initRelations(Window *win, InputPanel *input)
{
    this->win = win;
    this->input = input;

}

void Controller::setField(Field *f)
{
  this->fld = f;
}

void Controller::setMan(Man *m1[],Man *m2[])
{
    for (int i=0; i<pcsTotal;i++)
    {   this->man1[i] = m1[i];
        this->man2[i] = m2[i];
    }
}

void Controller::setPiece(int pcs)
{
    pcsTotal = pcs;
}
// determine the position of each man at the beginning next to the board
void Controller::place()
{
    if(pcsTotal ==3)
    {
        for (int i=0; i<pcsTotal; i++)
        {    man1[i]->setCenter(700,300+(i+1)*40);
             man2[i]->setCenter(100,300+(i+1)*40);
        }
    }
    if(pcsTotal==6)
    {
        for (int i=0; i<pcsTotal; i++)
        {  man1[i]->setCenter(700,250+(i+1)*40);
           man2[i]->setCenter(100,250+(i+1)*40);
        }
    }
    if(pcsTotal==9)
    {   for (int i=0; i<pcsTotal; i++)
            {   man1[i]->setCenter(700,200+(i+1)*40);
                man2[i]->setCenter(100,200+(i+1)*40);
            }
    }
    if(pcsTotal==12)
    {   for (int i=0; i<pcsTotal; i++)
        {   man1[i]->setCenter(700,150+(i+1)*40);
            man2[i]->setCenter(100,150+(i+1)*40);
        }
    }
    // reinitialize the attributs , to reset in case of replay
    placeCounter =0;
    deleteCounter1 =0;
    deleteCounter2 =0;
    pcsPlaced = 0;
    player =1;
    gain = false;
    man1Counter =-1;
    man2Counter =-1;
    win->setMen(man1,man2);
    win->renew();
}
void Controller::onCommandEntered()
{
    QString p1,p2;
    QLineEdit *textBox;
    textBox = input->getText();
    textBox->selectAll();
    if(placeCounter%2==0)
    {   win->setPlayer("2"); // inform user whose turn is to play
        player = 1;       //  used only in this class to place the "MAN"

        if ( man1Counter<pcsTotal-1-deleteCounter1)
            man1Counter++;
    }
    else
    {   win->setPlayer("1");
        player =2;
        if ( man2Counter<pcsTotal-1-deleteCounter2)
            man2Counter++;
    }

    //in placing phase
    if(placeCounter<(pcsTotal*2-deleteCounter1-deleteCounter2))
        {   p1="";
            p2= textBox->text().left(2).toLower();
            win->setPhase("Placing");
            move(p1,p2);
        }
    //in jumping phase
    else if(man1Counter<3 ||man2Counter <3)
    {   p1 = textBox->text().left(2).toLower();
        p2 = textBox->text().right(2).toLower();
        win->setPhase("Jumping");
        move(p1,p2);
    }
    // changing position: in neighborhood
    else
        {
            p1 = textBox->text().left(2).toLower();
            p2 = textBox->text().right(2).toLower();
            win->setPhase("Moving");
            remove(p1,p2);
        }
    //clear the textbox after Enter
    input->setText();
}
void Controller::start()
{
    input->setEnabled(true);
}

void Controller::move(QString p1, QString p2)
{  // get the coordinate of the point from his code
    QPoint point2 = fld->getPoint(p2);
    bool place = true;
    bool count = true;
    // for first phase of the game (placing)
    if(p1=="")
    {   switch(player)
        {
            case 1:
            // in case the point chosen is alread picked up by another "MAN", just a message is given
                for( int i=0;i<=(man1Counter);i++)
                {   if((point2 == man1[i]->getCenter())||(point2 == man2[i]->getCenter()))
                    {
                        qDebug()<<"1 Wrong point, already occupied!"    ;
                        place = false;
                        count = false;
                        break;
                    }
                }
                // in case a entered point is wrong, the "MAN" is placed
                // in center of the board and gives a new chance to place it
                if( point2==man1[man1Counter]->defaultCenter)
                {   qDebug()<<"2 Wrong point, not part of the board"     ;
                    place = true;
                    count = false;
                }

                if (place)
                {   man1[man1Counter]->setCenter(point2);
                    man1[man1Counter]->setID(man1Counter);
                    man1[man1Counter]->setPosition(true);
                    man1[man1Counter]->setStrID(p2);
                }
                if (!count) // to give a new chance after error in writing the code
                {   man1Counter--;
                    placeCounter--;
                }
            break;
            case 2:

                for( int i=0;i<=man1Counter;i++)
                {   if((point2 == man1[i]->getCenter())||(point2 == man2[i]->getCenter()))
                    {   // in case the point chosen is alread picked up by another "MAN", just a message is given
                        qDebug()<<"3 Wrong point, already occupied!"    ;
                        place = false;
                        count = false;
                        break;
                    }
                }
                // in case a point is entered mistakenly, the "MAN" is placed
                // in center of the board and given a new chance to place it
                if( point2==man2[man2Counter]->defaultCenter)
                {   qDebug()<<"4 Wrong point, not part of the board"     ;
                    place = true;
                    count = false;
                }
               if (place)
                {   man2[man2Counter]->setCenter(point2);
                    man2[man2Counter]->setID(man2Counter);
                    man2[man2Counter]->setPosition(true);
                    man2[man2Counter]->setStrID(p2);
                }
                if(!count)// to give a new chance after error in writing the code
                {   man2Counter--;
                    placeCounter--;
                }
           break;
         }
    }

    // for last phase of the game (jumping)
    else
    {   QPoint point1 = fld->getPoint(p1);
        point2 = fld->getPoint(p2);
        switch(player)
        {   case 1:
                for(int i=0;i<=man1Counter;i++)
                {
                    if (man1[i]->getCenter()==point1)
                    {   man1[i]->setCenter(point2);
                        man1[i]->setPosition(true);
                        man1[i]->setStrID(p2);
                    }
                }
            break;
            case 2:
                for(int i=0;i<=man1Counter;i++) //"man1Counter" as man2Counter is smaller than it
                {
                    if (man2[i]->getCenter()==point1)
                    {   man2[i]->setCenter(point2);
                        man2[i]->setPosition(true);
                        man2[i]->setStrID(p2);
                    }
                }
            break;
        }
    }
    placeCounter++;
    win->setMen(man1,man2);
    win->renew();

    //check if one party get a score
    if (score())
    {// firstly the party gained a score eleminate one "MAN" from the stock of the men.
     //later when all "MEN" are on the board the party gained can choose a "MAN" from the board
        QPoint pt ;
        switch (player)
        {   case 1:
            //before all men are on board
            if(man2[pcsTotal-1-deleteCounter2]->getX()==100)
            {
                 man2[pcsTotal-1-deleteCounter2]->setCenter(700,200+40*deleteCounter2);
                 deleteCounter2++;
            }
            //if all are on board
            else
            {   win->setMessage(true);
                onPointToDelete();
                pt = fld->getPoint(pointToDelete);
                for (int i=0;i<=man2Counter;i++)
                {   if(man2[i]->getCenter()==pt)
                        {  man2[i]->setCenter(700,200+40*deleteCounter2);
                           man2[i]->setStrID("");
                           man2[i]->setPosition(false);
                           deleteCounter2++;
                           man2Counter--;
                           break;
                        }
               }
            }
            break;
            case 2:
            if(man1[pcsTotal-1-deleteCounter1]->getX()==700)
            {   man1[pcsTotal-1-deleteCounter1]->setCenter(100,200+40*deleteCounter1);
                deleteCounter1++;
            }
            else
            {   win->setMessage(true);
                onPointToDelete();
                pt = fld->getPoint(pointToDelete);
                for (int i=0;i<=man1Counter;i++)
                {   if(man1[i]->getCenter()==pt)
                    {  man1[i]->setCenter(100,200+40*deleteCounter1);
                       man1[i]->setStrID("");
                       man1[i]->setPosition(false);
                       deleteCounter1++;
                       man1Counter--;
                       break;
                    }
                }
            }
            break;


        }
    }
    win->setMen(man1,man2);
    win->renew();
}

void Controller::remove(QString p1, QString p2)
{   // get the coordinates of points from the codes given
    QPoint point1 = fld->getPoint(p1);
    QPoint point2 = fld->getPoint(p2);
    bool place = true;
    bool count = true;
    int id;
    //check if the points are next to each other
    if (fld->isNeighbor(point1,point2))
    {   switch(player)
        {   case 1:
            //check if a code is wrong
            if(point1 == man1[0]->defaultCenter||point2 == man1[0]->defaultCenter)
            {   qDebug()<<"Wrong point/s";
                place = false;
                count = false;
                break;
            }
            // get the "MAN" placed in point1
            for(int i=0; i<=(man1Counter);i++)
            {   if(man1[i]->getCenter()==point1)
                {   id = man1[i]->getID();
                    break;
                }
                // when no MAN is placed at the point given
                if (i==man1Counter)
                {   qDebug()<<"Wrong point :"<<p1;
                    place = false;
                    count = false;
                }
            }
            // in case the point chosen is alread picked up by another "MAN", just a message is given
            for( int i=0;i<=man1Counter;i++)
            {   if((point2 == man1[i]->getCenter())||(point2 == man2[i]->getCenter()))
                {
                    qDebug()<<"5 Wrong point, already occupied!"    ;
                    place = false;
                    count = false;
                    break;
                }
            }
            //every check is ok change position of the MAN
            if (place)
            {   man1[id]->setCenter(point2);
                man1[id]->setPosition(true);
                man1[id]->setStrID(p2);
            }
            break;
            case 2:
            //check if a code is wrong
            if(point1 == man2[0]->defaultCenter||point2 == man2[0]->defaultCenter)
            {   qDebug()<<"Wrong point/s";
                place = false;
                count = false;
                break;
            }
            // get the "MAN" placed in point1
            for(int i=0; i<=(man2Counter);i++)
            {   if(man2[i]->getCenter()==point1)
                {   id = man2[i]->getID();
                    break;
                }
                // when no MAN is placed at the point given
                if (i==man2Counter)
                {   qDebug()<<"Wrong point :"<<p1;
                    place = false;
                    count = false;
                }
            }
            // in case the point chosen is alread picked up by another "MAN", just a message is given
            for( int i=0;i<=(man2Counter);i++)
            {   if((point2 == man1[i]->getCenter())||(point2 == man2[i]->getCenter()))
                {
                    qDebug()<<"6 Wrong point, already occupied!"    ;
                    place = false;
                    count = false;
                    break;
                }
            }
            if (place)
            {   man2[id]->setCenter(point2);
                man2[id]->setPosition(true);
                man2[id]->setStrID(p2);
            }
            break;
        }
        if (!count) // to give a new chance
        {   placeCounter--;
        }
        placeCounter++;

        win->setMen(man1,man2);
        win->renew();

        //check if one party get a score
        if (score())
        {   qDebug()<<"Choose a 'MAN' to omit from the game";
            win->setMessage(true);
            onPointToDelete();
            QPoint pt = fld->getPoint(pointToDelete);
            switch (player)
            {   case 1:
                for (int i=0;i<=man2Counter;i++)
                {   if(man2[i]->getCenter()==pt)
                    {  man2[i]->setCenter(700,200+40*deleteCounter2);
                       man2[i]->setStrID("");
                       man2[i]->setPosition(false);
                       deleteCounter2++;
                       man2Counter--;
                       break;
                    }
                }
                break;
                case 2:
                for (int i=0;i<=man1Counter;i++)
                {   if(man1[i]->getCenter()==pt)
                    {  man1[i]->setCenter(100,200+40*deleteCounter1);
                       man1[i]->setStrID("");
                       man1[i]->setPosition(false);
                       deleteCounter1++;
                       man1Counter--;
                       break;
                    }
                }
                break;
            }

        }
        win->setMen(man1,man2);
        win->renew();

    }
    else
    {
        qDebug()<<p1<<" and "<<p2<<" are not neighbor";
    }
}



bool Controller::score()
{   gain = false;
    switch (player)
    {   case 1:
        for (int i=0;i<man1Counter-1;i++)
            {   for (int j=1;j<man1Counter;j++)
                {   for (int k=2;k<man1Counter+1;k++)
                    {    if(i!=j && i!=k && j!=k)
                      // control for not count several times the same score
                        {   if(man1[i]->changePosition() || man1[j]->changePosition()|| man1[i]->changePosition())
                            {   //horizontally 3 pieces alined
                                if((man1[i]->getStrID().at(0)==man1[j]->getStrID().at(0)) && (man1[i]->getStrID().at(0)==man1[k]->getStrID().at(0)))
                                {    // control for the two small horizontal lines in the middle, "52" is the value for 4 in ascii table
                                     if(man1[i]->getStrID().at(0)=="d"&& man1[j]->getStrID().at(0)=="d" &&man1[k]->getStrID().at(0)=="d")
                                     {   if( (man1[i]->getStrID().at(1)<52 &&man1[j]->getStrID().at(1)<52 &&man1[k]->getStrID().at(1)<52))
                                             gain = true;
                                         if ((man1[i]->getStrID().at(1)>52 &&man1[j]->getStrID().at(1)>52 &&man1[k]->getStrID().at(1)>52))
                                             gain = true;
                                     }
                                     else
                                    {    gain =true;
                                    }
                                }
                        //vertically 3 pieces alined, 100 is ascii for d
                                if((man1[i]->getStrID().at(1)==man1[j]->getStrID().at(1)) && (man1[i]->getStrID().at(1)==man1[k]->getStrID().at(1)))
                                {    if(man1[i]->getStrID().at(1)=="4" && man1[j]->getStrID().at(1)== "4" &&man1[k]->getStrID().at(1)=="4")
                                     {   if((man1[i]->getStrID().at(0)<100 &&man1[j]->getStrID().at(0)<100 &&man1[k]->getStrID().at(0)<100))
                                            gain = true;
                                         if ((man1[i]->getStrID().at(0)>100 &&man1[j]->getStrID().at(0)>100 &&man1[k]->getStrID().at(0)>100))
                                            gain = true;
                                    }
                                    else
                                    {   gain =true;
                                    }
                                }
                            }
                            //to avoid a double counting of a score
                            if(gain)
                            {   man1[i]->setPosition(false);
                                man1[j]->setPosition(false);
                                man1[k]->setPosition(false);
                            }
                        }
                    }
                }
            }
        break;
        case 2:
            for (int i=0;i<man2Counter-1;i++)
            {   for (int j=1;j<man2Counter;j++)
                {   for (int k=2;k<man2Counter+1;k++)
                    {   if(i!=j && i!=k && j!=k)
                       // control for not count several times the same score
                        {   if(man2[i]->changePosition() || man2[j]->changePosition()|| man2[i]->changePosition())
                            {  //horizontally 3 pieces alined
                                if((man2[i]->getStrID().at(0)==man2[j]->getStrID().at(0)) && (man2[i]->getStrID().at(0)==man2[k]->getStrID().at(0)))
                                {
                                    // control for the two small horizontal line in the middle
                                    if(man2[i]->getStrID().at(0)=="d"&& man2[j]->getStrID().at(0)=="d" &&man2[k]->getStrID().at(0)=="d")
                                    {
                                        if( (man2[i]->getStrID().at(1)<52 &&man2[j]->getStrID().at(1)<52 &&man2[k]->getStrID().at(1)<52))
                                        {     gain = true;

                                        }
                                        if((man2[i]->getStrID().at(1)>52 &&man2[j]->getStrID().at(1)>52 &&man2[k]->getStrID().at(1)>52))
                                         {   gain = true;

                                        }
                                    }
                                    else
                                    {    gain =true;

                                    }
                                }
                               //vertically 3 pieces alined
                                if((man2[i]->getStrID().at(1)==man2[j]->getStrID().at(1)) && (man2[i]->getStrID().at(1)==man2[k]->getStrID().at(1)))
                                {   if(man2[i]->getStrID().at(1)== "4" && man2[j]->getStrID().at(1)== "4" &&man2[k]->getStrID().at(1)=="4")
                                    {   if((man2[i]->getStrID().at(0)<100 &&man2[j]->getStrID().at(0)<100 &&man2[k]->getStrID().at(0)<100))
                                            gain = true;
                                         if ((man2[i]->getStrID().at(0)>100 &&man2[j]->getStrID().at(0)>100 &&man2[k]->getStrID().at(0)>100))
                                            gain = true;
                                    }
                                    else
                                    {   gain =true;
                                    }
                                }
                            }
                            if(gain)
                            {   man2[i]->setPosition(false);
                                man2[j]->setPosition(false);
                                man2[k]->setPosition(false);
                            }
                         }
                    }
                }
            }
        break;
    }
    return gain;
}

// there is a bug at this point

void Controller::onPointToDelete()
{
    QLineEdit *delBox;
    delBox = input->getDelPoint();
    delBox->selectAll();
    pointToDelete=delBox->text().left(2).toLower();
    if(pointToDelete !="")
        win->setMessage(false);
    input->setText();


}

