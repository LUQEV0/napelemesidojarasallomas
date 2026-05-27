#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

// BME280 szenzor példányosítása I2C kommunikációhoz
Adafruit_BME280 bme; 

// Időintervallum a mérések között mikroszekundumban (pl. 15 perc = 900 másodperc)
#define TIME_TO_SLEEP  900 
#define S_TO_uS_FACTOR 1000000ULL  // Konverziós faktor másodpercből mikroszekundumba

void setup() {
  Serial.begin(115200);
  while(!Serial); // Várakozás a soros portra
  
  Serial.println(F("--- Napelemes Időjárás Állomás ---"));

  // BME280 szenzor inicializálása (0x76 vagy 0x77 I2C címen)
  if (!bme.begin(0x76)) {
    Serial.println(F("Nem található érvényes BME280 szenzor, ellenőrizd a bekötést!"));
    while (1);
  }

  // Adatok beolvasása és kiíratása
  readWeatherData();

  // ESP32 konfigurálása az időzített ébredésre
  esp_sleep_enable_timer_wakeup(TIME_TO_SLEEP * S_TO_uS_FACTOR);
  
  Serial.println("Mérés kész. ESP32 mély alvásba merül...");
  Serial.flush(); 
  
  // Alvás indítása az energiatakarékosság jegyében
  esp_deep_sleep_start();
}

void loop() {
  // A Deep Sleep miatt a loop() sosem fut le, az ébredés után a setup() indul újra.
}

void readWeatherData() {
  float temp = bme.readTemperature();
  float humidity = bme.readHumidity();
  float pressure = bme.readPressure() / 100.0F; // Pa-ból hPa-ba váltás

  Serial.print(F("Hőmérséklet: "));
  Serial.print(temp);
  Serial.println(F(" *C"));

  Serial.print(F("Páratartalom: "));
  Serial.print(humidity);
  Serial.println(F(" %"));

  Serial.print(F("Légnyomás: "));
  Serial.print(pressure);
  Serial.println(F(" hPa"));
  Serial.println(F("--------------------------------"));
}
