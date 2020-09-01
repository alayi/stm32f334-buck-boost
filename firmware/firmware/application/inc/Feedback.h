/********************************************************************************
 * class        Filtering and conversion ADC result                             *
 *                                                                              *
 * file         Feedback.h                                                      *
 * author       Ilya Galkin                                                     *
 * date         19.06.2020                                                      *
 *                                                                              *
 ********************************************************************************/

/********************************************************************************
 * Include 
 ********************************************************************************/

#include "Adc.h"
#include "FilterWindowMedium.h"

/********************************************************************************
 * Class
 * 
 * Divider input voltage: 39 kOhm / 10 kOhm + 1= 4.9
 * Divider output voltage: 39 kOhm / 10 kOhm + 1 = 4.9
 * 
 * Gain output current: 50
 * Current shunt: 0.02 Ohm
 * 
 ********************************************************************************/

class Feedback {
    public:
        constexpr static uint16_t sizeWindow = 20;

        static float GetInputVoltage();
        static float GetInputCurrent();
        static float GetOutputVoltage();
        static float GetOutputCurrent();

    private:
        constexpr static float voltageDiv = 4.9f;
        constexpr static float sampleStepAdc = 0.000805f;
        constexpr static float currentGain = 50.0f;
        constexpr static float currentShunt = 0.02f;
};