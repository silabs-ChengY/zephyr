/*
 * Copyright (c) 2021 Sateesh Kotapati
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <init.h>
#include <drivers/gpio.h>
#include <sys/printk.h>

/* This pin is used to enable the serial port using the board controller */
#define VCOM_ENABLE_GPIO_NAME  "GPIO_A"
#define VCOM_ENABLE_GPIO_PIN   5

static int efr32bg_sltb010a_init(const struct device *dev)
{
	const struct device *vce_dev; /* Virtual COM Port Enable GPIO Device */

	ARG_UNUSED(dev);

	/* Enable the board controller to be able to use the serial port */
	vce_dev = device_get_binding(VCOM_ENABLE_GPIO_NAME);
	if (!vce_dev) {
		printk("Virtual COM Port Enable device was not found!\n");
		return -ENODEV;
	}

	gpio_pin_configure(vce_dev, VCOM_ENABLE_GPIO_PIN, GPIO_OUTPUT_HIGH);

	return 0;
}

/* needs to be done after GPIO driver init */
SYS_INIT(efr32bg_sltb010a_init, POST_KERNEL, CONFIG_KERNEL_INIT_PRIORITY_DEVICE);
