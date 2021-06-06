/* SPDX-License-Identifier: (GPL-2.0+ OR MIT) */
/*
 *
 * Copyright (C) 2020 Amlogic, Inc. All rights reserved.
 * Copyright (C) 2021 JetHome. All rights reserved.
 *
 */

#ifndef __AXG_S400_V1_H__
#define __AXG_S400_V1_H__

#include <asm/arch/cpu.h>


#define CONFIG_SYS_GENERIC_BOARD  1
#ifndef CONFIG_AML_MESON
#warning "include warning"
#endif

/*
 * platform power init config
 */
#define CONFIG_PLATFORM_POWER_INIT
#define CONFIG_VCCK_INIT_VOLTAGE	1100
#define CONFIG_VDDEE_INIT_VOLTAGE	950		// voltage for power up
#define CONFIG_VDDEE_SLEEP_VOLTAGE	 810		// voltage for suspend

#define CONFIG_CMDLINE_EDITING
#define CONFIG_AUTO_COMPLETE
#define CONFIG_CMD_SETEXPR

/* SMP Definitinos */
#define CPU_RELEASE_ADDR		secondary_boot_func

/* config saradc*/
#define CONFIG_CMD_SARADC 1

/* command watchdog */
#define CONFIG_CMD_WATCHDOG 1

/*config a/b system*/
#define CONFIG_AB_SYSTEM 1

/* support ext4*/
#define CONFIG_CMD_EXT4 1

/* Bootloader Control Block function
   That is used for recovery and the bootloader to talk to each other
  */
#define CONFIG_BOOTLOADER_CONTROL_BLOCK

/* Serial config */
#define CONFIG_CONS_INDEX 2
#define CONFIG_BAUDRATE  115200
#define CONFIG_AML_MESON_SERIAL   1
#define CONFIG_SERIAL_MULTI		1

#define CONFIG_BT_WAKEUP
//#define CONFIG_WIFI_WAKEUP

//Enable ir remote wake up for bl30
#define CONFIG_IR_REMOTE_POWER_UP_KEY_CNT 5
#define CONFIG_IR_REMOTE_POWER_UP_KEY_VAL1 0xef10fe01 //amlogic tv ir --- power
#define CONFIG_IR_REMOTE_POWER_UP_KEY_VAL2 0XBB44FB04 //amlogic tv ir --- ch+
#define CONFIG_IR_REMOTE_POWER_UP_KEY_VAL3 0xF20DFE01 //amlogic tv ir --- ch-
#define CONFIG_IR_REMOTE_POWER_UP_KEY_VAL4 0xFFFFFFFF
#define CONFIG_IR_REMOTE_POWER_UP_KEY_VAL5 0xe51afb04
#define CONFIG_IR_REMOTE_POWER_UP_KEY_VAL6 0xFFFFFFFF
#define CONFIG_IR_REMOTE_POWER_UP_KEY_VAL7 0xFFFFFFFF
#define CONFIG_IR_REMOTE_POWER_UP_KEY_VAL8 0xFFFFFFFF
#define CONFIG_IR_REMOTE_POWER_UP_KEY_VAL9 0xFFFFFFFF

/*config the default parameters for adc power key*/
#define CONFIG_ADC_POWER_KEY_CHAN   0  /*channel range: 0-7*/
#define CONFIG_ADC_POWER_KEY_VAL    0  /*sample value range: 0-1023*/

/* args/envs */
#define CONFIG_SYS_MAXARGS  64

#define CONFIG_EXTRA_ENV_SETTINGS \
        "preloadaddr=0x4000000\0"\
        "mmc_list=1\0"\
        "mmc_part_list=0x4 0x5 0x6 0x7 0x8 0x9 0xa\0"\
        "sdc_list=0\0"\
        "sdc_part_list=1\0"\
        "usb_list=0 1\0"\
        "usb_part_list=1\0"\
        "boot_order=usb mmc\0"\
        "boot_scripts=boot.scr\0"\
        "boot_mmc="                                        \
                "setenv devtype mmc; "                        \
                "for n in ${mmc_list}; do "                \
                        "setenv devnum ${n}; "                \
                        "for k in ${mmc_part_list}; do " \
                                "setenv devpart ${k}; " \
                                "run boot_attempt; "                \
                        "done;" \
                "done;\0"\
        "boot_usb="                                        \
                "usb start; "                                \
                "setenv devtype usb; "                        \
                "for n in ${usb_list}; do "                \
                        "setenv devnum ${n}; "                \
                        "for k in ${usb_part_list}; do " \
                                "setenv devpart ${k}; " \
                                "run boot_attempt; "                \
                        "done;" \
                "done;\0"\
        "boot_default="                                        \
                "for type in ${boot_order}; do "        \
                        "run boot_${type}; "                \
                "done\0"\
        "boot_attempt="                                        \
                "for script in ${boot_scripts}; do "        \
                        "echo Attempting fetch ${script} in ${devtype} ${devnum}:${devpart}...; "        \
                        "if fatload ${devtype} ${devnum}:${devpart} ${preloadaddr} ${script}; then "\
                                "autoscr ${preloadaddr}; "        \
                        "elif ext4load ${devtype} ${devnum}:${devpart} ${preloadaddr} ${script}; then "\
                                "autoscr ${preloadaddr}; "        \
                        "fi;" \
                "done;\0" \
        "firstboot=1\0"\
        "upgrade_step=0\0"\
        "jtag=disable\0"\
        "loadaddr=1080000\0"\
        "dtb_mem_addr=0x1000000\0" \
        "usb_burning=update 1000\0" \
        "fdt_high=0x20000000\0"\
        "try_auto_burn=update 700 750;\0"\
        "sdcburncfg=aml_sdc_burn.ini\0"\
        "sdc_burning=sdc_burn ${sdcburncfg}\0"\
        "wipe_data=successful\0"\
        "wipe_cache=successful\0"\
        "EnableSelinux=enforcing\0" \
        "recovery_part=recovery\0"\
        "recovery_offset=0\0"\
        "active_slot=normal\0"\
        "boot_part=boot\0"\
        "lock=10001000\0"\
        "fs_type=""rootfstype=ramfs""\0"\
        "armbian_mmc_dev=1\0"\
        "armbian_rootfs_part=4\0"\
        "armbian_partitions=4M(bootloader),64M@36M(reserved),8M@116M(env),-@132M(rootfs)\0"\
        "armbian_kernel_addr_r=0x11000000\0"\
        "armbian_ramdisk_addr_r=0x13000000\0"\
        "armbian_LINUX=/boot/Image\0"\
        "armbian_INITRD=/boot/uInitrd\0"\
        "armbian_FDT=/boot/dtb/amlogic/meson-axg-jethome-jethub-j100.dtb\0"\
        "armbian_bootargs="\
            "setenv bootargs root=/dev/mmcblk${armbian_mmc_dev}p${armbian_rootfs_part} blkdevparts=mmcblk${armbian_mmc_dev}:${armbian_partitions} rootflags=data=writeback rw console=ttyAML0,115200n8 console=serial no_console_suspend consoleblank=0 fsck.fix=yes fsck.repair=yes net.ifnames=0; "\
            "\0"\
        "armbian_addids="\
            "if printenv mac; then "\
              "setenv bootargs ${bootargs} mac=${mac}; "\
            "fi; "\
            "if printenv usid; then "\
              "setenv bootargs ${bootargs} usid=${usid}; "\
            "fi; "\
            "if printenv serial; then "\
              "setenv bootargs ${bootargs} serial=${serial}; "\
            "fi; "\
            "if printenv cpuid; then "\
              "setenv bootargs ${bootargs} cpuid=${cpuid}; "\
            "fi;"\
            "\0"\
        "initargs="\
            "init=/sbin/init console=ttyS0,115200 no_console_suspend earlycon=aml_uart,0xff803000 ramoops.pstore_en=1 ramoops.record_size=0x8000 ramoops.console_size=0x4000 "\
            "\0"\
        "upgrade_check="\
            "echo upgrade_step=${upgrade_step}; "\
            "if itest ${upgrade_step} == 3; then "\
                "run storeargs; run update;"\
            "else fi;"\
            "\0"\
        "storeargs="\
            "setenv bootargs ${initargs} ${fs_type} jtag=${jtag}; "\
            "setenv bootargs ${bootargs} slot_suffix=${active_slot}; "\
            "\0"\
        "switch_bootmode="\
            "get_rebootmode;"\
            "if test ${reboot_mode} = factory_reset; then "\
                    "run recovery_from_flash;"\
            "else if test ${reboot_mode} = update; then "\
                    "run update;"\
            "else if test ${reboot_mode} = cold_boot; then "\
                /*"run try_auto_burn; "*/\
            "else if test ${reboot_mode} = fastboot; then "\
                "fastboot;"\
            "fi;fi;fi;fi;"\
            "\0" \
        "storeboot="\
            "get_system_as_root_mode;"\
            "echo system_mode: ${system_mode};"\
            "if test ${system_mode} = 1; then "\
                    "setenv fs_type ""ro rootwait skip_initramfs"";"\
                    "run storeargs;"\
            "fi;"\
            "usb_burn jethome_burn.ini; "\
            "mmc dev ${armbian_mmc_dev}; "\
            "run armbian_bootargs; "\
            "if ext4load mmc ${armbian_mmc_dev}:0x${armbian_rootfs_part} ${armbian_kernel_addr_r} ${armbian_LINUX}; then "\
                "if ext4load mmc ${armbian_mmc_dev}:0x${armbian_rootfs_part} ${armbian_ramdisk_addr_r} ${armbian_INITRD}; then "\
                    "if ext4load mmc ${armbian_mmc_dev}:0x${armbian_rootfs_part} ${dtb_mem_addr} ${armbian_FDT}; then "\
                        "fdt addr ${dtb_mem_addr}; "\
                        "run armbian_addids; "\
                        "booti ${armbian_kernel_addr_r} ${armbian_ramdisk_addr_r} ${dtb_mem_addr}; "\
                    "fi;"\
                "fi;"\
            "fi;"\
            "run boot_default;"\
            "\0"\
        "factory_reset_poweroff_protect="\
            "echo wipe_data=${wipe_data}; echo wipe_cache=${wipe_cache};"\
            "if test ${wipe_data} = failed; then "\
                "run storeargs;"\
                "if mmcinfo; then "\
                    "run recovery_from_sdcard;"\
                "fi;"\
                "if usb start 0; then "\
                    "run recovery_from_udisk;"\
                "fi;"\
                "run recovery_from_flash;"\
            "fi; "\
            "if test ${wipe_cache} = failed; then "\
                "run storeargs;"\
                "if mmcinfo; then "\
                    "run recovery_from_sdcard;"\
                "fi;"\
                "if usb start 0; then "\
                    "run recovery_from_udisk;"\
                "fi;"\
                "run recovery_from_flash;"\
            "fi; \0" \
         "update="\
            /*first usb burning, second sdc_burn, third ext-sd autoscr/recovery, last udisk autoscr/recovery*/\
            "run usb_burning; "\
            "run sdc_burning; "\
            "if mmcinfo; then "\
                "run recovery_from_sdcard;"\
            "fi;"\
            "if usb start 0; then "\
                "run recovery_from_udisk;"\
            "fi;"\
            "run recovery_from_flash;"\
            "\0"\
        "recovery_from_sdcard="\
            "if fatload mmc 0 ${loadaddr} aml_autoscript; then autoscr ${loadaddr}; fi;"\
            "if fatload mmc 0 ${loadaddr} recovery.img; then "\
                    "if fatload mmc 0 ${dtb_mem_addr} dtb.img; then echo sd dtb.img loaded; fi;"\
                    "wipeisb; "\
                    "bootm ${loadaddr};fi;"\
            "\0"\
        "recovery_from_udisk="\
            "if fatload usb 0 ${loadaddr} aml_autoscript; then autoscr ${loadaddr}; fi;"\
            "if fatload usb 0 ${loadaddr} recovery.img; then "\
                "if fatload usb 0 ${dtb_mem_addr} dtb.img; then echo udisk dtb.img loaded; fi;"\
                "wipeisb; "\
                "bootm ${loadaddr};fi;"\
            "\0"\
        "recovery_from_flash="\
            "setenv bootargs ${bootargs} aml_dt=${aml_dt} recovery_part={recovery_part} recovery_offset={recovery_offset};"\
            "if imgread kernel ${recovery_part} ${loadaddr} ${recovery_offset}; then wipeisb; bootm ${loadaddr}; fi;"\
            "\0"\
        "armbian_keyman="\
            "if keyman init 0x1234; then "\
                "keyman read usid ${loadaddr} str; "\
                "if keyman read mac ${loadaddr} str; then "\
                    "setenv ethaddr ${mac};"\
                "fi;"\
                "chipid; "\
                "keyman read serial ${loadaddr} str; "\
                "saveenv; "\
            "fi;"\
            "\0"\
        "bcb_cmd="\
            "get_avb_mode;"\
            "get_valid_slot;"\
            "\0"\
        "upgrade_key="\
            "if gpio input GPIOAO_3; then "\
                "echo detect upgrade key; run update;"\
            "fi;"\
            "\0"\
	"irremote_update="\
		"if irkey 2500000 0xe31cfb04 0xb748fb04; then "\
			"echo read irkey ok!; " \
		"if itest ${irkey_value} == 0xe31cfb04; then " \
			"run update;" \
		"else if itest ${irkey_value} == 0xb748fb04; then " \
			"run update;\n" \
			"fi;fi;" \
		"fi;\0" \


#define CONFIG_PREBOOT  \
            "run armbian_keyman; "\
            "run bcb_cmd; "\
            "run factory_reset_poweroff_protect;"\
            "run upgrade_check;"\
            "run storeargs;"\
            "run switch_bootmode;"
#define CONFIG_BOOTCOMMAND "run storeboot"

//#define CONFIG_ENV_IS_NOWHERE  1
#define CONFIG_ENV_SIZE   (64*1024)
#define CONFIG_FIT 1
#define CONFIG_OF_LIBFDT 1
#define CONFIG_ANDROID_BOOT_IMAGE 1
#define CONFIG_ANDROID_IMG 1
#define CONFIG_SYS_BOOTM_LEN (64<<20) /* Increase max gunzip size*/

/* cpu */
#define CONFIG_CPU_CLK					1200 //MHz. Range: 600-1800, should be multiple of 24

/* ddr */
#define CONFIG_DDR_SIZE					0 //MB //0 means ddr size auto-detect

/* IMPORTANT
 *    DDR clk <= 400MHz, please enable CONFIG_DDR_PLL_BYPASS blow
 *    DDR clk > 400MHz, please disable CONFIG_DDR_PLL_BYPASS blow
 */
#define CONFIG_DDR_CLK					912  //MHz, Range: 200-1200, should be multiple of 24
#define CONFIG_DDR4_CLK					912  //MHz, this is for same board with DDR4 chip

#define CONFIG_NR_DRAM_BANKS			1
/* DDR type setting
 *    CONFIG_DDR_TYPE_LPDDR3   : LPDDR3
 *    CONFIG_DDR_TYPE_DDR3     : DDR3
 *    CONFIG_DDR_TYPE_DDR4     : DDR4
 *    CONFIG_DDR_TYPE_AUTO     : DDR3/DDR4 auto detect */
#define CONFIG_DDR_TYPE					CONFIG_DDR_TYPE_AUTO
/* DDR channel setting, please refer hardware design.
 *    CONFIG_DDR0_16BIT        : DDR0 16bit mode
 *    CONFIG_DDR0_16BIT_2      : DDR0 16bit mode, 2ranks
 *    CONFIG_DDR_CHL_AUTO      : auto detect RANK0 / RANK0+1 */
#define CONFIG_DDR_CHANNEL_SET			CONFIG_DDR0_16BIT
/* ddr functions */
#define CONFIG_DDR_FULL_TEST			0 //0:disable, 1:enable. ddr full test
#define CONFIG_CMD_DDR_D2PLL			0 //0:disable, 1:enable. d2pll cmd
#define CONFIG_CMD_DDR_TEST				0 //0:disable, 1:enable. ddrtest cmd
#define CONFIG_DDR_LOW_POWER			1 //0:disable, 1:enable. ddr clk gate for lp
#define CONFIG_DDR_ZQ_PD				0 //0:disable, 1:enable. ddr zq power down
#define CONFIG_DDR_USE_EXT_VREF			0 //0:disable, 1:enable. ddr use external vref
#define CONFIG_DDR4_TIMING_TEST			0 //0:disable, 1:enable. ddr4 timing test function
#define CONFIG_DDR_PLL_BYPASS			0 //0:disable, 1:enable. ddr pll bypass function
#define CONFIG_DDR_FUNC_PRINT_WINDOW	0 //0:disable, 1:enable. print ddr training window

/* storage: emmc/nand/sd */
#define	CONFIG_STORE_COMPATIBLE 1
/*
*				storage
*		|---------|---------|
*		|					|
*		emmc<--Compatible-->nand
*					|-------|-------|
*					|				|
*					MTD<-Exclusive->NFTL
*/
/* axg only support slc nand */
/* swither for mtd nand which is for slc only. */
/* support for mtd */
//#define CONFIG_AML_MTD 1
/* support for nftl */
//#define CONFIG_AML_NAND	1

#if defined(CONFIG_AML_NAND) && defined(CONFIG_AML_MTD)
#error CONFIG_AML_NAND/CONFIG_AML_MTD can not support at the sametime;
#endif

#ifdef CONFIG_AML_MTD

/* #define CONFIG_ENV_IS_IN_NAND 1 */
#ifdef CONFIG_ENV_IS_IN_NAND
#define CONFIG_ENV_OFFSET 0
#ifdef CONFIG_ENV_SIZE
#undef CONFIG_ENV_SIZE
/*
 *The env size must be an integer
 *multiple of the block size
 */
#define CONFIG_ENV_SIZE (128*1024)
#endif
#endif



/* bootlaoder is construct by bl2 and fip
 * when DISCRETE_BOOTLOADER is enabled, bl2 & fip
 * will not be stored continuously, and nand layout
 * would be bl2|rsv|fip|normal, but not
 * bl2|fip|rsv|noraml anymore
 */
#define CONFIG_DISCRETE_BOOTLOADER

#ifdef  CONFIG_DISCRETE_BOOTLOADER
#define CONFIG_TPL_SIZE_PER_COPY          0x200000
#define CONFIG_TPL_COPY_NUM               4
#define CONFIG_TPL_PART_NAME              "tpl"
/* for bl2, restricted by romboot */
#define CONFIG_BL2_COPY_NUM               8
#endif /* CONFIG_DISCRETE_BOOTLOADER */

#define CONFIG_CMD_NAND 1
#define CONFIG_MTD_DEVICE y
/* mtd parts of ourown.*/
#define CONFIFG_AML_MTDPART	1
/* mtd parts by env default way.*/
/*
#define MTDIDS_NAME_STR		"aml_nand.0"
#define MTDIDS_DEFAULT		"nand1=" MTDIDS_NAME_STR
#define MTDPARTS_DEFAULT	"mtdparts=" MTDIDS_NAME_STR ":" \
					"3M@8192K(logo),"	\
					"10M(recovery),"	\
					"8M(kernel),"	\
					"40M(rootfs),"	\
					"-(data)"
*/
#define CONFIG_CMD_UBI
#define CONFIG_CMD_UBIFS
#define CONFIG_RBTREE
#define CONFIG_CMD_NAND_TORTURE 1
#define CONFIG_CMD_MTDPARTS   1
#define CONFIG_MTD_PARTITIONS 1
#define CONFIG_SYS_MAX_NAND_DEVICE  2
#define CONFIG_SYS_NAND_BASE_LIST   {0}
#endif
/* endof CONFIG_AML_MTD */
#define		CONFIG_AML_SD_EMMC 1
#ifdef		CONFIG_AML_SD_EMMC
	#define 	CONFIG_GENERIC_MMC 1
	#define 	CONFIG_CMD_MMC 1
    #define     CONFIG_CMD_GPT 1
	#define	CONFIG_SYS_MMC_ENV_DEV 1
	#define CONFIG_EMMC_DDR52_EN 0
	#define CONFIG_EMMC_DDR52_CLK 35000000
#endif
/* storage macro checks */
#if defined(CONFIG_AML_MTD) && defined(CONFIG_AML_NAND)
#error mtd/nftl are mutually-exclusive, only 1 nand driver can be enabled.
#endif

#define 	CONFIG_ENV_OVERWRITE
#define 	CONFIG_CMD_SAVEENV

/* fixme, need fix*/

#if (defined(CONFIG_ENV_IS_IN_AMLNAND) || defined(CONFIG_ENV_IS_IN_MMC)) && defined(CONFIG_STORE_COMPATIBLE)
#error env in amlnand/mmc already be compatible;
#endif

#if defined(CONFIG_ENV_IS_IN_AMLNAND) && defined(CONFIG_ENV_IS_IN_NAND)
#error CONFIG_ENV_IS_IN_AMLNAND and CONFIG_ENV_IS_IN_NAND are not compatibility
#endif

#define		CONFIG_PARTITIONS 1
#define 	CONFIG_SYS_NO_FLASH  1
//#define     CONFIG_AML_GPT


/* vpu */
//#define CONFIG_AML_VPU 1
//#define CONFIG_VPU_CLK_LEVEL_DFT 3

/* DISPLAY & HDMITX */
//#define CONFIG_AML_HDMITX20 1
//#define CONFIG_AML_CANVAS 1
//#define CONFIG_AML_VOUT 1
//#define CONFIG_AML_OSD 1
//#define CONFIG_OSD_SCALE_ENABLE 0
//#define CONFIG_CMD_BMP 1

#if defined(CONFIG_AML_VOUT)
//#define CONFIG_AML_CVBS 1
#endif

//#define CONFIG_AML_LCD    1

/*#define CONFIG_AML_LCD_TV 1*/
//#define CONFIG_AML_LCD_TABLET 1

/* USB
 * Enable CONFIG_MUSB_HCD for Host functionalities MSC, keyboard
 * Enable CONFIG_MUSB_UDD for Device functionalities.
 */
/* #define CONFIG_MUSB_UDC		1 */
#define CONFIG_CMD_USB 1
#if defined(CONFIG_CMD_USB)
	#define CONFIG_GXL_XHCI_BASE            0xff500000
	#define CONFIG_GXL_USB_PHY2_BASE        0xffe09000
	#define CONFIG_GXL_USB_PHY3_BASE        0xffe09080
	#define CONFIG_USB_STORAGE      1
	#define CONFIG_USB_XHCI		1
	#define CONFIG_USB_XHCI_AMLOGIC_GXL 1
#endif //#if defined(CONFIG_CMD_USB)

#define CONFIG_TXLX_USB        1

//UBOOT fastboot config
#define CONFIG_CMD_FASTBOOT 1
#define CONFIG_FASTBOOT_FLASH_MMC_DEV 1
#ifdef CONFIG_AML_MTD
#define CONFIG_FASTBOOT_FLASH_NAND_DEV 1
#endif
#define CONFIG_FASTBOOT_FLASH 1
#define CONFIG_USB_GADGET 1
#define CONFIG_USBDOWNLOAD_GADGET 1
#define CONFIG_SYS_CACHELINE_SIZE 64
#define CONFIG_FASTBOOT_MAX_DOWN_SIZE	0xA000000
#define CONFIG_DEVICE_PRODUCT	"jethome_j100"

//UBOOT Facotry usb/sdcard burning config
#define CONFIG_AML_V2_FACTORY_BURN              1       //support facotry usb burning
#define CONFIG_AML_FACTORY_BURN_LOCAL_UPGRADE   1       //support factory sdcard burning
#define CONFIG_POWER_KEY_NOT_SUPPORTED_FOR_BURN 1       //There isn't power-key for factory sdcard burning
#define CONFIG_SD_BURNING_SUPPORT_UI            1       //Displaying upgrading progress bar when sdcard/udisk burning

#define CONFIG_AML_SECURITY_KEY                 1
#define CONFIG_UNIFY_KEY_MANAGE                 1

/* net */
#define CONFIG_CMD_NET   1
#if defined(CONFIG_CMD_NET)
	#define CONFIG_DESIGNWARE_ETH 1
	#define CONFIG_PHYLIB	1
	#define CONFIG_NET_MULTI 1
	#define CONFIG_CMD_PING 1
	#define CONFIG_CMD_DHCP 1
	#define CONFIG_CMD_RARP 1
	#define CONFIG_HOSTNAME        arm_gxbb
	#define CONFIG_ETHADDR         00:15:18:01:81:31   /* Ethernet address */
	#define CONFIG_IPADDR          10.18.9.97          /* Our ip address */
	#define CONFIG_GATEWAYIP       10.18.9.1           /* Our getway ip address */
	#define CONFIG_SERVERIP        10.18.9.113         /* Tftp server ip address */
	#define CONFIG_NETMASK         255.255.255.0
#endif /* (CONFIG_CMD_NET) */

/* other devices */
/* I2C DM driver*/
//#define CONFIG_DM_I2C

#if defined(CONFIG_DM_I2C)
#define CONFIG_SYS_I2C_MESON		1
#else
#define CONFIG_SYS_I2C_AML			1
#define CONFIG_SYS_I2C_SPEED		400000
#define CONFIG_I2C_MULTI_BUS 		1
#endif

#define CONFIG_EFUSE 1

/* #define CONFIG_SYS_I2C_AML_IS31F123XX 1 */

/* commands */
#define CONFIG_CMD_CACHE 1
#define CONFIG_CMD_BOOTI 1
#define CONFIG_CMD_EFUSE 1
#define CONFIG_CMD_I2C 1
#define CONFIG_CMD_MEMORY 1
#define CONFIG_CMD_FAT 1
#define CONFIG_CMD_GPIO 1
#define CONFIG_CMD_RUN
#define CONFIG_CMD_REBOOT 1
#define CONFIG_CMD_ECHO 1
#define CONFIG_CMD_JTAG	1
#define CONFIG_CMD_AUTOSCRIPT 1
#define CONFIG_CMD_MISC 1

/*file system*/
#define CONFIG_DOS_PARTITION 1
#define CONFIG_EFI_PARTITION 1
#define CONFIG_AML_PARTITION 1
#define CONFIG_MMC 1
#define CONFIG_FS_FAT 1
#define CONFIG_FS_EXT4 1
#define CONFIG_LZO 1

/* Cache Definitions */
//#define CONFIG_SYS_DCACHE_OFF
//#define CONFIG_SYS_ICACHE_OFF

/* other functions */
#define CONFIG_NEED_BL301	1
#define CONFIG_NEED_BL32	1
#define CONFIG_CMD_RSVMEM	1
#define CONFIG_FIP_IMG_SUPPORT	1
#define CONFIG_BOOTDELAY	1
#define CONFIG_SYS_LONGHELP 1
#define CONFIG_CMD_MISC     1
#define CONFIG_CMD_ITEST    1
#define CONFIG_CMD_CPU_TEMP 1
#define CONFIG_SYS_MEM_TOP_HIDE 0
#define CONFIG_MULTI_DTB	1

#define CONFIG_CMD_CHIPID 1

/* debug mode defines */
//#define CONFIG_DEBUG_MODE			1
#ifdef CONFIG_DEBUG_MODE
#define CONFIG_DDR_CLK_DEBUG		636
#define CONFIG_CPU_CLK_DEBUG		600
#endif

//2017.04.26
//data compress for BL30,BL32,BL33
//compress ratio is about 50%, BL31 will take the decompress
//profit :
//          size : u-boot.bin 1.2MB -> 780KB
//          boot time : 140ms decrease
//default: enable the data compress feature
//to disable the data compress please just define followings
//#define CONFIG_AML_BL30_COMPRESS_DISABLE 1
//#define CONFIG_AML_BL32_COMPRESS_DISABLE 1
//#define CONFIG_AML_BL33_COMPRESS_DISABLE 1


//support secure boot
#define CONFIG_AML_SECURE_UBOOT   1

#if defined(CONFIG_AML_SECURE_UBOOT)

//for GXBB SRAM size limitation just disable NAND
//as the socket board default has no NAND
//#undef CONFIG_AML_NAND

//unify build for generate encrypted bootloader "u-boot.bin.encrypt"
#define CONFIG_AML_CRYPTO_UBOOT   0

//unify build for generate encrypted kernel image
//SRC : "board/amlogic/axg_s400_v1/boot.img"
//DST : "fip/boot.img.encrypt"
//#define CONFIG_AML_CRYPTO_IMG       1

#endif //CONFIG_AML_SECURE_UBOOT

#define CONFIG_SECURE_STORAGE 1

//build with uboot auto test
//#define CONFIG_AML_UBOOT_AUTO_TEST 1

//board customer ID
//#define CONFIG_CUSTOMER_ID  (0x6472616F624C4D41)

#if defined(CONFIG_CUSTOMER_ID)
  #undef CONFIG_AML_CUSTOMER_ID
  #define CONFIG_AML_CUSTOMER_ID  CONFIG_CUSTOMER_ID
#endif
#define ETHERNET_INTERNAL_PHY

//Ignore commands: 'store disprotect key', 'store erase key', 'keyman write <key> ...', 'keyunify write <key> ...'
//with successful result code
#define CONFIG_IGNORE_AML_KEY_WRITE 1

#endif

