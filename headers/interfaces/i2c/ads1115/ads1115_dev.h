#ifndef _ADS1115DEVICE_H_
#define _ADS1115DEVICE_H_

#include <vector>

#include "i2cdevicebase.h"
#include "ADS1115.h"

class ADS1115Device : public ADS1115, public I2CDeviceBase {
    public:
        // Constructor
        ADS1115Device() {}
        ADS1115Device(PeripheralI2C *i2cController, uint8_t addr = 0x48) : ADS1115(i2cController, addr) {}

        std::vector<uint8_t> getDeviceAddresses() const override {
            return {0x48,0x49,0x4A,0x4B};
        }
};

#endif
