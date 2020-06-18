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
float temp = 0.0f;
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
        temp = Feedback::inputVoltage();
        if (temp > 9) { Led::On(Led::TypeSignal::overTemperatureProtection); }
        if (temp < 9) { Led::Off(Led::TypeSignal::overTemperatureProtection); }
    }
}