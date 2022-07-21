# message-and-modbusRTU
C++ project that allows for a message to be sent via ModbusRTU

A ModbusRTU server is implemented. The message represents a Modbus message as a byte sequence, which inherits from ```std::vector<uint8_t>``` and adds some methods:
- ```std::string toString()``` returns the representation of the message, showing the number of bytes and the value of them in hexadecimal.
- ```bool crcOK()``` indicates if the CRC is correct.
- ```void aniadeCRC()``` adds the CRC to the message.
- ```uint16_t getWordAt(unsigned ind)``` returns the dbyte starting from the ```ind``` position.
- ```void setWordAt(unsigned ind, uint16_t dato)``` places the dbyte starting from the ```ind``` position.
- ```void pushWord_back(uint16_t dato)``` adds a dbyte to the end of the message.
- the operator ```<<``` is overloaded so it can return through a ```std::ostream``` the same as 
```toString()```.

The ModbusRTU server has the following methods:
- ```ModbusRTU(uint8_t id)``` constructor where the device id is specified.
- ```Mensaje peticion(Mensaje recibido)``` recieves as parameter a Modbus/RTU petition message and returns the corresponding answer.
