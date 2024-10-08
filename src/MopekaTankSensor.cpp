#include "MopekaTankSensor.h"

MopekaTankSensor::MopekaTankSensor() : lastTransmission(0) {
    advertisingData = {
        .Preamble = 0xFF0D,
        .ManufacturerData = {0x59, 0x00, 0x0C},
        .Battery = 0x64,      
        .Temperature = 0x28,  
        .Sensor = 0xC000,     
        .MAC = {0x00, 0x00, 0x00},
        .X = 0x0, 
        .Y = 0x0, 
        .Postamble = 0xFEE50203
    };
}

void MopekaTankSensor::setup() {
    dataChanged = false;

    if (!BLE.begin()) {
        Serial.println("failed to initialize BLE!");
        while (1);
    }

    BLEService myService(SERVICE_UUID);
    BLE.addService(myService);

    // Get the BLE MAC address as a string
    String bleMacAddress = BLE.address();
    Serial.print("BLE MAC Address: ");
    Serial.println(bleMacAddress.c_str());

    // Convert the MAC address string to a byte array
    uint8_t mac[6];
    sscanf(bleMacAddress.c_str(), "%02x:%02x:%02x:%02x:%02x:%02x", 
            &mac[0], &mac[1], &mac[2], &mac[3], &mac[4], &mac[5]);

    // Copy the last 3 bytes into advertisingData.MAC
    memcpy(advertisingData.MAC, &mac[3], 3);
    
    BLEAdvertisingData advData;
    advData.setRawData((uint8_t*)&advertisingData, sizeof(AdvertisingData));
    BLE.setAdvertisingData(advData);

    BLEAdvertisingData scanData;
    scanData.setLocalName(_NAME);
    BLE.setScanResponseData(scanData);
    
    BLE.advertise();
}

uint8_t MopekaTankSensor::getSensorQuality() {
    return advertisingData.Sensor >> 14;
}

void MopekaTankSensor::setSensorQuality(uint8_t quality) {
    advertisingData.Sensor = (quality << 14) + (advertisingData.Sensor & 0x3FFF);
    dataChanged = true;
}

uint16_t MopekaTankSensor::getSensorValue() {
    return advertisingData.Sensor & 0x3FFF;
}


void MopekaTankSensor::setSensorValue(uint16_t value) {
    advertisingData.Sensor = (advertisingData.Sensor & 0xC000) + (value & 0x3FFF);
    dataChanged = true;
}

void MopekaTankSensor::loop() {
    if (!dataChanged && millis() - lastTransmission < TRANSMIT_INTERVAL) {
        return;
    }

    lastTransmission = millis();
    
    if (dataChanged) {
        dataChanged = false;
        BLE.advertise();
    }
    else {
        BLE.poll();
    }

    delay(1);
}
