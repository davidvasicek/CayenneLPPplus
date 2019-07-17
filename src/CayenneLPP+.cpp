// Adapted from https://developer.mbed.org/teams/myDevicesIoT/code/Cayenne-LPP/

// Copyright © 2017 The Things Network
// Use of this source code is governed by the MIT license that can be found in the LICENSE file.

#include "CayenneLPP+.h"

CayenneLPP::CayenneLPP(uint8_t size) : maxsize(size)
{
  buffer = (uint8_t *)malloc(size);
  cursor = 0;
}

CayenneLPP::~CayenneLPP(void)
{
  free(buffer);
}

void CayenneLPP::reset(void)
{
  cursor = 0;
}

uint8_t CayenneLPP::getSize(void)
{
  return cursor;
}

uint8_t *CayenneLPP::getBuffer(void)
{
  //    uint8_t[cursor] result;
  //    memcpy(result, buffer, cursor);
  //    return result;
  return buffer;
}

uint8_t CayenneLPP::copy(uint8_t *dst)
{
  memcpy(dst, buffer, cursor);
  return cursor;
}

uint8_t CayenneLPP::addDigitalInput(uint8_t channel, uint8_t value)
{
  if ((cursor + LPP_DIGITAL_INPUT_SIZE) > maxsize)
  {
    return 0;
  }
  buffer[cursor++] = channel;
  buffer[cursor++] = LPP_DIGITAL_INPUT;
  buffer[cursor++] = value;

  return cursor;
}

uint8_t CayenneLPP::addDigitalOutput(uint8_t channel, uint8_t value)
{
  if ((cursor + LPP_DIGITAL_OUTPUT_SIZE) > maxsize)
  {
    return 0;
  }
  buffer[cursor++] = channel;
  buffer[cursor++] = LPP_DIGITAL_OUTPUT;
  buffer[cursor++] = value;

  return cursor;
}

uint8_t CayenneLPP::addAnalogInput(uint8_t channel, float value)
{
  if ((cursor + LPP_ANALOG_INPUT_SIZE) > maxsize)
  {
    return 0;
  }

  int16_t val = value * 100;
  buffer[cursor++] = channel;
  buffer[cursor++] = LPP_ANALOG_INPUT;
  buffer[cursor++] = val >> 8;
  buffer[cursor++] = val;

  return cursor;
}

uint8_t CayenneLPP::addAnalogOutput(uint8_t channel, float value)
{
  if ((cursor + LPP_ANALOG_OUTPUT_SIZE) > maxsize)
  {
    return 0;
  }
  int16_t val = value * 100;
  buffer[cursor++] = channel;
  buffer[cursor++] = LPP_ANALOG_OUTPUT;
  buffer[cursor++] = val >> 8;
  buffer[cursor++] = val;

  return cursor;
}

uint8_t CayenneLPP::addLuminosity(uint8_t channel, uint16_t lux)
{
  if ((cursor + LPP_LUMINOSITY_SIZE) > maxsize)
  {
    return 0;
  }
  buffer[cursor++] = channel;
  buffer[cursor++] = LPP_LUMINOSITY;
  buffer[cursor++] = lux >> 8;
  buffer[cursor++] = lux;

  return cursor;
}

uint8_t CayenneLPP::addPresence(uint8_t channel, uint8_t value)
{
  if ((cursor + LPP_PRESENCE_SIZE) > maxsize)
  {
    return 0;
  }
  buffer[cursor++] = channel;
  buffer[cursor++] = LPP_PRESENCE;
  buffer[cursor++] = value;

  return cursor;
}

uint8_t CayenneLPP::addTemperature(uint8_t channel, float celsius)
{
  if ((cursor + LPP_TEMPERATURE_SIZE) > maxsize)
  {
    return 0;
  }
  int16_t val = celsius * 10;
  buffer[cursor++] = channel;
  buffer[cursor++] = LPP_TEMPERATURE;
  buffer[cursor++] = val >> 8;
  buffer[cursor++] = val;

  return cursor;
}

uint8_t CayenneLPP::addRelativeHumidity(uint8_t channel, float rh)
{
  if ((cursor + LPP_RELATIVE_HUMIDITY_SIZE) > maxsize)
  {
    return 0;
  }
  buffer[cursor++] = channel;
  buffer[cursor++] = LPP_RELATIVE_HUMIDITY;
  buffer[cursor++] = rh * 2;

  return cursor;
}

uint8_t CayenneLPP::addAccelerometer(uint8_t channel, float x, float y, float z)
{
  if ((cursor + LPP_ACCELEROMETER_SIZE) > maxsize)
  {
    return 0;
  }
  int16_t vx = x * 1000;
  int16_t vy = y * 1000;
  int16_t vz = z * 1000;

  buffer[cursor++] = channel;
  buffer[cursor++] = LPP_ACCELEROMETER;
  buffer[cursor++] = vx >> 8;
  buffer[cursor++] = vx;
  buffer[cursor++] = vy >> 8;
  buffer[cursor++] = vy;
  buffer[cursor++] = vz >> 8;
  buffer[cursor++] = vz;

  return cursor;
}

uint8_t CayenneLPP::addBarometricPressure(uint8_t channel, float hpa)
{
  if ((cursor + LPP_BAROMETRIC_PRESSURE_SIZE) > maxsize)
  {
    return 0;
  }
  int16_t val = hpa * 10;

  buffer[cursor++] = channel;
  buffer[cursor++] = LPP_BAROMETRIC_PRESSURE;
  buffer[cursor++] = val >> 8;
  buffer[cursor++] = val;

  return cursor;
}

uint8_t CayenneLPP::addUnixTime(uint8_t channel, uint32_t unixtime)
{
  if ((cursor + LPP_UNIXTIME_SIZE) > maxsize)
  {
    return 0;
  }
  int32_t val = unixtime;

  buffer[cursor++] = channel;
  buffer[cursor++] = LPP_UNIXTIME;
  buffer[cursor++] = val >> 24;
  buffer[cursor++] = val >> 16;
  buffer[cursor++] = val >> 8;
  buffer[cursor++] = val;

  return cursor;
}

uint8_t CayenneLPP::addGyrometer(uint8_t channel, float x, float y, float z)
{
  if ((cursor + LPP_GYROMETER_SIZE) > maxsize)
  {
    return 0;
  }
  int16_t vx = x * 100;
  int16_t vy = y * 100;
  int16_t vz = z * 100;

  buffer[cursor++] = channel;
  buffer[cursor++] = LPP_GYROMETER;
  buffer[cursor++] = vx >> 8;
  buffer[cursor++] = vx;
  buffer[cursor++] = vy >> 8;
  buffer[cursor++] = vy;
  buffer[cursor++] = vz >> 8;
  buffer[cursor++] = vz;

  return cursor;
}

uint8_t CayenneLPP::addGPS(uint8_t channel, float latitude, float longitude, float meters)
{
  if ((cursor + LPP_GPS_SIZE) > maxsize)
  {
    return 0;
  }
  int32_t lat = latitude * 10000;
  int32_t lon = longitude * 10000;
  int32_t alt = meters * 100;

  buffer[cursor++] = channel;
  buffer[cursor++] = LPP_GPS;

  buffer[cursor++] = lat >> 16;
  buffer[cursor++] = lat >> 8;
  buffer[cursor++] = lat;
  buffer[cursor++] = lon >> 16;
  buffer[cursor++] = lon >> 8;
  buffer[cursor++] = lon;
  buffer[cursor++] = alt >> 16;
  buffer[cursor++] = alt >> 8;
  buffer[cursor++] = alt;

  return cursor;
}


uint8_t CayenneLPP::addSoilMoisture(uint8_t channel, float sm)
{
  if ((cursor + LPP_SOIL_MOISTURE_SIZE) > maxsize)
  {
    return 0;
  }
  buffer[cursor++] = channel;
  buffer[cursor++] = LPP_SOIL_MOISTURE;
  buffer[cursor++] = sm * 2;

  return cursor;
}


uint8_t CayenneLPP::addGPSplus(uint8_t channel, float latitude, float longitude, float altitude, uint8_t satellites, uint16_t speed, long timestamp)
{
  if ((cursor + LPP_GPS_PLUS_SIZE) > maxsize)
  {
    return 0;
  }
  int32_t lat = latitude * 10000;
  int32_t lon = longitude * 10000;
  int32_t alt = altitude * 100;

  buffer[cursor++] = channel;
  buffer[cursor++] = LPP_GPS_PLUS;

  buffer[cursor++] = lat >> 16;
  buffer[cursor++] = lat >> 8;
  buffer[cursor++] = lat;
  buffer[cursor++] = lon >> 16;
  buffer[cursor++] = lon >> 8;
  buffer[cursor++] = lon;
  buffer[cursor++] = alt >> 16;
  buffer[cursor++] = alt >> 8;
  buffer[cursor++] = alt;
  buffer[cursor++] = satellites;
  buffer[cursor++] = speed >> 8;
  buffer[cursor++] = speed;
  buffer[cursor++] = timestamp >> 24;
  buffer[cursor++] = timestamp >> 16;
  buffer[cursor++] = timestamp >> 8;
  buffer[cursor++] = timestamp;

  return cursor;
}

uint8_t CayenneLPP::addDustDensity(uint8_t channel, float dd)
{
  if ((cursor + LPP_DUST_DENSITY_SIZE) > maxsize)
  {
    return 0;
  }

  int16_t val = dd * 10;
  buffer[cursor++] = channel;
  buffer[cursor++] = LPP_DUST_DENSITY;
  buffer[cursor++] = val >> 8;
  buffer[cursor++] = val;

  return cursor;
}

/*
*  Funkce pro převod data a času do epochtime formátu
*  volání funkce: convertToEpochtime(day, month, year, hour, minutes, seconds);
*/
uint32_t CayenneLPP::convertToEpochtime(uint16_t year, uint8_t month, uint8_t day, uint8_t hour, uint8_t minutes, uint8_t seconds){

    uint32_t epochtime = 0;

    int daysInMonths[] = {31 ,28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int daysInMonths_leapYear[] = {31 ,29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    if(day > 0 && month > 0 && year > 0){ // den, měsíc a rok musí být větší nule
        
        for(int i = 1970; i < year ; i++){ // cyklus for spočítá počet sekund za již uplynulé celé roky od roku 1970
  
          if(i % 4 == 0){
              epochtime += 366 * 86400;
          }else{
              epochtime += 365 * 86400;
          }
        }
  
        for(int i = 0; i < month -1; i++){ // cyklus for spočítá počet sekund za již uplynulé celé měsíce aktuálního roku
        
          if(i % 4 == 0){
              epochtime += daysInMonths_leapYear[i] * 86400; 
          }else{
              epochtime += daysInMonths[i] * 86400; 
          }
        }
  
      epochtime += (day-1) * 86400;  // připočte se počet sekund za uplynulé dny v aktuálním měsíci      
      epochtime += hour * (unsigned long)3600; // připočte se počet sekund za uplynulé hodiny v aktuálním dni 
      epochtime += minutes * 60; // připočte se počet sekund za uplynulé minuty v aktuální hodině
      epochtime += seconds; // připočte se počet uběhlých sekund
    }
        
    return epochtime;
}




