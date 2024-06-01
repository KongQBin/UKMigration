#include <common.h>
#include <command.h>

int
do_name (cmd_tbl_t *cmdtp, int flag, int argc, char *argv[])
{
	printf ("\n%s\n", "KongBin,2024.06.01");
	return 0;
}

U_BOOT_CMD(
	name,	1,		1,	do_name,
	"version - print monitor version\n",
	NULL
);
