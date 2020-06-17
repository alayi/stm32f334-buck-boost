/********************************************************************************
 * project     Class for initialization and contoller LED                       *
 *                                                                              *
 * file        Led.h                                                            *
 * author      Ilya Galkin                                                      *
 * date        11.05.2020                                                       *
 *                                                                              *
 ********************************************************************************/

#pragma once

/********************************************************************************
 * Include 
 ********************************************************************************/

#include "stm32f3xx.h"
#include "Gpio.h"

/********************************************************************************
 * Class Led
 * 
 * LED0     -   BLUE    -   PB15    -   Status signal
 * LED1     -   RED     -   PB14    -   Over current protection
 * LED2     -   RED     -   PB13    -   Over voltage protection
 * LED3     -   RED     -   PB12    -   Over temperature protection
 * 
 ********************************************************************************/

class Led {

    public:
        enum class TypeSignal:int {
            status, 
            overCurrentProtection, 
            overVoltageProtection, 
            overTemperatureProtection
        };

    public:
        static void Init (void);
        static void On (TypeSignal led);
        static void Off (TypeSignal led);
        static void Toggle (TypeSignal led);
};