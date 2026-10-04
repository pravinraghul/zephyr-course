#include <zephyr/shell/shell.h>
#include <zephyr/drivers/sensor.h>

const struct device *dev = DEVICE_DT_GET(DT_NODELABEL(dummudriver0));

static int sencmd_sample_fetch(const struct shell *sh, size_t argc, char **argv) {
    ARG_UNUSED(argc);
    ARG_UNUSED(argv);

    if (!device_is_ready(dev)) {
        shell_error(sh, "Device not ready");
        return -ENODEV;
    }

    int ret = sensor_sample_fetch(dev);
    if (ret < 0) {
        shell_error(sh, "sample_fetch failed: %d", ret);
        return ret;
    }

    shell_print(sh, "sample_fetch OK");
    return 0;
}

static int sencmd_channel_get(const struct shell *sh, size_t argc, char **argv) {
    ARG_UNUSED(argc);
    ARG_UNUSED(argv);
    struct sensor_value val;
    if (!device_is_ready(dev)) {
        shell_error(sh, "Device not ready");
        return -ENODEV;
    }

    int ret = sensor_channel_get(dev, SENSOR_CHAN_AMBIENT_TEMP, &val);
    if (ret < 0) {
        shell_error(sh, "channel_get failed: %d", ret);
        return ret;
    }

    shell_print(sh, "channel_get OK (val=%d)", val.val1);
    return 0;
}

static int sencmd_info(const struct shell *sh, size_t argc, char **argv) {
    ARG_UNUSED(argc);
    ARG_UNUSED(argv);

    bool ready = device_is_ready(dev);
    shell_print(sh, "Device: %s", dev->name);
    shell_print(sh, "Status: %s", ready ? "ready" : "not ready");
    return 0;
}

static int sencmd_set_value(const struct shell *sh, size_t argc, char **argv) {
    if (!device_is_ready(dev)) {
        shell_error(sh, "Device not ready");
        return -ENODEV;
    }

    if (argc < 2) {
        shell_error(sh, "Missing argument. Usage: sensor set <0|1>");
        return -EINVAL;
    }

    char *end;
    long value = strtol(argv[1], &end, 0);

    if (*end != '\0' || end == argv[1]) {
        shell_error(sh, "Invalid value '%s', expected a number (0 or 1)", argv[1]);
        return -EINVAL;
    }

    if (value < 0 || value > 1) {
        shell_error(sh, "Value %ld out of range, expected 0 or 1", value);
        return -ERANGE;
    }

    shell_print(sh, "invert set to %ld", value);
    return 0;
}

SHELL_STATIC_SUBCMD_SET_CREATE(subcmd,
    SHELL_CMD(fetch, NULL, "Fetch sensor sample", sencmd_sample_fetch),
    SHELL_CMD(read, NULL, "Get sensor value", sencmd_channel_get),
    SHELL_CMD(info, NULL, "Device info", sencmd_info),
    SHELL_CMD_ARG(set, NULL, "set <0|1>", sencmd_set_value, 2, 0),
    SHELL_SUBCMD_SET_END
);

SHELL_CMD_REGISTER(sensor, &subcmd, "Dummy Sensor", NULL);