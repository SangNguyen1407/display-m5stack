#include "Order.h"

Order::Order(): currentItemPage(0) {
    setupButtons();
}

int Order::show() {
    drawPage();

    while (true){
        M5.update();

        if (M5.Touch.getCount() > 0) {
            auto touch = M5.Touch.getDetail();

            if(touch.x > 280){
                scrollUpButton.isPressed(touch.x, touch.y);
                scrollDownButton.isPressed(touch.x, touch.y);
            }
            else if(touch.y < 200) {
                // アイテムの選択処理
                int index = touch.y / 50;
                if (index < items.size()) {
                    showQRCode(items[index].equipmentCode);
                    drawPage();
                }
            }
            scrollUpButton.update();
            scrollDownButton.update();
        }
        // BtnAが押されたら前の画面に戻る
        if (M5.BtnA.wasPressed()) {
            return 0; // ホームページへ戻る
        }
    }
}

void Order::drawPage() {
    int y = 0;

    M5.Lcd.fillScreen(BLACK);
    M5.Lcd.setTextColor(WHITE);
    M5.Lcd.setTextDatum(TL_DATUM);
    M5.Lcd.setTextSize(2);
    M5.Lcd.drawString("新規注文",5, y);

    y +=35;

    M5.Lcd.drawLine(0, y, M5.Lcd.width(),y);

    y +=15;

    M5.Lcd.setTextSize(1);
    M5.Lcd.setTextDatum(ML_DATUM);
    int startIndex = currentItemPage * 6;
    int endIndex = std::min(startIndex + 6, static_cast<int>(items.size()));
    for (int i = startIndex; i < endIndex; i++) {
        const auto& item = items[i];
        M5.Lcd.drawString(item.equipmentName, 10, y);
        M5.Lcd.drawString("¥" + String(item.price), 200, y);
        y += 30;
    }

    // スクロールボタンの描画
    scrollUpButton.draw();
    scrollDownButton.draw();
}

void Order::showQRCode(String id) {
    bool shouldClose = false;  // ダイアログを閉じるためのフラグ

    const int mx = 50;
    const int my = 20;
    const int p = 30;
    const int dialogW = M5.Lcd.width() -mx*2;
    const int dialogH = M5.Lcd.height()-my*2;

    // ダイアログの描画
    M5.Lcd.drawRect(mx,my,dialogW,dialogH, WHITE);
    M5.Lcd.fillRect(mx+2,my+2,dialogW-4,dialogH-4, BLUE);

    M5.Lcd.setColor(WHITE);
    M5.Lcd.qrcode(id, mx+p,my+p,std::min(dialogW,dialogH)-p*2,6);

    // 閉じるボタンの作成
    MyButton closeButton(
        "閉じる", 
        mx + dialogW - 60, my + dialogH - 30, 60, 30, 
        [&shouldClose]() { shouldClose = true;}, 
        RED, WHITE, 1
    );

    closeButton.draw();
    
    while (!shouldClose) {  // フラグがfalseの間ループを続ける
        M5.update();
        if (M5.Touch.getCount() > 0) {
            auto touch = M5.Touch.getDetail();
            closeButton.isPressed(touch.x, touch.y);
        }
        closeButton.update();
    }
}

void Order::setupButtons() {
    scrollUpButton = MyButton(
        "▲",
        280, 40, 30, 30,
        [this]() { scrollUp(); },
        WHITE, BLACK, 1.4
    );

    scrollDownButton = MyButton(
        "▼",
        280, 180, 30, 30,
        [this]() { scrollDown(); },
        GREEN, WHITE, 1.4
    );
}

void Order::scrollUp() {
    if (currentItemPage > 0) {
        currentItemPage--;
        drawPage();
    }
}

void Order::scrollDown() {
    if ((currentItemPage + 1) * 6 < items.size()) {
        currentItemPage++;
        drawPage();
    }
}