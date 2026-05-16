#define DT_DRV_COMPAT my_driver_sensor

#include <zephyr/kernel.h>
#include <zephyr/devicetree.h>

#include "my_driver.h"

static int my_driver_init(const struct device *dev)
{
    const struct my_driver_config *cfg = dev->config;
    struct my_driver_data *data = dev->data;

    data->led_state = false;

    if (!gpio_is_ready_dt(&cfg->drive_pin)) {
        return -ENODEV;
    }

    int ret = gpio_pin_configure_dt(
        &cfg->drive_pin,
        GPIO_OUTPUT_INACTIVE);

    if (ret < 0) {
        return ret;
    }

    return 0;
}

static int my_driver_sample_fetch(
    const struct device *dev,
    enum sensor_channel chan)
{
    const struct my_driver_config *cfg = dev->config;
    struct my_driver_data *data = dev->data;

    ARG_UNUSED(chan);

    gpio_pin_set_dt(&cfg->drive_pin, 1);

    data->led_state = false;

    return 0;
}

static int my_driver_channel_get(
    const struct device *dev,
    enum sensor_channel chan,
    struct sensor_value *val)
{
    const struct my_driver_config *cfg = dev->config;
    struct my_driver_data *data = dev->data;

    ARG_UNUSED(chan);

    gpio_pin_set_dt(&cfg->drive_pin, 0);

    data->led_state = true;

    val->val1 = 1;
    val->val2 = 0;

    return 0;
}

static int my_driver_toggle_impl(
    const struct device *dev)
{
    const struct my_driver_config *cfg = dev->config;
    struct my_driver_data *data = dev->data;

    data->led_state = !data->led_state;

    gpio_pin_set_dt(
        &cfg->drive_pin,
        data->led_state);

    return 0;
}

static const struct my_driver_api my_driver_api = {
    .sensor_api = {
        .sample_fetch = my_driver_sample_fetch,
        .channel_get = my_driver_channel_get,
    },

    .toggle = my_driver_toggle_impl,
};

#define MY_DRIVER_DEFINE(inst)                                                          \
    static struct my_driver_data data_##inst = {                                        \
        .led_state = false                                                             \
    };                                                                                  \
                                                                                        \
    static const struct my_driver_config config_##inst = {                              \
        .drive_pin = GPIO_DT_SPEC_INST_GET(inst, drive_gpios),                          \
    };                                                                                  \
                                                                                        \
    SENSOR_DEVICE_DT_INST_DEFINE(inst,                                                  \
                                 my_driver_init,                                        \
                                 NULL,                                                  \
                                 &data_##inst,                                          \
                                 &config_##inst,                                        \
                                 POST_KERNEL,                                           \
                                 10,                           \
                                 &my_driver_api);

DT_INST_FOREACH_STATUS_OKAY(MY_DRIVER_DEFINE)
