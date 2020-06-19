/********************************************************************************
 * Class        Application logic for dc/dc buck-boost                          *
 *                                                                              *
 * file         Application.h                                                   *
 * author       Ilya Galkin                                                     *
 * date         18.06.2020                                                      *
 *                                                                              *
 ********************************************************************************/

#pragma once

/********************************************************************************
 * Include 
 ********************************************************************************/

#include "stm32f3xx.h"
#include "startupF334.h"

#include "Pid.h"

#include "Feedback.h"

#include "Hrpwm.h"
#include "Led.h"

/********************************************************************************
 * Class 
 ********************************************************************************/

class Application {
    public:
        struct StatusFlag {
            static bool errorUVLO;
        };

        static float limitUVLO;         
        static float referenceOutputVoltage;
        
        constexpr static uint16_t boostFixDuty = 6000;
        static uint16_t duty;

    public:
        static void Init();
        static void SetUserSettings (float uvlo, float referenceVoltage);
        
    private:
        static void StartApplicationTimer();
        static bool UVLO (float reference);
};