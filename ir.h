#define NEC_BITS          32
#define NEC_HDR_MARK    9000
#define NEC_HDR_SPACE   4500
#define NEC_BIT_MARK     560
#define NEC_ONE_SPACE   1690
#define NEC_ZERO_SPACE   560
#define NEC_RPT_SPACE   2250

namespace ir {
    PwmOut irOut(PTA1);

    enum IR_COMMAND {
        BRIGHTNESS_UP, BRIGHTNESS_DOWN, OFF, ON,
        RED, GREEN, BLUE,WHITE,
        RED_1,GREEN_1,BLUE_1,FLASH,
        RED_2,GREEN_2,BLUE_2,STROBE,
        RED_3,GREEN_3, BLUE_3,FADE,
        RED_4,GREEN_4,BLUE_4,SMOOTH,
    };
    
    const static uint8_t keyMapping[] = {
        BRIGHTNESS_UP, BRIGHTNESS_DOWN, OFF, ON,
        BLUE, GREEN, RED,WHITE,
        GREEN_4, RED_4, BLUE_4,FLASH,
        GREEN_3, RED_3, BLUE_3,STROBE,
        GREEN_2, RED_2, BLUE_2,FADE,
        GREEN_1, RED_1, BLUE_1,SMOOTH
    };
    
    void mark(int time) {
        irOut = 0.5;
        wait_us(time);
        irOut = 0;
    }
    
    void space(int time) {
        irOut = 0;
        wait_us(time);    
    }
    
    void sendNecByte(uint8_t byte) {
        for(size_t c=0; c<8; c++) {
            if (byte & (1 << c)) {
                mark(NEC_BIT_MARK);
                space(NEC_ONE_SPACE);
            } else {
                mark(NEC_BIT_MARK);
                space(NEC_ZERO_SPACE);
            }
        }   
    }
    
    void  send(uint8_t cmd, uint8_t addr = 0)
    {
        cmd = keyMapping[cmd];
        irOut.period_us(26.3);

        // Header
        mark(NEC_HDR_MARK);
        space(NEC_HDR_SPACE);
    
        // Device
        sendNecByte(addr);
        sendNecByte(~addr);
        
        // Command
        sendNecByte(cmd);
        sendNecByte(~cmd);
    
        // Footer
        mark(NEC_BIT_MARK);
        space(0);  // Always end with the LED off
    }
}