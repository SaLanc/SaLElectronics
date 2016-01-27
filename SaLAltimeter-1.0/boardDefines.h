#define HAS_SPI_MODULE 1
#include <samd21g18a.h>

#define HAS_MS5607 1
#define MS5607_MOSI_PIN PIN_PA13
#define MS5607_MISO_PIN PIN_PA14
#define MS5607_SCK_PIN PIN_PA15
#define MS5607_SLAVE_SELECT_PIN PIN_PA09

#define HAS_ADXL345 1
#define ADXL345_MOSI_PIN PIN_PA13
#define ADXL345_MISO_PIN PIN_PA14
#define ADXL345_SCK_PIN PIN_PA15
#define ADXL345_SLAVE_SELECT_PIN PIN_PA16

#define HAS_GPS 1
#define HAS_MTK3339 1
#define MTK3339_TX_PIN PIN_PB22
#define MTK3339_RX_PIN PIN_PB23

#define MY_ADXL345_DATA_RATE ADXL345_DATARATE_1600_HZ
#define MY_ADXL345_RANGE ADXL345_RANGE_2_G | ADXL345_RANGE_FULL_RANGE

#define NVM_DFLL_COARSE_POS    58
#define NVM_DFLL_COARSE_SIZE   6
#define NVM_DFLL_FINE_POS      64
#define NVM_DFLL_FINE_SIZE     10

#define BUZZER PIN_PA12

