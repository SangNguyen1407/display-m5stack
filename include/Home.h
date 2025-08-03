#ifndef HOME_H
#define HOME_H

#include <Arduino.h>
#include <M5Unified.h>
#include <MyButton.h>

class Home {
    public:
        Home();
        int show();

    private:
        struct OrderedItem {
            String status;
            String date;
            String name;
        };

        static const int ORDER_HISTORY_SIZE = 5;
        OrderedItem orderHistory[ORDER_HISTORY_SIZE];
        
        MyButton newOrderButton;
        MyButton deliveryButton;
        
        void drawPage();
        void setupButtons();

        int currentPage; 
};

#endif