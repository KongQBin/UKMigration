/*
 * libc/stdlib/abs.c
 */

#include <xboot/module.h>
#include <stdlib.h>

int abs(int n)
{
	return ((n < 0) ? -n : n);
}
EXPORT_SYMBOL(abs);
