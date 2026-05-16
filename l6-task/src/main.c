#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/drivers/sensor.h>

#include "my_driver.h"

#define SLEEP_TIME_MS 100

const struct device *dev =
    DEVICE_DT_GET_ONE(my_driver_sensor);

int main(void)
{
    struct sensor_value val;

    if (!device_is_ready(dev))
	{
        return 0;
    }

    sensor_sample_fetch(dev);
    k_sleep(K_SECONDS(1));
    sensor_channel_get(
        dev,
        SENSOR_CHAN_ALL,
        &val);
    k_sleep(K_SECONDS(1));

    while (1)
	{
        my_driver_toggle(dev);
        k_sleep(K_MSEC(SLEEP_TIME_MS));
    }
}