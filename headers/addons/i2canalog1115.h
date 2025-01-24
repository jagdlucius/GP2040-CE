#ifndef _I2C1115Analog_H
#define _I2C1115Analog_H

#include "ads1115_dev.h"

#include "gpaddon.h"

#include "GamepadEnums.h"
#include "peripheralmanager.h"

#ifndef I2C_ANALOG1115_ENABLED
#define I2C_ANALOG1115_ENABLED 0
#endif

#ifndef I2C_ANALOG1115_SDA_PIN
#define I2C_ANALOG1115_SDA_PIN    -1
#endif

#ifndef I2C_ANALOG1115_SCL_PIN
#define I2C_ANALOG1115_SCL_PIN    -1
#endif

#ifndef I2C_ANALOG1115_BLOCK
#define I2C_ANALOG1115_BLOCK i2c0
#endif

#ifndef I2C_ANALOG1115_SPEED
#define I2C_ANALOG1115_SPEED 400000
#endif

#ifndef I2C_ANALOG1115_ADDRESS
#define I2C_ANALOG1115_ADDRESS 0x48
#endif

// Analog Module Name
#define I2CAnalog1115Name "I2C1115Analog"

typedef struct {
	float A[4];
} ADS1115_PINS;

class I2CAnalog1115Input : public GPAddon {
public:
	virtual bool available();
	virtual void setup();       // Analog Setup
	virtual void preprocess() {}
	virtual void process();     // Analog Process
    virtual std::string name() { return I2CAnalog1115Name; }
private:
    ADS1115Device * ads;
	ADS1115_PINS pins;
	int channelHop;
	uint32_t uIntervalMS;       // ADS1115 Interval
	uint32_t nextTimer;         // Turbo Timer
};

#endif  // _I2C1115Analog_H_
