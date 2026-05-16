#include <stdio.h>
#include <zephyr/init.h>

static int board_my_board_init(void)
{
    printf("My board has been initialized");

    return 0;
}

SYS_INIT(board_my_board_init, POST_KERNEL,
        CONFIG_KERNEL_INIT_PRIORITY_DEFAULT);
