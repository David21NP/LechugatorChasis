#ifndef LECHUGATOR_SERIAL_H
#define LECHUGATOR_SERIAL_H

#include <Arduino.h>
#include <vector>

// #define SerialLogger Serial

namespace Lechugator
{
  class SerialObj
  {
  private:
    unsigned long baud = 0;

  public:
    HardwareSerial serialHardware = Serial;
    SerialObj(const HardwareSerial &_serialHardware, const unsigned long &_baud);
    SerialObj(const HardwareSerial &_serialHardware);
    SerialObj(const unsigned long &_baud);
    SerialObj();
    void begin();
  };

  class SerialLogger
  {
  private:
    std::vector<SerialObj> serialObjs;

  public:
    SerialLogger();
    ~SerialLogger();
    SerialLogger(const unsigned long &_baud);

    void initLoggers();

    void addLogger(const HardwareSerial &_serialHardware, const unsigned long &_baud);
    void addLogger(const HardwareSerial &_serialHardware);
    void addLogger(const unsigned long &_baud);
    void addLogger();

    template <typename T>
    void print(const T &x)
    {
      for (SerialObj &serialObj : serialObjs)
      {
        serialObj.serialHardware.print(x);
      }
    }

    template <typename T>
    void println(const T &x)
    {
      for (SerialObj &serialObj : serialObjs)
      {
        serialObj.serialHardware.println(x);
      }
    }
  };

} // namespace Lechugator

#endif
