

#include <SaLPort.h>

void SaLPinMode(uint8_t pin,uint8_t DIR) {
    PortGroup *const port = SaLGetPort(pin);
    uint32_t pin_mask = (1UL << (pin % 32));

    if ( DIR == OUTPUT) {
        port->DIRSET.reg = pin_mask;
        port->PINCFG[pin].reg = 0;

    } else if(DIR == INPUT) {
        port->DIRCLR.reg = pin_mask;
        port->PINCFG[pin].reg = PORT_PINCFG_INEN;
        port->PINCFG[pin].reg |= PORT_PINCFG_PULLEN;
    } else if (DIR == OUTSTRONG) {
        port->DIRSET.reg = pin_mask;
        port->PINCFG[pin].reg = 0x40;

    }
}