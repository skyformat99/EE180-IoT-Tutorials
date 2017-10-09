#include <linux/module.h>	/* Used by all kernel modules */
#include <linux/kernel.h>	/* Useful for printk() */
#include <linux/init.h>		/* Used for init and exit declaration */
#include <linux/smp.h>		/* Used for get_cpu() and put_cpu() */
#include <linux/time.h>		/* Used for do_gettimeofday() */

MODULE_DESCRIPTION("A basic Hello World kernel module");
MODULE_LICENSE("GPL");

static struct timeval tv;

/* Initialization function */
static int intro_init(void)
{
	int cpu_id;

	do_gettimeofday(&tv);
	cpu_id = get_cpu();
	put_cpu();

	/* print to kernel message buffer */
	printk("Hello! | Timestamp: %9i.%06i | CPU: %i\n",
		       	(int) tv.tv_sec, (int) tv.tv_usec, cpu_id);
	return 0;
}

/* Exit function */
static void intro_exit(void)
{
}

/* Declare initilization and exit functions */
module_init(intro_init);
module_exit(intro_exit);
