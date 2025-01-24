

#ifndef _ADS1115_H_
#define _ADS1115_H_

#include "peripheral_i2c.h"


// Default I2C Address for ADS1115
#define ADS1115_ADDRESS 0x48

// ADS1115 Register Addresses
#define ADS1115_REG_CONVERSION 0x00
#define ADS1115_REG_CONFIG     0x01

//Muxes
#define ADS1115_MUX_AIN0_G 0x05
#define ADS1115_MUX_AIN1_G 0X06
#define ADS1115_MUX_AIN2_G 0X07
#define ADS1115_MUX_AIN3_G 0X08





class ADS1115 {
    protected:
	    uint8_t address;
	    PeripheralI2C* i2c;
    public:

        //Constructor
	    ADS1115() {}
	    ADS1115(PeripheralI2C *i2cController, uint8_t addr = 0x48);

        // Initialize the ADS1115 in continuous mode, AIN0 to GND, 860 SPS, PGA=2.048V
        void initialize();

        // Read the latest ADC conversion result
        int16_t readConversion();

         // New method to set the MUX dynamically 
        void setMux(uint8_t mux);

        void setI2C(PeripheralI2C *i2cController) { this->i2c = i2cController; }
	    void setAddress(uint8_t addr) { this->address = addr; }

    private:

};

#endif /* _ADS1115_H_ */
