/********************************************************************************
 * project     Class for filtering and conversion ADC result                    *
 *                                                                              *
 * file        Feedback.h                                                       *
 * author      Ilya Galkin                                                      *
 * date        19.06.2020                                                       *
 *                                                                              *
 ********************************************************************************/

/********************************************************************************
 * Include 
 ********************************************************************************/

#include "Adc.h"

/********************************************************************************
 * Class
 * 
 * Divider input voltage: 39 kOhm / 10 kOhm + 1= 4.9
 * Divider output voltage: 39 kOhm / 10 kOhm + 1 = 4.9
 * 
 * Gain input current: 50
 * Gain output current: 50
 * Current shunt: 0.015 Ohm
 * 
 ********************************************************************************/

class Feedback {
    public:
        static float GetInputVoltage() {
            return (Feedback::voltageDiv * Feedback::sampleStepAdc * Adc::inputVoltage);
        };

        static float GetInputCurrent() {
            return (Adc::inputCurrent * Feedback::sampleStepAdc / Feedback::currentGain / Feedback::currentShunt);
        };

        static float GetOutputVoltage() {
            return (Feedback::voltageDiv * Feedback::sampleStepAdc * Adc::outputVoltage);
        };

        static float GetOutputCurrent() {
            return (Adc::outputCurrent * Feedback::sampleStepAdc / Feedback::currentGain / Feedback::currentShunt + staticErrorOutputCurrent);
        };

    private:
        constexpr static float voltageDiv = 4.9f;
        constexpr static float sampleStepAdc = 0.000805f;
        constexpr static float currentGain = 50.0f;
        constexpr static float currentShunt = 0.015f;
        constexpr static float staticErrorOutputCurrent = -0.1f;
};