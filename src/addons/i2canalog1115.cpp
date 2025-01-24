#include "addons/i2canalog1115.h"
#include "storagemanager.h"
#include "helper.h"
#include "config.pb.h"

#define ADS_MAX (float)((1 << 23) - 1)
#define VREF_VOLTAGE 2.048f

bool I2CAnalog1115Input::available() {
    ads = new ADS1115Device();
    PeripheralI2CScanResult result = PeripheralManager::getInstance().scanForI2CDevice(ads->getDeviceAddresses());
    if (result.address > -1) {
        ads->setAddress(result.address);
        ads->setI2C(PeripheralManager::getInstance().getI2C(result.block));
        return true;
    } else {
        delete ads;
        }
    return false;
}

void I2CAnalog1115Input::setup() {

    memset(&pins, 0, sizeof(ADS1115_PINS));
    channelHop = 0;

    uIntervalMS = 1;
    nextTimer = getMillis();

    // Init our ADS1115 library
    ads->initialize();                           // START/SYNC command
}

void I2CAnalog1115Input::process()
{
    if (nextTimer < getMillis()) {
        float result;
        uint32_t readValue;
        if ( ads->isReady() ) {
            readValue = ads->readConversion();
            result = readValue / float(ADS_MAX); // gives us 0.0f to 1.0f (actual voltage is times voltage)
            pins.A[channelHop] = result;
            channelHop = (channelHop+1) % 4; // Loop 0-3
            ads->setMux(channelHop);
            nextTimer = getMillis() + uIntervalMS; // interval for read (we can't be too fast)
        }
    }

    Gamepad * gamepad = Storage::getInstance().GetGamepad();
    gamepad->state.lx = (uint16_t)(65535.f*pins.A[0]);
    gamepad->state.ly = (uint16_t)(65535.f*pins.A[1]);
    gamepad->state.rx = (uint16_t)(65535.f*pins.A[2]);
    gamepad->state.ry = (uint16_t)(65535.f*pins.A[3]);

}
