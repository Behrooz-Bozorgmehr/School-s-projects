#ifndef CONTROLLER_H
#define CONTROLLER_H
#include "window.h"
#include "inputpanel.h"
#include "man.h"
#include "field.h"
#include <QDebug>
#include <QWidget>
#include <QLineEdit>
#define MAXPCS 12;
class InputPanel;
class Window;
class Field;
class Man;
class Controller :public QWidget
{
    Q_OBJECT
public:
    Controller();
    ~Controller();
    void initRelations(Window *win, InputPanel *input);
    void setField(Field *f);
    void setMan(Man *m1[], Man *m2[]);
    void setPiece(int pcs);
    void move(QString p1,QString p2);
    void remove(QString p1, QString p2);
    QPoint delPoint(QString p);
    bool score();

private:
    int placeCounter =0;
    int deleteCounter1 =0;
    int deleteCounter2 =0;
    int pcsTotal;
    int pcsPlaced;
    int player;
    int man1Counter;
    int man2Counter;
    bool gain;
    InputPanel *input;
    Window* win;
    Field *fld;
    Man **man1;
    Man **man2;
    QString pointToDelete;

public slots:
    void place();
    void onCommandEntered();
    void onPointToDelete();
    void start();



};

#endif // CONTROLLER_H
