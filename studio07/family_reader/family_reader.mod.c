#include <linux/module.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

MODULE_INFO(vermagic, VERMAGIC_STRING);

__visible struct module __this_module
__attribute__((section(".gnu.linkonce.this_module"))) = {
	.name = KBUILD_MODNAME,
	.init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
	.exit = cleanup_module,
#endif
	.arch = MODULE_ARCH_INIT,
};

static const struct modversion_info ____versions[]
__used
__attribute__((section("__versions"))) = {
	{ 0x28f64ed0, __VMLINUX_SYMBOL_STR(module_layout) },
	{ 0x8e437fed, __VMLINUX_SYMBOL_STR(kobject_put) },
	{ 0x2e5810c6, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr1) },
	{ 0xb6039950, __VMLINUX_SYMBOL_STR(find_vpid) },
	{ 0xb1ad28e0, __VMLINUX_SYMBOL_STR(__gnu_mcount_nc) },
	{ 0x91715312, __VMLINUX_SYMBOL_STR(sprintf) },
	{ 0xed665e0e, __VMLINUX_SYMBOL_STR(kobject_create_and_add) },
	{ 0x27e1a049, __VMLINUX_SYMBOL_STR(printk) },
	{ 0x314b01f6, __VMLINUX_SYMBOL_STR(sysfs_create_group) },
	{ 0x1c162d6, __VMLINUX_SYMBOL_STR(pid_task) },
	{ 0x373db350, __VMLINUX_SYMBOL_STR(kstrtoint) },
	{ 0x3140f421, __VMLINUX_SYMBOL_STR(kernel_kobj) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";


MODULE_INFO(srcversion, "1FE2FEAE0A9D8A53C2CC3FC");
