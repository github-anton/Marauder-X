#pragma once

#ifndef flipperLED_h
#define flipperLED_h

#include "configs.h"
#include "Settings.h"
#include "Marauder.h"

#include <Arduino.h>


class flipperLED {

  public:
    void RunSetup();
    void main();
    void attackLED();
    void sniffLED();
    void offLED();
};

#endif
