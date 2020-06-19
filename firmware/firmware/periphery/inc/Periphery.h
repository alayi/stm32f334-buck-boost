/********************************************************************************
 * class        Setting periphery                                               *
 *                                                                              *
 * file         Periphery.h                                                     *
 * author       Ilya Galkin                                                     *
 * date         17.06.2020                                                      *
 *                                                                              *
 ********************************************************************************/

#pragma once

/********************************************************************************
 * Include 
 ********************************************************************************/

#include "stm32f3xx.h"
#include "startupF334.h"

#include "Led.h"
#include "Hrpwm.h"
#include "Clock.h"
#include "Adc.h"

/********************************************************************************
 * Class Periphery
 ********************************************************************************/

class Periphery {
    public:
        static void ResetHrpwmChannel() {
            Gpio::Init<8,9,10,11>(GPIOA, Gpio::Mode::output, Gpio::Type::PP); 
            Gpio::Reset<8,9,10,11>(GPIOA);
        }

        static void Init() {
            Periphery::ResetHrpwmChannel();
            Clock::Init();
            Led::Init();
            Hrpwm::Init();
            Adc::Init();
        }
};