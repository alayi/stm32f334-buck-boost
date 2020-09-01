/********************************************************************************
 * Include 
 ********************************************************************************/

#include "Feedback.h"

/********************************************************************************
 * Class Feedback
 ********************************************************************************/

float Feedback::GetInputVoltage() {
    Adc::Status::stopInputVoltage = true;
    float inputVoltage = FilterWindowMedium::Compute(Adc::inputVoltage, Adc::sizeBuffer, sizeWindow);
    Adc::Status::stopInputVoltage = false;
    return (inputVoltage * Feedback::voltageDiv * Feedback::sampleStepAdc);
};

float Feedback::GetInputCurrent() {
    Adc::Status::stopInputCurrent = true;
    float inputCurrent = FilterWindowMedium::Compute(Adc::inputCurrent, Adc::sizeBuffer, sizeWindow);
    Adc::Status::stopInputCurrent = false;
    return (inputCurrent * Feedback::sampleStepAdc / Feedback::currentGain / Feedback::currentShunt);
};


float Feedback::GetOutputVoltage() {
    Adc::Status::stopOutputVoltage = true;
    float outputVoltage = FilterWindowMedium::Compute(Adc::outputVoltage, Adc::sizeBuffer, sizeWindow);
    Adc::Status::stopOutputVoltage = false;
    return (outputVoltage * Feedback::voltageDiv * Feedback::sampleStepAdc);
};

float Feedback::GetOutputCurrent() {
    Adc::Status::stopOutputCurrent = true;
    float outputCurrent = FilterWindowMedium::Compute(Adc::outputCurrent, Adc::sizeBuffer, sizeWindow);
    Adc::Status::stopOutputCurrent = false;
    return (outputCurrent * Feedback::sampleStepAdc / Feedback::currentGain / Feedback::currentShunt);
};