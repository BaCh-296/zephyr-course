#ifndef MY_DRIVER_H_
#define MY_DRIVER_H_

#include <zephyr/device.h>
#include <zephyr/drivers/sensor.h>

struct my_driver_config {
    struct gpio_dt_spec drive_pin;
};

struct my_driver_data {
    bool led_state;
};

#endif
