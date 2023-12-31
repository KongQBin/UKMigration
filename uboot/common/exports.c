#include <common.h>
#include <exports.h>

DECLARE_GLOBAL_DATA_PTR;

static void dummy(void)
{
}

unsigned long get_version(void)
{
	return XF_VERSION;
}

void jumptable_init (void)
{
	// 经查询 gd->jt 一直在作为左值，没有被使用过
	// 根据经验，这像是在初始化类似符号表的逻辑，可能有些特殊的板子会用吧
	int i;

	gd->jt = (void **) malloc (XF_MAX * sizeof (void *));
	for (i = 0; i < XF_MAX; i++)
		gd->jt[i] = (void *) dummy;

	gd->jt[XF_get_version] = (void *) get_version;
	gd->jt[XF_malloc] = (void *) malloc;
	gd->jt[XF_free] = (void *) free;
	gd->jt[XF_getenv] = (void *) getenv;
	gd->jt[XF_setenv] = (void *) setenv;
	gd->jt[XF_get_timer] = (void *) get_timer;
	gd->jt[XF_simple_strtoul] = (void *) simple_strtoul;
	gd->jt[XF_udelay] = (void *) udelay;
	gd->jt[XF_simple_strtol] = (void *) simple_strtol;
	gd->jt[XF_strcmp] = (void *) strcmp;
#if defined(CONFIG_I386) || defined(CONFIG_PPC)
	gd->jt[XF_install_hdlr] = (void *) irq_install_handler;
	gd->jt[XF_free_hdlr] = (void *) irq_free_handler;
#endif	/* I386 || PPC */
#if defined(CONFIG_CMD_I2C)
	gd->jt[XF_i2c_write] = (void *) i2c_write;
	gd->jt[XF_i2c_read] = (void *) i2c_read;
#endif
}
