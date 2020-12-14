#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/proc_fs.h>
#include <linux/kthread.h>
#include <linux/mutex.h>
#include <linux/completion.h>
#include <linux/time.h>
#include <asm/fpu/internal.h>
#include "tiktok.h"

static const char proc_dirname[] = "tiktok";
struct proc_dir_entry *tiktok_proc_root;
struct mutex perf_lock;
struct completion perf_done;

int perf_thread(void *data) {
	int i = 0;
	u64 nsecs = 0;
	u64 msecs;
	u64 seqs[TIKTOK_REPEATS];
	kernel_fpu_begin();
	while (i < TIKTOK_WARMUP) {
		target_main();
		i += 1;
	}
	i = 0;
	while (i < TIKTOK_REPEATS) {
		struct timespec start = {0}, end = {0};
		getrawmonotonic(&start);
		target_main();
		getrawmonotonic(&end);
		seqs[i] = (end.tv_sec - start.tv_sec) * 1000000000 + end.tv_nsec - start.tv_nsec;
		nsecs += seqs[i];
		i += 1;
		cond_resched();
	}
	kernel_fpu_end();
	msecs = nsecs / TIKTOK_REPEATS / 1000;
	i = 0;
	printk(KERN_INFO "Tiktok: seqs: ");
	while (i < TIKTOK_REPEATS) {
		printk(KERN_INFO "%llu", seqs[i]);
		i += 1;
	}
	printk(KERN_INFO "Tiktok: Average runtime: %llu.%llu\n", msecs / 1000, msecs % 1000);
	complete_and_exit(&perf_done, 0);
}

ssize_t tiktok_run_perf(struct file *filp, const char __user *buf,
						  size_t len, loff_t *ppos) {
	struct task_struct *runner;
	mutex_lock(&perf_lock);
	reinit_completion(&perf_done);
	runner = kthread_create(perf_thread, NULL, "tiktok_run");
	kthread_bind(runner, 0);
	wake_up_process(runner);
	wait_for_completion(&perf_done);
	mutex_unlock(&perf_lock);
	return len;
}

static const struct file_operations tiktok_perf_fops = {
	.owner		= THIS_MODULE,
	.write		= tiktok_run_perf
};

static int __init tiktok_init(void) {
	if ((tiktok_proc_root = proc_mkdir(proc_dirname, NULL)) == NULL)
		return -EEXIST;
	if (proc_create("perf", 0444, tiktok_proc_root, &tiktok_perf_fops) == NULL)
		return -ENOMEM;
	printk(KERN_INFO "Tiktok loaded\n");
	mutex_init(&perf_lock);
	init_completion(&perf_done);
	return 0;
}

static void __exit tiktok_exit(void) {
	remove_proc_entry("perf", tiktok_proc_root);
	remove_proc_entry("tiktok", NULL);
	printk(KERN_INFO "Tiktok exits\n");
}

module_init(tiktok_init);
module_exit(tiktok_exit);

MODULE_LICENSE("GPL v2");
MODULE_ALIAS("tiktok");
MODULE_AUTHOR("Jiahao Li <gloit042@gmail.com>");
MODULE_DESCRIPTION("stat program running time in kernel");

