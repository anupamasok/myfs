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
	{ 0x99ed5c78, __VMLINUX_SYMBOL_STR(module_layout) },
	{ 0x6506dc7d, __VMLINUX_SYMBOL_STR(kmem_cache_destroy) },
	{ 0xf77d324b, __VMLINUX_SYMBOL_STR(iget_failed) },
	{ 0x33d53fbc, __VMLINUX_SYMBOL_STR(kmalloc_caches) },
	{ 0x60a13e90, __VMLINUX_SYMBOL_STR(rcu_barrier) },
	{ 0xf75bb387, __VMLINUX_SYMBOL_STR(from_kuid_munged) },
	{ 0x44b1d426, __VMLINUX_SYMBOL_STR(__dynamic_pr_debug) },
	{ 0xb39af84a, __VMLINUX_SYMBOL_STR(mount_bdev) },
	{ 0x608ca1a7, __VMLINUX_SYMBOL_STR(from_kgid_munged) },
	{ 0x1bc84e15, __VMLINUX_SYMBOL_STR(make_kgid) },
	{ 0xab6981c4, __VMLINUX_SYMBOL_STR(__bread_gfp) },
	{ 0x27e1a049, __VMLINUX_SYMBOL_STR(printk) },
	{ 0x64372238, __VMLINUX_SYMBOL_STR(kmem_cache_free) },
	{ 0x37627b92, __VMLINUX_SYMBOL_STR(__brelse) },
	{ 0xeeab0dae, __VMLINUX_SYMBOL_STR(inode_init_once) },
	{ 0x90af41f3, __VMLINUX_SYMBOL_STR(kmem_cache_alloc) },
	{ 0x50ef55be, __VMLINUX_SYMBOL_STR(make_kuid) },
	{ 0x8ad3b77d, __VMLINUX_SYMBOL_STR(unlock_new_inode) },
	{ 0x3a1f90c9, __VMLINUX_SYMBOL_STR(kill_block_super) },
	{ 0xbdfb6dbb, __VMLINUX_SYMBOL_STR(__fentry__) },
	{ 0x3f79aa78, __VMLINUX_SYMBOL_STR(kmem_cache_alloc_trace) },
	{ 0xb0d332f2, __VMLINUX_SYMBOL_STR(kmem_cache_create) },
	{ 0xde0af099, __VMLINUX_SYMBOL_STR(register_filesystem) },
	{ 0x37a0cba, __VMLINUX_SYMBOL_STR(kfree) },
	{ 0x643e0ce5, __VMLINUX_SYMBOL_STR(call_rcu_sched) },
	{ 0xf569373e, __VMLINUX_SYMBOL_STR(sb_set_blocksize) },
	{ 0x686cb96e, __VMLINUX_SYMBOL_STR(d_make_root) },
	{ 0x243e8455, __VMLINUX_SYMBOL_STR(unregister_filesystem) },
	{ 0x3a74c908, __VMLINUX_SYMBOL_STR(iget_locked) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";


MODULE_INFO(srcversion, "87DC0148EF6B95F7050F07B");
