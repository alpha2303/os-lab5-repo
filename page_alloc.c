#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/kthread.h>

MODULE_AUTHOR("TEAM 2");
MODULE_DESCRIPTION("LAB 5");
MODULE_LICENSE("GPL");

static struct task_struct *worker_thread;
static unsigned int objnum = 2000;
struct Page {
    unsigned int pageArray[8];
};

module_param(objnum, uint, S_IRUSR | S_IWUSR);

static int thread_func(void *data) {
    printk(KERN_ALERT "Number of objects: %d\n", objnum);
    printk(KERN_ALERT "Size of Page Struct: %d\n", sizeof(struct Page));
    return 0;
}

static int __init hello_init(void) {
    int cpu_id = 0;
    printk(KERN_ALERT "Creating thread on CPU %d\n", cpu_id);
    worker_thread = kthread_create(thread_func, NULL, "page_alloc");
    kthread_bind(worker_thread, cpu_id);
    printk(KERN_ALERT "Hello World!\n");
    printk(KERN_ALERT "Objnum: %d\n", objnum);
    return 0;
}

static void __exit hello_exit(void) {
    printk(KERN_ALERT "Goodbye, World!\n");
}

module_init(hello_init);
module_exit(hello_exit);