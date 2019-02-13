#include "Adafruit_VL53L0X.h"
#include "Wire.h"
extern "C" {
  #include "utility/twi.h"
  }

Adafruit_VL53L0X lox1 = Adafruit_VL53L0X();
Adafruit_VL53L0X lox2 = Adafruit_VL53L0X();
Adafruit_VL53L0X lox3 = Adafruit_VL53L0X();
uint16_t toInt;

#define TCAADDR 0x70

#define LOX_ADDR 0x29



#define lox1_dio 31
#define lox2_dio 33
#define lox3_dio 35

VL53L0X_RangingMeasurementData_t measure1;
VL53L0X_RangingMeasurementData_t measure2;
VL53L0X_RangingMeasurementData_t measure3;

void init6498()
{
  //INIT LOXIUS UNO
  tcaselect(0);
  if(!lox1.begin(LOX_ADDR)) {
    Serial.println(F("Failed to boot lox1"));
    while(1);
  }
  Serial.println("lox1: ONLINE");
  delay(1000);
  
  //INIT LOXIUS DOS
  tcaselect(2);
  if(!lox2.begin(LOX_ADDR)) {
    Serial.println(F("Failed to boot lox2"));
    while(1);
  }
  Serial.println("lox2: ONLINE");
  delay(1000);
  
  //INIT LOXIUS TRES
  tcaselect(1);
  if(!lox3.begin(LOX_ADDR)) {
    Serial.println(F("Failed to boot lox3"));
    while(1);
  }
  Serial.println("lox3: ONLINE");
  delay(100);
}

void setup() {


  // wait until serial port opens for native USB devices
  while (! Serial) {
    delay(1);
  }
  Wire.begin();
  Serial.begin(115200);
  Serial.println("Serial Ready");
  Serial.println("Starting...");
  init6498();
}

void tcaselect(uint8_t i) {
  if (i > 7) return;
  Wire.beginTransmission(TCAADDR);
  Wire.write(1 << i);
  Wire.endTransmission();  
}

void loop() {
  // put your main code here, to run repeatedly:

  lox1.rangingTest(&measure1, false);
  if (measure1.RangeStatus != 4) {  // phase failures have incorrect data
    Serial.print("Distance (mm 1): "); 
    Serial.println(measure1.RangeMilliMeter);
  } else {
    Serial.println(" out of range ");
  }
  if(measure1.RangeMilliMeter <= 100)
  {
      digitalWrite(lox1_dio, HIGH);
  }
  else if(measure1.RangeMilliMeter > 100 )
  {
      digitalWrite(lox1_dio, LOW);
  }

  lox2.rangingTest(&measure2, false);
  if (measure2.RangeStatus != 4) {  // phase failures have incorrect data
    Serial.print("Distance (mm 2): "); 
    Serial.println(measure2.RangeMilliMeter);
  } else {
    Serial.println(" out of range ");
  }
  if(measure2.RangeMilliMeter <= 100)
  {
      digitalWrite(lox2_dio, HIGH);
      Serial.println("HIGH");
  }
  else if(measure2.RangeMilliMeter > 100)
  {
      digitalWrite(lox2_dio, LOW);
      Serial.println("LOW");
  }
  lox3.rangingTest(&measure3, false);
  if (measure3.RangeStatus != 4) {  // phase failures have incorrect data
    Serial.print("Distance (mm 3): "); 
    Serial.println(measure3.RangeMilliMeter);
  } else {
    Serial.println(" out of range ");
  }
  if(measure3.RangeMilliMeter <= 100)
  {
      digitalWrite(lox3_dio, HIGH);
      Serial.println("HIGH");
  }
  else if(measure3.RangeMilliMeter > 100)
  {
      digitalWrite(lox3_dio, LOW);
      Serial.println("LOW");
  }
  //read_triple_sensors();
    
  delay(100);
  
}
