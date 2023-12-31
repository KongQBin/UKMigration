/*
 * libc/stdlib/atoll.c
 */

#include <xboot/module.h>
#include <stddef.h>
#include <stdlib.h>

long long atoll(const char * nptr)
{
	return (long long)strtoll(nptr, NULL, 10);
}
EXPORT_SYMBOL(atoll);
