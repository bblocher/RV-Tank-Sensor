#include "TankWeightSensor.h"

TankWeightSensor::TankWeightSensor(int doutPin, int sckPin, float scaleValue)
  : scaleValue(scaleValue) {
  scale.begin(doutPin, sckPin);
}

void TankWeightSensor::setup() {
  scale.set_scale(scaleValue);
  scale.set_offset(TANK_OFFSET);
}

float TankWeightSensor::getUnits(int times) {
  float units = scale.get_units(times);
  if(TANK_INVERT)
    units = -units;

  if (units < 0) {
    units = 0;
  }
  
  return units;
}

float TankWeightSensor::getValue(int times) {
  float value = scale.get_value(times);
  if(TANK_INVERT)
    value = -value;

  if (value < 0) {
    value = 0;
  }
  
  return value;
}
