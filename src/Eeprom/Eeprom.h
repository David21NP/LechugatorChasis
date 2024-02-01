#ifndef EEPROM_H
#define EEPROM_H

#include <Arduino.h>
#include <EEPROM.h>

namespace Lechugator {
    class Eeprom
    {
    private:
        int length;
    public:
        Eeprom();
        ~Eeprom();

        void WriteMem(int, byte);
        byte ReadMem(int);
        void ClearMem();

        void WriteFloat(int, float);
        float ReadFloat(int);
    };
}


#endif