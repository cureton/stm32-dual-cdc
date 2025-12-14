#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/flash.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/usb/usbd.h>

#include <libopencm3/cm3/cortex.h> // For __WFI();



#include <stddef.h> /* for NULL */
#include "isr.h"

#include "usb_descriptors.h"  /* dev_descriptor, config_descriptor, usb_strings*/
#include "usb_cdc.h"

/* --------------------------------------------------------------------------
 * Clock Setup
 * -------------------------------------------------------------------------- */
static void clock_setup(void)
{
    rcc_clock_setup_pll(&rcc_hse_25mhz_3v3[RCC_CLOCK_3V3_96MHZ]);
}

/* --------------------------------------------------------------------------
 * GPIO Setup: PA11/PA12 USB, PA9 fake VBUS, PC13 LED
 * -------------------------------------------------------------------------- */
static void gpio_setup(void)
{
    rcc_periph_clock_enable(RCC_GPIOA);
    rcc_periph_clock_enable(RCC_GPIOC);

    /* USB pins: PA11 = DM, PA12 = DP (AF10) */
    gpio_mode_setup(GPIOA, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO11 | GPIO12);
    gpio_set_af(GPIOA, GPIO_AF10, GPIO11 | GPIO12);

    /* Fake VBUS: PA9 high so OTG FS thinks VBUS is present */
    gpio_mode_setup(GPIOA, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO9);
    gpio_set(GPIOA, GPIO9);

    /* Optional: PC13 as LED output */
    gpio_mode_setup(GPIOC, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO13);
    gpio_set(GPIOC, GPIO13); /* LED off (board-dependent) */
}


void hard_fault_handler(void)
{
    while (1) {
        gpio_toggle(GPIOC, GPIO13);
        for (volatile int i = 0; i < 500000; i++);
    }
}

/* --------------------------------------------------------------------------
 * main()
 * -------------------------------------------------------------------------- */
int main(void)
{
    clock_setup();
    gpio_setup();

    usb_cdc_setup();

    int count =0;

    while (1) {
	
	/* TODO = Enable USB interrupts, and call establish WFI asm to wait-for-interrutpts 
           this is probably the right way to do it, howevre for the moment I am going to thrash on 
           usb_poll()
        */

	usb_cdc_poll();
    }
    return 0;
}
