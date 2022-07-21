//jesus elias soto
//20/11/2019

#include "Mensaje.hpp"


#ifndef _MODBUSRTU_
#define _MODBUSRTU_


class ModbusRTU {
  
  
public:

  ModbusRTU (uint8_t id);
  
  Mensaje peticion (Mensaje recibido);
  
private:

  uint8_t _id;
  
  std::vector<bool> _DO;
  std::vector<uint16_t> _AO;
  
public:

  Mensaje atiende03 (Mensaje recibido);
  
  Mensaje atiende01 (Mensaje recibido);
  
  Mensaje atiende05 (Mensaje recibido);
  
  Mensaje atiende06 (Mensaje recibido);
  
  /*respuesta = atiende16 (recibido);*/
  
};


#endif
