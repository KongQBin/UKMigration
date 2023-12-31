/*
 * libc/stdlib/atoi.c
 */

#include <xboot/module.h>
#include <stddef.h>
#include <stdlib.h>

int atoi(const char * nptr)
{
	return (int)strtol(nptr, NULL, 10);
}
EXPORT_SYMBOL(atoi);
