# LPP+

LPP+ je rozšířené kódování užitečného zatížení dosavadního Cayenne Low Power Packet (LPP) o vlastní senzory. Projekt obsahuje nový dekoder LPP packetu (JS) a nové rozšířené knihovny pro zakodování obsahu do LPP formátu. 

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
```
function Decoder(bytes, port) {




    function getDecimalNumberFromBytes(signed, size) {

       var value = 0; // inicializace proměnné value, do které se bude ukládat výsledek převaděného HEX na DECimal
       
       for(var i = size-1; i >= 0; i--){
              
            value += bytes[bytesCounter++] << i*8; // bitový posun dle velikosti 
        }
       
       if(signed){ // jestlže je unsigned

        if(value>= Math.pow(2, size*8-1)){
          
            var hex = value.toString(16);
                        
              if(hex.length % 2 !== 0 ) {
                            hex = "0" + hex;
                        }
                        var num = parseInt(hex, 16);
                        var maxVal = Math.pow(2, hex.length / 2 * 8);
                        if (num > maxVal / 2 - 1) {
value = num - maxVal;
                        }
            }           
        }
        
        return value;
    }

    function addToPayload(name, resolution, value) {
      
      var fixed = resolution.toString().split(".")[1];
      if (fixed == undefined){
        
        fixed = 0;
        
      }

        payload[name] = (value * resolution).toFixed(fixed.length);

     }

    var bytesCounter = 0;
    var payload = {};

    /**
     * @reference https://github.com/myDevicesIoT/cayenne-docs/blob/master/docs/LORA.md
     * 
     * Type                 IPSO    LPP     Hex     Data Size   Data Resolution per bit
     *  Digital Input       3200    0       0       1           1
     *  Digital Output      3201    1       1       1           1
     *  Analog Input        3202    2       2       2           0.01 Signed
     *  Analog Output       3203    3       3       2           0.01 Signed
     *  Illuminance Sensor  3301    101     65      2           1 Lux Unsigned MSB
     *  Presence Sensor     3302    102     66      1           1
     *  Temperature Sensor  3303    103     67      2           0.1 °C Signed MSB
     *  Humidity Sensor     3304    104     68      1           0.5 % Unsigned
     *  Accelerometer       3313    113     71      6           0.001 G Signed MSB per axis
     *  Barometer           3315    115     73      2           0.1 hPa Unsigned MSB
     *  Gyrometer           3334    134     86      6           0.01 °/s Signed MSB per axis
     *  GPS Location        3336    136     88      9           Latitude  : 0.0001 ° Signed MSB
     *                                                          Longitude : 0.0001 ° Signed MSB
     *                                                          Altitude  : 0.01 meter Signed MSB
     */
    
    var sensor_types = { 
    0  : {'size': 1, 'name': 'Digital Input'      , 'signed': false, 'resolution': 1, 'decimal_point': 0},
    1  : {'size': 1, 'name': 'Digital Output'     , 'signed': false, 'resolution': 1, 'decimal_point': 0},
    2  : {'size': 2, 'name': 'Analog Input'       , 'signed': true , 'resolution': 0.01, 'decimal_point': 0},
    3  : {'size': 2, 'name': 'Analog Output'      , 'signed': true , 'resolution': 0.01, 'decimal_point': 0},
    101: {'size': 2, 'name': 'Illuminance Sensor' , 'signed': false, 'resolution': 1, 'decimal_point': 0},
    102: {'size': 1, 'name': 'Presence Sensor'    , 'signed': false, 'resolution': 1, 'decimal_point': 0},
    103: {'size': 2, 'name': 'Temperature Sensor' , 'signed': true , 'resolution': 0.1, 'decimal_point': 0},
    104: {'size': 1, 'name': 'Humidity Sensor'    , 'signed': false, 'resolution': 0.5, 'decimal_point': 0},
    113: {'size': 6, 'name': 'Accelerometer'      , 'signed': true , 'resolution': 0.001, 'decimal_point': 0},
    115: {'size': 2, 'name': 'Barometer'          , 'signed': false, 'resolution': 0.1, 'decimal_point': 0},
    134: {'size': 6, 'name': 'Gyrometer'          , 'signed': true , 'resolution': 0.01, 'decimal_point': 0},
    136: {'size': 9, 'name': 'GPS Location' , 'signed': false, 'resolution': [0.0001,0.0001,0.01],  'decimal_point': [4,4,0.2]}
    };
    
    
    
    while(bytesCounter < bytes.length){
      
      var channel = bytes[bytesCounter++];
      var sensor_code = bytes[bytesCounter++];
      
      var signed = sensor_types[sensor_code].signed;
      var size = sensor_types[sensor_code].size;
      var name = sensor_types[sensor_code].name + "_" + channel;
      var resolution = sensor_types[sensor_code].resolution;
    
      switch (sensor_code) {
        case 0  : addToPayload(name, resolution, getDecimalNumberFromBytes(signed, size)); break; // Digital Input
        case 1  : addToPayload(name, resolution, getDecimalNumberFromBytes(signed, size)); break;// Digital Output
        case 2  : addToPayload(name, resolution, getDecimalNumberFromBytes(signed, size)); break; // Analog Input
        case 3  : addToPayload(name, resolution, getDecimalNumberFromBytes(signed, size)); break; // Analog Output
        case 101: addToPayload(name, resolution, getDecimalNumberFromBytes(signed, size)); break;  // Illuminance Sensor
        case 102: addToPayload(name, resolution, getDecimalNumberFromBytes(signed, size)); break; // Presence Sensor
        case 103: addToPayload(name, resolution, getDecimalNumberFromBytes(signed, size)); break; // Temperature Sensor
        case 104: addToPayload(name, resolution, getDecimalNumberFromBytes(signed, size)); break; // Humidity Sensor
        case 113: addToPayload(name, resolution, getDecimalNumberFromBytes(signed, size)); break; // Accelerometer
        case 115: addToPayload(name, resolution, getDecimalNumberFromBytes(signed, size)); break; // Barometer
        case 134:  // Gyrometer
          payload["sensorcode"] = 134;
          break;
        case 136:  // GPS Location

        
        name = sensor_types[sensor_code].name + "_" + channel + ".latitude";
        resolution = sensor_types[sensor_code].resolution[0];
        addToPayload(name, resolution, getDecimalNumberFromBytes(signed, 3));

        name = sensor_types[sensor_code].name + "_" + channel + ".longitude";
      resolution = sensor_types[sensor_code].resolution[1];
      addToPayload(name, resolution, getDecimalNumberFromBytes(signed, 3));
        
        name = sensor_types[sensor_code].name + "_" + channel + ".altitude";
      resolution = sensor_types[sensor_code].resolution[2];
      addToPayload(name, resolution, getDecimalNumberFromBytes(signed, 3));

        
       
            break;
        }
        
        
    
    //bytesCounter = 4;
    
    }
      
    
      
        var result = ""; for (var i = 0; i < bytes.length; i++) { result += String.fromCharCode(parseInt(bytes[i])); } 
        return payload; 
      
      }
      
 ```     
