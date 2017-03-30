#include <linux/module.h>
#include <linux/kernel.h>

int hello_init(void)
{
	printk(KERN_INFO "Kern Hello \r\n");
	return 0;
}

void exit_hello(void)
{
	printk(KERN_INFO "Kern Goodbye \r\n");
}

module_init(hello_init);
module_exit(exit_hello);
