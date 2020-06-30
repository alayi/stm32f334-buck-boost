/********************************************************************************
 * Include 
 ********************************************************************************/

#include "Application.h"

/********************************************************************************
 * Variables
 ********************************************************************************/

bool Application::StatusFlag::errorUVLO = 0;

uint16_t Application::dutyBuck = 0;
uint16_t Application::dutyBoost = 0;
float Application::limitUVLO = 0.0f;
float Application::referenceOutputVoltage = 0.0f;
float Application::referenceOutputCurrent = 0.0f;

PidController pidVoltageMode;
PidController pidCurrentMode;

/********************************************************************************
 * Class
 ********************************************************************************/

void Application::Init() {
    Application::SetUserSettings(3.0f, 8.4f, 1.0f);

    Application::StatusFlag::errorUVLO = Application::UVLO(Application::limitUVLO);
    if (Application::StatusFlag::errorUVLO) {
        Hrpwm::SetDuty(Hrpwm::Channel::boost, 0);
        Hrpwm::SetDuty(Hrpwm::Channel::buck, 0);
        Hrpwm::DriverControl(Hrpwm::Channel::boost, Hrpwm::Status::enable);
        Hrpwm::DriverControl(Hrpwm::Channel::buck, Hrpwm::Status::enable);
        Led::On(Led::TypeSignal::status);
    }

    Application::StartApplicationTimer();
}

void Application::SetUserSettings (float uvlo, float referenceVoltage, float referenceCurrent) {
    Application::limitUVLO = uvlo;
    Application::referenceOutputVoltage = referenceVoltage;
    Application::referenceOutputCurrent = referenceCurrent;
}

void Application::StartApplicationTimer() {
    RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;     

    TIM3->PSC = 36-1;
    TIM3->ARR = 100;
    TIM3->DIER |= TIM_DIER_UIE;
    TIM3->CR1  |= TIM_CR1_CEN;

    NVIC_EnableIRQ(TIM3_IRQn);
}

bool Application::UVLO (float reference) {
    float voltage = 0.0f;
    while (voltage < reference) {
        voltage = Feedback::GetInputVoltage();
    }
    return true;
}

/********************************************************************************
 * Application
 ********************************************************************************/

void sTim3::handler (void) {
    TIM3->SR &= ~TIM_SR_UIF;

    float inputVoltage = Feedback::GetInputVoltage();
    if (inputVoltage < 6.0f) { Application::dutyBoost = 15000; }
    if ((inputVoltage >= 6.0f) && (inputVoltage < 12.0f)) { Application::dutyBoost = 18000; }
    if (inputVoltage >= 12.0f) { Application::dutyBoost = 20000; }
    Hrpwm::SetDuty(Hrpwm::Channel::boost, Application::dutyBoost);

    float result = 0.0f;

    float outputVoltage = Feedback::GetOutputVoltage();
    float outputCurrent = Feedback::GetOutputCurrent();

    if (outputVoltage < (Application::referenceOutputVoltage - 0.2f)) {
        pidCurrentMode
            .SetReference(Application::referenceOutputCurrent)
            .SetSaturation(-29800, 29800)
            .SetFeedback(outputCurrent, 0.001)
            .SetCoefficient(10,0,0,0,0)
            .Compute();
        result = pidCurrentMode.Get();
    } 
    
    if ((outputCurrent < 0.05f) || (outputVoltage >= (Application::referenceOutputVoltage - 0.2f))) {
        pidVoltageMode
            .SetReference(Application::referenceOutputVoltage)
            .SetSaturation(-29800, 29800)
            .SetFeedback(outputVoltage, 0.001)
            .SetCoefficient(10,0,0,0,0)
            .Compute();
        result = pidVoltageMode.Get();
    }

    Application::dutyBuck += result;
    Hrpwm::SetDuty(Hrpwm::Channel::buck, Application::dutyBuck); 
}