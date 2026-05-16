#include <zephyr/kernel.h>
#include <zephyr/device.h>

#include <zephyr/drivers/sensor.h>

const struct device *dev =
    DEVICE_DT_GET_ONE(my_driver_sensor);

int main(void)
{
    struct sensor_value val;

    if (!device_is_ready(dev))
	{
        return 0;
    }

    while (1)
	{
        sensor_sample_fetch(dev);
        k_sleep(K_SECONDS(1));
        sensor_channel_get(
            dev,
            SENSOR_CHAN_ALL,
            &val);
        k_sleep(K_SECONDS(1));
    }
}