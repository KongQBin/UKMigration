/*
 * resource/res-led-console.c
 *
 * Copyright(c) 2007-2013 jianjun jiang <jerryjianjun@gmail.com>
 * official site: http://xboot.org
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 */


#include <xboot.h>
#include <types.h>
#include <io.h>
#include <xboot/log.h>
#include <xboot/printk.h>
#include <xboot/initcall.h>
#include <led/led.h>
#include <led/trigger.h>
#include <xboot/resource.h>
#include <s5pv210/reg-gpio.h>

/*
 * led trigger for console using gph2_5.
 */
static void led_gph2_5_init(void)
{
	/* set GPH2_5 output and pull up */
	writel(S5PV210_GPH2CON, (readl(S5PV210_GPH2CON) & ~(0xf<<20)) | (0x1<<20));
	writel(S5PV210_GPH2PUD, (readl(S5PV210_GPH2PUD) & ~(0x3<<10)) | (0x2<<10));
}

static void led_gph2_5_set(u8_t brightness)
{
	if(brightness)
		writel(S5PV210_GPH2DAT, (readl(S5PV210_GPH2DAT) & ~(0x1<<5)) | (0x1<<5));
	else
		writel(S5PV210_GPH2DAT, (readl(S5PV210_GPH2DAT) & ~(0x1<<5)) | (0x0<<5));
}

static struct led led_gph2_5 = {
	.name		= "led-gph2_5",
	.init		= led_gph2_5_init,
	.set		= led_gph2_5_set,
};

/*
 * the led-console resource.
 */
static struct resource led_console = {
	.name		= "led-console",
	.data		= &led_gph2_5,
};

static __init void dev_console_init(void)
{
	if(!register_resource(&led_console))
		LOG_E("failed to register resource '%s'", led_console.name);
}

static __exit void dev_console_exit(void)
{
	if(!unregister_resource(&led_console))
		LOG_E("failed to unregister resource '%s'", led_console.name);
}

core_initcall(dev_console_init);
core_exitcall(dev_console_exit);
