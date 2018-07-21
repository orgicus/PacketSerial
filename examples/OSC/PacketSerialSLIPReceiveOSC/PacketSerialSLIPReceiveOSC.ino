// requires OSC library:  https://github.com/CNMAT/OSC 
#include <OSCBundle.h>
#include <PacketSerial.h>

//packet serial instance for SLIP with a 4K buffer
PacketSerial_<SLIP, SLIP::END, 4096> serial;

void setup() {

  // setup built-in LED as output
  pinMode(LED_BUILTIN, OUTPUT);
  
  // init serial:
  //  1. set a packet handler: a function to be called when a full SLIP packet is received
  serial.setPacketHandler(&onPacket);
  //  2. set the baud rate, same as Arduino's usual Serial
  serial.begin(115200);
  
}

void loop() {
  
  // update serial continuously so it can keep track of bytes / SLIP packets as data comes in
  serial.update();
  
}

// called whenever a complete SLIP packet has arrived and has been decoded
void onPacket(const uint8_t* buffer, size_t size)
{
  
  // fill an OSC message with what SLIP decoded bytes come in.
  // note that you use an OSCBundle in a very similar fashion to group multiple messages in one go
  OSCMessage message;
  message.fill(buffer, size);
  
  // if the message can be successfully parsed from the bytes:
  if (!message.hasError()){
    
  // trigger the onLED function when an OSC message with the /led address comes in
    message.dispatch("/led", onLED);
    
  }
  
}

// automatically called when a /led message arrives
void onLED(OSCMessage& msg)
{
  // check if we do have an integer as the first argument
  if (msg.isInt(0))
  {
    
    // if the int argument is a 1, turn the LED on
    if(msg.getInt(0) == 1){
    
      digitalWrite(LED_BUILTIN, HIGH);
    
    // otherwise turn it off  
    }else{
      
      digitalWrite(LED_BUILTIN, LOW);
      
    }
    
  }
  
}
