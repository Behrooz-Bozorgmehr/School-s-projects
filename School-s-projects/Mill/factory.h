#ifndef FACTORY_H
#define FACTORY_H
#include "window.h"
#include "controller.h"
#include "inputpanel.h"


class Factory
{
public:
   Factory();
   ~Factory();
   void build();
private:
   Window* win;
   Controller* control;
   InputPanel* input;


};



#endif // FACTORY_H
