/********************************************************************************
 * Include 
 ********************************************************************************/

#include "Application.h"

/********************************************************************************
 * Variables
 ********************************************************************************/

uint16_t Application::dutyResult = 0;

float Application::referenceOutputVoltage = 0.0f;
float Application::referenceOutputCurrent = 0.0f;

PidController pidVoltageMode;
PidController pidCurrentMode;

/********************************************************************************
 * Class
 ********************************************************************************/

void Application::Init() {
    Application::SetUserSettings(8.0f, 1.0f);

    Hrpwm::SetDuty(Hrpwm::Channel::boost, 30000);
    Hrpwm::SetDuty(Hrpwm::Channel::buck, 0);

    Hrpwm::DriverControl(Hrpwm::Channel::boost, Hrpwm::Status::enable);
    Hrpwm::DriverControl(Hrpwm::Channel::buck, Hrpwm::Status::enable);

    Application::StartHighSpeedProcessing();
    Application::StartLowSpeedProcessing();
}

void Application::SetUserSettings (float referenceVoltage, float referenceCurrent) {
    Application::referenceOutputVoltage = referenceVoltage;
    Application::referenceOutputCurrent = referenceCurrent;
}

void Application::StartHighSpeedProcessing() {
    RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;     

    TIM3->PSC = 36-1;
    TIM3->ARR = 200;
    TIM3->DIER |= TIM_DIER_UIE;
    TIM3->CR1  |= TIM_CR1_CEN;

    NVIC_EnableIRQ(TIM3_IRQn);
}

void Application::StartLowSpeedProcessing() {
    RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;     

    TIM2->PSC = 36000-1;
    TIM2->ARR = 1000;
    TIM2->DIER |= TIM_DIER_UIE;
    TIM2->CR1  |= TIM_CR1_CEN;

    NVIC_EnableIRQ(TIM2_IRQn);
}

/********************************************************************************
 * High speed processing #1
 ********************************************************************************/

void sTim3::handler (void) {
    TIM3->SR &= ~TIM_SR_UIF;

    float result = 0.0f;

    float inputVoltage = Feedback::GetInputVoltage();
    float inputCurrent = Feedback::GetInputCurrent();
    float outputVoltage = Feedback::GetOutputVoltage();
    float outputCurrent = Feedback::GetOutputCurrent();

    // Boost mode
    if (inputVoltage < (Application::referenceOutputVoltage - 1.0f)) {
        Hrpwm::SetDuty(Hrpwm::Channel::buck, 27000);

        pidVoltageMode
            .SetReference(Application::referenceOutputVoltage)
            .SetSaturation(-29800, 29800)
            .SetFeedback(outputVoltage, 0.002)
            .SetCoefficient(20,0,0,0,0)
            .Compute();
        result = pidVoltageMode.Get();

        Application::dutyResult += result;
        Hrpwm::SetDuty(Hrpwm::Channel::boost, Application::dutyResult);
    }

    // Buck-boost mode
    if ((inputVoltage >= (Application::referenceOutputVoltage - 1.0f)) && ((inputVoltage <= (Application::referenceOutputVoltage + 1.0f)))) {
        Hrpwm::SetDuty(Hrpwm::Channel::boost, 9000);

        pidVoltageMode
            .SetReference(Application::referenceOutputVoltage)
            .SetSaturation(-29800, 29800)
            .SetFeedback(outputVoltage, 0.002)
            .SetCoefficient(20,0,0,0,0)
            .Compute();
        result = pidVoltageMode.Get();

        Application::dutyResult += result;
        Hrpwm::SetDuty(Hrpwm::Channel::buck, Application::dutyResult);
    }

    // Buck mode
    if (inputVoltage > (Application::referenceOutputVoltage + 1.0f)) {
        Hrpwm::SetDuty(Hrpwm::Channel::boost, 6000);

        pidVoltageMode
            .SetReference(Application::referenceOutputVoltage)
            .SetSaturation(-29800, 29800)
            .SetFeedback(outputVoltage, 0.002)
            .SetCoefficient(20,0,0,0,0)
            .Compute();
        result = pidVoltageMode.Get();

        Application::dutyResult += result;
        Hrpwm::SetDuty(Hrpwm::Channel::buck, Application::dutyResult);
    }

/*
        pidCurrentMode
            .SetReference(Application::referenceOutputCurrent)
            .SetSaturation(-29800, 29800)
            .SetFeedback(outputCurrent, 0.001)
            .SetCoefficient(15,0,0,0,0)
            .Compute();
        result = pidCurrentMode.Get();
*/

}

/********************************************************************************
 * Low speed processing #1
 ********************************************************************************/

void sTim2::handler (void) {
    TIM2->SR &= ~TIM_SR_UIF;
}