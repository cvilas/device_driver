#include <linux/module.h>
#include <linux/init.h>
#include <linux/gpio/consumer.h>

static struct gpio_desc *led, *button;

#define IO_LED 21
#define IO_BUTTON 20
#define IO_OFFSET 0

static int __init my_init(void) {
	int status;

	led = gpio_to_desc(IO_LED + IO_OFFSET);
	if( !led ) {
		printk("gpioctrl - Error getting LED pin\n");
		return -ENODEV;
	}
	
	button = gpio_to_desc(IO_BUTTON + IO_OFFSET);
	if( !button ) {
		printk("gpioctrl - Error getting button pin\n");
		return -ENODEV;
	}

	status = gpiod_direction_output(led, 0);
	if(status) {
		printk("gpioctrl - Error configuring LED pin as output\n");
		return status;
	}

	status = gpiod_direction_input(button);
	if( button ) {
		printk("gpioctrl - Error configuring button pin as input\n");
		return status;
	}
	
	gpiod_set_value(led, 1);
	printk("gpioctrl - button is %spressed\n", gpiod_get_value(button) ? "" : "not ");

	return 0;
}

static void __exit my_exit(void) {
	printk("hello - Goodbye Kernel!\n");
}

module_init(my_init);
module_exit(my_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Vilas Chitrakaran");
MODULE_DESCRIPTION("A example for using GPIOs without device tree");

