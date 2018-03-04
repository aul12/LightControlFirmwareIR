#include "ir.h"
#define MINIMAL_STEP 50
#define FADE_STEP 400

uint8_t command = 255;
int state = 0;

void doWakeUp() {
    if(state == 0) {
        for(int c=0; c<20; c++) {
            ir::send(ir::ON);
            wait_ms(MINIMAL_STEP);
            ir::send(ir::WHITE);
            wait_ms(MINIMAL_STEP);
            ir::send(ir::BRIGHTNESS_DOWN);
            wait_ms(MINIMAL_STEP);
        }
    } else {
        if(state % 60== 0) {
            ir::send(ir::BRIGHTNESS_UP);
        }
    }
    state++;
}

void fade() {
    static int row = 1, col = 0;
    static int brightness = 10;
    static bool brightnessDown = true;
    
    if(state == 0) {
        row = 1;
        col = 0;
        state = 1;
        brightness = 10;
        brightnessDown = true;
    }
    
    if(brightness <= 0 && brightnessDown) {
        ir::send(4*row + col);  
        if(++row >= 6) {
            row = 1;
            if(++col >= 3) {
                col = 0;
            }  
        }
        brightnessDown = false;
    } else if(brightnessDown) {
        ir::send(ir::BRIGHTNESS_DOWN);
        brightness--;
    } else {
        ir::send(ir::BRIGHTNESS_UP);
        if(++brightness >= 15) {
            brightnessDown = true;    
        }
    }
}

void commandTicker() {
    if(command < 24) {
        if(++state < 10) {
            ir::send(command);
        }
    } else if(command == 24) {
        doWakeUp();
    } else if(command == 25) {
        fade();
    }
}