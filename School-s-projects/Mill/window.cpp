#include "window.h"
#include <QDebug>
#include <QPalette>

Window::Window(int x, int y)
{
    //initialization of attributs
    ctr = nullptr;
    input = nullptr;
    fld = nullptr;
    man1 = nullptr;
    man2 = nullptr;
    lblPhase = nullptr;
    lblTurn = nullptr;
    lbl3 = nullptr;
    lbl6 = nullptr;
    lbl9 = nullptr;
    lbl12 = nullptr;
    lblPoint = nullptr;
    player = "1";
    phase = "Placing";
    this->x = x;
    this->y = y;
    three = nullptr;
    six = nullptr;
    nine = nullptr;
    twelve = nullptr;

    // position of RB. & their labels
    xRadio = 50;
    yRadio = 50;
    dist = 30;      // distance between each RB. & between RB and its label
    xLbl  = 0;
    yLbl =0;
    width = 400;
    pcsTotal = MAXPCS;
    rb3 = new QShortcut(this);
    rb3->setKey(Qt::CTRL + Qt::Key_3);
    rb6 = new QShortcut(this);
    rb6->setKey(Qt::CTRL + Qt::Key_6);
    rb9 = new QShortcut(this);
    rb9->setKey(Qt::CTRL + Qt::Key_9);
    rb12 = new QShortcut(this);
    rb12->setKey(Qt::CTRL + Qt::Key_1);
    // arrange elements of window
    setup();
    // set board of the game
    gameField();
}

Window::~Window()
{}

void Window::setup()
{   // set window size
    this->setGeometry(x,y,WIDTH,HEIGHT);
    this->setWindowTitle(TITLE);
    this->setFixedSize(WIDTH,HEIGHT);

    // set black background color
    QPalette pal = palette();
    pal.setColor(QPalette::Background, Qt::darkCyan);
    this->setAutoFillBackground(true);
    this->setPalette(pal);

    //creat buttons & labels
    lblPoint = new QLabel("Enter a point: ",this);
    lblPoint->setGeometry(100,700,100,30);
    lblExample =new QLabel("Example: <<a4>>, <<f2 f4>>", this);
    lblExample->setGeometry(450,700,200,30);
    lblPhase = new QLabel("Phase: "+phase,this);
    lblPhase->setGeometry(10,15,width,25);
    lblTurn = new QLabel("Player: "+player,this);
    lblTurn->setGeometry(700,15,width,25);
    msg = new QLabel("Choose a MAN to remove from the game",this);
    msg->setGeometry(200,670,300,30);
    msg->setVisible(false);

    //RadioButtons give the choice of No. men(3,6,9 or 12)
    // distance  between RB and its label
    xLbl = xRadio +dist;
    yLbl = yRadio;

    three = new QRadioButton("&&three",this);
    three->setGeometry(xRadio,yRadio,20,20);
    lbl3 = new QLabel("Three men's mill: Press CTRL+3 ",this);
    lbl3->setGeometry(xLbl,yLbl,width,25);

    six = new QRadioButton("&&six",this);
    six->setGeometry(xRadio,yRadio+dist,20,20);
    lbl6 = new QLabel("Six men's mill: Press CTRL+6 ",this);
    lbl6->setGeometry(xLbl,yLbl+dist,width,25);

    nine = new QRadioButton("&&Nine",this);
    nine->setGeometry(xRadio,yRadio+2*dist,20,20);
    lbl9 = new QLabel("Nine men's mill: Press CTRL+9 ",this);
    lbl9->setGeometry(xLbl,yLbl+2*dist,width,25);

    twelve = new QRadioButton("&&twelve",this);
    twelve->setGeometry(xRadio,yRadio+3*dist,20,20);
    lbl12 = new QLabel("Twelve men's mill: Press CTRL+1 ",this);
    lbl12->setGeometry(xLbl,yLbl+3*dist,width,25);


}

void Window::gameField()
{   // define the size & position of the board
    int centerX,centerY,x,y,width;
    centerX = WIDTH/2 ;
    centerY = HEIGHT/2 ;
    width = WIDTH/2;
    x = centerX-(width/2) ;
    y = centerY -(width/2);

    // set the board
    fld = new Field(x,y,width,pcsTotal,this);

    // set elements of the game
    man1 = (Man**)new Man *[pcsTotal];
    man2 = (Man**)new Man *[pcsTotal];
    QColor col1(Qt::red);
    QColor col2(Qt::blue);
    for (int i=0;i<pcsTotal; i++)
    {
        man1[i] = new Man(15,col1 );
        man2[i] = new Man(15,col2 );
    }

}

void Window::paintEvent(QPaintEvent *e)
{   // draw whole window
    QPainter ptr(this);
    ptr.setPen(QPen(Qt::black, 2));

    // draw board of the game
    fld->draw(&ptr);

    // draw men
    for (int i=0; i<pcsTotal; i++)
        {
            man1[i]->draw(&ptr);
            man2[i]->draw(&ptr);
        }
}

void Window::setPiece(int pcs)
{
    pcsTotal = pcs;
}

void Window::setPlayer(QString x)
{
    player =x;      // update
    lblTurn->setText("Player:"+player);

}

void Window::setPhase(QString x)
{
    phase = x;
    lblPhase->setText("Phase: "+phase);
}

void Window::initRelations(Controller *control, InputPanel *input)
{
    this->ctr = control;
    this->input = input;
    QLineEdit *text;
    QLineEdit *del;

    // connect shortcuts to RadioButtons
    connect(rb3,SIGNAL(activated()),three,SLOT(click(void)));
    connect(rb6,SIGNAL(activated()),six,SLOT(click(void)));
    connect(rb9,SIGNAL(activated()),nine,SLOT(click(void)));
    connect(rb12,SIGNAL(activated()),twelve,SLOT(click(void)));

    // connect RadioButtons to slots, slots will call the right methods
    connect(three,SIGNAL(clicked(bool)),this,SLOT(setTotal(void)));
    connect(six,SIGNAL(clicked(bool)),this,SLOT(setTotal(void)));
    connect(nine,SIGNAL(clicked(bool)),this,SLOT(setTotal(void)));
    connect(twelve,SIGNAL(clicked(bool)),this,SLOT(setTotal(void)));

    // connect text box to slots,
    text = this->input->getText();
    del = this->input->getDelPoint();
    connect(text,SIGNAL(returnPressed()),ctr,SLOT(onCommandEntered()));
    connect(del,SIGNAL(returnPressed()),ctr,SLOT(onPointToDelete()));


}

void Window::setMessage(bool b)
{
    msg->setVisible(b);
}


//change the number of men based on version of the game
// call the board and the logic of the game to adapte themselves
void Window::setTotal()
{
    if (three->isChecked())
        pcsTotal = 3;
    if (six->isChecked())
        pcsTotal = 6;
    if (nine->isChecked())
        pcsTotal = 9;
    if (twelve->isChecked())
        pcsTotal = 12;

    fld->setPiece(pcsTotal);
    ctr->setPiece(pcsTotal);
    ctr->setField(fld);
    ctr->place();
}
// change the position and properties of each man
void Window::setMen(Man **man1, Man **man2)
{
    this->man1 = man1;
    this->man2 = man2;
}

// update the window
void Window::renew()
{
    this->update();
}






