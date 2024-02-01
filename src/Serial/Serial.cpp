#include "Serial.h"

// #define SerialLogger Serial

namespace Lechugator
{

  SerialObj::SerialObj(const HardwareSerial &_serialHardware, const unsigned long &_baud) : serialHardware(_serialHardware),
                                                                                            baud(_baud)
  {
  }
  SerialObj::SerialObj(const HardwareSerial &_serialHardware) : SerialObj(_serialHardware, 115200)
  {
  }
  SerialObj::SerialObj(const unsigned long &_baud) : SerialObj(Serial, _baud)
  {
  }
  SerialObj::SerialObj() : SerialObj(115200)
  {
  }
  void SerialObj::begin()
  {
    serialHardware.begin(baud);
  }

  SerialLogger::SerialLogger()
  {
    serialObjs.push_back(SerialObj());
  }
  SerialLogger::SerialLogger(const unsigned long &_baud)
  {
    serialObjs.push_back(SerialObj(_baud));
  }

  void SerialLogger::addLogger(const HardwareSerial &_serialHardware, const unsigned long &_baud)
  {
    serialObjs.push_back(SerialObj(_serialHardware, _baud));
  }
  void SerialLogger::addLogger(const HardwareSerial &_serialHardware)
  {
    serialObjs.push_back(SerialObj(_serialHardware));
  }
  void SerialLogger::addLogger(const unsigned long &_baud)
  {
    serialObjs.push_back(SerialObj(_baud));
  }
  void SerialLogger::addLogger()
  {
    serialObjs.push_back(SerialObj());
  }

  void SerialLogger::initLoggers()
  {
    for (SerialObj &serialObj : serialObjs)
    {
      serialObj.begin();
    }
  }

  SerialLogger::~SerialLogger()
  {
    serialObjs.clear();
  }

} // namespace Lechugator