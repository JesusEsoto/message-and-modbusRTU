
//jesus elias soto
//20/11/2019

#ifndef _MENSAJE_
#define _MENSAJE_

#include <vector>
#include <string>

class Mensaje : public  std::vector<uint8_t> {


public:
  // usamos todos los constructores de la clase madre
  using std::vector<uint8_t>::vector;

  std::string toString() const;

  // devuelve si el CRC es correcto
  bool crcOK() const;

  // Añade el CRC al mensaje
  void aniadeCRC() ;

  // Devuelve doble byte en indice
  uint16_t getWordAt(unsigned ind) const;

  // colocar doble byte en indice
  void setWordAt(unsigned ind, uint16_t dato) ;

  // añade word al final del mensaje
  void pushWord_back(uint16_t dato) ; 
  
  uint8_t getId();
  
  uint8_t getFuncion();
  
  uint16_t getOffset();
  
  uint16_t getNumPosiciones();
  
  
private:

  Mensaje crc16 (Mensaje mensaje, int len) const;
  Mensaje crc16 (Mensaje mensaje) const;
  
};

std::ostream& operator << (std::ostream& os, const Mensaje& men);


#endif
