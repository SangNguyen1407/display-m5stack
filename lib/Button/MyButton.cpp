#include "MyButton.h"

MyButton::MyButton(
    const String& label,
    int x, int y, int width, int height,
    std::function<void()> onPressed,
    uint32_t color,
    uint32_t textColor,
    float textSize,
    bool autoDraw
) : label(label), x(x), y(y), width(width), height(height),
    onPressed(onPressed), color(color), textColor(textColor),
    textSize(textSize), autoDrawEnabled(autoDraw)
{
    if (autoDrawEnabled) {
        draw();
    }
}

void MyButton::draw() const {
    int32_t colorValue = isHighlighted? color : ((color & 0xFF000000) | (~color & 0x00FFFFFF));
    M5.Lcd.fillRect(x, y, width, height, colorValue);
    M5.Lcd.drawRect(x, y, width, height, colorValue);

    int32_t textColorValue = isHighlighted? textColor : ((textColor & 0xFF000000) | (~textColor & 0x00FFFFFF));
    M5.Lcd.setTextSize(textSize);
    M5.Lcd.setTextColor(textColorValue);
    M5.Lcd.setTextDatum(MC_DATUM);
    M5.Lcd.drawString(label, x + width / 2, y + height / 2);
}

bool MyButton::isPressed(int touchX, int touchY){
    bool pressed = (touchX >= x && touchX < x + width &&
                    touchY >= y && touchY < y + height);
    if (pressed && !isHighlighted) {
        isHighlighted = true;
        pressTime = millis();
        draw();
        if (onPressed) {
            onPressed();
        }
    }
    return pressed;
}

void MyButton::update(){
    if (isHighlighted && millis() - pressTime > 200) {
        isHighlighted = false;
        draw();
    }
}