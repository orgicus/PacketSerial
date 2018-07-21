// requires OSC library:  https://github.com/CNMAT/OSC 
#include <OSCBundle.h>
#include <PacketSerial.h>

//END-OF-TRANSMISSION (byte) to mark SLIP packet transmission begin and end
#define EOT 0300

//packet serial instance for SLIP with a 4K buffer
PacketSerial_<SLIP, SLIP::END, 4096> serial;

void setup() {
  
  // init serial: set the baud rate, same as Arduino's usual Serial
  serial.begin(115200);
  
}

void loop() {
  
  // create a message
  OSCMessage msg("/alive");

  // send a message
  // step 1: SLIP serial begin packet (1 byte)
  serial.send(EOT,1);
  // step 2: write the OSC bytes
  msg.send(*serial.getStream());
  // step 3: SLIP serial end packet (1 byte)
  serial.send(EOT,1);
  
  // wait a sec.
  delay(1000);
  
}
