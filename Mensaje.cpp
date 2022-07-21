//jesus elias soto
//20/11/2019


#include "Mensaje.hpp"
#include <iostream>
#include <sstream>
#include <iomanip>


std::string Mensaje::toString() const{
  
  std::ostringstream oss; 

  oss << "[(" << size() << ") ";
   
  for(unsigned i = 0; i < size(); i++){
    oss << std::hex << std::setw(2) << std::setfill('0') 
        << (int)at(i) << " ";
    
  }
  oss << "]";
  
  return oss.str();

}

Mensaje Mensaje::crc16(Mensaje mensaje, int len) const{
#define POLY 0xA001
  int i;
  unsigned int crc = 0xFFFF;


  for(int ba = 0; ba < len; ba++) {
    crc ^= mensaje[ba];
    for(i = 0; i < 8; i++) {
      if(crc & 0x0001) {
        crc = (crc >> 1) ^ POLY;
      } else {
        crc >>= 1;
      }
    }
  }
  Mensaje crcOrdenado;
  crcOrdenado.push_back(crc & 0xff);
  crcOrdenado.push_back(crc >> 8);
  return crcOrdenado;
}


Mensaje Mensaje::crc16(Mensaje mensaje)  const{
  return crc16(mensaje, mensaje.size());
}

bool Mensaje::crcOK()const{
  
  Mensaje crcCalculado = crc16( (*this) );

  
  if ( (crcCalculado[0] != 0) )
  return false;
  if ( (crcCalculado[1] != 0) )
  return false;
  
  return true;
  
}

void Mensaje::aniadeCRC(){
  
  Mensaje crcCalculado = crc16( (*this) );
  
  (*this).push_back (crcCalculado[0]);
  (*this).push_back (crcCalculado[1]);
  
}

uint16_t Mensaje::getWordAt(unsigned ind) const{
  
  uint16_t resultado = at(ind);
  resultado = resultado << 8;
  
  uint16_t menosSignificativo = at (ind + 1);
  
  resultado = resultado | menosSignificativo;
  
  return resultado;
 
}

void Mensaje::setWordAt(unsigned ind, uint16_t dato) {
  
  uint8_t parteInferior = (dato & 0xFF);
  uint8_t parteSUperior = (dato >> 8);
  
  at(ind) = parteSUperior;
  at (ind + 1) = parteInferior;
  
}

void Mensaje::pushWord_back(uint16_t dato) {
  
  uint8_t parteInferior = (dato & 0xFF);
  uint8_t parteSuperior = (dato >> 8);
  
  (*this).push_back (parteSuperior);
  (*this).push_back (parteInferior);
  
}

uint8_t Mensaje::getId(){
  
  uint8_t id= (*this)[0];
  
  return id;
}

uint8_t Mensaje::getFuncion(){
  
  uint8_t funcion = (*this)[1];
  
  return funcion;
  
}

uint16_t Mensaje::getOffset(){
  
  uint16_t offset = getWordAt (2);
  
  return offset;
  
}
  
uint16_t Mensaje::getNumPosiciones(){
  
  uint16_t numPos = getWordAt (4);
  
  return numPos;
  
}

std::ostream& operator << (std::ostream& os, const Mensaje& men){
  
  os << men.toString();
  
  return os;
}









