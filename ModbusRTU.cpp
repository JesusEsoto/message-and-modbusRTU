//jesus elias soto
//20/11/2019


#include "ModbusRTU.hpp"
#include "Mensaje.hpp"
#include <iostream>


ModbusRTU::ModbusRTU (uint8_t id) : _DO(15), _AO(21) {
  
  _id = id;
  
  for (unsigned i = 0; i < _DO.size(); i++){
    if (i < 8){
      _DO[i] = true;
      
    } else{
      _DO[i] = false;
    
    } 
  }
  _AO[0] = 3;
  for (unsigned i = 0; i < _AO.size(); i++){
    _AO[i] = (i * 2) + 3;
    
  }
  
  

}

Mensaje ModbusRTU::peticion (Mensaje recibido) {
  
  Mensaje respuesta;
  
  std::cerr << "Recibido mensaje" << recibido.toString() << std::endl;
  
  
  uint8_t id = recibido[0];
  uint8_t funcion = recibido[1];


  std::cerr << "El mensaje es para " << (int)id << " y la funcion es "
      << (int)funcion << std::endl;
  
  switch (funcion){

  case 3:
    respuesta = atiende03 (recibido);
    break;
    
  case 1:
    respuesta = atiende01 (recibido);
    break;
    
  case 5:
    respuesta = atiende05 (recibido);
    break;
    

    
  case 6:
    respuesta = atiende06 (recibido);
    break;
    
  /*case 16:
    respuesta = atiende16 (recibido);
    break;*/
    
    default:
    
    std:: cerr << "FUncion no implementada." << std::endl;
  }
  
  return respuesta;
}

Mensaje ModbusRTU::atiende03 (Mensaje recibido) {
  
  Mensaje respuesta;
  
  respuesta.push_back (recibido[0]);
  respuesta.push_back (recibido[1]);
  
  unsigned offset = recibido.getWordAt(2);
  unsigned numPos = recibido.getWordAt(4);
  
  respuesta.push_back( (2*numPos) );
 
  for (unsigned i = offset; i < (offset + numPos); i++){
    unsigned j = i - 49;
    
    std::cerr << "Accediendo AO[" << j << "]: " << _AO[j] << std::endl;
    respuesta.pushWord_back(_AO[j]);
    
  }
  
  respuesta.aniadeCRC();
  
  return respuesta;
}

Mensaje ModbusRTU::atiende01(Mensaje recibido) {
  
  Mensaje respuesta;
    
  std::cerr << "Entramos en método atiende01 con mensaje " 
      << recibido.toString() << std::endl;
  
  respuesta.push_back(recibido[0]); //id
  respuesta.push_back(recibido[1]); //funcion
  
  unsigned offset = recibido.getWordAt(2); //offset
  unsigned numPos = recibido.getWordAt(4); //numero de posiciones
  
  unsigned numBytes = ((numPos - 1)/8) + 1;
  
  respuesta.push_back (numBytes);
  
  unsigned posBit = 0;
  uint8_t dato = 0;
  for (unsigned p = offset; p < (offset + numPos); p++){
    std::cerr << "Accediendo DO[" << p << "]: " << _DO[p] << std::endl;
    if (_DO[p]){
      dato = dato | (1 << posBit);
    }
    posBit++;
    if(posBit == 8){ 
      respuesta.push_back(dato);
      dato = 0;
      posBit = 0;
      
    }
    
  }
  
  if (posBit < 8 && posBit != 0){
    respuesta.push_back(dato);
    
  }
  
  respuesta.aniadeCRC();
  
  return respuesta;

}

Mensaje ModbusRTU::atiende05 (Mensaje recibido) {
  
  std::cerr << "Entramos en método atiende05 con mensaje " 
      << recibido.toString() << std::endl;
  
  unsigned offset = recibido.getWordAt(2);
  
  
  if ( (recibido[4] == 0xFF) && (recibido[5] == 0x00) ){
    _DO[offset] = true;
    std::cerr << "Ponemos a 1 la DO[" << offset << "]: " << _DO[offset] 
        << std::endl;
    
  } else if ( (recibido[4] == 0x00) && (recibido[5] == 0x00) ){
    _DO[offset] = false;
    std::cerr << "Ponemos a 0 la DO[" << offset << "]: " << _DO[offset] 
        << std::endl;
  }
  
  
  return recibido;
  
}

Mensaje ModbusRTU::atiende06 (Mensaje recibido) {
  
  
  std::cerr << "Entramos en método atiende06 con mensaje " 
      << recibido.toString() << std::endl;
  
  unsigned offset = recibido.getWordAt(2);
  unsigned dato = recibido.getWordAt(4);
  
 
  _AO[offset] = dato;
  std::cerr << "Escribimos la AO[" << offset << "]: " << _AO[offset] 
      << std::endl;
  

  return recibido;
}




