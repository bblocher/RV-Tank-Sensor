#ifndef TANKWEIGHTSENSOR_H
#define TANKWEIGHTSENSOR_H

#include "HX711.h"

#ifndef TANK_OFFSET
  #define TANK_OFFSET 0.0f
#endif

#ifndef TANK_SCALE
  #define TANK_SCALE 2280.0f
#endif

class TankWeightSensor {
public:
  TankWeightSensor(int doutPin, int sckPin, float scale = TANK_SCALE);
  void setup();
  float getUnits(int times = 5);
  float getValue(int times = 5);

private:
  HX711 scale;
  float scaleValue;
};

#endif // TANKWEIGHTSENSOR_H
