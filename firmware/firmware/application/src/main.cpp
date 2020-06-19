/********************************************************************************
 * project     DC/DC buck-boost converter with digital control on the STM32F334 *
 *                                                                              *
 * file        main.cpp                                                         *
 * author      Ilya Galkin                                                      *
 * date        17.06.2020                                                       *
 * brief       Main program body                                                *
 *                                                                              *
 ********************************************************************************/

/********************************************************************************
 * Include 
 ********************************************************************************/

#include "main.h"
float tempInVoltage = 0.0f;
float tempInCurrent = 0.0f;
float tempOutVoltage = 0.0f;
float tempOutCurrent = 0.0f;
/********************************************************************************
 * Main program body
 ********************************************************************************/

int main (void) {

    Periphery::Init();

    Led::On(Led::TypeSignal::status);
    Led::Off(Led::TypeSignal::overCurrentProtection);
    Led::Off(Led::TypeSignal::overVoltageProtection);
    Led::Off(Led::TypeSignal::overTemperatureProtection);

    Hrpwm::DriverControl(Hrpwm::Channel::boost, Hrpwm::Status::enable);
    Hrpwm::DriverControl(Hrpwm::Channel::buck, Hrpwm::Status::enable);

    Hrpwm::SetDuty(Hrpwm::Channel::buck, 15000);   
    Hrpwm::SetDuty(Hrpwm::Channel::boost, 29800); 

    while(1) {
        tempInVoltage = Feedback::inputVoltage();
        tempInCurrent = Feedback::inputCurrent();
        tempOutVoltage = Feedback::outputVoltage();
        tempOutCurrent = Feedback::outputCurrent();
    }
}