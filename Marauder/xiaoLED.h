#pragma once

#ifndef xiaoLED_H
#define xiaoLED_H


#define XIAO_LED_PIN 21


class xiaoLED {

    public:
        void RunSetup();
        void main();
        void attackLED();
        void sniffLED();
        void offLED();
};

#endif  /* xiaoLED_H */