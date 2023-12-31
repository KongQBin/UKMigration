#ifndef __ARM32_IRQFLAGS_H__
#define __ARM32_IRQFLAGS_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <types.h>

#if __ARM_ARCH__ >= 6
/*
 * Enable IRQ
 */
static inline void arch_local_irq_enable(void)
{
	__asm__ __volatile__(
		"cpsie i"
		:
		:
		: "memory", "cc");
}

/*
 * Disable IRQ
 */
static inline void arch_local_irq_disable(void)
{
	__asm__ __volatile__(
		"cpsid i"
		:
		:
		: "memory", "cc");
}

/*
 * Save IRQ flags and disable IRQ
 */
static inline irq_flags_t arch_local_irq_save(void)
{
	irq_flags_t flags;

	__asm__ __volatile__(
		"mrs	%0, cpsr\n"
		"cpsid	i"
		: "=r" (flags)
		:
		: "memory", "cc");

	return flags;
}

/*
 * Restore IRQ flags
 */
static inline void arch_local_irq_restore(irq_flags_t flags)
{
	__asm__ __volatile__(
		"msr cpsr_c, %0"
		:
		: "r" (flags)
		: "memory", "cc");
}

/*
 * Save IRQ flags
 */
static inline irq_flags_t arch_local_save_flags(void)
{
	irq_flags_t flags;

	__asm__ __volatile__(
		"mrs %0, cpsr"
		: "=r" (flags)
	  	:
		: "memory", "cc");

	return flags;
}
#else
/*
 * Enable IRQ
 */
static inline void arch_local_irq_enable(void)
{
	irq_flags_t temp;

	__asm__ __volatile__(
		"mrs %0, cpsr\n"
		"bic %0, %0, #(1<<7)\n"
		"msr cpsr_c, %0"
		: "=r" (temp)
		:
		: "memory", "cc");
}

/*
 * Disable IRQ
 */
static inline void arch_local_irq_disable(void)
{
	irq_flags_t temp;

	__asm__ __volatile__(
		"mrs %0, cpsr\n"
		"orr %0, %0, #(1<<7)\n"
		"msr cpsr_c, %0"
		: "=r" (temp)
		:
		: "memory", "cc");
}

/*
 * Save IRQ flags and disable IRQ
 */
static inline irq_flags_t arch_local_irq_save(void)
{
	irq_flags_t flags, temp;

	__asm__ __volatile__(
		"mrs %0, cpsr\n"
		"orr %1, %0, #(1<<7)\n"
		"msr cpsr_c, %1"
		: "=r" (flags), "=r" (temp)
		:
		: "memory", "cc");

	return flags;
}

/*
 * Restore IRQ flags
 */
static inline void arch_local_irq_restore(irq_flags_t flags)
{
	__asm__ __volatile__(
		"msr cpsr_c, %0"
		:
		: "r" (flags)
		: "memory", "cc");
}

/*
 * Save IRQ flags
 */
static inline irq_flags_t arch_local_save_flags(void)
{
	irq_flags_t flags;

	__asm__ __volatile__(
		"mrs %0, cpsr"
		: "=r" (flags)
	  	:
		: "memory", "cc");

	return flags;
}
#endif

#define local_irq_enable()			do { arch_local_irq_enable(); } while(0)
#define local_irq_disable()			do { arch_local_irq_disable(); } while(0)
#define local_irq_save(flags)		do { flags = arch_local_irq_save(); } while(0)
#define local_irq_restore(flags)	do { arch_local_irq_restore(flags); } while(0)
#define local_save_flags(flags)		do { flags = arch_local_save_flags(); } while(0)

#ifdef __cplusplus
}
#endif

#endif /* __ARM32_IRQFLAGS_H__ */
