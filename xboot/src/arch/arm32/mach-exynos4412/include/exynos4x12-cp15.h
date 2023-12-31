#ifndef __EXYNOS4X12_CP15_H__
#define __EXYNOS4X12_CP15_H__

#include <xboot.h>

void irq_enable(void);
void irq_disable(void);
void fiq_enable(void);
void fiq_disable(void);
void icache_enable(void);
void icache_disable(void);
void dcache_enable(void);
void dcache_disable(void);
void mmu_enable(void);
void mmu_disable(void);
void vic_enable(void);
void vic_disable(void);
void branch_enable(void);
void branch_disable(void);

#endif /* __EXYNOS4X12_CP15_H__ */
