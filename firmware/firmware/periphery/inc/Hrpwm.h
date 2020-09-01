/********************************************************************************
 * project     Class for initialization and work with High Resolution PWM       *
 *                                                                              *
 * file        Hrpwm.h                                                          *
 * author      Ilya Galkin                                                      *
 * date        13.05.2020                                                       *
 *                                                                              *
 ********************************************************************************/

#pragma once

/********************************************************************************
 * Include 
 ********************************************************************************/

#include "stm32f3xx.h"
#include "Gpio.h"

/********************************************************************************
 * Class HRPWM
 * 
 * Dead time - 34.7 ns
 * Channel A and B
 * 
 ********************************************************************************/

class Hrpwm {
    public:
        enum class Channel {
            buck, boost
        };

        enum class Status {
            disable, enable
        };

    public:
        static void Init();
        static void SetDuty(Channel channel, uint16_t duty);
        static void DriverControl(Channel channel, Status status);

    private:
        static void InitGpio();

    private:
        constexpr static uint16_t periodHrpwm = 30000;     // Fsw = 207 kHz
};