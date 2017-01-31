#include <linux/module.h>
#include <linux/kernel.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Your name");
MODULE_DESCRIPTION("PMUON");

int init_module(void) {
	unsigned int v;
	printk("Turn PMU on\n");
	
	// 1. Enable "User Enable Register"
	asm volatile("mcr p15, 0, %0, c9, c14, 0\n\t" :: "r" (0x00000001));

	// 2. Reset Performance Monitor Control Register(PMCR), Count Enable Set Register (PMCNTENSET), and Overflow Flag Status Register (PMOVSR)
	asm volatile ("mcr p15, 0, %0, c9, c12, 0\n\t" :: "r"(0x00000017));
	asm volatile ("mcr p15, 0, %0, c9, c12, 1\n\t" :: "r"(0x8000003f));
	asm volatile ("mcr p15, 0, %0, c9, c12, 3\n\t" :: "r"(0x8000003f));
	
	// 3. Disable Interrupt Enable Clear Register
	asm volatile("mcr p15, 0, %0, c9, c14, 2\n\t" :: "r" (~0));

	// 4. Read how many event counters exist
	asm volatile("mrc p15, 0, %0, c9, c12, 0\n\t" : "=r" (v)); // Read PMCR
	printk("pmon_init(): have %d configurable event counters.\n", (v >> 11) & 0x1f);

	// 5. Set event counter registers
	// ***** YOUR CODE STARTS HERE *****

	//write pmselr
	asm volatile("mcr p15, 0, %0, c9, c12, 5\n\t" :: "r" (0x0));
	//write pmxevtyper
	asm volatile("mcr p15, 0, %0, c9, c13, 1\n\t" :: "r" (0x04));
	//read pmxevcntr
	asm volatile("mrc p15, 0, %0, c9, c13, 2\n\t" : "=r" (v));
	printk("pmon_init(): First event counter has %d 0x04 events.\n", (v) & 0x1f);

	//write pmselr
	asm volatile("mcr p15, 0, %0, c9, c12, 5\n\t" :: "r" (0x1));
	//write pmxevtyper
	asm volatile("mcr p15, 0, %0, c9, c13, 1\n\t" :: "r" (0x03));
	//read pmxevcntr
	asm volatile("mrc p15, 0, %0, c9, c13, 2\n\t" : "=r" (v));
	printk("pmon_init(): Second event counter has %d 0x03 events.\n", (v) & 0x1f);

	//write pmselr
	asm volatile("mcr p15, 0, %0, c9, c12, 5\n\t" :: "r" (0x2));
	//write pmxevtyper
	asm volatile("mcr p15, 0, %0, c9, c13, 1\n\t" :: "r" (0x16));
	//read pmxevcntr
	asm volatile("mrc p15, 0, %0, c9, c13, 2\n\t" : "=r" (v));
	printk("pmon_init(): Third event counter has %d 0x16 events.\n", (v) & 0x1f);

	//write pmselr
	asm volatile("mcr p15, 0, %0, c9, c12, 5\n\t" :: "r" (0x3));
	//write pmxevtyper
	asm volatile("mcr p15, 0, %0, c9, c13, 1\n\t" :: "r" (0x17));
	//read pmxevcntr
	asm volatile("mrc p15, 0, %0, c9, c13, 2\n\t" : "=r" (v));
	printk("pmon_init(): Fourth event counter has %d 0x17 events.\n", (v) & 0x1f);

	//write pmselr
	asm volatile("mcr p15, 0, %0, c9, c12, 5\n\t" :: "r" (0x4));
	//write pmxevtyper
	asm volatile("mcr p15, 0, %0, c9, c13, 1\n\t" :: "r" (0xC9));
	//read pmxevcntr
	asm volatile("mrc p15, 0, %0, c9, c13, 2\n\t" : "=r" (v));
	printk("pmon_init(): Fifth event counter has %d 0xC9 events.\n", (v) & 0x1f);

	//write pmselr
	asm volatile("mcr p15, 0, %0, c9, c12, 5\n\t" :: "r" (0x5));
	//write pmxevtyper
	asm volatile("mcr p15, 0, %0, c9, c13, 1\n\t" :: "r" (0xCC));
	//read pmxevcntr
	asm volatile("mrc p15, 0, %0, c9, c13, 2\n\t" : "=r" (v));
	printk("pmon_init(): Sixth event counter has %d 0xCC events.\n", (v) & 0x1f);


	// ***** YOUR CODE ENDS HERE *******
	return 0;
}

void cleanup_module(void) {
	printk("GOODBYE, PMU Off\n");
}
