#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/kthread.h>
#include <linux/hrtimer.h>
#include <linux/ktime.h>

const char gacMyktname[] = "NaroLab01";
int s32data;
struct task_struct *gpkthmykth;
#define SEC2NSEC(x) (1000000000*(x))

static unsigned long log_sec  = 1;
static unsigned long log_nsec = 0;
static unsigned long gu64int = 0;  /* 1s = 1e9 ns */
static struct hrtimer gstmyhrt;

enum hrtimer_restart mycallback(struct hrtimer *psthrt)
{
	ktime_t s64current, s64interval;
	/* Reset Timer */
	s64current  = ktime_get();
	s64interval = ktime_set(0, gu64int);
	hrtimer_forward(psthrt, s64current, s64interval);

	/* Wake up my kthread */
	wake_up_process(gpkthmykth);

	return HRTIMER_RESTART;
}

int mykthread(void* ptr)
{
	int s32ret;
	ktime_t s64firstblood;
	printk(KERN_ALERT "Running my kernel thread Name = %s.\n", gacMyktname);

	gu64int = SEC2NSEC(log_sec) + log_nsec; 
	/* Init Timer */
	s64firstblood = ktime_set(0, gu64int);	
	hrtimer_init(&gstmyhrt, CLOCK_MONOTONIC, HRTIMER_MODE_REL);
	gstmyhrt.function = &mycallback;
	hrtimer_start(&gstmyhrt, s64firstblood, HRTIMER_MODE_REL);

	/* Start Loop */
	while(!kthread_should_stop())
	{
		schedule();
		printk(KERN_NOTICE "nvcsw = %lu, nivcsw = %lu\n", current->nvcsw, current->nivcsw);
		set_current_state(TASK_INTERRUPTIBLE);
	}
	/* When unload this module */
	printk(KERN_ALERT "Jump out from the inf loop!\n");

	/* Cancel Timer */
	s32ret = hrtimer_cancel(&gstmyhrt);
	if(s32ret)
	{
		printk(KERN_ALERT "HR Timer is active!\n");
	}
	printk(KERN_ALERT "HR Timer has been canceled!\n");

	return 0;
}

static int hello_init(void)
{
	printk(KERN_ALERT "Ready to start kthread.\n");
	gpkthmykth = kthread_run(mykthread, (void*)&s32data, gacMyktname);
	return 0;
}

static void hello_exit(void)
{
	printk(KERN_ALERT "Unload module.\n");
	kthread_stop(gpkthmykth);
}

module_init(hello_init);
module_exit(hello_exit);
module_param(log_sec,  ulong, S_IRUGO);
module_param(log_nsec, ulong, S_IRUGO);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Shakespeare");
MODULE_DESCRIPTION("A Hello, World Module");


