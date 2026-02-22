#include "joystick.h"
#include "libopencm3/stm32/adc.h"

double readJoystick(int channel) {
    uint8_t cA[16];
    cA[0] = channel;

    adc_set_regular_sequence(ADC1, 1, cA);
    adc_start_conversion_regular(ADC1);

    while (!(adc_eoc(ADC1)));

    uint32_t value = adc_read_regular(ADC1);
    return ((double)value - 950.0) / 1040.0;
}