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
 ********************************************************************************/

class Feedback {
    public:
        static float inputVoltage() {
            return (Feedback::voltageDiv * Feedback::sampleStepAdc * Adc::inputVoltage);
        };
/*
        static float inputCurrent() {

        };

        static float outputVoltage() {

        };

        static float outputCurrent() {

        };
*/
    private:
        constexpr static float voltageDiv = 4.9f;
        constexpr static float sampleStepAdc = 0.000805f;
};