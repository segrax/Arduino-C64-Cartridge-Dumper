/**
 * Commodore 64 Cartridge Dumper
 *   
 * (c) 2014 Robert Crossfield
 **/

int pinsAddress[16] = {52, 50, 48, 46, 44, 42, 40, 38, 36, 34, 32, 30, 28, 26, 24, 22};
int pinsData[8]     = {23, 25, 27, 29, 31, 33, 35, 37};

String commandInput = "";         // a string to hold incoming data
boolean commandComplete = false;

void setup() {
  Serial.begin(9600); 
  
  for( int pin = 0; pin < 16; ++pin )
    pinMode(pinsAddress[pin], OUTPUT);
    
  for( int pin = 0; pin < 8; ++pin ) {
    pinMode(pinsData[pin], INPUT);
  }

  commandInput.reserve(200);
}

/**
 * Handle serial port event
 **/
void serialEvent() {
  while (Serial.available()) {
    char inChar = (char)Serial.read();

    commandInput += inChar;
    if (inChar == '\n')
      commandComplete = true;
  }
}

void loop() {
  
  if( commandComplete == true ) {
    commandComplete = false;
    
    if( commandInput == "DUMP\n" )
        dump();
        
    commandInput = "";
  }
}

void dump() {
   Serial.println("dumping");
   
   for( int address = 0; address < 0x2000; ++address ) 
     Serial.write(readAddress( address ));

}

/**
 * Read a byte from an address
 *
 * @param int pAddress Address to read a byte from
 *
 * @return char
 **/
unsigned char readAddress( int pAddress ) {
  
  setAddress( pAddress );
  
  return getData();
}

/**
 * Read the data pins
 *
 * @return char
 **/
unsigned char getData() {
  unsigned char data = 0;
  
  for( int pin = 0; pin < 8; ++pin ) {
    unsigned char pinData = digitalRead( pinsData[pin] );
    if( pinData == HIGH )
      data |= (1 << pin);
  }
  
  return data;
}

/**
 * Set the address pins
 *
 * @param int pAddress
 **/
void setAddress( int pAddress ) {
    
  for( int pin = 0; pin < 16; ++pin ) {
    if( pAddress & 1 )
      digitalWrite( pinsAddress[pin], HIGH );
    else
      digitalWrite( pinsAddress[pin], LOW );
      
      pAddress >>= 1;
  }
  
  //delay(2);
}

