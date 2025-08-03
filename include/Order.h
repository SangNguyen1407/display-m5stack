#ifndef ORDER_H
#define ORDER_H
#include <Arduino.h>
#include <M5Unified.h>
#include "MyButton.h"

class Order {
    public:
        Order();
        int show();
    private:
        struct Item {
            int _RowNumber;
            String RowID;
            String equipmentCode;
            String equipmentName;
            String storePlace;
            int price;
            String orderNumber;
            String supplierName;
            String RelatedOrderItems;
        };
        std::vector<Item> items;
        int currentItemPage; 

        MyButton scrollUpButton;
        MyButton scrollDownButton;

        void drawPage();
        void setupButtons();

        void scrollUp();
        void scrollDown();
        void showQRCode(String id);
};

#endif