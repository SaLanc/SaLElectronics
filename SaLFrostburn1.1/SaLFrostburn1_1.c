/*
 * SaLFrostburn1.1.c
 *
 * Created: 3/9/2016 10:23:00 AM
 * Author : Stephen Arwine
 */


#include "sam.h"
#include <SaL.h>
#include <SaLUSART.h>
#include <SaLPort.h>
#include <SaLSample.h>
#include <SaLUsb.h>


int main(void) {
    /* Initialize the SAM system */
    SystemInit();

    SaLDelayInit();
    SalGclkInit();
    SaLRtcInit();
    uart_init(9600);
    //SaLTC4Init();
    sampleInit();
    adcInit();

    pinOut(CC1120_SLAVE_SELECT);
    pinOut(AT25SF_SLAVE_SELECT);
    pinOut(MS5607_SLAVE_SELECT);
    pinOut(ADXL345_SLAVE_SELECT);
    // SaLPinMode(PIN_PA13,INPUT);

     pinOut(MS5607_MOSI);
     pinOut(MS5607_SCK);
    pinIn(MS5607_MISO);




    pinHigh(CC1120_SLAVE_SELECT);
    pinHigh(AT25SF_SLAVE_SELECT);
    pinHigh(MS5607_SLAVE_SELECT);
    pinHigh(ADXL345_SLAVE_SELECT);



    pinOut(LedPin);
    pinHigh(LedPin);

    struct AccelerometerModule myAccelerometer;
    initAccelerometer(&myAccelerometer);
    initBarometer();
    //SaLFlashMemInit();


 //    uint8_t message[255];
 //   AT25SFErace4KBlock(0);
//	     AT25SFWriteByte(0x00101,252);
//	   volatile uint8_t byte = AT25SFGetByte(0x00101);
//    SaLDigitalOut(AT25SF_SLAVE_SELECT_PIN,false);
    byteOut(AT25SF_SCK_PIN,AT25SF_MOSI_PIN,0x9f);
    volatile uint8_t _byte = getByte(AT25SF_SCK_PIN,AT25SF_MISO_PIN);
    SaLDigitalOut(AT25SF_SLAVE_SELECT_PIN,true);

//pinLow(MS5607_SLAVE_SELECT);
//volatile uint8_t _byte =  syncByte(MS5607_SCK,MS5607_MOSI,MS5607_MISO,0xA0);

//pinHigh(MS5607_SLAVE_SELECT);

//
//     pinLow(CC1120_SLAVE_SELECT);
//     volatile uint8_t ccstatus = syncByte(CC1120_SCK ,CC1120_MOSI, CC1120_MISO, 0x80 | 0x30);
//     pinHigh(CC1120_SLAVE_SELECT);
//
//     pinLow(CC1120_SLAVE_SELECT);
//
//     while (pinRead(CC1120_MISO));
//     volatile uint8_t ccstatus2 = syncByte(CC1120_SCK ,CC1120_MOSI, CC1120_MISO, 0x80 | 0x3B);
//     volatile uint8_t ccstatus3 = getByte(CC1120_SCK_PIN,CC1120_MISO_PIN);
//     // byteOut(CC1120_SCK_PIN,CC1120_MOSI_PIN, 0b10111101 );
//     pinHigh(CC1120_SLAVE_SELECT);

    volatile float batt;

    volatile float accelX;
    volatile float accelXOffset;

    for (uint8_t i = 0; i < 20; i++) {
        accelXOffset += (1.8 - (adcRead(ADXL278_ACCELX) * (3.60/2.0)/pow(2,12)))/((1.8-0.50)/70);
    }
    accelXOffset = accelXOffset / 20;

    while (1) {

        delay_ms(100);
       // pinToggle(LedPin);

        sampleTick();
        batt = senseBatVolts(senseBat);
        accelX = (1.8 - (adcRead(ADXL278_ACCELX) * (3.60/2.0)/pow(2,12)))/((1.8-0.50)/70) - accelXOffset;
        // batt = accelX;

    }
}
