#include "inputpanel.h"

InputPanel::InputPanel(Window* win)
{   //initialize attributs
    textBox = new QLineEdit(win);
    textBox->setVisible(true);
    textBox->setGeometry(200,700,210,30);
    delPoint = new QLineEdit(win);
    delPoint->setVisible(true);
    delPoint->setGeometry(200,750,210,30);
    del = new QLabel("Man to delete: ", win);
    del->setVisible(true);
    del->setGeometry(100,750,100,30);

}

InputPanel::~InputPanel()
{

}

QLineEdit * InputPanel::getText()
{
    return textBox;
}

QLineEdit *InputPanel::getDelPoint()
{
    return delPoint;
}

void InputPanel::setText()
{
    textBox->del();
    delPoint->del();
}
