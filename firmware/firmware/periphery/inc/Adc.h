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
 * Divider input voltage: 39 kOhm / 10 kOhm = 4.9
 * Divider output voltage: 39 kOhm / 10 kOhm = 4.9
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

        static float inputVoltage [sizeBuffer];
        static float inputCurrent [sizeBuffer];
        static float outputVoltage [sizeBuffer];
        static float outputCurrent [sizeBuffer];
        static uint16_t step;

    public:
        static void Init();

    private:
        constexpr static float voltageDivInput = 19.6078f;
        constexpr static float voltageDivOutput12V = 4.1667f;
        constexpr static float voltageDivOutput24V = 8.3333f;

    private:    
        static void GpioInit();
        static void StartCallibrationAdc();
        static void InitTimerEvent();
};