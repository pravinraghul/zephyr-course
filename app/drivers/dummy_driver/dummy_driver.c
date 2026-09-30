#include <zephyr/drivers/sensor.h>
#include <zephyr/logging/log.h>
#include <zephyr/drivers/gpio.h>

#define DT_DRV_COMPAT dummy_driver
#define LED_NODE DT_ALIAS(app_led)

LOG_MODULE_REGISTER(dummy_driver, LOG_LEVEL_INF);

static const struct gpio_dt_spec led = GPIO_DT_SPEC_GET(LED_NODE, gpios);

static int device_off(const struct device *dev,
                             enum sensor_channel chan,
                             struct sensor_value * val) {
    if (gpio_pin_set_dt(&led, 0) < 0) {
        return -1;
    }
    LOG_INF("Turn OFF LED");
    return 0;
}

static int device_on(const struct device *dev,
				                enum sensor_channel chan) {
    if (gpio_pin_set_dt(&led, 1) < 0) {
        return -1;
    }
    LOG_INF("Turn ON LED");
    return 0;
}

static DEVICE_API(sensor, sensor_dummy) = {
    .channel_get = device_off,
    .sample_fetch = device_on,
};

static int init(const struct device *dev) {

    if (!gpio_is_ready_dt(&led)) 
        return -1;

    if (gpio_pin_configure_dt(&led, GPIO_OUTPUT_ACTIVE) < 0) 
        return -1;

    LOG_INF("Device ON/OFF Initialized!");
    
    if (gpio_pin_set_dt(&led, 1) < 0)
        return -1;

    return 0;
}

DEVICE_DT_INST_DEFINE(0, init, NULL, NULL, NULL, POST_KERNEL, 80, &sensor_dummy);