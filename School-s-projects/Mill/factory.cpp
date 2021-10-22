#include "factory.h"

Factory::Factory()
{   //initialize attributs
    win = new Window(600,100);
    control = new Controller();
    input = new InputPanel(win);
}

Factory::~Factory()
{
    delete win;
    delete control;
    delete input;
}
//set the relations and show the result
void Factory::build()
{   win->initRelations(control,input);
    control->initRelations(win,input);
    win->show();
}
