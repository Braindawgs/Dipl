#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/gpio.h>
#include <linux/interrupt.h>
#include <linux/kthread.h>

#define IRQF_TRIGGER_BOTH 0x00000003
#define IRQF_TRIGGER_RISING 0x00000001
#define IRQF_DISABLED 0x00000020

static struct gpio led = {17, GPIOF_DIR_OUT ,"LED_OUT"};//GPIOF_DIR_OUT neprepoznaje ga

static struct gpio button = {10, GPIOF_IN, "GPIO_IN"};

static int button_irq = -1;

//static struct task_struct *ts = NULL;

/*static int led_thread(void *data)
{
	printk(KERN_INFO "Entering LED thread");	

	while(!kthread_should_stop())
	{
		if(gpio_get_value(button.gpio))
		gpio_set_value(led.gpio,  1);
		else 
		gpio_set_value(led.gpio, 0);
	}

	printk(KERN_INFO "Exiting LED thread");
	return 0;
}*/

irqreturn_t button_isr(int irq, void *data)
	{
		printk(KERN_INFO " Value %d",gpio_get_value(button.gpio));
		printk(KERN_INFO "Entering IRQ Handler\r\n");	
		gpio_set_value(led.gpio, gpio_get_value(button.gpio));
	/*	if(gpio_get_value(button.gpio))
		gpio_set_value(led.gpio,1);
		else 							
		gpio_set_value(led.gpio,0);*/
return IRQ_HANDLED;
	}


/*MODULE INIT FUNCTION*/
static int gpiomod_init(void)
{
	printk(KERN_INFO "Init Complete\r\n");

	int ret = 0;

	ret = gpio_request(17, "LED_OUT");
		if(ret)
			{
				printk(KERN_ERR "Unable to req GPIO -- LED_OUT\r\n");
				return ret; 
			}
	
	ret = gpio_request(10, "GPIO_IN");
		if(ret)
			{
				printk(KERN_ERR "Unable to req GPIO -- GPIO_IN\r\n");
				return ret; 
			}
	gpio_direction_output(17,0);
	gpio_direction_input(10);

	ret = gpio_to_irq(button.gpio);
		if(ret < 0)
			{
				printk(KERN_ERR "Unable to req IRQ\n\r");	
				gpio_free(10);	
			}
	
	button_irq = ret;
	printk(KERN_INFO "Req for IRQ complete\r\n");
	
	ret = request_irq(button_irq, button_isr, IRQF_TRIGGER_BOTH | IRQF_DISABLED, "GPIO_IN", NULL);	

/*	ts = kthread_create(led_thread, NULL, "led_thread\r\n");
		if(ts)
			wake_up_process(ts);
		else 
			printk(KERN_ERR "Unable to create thread\r\n");*/

	return 0;
}

/*MODULE EXIT FUNCTION*/
static void gpiomod_exit(void)
{
	printk(KERN_INFO "Exiting module\r\n");

//	if(ts) { kthread_stop(ts); }

	free_irq(button_irq, NULL);	
	gpio_free(17);
	gpio_free(10);		
}

MODULE_LICENSE("GPL");

module_init(gpiomod_init);
module_exit(gpiomod_exit);



