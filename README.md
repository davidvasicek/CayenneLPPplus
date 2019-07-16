# LPP+

Cayenne LPP+ (Low Power Packet) je rozšíření dosavadního [Cayenne LPP](https://mydevices.com/cayenne/docs/lora/#lora-how-lorawan-works) vlastní senzory. Formát kódování umožňuje jednoduchý a pohodlnný způsob odesílání dat v sítích LoRaWAN s co nejmenší velikosti užitečného zatížení.

Tento projekt vytváří nový dekodér takového zatížení a rozšířenou knihovnu [CayenneLPP](https://github.com/TheThingsNetwork/arduino-device-lib) pro kódování tohoto užitečného zatížení.

### Změny ve verzích

v1.0.0 - 16.7.2019 - přidána rozšířená GPS (HEX = 89)
                   - přidán senzor vlhkosti půdy (HEX = 87)

### Rozšířená tabulka

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
  <td>135</td>
  <td>87</td>
  <td>1</td>
  <td>0.5 % Unsigned</td>
</tr>
</tbody>
</table>


### decoder

Dekoder LPP packetu je kód v jazyce Javascript a je implementovatelný do [The Things Network](https://www.thethingsnetwork.org/) (TTN). Jeho úkolem je dekódování užitečného zatížení zakodováného knihovnou CayenneLPP.

##### implementace dekodéru

1. Ve vaší aplikaci přejděte do Payload Formats
2. v Payload Format zvolte Custom
3. zvolte decoder
4. vložte kód dekodéru [Decoder.js](https://github.com/davidvasicek/LPPplus/blob/master/decoder.js)
5. do Payload vložte testovací posloupnost bytů (např. 01 89 07 9A 87 02 C5 68 00 67 84 05 00 00 5D 2D 8D 0B)
6. stiskněte Test
7. sledujte výsledek

![alt text](https://github.com/davidvasicek/LPPplus/blob/master/img/decoder_implement.png "Logo Title Text 1")

| Tables                        | Cool  |
| Tables        | Are           | Cool  |
| ------------- |:-------------:| -----:|
| col 3 is      | right-aligned | $1600 |
| col 2 is      | centered      |   $12 |
| zebra stripes | are neat      |    $1 |


