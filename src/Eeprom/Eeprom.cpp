#include "Eeprom.h"

namespace Lechugator {
    Eeprom::Eeprom(/* args */)
    {
        length = EEPROM.length();
    }

    Eeprom::~Eeprom()
    {
    }

    void Eeprom::ClearMem()
    {
        for (int i = 0; i < length; i++)
        {
            EEPROM.write(i, 0);
        }
    }

    void Eeprom::WriteMem(int pos, byte data)
    {
        if (pos < length)
            EEPROM.write(pos, data);
    }

    byte Eeprom::ReadMem(int pos)
    {
        if (pos < length)
        {
            return EEPROM.read(pos);
        }
        return 0;
    }
    void Eeprom::WriteFloat(int pos, float data)
    {
        if ((pos + sizeof(float)) < length)
            EEPROM.put(pos, data);
    }

    float Eeprom::ReadFloat(int pos)
    {
        float toReturn = -1;
        if ((pos + sizeof(float)) < length)
        {
            return EEPROM.get(pos, toReturn);
        }
        return toReturn;
    }
    
}