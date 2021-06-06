/* SPDX-License-Identifier: (GPL-2.0+ OR MIT) */
/*
 * common/cmd_chipid.c
 *
 * Copyright (C) 2020 Amlogic, Inc. All rights reserved.
 *
 */

#include <common.h>
#include <command.h>
#include <asm/cpu_id.h>

static int do_chipid(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
	int i;
	uint8_t buff[16];
	char cpuid_buff[16 * 2 + 1] = {0};
	long lAddr1;
	char *end;

	printf("\nSerial\t\t: ");

	if (get_chip_id(&buff[0], sizeof(buff)) == 0) {
		for (i = 0; i < sizeof(buff); i++)
		{
			printf("%02x", buff[i]);
			sprintf(&cpuid_buff[i * 2], "%02x", buff[i]);
		}
		setenv("cpuid", cpuid_buff);

		if (argc > 1) {
			lAddr1 = simple_strtoul(argv[1], &end, 16);
			memcpy((void*)lAddr1, buff, 16);
		}
		printf("\n");
	}
	else
		printf("error\n");

	return 0;
}

U_BOOT_CMD(
	chipid,		2,	1,	do_chipid,
	"Print Chip ID",
	"    chipid [addr] - if addr then write chipid to memory at %addr"
);
