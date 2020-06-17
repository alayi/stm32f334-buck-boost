
/********************************************************************************
 * Include 
 ********************************************************************************/

#include "Led.h"

/********************************************************************************
 * Class Led
 * 
 * LED0     -   BLUE    -   PB15    -   Status signal
 * LED1     -   RED     -   PB14    -   Over current protection
 * LED2     -   RED     -   PB13    -   Over voltage protection
 * LED3     -   RED     -   PB12    -   Over temperature protection
 * 
 ********************************************************************************/

void Led::Init (void) {
    Gpio::Init<12,13,14,15>(GPIOB, Gpio::Mode::output, Gpio::Type::PP); 
};

void Led::On (TypeSignal led) {
    switch (led) {
        case Led::TypeSignal::status:
            Gpio::Set<15>(GPIOB);
            break;
        case Led::TypeSignal::overCurrentProtection:
            Gpio::Set<14>(GPIOB);
            break;
        case Led::TypeSignal::overVoltageProtection:
            Gpio::Set<13>(GPIOB);
            break;
        case Led::TypeSignal::overTemperatureProtection:
            Gpio::Set<12>(GPIOB);
            break;
        default:
            Gpio::Reset<12>(GPIOB);
            Gpio::Reset<13>(GPIOB);
            Gpio::Reset<14>(GPIOB);
            Gpio::Reset<15>(GPIOB);
            break;
    }
};

void Led::Off (TypeSignal led) {
    switch (led) {
        case Led::TypeSignal::status:
            Gpio::Reset<15>(GPIOB);
            break;
        case Led::TypeSignal::overCurrentProtection:
            Gpio::Reset<14>(GPIOB);
            break;
        case Led::TypeSignal::overVoltageProtection:
            Gpio::Reset<13>(GPIOB);
            break;
        case Led::TypeSignal::overTemperatureProtection:
            Gpio::Reset<12>(GPIOB);
            break;
        default:
            Gpio::Reset<12>(GPIOB);
            Gpio::Reset<13>(GPIOB);
            Gpio::Reset<14>(GPIOB);
            Gpio::Reset<15>(GPIOB);
            break;
    }
};

void Led::Toggle (TypeSignal led) {
    switch (led) {
        case Led::TypeSignal::status:
            Gpio::Toggle<15>(GPIOB);
            break;
        case Led::TypeSignal::overCurrentProtection:
            Gpio::Toggle<14>(GPIOB);
            break;
        case Led::TypeSignal::overVoltageProtection:
            Gpio::Toggle<13>(GPIOB);
            break;
        case Led::TypeSignal::overTemperatureProtection:
            Gpio::Toggle<12>(GPIOB);
            break;
        default:
            Gpio::Reset<12>(GPIOB);
            Gpio::Reset<13>(GPIOB);
            Gpio::Reset<14>(GPIOB);
            Gpio::Reset<15>(GPIOB);
            break;
    }
};