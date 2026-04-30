#pragma once

#ifndef stickcLED_H
#define stickcLED_H

#include "configs.h"
#include <Arduino.h>

#if defined(MARAUDER_M5STICKC) || defined(MARAUDER_M5STICKCP2)


class stickcLED {

    public:
        void RunSetup();
        void main();
        void attackLED();
        void sniffLED();
        void offLED();
};

#endif
#endif  /* stickcLED_H */
