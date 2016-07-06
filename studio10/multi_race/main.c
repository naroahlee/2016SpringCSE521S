#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/kthread.h>
#include <linux/hrtimer.h>
#include <linux/ktime.h>

const char gacMyktname[] = "NaroStudio10";
struct task_struct *gpkthmykth[4];
#define SEC2NSEC(x) (1000000000*(x))
#define IRT_TIME (1000000)
volatile int race = 0;

int mykthread(void* ptr)
{
	int s32i;
	printk(KERN_ALERT "Running my kernel thread Name = %s.\n", gacMyktname);

	/* Start Loop */
	for(s32i = 0; s32i < IRT_TIME; s32i++)
	{
		race++;
	}

	printk(KERN_ALERT "Jump out from the inf loop!\n");


	return 0;
}


static int hello_init(void)
{
	printk(KERN_ALERT "Ready to start kthread.\n");
	gpkthmykth[0] = kthread_create(mykthread, NULL, gacMyktname);
	gpkthmykth[1] = kthread_create(mykthread, NULL, gacMyktname);
	gpkthmykth[2] = kthread_create(mykthread, NULL, gacMyktname);
	gpkthmykth[3] = kthread_create(mykthread, NULL, gacMyktname);

	set_cpus_allowed(gpkthmykth[0], *cpumask_of(0));
	set_cpus_allowed(gpkthmykth[1], *cpumask_of(1));
	set_cpus_allowed(gpkthmykth[2], *cpumask_of(2));
	set_cpus_allowed(gpkthmykth[3], *cpumask_of(3));

	wake_up_process(gpkthmykth[0]);
	wake_up_process(gpkthmykth[1]);
	wake_up_process(gpkthmykth[2]);
	wake_up_process(gpkthmykth[3]);
	return 0;
}

static void hello_exit(void)
{
	printk(KERN_ALERT "Unload module.\n");
	/*
	kthread_stop(gpkthmykth[0]);
	kthread_stop(gpkthmykth[1]);
	kthread_stop(gpkthmykth[2]);
	kthread_stop(gpkthmykth[3]);
	*/
	printk(KERN_ALERT "race = %d.\n", race);
}

module_init(hello_init);
module_exit(hello_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Shakespeare");
MODULE_DESCRIPTION("A Hello, World Module");
