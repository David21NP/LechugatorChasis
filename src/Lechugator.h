#ifndef LECHUGATOR_H
#define LECHUGATOR_H


// #if !( defined(STM32F0) || defined(STM32F1) || defined(STM32F2) || defined(STM32F3)  ||defined(STM32F4) || defined(STM32F7) || \
//        defined(STM32L0) || defined(STM32L1) || defined(STM32L4) || defined(STM32H7)  ||defined(STM32G0) || defined(STM32G4) || \
//        defined(STM32WB) || defined(STM32MP1) || defined(STM32L5) )
//   #error This code is designed to run on STM32F/L/H/G/WB/MP1 platform! Please check your Tools->Board setting.
// #endif


#include <Arduino.h>
#include <EEPROM.h>

#include "./util/ILechugator.h"

// class Ramps
// {
// private:
// public:
//     Ramps_1_4::Eeprom m_eeprom;
//     Ramps_1_4::I2C_Ramps m_i2c;
//     Ramps_1_4::Power_Output m_pwo;
//     Ramps_1_4::Servos_Ramps m_servos;
//     Ramps_1_4::Steppers m_steppers;
//     Ramps_1_4::Thermistors m_thermistors;
//     Ramps();
//     ~Ramps();
//     void begin();
// };

#endif