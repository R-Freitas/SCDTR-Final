#include <Wire.h>


#define N_ELEMENTS 4

int address=0;
int n=0;
int j=0;
int found_elements=1;
int elements[N_ELEMENTS];
byte control=1;
unsigned long t_0,diff;


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
    Wire.write('E');
    Wire.write(address);        
    control = Wire.endTransmission(true);
  }

  t_0=micros();
  while(diff<500)
  {
    diff=micros()-t_0;
  }
  

  Wire.beginTransmission(0);
  Wire.write('F');        
  control = Wire.endTransmission(true);
  

}

void loop() {

    
  Serial.println("Os enderecos sao:");
  for (j=0;j<found_elements;j++){
    Serial.println(elements[j]);
  }
  
  delay(500);
  
}

void receiveEvent(int numBytes){
  char indic = Wire.read();
  switch(indic){
    case 'E':
      elements[found_elements]=Wire.read();
      found_elements++;
      t_0=micros();
      break;
      
    case 'F':
      Serial.println("Setup ended");
      digitalWrite(LED_BUILTIN,HIGH);
      break;
  }

  
  
}



