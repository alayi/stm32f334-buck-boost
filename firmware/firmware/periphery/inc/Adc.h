/********************************************************************************
 * project     Class for initialization and read ADC                            *
 *                                                                              *
 * file        Adc.h                                                            *
 * author      Ilya Galkin                                                      *
 * date        15.05.2020                                                       *
 *                                                                              *
 ********************************************************************************/

#pragma once

/********************************************************************************
 * Include 
 ********************************************************************************/

#include "stm32f3xx.h"
#include "startupF334.h"
#include "Gpio.h"

/********************************************************************************
 * Class ADC
 * 
 * Pin voltage input    - PA0   - ADC1 IN1
 * Pin current input    - PA1   - ADC1 IN2
 * Pin voltage output   - PA2   - ADC1 IN3
 * Pin current output   - PA3   - ADC1 IN4
 * 
 ********************************************************************************/

class Adc {

    public:
        constexpr static uint16_t sizeBuffer = 50;

        static uint16_t inputVoltage;
        static uint16_t inputCurrent;
        static uint16_t outputVoltage;
        static uint16_t outputCurrent;
        static uint16_t step;

    public:
        static void Init();

    private:    
        static void GpioInit();
        static void StartCallibrationAdc();
        static void InitTimerEvent();
};