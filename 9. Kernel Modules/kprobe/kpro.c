#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/kprobes.h>	/* Required for kprobes */

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("kprobe example");

static struct kprobe kp;

int Pre_Handler(struct kprobe *p, struct pt_regs *regs)
{
    printk("Received ping!\n");
    return 0;
}
 
void Post_Handler(struct kprobe *p, struct pt_regs *regs, unsigned long flags)
{
    /* Can do any required post handler work here */
}

/* 
 * Register kprobe at function call's address 
 * Function addresses can be found in /proc/kallsyms
 * Assign pre and post handlers
 */
int kpro_init(void)
{
    printk("kprobe module inserted\n");
    kp.pre_handler = Pre_Handler;
    kp.post_handler = Post_Handler;
    kp.addr = (kprobe_opcode_t *)0xc17c1170;	/* ping_rcv() address */
    register_kprobe(&kp);
    return 0;
} 

/* Unregister kprobe and exit */ 
void kpro_exit(void)
{
    unregister_kprobe(&kp);
    printk("kprobe module removed\n");
}
 
module_init(kpro_init);
module_exit(kpro_exit);
