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
 * Divider input voltage: 39 kOhm / 10 kOhm = 4.9
 * Divider output voltage: 39 kOhm / 10 kOhm = 4.9
 * 
 * Gain input current: 20 kOhm / (1 kOhm + 1 kOhm) = 10
 * Gain output current: 20 kOhm / (1 kOhm + 1 kOhm) = 10
 * Current shunt: 0.05 Ohm
 * 
 ********************************************************************************/

class Feedback {
    public:
        static float inputVoltage() {
            return (Feedback::voltageDiv * Feedback::sampleStepAdc * Adc::inputVoltage);
        };

        static float inputCurrent() {
            return (Adc::inputCurrent * Feedback::sampleStepAdc / Feedback::currentGain / Feedback::currentShunt);
        };

        static float outputVoltage() {
            return (Feedback::voltageDiv * Feedback::sampleStepAdc * Adc::outputVoltage);
        };

        static float outputCurrent() {
            return (Adc::outputCurrent * Feedback::sampleStepAdc / Feedback::currentGain / Feedback::currentShunt);
        };

    private:
        constexpr static float voltageDiv = 4.9f;
        constexpr static float sampleStepAdc = 0.000805f;
        constexpr static float currentGain = 10.0f;
        constexpr static float currentShunt = 0.05f;
};