#include <linux/init.h> /* Needed for the macros */
#include <linux/module.h> /* Needed by all modules */
#include <linux/kernel.h> /* Needed for KERN_INFO */
 
static int __init hello_init(void) {
    printk(KERN_INFO "Example 2\n");
 
    return 0;    // not 0 is failed. -> init_module failed.
}
 
static void __exit hello_exit(void) {
    printk(KERN_INFO "Exit Example 2\n");
}
 
module_init(hello_init);
module_exit(hello_exit);
