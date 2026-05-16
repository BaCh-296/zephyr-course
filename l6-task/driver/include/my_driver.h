#ifndef MY_DRIVER_H_
#define MY_DRIVER_H_

#include <zephyr/device.h>
#include <zephyr/drivers/sensor.h>
#include <zephyr/drivers/gpio.h>

struct my_driver_config {
    struct gpio_dt_spec drive_pin;
};

struct my_driver_data {
    bool led_state;
};

struct my_driver_api {
    struct sensor_driver_api sensor_api;

    int (*toggle)(const struct device *dev);
};

static inline int my_driver_toggle(
    const struct device *dev)
{
    const struct my_driver_api *api =
        (const struct my_driver_api *)dev->api;

    return api->toggle(dev);
}

#endif
