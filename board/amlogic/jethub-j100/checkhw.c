// SPDX-License-Identifier: GPL-2.0+
/*
 * Copyright (C) 2021 JetHome
 * Author: Vyacheslav Bocharov <devel@lexina.in>
 */

#include <common.h>
#include <dm.h>
#include <env.h>
#include <init.h>
#include <net.h>
#include <asm/io.h>
#include <asm/arch/gx.h>
#include <asm/arch/sm.h>
#include <asm/arch/eth.h>
#include <asm/arch/mem.h>

#ifdef CONFIG_MULTI_DTB
int checkhw(char * name)
{
        unsigned int ddr_size=0;
        char loc_name[64] = {0};
        int i;
        for (i=0; i<CONFIG_NR_DRAM_BANKS; i++) {
                ddr_size += gd->bd->bi_dram[i].size;
        }
#if defined(CONFIG_SYS_MEM_TOP_HIDE)
        ddr_size += CONFIG_SYS_MEM_TOP_HIDE;
#endif
        strcpy(loc_name, "axg_jethubj100_v1\0");
        switch (ddr_size) {

                case 0x20000000:
                case 0x40000000:
			strcpy(loc_name, "axg_jethubj100_v1\0");
                        break;

                default:
                        strcpy(loc_name, "axg_unsupport");
                        break;
        }
        strcpy(name, loc_name);
        env_set("aml_dt", loc_name);
        return 0;
}
#endif
