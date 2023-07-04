#include <Wire.h>
#include "SparkFun_SGP30_Arduino_Library.h"
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <Arduino_GFX_Library.h>
#include <AccelStepper.h>

#define DHT_PIN 12
#define DHT_TYPE DHT22

DHT dht(DHT_PIN, DHT_TYPE);
SGP30 sgp;

Arduino_DataBus *bus = create_default_Arduino_DataBus();
Arduino_GFX *gfx = new Arduino_GC9A01(bus, 7 /* RST */, 0 /* rotation */, true /* IPS */);

// Define pin connections
const int stepPin = 3;
const int dirPin = 2;

AccelStepper stepper(stepPin, dirPin);

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

  delay(200);

  // Lesen der Temperatur- und Luftfeuchtigkeitswerte vom DHT22-Sensor
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();

  // Ausgabe der Werte auf dem seriellen Monitor
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.print(" °C\tHumidity: ");
  Serial.print(humidity);
  Serial.print(" %\t");
  Serial.print("eCO2: ");
  Serial.print(co2);
  Serial.print(" ppm\tTVOC: ");
  Serial.print(tvoc);
  Serial.println(" ppb");

  // Motorsteuerung basierend auf dem CO2-Wert
  if (co2 > 401) {
    stepper.moveTo(0); // Position für "hoher" CO2-Wert
    } else if (co2 < 400) {
    stepper.moveTo(1000); // Position für "niedriger" CO2-Wert
  }

  // Bewegung des Stepper Motors
  stepper.run();

  gfx->setCursor(up_pos_x, up_pos_y);
  gfx->print(temperature, 2);
  gfx->print(" C");
  gfx->setCursor(do_pos_x, do_pos_y);
  gfx->print(humidity, 2);
  gfx->print(" %");

  delay(500);
}
