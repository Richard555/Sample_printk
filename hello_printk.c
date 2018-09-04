/*
 * "Hello, world!" minimal kernel module
 *
 * Richard
 *
 */

/*
 * The below are header files provided by the kernel which are
 * required for all modules.  They include things like the definition
 * of the module_init() macro.
 */
#include <linux/init.h>
#include <linux/module.h>


void test_atomic (void)
{
	atomic_t at;
	int ret;
	
	atomic_set(&at, 5);
	printk(KERN_ALERT "at.counter = %d\n", atomic_read(&at));
	atomic_dec(&at);
	printk(KERN_ALERT "after atomic_dec(&at). at.counter = %d\n", atomic_read(&at));
	
	//testing 4 + 1
	atomic_set(&at, 4);
	ret = atomic_inc_unless_negative(&at);
	printk(" For    4+1 at = %x, ret =%d \n", at.counter, ret);

	//testing -8 + 1
	atomic_set(&at, -8);
	ret = atomic_inc_unless_negative(&at);
	printk(" For (-8)+1 at = %x, ret=%d \n", at.counter, ret);
}


/*
 * This is the init function, which is run when the module is first
 * loaded.  The __init keyword tells the kernel that this code will
 * only be run once, when the module is loaded.
 */

static int __init
hello_init(void)
{
	
	printk("Hello, world!\n");
//	test_atomic();
	return 0;
}

/*
 * The below macro informs the kernel as to which function to use as
 * the init function.
 */

module_init(hello_init);

/*
 * Similary, the exit function is run once, upon module unloading, and
 * the module_exit() macro identifies which function is the exit
 * function.
 */

static void __exit
hello_exit(void)
{
	printk("Goodbye, world!\n");
}

module_exit(hello_exit);

/*
 * MODULE_LICENSE() informs the kernel what license the module source
 * code is under, which affects which symbols it may access in the
 * main kernel.  Certain module licenses will "taint" the kernel,
 * indicating that non-open or untrusted code has been loaded.
 * Modules licensed under GPLv2 do not taint the kernel and can access
 * all symbols, but declaring it so is a legal statement that the
 * source code to this module is licensed under GPLv2, and so you must
 * provide the source code if you ship a binary version of the module.
 */
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Richard");
MODULE_DESCRIPTION("\"Hello, world!\" minimal module");
MODULE_VERSION("printk");
