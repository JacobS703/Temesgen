#include <EEPROM.h>
#include <Wire.h>

#define eeprom 0x50 // defines the base address of the EEPROM
#define b_pin_0 7
#define temp_pin_0 A0
#define temp_pin_1 A1
#define temp_pin_2 A2
#define temp_pin_3 A3

int temp_val_0;
int temp_val_1;
int temp_val_2;
int temp_val_3;
int address = 0;

byte value;
byte i;

void writeEEPROM(int deviceaddress, unsigned int eeaddress, byte data)
{
  Wire.beginTransmission(deviceaddress);
  Wire.write((int)(eeaddress >> 8));   // writes the MSB
  Wire.write((int)(eeaddress & 0xFF)); // writes the LSB
  Wire.write(data);
  Wire.endTransmission();
}
// defines the readEEPROM function
byte readEEPROM(int deviceaddress, unsigned int eeaddress)
{
  byte rdata = 0xFF;
  Wire.beginTransmission(deviceaddress);
  Wire.write((int)(eeaddress >> 8));   // writes the MSB
  Wire.write((int)(eeaddress & 0xFF)); // writes the LSB
  Wire.endTransmission();
  Wire.requestFrom(deviceaddress, 1);
  if (Wire.available())
    rdata = Wire.read();
  return rdata;
}

void Write_1()
{
  temp_val_0 = analogRead(temp_pin_0);
  temp_val_1 = analogRead(temp_pin_1);
  temp_val_2 = analogRead(temp_pin_2);
  temp_val_3 = analogRead(temp_pin_3);
  Serial.println(String(temp_val_0) + "," + String(temp_val_1) + "," + String(temp_val_2) + "," + String(temp_val_3));

  temp_val_0 = temp_val_0 - 600;
  temp_val_1 = temp_val_1 - 600;
  temp_val_2 = temp_val_2 - 600;
  temp_val_3 = temp_val_3 - 600;

  delay(60000 * 10);
  EEPROM.write(i, temp_val_0);
  EEPROM.write(i + 1, temp_val_1);
  EEPROM.write(i + 2, temp_val_2);
  EEPROM.write(i + 3, temp_val_3);
  i = i + 4;
}

void Read_1()
{
  value = EEPROM.read(address);
  value = value + 900;
  Serial.print(address);
  Serial.print("\t");
  Serial.print(value, DEC);
  Serial.println();
  address = address + 1;
  if (address == EEPROM.length())
  {
    address = 0;
  }
  delay(500);
}

void setup()
{
  pinMode(temp_pin_0, INPUT);
  pinMode(temp_pin_1, INPUT);
  pinMode(temp_pin_2, INPUT);
  pinMode(temp_pin_3, INPUT);
  pinMode(b_pin_0, INPUT);
  Serial.begin(9600);
  Wire.begin();             // creates a Wire object
  unsigned int address = 0; // first address of the EEPROM
}

void loop()
{
  // put your main code here, to run repeatedly:
  if (digitalRead(b_pin_0) == LOW)
  {
    Read_1();
  }
  else
  {
    Write_1();
  }
}
