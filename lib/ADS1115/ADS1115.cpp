#include "ADS1115.h"
#include "iostream"

ADS1115::ADS1115(PeripheralI2C *i2cController, uint8_t addr) {
  i2c = i2cController;
  address = addr;
}

// Function to initialize the ADS1115 in continuous mode
void ADS1115::initialize() {
    // Configure the ADS1115
    uint8_t config[3];
    config[0] = ADS1115_REG_CONFIG; // Register pointer to Config register

  // Config MSB (byte 1):
    // OS=0 (continuous mode), PGA=±2.048V (010), MODE=0 (continuous), MUX set to AIN0 to GND (100b = 4)
    config[1] = 0x84;

    // Config LSB (byte 2):
    // DR=860 SPS, COMP_MODE=0, COMP_POL=0, COMP_LAT=0, COMP_QUE=11 (disable comparator)
    config[2] = 0xE3;

    // Write the configuration to the ADS1115
    i2c->write(address, config, 3);
}

// Function to read the latest ADC conversion result
int16_t ADS1115::readConversion() {
    // Read the conversion register
    uint8_t read_data[2];
    i2c->readRegister(address, ADS1115_REG_CONVERSION, read_data, 2);

    // Combine MSB and LSB to form a 16-bit result
    int16_t result = (read_data[0] << 8) | read_data[1];
    return result;
}

void ADS1115::printI2CScan() {
    // Call the scan method
    std::map<uint8_t, bool> scanResults = i2c->scan();

    // Print the results
    if (scanResults.empty()) {
        printf("No devices found on the I2C bus.\n");
    } else {
        printf("I2C devices found:\n");
        for (const auto& [address, status] : scanResults) {
            printf("Address: 0x%02X, Status: %s\n", address, status ? "Present" : "Not Responding");
        }
    }
}

void ADS1115::setMux(uint8_t mux) {
    // Ensure the MUX value is valid (0-7)
    if (mux > 7) return;

    // Read the current configuration register
    uint8_t config[2];
    i2c->readRegister(address, ADS1115_REG_CONFIG, config, 2);

    // Update only the MUX bits (bits 14-12)
    config[0] = (config[0] & 0x8F) | ((mux & 0x07) << 4);

    // Write the updated configuration back to the ADS1115
    uint8_t new_config[3] = {ADS1115_REG_CONFIG, config[0], config[1]};
    i2c->write(address, new_config, 3);
}

bool ADS1115::isReady() {
    // Read the current configuration register
    uint8_t config[2];
    i2c->readRegister(address, ADS1115_REG_CONFIG, config, 2);

    // Check the OS bit (bit 15) in the configuration register
    return (config[0] & 0x80) != 0; // Bit 15 is the MSB of config[0]
}

void ADS1115::setChannel(uint8_t channel){
  config = 0x00;
	switch (channel){
    case (0):
      config = ADS1115_MUX_AIN0_G;
      break;
    case (1):
      config = ADS1115_MUX_AIN1_G;
      break;
    case (2):
      config = ADS1115_MUX_AIN2_G;
      break;
    case (3):
      config = ADS1115_MUX_AIN3_G;
      break;
	  default:
	    break;
  }
  setMux(config);
}
