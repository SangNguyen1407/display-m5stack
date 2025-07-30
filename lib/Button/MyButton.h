#ifndef BUTTON_H
#define BUTTON_H

// #include <M5Core2.h>
#include <M5Unified.h>
#include <MyButton.h>

class MyButton {
    public:
        MyButton() = default;
        MyButton(
            const String& label,
            int x, int y, int width, int height,
            std::function<void()> onPressed,
            uint32_t color = WHITE,
            uint32_t textColor = BLACK,
            float textSize = 1,
            bool autoDraw = true
        );
        void draw() const;
        bool isPressed(int touchX, int touchY);
        void update();

    private:
        String label;
        int x = 0, y = 0, width = 0, height = 0;
        uint32_t color = WHITE, textColor = BLACK;
        std::function<void()> onPressed;
        unsigned long pressTime = 0;
        bool isHighlighted = false;
        float textSize = 1;
        bool autoDrawEnabled = true;
};

#endif