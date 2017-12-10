#include <Wire.h>

#define N_ELEMENTS 2

int address=0;
int n=0;
int j=0;
int found_elements=1;
int elements[N_ELEMENTS];
int setup_control=0;
int m=0, k=0;
byte control=1;


void setup() {
  Serial.begin(9600);
  Serial.println("Begin Setup");
  pinMode(LED_BUILTIN, OUTPUT);
  
  digitalWrite(LED_BUILTIN,HIGH);
  delay(500);
  digitalWrite(LED_BUILTIN,LOW);

  pinMode(2,INPUT_PULLUP);
  pinMode(3,INPUT_PULLUP);
  pinMode(4,INPUT_PULLUP);
  pinMode(5,INPUT_PULLUP);
  pinMode(6,INPUT_PULLUP);
  pinMode(7,INPUT_PULLUP);
  pinMode(8,INPUT_PULLUP);
  
  // Various initialization processes needed (such as reading adress pins, enabling general call, and using builtin led for control purposes)
  
  for (int i=2; i <= 8; i++){
    bitWrite(address, n, !digitalRead(i));
    n++;
  } //reading the address coded in digital ports from 2 to 8
  
  elements[0]=address;  //Saving own address
  Wire.begin(address);  //Initialize I2C comunication
  bitSet(TWAR, TWGCE);
  Wire.onReceive(receiveEvent);

  delay(100);
  
  while (control != 0){
    Wire.beginTransmission(0);
    Wire.write(address);        
    control = Wire.endTransmission(true);
  }
    
  Serial.println("Setup ended");

}

void loop() {

    
  Serial.println("Os enderecos sao:");
  for (j=0;j<found_elements;j++){
    Serial.println(elements[j]);
  }
  
  delay(500);
  
}

void receiveEvent(int numBytes){
  elements[found_elements]=Wire.read();
  found_elements++;
  if (found_elements == N_ELEMENTS){
    digitalWrite(LED_BUILTIN,HIGH);
    setup_control = 1;  
  }

  
  
}



