
/********************************************************************************
 * Include 
 ********************************************************************************/

#include "Adc.h"

float Adc::inputVoltage [Adc::sizeBuffer];
float Adc::inputCurrent [Adc::sizeBuffer];
float Adc::outputVoltage [Adc::sizeBuffer];
float Adc::outputCurrent [Adc::sizeBuffer];

uint16_t Adc::step = 0;

/********************************************************************************
 * Class ADC
 ********************************************************************************/

void Adc::Init() {
    RCC->AHBENR |= RCC_AHBENR_ADC12EN;

    Adc::GpioInit();
    Adc::InitTimerEvent();
    Adc::StartCallibrationAdc();

    ADC1->JSQR |= 0x1030817B;               // Lenght = 4, Trigger = event 14, Type trigger = rising edge, Channel = IN1, IN2, IN3 and IN4

    ADC1->IER |= ADC_IER_JEOSIE;            // Interrupt enable
    NVIC_EnableIRQ(ADC1_2_IRQn);            // Enable interrupt ADC1 and ADC2

    ADC1->CR |= ADC_CR_ADEN;                // Enable ADC1
    while(!(ADC1->ISR & ADC_ISR_ADRDY));    // Wait ready ADC1

    ADC1->CR |= ADC_CR_JADSTART;            // Enable injector conversion
}

void Adc::GpioInit() {
    Gpio::Init<14>(GPIOB, Gpio::Mode::output, Gpio::Type::PP);
    Gpio::Init<0,1,2,3,5>(GPIOA, Gpio::Mode::input);
}

void Adc::StartCallibrationAdc() {
    ADC1->CR &= ~ADC_CR_ADVREGEN;
    ADC1->CR |= ADC_CR_ADVREGEN_0;      // Enable Vref
    ADC1->CR &= ~ADC_CR_ADCALDIF;

    ADC1->CR |= ADC_CR_ADCAL;           // Start calibration
    while (ADC1->CR & ADC_CR_ADCAL);    // Wait end calibration
}

void Adc::InitTimerEvent() {
    RCC->APB1ENR |= RCC_APB1ENR_TIM6EN;
    TIM6->PSC = 36000-1;
    TIM6->ARR = 1000;
    TIM6->CR2 |= TIM_CR2_MMS_1;         // Enable generation TRGO for ADC
    TIM6->CR1  |= TIM_CR1_CEN;
}

/********************************************************************************
 * ADC handler
 ********************************************************************************/

void sAdc::handler (void) {
    ADC1->ISR |= ADC_ISR_JEOS;
    Gpio::Toggle<15>(GPIOA);

    Adc::inputVoltage[Adc::step++] = ADC1->JDR1;
    Adc::inputCurrent[Adc::step++] = ADC1->JDR2;
    Adc::outputCurrent[Adc::step++] = ADC1->JDR3;
    Adc::outputVoltage[Adc::step++] = ADC1->JDR4;

    if (Adc::step >= 50) { Adc::step = 0; } 
}