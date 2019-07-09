# LPP++

LPP++ je rozšířené kódování užitečného zatížení dosavadního Cayenne Low Power Packet (LPP) o vlastní senzory. Projekt obsahuje nový dekoder LPP packetu (JS) a nové rozšířené knihovny pro zakodování obsahu do LPP formátu. 

### Změny

v1.0 - 9.7.2019 - přidán senzor vlhkosti půdy (HEX = 87)

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
  <td>Soil Moisture</td>
  <td>???</td>
  <td>135</td>
  <td>87</td>
  <td>1</td>
  <td>0.5 % Unsigned</td>
</tr>
</tbody>
</table>
