#ifndef DUMMY_DRIVER_H_
#define DUMMY_DRIVER_H_

#include <zephyr/device.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

int dummy_driver_set_invert(const struct device *dev, bool invert);

#ifdef __cplusplus
}
#endif

#endif /* DUMMY_DRIVER_H_ */