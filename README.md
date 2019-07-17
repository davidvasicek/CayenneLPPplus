# CayenneLPP+

Cayenne LPP+ (Low Power Packet) je rozšíření dosavadního [Cayenne LPP](https://mydevices.com/cayenne/docs/lora/#lora-how-lorawan-works) vlastní senzory. Formát kódování umožňuje jednoduchý a pohodlnný způsob odesílání dat v sítích LoRaWAN s co nejmenší velikosti užitečného zatížení.

Tento projekt vytváří nový dekodér takového zatížení a rozšířenou knihovnu [CayenneLPP](https://github.com/TheThingsNetwork/arduino-device-lib) pro kódování tohoto užitečného zatížení.

#### Změny ve verzích

  v1.0.0 - 16.7.2019 - přidána rozšířená GPS (HEX = 89)
                   - přidán senzor vlhkosti půdy (HEX = 87)

#### Rozšířená tabulka

<table style="width: 100%;">
<tbody>
  <tr>
    <td style="font-size: 15px; padding: 10px;"><b>Type</b></td>
    <td style="font-size: 15px; padding: 10px;"><b>IPSO</b></td>
    <td style="font-size: 15px; padding: 10px;"><b>LPP</b></td>
    <td style="font-size: 15px; padding: 10px;"><b>Hex</b></td>
    <td style="font-size: 15px; padding: 10px;"><b>Data Size</b></td>
    <td style="font-size: 15px; padding: 10px;"><b>Data Resolution per bit</b></td>
  </tr>
  <tr>
    <td>Digital Input</td>
    <td>3200</td>
    <td>0</td>
    <td>0</td>
    <td>1</td>
    <td>1</td>
  </tr>
  <tr>
    <td>Digital Output</td>
    <td>3201</td>
    <td>1</td>
    <td>1</td>
    <td>1</td>
    <td>1</td>
  </tr>
  <tr>
    <td>Analog Input</td>
    <td>3202</td>
    <td>2</td>
    <td>2</td>
    <td>2</td>
    <td>0.01 Signed</td>
  </tr>
  <tr>
    <td>Analog Output</td>
    <td>3203</td>
    <td>3</td>
    <td>3</td>
    <td>2</td>
    <td>0.01 Signed</td>
  </tr>
  <tr>
    <td>Illuminance Sensor</td>
    <td>3301</td>
    <td>101</td>
    <td>65</td>
    <td>2</td>
    <td>1 Lux Unsigned MSB</td>
  </tr>
  <tr>
    <td>Presence Sensor</td>
    <td>3302</td>
    <td>102</td>
    <td>66</td>
    <td>1</td>
    <td>1</td>
  </tr>
  <tr>
    <td>Temperature Sensor</td>
    <td>3303</td>
    <td>103</td>
    <td>67</td>
    <td>2</td>
    <td>0.1 °C Signed MSB</td>
  </tr>
  <tr>
    <td>Humidity Sensor</td>
    <td>3304</td>
    <td>104</td>
    <td>68</td>
    <td>1</td>
    <td>0.5 % Unsigned</td>
  </tr>
  <tr>
    <td>Accelerometer</td>
    <td>3313</td>
    <td>113</td>
    <td>71</td>
    <td>6</td>
    <td>0.001 G Signed MSB per axis</td>
  </tr>
  <tr>
    <td>Barometer</td>
    <td>3315</td>
    <td>115</td>
    <td>73</td>
    <td>2</td>
    <td>0.1 hPa Unsigned MSB</td>
  </tr>
  <tr>
  <tr>
    <td>Unix Time</td>
    <td>???</td>
    <td>133</td>
    <td>85</td>
    <td>4</td>
    <td>1 sec Unsigned</td>
  </tr>
  <tr>
    <td>Gyrometer</td>
    <td>3334</td>
    <td>134</td>
    <td>86</td>
    <td>6</td>
    <td>0.01 °/s Signed MSB per axis</td>
  </tr>
  <tr>
    <td rowspan="3">GPS Location</td>
    <td rowspan="3">3336</td>
    <td rowspan="3">136</td>
    <td rowspan="3">88</td>
    <td rowspan="3">9</td>
    <td>Latitude : 0.0001 ° Signed MSB</td>
    </tr>
    <tr>
    <td>Longitude : 0.0001 ° Signed MSB</td>
    </tr>
    <tr>
    <td>Altitude : 0.01 meter Signed MSB</td>
  </tr>
  
  <tr>
    <td rowspan="6">GPS Location (extended)</td>
    <td rowspan="6">???</td>
    <td rowspan="6">137</td>
    <td rowspan="6">89</td>
    <td rowspan="6">18</td>
    <td>Latitude : 0.0001 ° Signed MSB (3Byte)</td>
    </tr>
    <tr>
      <td>Longitude : 0.0001 ° Signed MSB (3Byte)</td>
    </tr>
    <tr>
      <td>Altitude : 0.01 meter Signed MSB (3Byte)</td>
    </tr>
    <tr>
      <td>Satellites : 1 satelite Unsigned (1Byte)</td>
    </tr>
    <tr>
      <td>Speed : 0.01 meter Unsigned (2Byte)</td>
    </tr>
    <tr>
      <td>TimeStamp : 1 ms Unsigned (6Byte)</td>
  </tr>
  <tr>
    <td>Soil Moisture</td>
    <td>???</td>
    <td>138</td>
    <td>8A</td>
    <td>1</td>
    <td>0.5 % Unsigned</td>
  </tr>
  <tr>
    <td>Dust Density</td>
    <td>???</td>
    <td>139</td>
    <td>8B</td>
    <td>2</td>
    <td>0.1 ug/cm3 signed MSB</td>
  </tr>
</tbody>
</table>


### Decoder

Dekoder LPP packetu je kód v jazyce Javascript a je implementovatelný do [The Things Network](https://www.thethingsnetwork.org/) (TTN). Jeho úkolem je dekódování užitečného zatížení zakodováného knihovnou CayenneLPP.

##### implementace dekodéru

1. Ve vaší aplikaci přejděte do Payload Formats.
2. V Payload Format zvolte Custom.
3. Zvolte decoder.
4. Vložte kód dekodéru [Decoder.js](https://github.com/davidvasicek/LPPplus/blob/master/decoder.js).
5. Do Payload vložte testovací posloupnost bytů (např. 01 89 07 9A 87 02 C5 68 00 67 84 05 00 00 5D 2D 8D 0B).
6. Stiskněte Test.
7. Sledujte výsledek.

![alt text](https://github.com/davidvasicek/LPPplus/blob/master/img/decoder_implement.png "Logo Title Text 1")

### Coder (knihovna CayenneLPP+)

Knihovna LPP+ je rozšíření knihovny CayenneLPP od The Things Network a implementuje do této knihovny nové senzory. Knihovna je psaná v jazyce C. 

Při použití knihovny doporučujeme zkontrolovat aktuální verzi knihovny, která se stále vyvíjí.

##### metody knihovny

###### Metody add...
```c
uint8_t addDigitalInput(uint8_t channel, uint8_t value);
uint8_t addDigitalOutput(uint8_t channel, uint8_t value);
uint8_t addAnalogInput(uint8_t channel, float value);
uint8_t addAnalogOutput(uint8_t channel, float value);
uint8_t addLuminosity(uint8_t channel, uint16_t lux);
uint8_t addPresence(uint8_t channel, uint8_t value);
uint8_t addTemperature(uint8_t channel, float celsius);
uint8_t addRelativeHumidity(uint8_t channel, float rh);
uint8_t addAccelerometer(uint8_t channel, float x, float y, float z);
uint8_t addBarometricPressure(uint8_t channel, float hpa);
uint8_t addGyrometer(uint8_t channel, float x, float y, float z);
uint8_t addGPS(uint8_t channel, float latitude, float longitude, float meters);
uint8_t addGPSplus(uint8_t channel, float latitude, float longitude, float meters, int satellites, float speed, long timestamp);
uint8_t addSoilMoisture(uint8_t channel, float sm);
uint8_t addDustDensity(uint8_t channel, float dd);
```

###### Metoda convertToEpochtime
Metoda vrací hodnotu epochtime/unixtime (tj. převedené aktuální datum a čas na počet sekund od 1.1.1970 00:00:00 hod)

##### implementace knihovny

1. Stáhněte knihovnu kliknutím na Clone or download -> Download ZIP.
2. Přejděte do prostředí Arduino IDE a zvolte Projekt -> Přidat knihovnu -> Přidat .ZIP knihovnu... -> CayenneLPPplus-master.zip
3. Použíjte knihovnu

    ```c
      #include <CayenneLPP+.h>
      CayenneLPP lpp(80);
      
      uint32_t TimeStamp = lpp.convertToEpochtime(year, month, day, hour, minute, second);

      lpp.reset();
      lpp.addGPSplus(1, Latitude, Longitude, Altitude, Satelittess, Speed, TimeStamp);

      LMIC_setTxData2(1,lpp.getBuffer(), lpp.getSize(), 0);  
    ```
