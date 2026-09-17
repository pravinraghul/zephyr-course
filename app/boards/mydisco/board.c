#include <zephyr/kernel.h>
#include <zephyr/init.h>
#include <zephyr/sys/printk.h>

static int mydisco_board_init(void) {
    printk("Board Initialized\n");
    return 0;
}
SYS_INIT(mydisco_board_init, POST_KERNEL, CONFIG_KERNEL_INIT_PRIORITY_DEFAULT);