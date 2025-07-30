#include <Home.h>

Home::Home() : nextPage(0) {
    orderHistory[0] = {"注文待", "", "黒色ボールペン"};
    orderHistory[1] = {"注文済", "2024/7/28", "メモパッド"};
    orderHistory[2] = {"注文済", "2024/7/28", "単三電池 24本入り"};
    orderHistory[3] = {"注文済", "2024/7/14", "ホワイトボードマーカー"};
    orderHistory[4] = {"注文済", "2024/7/15", "テスト"};

    setupButtons();
}

int Home::show(){
    drawPage();
    nextPage = 0;
    bool showSomeDialog = false;

    while (true) {
        M5.update();
        // bool hasUpdate = fetchOrderHistory();
        
        // if(hasUpdate){
        //     drawOrderedItems();
        // }
        if(M5.Touch.getCount() > 0){
            auto touch = M5.Touch.getDetail();
            newOrderButton.isPressed(touch.x, touch.y);
            deliveryButton.isPressed(touch.x, touch.y);
        }
        newOrderButton.update();
        deliveryButton.update();
    
        if (nextPage != 0) {
            return nextPage;  // ページ遷移
        }   

    }
}

void Home::drawPage(){
    int y = 0;

    M5.Lcd.fillScreen(BLACK);
    M5.Lcd.setTextColor(WHITE);
    M5.Lcd.setTextDatum(TL_DATUM);
    M5.Lcd.setTextSize(1.5);
    M5.Lcd.drawString("発注履歴",5, y);

    y +=35;

    M5.Lcd.drawLine(0, y, M5.Lcd.width(),y, WHITE);
    y +=15;

    M5.Lcd.setTextSize(1);
    M5.Lcd.setTextDatum(ML_DATUM);
    int rowHeight = 20;
    for (int i = 0; i < ORDER_HISTORY_SIZE; i++) {
        String status = orderHistory[i].status;

        M5.Lcd.fillRoundRect(10,y,70,rowHeight, rowHeight/2 ,status=="注文待"? BLUE:TFT_ORANGE);
        M5.Lcd.drawString(status,               20,y+rowHeight/2);
        M5.Lcd.drawString(orderHistory[i].name, 90,y+rowHeight/2);
        
        y += rowHeight + 10;
    }
    newOrderButton.draw();
    deliveryButton.draw();
}

void Home::setupButtons(){
    newOrderButton = MyButton(
        "新規注文",
        20, 200, 120, 30,
        [this]() { nextPage = 1; },
        WHITE, BLACK, 1.4
    );

    deliveryButton = MyButton(
        "納品",
        180, 200, 120, 30,
        [this]() { nextPage = 2; },
        GREEN, WHITE, 1.4
    );
}


// void Home::drawOrderedItems(){
//     // 画面上にオーダーを描画
//     int y = 50;
//     M5.Lcd.setTextSize(1);
//     M5.Lcd.setTextDatum(ML_DATUM);
//     int rowHeight = 20;
//     for (int i = 0; i < ORDER_HISTORY_SIZE; i++) {
//         String status = orderHistory[i].OrderState;

//         M5.Lcd.fillRoundRect(10,y, 70, rowHeight, rowHeight/2 ,status=="注文待"? BLUE:TFT_ORANGE);
//         M5.Lcd.drawString(status, 20, y+rowHeight/2);
//         M5.Lcd.drawString(orderHistory[i].ItemName, 90, y+rowHeight/2);
        
//         y += rowHeight + 10;
//     }    
// }

// bool Home::fetchOrderHistory(){
//     if(millis() - previousFetchMillis < 5000){
//         return false;
//     }
//     previousFetchMillis = millis();
//     String oldItemsTopCode = orderedItems[0].ItemCode;
//     const char* selector = "FILTER('注文アイテム', ([場所名]='居室'))";
// }