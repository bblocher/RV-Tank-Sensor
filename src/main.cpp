#include <MopekaTankSensor.h>
#include <TankWeightSensor.h>

// HX711 circuit wiring
#define LOADCELL_DOUT_PIN 19
#define LOADCELL_SCK_PIN 18
#define MONITOR_INTERVAL 1000;

MopekaTankSensor tankSensor;
TankWeightSensor weightSensor(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);

void setup() {
  Serial.begin(9600);
  tankSensor.setup();
  weightSensor.setup();
}

long lastTankReading = 0;

void loop() {
  // Monitor the tank
  if (millis() - lastTankReading > 10000) {
    lastTankReading = millis();

    float unit = weightSensor.getUnits();
    Serial.println(unit);
    
    // Update tank sensor data
    tankSensor.setSensorValue(weightSensor.getUnits());
  }
  
  // Run the tank sensor loop
  tankSensor.loop();
  delay(1);
}