#include <MS5607.h>
#include <math.h>



uint32_t read_Adc(uint8_t _cmd) {
    SaLDigitalOut(MS5607_SLAVE_SELECT_PIN,FALSE);
    byteOut(MS5607_SCK_PIN,MS5607_MOSI_PIN,_cmd);
    SaLDigitalOut(MS5607_SLAVE_SELECT_PIN,TRUE);
    delay_us(900);

    SaLDigitalOut(MS5607_SLAVE_SELECT_PIN,FALSE);
    byteOut(MS5607_SCK_PIN,MS5607_MOSI_PIN,cmdAdcRead_);
    volatile uint8_t _byte1 = getByte(MS5607_SCK_PIN,MS5607_MISO_PIN);
    volatile uint8_t _byte2 = getByte(MS5607_SCK_PIN,MS5607_MISO_PIN);
    volatile uint8_t _byte3 = getByte(MS5607_SCK_PIN,MS5607_MISO_PIN);
    SaLDigitalOut(MS5607_SLAVE_SELECT_PIN,TRUE);

    uint32_t _receive = _byte1;
    _receive = (_receive * 256) + _byte2;
    _receive = (_receive * 256) + _byte3;

    return _receive;

}

uint32_t readMS5607AdcResults(){
	
	 SaLDigitalOut(MS5607_SLAVE_SELECT_PIN,FALSE);
	 byteOut(MS5607_SCK_PIN,MS5607_MOSI_PIN,cmdAdcRead_);
	 volatile uint8_t _byte1 = getByte(MS5607_SCK_PIN,MS5607_MISO_PIN);
	 volatile uint8_t _byte2 = getByte(MS5607_SCK_PIN,MS5607_MISO_PIN);
	 volatile uint8_t _byte3 = getByte(MS5607_SCK_PIN,MS5607_MISO_PIN);
	 SaLDigitalOut(MS5607_SLAVE_SELECT_PIN,TRUE);
	 
	 uint32_t _receive = (_byte1 << 16) | (_byte2 << 8) | (_byte3);
	 return _receive;
}

void getMS5607Coeff(uint16_t *coefficients) {

    for (uint8_t coeff_num = 0; coeff_num < 6 ; ++coeff_num ) {
        delay_us(600);
        uint8_t _cmd = MS5607_CMD_PROM_READ + ((coeff_num+1)*2);
        delay_us(600);
        SaLDigitalOut(MS5607_SLAVE_SELECT_PIN,FALSE);
        byteOut(MS5607_SCK_PIN,MS5607_MOSI_PIN,_cmd);
        uint8_t _byte1 = getByte(MS5607_SCK_PIN,MS5607_MISO_PIN);
        uint8_t _byte2 = getByte(MS5607_SCK_PIN,MS5607_MISO_PIN);
        SaLDigitalOut(MS5607_SLAVE_SELECT_PIN,TRUE);
        *(coefficients+coeff_num) = (_byte1 << 8) | _byte2;
    }
}
uint32_t ConvertPressureTemperature(uint32_t *pressure, uint32_t *temperature, uint16_t *coefficients) {
    const uint64_t C1 = (uint64_t)(*coefficients);
    const uint64_t C2 = (uint64_t)(*(coefficients + 1));
    const uint64_t C3 = (uint64_t)(*(coefficients + 2));
    const uint64_t C4 = (uint64_t)(*(coefficients + 3));
    const uint64_t C5 = (uint64_t)(*(coefficients + 4));
    const uint64_t C6 = (uint64_t)(*(coefficients + 5));

    // calculate 1st order pressure and temperature (MS5607 1st order algorithm)
    const volatile int32_t dT    = *temperature - (C5 * 256);
    const volatile int32_t temp  = 2000 + (dT * C6) / (8388608) ;

    const volatile int64_t OFF   = (C2 * (131072)) + ((C4 * dT) / (64));
    const volatile int64_t SENS  = (C1 * (65536)) + ((C3 * dT) / (128));
    const volatile int32_t press = ((*pressure * SENS / (2097152) - OFF) / (32768));
    return press;
}

// uint32_t getAltFt() {
// 
//     const uint32_t temperature = read_Adc(cmdAdcD2_);
//     const uint32_t pressure    = read_Adc(cmdAdcD1_);
//     const uint32_t pressConv   = ConvertPressureTemperature(pressure, temperature);
// 
//     //const int32_t AltCm = pascalToCent(pressConv);
//     volatile uint32_t AltFt = paToFeetNOAA(pressConv);
// 
//     return AltFt;
// }


uint32_t paToFeetNOAA(const int32_t pressurePa) {
    double pressMillibar = 0.01 *pressurePa;

    double altFeet = (1-pow((pressMillibar/1013.25),(0.190284)))*145366.45;
    return (uint32_t)altFeet;
}

