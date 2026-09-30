#include <zephyr/drivers/gpio.h>
#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>
#include <zephyr/drivers/sensor.h>
#include <drivers/dummy_driver/dummy_driver.h>

LOG_MODULE_REGISTER(main, LOG_LEVEL_INF);

const struct device* driver = DEVICE_DT_GET(DT_NODELABEL(dummudriver0));

int main(void)
{
    bool invert = true;
    struct sensor_value val;

    while (1) {
        if (invert) 
            invert = false;
        else
            invert = true;

        dummy_driver_set_invert(driver, invert);
        sensor_sample_fetch(driver);
        sensor_channel_get(driver, SENSOR_CHAN_AMBIENT_TEMP, &val);
        k_msleep(1000);
    }
    return 0;
}
