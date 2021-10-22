#ifndef INPUTPANEL_H
#define INPUTPANEL_H

#include "window.h"
#include <QLineEdit>
#include <QLabel>

class Window;

class InputPanel :public QLineEdit
{
    //Q_OBJECT
public:
    InputPanel(Window* win);
    ~InputPanel();
    QLineEdit* getText();
    QLineEdit *getDelPoint();
    void setText();

private:
    QLineEdit* textBox;
    QLineEdit* delPoint;
    QLabel* del;
/*
public slots:
    void onCommandEntered();
*/


};

#endif // INPUTPANEL_H
