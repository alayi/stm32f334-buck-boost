/********************************************************************************
 * Include 
 ********************************************************************************/

#include "Application.h"

/********************************************************************************
 * Variables
 ********************************************************************************/

bool Application::StatusFlag::errorUVLO = 0;

/********************************************************************************
 * Class
 ********************************************************************************/

void Application::Init() {
    Application::StatusFlag::errorUVLO = Application::UVLO(5.0);
    if (Application::StatusFlag::errorUVLO) {Led::On(Led::TypeSignal::status);}

    Application::StartApplicationTimer();
}

void Application::StartApplicationTimer() {
    RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;     

	TIM3->PSC = 36000-1;					
	TIM3->ARR = 1000;			
	TIM3->DIER |= TIM_DIER_UIE;				
	TIM3->CR1  |= TIM_CR1_CEN;	

    NVIC_EnableIRQ(TIM3_IRQn);			
}

bool Application::UVLO (float reference) {
    float voltage = 0.0f;
    while (voltage < reference) {
        voltage = Feedback::inputVoltage();
    }
    return true;
}

/********************************************************************************
 * Application
 ********************************************************************************/

void sTim3::handler (void) {
    TIM3->SR &= ~TIM_SR_UIF;
    Led::Toggle(Led::TypeSignal::overTemperatureProtection);

    Hrpwm::DriverControl(Hrpwm::Channel::boost, Hrpwm::Status::enable);
    Hrpwm::DriverControl(Hrpwm::Channel::buck, Hrpwm::Status::enable);

    Hrpwm::SetDuty(Hrpwm::Channel::buck, 15000);   
    Hrpwm::SetDuty(Hrpwm::Channel::boost, 29800); 
}