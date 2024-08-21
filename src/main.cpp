#include <MopekaTankSensor.h>
#include <TankWeightSensor.h>

// HX711 circuit wiring
#define LOADCELL_DOUT_PIN 19
#define LOADCELL_SCK_PIN 18
#define MONITOR_INTERVAL 1000

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
  if (millis() - lastTankReading > MONITOR_INTERVAL) {
    lastTankReading = millis();

    Serial.println(weightSensor.getValue());
    
    // Update tank sensor data
    float unit = weightSensor.getUnits();
    Serial.println(unit);
    tankSensor.setSensorValue(unit);
  }
  
  // Run the tank sensor loop
  tankSensor.loop();
  delay(1);
}