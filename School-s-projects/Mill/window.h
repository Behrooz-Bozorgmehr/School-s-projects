#ifndef WINDOW_H
#define WINDOW_H
//#include "field.h"
#include "controller.h"
#include "inputpanel.h"
#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QRadioButton>
#include <QPainter>
#include <QLineEdit>
#include <QShortcut>
#include "man.h"

#define TITLE "MEN'S MORRIS GAME"
#define WIDTH 800
#define HEIGHT 800
#define RADIUS 10
#define MAXPCS 12;

class Controller;
class InputPanel;
class Field;
class Window : public QWidget
{
    Q_OBJECT

public:
    Window(int x, int y);
    ~Window();
    void setup();
    void gameField();
    void paintEvent(QPaintEvent *e);
    void setPiece(int x);
    void setPlayer(QString x);
    void setPhase(QString x);
    void initRelations(Controller *control, InputPanel *input);
    void setMessage(bool b);


protected:
    Controller* ctr;
    InputPanel* input;
    Field* fld;
    Man **man1;
    Man **man2;

 private:
    int x;
    int y;

    //indicators
    QLabel *lblPhase;
    QLabel *lblTurn;
    QLabel *lbl3;
    QLabel *lbl6;
    QLabel *lbl9;
    QLabel *lbl12;
    QLabel *lblPoint;
    QLabel *lblExample;
    QLabel *msg;
    QString player = "1";
    QString phase = "Placing";

    QRadioButton *three;
    QRadioButton *six;
    QRadioButton *nine;
    QRadioButton *twelve;

    // position of RB. & their labels
    int xRadio = 50;
    int yRadio = 50;
    int dist = 30;      // distance between each RB. & between RB and its label
    int xLbl ;
    int yLbl;
    int width = 400;
    int pcsTotal = 12;

  //  bool message;

    // shortcuts to be totally based on keyboard
    QShortcut *rb3;
    QShortcut *rb6;
    QShortcut *rb9;
    QShortcut *rb12;

public slots:
    void setTotal();
    void setMen(Man **man1,Man **man2);
    void renew();


};

#endif // WINDOW_H
