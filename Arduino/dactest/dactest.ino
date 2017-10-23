/* DAC test, egy DAC, van csak(lehetne több is,csak itthon kevés a kábel hozzá).
Soros portról beolvassa az értékeket(4 int -et) érték1,érték2,érték3,érték4 formában.
Ezekból az elsőt kirakja a dac-ra, +mind a 4-et visszadoba soros porton hogy lássék.
*/
// inslude the SPI library:
#include <SPI.h>
// Chip select aurduino portok define-ja
#define CS1 2
#define CS2 3
#define CS3 4
#define CS4 5
void DACset(int value,int CS)
{
  int data;
  data=28672+16*value;  // Config biteket állító offset + felszorzás, mert az utolsó 4 bit dont care 
  SPI.beginTransaction(SPISettings(20000000, MSBFIRST, SPI_MODE0));  
  digitalWrite(CS,LOW); //CS enable
  SPI.transfer16(data); //SPI küldés
  digitalWrite(CS,HIGH); //CS disable
  SPI.endTransaction();
}
int j[4]; //belső változó a kiadandó értéknek


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(CS1,OUTPUT);
   digitalWrite(CS1,HIGH);
  SPI.begin();
}

void loop() {
  // Serial olvasás
while (Serial.available()) 
  {
    for(int i=0;i<4;i++) j[i]=Serial.parseInt();
  }
  for(int i=0;i<4;i++) if(j[i]>1000) j[i]=1000;
DACset((j[0]/1000)*255,CS1); //DAC állítása
//Soros portra visszaírás
for(int i=0;i<4;i++)
  {
    Serial.print(j[i]);
    Serial.println();
  }
delay(1000);//hogy legyen idő olvasni
}
