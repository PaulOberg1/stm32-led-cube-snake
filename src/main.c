#include <stdlib.h>
#include <time.h>

#include "game.h"

#include "libopencm3/stm32/rcc.h"
#include "libopencm3/stm32/gpio.h"
#include "libopencm3/stm32/usart.h"
#include "libopencm3/stm32/adc.h"

static void hardware_init(void) {

    rcc_periph_clock_enable(RCC_GPIOA);
    rcc_periph_clock_enable(RCC_GPIOB);
    rcc_periph_clock_enable(RCC_GPIOC);
    rcc_periph_clock_enable(RCC_ADC12);
    rcc_periph_clock_enable(RCC_USART1);

    gpio_mode_setup(GPIOA, GPIO_MODE_ANALOG, GPIO_PUPD_NONE, GPIO1);
    gpio_mode_setup(GPIOA, GPIO_MODE_ANALOG, GPIO_PUPD_NONE, GPIO0);
    gpio_mode_setup(GPIOC, GPIO_MODE_ANALOG, GPIO_PUPD_NONE, GPIO1);
    gpio_mode_setup(GPIOC, GPIO_MODE_ANALOG, GPIO_PUPD_NONE, GPIO0);

    adc_power_off(ADC1);
    adc_set_clk_prescale(ADC1, ADC_CCR_CKMODE_DIV1);
    adc_disable_external_trigger_regular(ADC1);
    adc_set_right_aligned(ADC1);
    adc_set_sample_time_on_all_channels(ADC1, ADC_SMPR_SMP_61DOT5CYC);
    adc_set_resolution(ADC1, ADC_CFGR1_RES_12_BIT);
    adc_power_on(ADC1);

    gpio_mode_setup(GPIOB, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO5);
    gpio_set(GPIOB, GPIO5);

    gpio_mode_setup(GPIOB, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO6);
    gpio_set_af(GPIOB, GPIO_AF7, GPIO6);
    gpio_mode_setup(GPIOB, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO7);
    gpio_set_af(GPIOB, GPIO_AF7, GPIO7);

    usart_set_baudrate(USART1, 9600);
    usart_set_databits(USART1, 8);
    usart_set_stopbits(USART1, USART_STOPBITS_1);
    usart_set_mode(USART1, USART_MODE_TX_RX);
    usart_set_parity(USART1, USART_PARITY_NONE);
    usart_set_flow_control(USART1, USART_FLOWCONTROL_NONE);
    usart_enable(USART1);
}

int main(void) {
    srand(time(NULL));
    hardware_init();
    game();

    while (1);
}