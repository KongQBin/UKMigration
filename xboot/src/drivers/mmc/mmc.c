/*
 * drivers/mmc/mmc.c
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
#include <string.h>
#include <malloc.h>
#include <xboot/initcall.h>
#include <xboot/list.h>
#include <xboot/proc.h>
#include <xboot/printk.h>
#include <xboot/device.h>
#include <xboot/blkdev.h>
#include <xboot/ioctl.h>
#include <mmc/mmc_host.h>
#include <mmc/mmc_card.h>
#include <mmc/mmc.h>

/*
 * initial mmc card
 */
static __init void mmc_card_init(void)
{
	/*
	 * probe all mmc card
	 */
	mmc_card_probe();
}

/*
 * remove mmc card
 */
static __exit void mmc_card_exit(void)
{
	/*
	 * remove all mmc card
	 */
	mmc_card_remove();
}

device_initcall(mmc_card_init);
device_exitcall(mmc_card_exit);
