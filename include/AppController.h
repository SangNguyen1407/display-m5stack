#ifndef APP_CONTROLLER_H
#define APP_CONTROLLER_H

#include "Home.h"
#include "Order.h"

class AppController {
public:
    AppController();
    void run();

private:
    int currentPage;
    Home home;
    Order order;
};

#endif