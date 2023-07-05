#include <Wire.h>
#include "SparkFun_SGP30_Arduino_Library.h"
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <Arduino_GFX_Library.h>


#define DHT_PIN 12
#define DHT_TYPE DHT22

int step_count = 0;
int step_curr  = 170;
int step_delay = 10;

DHT dht(DHT_PIN, DHT_TYPE);
SGP30 sgp;

Arduino_DataBus *bus = create_default_Arduino_DataBus();
Arduino_GFX *gfx = new Arduino_GC9A01(bus, 7 /* RST */, 0 /* rotation */, true /* IPS */);

// Define pin connections
const int stepPin = 3;
const int dirPin = 2;


int up_pos_x  = 70;
int up_pos_y  = 70;
int do_pos_x  = 70;
int do_pos_y  = 140;

void setup() {
  Serial.begin(9600);
  dht.begin();
  Wire.begin();
  while (!Serial);
  Serial.println("SGP30 test");

  if (!sgp.begin()) {
    Serial.println("SGP30 sensor not found :(");
    while (1);
  }

  sgp.initAirQuality();

  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);

  gfx->begin();
  gfx->setTextSize(3);
  gfx->setTextColor(WHITE, BLUE);
  delay(5000);
  gfx->fillScreen(BLUE);
}

void loop() {
  // Messung der Luftqualität mit dem SGP30-Sensor
  sgp.measureAirQuality();

  // Lesen der gemessenen Werte vom SGP30-Sensor
  uint16_t co2 = sgp.CO2;
  uint16_t tvoc = sgp.TVOC;

  step_count = map(co2, 100, 1000, 0, 500);



  if (step_curr < step_count){
    step_curr += 1;
    digitalWrite(dirPin, HIGH);
    digitalWrite(stepPin, HIGH);
    delay(step_delay);
    digitalWrite(stepPin, LOW); 
    delay(step_delay);
  } else if (step_curr > step_count){
    step_curr -= 1;
    digitalWrite(dirPin, LOW);
    digitalWrite(stepPin, HIGH);
    delay(step_delay);
    digitalWrite(stepPin, LOW); 
    delay(step_delay);
  }


  // if (step_curr <= step_count){
  //   digitalWrite(dirPin, HIGH);
  //   for (;step_curr <= step_count;step_curr += 1){
  //     digitalWrite(stepPin, HIGH);
  //     delay(step_delay);
  //     digitalWrite(stepPin, LOW); 
  //     delay(step_delay);
  //   }
  // } else if (step_curr >= step_count){
  //   digitalWrite(dirPin, LOW);
  //   for (;step_curr >= step_count;step_curr -= 1){
  //     digitalWrite(stepPin, HIGH);
  //     delay(step_delay);
  //     digitalWrite(stepPin, LOW); 
  //     delay(step_delay);
  //   }
  // }


  Serial.println(step_count);
  Serial.println(step_curr);

  // Lesen der Temperatur- und Luftfeuchtigkeitswerte vom DHT22-Sensor
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();

  // Ausgabe der Werte auf dem seriellen Monitor
  // Serial.print("Temperature: ");
  // Serial.print(temperature);
  // Serial.print(" °C\tHumidity: ");
  // Serial.print(humidity);
  // Serial.print(" %\t");
  Serial.print("eCO2: ");
  Serial.println(co2);
  // Serial.print(" ppm\tTVOC: ");
  // Serial.print(tvoc);
  // Serial.println(" ppb");



  gfx->setCursor(up_pos_x, up_pos_y);
  gfx->print(temperature, 2);
  gfx->print(" C");
  gfx->setCursor(do_pos_x, do_pos_y);
  gfx->print(humidity, 2);
  gfx->print(" %");


}
