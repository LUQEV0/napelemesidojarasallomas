# Napelemes IoT Időjárás Állomás

Ez egy energiatakarékos, napelemmel táplált időjárás-állomás projekt, amely egy ESP32 mikrokontrollerre és egy BME280 szenzorra épül.

## 🛠️ Felhasznált Hardver elemek
* **Mikrokontroller:** DFRobot FireBeetle ESP32 (IoT fejlesztői kártya alacsony fogyasztással)
* **Szenzor:** BME280 (Hőmérséklet, páratartalom és légnyomás mérésére)
* **Töltésvezérlő:** DFRobot Solar Lipo Charger (Napelemes akkutöltő)
* **Akkumulátor:** 3.7V Polymer Lithium Ion (LiPo) akkumulátor
* **Energiaforrás:** 2x 6V 1W Napelem (párhuzamosan kötve)

## 📐 Működési elv
A rendszer az akkumulátorból kapja a tápellátást, amelyet a napelemek folyamatosan töltenek a töltésvezérlőn keresztül. Az energiatakarékosság maximalizálása érdekében az ESP32 **Deep Sleep** (mély alvás) módot használ. 

1. Az ESP32 felébred.
2. Inicializálja az I2C buszon keresztül a BME280 szenzort.
3. Beolvassa a környezeti adatokat (Hőmérséklet, Páratartalom, Légnyomás).
4. Elküldi az adatokat (vagy kiírja a soros portra).
5. Újra alvó állapotba kerül 15 percre, ahol a fogyasztása minimális (mikroamper nagyságrendű).

## 🚀 Szoftveres követelmények
A kód futtatásához az Arduino IDE-ben telepíteni kell az alábbi könyvtárakat:
* `Adafruit BME280 Library`
* `Adafruit Unified Sensor`
