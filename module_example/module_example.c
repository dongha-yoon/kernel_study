#include <linux/module.h> /* Needed by all modules */
#include <linux/kernel.h> /* Needed for KERN_INFO */

int init_module(void) {
    printk(KERN_INFO "Example 1\n");
    return 0;    // not 0 is failed. -> init_module failed.
}
 
void cleanup_module(void) {
    printk(KERN_INFO "Exit Example 1\n");
}
