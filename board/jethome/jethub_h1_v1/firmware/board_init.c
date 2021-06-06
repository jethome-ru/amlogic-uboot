/* SPDX-License-Identifier: (GPL-2.0+ OR MIT) */
/*
 *
 * Copyright (C) 2020 Amlogic, Inc. All rights reserved.
 * Copyright (C) 2021 JetHome. All rights reserved.
 *
 */

#include "power.c"

/* bl2 customer code */
void board_init(void)
{
	power_init(0);
}
