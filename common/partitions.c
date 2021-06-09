#include <common.h>
#include <malloc.h>
#include <linux/err.h>
#include <partition_table.h>
#include <linux/libfdt.h>
//#include <asm/arch/bl31_apis.h>
//#include <amlogic/aml_efuse.h>

#ifdef CONFIG_MULTI_DTB
	extern unsigned long get_multi_dt_entry(unsigned long fdt_addr);
#endif

struct partitions_data{
	int nr;
	struct partitions *parts;
};

struct partitions *part_table = NULL;
static int parts_total_num;
int has_boot_slot = 0;
int has_system_slot = 0;


int get_partitions_table(struct partitions **table)
{
	int ret = 0;
	if (part_table && parts_total_num) {
		*table = part_table;
		ret = parts_total_num;
	}
	return ret;
}
int get_partition_count(void)
{
	return parts_total_num;
}
struct partitions *get_partitions(void)
{
	return part_table;
}



void free_partitions(void)
{
	if (part_table)
		free(part_table);
	part_table = NULL;
}

#ifndef IS_FEAT_BOOT_VERIFY
#define IS_FEAT_BOOT_VERIFY() 0
#endif// #ifndef IS_FEAT_BOOT_VERIFY

/*
  return 0 if dts is valid
  other value are falure.
*/
int check_valid_dts(unsigned char *buffer)
{
	int ret = -__LINE__;
	char *dt_addr;

#ifdef CONFIG_MULTI_DTB
	dt_addr = (char *)get_multi_dt_entry((unsigned long)buffer);
#else
	dt_addr = (char *)buffer;
#endif
	pr_debug("start dts,buffer=%p,dt_addr=%p\n", buffer, dt_addr);
	ret = fdt_check_header(dt_addr);
	if ( ret < 0 )
		printf("%s: %s\n",__func__,fdt_strerror(ret));
	/* fixme, is it 0 when ok? */
	return ret;
}

int get_partition_from_dts(unsigned char *buffer)
{
	char *dt_addr;
	int nodeoffset,poffset=0;
	int *parts_num;
	char propname[8];
	const uint32_t *phandle;
	const char *uname;
	const char *usize;
	const char *umask;
	int index;
	int ret = -1;

	if ( buffer == NULL)
		goto _err;

	ret = check_valid_dts(buffer);
	pr_debug("%s() %d: ret %d\n",__func__, __LINE__, ret);
	if ( ret < 0 )
	{
		printf("%s() %d: ret %d\n",__func__, __LINE__, ret);
		goto _err;
	}
#ifdef CONFIG_MULTI_DTB
	dt_addr = (char *)get_multi_dt_entry((unsigned long)buffer);
#else
	dt_addr = (char *)buffer;
#endif
	nodeoffset = fdt_path_offset(dt_addr, "/partitions");
	if (nodeoffset < 0)
	{
		printf("%s: not find /partitions node %s.\n",__func__,fdt_strerror(nodeoffset));
		ret = -1;
		goto _err;
	}
	parts_num = (int *)fdt_getprop(dt_addr, nodeoffset, "parts", NULL);
	pr_debug("parts: %d\n",be32_to_cpup((u32*)parts_num));

	if (parts_num > 0)
	{
		part_table = (struct partitions *)malloc(sizeof(struct partitions)*(be32_to_cpup((u32*)parts_num)));
		if (!part_table) {
			printk("%s part_table alloc _err\n",__func__);
			//kfree(data);
			return -1;
		}
		memset(part_table, 0, sizeof(struct partitions)*(be32_to_cpup((u32*)parts_num)));
		parts_total_num = be32_to_cpup((u32*)parts_num);
	}
	for (index = 0; index < be32_to_cpup((u32*)parts_num); index++)
	{
		sprintf(propname,"part-%d", index);

		phandle = fdt_getprop(dt_addr, nodeoffset, propname, NULL);
		if (!phandle) {
			printf("don't find  match part-%d\n",index);
			goto _err;
		}
		if (phandle) {
			poffset = fdt_node_offset_by_phandle(dt_addr, be32_to_cpup((u32*)phandle));
			if (!poffset) {
				printf("%s:%d,can't find device node\n",__func__,__LINE__);
				goto _err;
			}
		}
		uname = fdt_getprop(dt_addr, poffset, "pname", NULL);
		//printf("%s:%d  uname: %s\n",__func__,__LINE__, uname);
		/* a string but not */
		usize = fdt_getprop(dt_addr, poffset, "size", NULL);
		//printf("%s:%d size: 0x%x  0x%x\n",__func__,__LINE__, be32_to_cpup((u32*)usize), be32_to_cpup((((u32*)usize)+1)));
		umask = fdt_getprop(dt_addr, poffset, "mask", NULL);
		//printf("%s:%d mask: 0x%x\n",__func__,__LINE__, be32_to_cpup((u32*)umask));
		/* fill parition table */
		if (uname != NULL)
			memcpy(part_table[index].name, uname, strlen(uname));
		part_table[index].size = ((unsigned long)be32_to_cpup((u32*)usize) << 32) | (unsigned long)be32_to_cpup((((u32*)usize)+1));
		part_table[index].mask_flags = be32_to_cpup((u32*)umask);
		pr_debug("%02d:%10s\t%016llx %01x\n", index, uname, part_table[index].size, part_table[index].mask_flags);

		if (strcmp(uname, "boot_a") == 0) {
			has_boot_slot = 1;
			printf("set has_boot_slot = 1\n");
		}
		else if (strcmp(uname, "boot") == 0) {
			has_boot_slot = 0;
			printf("set has_boot_slot = 0\n");
		}
		if (strcmp(uname, "system_a") == 0)
			has_system_slot = 1;
		else if (strcmp(uname, "system") == 0)
			has_system_slot = 0;
	}
	return 0;

_err:
	if (part_table != NULL) {
		free(part_table);
		part_table = NULL;
	}
	return ret;
}
