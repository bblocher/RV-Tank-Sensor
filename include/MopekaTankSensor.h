#ifndef MOPEKATANKSENSOR_H
#define MOPEKATANKSENSOR_H

#include <ArduinoBLE.h>

#define SERVICE_UUID "FEE5"
#define TRANSMIT_INTERVAL 1000

#ifndef _NAME
    #define _NAME "Unknown"
#endif

struct AdvertisingData {
    u_int16_t Preamble;
    uint8_t ManufacturerData[3];
    uint8_t Battery;
    uint8_t Temperature;
    uint16_t Sensor;
    uint8_t MAC[3];
    int8_t X;
    int8_t Y;
    u_int32_t Postamble;
} __attribute__((packed));

class MopekaTankSensor {
public:
    MopekaTankSensor();
    void setup();
    void loop();
    uint8_t getSensorQuality();
    void setSensorQuality(uint8_t quality);
    uint16_t getSensorValue();
    void setSensorValue(uint16_t value);

private:
    AdvertisingData advertisingData;
    long lastTransmission;
    bool dataChanged;
};

#endif // MOPEKATANKSENSOR_H
