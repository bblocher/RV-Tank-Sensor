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
  float value = scale.get_units(times);
  if (value < 0)
    value = 0;
    
  return value;
}

float TankWeightSensor::getValue(int times) {
  return scale.get_value(times);
}
