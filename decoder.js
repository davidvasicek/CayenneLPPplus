function Decoder(bytes, port) {

  /** Funkce getDecimalNumberFromBytes slouží pro převod bytů payloadu na decimální číslo. 
   *  Parametry : dataSigned (bool) - signed int / unsigned int
   *              dataSize (int) - počet bytů payloadu - 2 byty (1byte kanál, 1byte typ senzoru)
   */ 
  function getDecimalNumberFromBytes(dataSigned, dataSize) {

    var decimalValue = 0; // inicializace proměnné decimalValue, do které se bude ukládat výsledky převaděného HEX na DECimal
       
    for(var i = dataSize - 1; i >= 0; i--){ // cyklus for projíždí jednotlivé byty a převádí je na decimální číslo.
              
      decimalValue += bytes[bytesPosition++] << i*8; // bitový posun dle velikosti 
    }

    if(dataSigned){ // Jestliže je signed, zjistí nejvyšší bit aby rozlišil, zda se jedná o kladnou či zápornou hodnotu

      if(decimalValue >= Math.pow(2, dataSize * 8 - 1)){
          
          var HEX = decimalValue.toString(16);
                        
          if(HEX.length % 2 !== 0 ) {
              
            HEX = "0" + HEX;
          }
                        
          var DEC = parseInt(HEX, 16);
          var maxBit = Math.pow(2, HEX.length / 2 * 8);
            
          if (DEC > maxBit / 2 - 1) {
            decimalValue = DEC - maxBit;
          }
        }           
      }
        
      return decimalValue;
  }
  
  /** Funkce addToPayload slouží pro přidání senzorových dat do JSON objektu. 
   *  Parametry : sensorName (String) - název senzoru / typ senzoru
   *              dataResolution (float) - rozlišení dat na 1 bit
   *              decimalValue (int) - hodnota v decimálním tvaru
   */ 
  function addToPayload(sensorName, dataResolution, decimalValue) {
    
    // Zjistí počet míst za desetinnou čárkou
    var fixed = dataResolution.toString().split(".")[1];
    if (fixed == undefined){
        
      fixed = 0;
    }
      payload[sensorName] = (decimalValue * dataResolution).toFixed(fixed.length);
  }

  var bytesPosition = 0; // Kurzor / ukazatel na pozici bytů v payloadu
  var payload = {}; // JSON objekt

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
    *  Unix Time           ????    133     85      4           1 s Unsigned
    *  Gyrometer           3334    134     86      6           0.01 °/s Signed MSB per axis
    *  GPS Location        3336    136     88      9           Latitude  : 0.0001 ° Signed MSB (3Byte)
    *                                                          Longitude : 0.0001 ° Signed MSB (3Byte)
    *                                                          Altitude  : 0.01 meter Signed MSB (3Byte)
    *  GPS Location        ????    137     89      16          Latitude  : 0.0001 ° Signed (3Byte)
    *                                                          Longitude : 0.0001 ° Signed (3Byte)
    *                                                          Altitude  : 0.01 meter Signed (3Byte)
    *                                                          Satellites : 1 satelite Unsigned (1Byte)
    *                                                          Speed : 0.01 meter Unsigned (2Byte)
    *                                                          TimeStamp : 1 ms Unsigned (4Byte)
    */
  
  // LPP tabulka v JSON tvaru
  var sensorTypes = { 
    0  : {'size': 1  , 'name': 'Digital Input'      , 'signed': false , 'resolution': 1                               },
    1  : {'size': 1  , 'name': 'Digital Output'     , 'signed': false , 'resolution': 1                               },
    2  : {'size': 2  , 'name': 'Analog Input'       , 'signed': true  , 'resolution': 0.01                            },
    3  : {'size': 2  , 'name': 'Analog Output'      , 'signed': true  , 'resolution': 0.01                            },
    101: {'size': 2  , 'name': 'Illuminance Sensor' , 'signed': false , 'resolution': 1                               },
    102: {'size': 1  , 'name': 'Presence Sensor'    , 'signed': false , 'resolution': 1                               },
    103: {'size': 2  , 'name': 'Temperature Sensor' , 'signed': true  , 'resolution': 0.1                             },
    104: {'size': 1  , 'name': 'Humidity Sensor'    , 'signed': false , 'resolution': 0.5                             },
    113: {'size': 6  , 'name': 'Accelerometer'      , 'signed': true  , 'resolution': 0.001                           },
    115: {'size': 2  , 'name': 'Barometer'          , 'signed': false , 'resolution': 0.1                             },
    133: {'size': 4  , 'name': 'UnixTime'           , 'signed': true  , 'resolution': 0.01                            },
    134: {'size': 6  , 'name': 'Gyrometer'          , 'signed': true  , 'resolution': 0.01                            },
    136: {'size': 9  , 'name': 'gps'       , 'signed': false , 'resolution': [0.0001, 0.0001, 0.01]          },
    137: {'size': 16 , 'name': 'gps'       , 'signed': false , 'resolution': [0.0001, 0.0001, 0.01, 1, 1, 1] }
  };
  
  // Bude pročítat celý payload byte po byte, dokud nenarazí na konec 
  while(bytesPosition < bytes.length){
      
    var sensorChannel = bytes[bytesPosition++];
    var sensorCode = bytes[bytesPosition++];
      
    var sensorName = sensorTypes[sensorCode].name + "_" + sensorChannel;
    var dataSigned = sensorTypes[sensorCode].signed;
    var dataSize = sensorTypes[sensorCode].size;
    var dataResolution = sensorTypes[sensorCode].resolution;
    
    switch (sensorCode) {

      case 0   :  addToPayload(sensorName, dataResolution, getDecimalNumberFromBytes(dataSigned, dataSize)); break;  // Digital Input
      case 1   :  addToPayload(sensorName, dataResolution, getDecimalNumberFromBytes(dataSigned, dataSize)); break;  // Digital Output
      case 2   :  addToPayload(sensorName, dataResolution, getDecimalNumberFromBytes(dataSigned, dataSize)); break;  // Analog Input
      case 3   :  addToPayload(sensorName, dataResolution, getDecimalNumberFromBytes(dataSigned, dataSize)); break;  // Analog Output
      case 101 :  addToPayload(sensorName, dataResolution, getDecimalNumberFromBytes(dataSigned, dataSize)); break;  // Illuminance Sensor
      case 102 :  addToPayload(sensorName, dataResolution, getDecimalNumberFromBytes(dataSigned, dataSize)); break;  // Presence Sensor
      case 103 :  addToPayload(sensorName, dataResolution, getDecimalNumberFromBytes(dataSigned, dataSize)); break;  // Temperature Sensor
      case 104 :  addToPayload(sensorName, dataResolution, getDecimalNumberFromBytes(dataSigned, dataSize)); break;  // Humidity Sensor
      case 113 :  addToPayload(sensorName, dataResolution, getDecimalNumberFromBytes(dataSigned, dataSize)); break;  // Accelerometer
      case 115 :  addToPayload(sensorName, dataResolution, getDecimalNumberFromBytes(dataSigned, dataSize)); break;  // Barometer
      case 115 :  addToPayload(sensorName, dataResolution, getDecimalNumberFromBytes(dataSigned, dataSize)); break;  // Unix Time
      case 134 :  addToPayload(sensorName, dataResolution, getDecimalNumberFromBytes(dataSigned, dataSize)); break;  // Gyrometer
      case 136 :                                                                                   // GPS Location
                  sensorName = sensorTypes[sensorCode].name + "_" + sensorChannel + ".latitude";
                  dataResolution = sensorTypes[sensorCode].resolution[0];
                  addToPayload(sensorName, dataResolution, getDecimalNumberFromBytes(dataSigned, 3));

                  sensorName = sensorTypes[sensorCode].name + "_" + sensorChannel + ".longitude";
                  dataResolution = sensorTypes[sensorCode].resolution[1];
                  addToPayload(sensorName, dataResolution, getDecimalNumberFromBytes(dataSigned, 3));
        
                  sensorName = sensorTypes[sensorCode].name + "_" + sensorChannel + ".altitude";
                  dataResolution = sensorTypes[sensorCode].resolution[2];
                  addToPayload(sensorName, dataResolution, getDecimalNumberFromBytes(dataSigned, 3));

                  break;

      case 137 :                                                                                    // GPS Location extended
                  sensorName = sensorTypes[sensorCode].name + "_" + sensorChannel + ".latitude";
                  dataResolution = sensorTypes[sensorCode].resolution[0];
                  addToPayload(sensorName, dataResolution, getDecimalNumberFromBytes(dataSigned, 3));

                  sensorName = sensorTypes[sensorCode].name + "_" + sensorChannel + ".longitude";
                  dataResolution = sensorTypes[sensorCode].resolution[1];
                  addToPayload(sensorName, dataResolution, getDecimalNumberFromBytes(dataSigned, 3));
        
                  sensorName = sensorTypes[sensorCode].name + "_" + sensorChannel + ".altitude";
                  dataResolution = sensorTypes[sensorCode].resolution[2];
                  addToPayload(sensorName, dataResolution, getDecimalNumberFromBytes(dataSigned, 3));

                  sensorName = sensorTypes[sensorCode].name + "_" + sensorChannel + ".satelites";
                  dataResolution = sensorTypes[sensorCode].resolution[3];
                  addToPayload(sensorName, dataResolution, getDecimalNumberFromBytes(dataSigned, 1));
      
                  sensorName = sensorTypes[sensorCode].name + "_" + sensorChannel + ".speed";
                  dataResolution = sensorTypes[sensorCode].resolution[4];
                  addToPayload(sensorName, dataResolution, getDecimalNumberFromBytes(dataSigned, 2));
      
                  sensorName = sensorTypes[sensorCode].name + "_" + sensorChannel + ".timestamp";
                  dataResolution = sensorTypes[sensorCode].resolution[5];
                  addToPayload(sensorName, dataResolution, getDecimalNumberFromBytes(dataSigned, 4));
                  break;

      case 138 :  addToPayload(sensorName, dataResolution, getDecimalNumberFromBytes(dataSigned, dataSize)); break;  // Soil Moisture
    }
  }
      
  return payload; 
}
