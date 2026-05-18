# TP #4: Módulos de kernel

# 

Si ejecutamos las siguientes instrucciones:
```bash
cd part1
cd module
make
sudo insmod mimodulo.ko
sudo dmesg
```

Se obtiene la siguiente salida por la consola:

```bash
[    0.000000] Linux version 6.17.0-22-generic (buildd@lcy02-amd64-038) (x86_64-linux-gnu-gcc-13 (Ubuntu 13.3.0-6ubuntu2~24.04.1) 13.3.0, GNU ld (GNU Binutils for Ubuntu) 2.42) #22~24.04.1-Ubuntu SMP PREEMPT_DYNAMIC Thu Mar 26 15:25:54 UTC 2 (Ubuntu 6.17.0-22.22~24.04.1-generic 6.17.13)
[    0.000000] Command line: BOOT_IMAGE=/boot/vmlinuz-6.17.0-22-generic root=UUID=154e4895-b405-436c-ac14-63ad0b84fe4c ro quiet splash
[    0.000000] KERNEL supported cpus:
[    0.000000]   Intel GenuineIntel
[    0.000000]   AMD AuthenticAMD
[    0.000000]   Hygon HygonGenuine
[    0.000000]   Centaur CentaurHauls
[    0.000000]   zhaoxin   Shanghai  
[    0.000000] [Firmware Bug]: TSC doesn't count with P0 frequency!
[    0.000000] BIOS-provided physical RAM map:
[    0.000000] BIOS-e820: [mem 0x0000000000000000-0x000000000009fbff] usable
[    0.000000] BIOS-e820: [mem 0x000000000009fc00-0x000000000009ffff] reserved
[    0.000000] BIOS-e820: [mem 0x00000000000f0000-0x00000000000fffff] reserved
[    0.000000] BIOS-e820: [mem 0x0000000000100000-0x00000000dffeffff] usable
[    0.000000] BIOS-e820: [mem 0x00000000dfff0000-0x00000000dfffffff] ACPI data
[    0.000000] BIOS-e820: [mem 0x00000000fec00000-0x00000000fec00fff] reserved
[    0.000000] BIOS-e820: [mem 0x00000000fee00000-0x00000000fee00fff] reserved
[    0.000000] BIOS-e820: [mem 0x00000000fffc0000-0x00000000ffffffff] reserved
[    0.000000] BIOS-e820: [mem 0x0000000100000000-0x000000011fffffff] usable
[    0.000000] NX (Execute Disable) protection: active
[    0.000000] APIC: Static calls initialized
[    0.000000] SMBIOS 2.5 present.
[    0.000000] DMI: innotek GmbH VirtualBox/VirtualBox, BIOS VirtualBox 12/01/2006
[    0.000000] DMI: Memory slots populated: 0/0
[    0.000000] Hypervisor detected: KVM
[    0.000000] last_pfn = 0xe0000 max_arch_pfn = 0x400000000
[    0.000000] kvm-clock: Using msrs 4b564d01 and 4b564d00
[    0.000001] kvm-clock: using sched offset of 5337748540 cycles
[    0.000003] clocksource: kvm-clock: mask: 0xffffffffffffffff max_cycles: 0x1cd42e4dffb, max_idle_ns: 881590591483 ns
[    0.000006] tsc: Detected 3693.068 MHz processor
[    0.001241] e820: update [mem 0x00000000-0x00000fff] usable ==> reserved
[    0.001243] e820: remove [mem 0x000a0000-0x000fffff] usable
[    0.001246] last_pfn = 0x120000 max_arch_pfn = 0x400000000
[    0.001328] MTRR map: 3 entries (3 fixed + 0 variable; max 19), built from 8 variable MTRRs
[    0.001330] x86/PAT: Configuration [0-7]: WB  WC  UC- UC  WB  WP  UC- WT  
[    0.001381] CPU MTRRs all blank - virtualized system.
[    0.001383] last_pfn = 0xe0000 max_arch_pfn = 0x400000000
[    0.004105] found SMP MP-table at [mem 0x0009fbf0-0x0009fbff]
[    0.004263] RAMDISK: [mem 0x2ea41000-0x33517fff]
[    0.004550] ACPI: Early table checksum verification disabled
[    0.004552] ACPI: RSDP 0x00000000000E0000 000024 (v02 VBOX  )
[    0.004555] ACPI: XSDT 0x00000000DFFF0030 00003C (v01 VBOX   VBOXXSDT 00000001 ASL  00000061)
[    0.004558] ACPI: FACP 0x00000000DFFF00F0 0000F4 (v04 VBOX   VBOXFACP 00000001 ASL  00000061)
[    0.004561] ACPI: DSDT 0x00000000DFFF02F0 002353 (v02 VBOX   VBOXBIOS 00000002 VBOX 0002A122)
[    0.004563] ACPI: FACS 0x00000000DFFF0200 000040
[    0.004564] ACPI: FACS 0x00000000DFFF0200 000040
[    0.004566] ACPI: APIC 0x00000000DFFF0240 00005C (v02 VBOX   VBOXAPIC 00000001 ASL  00000061)
[    0.004567] ACPI: SSDT 0x00000000DFFF02A0 000045 (v01 VBOX   VBOXCPUT 00000002 VBOX 0002A122)
[    0.004568] ACPI: Reserving FACP table memory at [mem 0xdfff00f0-0xdfff01e3]
[    0.004569] ACPI: Reserving DSDT table memory at [mem 0xdfff02f0-0xdfff2642]
[    0.004570] ACPI: Reserving FACS table memory at [mem 0xdfff0200-0xdfff023f]
[    0.004570] ACPI: Reserving FACS table memory at [mem 0xdfff0200-0xdfff023f]
[    0.004571] ACPI: Reserving APIC table memory at [mem 0xdfff0240-0xdfff029b]
[    0.004571] ACPI: Reserving SSDT table memory at [mem 0xdfff02a0-0xdfff02e4]
[    0.005167] No NUMA configuration found
[    0.005168] Faking a node at [mem 0x0000000000000000-0x000000011fffffff]
[    0.005173] NODE_DATA(0) allocated [mem 0x11ffd12c0-0x11fffbfff]
[    0.005612] Zone ranges:
[    0.005613]   DMA      [mem 0x0000000000001000-0x0000000000ffffff]
[    0.005614]   DMA32    [mem 0x0000000001000000-0x00000000ffffffff]
[    0.005616]   Normal   [mem 0x0000000100000000-0x000000011fffffff]
[    0.005616]   Device   empty
[    0.005617] Movable zone start for each node
[    0.005618] Early memory node ranges
[    0.005618]   node   0: [mem 0x0000000000001000-0x000000000009efff]
[    0.005619]   node   0: [mem 0x0000000000100000-0x00000000dffeffff]
[    0.005620]   node   0: [mem 0x0000000100000000-0x000000011fffffff]
[    0.005620] Initmem setup node 0 [mem 0x0000000000001000-0x000000011fffffff]
[    0.005648] On node 0, zone DMA: 1 pages in unavailable ranges
[    0.006061] On node 0, zone DMA: 97 pages in unavailable ranges
[    0.113406] On node 0, zone Normal: 16 pages in unavailable ranges
[    0.114367] ACPI: PM-Timer IO Port: 0x4008
[    0.114544] IOAPIC[0]: apic_id 2, version 32, address 0xfec00000, GSI 0-23
[    0.114547] ACPI: INT_SRC_OVR (bus 0 bus_irq 0 global_irq 2 dfl dfl)
[    0.114549] ACPI: INT_SRC_OVR (bus 0 bus_irq 9 global_irq 9 low level)
[    0.114552] ACPI: Using ACPI (MADT) for SMP configuration information
[    0.114556] CPU topo: Max. logical packages:   1
[    0.114556] CPU topo: Max. logical dies:       1
[    0.114557] CPU topo: Max. dies per package:   1
[    0.114559] CPU topo: Max. threads per core:   1
[    0.114560] CPU topo: Num. cores per package:     2
[    0.114560] CPU topo: Num. threads per package:   2
[    0.114561] CPU topo: Allowing 2 present CPUs plus 0 hotplug CPUs
[    0.114646] PM: hibernation: Registered nosave memory: [mem 0x00000000-0x00000fff]
[    0.114658] PM: hibernation: Registered nosave memory: [mem 0x0009f000-0x000fffff]
[    0.114659] PM: hibernation: Registered nosave memory: [mem 0xdfff0000-0xffffffff]
[    0.114661] [mem 0xe0000000-0xfebfffff] available for PCI devices
[    0.114662] Booting paravirtualized kernel on KVM
[    0.114663] clocksource: refined-jiffies: mask: 0xffffffff max_cycles: 0xffffffff, max_idle_ns: 1910969940391419 ns
[    0.114669] setup_percpu: NR_CPUS:8192 nr_cpumask_bits:2 nr_cpu_ids:2 nr_node_ids:1
[    0.118065] percpu: Embedded 84 pages/cpu s221184 r8192 d114688 u1048576
[    0.118069] pcpu-alloc: s221184 r8192 d114688 u1048576 alloc=1*2097152
[    0.118070] pcpu-alloc: [0] 0 1 
[    0.118154] kvm-guest: PV spinlocks enabled
[    0.118156] PV qspinlock hash table entries: 256 (order: 0, 4096 bytes, linear)
[    0.118159] Kernel command line: BOOT_IMAGE=/boot/vmlinuz-6.17.0-22-generic root=UUID=154e4895-b405-436c-ac14-63ad0b84fe4c ro quiet splash
[    0.118202] Unknown kernel command line parameters "splash", will be passed to user space.
[    0.118219] random: crng init done
[    0.118219] printk: log buffer data + meta data: 262144 + 917504 = 1179648 bytes
[    0.124900] Dentry cache hash table entries: 524288 (order: 10, 4194304 bytes, linear)
[    0.128255] Inode-cache hash table entries: 262144 (order: 9, 2097152 bytes, linear)
[    0.128388] software IO TLB: area num 2.
[    0.186144] Fallback order for Node 0: 0 
[    0.186150] Built 1 zonelists, mobility grouping on.  Total pages: 1048462
[    0.186151] Policy zone: Normal
[    0.186163] mem auto-init: stack:all(zero), heap alloc:on, heap free:off
[    0.193845] SLUB: HWalign=64, Order=0-3, MinObjects=0, CPUs=2, Nodes=1
[    0.205607] ftrace: allocating 61414 entries in 240 pages
[    0.205609] ftrace: allocated 240 pages with 4 groups
[    0.206927] Dynamic Preempt: voluntary
[    0.207094] rcu: Preemptible hierarchical RCU implementation.
[    0.207095] rcu: 	RCU restricting CPUs from NR_CPUS=8192 to nr_cpu_ids=2.
[    0.207096] 	Trampoline variant of Tasks RCU enabled.
[    0.207097] 	Rude variant of Tasks RCU enabled.
[    0.207097] 	Tracing variant of Tasks RCU enabled.
[    0.207097] rcu: RCU calculated value of scheduler-enlistment delay is 100 jiffies.
[    0.207098] rcu: Adjusting geometry for rcu_fanout_leaf=16, nr_cpu_ids=2
[    0.207110] RCU Tasks: Setting shift to 1 and lim to 1 rcu_task_cb_adjust=1 rcu_task_cpu_ids=2.
[    0.207111] RCU Tasks Rude: Setting shift to 1 and lim to 1 rcu_task_cb_adjust=1 rcu_task_cpu_ids=2.
[    0.207112] RCU Tasks Trace: Setting shift to 1 and lim to 1 rcu_task_cb_adjust=1 rcu_task_cpu_ids=2.
[    0.210154] NR_IRQS: 524544, nr_irqs: 440, preallocated irqs: 16
[    0.210530] rcu: srcu_init: Setting srcu_struct sizes based on contention.
[    0.234624] Console: colour VGA+ 80x25
[    0.234627] printk: legacy console [tty0] enabled
[    0.234672] ACPI: Core revision 20250404
[    0.235968] APIC: Switch to symmetric I/O mode setup
[    0.242004] ..TIMER: vector=0x30 apic1=0 pin1=2 apic2=-1 pin2=-1
[    0.242119] clocksource: tsc-early: mask: 0xffffffffffffffff max_cycles: 0x6a7782233a6, max_idle_ns: 881590537829 ns
[    0.242124] Calibrating delay loop (skipped) preset value.. 7386.13 BogoMIPS (lpj=3693068)
[    0.243118] Last level iTLB entries: 4KB 512, 2MB 512, 4MB 256
[    0.243119] Last level dTLB entries: 4KB 2048, 2MB 2048, 4MB 1024, 1GB 0
[    0.243122] mitigations: Enabled attack vectors: user_kernel, user_user, guest_host, guest_guest, SMT mitigations: auto
[    0.243122] Speculative Return Stack Overflow: IBPB-extending microcode not applied!
[    0.243122] Speculative Return Stack Overflow: WARNING: See https://kernel.org/doc/html/latest/admin-guide/hw-vuln/srso.html for mitigation options.
[    0.243122] Transient Scheduler Attacks: Vulnerable: No microcode
[    0.243122] Spectre V2 : Mitigation: Retpolines
[    0.243122] Speculative Return Stack Overflow: Vulnerable: Safe RET, no microcode
[    0.243122] Spectre V1 : Mitigation: usercopy/swapgs barriers and __user pointer sanitization
[    0.243122] Spectre V2 : Spectre v2 / SpectreRSB: Filling RSB on context switch and VMEXIT
[    0.243122] active return thunk: srso_alias_return_thunk
[    0.243122] x86/fpu: Supporting XSAVE feature 0x001: 'x87 floating point registers'
[    0.243122] x86/fpu: Supporting XSAVE feature 0x002: 'SSE registers'
[    0.243122] x86/fpu: Supporting XSAVE feature 0x004: 'AVX registers'
[    0.243122] x86/fpu: xstate_offset[2]:  576, xstate_sizes[2]:  256
[    0.243122] x86/fpu: Enabled xstate features 0x7, context size is 832 bytes, using 'standard' format.
[    0.249617] Freeing SMP alternatives memory: 52K
[    0.249623] pid_max: default: 32768 minimum: 301
[    0.249696] LSM: initializing lsm=lockdown,capability,landlock,yama,apparmor,ima,evm
[    0.249712] landlock: Up and running.
[    0.249713] Yama: becoming mindful.
[    0.249907] AppArmor: AppArmor initialized
[    0.250195] Mount-cache hash table entries: 8192 (order: 4, 65536 bytes, linear)
[    0.250304] Mountpoint-cache hash table entries: 8192 (order: 4, 65536 bytes, linear)
[    0.366224] APIC calibration not consistent with PM-Timer: 125ms instead of 100ms
[    0.366226] APIC delta adjusted to PM-Timer: 6293925 (7881341)
[    0.366402] smpboot: CPU0: AMD Ryzen 5 5600X 6-Core Processor (family: 0x19, model: 0x21, stepping: 0x0)
[    0.367122] Performance Events: PMU not available due to virtualization, using software events only.
[    0.367122] signal: max sigframe size: 1776
[    0.367122] rcu: Hierarchical SRCU implementation.
[    0.367122] rcu: 	Max phase no-delay instances is 400.
[    0.367122] Timer migration: 1 hierarchy levels; 8 children per group; 1 crossnode level
[    0.370303] NMI watchdog: Perf NMI watchdog permanently disabled
[    0.370416] smp: Bringing up secondary CPUs ...
[    0.370936] smpboot: x86: Booting SMP configuration:
[    0.370938] .... node  #0, CPUs:      #1
[    0.375218] smp: Brought up 1 node, 2 CPUs
[    0.375221] smpboot: Total of 2 processors activated (14772.27 BogoMIPS)
[    0.375609] Memory: 3918120K/4193848K available (22217K kernel code, 4652K rwdata, 16296K rodata, 5268K init, 4212K bss, 269444K reserved, 0K cma-reserved)
[    0.376356] devtmpfs: initialized
[    0.376356] x86/mm: Memory block size: 128MB
[    0.378304] clocksource: jiffies: mask: 0xffffffff max_cycles: 0xffffffff, max_idle_ns: 1911260446275000 ns
[    0.378304] posixtimers hash table entries: 1024 (order: 2, 16384 bytes, linear)
[    0.378304] futex hash table entries: 512 (32768 bytes on 1 NUMA nodes, total 32 KiB, linear).
[    0.378398] pinctrl core: initialized pinctrl subsystem
[    0.379127] PM: RTC time: 00:38:28, date: 2026-05-18
[    0.382363] NET: Registered PF_NETLINK/PF_ROUTE protocol family
[    0.383502] DMA: preallocated 512 KiB GFP_KERNEL pool for atomic allocations
[    0.383549] DMA: preallocated 512 KiB GFP_KERNEL|GFP_DMA pool for atomic allocations
[    0.383595] DMA: preallocated 512 KiB GFP_KERNEL|GFP_DMA32 pool for atomic allocations
[    0.383608] audit: initializing netlink subsys (disabled)
[    0.383684] audit: type=2000 audit(1779064715.841:1): state=initialized audit_enabled=0 res=1
[    0.383996] thermal_sys: Registered thermal governor 'fair_share'
[    0.383998] thermal_sys: Registered thermal governor 'bang_bang'
[    0.383999] thermal_sys: Registered thermal governor 'step_wise'
[    0.384001] thermal_sys: Registered thermal governor 'user_space'
[    0.384002] thermal_sys: Registered thermal governor 'power_allocator'
[    0.384214] cpuidle: using governor ladder
[    0.384214] cpuidle: using governor menu
[    0.386411] acpiphp: ACPI Hot Plug PCI Controller Driver version: 0.5
[    0.386853] PCI: Using configuration type 1 for base access
[    0.386855] PCI: Using configuration type 1 for extended access
[    0.386948] mtrr: your CPUs had inconsistent variable MTRR settings
[    0.386949] mtrr: probably your BIOS does not setup all CPUs.
[    0.386950] mtrr: corrected configuration.
[    0.387207] kprobes: kprobe jump-optimization is enabled. All kprobes are optimized if possible.
[    0.388685] HugeTLB: registered 2.00 MiB page size, pre-allocated 0 pages
[    0.388688] HugeTLB: 28 KiB vmemmap can be freed for a 2.00 MiB page
[    0.399964] ACPI: Added _OSI(Module Device)
[    0.399966] ACPI: Added _OSI(Processor Device)
[    0.399968] ACPI: Added _OSI(Processor Aggregator Device)
[    0.400122] ACPI: 2 ACPI AML tables successfully acquired and loaded
[    0.401427] ACPI: Interpreter enabled
[    0.401438] ACPI: PM: (supports S0 S5)
[    0.401440] ACPI: Using IOAPIC for interrupt routing
[    0.402336] PCI: Using host bridge windows from ACPI; if necessary, use "pci=nocrs" and report a bug
[    0.402339] PCI: Using E820 reservations for host bridge windows
[    0.402497] ACPI: Enabled 2 GPEs in block 00 to 07
[    0.408122] ACPI: PCI Root Bridge [PCI0] (domain 0000 [bus 00-ff])
[    0.408122] acpi PNP0A03:00: _OSC: OS supports [ExtendedConfig ASPM ClockPM Segments MSI EDR HPX-Type3]
[    0.408228] acpi PNP0A03:00: _OSC: platform does not support [PCIeCapability LTR DPC]
[    0.409088] acpi PNP0A03:00: _OSC: not requesting control; platform does not support [PCIeCapability]
[    0.409091] acpi PNP0A03:00: _OSC: OS requested [PCIeHotplug SHPCHotplug PME AER PCIeCapability LTR DPC]
[    0.409093] acpi PNP0A03:00: _OSC: platform willing to grant [PCIeHotplug SHPCHotplug PME AER]
[    0.409095] acpi PNP0A03:00: _OSC: platform retains control of PCIe features (AE_SUPPORT)
[    0.409122] PCI host bridge to bus 0000:00
[    0.409122] pci_bus 0000:00: root bus resource [io  0x0000-0x0cf7 window]
[    0.409122] pci_bus 0000:00: root bus resource [io  0x0d00-0xffff window]
[    0.409122] pci_bus 0000:00: root bus resource [mem 0x000a0000-0x000bffff window]
[    0.409122] pci_bus 0000:00: root bus resource [mem 0xe0000000-0xfdffffff window]
[    0.409122] pci_bus 0000:00: root bus resource [bus 00-ff]
[    0.409294] pci 0000:00:00.0: [8086:1237] type 00 class 0x060000 conventional PCI endpoint
[    0.410122] pci 0000:00:01.0: [8086:7000] type 00 class 0x060100 conventional PCI endpoint
[    0.410232] pci 0000:00:01.1: [8086:7111] type 00 class 0x01018a conventional PCI endpoint
[    0.410802] pci 0000:00:01.1: BAR 4 [io  0xd000-0xd00f]
[    0.410873] pci 0000:00:01.1: BAR 0 [io  0x01f0-0x01f7]: legacy IDE quirk
[    0.410876] pci 0000:00:01.1: BAR 1 [io  0x03f6]: legacy IDE quirk
[    0.410878] pci 0000:00:01.1: BAR 2 [io  0x0170-0x0177]: legacy IDE quirk
[    0.410879] pci 0000:00:01.1: BAR 3 [io  0x0376]: legacy IDE quirk
[    0.411122] pci 0000:00:02.0: [15ad:0405] type 00 class 0x030000 conventional PCI endpoint
[    0.411640] pci 0000:00:02.0: BAR 0 [io  0xd010-0xd01f]
[    0.411657] pci 0000:00:02.0: BAR 1 [mem 0xe0000000-0xe7ffffff pref]
[    0.411674] pci 0000:00:02.0: BAR 2 [mem 0xf0000000-0xf01fffff]
[    0.412244] pci 0000:00:02.0: Video device with shadowed ROM at [mem 0x000c0000-0x000dffff]
[    0.412632] pci 0000:00:03.0: [8086:100e] type 00 class 0x020000 conventional PCI endpoint
[    0.413122] pci 0000:00:03.0: BAR 0 [mem 0xf0200000-0xf021ffff]
[    0.413122] pci 0000:00:03.0: BAR 2 [io  0xd020-0xd027]
[    0.413122] pci 0000:00:04.0: [80ee:cafe] type 00 class 0x088000 conventional PCI endpoint
[    0.413737] pci 0000:00:04.0: BAR 0 [io  0xd040-0xd05f]
[    0.413754] pci 0000:00:04.0: BAR 1 [mem 0xf0400000-0xf07fffff]
[    0.413771] pci 0000:00:04.0: BAR 2 [mem 0xf0800000-0xf0803fff pref]
[    0.414112] pci 0000:00:05.0: [8086:2415] type 00 class 0x040100 conventional PCI endpoint
[    0.414122] pci 0000:00:05.0: BAR 0 [io  0xd100-0xd1ff]
[    0.414122] pci 0000:00:05.0: BAR 1 [io  0xd200-0xd23f]
[    0.414141] pci 0000:00:06.0: [106b:003f] type 00 class 0x0c0310 conventional PCI endpoint
[    0.414683] pci 0000:00:06.0: BAR 0 [mem 0xf0804000-0xf0804fff]
[    0.415122] pci 0000:00:07.0: [8086:7113] type 00 class 0x068000 conventional PCI endpoint
[    0.415122] pci 0000:00:07.0: quirk: [io  0x4000-0x403f] claimed by PIIX4 ACPI
[    0.415122] pci 0000:00:07.0: quirk: [io  0x4100-0x410f] claimed by PIIX4 SMB
[    0.422156] pci 0000:00:0d.0: [8086:2829] type 00 class 0x010601 conventional PCI endpoint
[    0.422721] pci 0000:00:0d.0: BAR 0 [io  0xd240-0xd247]
[    0.422738] pci 0000:00:0d.0: BAR 1 [io  0xd248-0xd24b]
[    0.422754] pci 0000:00:0d.0: BAR 2 [io  0xd250-0xd257]
[    0.422770] pci 0000:00:0d.0: BAR 3 [io  0xd258-0xd25b]
[    0.422786] pci 0000:00:0d.0: BAR 4 [io  0xd260-0xd26f]
[    0.422802] pci 0000:00:0d.0: BAR 5 [mem 0xf0806000-0xf0807fff]
[    0.452092] ACPI: PCI: Interrupt link LNKA configured for IRQ 11
[    0.452122] ACPI: PCI: Interrupt link LNKB configured for IRQ 10
[    0.452122] ACPI: PCI: Interrupt link LNKC configured for IRQ 9
[    0.452122] ACPI: PCI: Interrupt link LNKD configured for IRQ 11
[    0.452343] iommu: Default domain type: Translated
[    0.452343] iommu: DMA domain TLB invalidation policy: lazy mode
[    0.452698] SCSI subsystem initialized
[    0.453378] libata version 3.00 loaded.
[    0.453378] ACPI: bus type USB registered
[    0.454137] usbcore: registered new interface driver usbfs
[    0.454150] usbcore: registered new interface driver hub
[    0.454159] usbcore: registered new device driver usb
[    0.454230] pps_core: LinuxPPS API ver. 1 registered
[    0.454233] pps_core: Software ver. 5.3.6 - Copyright 2005-2007 Rodolfo Giometti <giometti@linux.it>
[    0.454237] PTP clock support registered
[    0.455245] EDAC MC: Ver: 3.0.0
[    0.457874] NetLabel: Initializing
[    0.457876] NetLabel:  domain hash size = 128
[    0.457878] NetLabel:  protocols = UNLABELED CIPSOv4 CALIPSO
[    0.457970] NetLabel:  unlabeled traffic allowed by default
[    0.458262] mctp: management component transport protocol core
[    0.458262] NET: Registered PF_MCTP protocol family
[    0.458262] PCI: Using ACPI for IRQ routing
[    0.458262] PCI: pci_cache_line_size set to 64 bytes
[    0.458512] e820: reserve RAM buffer [mem 0x0009fc00-0x0009ffff]
[    0.458515] e820: reserve RAM buffer [mem 0xdfff0000-0xdfffffff]
[    0.459231] pci 0000:00:02.0: vgaarb: setting as boot VGA device
[    0.459231] pci 0000:00:02.0: vgaarb: bridge control possible
[    0.459231] pci 0000:00:02.0: vgaarb: VGA device added: decodes=io+mem,owns=io+mem,locks=none
[    0.459231] vgaarb: loaded
[    0.460305] clocksource: Switched to clocksource kvm-clock
[    0.463303] VFS: Disk quotas dquot_6.6.0
[    0.463323] VFS: Dquot-cache hash table entries: 512 (order 0, 4096 bytes)
[    0.464949] AppArmor: AppArmor Filesystem Enabled
[    0.464968] pnp: PnP ACPI init
[    0.466422] pnp: PnP ACPI: found 2 devices
[    0.494673] clocksource: acpi_pm: mask: 0xffffff max_cycles: 0xffffff, max_idle_ns: 2085701024 ns
[    0.494784] NET: Registered PF_INET protocol family
[    0.495572] IP idents hash table entries: 65536 (order: 7, 524288 bytes, linear)
[    0.517515] tcp_listen_portaddr_hash hash table entries: 2048 (order: 3, 32768 bytes, linear)
[    0.517515] Table-perturb hash table entries: 65536 (order: 6, 262144 bytes, linear)
[    0.517515] TCP established hash table entries: 32768 (order: 6, 262144 bytes, linear)
[    0.517515] TCP bind hash table entries: 32768 (order: 8, 1048576 bytes, linear)
[    0.517515] TCP: Hash tables configured (established 32768 bind 32768)
[    0.517515] MPTCP token hash table entries: 4096 (order: 5, 98304 bytes, linear)
[    0.517515] UDP hash table entries: 2048 (order: 5, 131072 bytes, linear)
[    0.517515] UDP-Lite hash table entries: 2048 (order: 5, 131072 bytes, linear)
[    0.517515] NET: Registered PF_UNIX/PF_LOCAL protocol family
[    0.517515] NET: Registered PF_XDP protocol family
[    0.517515] pci_bus 0000:00: resource 4 [io  0x0000-0x0cf7 window]
[    0.517515] pci_bus 0000:00: resource 5 [io  0x0d00-0xffff window]
[    0.517515] pci_bus 0000:00: resource 6 [mem 0x000a0000-0x000bffff window]
[    0.517515] pci_bus 0000:00: resource 7 [mem 0xe0000000-0xfdffffff window]
[    0.522570] pci 0000:00:00.0: Limiting direct PCI/PCI transfers
[    0.525419] PCI: CLS 0 bytes, default 64
[    0.526438] PCI-DMA: Using software bounce buffering for IO (SWIOTLB)
[    0.526440] software IO TLB: mapped [mem 0x00000000dbff0000-0x00000000dfff0000] (64MB)
[    0.526496] clocksource: tsc: mask: 0xffffffffffffffff max_cycles: 0x6a7782233a6, max_idle_ns: 881590537829 ns
[    0.526660] clocksource: Switched to clocksource tsc
[    0.526698] platform rtc_cmos: registered platform RTC device (no PNP device found)
[    0.526713] Trying to unpack rootfs image as initramfs...
[    0.611556] Initialise system trusted keyrings
[    0.611577] Key type blacklist registered
[    0.611606] workingset: timestamp_bits=36 max_order=20 bucket_order=0
[    0.611606] squashfs: version 4.0 (2009/01/31) Phillip Lougher
[    0.611606] fuse: init (API version 7.44)
[    0.613541] integrity: Platform Keyring initialized
[    0.613611] integrity: Machine keyring initialized
[    0.614514] Key type asymmetric registered
[    0.614514] Asymmetric key parser 'x509' registered
[    0.614514] Block layer SCSI generic (bsg) driver version 0.4 loaded (major 242)
[    0.622654] io scheduler mq-deadline registered
[    0.623265] ledtrig-cpu: registered to indicate activity on CPUs
[    0.624025] ACPI: AC: AC Adapter [AC] (on-line)
[    0.624098] input: Power Button as /devices/LNXSYSTM:00/LNXPWRBN:00/input/input0
[    0.624182] ACPI: button: Power Button [PWRF]
[    0.624228] input: Sleep Button as /devices/LNXSYSTM:00/LNXSLPBN:00/input/input1
[    0.624310] ACPI: button: Sleep Button [SLPF]
[    0.626056] Serial: 8250/16550 driver, 32 ports, IRQ sharing enabled
[    0.628533] Linux agpgart interface v0.103
[    0.634580] loop: module loaded
[    0.638534] scsi host0: ata_piix
[    0.638534] scsi host1: ata_piix
[    0.638534] ata1: PATA max UDMA/33 cmd 0x1f0 ctl 0x3f6 bmdma 0xd000 irq 14 lpm-pol 0
[    0.638534] ata2: PATA max UDMA/33 cmd 0x170 ctl 0x376 bmdma 0xd008 irq 15 lpm-pol 0
[    0.639638] ACPI: bus type drm_connector registered
[    0.639983] tun: Universal TUN/TAP device driver, 1.6
[    0.640050] PPP generic driver version 2.4.2
[    0.641734] ohci-pci 0000:00:06.0: OHCI PCI host controller
[    0.641742] ohci-pci 0000:00:06.0: new USB bus registered, assigned bus number 1
[    0.641993] ohci-pci 0000:00:06.0: irq 22, io mem 0xf0804000
[    0.829836] Freeing initrd memory: 76636K
[    0.829961] usb usb1: New USB device found, idVendor=1d6b, idProduct=0001, bcdDevice= 6.17
[    0.829965] usb usb1: New USB device strings: Mfr=3, Product=2, SerialNumber=1
[    0.829967] usb usb1: Product: OHCI PCI host controller
[    0.829969] usb usb1: Manufacturer: Linux 6.17.0-22-generic ohci_hcd
[    0.829971] usb usb1: SerialNumber: 0000:00:06.0
[    0.830133] hub 1-0:1.0: USB hub found
[    0.830187] hub 1-0:1.0: 12 ports detected
[    0.831257] i8042: PNP: PS/2 Controller [PNP0303:PS2K,PNP0f03:PS2M] at 0x60,0x64 irq 1,12
[    0.840424] ata1.00: ATAPI: VBOX CD-ROM, 1.0, max UDMA/133
[    0.841072] serio: i8042 KBD port at 0x60,0x64 irq 1
[    0.841079] serio: i8042 AUX port at 0x60,0x64 irq 12
[    0.841385] mousedev: PS/2 mouse device common for all mice
[    0.842369] scsi 0:0:0:0: CD-ROM            VBOX     CD-ROM           1.0  PQ: 0 ANSI: 5
[    0.843043] input: AT Translated Set 2 keyboard as /devices/platform/i8042/serio0/input/input2
[    0.844286] rtc_cmos rtc_cmos: registered as rtc0
[    0.844452] rtc_cmos rtc_cmos: setting system clock to 2026-05-18T00:38:29 UTC (1779064709)
[    0.844689] rtc_cmos rtc_cmos: alarms up to one day, 114 bytes nvram
[    0.844753] i2c_dev: i2c /dev entries driver
[    0.844790] device-mapper: core: CONFIG_IMA_DISABLE_HTABLE is disabled. Duplicate IMA measurements will not be recorded in the IMA log.
[    0.844807] device-mapper: uevent: version 1.0.3
[    0.845091] device-mapper: ioctl: 4.50.0-ioctl (2025-04-28) initialised: dm-devel@lists.linux.dev
[    0.845097] amd_pstate: the _CPC object is not present in SBIOS or ACPI disabled
[    0.845188] drop_monitor: Initializing network drop monitor service
[    0.845339] NET: Registered PF_INET6 protocol family
[    0.846494] Segment Routing with IPv6
[    0.846504] In-situ OAM (IOAM) with IPv6
[    0.846590] NET: Registered PF_PACKET protocol family
[    0.846990] Key type dns_resolver registered
[    0.847770] IPI shorthand broadcast: enabled
[    0.850062] sched_clock: Marking stable (817570709, 31492149)->(926792690, -77729832)
[    0.852152] registered taskstats version 1
[    0.853102] Loading compiled-in X.509 certificates
[    0.853104] sr 0:0:0:0: [sr0] scsi3-mmc drive: 32x/32x xa/form2 tray
[    0.853108] cdrom: Uniform CD-ROM driver Revision: 3.20
[    0.853803] Loaded X.509 cert 'Build time autogenerated kernel key: 10e561fe75970ebe98357e1cb1b79397dec08fd7'
[    0.854091] Loaded X.509 cert 'Canonical Ltd. Live Patch Signing 2025 Kmod: d541cef61dc7e793b7eb7e899970a2eef0b5dc8c'
[    0.854372] Loaded X.509 cert 'Canonical Ltd. Live Patch Signing: 14df34d1a87cf37625abec039ef2bf521249b969'
[    0.854650] Loaded X.509 cert 'Canonical Ltd. Kernel Module Signing: 88f752e560a1e0737e31163a466ad7b70a850c19'
[    0.854652] blacklist: Loading compiled-in revocation X.509 certificates
[    0.854663] Loaded X.509 cert 'Canonical Ltd. Secure Boot Signing: 61482aa2830d0ab2ad5af10b7250da9033ddcef0'
[    0.854672] Loaded X.509 cert 'Canonical Ltd. Secure Boot Signing (2017): 242ade75ac4a15e50d50c84b0d45ff3eae707a03'
[    0.854707] Loaded X.509 cert 'Canonical Ltd. Secure Boot Signing (ESM 2018): 365188c1d374d6b07c3c8f240f8ef722433d6a8b'
[    0.854717] Loaded X.509 cert 'Canonical Ltd. Secure Boot Signing (2019): c0746fd6c5da3ae827864651ad66ae47fe24b3e8'
[    0.854726] Loaded X.509 cert 'Canonical Ltd. Secure Boot Signing (2021 v1): a8d54bbb3825cfb94fa13c9f8a594a195c107b8d'
[    0.854751] Loaded X.509 cert 'Canonical Ltd. Secure Boot Signing (2021 v2): 4cf046892d6fd3c9a5b03f98d845f90851dc6a8c'
[    0.854760] Loaded X.509 cert 'Canonical Ltd. Secure Boot Signing (2021 v3): 100437bb6de6e469b581e61cd66bce3ef4ed53af'
[    0.854769] Loaded X.509 cert 'Canonical Ltd. Secure Boot Signing (Ubuntu Core 2019): c1d57b8f6b743f23ee41f4f7ee292f06eecadfb9'
[    0.865406] Demotion targets for Node 0: null
[    0.866070] Key type .fscrypt registered
[    0.866073] Key type fscrypt-provisioning registered
[    0.866134] Key type big_key registered
[    0.867806] sr 0:0:0:0: Attached scsi CD-ROM sr0
[    0.867899] sr 0:0:0:0: Attached scsi generic sg0 type 5
[    0.887087] Key type encrypted registered
[    0.887091] AppArmor: AppArmor sha256 policy hashing enabled
[    0.887101] ima: No TPM chip found, activating TPM-bypass!
[    0.887105] Loading compiled-in module X.509 certificates
[    0.887466] Loaded X.509 cert 'Build time autogenerated kernel key: 10e561fe75970ebe98357e1cb1b79397dec08fd7'
[    0.887469] ima: Allocated hash algorithm: sha256
[    0.887480] ima: No architecture policies found
[    0.887496] evm: Initialising EVM extended attributes:
[    0.887498] evm: security.selinux
[    0.887499] evm: security.SMACK64
[    0.887501] evm: security.SMACK64EXEC
[    0.887502] evm: security.SMACK64TRANSMUTE
[    0.887503] evm: security.SMACK64MMAP
[    0.887505] evm: security.apparmor
[    0.887507] evm: security.ima
[    0.887508] evm: security.capability
[    0.887509] evm: HMAC attrs: 0x1
[    0.887848] PM:   Magic number: 10:922:607
[    0.891180] RAS: Correctable Errors collector initialized.
[    0.898978] clk: Disabling unused clocks
[    0.898980] PM: genpd: Disabling unused power domains
[    0.902885] Freeing unused decrypted memory: 2028K
[    0.903863] Freeing unused kernel image (initmem) memory: 5268K
[    0.903877] Write protecting the kernel read-only data: 38912k
[    0.904681] Freeing unused kernel image (text/rodata gap) memory: 308K
[    0.904969] Freeing unused kernel image (rodata/data gap) memory: 88K
[    0.949679] x86/mm: Checked W+X mappings: passed, no W+X pages found.
[    0.949684] Run /init as init process
[    0.949686]   with arguments:
[    0.949688]     /init
[    0.949689]     splash
[    0.949691]   with environment:
[    0.949692]     HOME=/
[    0.949693]     TERM=linux
[    1.127386] input: ImExPS/2 Generic Explorer Mouse as /devices/platform/i8042/serio1/input/input4
[    1.149175] ACPI: video: Video Device [GFX0] (multi-head: yes  rom: no  post: no)
[    1.149263] input: Video Bus as /devices/LNXSYSTM:00/LNXSYBUS:00/PNP0A03:00/LNXVIDEO:00/input/input5
[    1.163988] e1000: Intel(R) PRO/1000 Network Driver
[    1.163990] e1000: Copyright (c) 1999-2006 Intel Corporation.
[    1.170126] usb 1-1: new full-speed USB device number 2 using ohci-pci
[    1.176759] ahci 0000:00:0d.0: SSS flag set, parallel bus scan disabled
[    1.177294] ahci 0000:00:0d.0: AHCI vers 0001.0100, 32 command slots, 3 Gbps, SATA mode
[    1.177297] ahci 0000:00:0d.0: 2/2 ports implemented (port mask 0x3)
[    1.177300] ahci 0000:00:0d.0: flags: 64bit ncq stag only ccc 
[    1.179265] scsi host2: ahci
[    1.181087] scsi host3: ahci
[    1.181271] ata3: SATA max UDMA/133 abar m8192@0xf0806000 port 0xf0806100 irq 21 lpm-pol 1
[    1.181290] ata4: SATA max UDMA/133 abar m8192@0xf0806000 port 0xf0806180 irq 21 lpm-pol 1
[    1.575984] ata3: SATA link up 3.0 Gbps (SStatus 123 SControl 300)
[    1.576298] ata3.00: ATA-6: VBOX HARDDISK, 1.0, max UDMA/133
[    1.576302] ata3.00: 52428800 sectors, multi 128: LBA48 NCQ (depth 32)
[    1.576728] ata3.00: configured for UDMA/133
[    1.577012] scsi 2:0:0:0: Direct-Access     ATA      VBOX HARDDISK    1.0  PQ: 0 ANSI: 5
[    1.577568] sd 2:0:0:0: Attached scsi generic sg1 type 0
[    1.577760] sd 2:0:0:0: [sda] 52428800 512-byte logical blocks: (26.8 GB/25.0 GiB)
[    1.577769] sd 2:0:0:0: [sda] Write Protect is off
[    1.577772] sd 2:0:0:0: [sda] Mode Sense: 00 3a 00 00
[    1.577784] sd 2:0:0:0: [sda] Write cache: enabled, read cache: enabled, doesn't support DPO or FUA
[    1.577805] sd 2:0:0:0: [sda] Preferred minimum I/O size 512 bytes
[    1.598588]  sda: sda1 sda2
[    1.598725] sd 2:0:0:0: [sda] Attached SCSI disk
[    1.610503] e1000 0000:00:03.0 eth0: (PCI:33MHz:32-bit) 08:00:27:dd:25:c2
[    1.610599] e1000 0000:00:03.0 eth0: Intel(R) PRO/1000 Network Connection
[    1.664690] usb 1-1: New USB device found, idVendor=80ee, idProduct=0021, bcdDevice= 1.00
[    1.664697] usb 1-1: New USB device strings: Mfr=1, Product=3, SerialNumber=0
[    1.664699] usb 1-1: Product: USB Tablet
[    1.664702] usb 1-1: Manufacturer: VirtualBox
[    1.676039] hid: raw HID events driver (C) Jiri Kosina
[    1.892210] ata4: SATA link up 3.0 Gbps (SStatus 123 SControl 300)
[    1.892551] ata4.00: ATA-6: VBOX HARDDISK, 1.0, max UDMA/133
[    1.892556] ata4.00: 204800 sectors, multi 128: LBA48 NCQ (depth 32)
[    1.893127] ata4.00: configured for UDMA/133
[    1.893528] scsi 3:0:0:0: Direct-Access     ATA      VBOX HARDDISK    1.0  PQ: 0 ANSI: 5
[    1.894287] sd 3:0:0:0: Attached scsi generic sg2 type 0
[    1.894316] sd 3:0:0:0: [sdb] 204800 512-byte logical blocks: (105 MB/100 MiB)
[    1.894363] sd 3:0:0:0: [sdb] Write Protect is off
[    1.894366] sd 3:0:0:0: [sdb] Mode Sense: 00 3a 00 00
[    1.894378] sd 3:0:0:0: [sdb] Write cache: enabled, read cache: enabled, doesn't support DPO or FUA
[    1.894401] sd 3:0:0:0: [sdb] Preferred minimum I/O size 512 bytes
[    2.231298] sd 3:0:0:0: [sdb] Attached SCSI disk
[    2.233099] e1000 0000:00:03.0 enp0s3: renamed from eth0
[    2.259049] usbcore: registered new interface driver usbhid
[    2.259053] usbhid: USB HID core driver
[    2.264148] input: VirtualBox USB Tablet as /devices/pci0000:00/0000:00:06.0/usb1/1-1/1-1:1.0/0003:80EE:0021.0001/input/input6
[    2.265733] hid-generic 0003:80EE:0021.0001: input,hidraw0: USB HID v1.10 Mouse [VirtualBox USB Tablet] on usb-0000:00:06.0-1/input0
[    4.218082] EXT4-fs (sda2): mounted filesystem 154e4895-b405-436c-ac14-63ad0b84fe4c ro with ordered data mode. Quota mode: none.
[    4.463041] systemd[1]: Inserted module 'autofs4'
[    4.491553] systemd[1]: systemd 255.4-1ubuntu8.14 running in system mode (+PAM +AUDIT +SELINUX +APPARMOR +IMA +SMACK +SECCOMP +GCRYPT -GNUTLS +OPENSSL +ACL +BLKID +CURL +ELFUTILS +FIDO2 +IDN2 -IDN +IPTC +KMOD +LIBCRYPTSETUP +LIBFDISK +PCRE2 -PWQUALITY +P11KIT +QRENCODE +TPM2 +BZIP2 +LZ4 +XZ +ZLIB +ZSTD -BPF_FRAMEWORK -XKBCOMMON +UTMP +SYSVINIT default-hierarchy=unified)
[    4.491558] systemd[1]: Detected virtualization oracle.
[    4.491628] systemd[1]: Detected architecture x86-64.
[    4.494290] systemd[1]: Hostname set to <UbuntuSdC>.
[    4.816562] systemd[1]: Queued start job for default target graphical.target.
[    4.840928] systemd[1]: Created slice system-modprobe.slice - Slice /system/modprobe.
[    4.841227] systemd[1]: Created slice user.slice - User and Session Slice.
[    4.841283] systemd[1]: Started systemd-ask-password-wall.path - Forward Password Requests to Wall Directory Watch.
[    4.841449] systemd[1]: Set up automount proc-sys-fs-binfmt_misc.automount - Arbitrary Executable File Formats File System Automount Point.
[    4.841468] systemd[1]: Reached target integritysetup.target - Local Integrity Protected Volumes.
[    4.841485] systemd[1]: Reached target remote-fs.target - Remote File Systems.
[    4.841493] systemd[1]: Reached target slices.target - Slice Units.
[    4.841501] systemd[1]: Reached target snapd.mounts-pre.target - Mounting snaps.
[    4.841511] systemd[1]: Reached target swap.target - Swaps.
[    4.841521] systemd[1]: Reached target veritysetup.target - Local Verity Protected Volumes.
[    4.841646] systemd[1]: Listening on syslog.socket - Syslog Socket.
[    4.841729] systemd[1]: Listening on systemd-fsckd.socket - fsck to fsckd communication Socket.
[    4.841809] systemd[1]: Listening on systemd-initctl.socket - initctl Compatibility Named Pipe.
[    4.841902] systemd[1]: Listening on systemd-journald-dev-log.socket - Journal Socket (/dev/log).
[    4.842000] systemd[1]: Listening on systemd-journald.socket - Journal Socket.
[    4.842139] systemd[1]: Listening on systemd-oomd.socket - Userspace Out-Of-Memory (OOM) Killer Socket.
[    4.842151] systemd[1]: systemd-pcrextend.socket - TPM2 PCR Extension (Varlink) was skipped because of an unmet condition check (ConditionSecurity=measured-uki).
[    4.842885] systemd[1]: Listening on systemd-udevd-control.socket - udev Control Socket.
[    4.842978] systemd[1]: Listening on systemd-udevd-kernel.socket - udev Kernel Socket.
[    4.844349] systemd[1]: Mounting dev-hugepages.mount - Huge Pages File System...
[    4.845309] systemd[1]: Mounting dev-mqueue.mount - POSIX Message Queue File System...
[    4.845899] systemd[1]: Mounting sys-kernel-debug.mount - Kernel Debug File System...
[    4.855635] systemd[1]: Mounting sys-kernel-tracing.mount - Kernel Trace File System...
[    4.858081] systemd[1]: Starting systemd-journald.service - Journal Service...
[    4.863797] systemd[1]: Starting keyboard-setup.service - Set the console keyboard layout...
[    4.866245] systemd[1]: Starting kmod-static-nodes.service - Create List of Static Device Nodes...
[    4.867280] systemd[1]: Starting modprobe@configfs.service - Load Kernel Module configfs...
[    4.867922] systemd[1]: Starting modprobe@dm_mod.service - Load Kernel Module dm_mod...
[    4.884247] systemd[1]: Starting modprobe@drm.service - Load Kernel Module drm...
[    4.888692] systemd-journald[237]: Collecting audit messages is disabled.
[    4.889735] systemd[1]: Starting modprobe@efi_pstore.service - Load Kernel Module efi_pstore...
[    4.906824] systemd[1]: Starting modprobe@fuse.service - Load Kernel Module fuse...
[    4.908165] systemd[1]: Starting modprobe@loop.service - Load Kernel Module loop...
[    4.908237] systemd[1]: systemd-fsck-root.service - File System Check on Root Device was skipped because of an unmet condition check (ConditionPathExists=!/run/initramfs/fsck-root).
[    4.914616] systemd[1]: Starting systemd-modules-load.service - Load Kernel Modules...
[    4.914629] systemd[1]: systemd-pcrmachine.service - TPM2 PCR Machine ID Measurement was skipped because of an unmet condition check (ConditionSecurity=measured-uki).
[    4.919444] systemd[1]: Starting systemd-remount-fs.service - Remount Root and Kernel File Systems...
[    4.919474] systemd[1]: systemd-tpm2-setup-early.service - TPM2 SRK Setup (Early) was skipped because of an unmet condition check (ConditionSecurity=measured-uki).
[    4.937888] systemd[1]: Starting systemd-udev-trigger.service - Coldplug All udev Devices...
[    4.939057] systemd[1]: Mounted dev-hugepages.mount - Huge Pages File System.
[    4.941757] systemd[1]: Started systemd-journald.service - Journal Service.
[    4.964188] EXT4-fs (sda2): re-mounted 154e4895-b405-436c-ac14-63ad0b84fe4c r/w.
[    4.969507] lp: driver loaded but no devices found
[    4.982545] ppdev: user-space parallel port driver
[    5.028916] systemd-journald[237]: Received client request to flush runtime journal.
[    5.056997] systemd-journald[237]: File /var/log/journal/f74464dae0f64b65a6b2fd9e00edcb0c/system.journal corrupted or uncleanly shut down, renaming and replacing.
[    5.187769] loop0: detected capacity change from 0 to 8
[    5.192032] loop1: detected capacity change from 0 to 151464
[    5.207907] loop2: detected capacity change from 0 to 136904
[    5.210338] loop3: detected capacity change from 0 to 151512
[    5.217151] loop4: detected capacity change from 0 to 515416
[    5.239003] loop5: detected capacity change from 0 to 33792
[    5.240073] loop6: detected capacity change from 0 to 37864
[    5.243251] loop7: detected capacity change from 0 to 1088256
[    5.254439] loop8: detected capacity change from 0 to 1241248
[    5.258570] loop9: detected capacity change from 0 to 187776
[    5.421967] audit: type=1400 audit(1779064714.077:2): apparmor="STATUS" operation="profile_load" profile="unconfined" name="Discord" pid=359 comm="apparmor_parser"
[    5.424267] audit: type=1400 audit(1779064714.079:3): apparmor="STATUS" operation="profile_load" profile="unconfined" name=4D6F6E676F444220436F6D70617373 pid=360 comm="apparmor_parser"
[    5.425932] audit: type=1400 audit(1779064714.081:4): apparmor="STATUS" operation="profile_load" profile="unconfined" name="1password" pid=358 comm="apparmor_parser"
[    5.427072] audit: type=1400 audit(1779064714.082:5): apparmor="STATUS" operation="profile_load" profile="unconfined" name="QtWebEngineProcess" pid=361 comm="apparmor_parser"
[    5.429251] audit: type=1400 audit(1779064714.084:6): apparmor="STATUS" operation="profile_load" profile="unconfined" name="balena-etcher" pid=362 comm="apparmor_parser"
[    5.431116] audit: type=1400 audit(1779064714.086:7): apparmor="STATUS" operation="profile_load" profile="unconfined" name="buildah" pid=364 comm="apparmor_parser"
[    5.433127] audit: type=1400 audit(1779064714.088:8): apparmor="STATUS" operation="profile_load" profile="unconfined" name="brave" pid=363 comm="apparmor_parser"
[    5.433169] audit: type=1400 audit(1779064714.088:9): apparmor="STATUS" operation="profile_load" profile="unconfined" name="busybox" pid=365 comm="apparmor_parser"
[    5.435639] audit: type=1400 audit(1779064714.091:10): apparmor="STATUS" operation="profile_load" profile="unconfined" name="cam" pid=366 comm="apparmor_parser"
[    5.438482] audit: type=1400 audit(1779064714.093:11): apparmor="STATUS" operation="profile_load" profile="unconfined" name="ch-run" pid=368 comm="apparmor_parser"
[    6.152583] vboxguest: host-version: 7.2.6r172322 0x8000000f
[    6.170831] vbg_heartbeat_init: Setting up heartbeat to trigger every 2000 milliseconds
[    6.177600] input: VirtualBox mouse integration as /devices/pci0000:00/0000:00:04.0/input/input7
[    6.224193] piix4_smbus 0000:00:07.0: SMBus Host Controller at 0x4100, revision 0
[    6.392835] vmwgfx 0000:00:02.0: vgaarb: deactivate vga console
[    6.392951] Console: switching to colour dummy device 80x25
[    6.393961] vmwgfx 0000:00:02.0: [drm] FIFO at 0x00000000f0000000 size is 2048 KiB
[    6.393982] vmwgfx 0000:00:02.0: [drm] VRAM at 0x00000000e0000000 size is 131072 KiB
[    6.394042] vmwgfx 0000:00:02.0: [drm] Running on SVGA version 2.
[    6.394060] vmwgfx 0000:00:02.0: [drm] Capabilities: rect copy, cursor, cursor bypass, cursor bypass 2, alpha cursor, extended fifo, pitchlock, irq mask, gmr, traces, gmr2, screen object 2, command buffers, command buffers 2, gbobject, 
[    6.394063] vmwgfx 0000:00:02.0: [drm] *ERROR* vmwgfx seems to be running on an unsupported hypervisor.
[    6.394066] vmwgfx 0000:00:02.0: [drm] *ERROR* This configuration is likely broken.
[    6.394069] vmwgfx 0000:00:02.0: [drm] *ERROR* Please switch to a supported graphics device to avoid problems.
[    6.394071] vmwgfx 0000:00:02.0: [drm] DMA map mode: Caching DMA mappings.
[    6.394850] vmwgfx 0000:00:02.0: [drm] Legacy memory limits: VRAM = 131072 KiB, FIFO = 2048 KiB, surface = 393216 KiB
[    6.394854] vmwgfx 0000:00:02.0: [drm] MOB limits: max mob size = 131072 KiB, max mob pages = 32768
[    6.394857] vmwgfx 0000:00:02.0: [drm] Max GMR ids is 8192
[    6.394858] vmwgfx 0000:00:02.0: [drm] Max number of GMR pages is 1048576
[    6.394860] vmwgfx 0000:00:02.0: [drm] Maximum display memory size is 131072 KiB
[    6.452148] vmwgfx 0000:00:02.0: [drm] Screen Target display unit initialized
[    6.452587] vmwgfx 0000:00:02.0: [drm] Fifo max 0x00200000 min 0x00001000 cap 0x00000355
[    6.453243] vmwgfx 0000:00:02.0: [drm] Using command buffers with DMA pool.
[    6.453249] vmwgfx 0000:00:02.0: [drm] Available shader model: Legacy.
[    6.462389] [drm] Initialized vmwgfx 2.21.0 for 0000:00:02.0 on minor 0
[    6.483758] fbcon: vmwgfxdrmfb (fb0) is primary device
[    6.484686] Console: switching to colour frame buffer device 160x50
[    6.484694] vmwgfx 0000:00:02.0: [drm] fb0: vmwgfxdrmfb frame buffer device
[    6.582838] intel_rapl_common: Found RAPL domain package
[    6.582862] intel_rapl_common: Found RAPL domain core
[    7.104342] snd_intel8x0 0000:00:05.0: allow list rate for 1028:0177 is 48000
[    7.891404] NET: Registered PF_QIPCRTR protocol family
[    8.420685] e1000: enp0s3 NIC Link is Up 1000 Mbps Full Duplex, Flow Control: RX
[   12.168053] rfkill: input handler disabled
[   55.240396] systemd-journald[237]: File /var/log/journal/f74464dae0f64b65a6b2fd9e00edcb0c/user-1000.journal corrupted or uncleanly shut down, renaming and replacing.
[   55.484773] rfkill: input handler enabled
[   57.368860] rfkill: input handler disabled
[  138.296854] clocksource: Long readout interval, skipping watchdog check: cs_nsec: 1048057837 wd_nsec: 1048057375
[  327.736358] set_capacity_and_notify: 6 callbacks suppressed
[  327.736362] loop15: detected capacity change from 0 to 136816
[  413.268885] kauditd_printk_skb: 152 callbacks suppressed
[  413.268889] audit: type=1400 audit(1779065124.126:164): apparmor="STATUS" operation="profile_replace" profile="unconfined" name="rsyslogd" pid=6307 comm="apparmor_parser"
[  414.739183] audit: type=1400 audit(1779065125.609:165): apparmor="STATUS" operation="profile_replace" info="same as current profile, skipping" profile="unconfined" name="rsyslogd" pid=6478 comm="apparmor_parser"
[  417.549466] audit: type=1400 audit(1779065128.429:166): apparmor="STATUS" operation="profile_replace" info="same as current profile, skipping" profile="unconfined" name="lsb_release" pid=6561 comm="apparmor_parser"
[  417.569644] audit: type=1400 audit(1779065128.455:167): apparmor="STATUS" operation="profile_replace" profile="unconfined" name="nvidia_modprobe" pid=6564 comm="apparmor_parser"
[  417.683085] audit: type=1400 audit(1779065128.587:168): apparmor="STATUS" operation="profile_replace" profile="unconfined" name="nvidia_modprobe//kmod" pid=6564 comm="apparmor_parser"
[  419.041817] audit: type=1400 audit(1779065129.880:169): apparmor="STATUS" operation="profile_replace" info="same as current profile, skipping" profile="unconfined" name="1password" pid=6993 comm="apparmor_parser"
[  419.042529] audit: type=1400 audit(1779065129.880:170): apparmor="STATUS" operation="profile_replace" info="same as current profile, skipping" profile="unconfined" name="Discord" pid=6994 comm="apparmor_parser"
[  419.045762] audit: type=1400 audit(1779065129.880:171): apparmor="STATUS" operation="profile_replace" info="same as current profile, skipping" profile="unconfined" name=4D6F6E676F444220436F6D70617373 pid=6995 comm="apparmor_parser"
[  419.047387] audit: type=1400 audit(1779065129.880:172): apparmor="STATUS" operation="profile_replace" info="same as current profile, skipping" profile="unconfined" name="QtWebEngineProcess" pid=6996 comm="apparmor_parser"
[  419.048913] audit: type=1400 audit(1779065129.880:173): apparmor="STATUS" operation="profile_replace" info="same as current profile, skipping" profile="unconfined" name="balena-etcher" pid=6997 comm="apparmor_parser"
[  419.050167] audit: type=1400 audit(1779065129.880:174): apparmor="STATUS" operation="profile_replace" info="same as current profile, skipping" profile="unconfined" name="brave" pid=6998 comm="apparmor_parser"
[  419.051863] audit: type=1400 audit(1779065129.880:175): apparmor="STATUS" operation="profile_replace" info="same as current profile, skipping" profile="unconfined" name="buildah" pid=6999 comm="apparmor_parser"
[  419.053339] audit: type=1400 audit(1779065129.880:176): apparmor="STATUS" operation="profile_replace" info="same as current profile, skipping" profile="unconfined" name="cam" pid=7000 comm="apparmor_parser"
[  419.054210] audit: type=1400 audit(1779065129.880:177): apparmor="STATUS" operation="profile_replace" info="same as current profile, skipping" profile="unconfined" name="ch-checkns" pid=7001 comm="apparmor_parser"
[  419.056267] audit: type=1400 audit(1779065129.880:178): apparmor="STATUS" operation="profile_replace" info="same as current profile, skipping" profile="unconfined" name="ch-run" pid=7002 comm="apparmor_parser"
[  426.280067] systemd[1]: systemd 255.4-1ubuntu8.15 running in system mode (+PAM +AUDIT +SELINUX +APPARMOR +IMA +SMACK +SECCOMP +GCRYPT -GNUTLS +OPENSSL +ACL +BLKID +CURL +ELFUTILS +FIDO2 +IDN2 -IDN +IPTC +KMOD +LIBCRYPTSETUP +LIBFDISK +PCRE2 -PWQUALITY +P11KIT +QRENCODE +TPM2 +BZIP2 +LZ4 +XZ +ZLIB +ZSTD -BPF_FRAMEWORK -XKBCOMMON +UTMP +SYSVINIT default-hierarchy=unified)
[  426.280091] systemd[1]: Detected virtualization oracle.
[  426.280437] systemd[1]: Detected architecture x86-64.
[  426.608957] systemd[1]: Stopping systemd-journald.service - Journal Service...
[  426.609101] systemd-journald[237]: Received SIGTERM from PID 1 (systemd).
[  426.657647] systemd[1]: systemd-journald.service: Deactivated successfully.
[  426.657847] systemd[1]: Stopped systemd-journald.service - Journal Service.
[  426.667741] systemd[1]: Starting systemd-journald.service - Journal Service...
[  426.684918] systemd-journald[7665]: Collecting audit messages is disabled.
[  426.702318] systemd[1]: Started systemd-journald.service - Journal Service.
[  426.842343] kauditd_printk_skb: 129 callbacks suppressed
[  426.842346] audit: type=1400 audit(1779065137.747:308): apparmor="STATUS" operation="profile_replace" info="same as current profile, skipping" profile="unconfined" name="/usr/sbin/sssd" pid=7682 comm="apparmor_parser"
[  435.699887] audit: type=1400 audit(1779065146.604:309): apparmor="STATUS" operation="profile_replace" info="same as current profile, skipping" profile="unconfined" name="/usr/lib/snapd/snap-confine" pid=9210 comm="apparmor_parser"
[  435.700260] audit: type=1400 audit(1779065146.605:310): apparmor="STATUS" operation="profile_replace" info="same as current profile, skipping" profile="unconfined" name="/usr/lib/snapd/snap-confine//mount-namespace-capture-helper" pid=9210 comm="apparmor_parser"
[  441.890138] loop16: detected capacity change from 0 to 8
[  442.027535] audit: type=1400 audit(1779065152.922:311): apparmor="STATUS" operation="profile_replace" profile="unconfined" name="/usr/lib/snapd/snap-confine" pid=9574 comm="apparmor_parser"
[  442.029447] audit: type=1400 audit(1779065152.934:312): apparmor="STATUS" operation="profile_replace" profile="unconfined" name="/usr/lib/snapd/snap-confine//mount-namespace-capture-helper" pid=9574 comm="apparmor_parser"
[  445.088687] audit: type=1400 audit(1779065155.950:313): apparmor="STATUS" operation="profile_replace" profile="unconfined" name="/snap/snapd/25935/usr/lib/snapd/snap-confine" pid=9831 comm="apparmor_parser"
[  445.699732] audit: type=1400 audit(1779065156.604:314): apparmor="STATUS" operation="profile_replace" profile="unconfined" name="/snap/snapd/25935/usr/lib/snapd/snap-confine//mount-namespace-capture-helper" pid=9831 comm="apparmor_parser"
[  447.977354] audit: type=1400 audit(1779065158.616:315): apparmor="STATUS" operation="profile_replace" info="same as current profile, skipping" profile="unconfined" name="snap-update-ns.firmware-updater" pid=9833 comm="apparmor_parser"
[  448.205630] audit: type=1400 audit(1779065158.616:316): apparmor="STATUS" operation="profile_replace" profile="unconfined" name="snap.firmware-updater.firmware-notifier" pid=9834 comm="apparmor_parser"
[  448.397552] audit: type=1400 audit(1779065158.616:317): apparmor="STATUS" operation="profile_replace" profile="unconfined" name="snap.firmware-updater.firmware-updater" pid=9835 comm="apparmor_parser"
[  448.642173] audit: type=1400 audit(1779065158.616:318): apparmor="STATUS" operation="profile_replace" profile="unconfined" name="snap.firmware-updater.firmware-updater-app" pid=9836 comm="apparmor_parser"
[  448.763576] audit: type=1400 audit(1779065159.667:319): apparmor="STATUS" operation="profile_replace" profile="unconfined" name="snap.firmware-updater.hook.configure" pid=9837 comm="apparmor_parser"
[  449.022123] audit: type=1400 audit(1779065159.923:320): apparmor="STATUS" operation="profile_replace" info="same as current profile, skipping" profile="unconfined" name="snap-update-ns.snapd-desktop-integration" pid=9838 comm="apparmor_parser"
[  449.141620] audit: type=1400 audit(1779065160.046:321): apparmor="STATUS" operation="profile_replace" profile="unconfined" name="snap.snapd-desktop-integration.hook.configure" pid=9839 comm="apparmor_parser"
[  449.374645] audit: type=1400 audit(1779065160.099:322): apparmor="STATUS" operation="profile_replace" profile="unconfined" name="snap.snapd-desktop-integration.snapd-desktop-integration" pid=9840 comm="apparmor_parser"
[  449.568359] audit: type=1400 audit(1779065160.466:323): apparmor="STATUS" operation="profile_replace" info="same as current profile, skipping" profile="unconfined" name="snap-update-ns.snap-store" pid=9841 comm="apparmor_parser"
[  449.683929] audit: type=1400 audit(1779065160.582:324): apparmor="STATUS" operation="profile_replace" profile="unconfined" name="snap.snap-store.hook.configure" pid=9842 comm="apparmor_parser"
[  468.198112] loop16: detected capacity change from 0 to 8
[  468.299587] kauditd_printk_skb: 15 callbacks suppressed
[  468.299590] audit: type=1400 audit(1779065179.196:340): apparmor="STATUS" operation="profile_replace" info="same as current profile, skipping" profile="unconfined" name="/usr/lib/snapd/snap-confine" pid=10084 comm="apparmor_parser"
[  468.299883] audit: type=1400 audit(1779065179.196:341): apparmor="STATUS" operation="profile_replace" info="same as current profile, skipping" profile="unconfined" name="/usr/lib/snapd/snap-confine//mount-namespace-capture-helper" pid=10084 comm="apparmor_parser"
[  469.102120] audit: type=1400 audit(1779065180.007:342): apparmor="STATUS" operation="profile_replace" info="same as current profile, skipping" profile="unconfined" name="snap-update-ns.firefox" pid=10290 comm="apparmor_parser"
[  469.102812] audit: type=1400 audit(1779065180.007:343): apparmor="STATUS" operation="profile_replace" profile="unconfined" name="/snap/snapd/25935/usr/lib/snapd/snap-confine" pid=10288 comm="apparmor_parser"
[  469.106898] audit: type=1400 audit(1779065180.013:344): apparmor="STATUS" operation="profile_replace" profile="unconfined" name="/snap/snapd/25935/usr/lib/snapd/snap-confine//mount-namespace-capture-helper" pid=10288 comm="apparmor_parser"
[  469.107564] audit: type=1400 audit(1779065180.013:345): apparmor="STATUS" operation="profile_replace" info="same as current profile, skipping" profile="unconfined" name="snap-update-ns.firmware-updater" pid=10291 comm="apparmor_parser"
[  469.111786] audit: type=1400 audit(1779065180.017:346): apparmor="STATUS" operation="profile_replace" info="same as current profile, skipping" profile="unconfined" name="snap-update-ns.mesa-2404" pid=10292 comm="apparmor_parser"
[  469.115094] audit: type=1400 audit(1779065180.019:347): apparmor="STATUS" operation="profile_replace" info="same as current profile, skipping" profile="unconfined" name="snap-update-ns.snap-store" pid=10293 comm="apparmor_parser"
[  469.116599] audit: type=1400 audit(1779065180.022:348): apparmor="STATUS" operation="profile_replace" info="same as current profile, skipping" profile="unconfined" name="snap-update-ns.snapd-desktop-integration" pid=10294 comm="apparmor_parser"
[  469.123664] audit: type=1400 audit(1779065180.029:349): apparmor="STATUS" operation="profile_replace" info="same as current profile, skipping" profile="unconfined" name="snap.firefox.firefox" pid=10299 comm="apparmor_parser"
[  662.501568] kauditd_printk_skb: 19 callbacks suppressed
[  662.501571] audit: type=1400 audit(1779065373.409:369): apparmor="DENIED" operation="open" class="file" profile="snap.firefox.firefox" name="/etc/vulkan/implicit_layer.d/" pid=15251 comm="glxtest" requested_mask="r" denied_mask="r" fsuid=1000 ouid=0
[  662.504857] audit: type=1400 audit(1779065373.412:370): apparmor="DENIED" operation="open" class="file" profile="snap.firefox.firefox" name="/etc/vulkan/implicit_layer.d/" pid=15251 comm="glxtest" requested_mask="r" denied_mask="r" fsuid=1000 ouid=0
[  662.505445] audit: type=1400 audit(1779065373.412:371): apparmor="DENIED" operation="open" class="file" profile="snap.firefox.firefox" name="/etc/vulkan/icd.d/" pid=15251 comm="glxtest" requested_mask="r" denied_mask="r" fsuid=1000 ouid=0
[  662.624950] audit: type=1400 audit(1779065373.533:372): apparmor="DENIED" operation="open" class="file" profile="snap.firefox.firefox" name="/etc/vulkan/icd.d/" pid=15251 comm="glxtest" requested_mask="r" denied_mask="r" fsuid=1000 ouid=0
[  662.626218] audit: type=1400 audit(1779065373.534:373): apparmor="DENIED" operation="open" class="file" profile="snap.firefox.firefox" name="/etc/vulkan/implicit_layer.d/" pid=15251 comm="glxtest" requested_mask="r" denied_mask="r" fsuid=1000 ouid=0
[  662.627246] audit: type=1400 audit(1779065373.535:374): apparmor="DENIED" operation="open" class="file" profile="snap.firefox.firefox" name="/etc/vulkan/implicit_layer.d/" pid=15251 comm="glxtest" requested_mask="r" denied_mask="r" fsuid=1000 ouid=0
[  662.627898] audit: type=1400 audit(1779065373.536:375): apparmor="DENIED" operation="open" class="file" profile="snap.firefox.firefox" name="/etc/vulkan/icd.d/" pid=15251 comm="glxtest" requested_mask="r" denied_mask="r" fsuid=1000 ouid=0
[  662.628922] audit: type=1400 audit(1779065373.537:376): apparmor="DENIED" operation="open" class="file" profile="snap.firefox.firefox" name="/etc/vulkan/implicit_layer.d/" pid=15251 comm="glxtest" requested_mask="r" denied_mask="r" fsuid=1000 ouid=0
[  662.629677] audit: type=1400 audit(1779065373.538:377): apparmor="DENIED" operation="open" class="file" profile="snap.firefox.firefox" name="/etc/vulkan/implicit_layer.d/" pid=15251 comm="glxtest" requested_mask="r" denied_mask="r" fsuid=1000 ouid=0
[  662.630391] audit: type=1400 audit(1779065373.538:378): apparmor="DENIED" operation="open" class="file" profile="snap.firefox.firefox" name="/etc/vulkan/implicit_layer.d/" pid=15251 comm="glxtest" requested_mask="r" denied_mask="r" fsuid=1000 ouid=0
[  674.214579] kauditd_printk_skb: 8 callbacks suppressed
[  674.214583] audit: type=1400 audit(1779065385.122:387): apparmor="DENIED" operation="open" class="file" profile="snap.firefox.firefox" name="/proc/pressure/memory" pid=15168 comm="MemoryPoller" requested_mask="r" denied_mask="r" fsuid=1000 ouid=0
[  679.215609] audit: type=1400 audit(1779065390.122:388): apparmor="DENIED" operation="open" class="file" profile="snap.firefox.firefox" name="/proc/pressure/memory" pid=15168 comm="MemoryPoller" requested_mask="r" denied_mask="r" fsuid=1000 ouid=0
[  684.216558] audit: type=1400 audit(1779065395.123:389): apparmor="DENIED" operation="open" class="file" profile="snap.firefox.firefox" name="/proc/pressure/memory" pid=15168 comm="MemoryPoller" requested_mask="r" denied_mask="r" fsuid=1000 ouid=0
[  689.310512] audit: type=1400 audit(1779065400.216:390): apparmor="DENIED" operation="open" class="file" profile="snap.firefox.firefox" name="/proc/pressure/memory" pid=15168 comm="MemoryPoller" requested_mask="r" denied_mask="r" fsuid=1000 ouid=0
[  694.325304] audit: type=1400 audit(1779065405.232:391): apparmor="DENIED" operation="open" class="file" profile="snap.firefox.firefox" name="/proc/pressure/memory" pid=15168 comm="MemoryPoller" requested_mask="r" denied_mask="r" fsuid=1000 ouid=0
[  699.361554] audit: type=1400 audit(1779065410.268:392): apparmor="DENIED" operation="open" class="file" profile="snap.firefox.firefox" name="/proc/pressure/memory" pid=15168 comm="MemoryPoller" requested_mask="r" denied_mask="r" fsuid=1000 ouid=0
[  704.498199] audit: type=1400 audit(1779065415.405:393): apparmor="DENIED" operation="open" class="file" profile="snap.firefox.firefox" name="/proc/pressure/memory" pid=15168 comm="MemoryPoller" requested_mask="r" denied_mask="r" fsuid=1000 ouid=0
[  722.393297] audit: type=1400 audit(1779065433.298:394): apparmor="DENIED" operation="open" class="file" profile="snap.firefox.firefox" name="/proc/pressure/memory" pid=15168 comm="MemoryPoller" requested_mask="r" denied_mask="r" fsuid=1000 ouid=0
[  727.401501] audit: type=1400 audit(1779065438.307:395): apparmor="DENIED" operation="open" class="file" profile="snap.firefox.firefox" name="/proc/pressure/memory" pid=15168 comm="MemoryPoller" requested_mask="r" denied_mask="r" fsuid=1000 ouid=0
[  732.410933] audit: type=1400 audit(1779065443.317:396): apparmor="DENIED" operation="open" class="file" profile="snap.firefox.firefox" name="/proc/pressure/memory" pid=15168 comm="MemoryPoller" requested_mask="r" denied_mask="r" fsuid=1000 ouid=0
[  737.488366] audit: type=1400 audit(1779065448.393:397): apparmor="DENIED" operation="open" class="file" profile="snap.firefox.firefox" name="/proc/pressure/memory" pid=15168 comm="MemoryPoller" requested_mask="r" denied_mask="r" fsuid=1000 ouid=0
[  742.492997] audit: type=1400 audit(1779065453.399:398): apparmor="DENIED" operation="open" class="file" profile="snap.firefox.firefox" name="/proc/pressure/memory" pid=15168 comm="MemoryPoller" requested_mask="r" denied_mask="r" fsuid=1000 ouid=0
[  747.509765] audit: type=1400 audit(1779065458.415:399): apparmor="DENIED" operation="open" class="file" profile="snap.firefox.firefox" name="/proc/pressure/memory" pid=15168 comm="MemoryPoller" requested_mask="r" denied_mask="r" fsuid=1000 ouid=0
[  752.514772] audit: type=1400 audit(1779065463.421:400): apparmor="DENIED" operation="open" class="file" profile="snap.firefox.firefox" name="/proc/pressure/memory" pid=15168 comm="MemoryPoller" requested_mask="r" denied_mask="r" fsuid=1000 ouid=0
[  757.554865] audit: type=1400 audit(1779065468.461:401): apparmor="DENIED" operation="open" class="file" profile="snap.firefox.firefox" name="/proc/pressure/memory" pid=15168 comm="MemoryPoller" requested_mask="r" denied_mask="r" fsuid=1000 ouid=0
[  762.555810] audit: type=1400 audit(1779065473.462:402): apparmor="DENIED" operation="open" class="file" profile="snap.firefox.firefox" name="/proc/pressure/memory" pid=15168 comm="MemoryPoller" requested_mask="r" denied_mask="r" fsuid=1000 ouid=0
[  768.007293] audit: type=1400 audit(1779065478.913:403): apparmor="DENIED" operation="open" class="file" profile="snap.firefox.firefox" name="/proc/pressure/memory" pid=15168 comm="MemoryPoller" requested_mask="r" denied_mask="r" fsuid=1000 ouid=0
[  773.078921] audit: type=1400 audit(1779065483.985:404): apparmor="DENIED" operation="open" class="file" profile="snap.firefox.firefox" name="/proc/pressure/memory" pid=15168 comm="MemoryPoller" requested_mask="r" denied_mask="r" fsuid=1000 ouid=0
[  778.380732] audit: type=1400 audit(1779065489.287:405): apparmor="DENIED" operation="open" class="file" profile="snap.firefox.firefox" name="/proc/pressure/memory" pid=15168 comm="MemoryPoller" requested_mask="r" denied_mask="r" fsuid=1000 ouid=0
[  783.381692] audit: type=1400 audit(1779065494.287:406): apparmor="DENIED" operation="open" class="file" profile="snap.firefox.firefox" name="/proc/pressure/memory" pid=15168 comm="MemoryPoller" requested_mask="r" denied_mask="r" fsuid=1000 ouid=0
[  788.392385] audit: type=1400 audit(1779065499.298:407): apparmor="DENIED" operation="open" class="file" profile="snap.firefox.firefox" name="/proc/pressure/memory" pid=15168 comm="MemoryPoller" requested_mask="r" denied_mask="r" fsuid=1000 ouid=0
[  793.461888] audit: type=1400 audit(1779065504.368:408): apparmor="DENIED" operation="open" class="file" profile="snap.firefox.firefox" name="/proc/pressure/memory" pid=15168 comm="MemoryPoller" requested_mask="r" denied_mask="r" fsuid=1000 ouid=0
[  796.192809] audit: type=1400 audit(1779065507.099:409): apparmor="DENIED" operation="open" class="file" profile="snap.firefox.firefox" name="/etc/vulkan/implicit_layer.d/" pid=15168 comm="CanvasRenderer" requested_mask="r" denied_mask="r" fsuid=1000 ouid=0
[  796.195015] audit: type=1400 audit(1779065507.100:410): apparmor="DENIED" operation="open" class="file" profile="snap.firefox.firefox" name="/etc/vulkan/implicit_layer.d/" pid=15168 comm="CanvasRenderer" requested_mask="r" denied_mask="r" fsuid=1000 ouid=0
[  796.195020] audit: type=1400 audit(1779065507.100:411): apparmor="DENIED" operation="open" class="file" profile="snap.firefox.firefox" name="/etc/vulkan/icd.d/" pid=15168 comm="CanvasRenderer" requested_mask="r" denied_mask="r" fsuid=1000 ouid=0
[  796.235571] audit: type=1400 audit(1779065507.142:412): apparmor="DENIED" operation="open" class="file" profile="snap.firefox.firefox" name="/etc/vulkan/icd.d/" pid=15168 comm="CanvasRenderer" requested_mask="r" denied_mask="r" fsuid=1000 ouid=0
[  796.236816] audit: type=1400 audit(1779065507.143:413): apparmor="DENIED" operation="open" class="file" profile="snap.firefox.firefox" name="/etc/vulkan/implicit_layer.d/" pid=15168 comm="CanvasRenderer" requested_mask="r" denied_mask="r" fsuid=1000 ouid=0
[  796.237855] audit: type=1400 audit(1779065507.143:414): apparmor="DENIED" operation="open" class="file" profile="snap.firefox.firefox" name="/etc/vulkan/implicit_layer.d/" pid=15168 comm="CanvasRenderer" requested_mask="r" denied_mask="r" fsuid=1000 ouid=0
[  796.237859] audit: type=1400 audit(1779065507.144:415): apparmor="DENIED" operation="open" class="file" profile="snap.firefox.firefox" name="/etc/vulkan/icd.d/" pid=15168 comm="CanvasRenderer" requested_mask="r" denied_mask="r" fsuid=1000 ouid=0
[  796.238901] audit: type=1400 audit(1779065507.145:416): apparmor="DENIED" operation="open" class="file" profile="snap.firefox.firefox" name="/etc/vulkan/implicit_layer.d/" pid=15168 comm="CanvasRenderer" requested_mask="r" denied_mask="r" fsuid=1000 ouid=0
[  796.239617] audit: type=1400 audit(1779065507.145:417): apparmor="DENIED" operation="open" class="file" profile="snap.firefox.firefox" name="/etc/vulkan/implicit_layer.d/" pid=15168 comm="CanvasRenderer" requested_mask="r" denied_mask="r" fsuid=1000 ouid=0
[  798.468228] kauditd_printk_skb: 8 callbacks suppressed
[  798.468231] audit: type=1400 audit(1779065509.374:426): apparmor="DENIED" operation="open" class="file" profile="snap.firefox.firefox" name="/proc/pressure/memory" pid=15168 comm="MemoryPoller" requested_mask="r" denied_mask="r" fsuid=1000 ouid=0
[  803.517242] audit: type=1400 audit(1779065514.423:427): apparmor="DENIED" operation="open" class="file" profile="snap.firefox.firefox" name="/proc/pressure/memory" pid=15168 comm="MemoryPoller" requested_mask="r" denied_mask="r" fsuid=1000 ouid=0
[  813.701601] audit: type=1400 audit(1779065524.607:428): apparmor="DENIED" operation="open" class="file" profile="snap.firefox.firefox" name="/proc/pressure/memory" pid=15168 comm="MemoryPoller" requested_mask="r" denied_mask="r" fsuid=1000 ouid=0
[  969.044253] audit: type=1400 audit(1779065679.952:429): apparmor="DENIED" operation="open" class="file" profile="snap.firefox.firefox" name="/proc/pressure/memory" pid=15168 comm="MemoryPoller" requested_mask="r" denied_mask="r" fsuid=1000 ouid=0
[  979.154624] audit: type=1400 audit(1779065690.063:430): apparmor="DENIED" operation="open" class="file" profile="snap.firefox.firefox" name="/proc/pressure/memory" pid=15168 comm="MemoryPoller" requested_mask="r" denied_mask="r" fsuid=1000 ouid=0
[  984.156304] audit: type=1400 audit(1779065695.064:431): apparmor="DENIED" operation="open" class="file" profile="snap.firefox.firefox" name="/proc/pressure/memory" pid=15168 comm="MemoryPoller" requested_mask="r" denied_mask="r" fsuid=1000 ouid=0
[  989.156744] audit: type=1400 audit(1779065700.065:432): apparmor="DENIED" operation="open" class="file" profile="snap.firefox.firefox" name="/proc/pressure/memory" pid=15168 comm="MemoryPoller" requested_mask="r" denied_mask="r" fsuid=1000 ouid=0
[  998.375646] audit: type=1400 audit(1779065709.284:433): apparmor="DENIED" operation="open" class="file" profile="snap.firefox.firefox" name="/proc/pressure/memory" pid=15168 comm="MemoryPoller" requested_mask="r" denied_mask="r" fsuid=1000 ouid=0
[ 1003.421591] audit: type=1400 audit(1779065714.330:434): apparmor="DENIED" operation="open" class="file" profile="snap.firefox.firefox" name="/proc/pressure/memory" pid=15168 comm="MemoryPoller" requested_mask="r" denied_mask="r" fsuid=1000 ouid=0
[ 1008.447756] audit: type=1400 audit(1779065719.357:435): apparmor="DENIED" operation="open" class="file" profile="snap.firefox.firefox" name="/proc/pressure/memory" pid=15168 comm="MemoryPoller" requested_mask="r" denied_mask="r" fsuid=1000 ouid=0
[ 1013.490766] audit: type=1400 audit(1779065724.400:436): apparmor="DENIED" operation="open" class="file" profile="snap.firefox.firefox" name="/proc/pressure/memory" pid=15168 comm="MemoryPoller" requested_mask="r" denied_mask="r" fsuid=1000 ouid=0
[ 1018.491639] audit: type=1400 audit(1779065729.401:437): apparmor="DENIED" operation="open" class="file" profile="snap.firefox.firefox" name="/proc/pressure/memory" pid=15168 comm="MemoryPoller" requested_mask="r" denied_mask="r" fsuid=1000 ouid=0
[ 1045.295139] audit: type=1400 audit(1779065756.204:438): apparmor="DENIED" operation="open" class="file" profile="snap.firefox.firefox" name="/proc/pressure/memory" pid=15168 comm="MemoryPoller" requested_mask="r" denied_mask="r" fsuid=1000 ouid=0
[ 1050.404431] audit: type=1400 audit(1779065761.313:439): apparmor="DENIED" operation="open" class="file" profile="snap.firefox.firefox" name="/proc/pressure/memory" pid=15168 comm="MemoryPoller" requested_mask="r" denied_mask="r" fsuid=1000 ouid=0
[ 1091.750129] audit: type=1400 audit(1779065802.660:440): apparmor="DENIED" operation="open" class="file" profile="snap.firefox.firefox" name="/proc/pressure/memory" pid=15168 comm="MemoryPoller" requested_mask="r" denied_mask="r" fsuid=1000 ouid=0
[ 1096.755807] audit: type=1400 audit(1779065807.666:441): apparmor="DENIED" operation="open" class="file" profile="snap.firefox.firefox" name="/proc/pressure/memory" pid=15168 comm="MemoryPoller" requested_mask="r" denied_mask="r" fsuid=1000 ouid=0
[ 1101.756957] audit: type=1400 audit(1779065812.666:442): apparmor="DENIED" operation="open" class="file" profile="snap.firefox.firefox" name="/proc/pressure/memory" pid=15168 comm="MemoryPoller" requested_mask="r" denied_mask="r" fsuid=1000 ouid=0
[ 1106.833825] audit: type=1400 audit(1779065817.743:443): apparmor="DENIED" operation="open" class="file" profile="snap.firefox.firefox" name="/proc/pressure/memory" pid=15168 comm="MemoryPoller" requested_mask="r" denied_mask="r" fsuid=1000 ouid=0
[ 1179.307876] audit: type=1400 audit(1779065890.219:444): apparmor="DENIED" operation="open" class="file" profile="snap.firefox.firefox" name="/proc/pressure/memory" pid=15168 comm="MemoryPoller" requested_mask="r" denied_mask="r" fsuid=1000 ouid=0
[ 1184.309734] audit: type=1400 audit(1779065895.221:445): apparmor="DENIED" operation="open" class="file" profile="snap.firefox.firefox" name="/proc/pressure/memory" pid=15168 comm="MemoryPoller" requested_mask="r" denied_mask="r" fsuid=1000 ouid=0
[ 1189.373327] audit: type=1400 audit(1779065900.285:446): apparmor="DENIED" operation="open" class="file" profile="snap.firefox.firefox" name="/proc/pressure/memory" pid=15168 comm="MemoryPoller" requested_mask="r" denied_mask="r" fsuid=1000 ouid=0
[ 1194.413450] audit: type=1400 audit(1779065905.324:447): apparmor="DENIED" operation="open" class="file" profile="snap.firefox.firefox" name="/proc/pressure/memory" pid=15168 comm="MemoryPoller" requested_mask="r" denied_mask="r" fsuid=1000 ouid=0
[ 1199.414433] audit: type=1400 audit(1779065910.325:448): apparmor="DENIED" operation="open" class="file" profile="snap.firefox.firefox" name="/proc/pressure/memory" pid=15168 comm="MemoryPoller" requested_mask="r" denied_mask="r" fsuid=1000 ouid=0
[ 1204.426694] audit: type=1400 audit(1779065915.337:449): apparmor="DENIED" operation="open" class="file" profile="snap.firefox.firefox" name="/proc/pressure/memory" pid=15168 comm="MemoryPoller" requested_mask="r" denied_mask="r" fsuid=1000 ouid=0
[ 1214.487556] audit: type=1400 audit(1779065925.399:450): apparmor="DENIED" operation="open" class="file" profile="snap.firefox.firefox" name="/proc/pressure/memory" pid=15168 comm="MemoryPoller" requested_mask="r" denied_mask="r" fsuid=1000 ouid=0
[ 1219.488237] audit: type=1400 audit(1779065930.399:451): apparmor="DENIED" operation="open" class="file" profile="snap.firefox.firefox" name="/proc/pressure/memory" pid=15168 comm="MemoryPoller" requested_mask="r" denied_mask="r" fsuid=1000 ouid=0
[ 1224.491180] audit: type=1400 audit(1779065935.402:452): apparmor="DENIED" operation="open" class="file" profile="snap.firefox.firefox" name="/proc/pressure/memory" pid=15168 comm="MemoryPoller" requested_mask="r" denied_mask="r" fsuid=1000 ouid=0
[ 1229.491866] audit: type=1400 audit(1779065940.403:453): apparmor="DENIED" operation="open" class="file" profile="snap.firefox.firefox" name="/proc/pressure/memory" pid=15168 comm="MemoryPoller" requested_mask="r" denied_mask="r" fsuid=1000 ouid=0
[ 1234.519332] audit: type=1400 audit(1779065945.430:454): apparmor="DENIED" operation="open" class="file" profile="snap.firefox.firefox" name="/proc/pressure/memory" pid=15168 comm="MemoryPoller" requested_mask="r" denied_mask="r" fsuid=1000 ouid=0
[ 1239.544068] audit: type=1400 audit(1779065950.455:455): apparmor="DENIED" operation="open" class="file" profile="snap.firefox.firefox" name="/proc/pressure/memory" pid=15168 comm="MemoryPoller" requested_mask="r" denied_mask="r" fsuid=1000 ouid=0
[ 1245.052909] audit: type=1400 audit(1779065955.965:456): apparmor="DENIED" operation="open" class="file" profile="snap.firefox.firefox" name="/proc/pressure/memory" pid=15168 comm="MemoryPoller" requested_mask="r" denied_mask="r" fsuid=1000 ouid=0
[ 1250.057223] audit: type=1400 audit(1779065960.969:457): apparmor="DENIED" operation="open" class="file" profile="snap.firefox.firefox" name="/proc/pressure/memory" pid=15168 comm="MemoryPoller" requested_mask="r" denied_mask="r" fsuid=1000 ouid=0
[ 1255.057920] audit: type=1400 audit(1779065965.970:458): apparmor="DENIED" operation="open" class="file" profile="snap.firefox.firefox" name="/proc/pressure/memory" pid=15168 comm="MemoryPoller" requested_mask="r" denied_mask="r" fsuid=1000 ouid=0
[ 1260.340575] audit: type=1400 audit(1779065971.252:459): apparmor="DENIED" operation="open" class="file" profile="snap.firefox.firefox" name="/proc/pressure/memory" pid=15168 comm="MemoryPoller" requested_mask="r" denied_mask="r" fsuid=1000 ouid=0
[ 1265.350827] audit: type=1400 audit(1779065976.263:460): apparmor="DENIED" operation="open" class="file" profile="snap.firefox.firefox" name="/proc/pressure/memory" pid=15168 comm="MemoryPoller" requested_mask="r" denied_mask="r" fsuid=1000 ouid=0
[ 1282.321249] audit: type=1400 audit(1779065993.233:461): apparmor="DENIED" operation="open" class="file" profile="snap.firefox.firefox" name="/proc/pressure/memory" pid=15168 comm="MemoryPoller" requested_mask="r" denied_mask="r" fsuid=1000 ouid=0
[ 1287.331155] audit: type=1400 audit(1779065998.243:462): apparmor="DENIED" operation="open" class="file" profile="snap.firefox.firefox" name="/proc/pressure/memory" pid=15168 comm="MemoryPoller" requested_mask="r" denied_mask="r" fsuid=1000 ouid=0
[ 1297.409811] audit: type=1400 audit(1779066008.322:463): apparmor="DENIED" operation="open" class="file" profile="snap.firefox.firefox" name="/proc/pressure/memory" pid=15168 comm="MemoryPoller" requested_mask="r" denied_mask="r" fsuid=1000 ouid=0
[ 1307.501780] audit: type=1400 audit(1779066018.414:464): apparmor="DENIED" operation="open" class="file" profile="snap.firefox.firefox" name="/proc/pressure/memory" pid=15168 comm="MemoryPoller" requested_mask="r" denied_mask="r" fsuid=1000 ouid=0
[ 1312.502539] audit: type=1400 audit(1779066023.414:465): apparmor="DENIED" operation="open" class="file" profile="snap.firefox.firefox" name="/proc/pressure/memory" pid=15168 comm="MemoryPoller" requested_mask="r" denied_mask="r" fsuid=1000 ouid=0
[ 1317.592710] audit: type=1400 audit(1779066028.505:466): apparmor="DENIED" operation="open" class="file" profile="snap.firefox.firefox" name="/proc/pressure/memory" pid=15168 comm="MemoryPoller" requested_mask="r" denied_mask="r" fsuid=1000 ouid=0
[ 1327.704984] audit: type=1400 audit(1779066038.617:467): apparmor="DENIED" operation="open" class="file" profile="snap.firefox.firefox" name="/proc/pressure/memory" pid=15168 comm="MemoryPoller" requested_mask="r" denied_mask="r" fsuid=1000 ouid=0
[ 1332.736246] audit: type=1400 audit(1779066043.648:468): apparmor="DENIED" operation="open" class="file" profile="snap.firefox.firefox" name="/proc/pressure/memory" pid=15168 comm="MemoryPoller" requested_mask="r" denied_mask="r" fsuid=1000 ouid=0
[ 1337.775695] audit: type=1400 audit(1779066048.687:469): apparmor="DENIED" operation="open" class="file" profile="snap.firefox.firefox" name="/proc/pressure/memory" pid=15168 comm="MemoryPoller" requested_mask="r" denied_mask="r" fsuid=1000 ouid=0
[ 1342.978601] audit: type=1400 audit(1779066053.890:470): apparmor="DENIED" operation="open" class="file" profile="snap.firefox.firefox" name="/proc/pressure/memory" pid=15168 comm="MemoryPoller" requested_mask="r" denied_mask="r" fsuid=1000 ouid=0
[ 1461.862641] audit: type=1400 audit(1779066172.776:471): apparmor="DENIED" operation="open" class="file" profile="snap.firefox.firefox" name="/proc/pressure/memory" pid=15168 comm="MemoryPoller" requested_mask="r" denied_mask="r" fsuid=1000 ouid=0
[ 1466.884501] audit: type=1400 audit(1779066177.798:472): apparmor="DENIED" operation="open" class="file" profile="snap.firefox.firefox" name="/proc/pressure/memory" pid=15168 comm="MemoryPoller" requested_mask="r" denied_mask="r" fsuid=1000 ouid=0
[ 1471.885531] audit: type=1400 audit(1779066182.799:473): apparmor="DENIED" operation="open" class="file" profile="snap.firefox.firefox" name="/proc/pressure/memory" pid=15168 comm="MemoryPoller" requested_mask="r" denied_mask="r" fsuid=1000 ouid=0
[ 1489.753986] audit: type=1400 audit(1779066200.668:474): apparmor="DENIED" operation="open" class="file" profile="snap.firefox.firefox" name="/proc/pressure/memory" pid=15168 comm="MemoryPoller" requested_mask="r" denied_mask="r" fsuid=1000 ouid=0
[ 1494.754596] audit: type=1400 audit(1779066205.669:475): apparmor="DENIED" operation="open" class="file" profile="snap.firefox.firefox" name="/proc/pressure/memory" pid=15168 comm="MemoryPoller" requested_mask="r" denied_mask="r" fsuid=1000 ouid=0
[ 1499.836723] audit: type=1400 audit(1779066210.751:476): apparmor="DENIED" operation="open" class="file" profile="snap.firefox.firefox" name="/proc/pressure/memory" pid=15168 comm="MemoryPoller" requested_mask="r" denied_mask="r" fsuid=1000 ouid=0
[ 1504.877631] audit: type=1400 audit(1779066215.792:477): apparmor="DENIED" operation="open" class="file" profile="snap.firefox.firefox" name="/proc/pressure/memory" pid=15168 comm="MemoryPoller" requested_mask="r" denied_mask="r" fsuid=1000 ouid=0
[ 1509.950421] audit: type=1400 audit(1779066220.865:478): apparmor="DENIED" operation="open" class="file" profile="snap.firefox.firefox" name="/proc/pressure/memory" pid=15168 comm="MemoryPoller" requested_mask="r" denied_mask="r" fsuid=1000 ouid=0
[ 1514.955573] audit: type=1400 audit(1779066225.870:479): apparmor="DENIED" operation="open" class="file" profile="snap.firefox.firefox" name="/proc/pressure/memory" pid=15168 comm="MemoryPoller" requested_mask="r" denied_mask="r" fsuid=1000 ouid=0
[ 1533.367492] audit: type=1400 audit(1779066244.282:480): apparmor="DENIED" operation="open" class="file" profile="snap.firefox.firefox" name="/proc/pressure/memory" pid=15168 comm="MemoryPoller" requested_mask="r" denied_mask="r" fsuid=1000 ouid=0
[ 1538.368561] audit: type=1400 audit(1779066249.283:481): apparmor="DENIED" operation="open" class="file" profile="snap.firefox.firefox" name="/proc/pressure/memory" pid=15168 comm="MemoryPoller" requested_mask="r" denied_mask="r" fsuid=1000 ouid=0
[ 1557.453679] audit: type=1400 audit(1779066268.368:482): apparmor="DENIED" operation="open" class="file" profile="snap.firefox.firefox" name="/proc/pressure/memory" pid=15168 comm="MemoryPoller" requested_mask="r" denied_mask="r" fsuid=1000 ouid=0
[ 1562.535201] audit: type=1400 audit(1779066273.450:483): apparmor="DENIED" operation="open" class="file" profile="snap.firefox.firefox" name="/proc/pressure/memory" pid=15168 comm="MemoryPoller" requested_mask="r" denied_mask="r" fsuid=1000 ouid=0
[ 1567.536072] audit: type=1400 audit(1779066278.451:484): apparmor="DENIED" operation="open" class="file" profile="snap.firefox.firefox" name="/proc/pressure/memory" pid=15168 comm="MemoryPoller" requested_mask="r" denied_mask="r" fsuid=1000 ouid=0
[ 1572.538741] audit: type=1400 audit(1779066283.454:485): apparmor="DENIED" operation="open" class="file" profile="snap.firefox.firefox" name="/proc/pressure/memory" pid=15168 comm="MemoryPoller" requested_mask="r" denied_mask="r" fsuid=1000 ouid=0
[ 1577.592852] audit: type=1400 audit(1779066288.508:486): apparmor="DENIED" operation="open" class="file" profile="snap.firefox.firefox" name="/proc/pressure/memory" pid=15168 comm="MemoryPoller" requested_mask="r" denied_mask="r" fsuid=1000 ouid=0
[ 1582.597963] audit: type=1400 audit(1779066293.513:487): apparmor="DENIED" operation="open" class="file" profile="snap.firefox.firefox" name="/proc/pressure/memory" pid=15168 comm="MemoryPoller" requested_mask="r" denied_mask="r" fsuid=1000 ouid=0
[ 1587.600469] audit: type=1400 audit(1779066298.515:488): apparmor="DENIED" operation="open" class="file" profile="snap.firefox.firefox" name="/proc/pressure/memory" pid=15168 comm="MemoryPoller" requested_mask="r" denied_mask="r" fsuid=1000 ouid=0
[ 1592.601335] audit: type=1400 audit(1779066303.516:489): apparmor="DENIED" operation="open" class="file" profile="snap.firefox.firefox" name="/proc/pressure/memory" pid=15168 comm="MemoryPoller" requested_mask="r" denied_mask="r" fsuid=1000 ouid=0
[ 1597.602578] audit: type=1400 audit(1779066308.518:490): apparmor="DENIED" operation="open" class="file" profile="snap.firefox.firefox" name="/proc/pressure/memory" pid=15168 comm="MemoryPoller" requested_mask="r" denied_mask="r" fsuid=1000 ouid=0
[ 1602.653459] audit: type=1400 audit(1779066313.569:491): apparmor="DENIED" operation="open" class="file" profile="snap.firefox.firefox" name="/proc/pressure/memory" pid=15168 comm="MemoryPoller" requested_mask="r" denied_mask="r" fsuid=1000 ouid=0
[ 1607.653816] audit: type=1400 audit(1779066318.569:492): apparmor="DENIED" operation="open" class="file" profile="snap.firefox.firefox" name="/proc/pressure/memory" pid=15168 comm="MemoryPoller" requested_mask="r" denied_mask="r" fsuid=1000 ouid=0
[ 1612.654792] audit: type=1400 audit(1779066323.570:493): apparmor="DENIED" operation="open" class="file" profile="snap.firefox.firefox" name="/proc/pressure/memory" pid=15168 comm="MemoryPoller" requested_mask="r" denied_mask="r" fsuid=1000 ouid=0
[ 1617.655573] audit: type=1400 audit(1779066328.571:494): apparmor="DENIED" operation="open" class="file" profile="snap.firefox.firefox" name="/proc/pressure/memory" pid=15168 comm="MemoryPoller" requested_mask="r" denied_mask="r" fsuid=1000 ouid=0
[ 1622.672274] audit: type=1400 audit(1779066333.587:495): apparmor="DENIED" operation="open" class="file" profile="snap.firefox.firefox" name="/proc/pressure/memory" pid=15168 comm="MemoryPoller" requested_mask="r" denied_mask="r" fsuid=1000 ouid=0
[ 1627.673122] audit: type=1400 audit(1779066338.588:496): apparmor="DENIED" operation="open" class="file" profile="snap.firefox.firefox" name="/proc/pressure/memory" pid=15168 comm="MemoryPoller" requested_mask="r" denied_mask="r" fsuid=1000 ouid=0
[ 1632.728170] audit: type=1400 audit(1779066343.643:497): apparmor="DENIED" operation="open" class="file" profile="snap.firefox.firefox" name="/proc/pressure/memory" pid=15168 comm="MemoryPoller" requested_mask="r" denied_mask="r" fsuid=1000 ouid=0
[ 1637.783111] audit: type=1400 audit(1779066348.698:498): apparmor="DENIED" operation="open" class="file" profile="snap.firefox.firefox" name="/proc/pressure/memory" pid=15168 comm="MemoryPoller" requested_mask="r" denied_mask="r" fsuid=1000 ouid=0
[ 1642.869567] audit: type=1400 audit(1779066353.784:499): apparmor="DENIED" operation="open" class="file" profile="snap.firefox.firefox" name="/proc/pressure/memory" pid=15168 comm="MemoryPoller" requested_mask="r" denied_mask="r" fsuid=1000 ouid=0
[ 1647.948547] audit: type=1400 audit(1779066358.864:500): apparmor="DENIED" operation="open" class="file" profile="snap.firefox.firefox" name="/proc/pressure/memory" pid=15168 comm="MemoryPoller" requested_mask="r" denied_mask="r" fsuid=1000 ouid=0
[ 1653.028349] audit: type=1400 audit(1779066363.943:501): apparmor="DENIED" operation="open" class="file" profile="snap.firefox.firefox" name="/proc/pressure/memory" pid=15168 comm="MemoryPoller" requested_mask="r" denied_mask="r" fsuid=1000 ouid=0
[ 1658.325081] audit: type=1400 audit(1779066369.240:502): apparmor="DENIED" operation="open" class="file" profile="snap.firefox.firefox" name="/proc/pressure/memory" pid=15168 comm="MemoryPoller" requested_mask="r" denied_mask="r" fsuid=1000 ouid=0
[ 1663.823662] audit: type=1400 audit(1779066374.738:503): apparmor="DENIED" operation="open" class="file" profile="snap.firefox.firefox" name="/proc/pressure/memory" pid=15168 comm="MemoryPoller" requested_mask="r" denied_mask="r" fsuid=1000 ouid=0
[ 1669.409155] audit: type=1400 audit(1779066380.325:504): apparmor="DENIED" operation="open" class="file" profile="snap.firefox.firefox" name="/proc/pressure/memory" pid=15168 comm="MemoryPoller" requested_mask="r" denied_mask="r" fsuid=1000 ouid=0
[ 1674.419364] audit: type=1400 audit(1779066385.335:505): apparmor="DENIED" operation="open" class="file" profile="snap.firefox.firefox" name="/proc/pressure/memory" pid=15168 comm="MemoryPoller" requested_mask="r" denied_mask="r" fsuid=1000 ouid=0
[ 1679.520161] audit: type=1400 audit(1779066390.436:506): apparmor="DENIED" operation="open" class="file" profile="snap.firefox.firefox" name="/proc/pressure/memory" pid=15168 comm="MemoryPoller" requested_mask="r" denied_mask="r" fsuid=1000 ouid=0
[ 1684.567922] audit: type=1400 audit(1779066395.484:507): apparmor="DENIED" operation="open" class="file" profile="snap.firefox.firefox" name="/proc/pressure/memory" pid=15168 comm="MemoryPoller" requested_mask="r" denied_mask="r" fsuid=1000 ouid=0
[ 1689.780637] audit: type=1400 audit(1779066400.697:508): apparmor="DENIED" operation="open" class="file" profile="snap.firefox.firefox" name="/proc/pressure/memory" pid=15168 comm="MemoryPoller" requested_mask="r" denied_mask="r" fsuid=1000 ouid=0
[ 1715.593583] audit: type=1400 audit(1779066426.510:509): apparmor="DENIED" operation="open" class="file" profile="snap.firefox.firefox" name="/proc/pressure/memory" pid=15168 comm="MemoryPoller" requested_mask="r" denied_mask="r" fsuid=1000 ouid=0
[ 1720.788081] audit: type=1400 audit(1779066431.704:510): apparmor="DENIED" operation="open" class="file" profile="snap.firefox.firefox" name="/proc/pressure/memory" pid=15168 comm="MemoryPoller" requested_mask="r" denied_mask="r" fsuid=1000 ouid=0
[ 1725.794832] audit: type=1400 audit(1779066436.711:511): apparmor="DENIED" operation="open" class="file" profile="snap.firefox.firefox" name="/proc/pressure/memory" pid=15168 comm="MemoryPoller" requested_mask="r" denied_mask="r" fsuid=1000 ouid=0
[ 1763.601774] audit: type=1400 audit(1779066474.518:512): apparmor="DENIED" operation="open" class="file" profile="snap.firefox.firefox" name="/proc/pressure/memory" pid=15168 comm="MemoryPoller" requested_mask="r" denied_mask="r" fsuid=1000 ouid=0
[ 1768.602205] audit: type=1400 audit(1779066479.518:513): apparmor="DENIED" operation="open" class="file" profile="snap.firefox.firefox" name="/proc/pressure/memory" pid=15168 comm="MemoryPoller" requested_mask="r" denied_mask="r" fsuid=1000 ouid=0
[ 1773.694914] audit: type=1400 audit(1779066484.611:514): apparmor="DENIED" operation="open" class="file" profile="snap.firefox.firefox" name="/proc/pressure/memory" pid=15168 comm="MemoryPoller" requested_mask="r" denied_mask="r" fsuid=1000 ouid=0
[ 1778.766287] audit: type=1400 audit(1779066489.682:515): apparmor="DENIED" operation="open" class="file" profile="snap.firefox.firefox" name="/proc/pressure/memory" pid=15168 comm="MemoryPoller" requested_mask="r" denied_mask="r" fsuid=1000 ouid=0
[ 1790.478901] audit: type=1400 audit(1779066501.396:516): apparmor="DENIED" operation="open" class="file" profile="snap.firefox.firefox" name="/proc/pressure/memory" pid=15168 comm="MemoryPoller" requested_mask="r" denied_mask="r" fsuid=1000 ouid=0
[ 1809.087817] audit: type=1400 audit(1779066520.005:517): apparmor="DENIED" operation="open" class="file" profile="snap.firefox.firefox" name="/proc/pressure/memory" pid=15168 comm="MemoryPoller" requested_mask="r" denied_mask="r" fsuid=1000 ouid=0
[ 1814.088426] audit: type=1400 audit(1779066525.006:518): apparmor="DENIED" operation="open" class="file" profile="snap.firefox.firefox" name="/proc/pressure/memory" pid=15168 comm="MemoryPoller" requested_mask="r" denied_mask="r" fsuid=1000 ouid=0
[ 1819.088681] audit: type=1400 audit(1779066530.006:519): apparmor="DENIED" operation="open" class="file" profile="snap.firefox.firefox" name="/proc/pressure/memory" pid=15168 comm="MemoryPoller" requested_mask="r" denied_mask="r" fsuid=1000 ouid=0
[ 1824.089442] audit: type=1400 audit(1779066535.007:520): apparmor="DENIED" operation="open" class="file" profile="snap.firefox.firefox" name="/proc/pressure/memory" pid=15168 comm="MemoryPoller" requested_mask="r" denied_mask="r" fsuid=1000 ouid=0
[ 1834.099292] audit: type=1400 audit(1779066545.017:521): apparmor="DENIED" operation="open" class="file" profile="snap.firefox.firefox" name="/proc/pressure/memory" pid=15168 comm="MemoryPoller" requested_mask="r" denied_mask="r" fsuid=1000 ouid=0
[ 1839.190156] audit: type=1400 audit(1779066550.108:522): apparmor="DENIED" operation="open" class="file" profile="snap.firefox.firefox" name="/proc/pressure/memory" pid=15168 comm="MemoryPoller" requested_mask="r" denied_mask="r" fsuid=1000 ouid=0
[ 1844.237793] audit: type=1400 audit(1779066555.155:523): apparmor="DENIED" operation="open" class="file" profile="snap.firefox.firefox" name="/proc/pressure/memory" pid=15168 comm="MemoryPoller" requested_mask="r" denied_mask="r" fsuid=1000 ouid=0
[ 1849.238717] audit: type=1400 audit(1779066560.156:524): apparmor="DENIED" operation="open" class="file" profile="snap.firefox.firefox" name="/proc/pressure/memory" pid=15168 comm="MemoryPoller" requested_mask="r" denied_mask="r" fsuid=1000 ouid=0
[ 1854.240136] audit: type=1400 audit(1779066565.156:525): apparmor="DENIED" operation="open" class="file" profile="snap.firefox.firefox" name="/proc/pressure/memory" pid=15168 comm="MemoryPoller" requested_mask="r" denied_mask="r" fsuid=1000 ouid=0
[ 1859.367915] audit: type=1400 audit(1779066570.285:526): apparmor="DENIED" operation="open" class="file" profile="snap.firefox.firefox" name="/proc/pressure/memory" pid=15168 comm="MemoryPoller" requested_mask="r" denied_mask="r" fsuid=1000 ouid=0
[ 1864.481890] audit: type=1400 audit(1779066575.399:527): apparmor="DENIED" operation="open" class="file" profile="snap.firefox.firefox" name="/proc/pressure/memory" pid=15168 comm="MemoryPoller" requested_mask="r" denied_mask="r" fsuid=1000 ouid=0
[ 1874.491911] audit: type=1400 audit(1779066585.409:528): apparmor="DENIED" operation="open" class="file" profile="snap.firefox.firefox" name="/proc/pressure/memory" pid=15168 comm="MemoryPoller" requested_mask="r" denied_mask="r" fsuid=1000 ouid=0
[ 1879.493034] audit: type=1400 audit(1779066590.410:529): apparmor="DENIED" operation="open" class="file" profile="snap.firefox.firefox" name="/proc/pressure/memory" pid=15168 comm="MemoryPoller" requested_mask="r" denied_mask="r" fsuid=1000 ouid=0
[ 1889.628033] audit: type=1400 audit(1779066600.545:530): apparmor="DENIED" operation="open" class="file" profile="snap.firefox.firefox" name="/proc/pressure/memory" pid=15168 comm="MemoryPoller" requested_mask="r" denied_mask="r" fsuid=1000 ouid=0
[ 1894.869540] audit: type=1400 audit(1779066605.787:531): apparmor="DENIED" operation="open" class="file" profile="snap.firefox.firefox" name="/proc/pressure/memory" pid=15168 comm="MemoryPoller" requested_mask="r" denied_mask="r" fsuid=1000 ouid=0
[ 1899.878260] audit: type=1400 audit(1779066610.796:532): apparmor="DENIED" operation="open" class="file" profile="snap.firefox.firefox" name="/proc/pressure/memory" pid=15168 comm="MemoryPoller" requested_mask="r" denied_mask="r" fsuid=1000 ouid=0
[ 1904.884181] audit: type=1400 audit(1779066615.802:533): apparmor="DENIED" operation="open" class="file" profile="snap.firefox.firefox" name="/proc/pressure/memory" pid=15168 comm="MemoryPoller" requested_mask="r" denied_mask="r" fsuid=1000 ouid=0
[ 1909.894154] audit: type=1400 audit(1779066620.812:534): apparmor="DENIED" operation="open" class="file" profile="snap.firefox.firefox" name="/proc/pressure/memory" pid=15168 comm="MemoryPoller" requested_mask="r" denied_mask="r" fsuid=1000 ouid=0
[ 1914.894886] audit: type=1400 audit(1779066625.813:535): apparmor="DENIED" operation="open" class="file" profile="snap.firefox.firefox" name="/proc/pressure/memory" pid=15168 comm="MemoryPoller" requested_mask="r" denied_mask="r" fsuid=1000 ouid=0
[ 1958.766393] audit: type=1400 audit(1779066669.685:536): apparmor="DENIED" operation="open" class="file" profile="snap.firefox.firefox" name="/proc/pressure/memory" pid=15168 comm="MemoryPoller" requested_mask="r" denied_mask="r" fsuid=1000 ouid=0
[ 7981.386263] audit: type=1400 audit(1779072692.345:537): apparmor="DENIED" operation="open" class="file" profile="snap.firefox.firefox" name="/proc/pressure/memory" pid=15168 comm="MemoryPoller" requested_mask="r" denied_mask="r" fsuid=1000 ouid=0
[ 7986.439516] audit: type=1400 audit(1779072697.399:538): apparmor="DENIED" operation="open" class="file" profile="snap.firefox.firefox" name="/proc/pressure/memory" pid=15168 comm="MemoryPoller" requested_mask="r" denied_mask="r" fsuid=1000 ouid=0
[ 7991.479897] audit: type=1400 audit(1779072702.439:539): apparmor="DENIED" operation="open" class="file" profile="snap.firefox.firefox" name="/proc/pressure/memory" pid=15168 comm="MemoryPoller" requested_mask="r" denied_mask="r" fsuid=1000 ouid=0
[ 7996.561886] audit: type=1400 audit(1779072707.521:540): apparmor="DENIED" operation="open" class="file" profile="snap.firefox.firefox" name="/proc/pressure/memory" pid=15168 comm="MemoryPoller" requested_mask="r" denied_mask="r" fsuid=1000 ouid=0
[ 8001.597710] audit: type=1400 audit(1779072712.557:541): apparmor="DENIED" operation="open" class="file" profile="snap.firefox.firefox" name="/proc/pressure/memory" pid=15168 comm="MemoryPoller" requested_mask="r" denied_mask="r" fsuid=1000 ouid=0
[ 8012.164321] audit: type=1400 audit(1779072723.124:542): apparmor="DENIED" operation="open" class="file" profile="snap.firefox.firefox" name="/proc/pressure/memory" pid=15168 comm="MemoryPoller" requested_mask="r" denied_mask="r" fsuid=1000 ouid=0
[ 8017.190684] audit: type=1400 audit(1779072728.150:543): apparmor="DENIED" operation="open" class="file" profile="snap.firefox.firefox" name="/proc/pressure/memory" pid=15168 comm="MemoryPoller" requested_mask="r" denied_mask="r" fsuid=1000 ouid=0
[ 8034.584360] audit: type=1400 audit(1779072745.544:544): apparmor="DENIED" operation="open" class="file" profile="snap.firefox.firefox" name="/proc/pressure/memory" pid=15168 comm="MemoryPoller" requested_mask="r" denied_mask="r" fsuid=1000 ouid=0
[ 8051.414048] audit: type=1400 audit(1779072762.374:545): apparmor="DENIED" operation="open" class="file" profile="snap.firefox.firefox" name="/proc/pressure/memory" pid=15168 comm="MemoryPoller" requested_mask="r" denied_mask="r" fsuid=1000 ouid=0
[ 8062.914863] audit: type=1400 audit(1779072773.875:546): apparmor="DENIED" operation="open" class="file" profile="snap.firefox.firefox" name="/proc/pressure/memory" pid=15168 comm="MemoryPoller" requested_mask="r" denied_mask="r" fsuid=1000 ouid=0
[ 8068.097167] audit: type=1400 audit(1779072779.057:547): apparmor="DENIED" operation="open" class="file" profile="snap.firefox.firefox" name="/proc/pressure/memory" pid=15168 comm="MemoryPoller" requested_mask="r" denied_mask="r" fsuid=1000 ouid=0
[ 8093.720637] audit: type=1400 audit(1779072804.680:548): apparmor="DENIED" operation="open" class="file" profile="snap.firefox.firefox" name="/proc/pressure/memory" pid=15168 comm="MemoryPoller" requested_mask="r" denied_mask="r" fsuid=1000 ouid=0
[ 8098.771053] audit: type=1400 audit(1779072809.730:549): apparmor="DENIED" operation="open" class="file" profile="snap.firefox.firefox" name="/proc/pressure/memory" pid=15168 comm="MemoryPoller" requested_mask="r" denied_mask="r" fsuid=1000 ouid=0
[ 8103.771726] audit: type=1400 audit(1779072814.731:550): apparmor="DENIED" operation="open" class="file" profile="snap.firefox.firefox" name="/proc/pressure/memory" pid=15168 comm="MemoryPoller" requested_mask="r" denied_mask="r" fsuid=1000 ouid=0
[ 8108.804827] audit: type=1400 audit(1779072819.764:551): apparmor="DENIED" operation="open" class="file" profile="snap.firefox.firefox" name="/proc/pressure/memory" pid=15168 comm="MemoryPoller" requested_mask="r" denied_mask="r" fsuid=1000 ouid=0
[ 8113.805860] audit: type=1400 audit(1779072824.766:552): apparmor="DENIED" operation="open" class="file" profile="snap.firefox.firefox" name="/proc/pressure/memory" pid=15168 comm="MemoryPoller" requested_mask="r" denied_mask="r" fsuid=1000 ouid=0
[ 8118.806789] audit: type=1400 audit(1779072829.766:553): apparmor="DENIED" operation="open" class="file" profile="snap.firefox.firefox" name="/proc/pressure/memory" pid=15168 comm="MemoryPoller" requested_mask="r" denied_mask="r" fsuid=1000 ouid=0
[ 8123.807448] audit: type=1400 audit(1779072834.767:554): apparmor="DENIED" operation="open" class="file" profile="snap.firefox.firefox" name="/proc/pressure/memory" pid=15168 comm="MemoryPoller" requested_mask="r" denied_mask="r" fsuid=1000 ouid=0
[ 8128.855688] audit: type=1400 audit(1779072839.815:555): apparmor="DENIED" operation="open" class="file" profile="snap.firefox.firefox" name="/proc/pressure/memory" pid=15168 comm="MemoryPoller" requested_mask="r" denied_mask="r" fsuid=1000 ouid=0
[ 8133.856140] audit: type=1400 audit(1779072844.816:556): apparmor="DENIED" operation="open" class="file" profile="snap.firefox.firefox" name="/proc/pressure/memory" pid=15168 comm="MemoryPoller" requested_mask="r" denied_mask="r" fsuid=1000 ouid=0
[ 8138.859883] audit: type=1400 audit(1779072849.819:557): apparmor="DENIED" operation="open" class="file" profile="snap.firefox.firefox" name="/proc/pressure/memory" pid=15168 comm="MemoryPoller" requested_mask="r" denied_mask="r" fsuid=1000 ouid=0
[ 8143.860717] audit: type=1400 audit(1779072854.820:558): apparmor="DENIED" operation="open" class="file" profile="snap.firefox.firefox" name="/proc/pressure/memory" pid=15168 comm="MemoryPoller" requested_mask="r" denied_mask="r" fsuid=1000 ouid=0
[ 8153.904340] audit: type=1400 audit(1779072864.864:559): apparmor="DENIED" operation="open" class="file" profile="snap.firefox.firefox" name="/proc/pressure/memory" pid=15168 comm="MemoryPoller" requested_mask="r" denied_mask="r" fsuid=1000 ouid=0
[ 8158.956753] audit: type=1400 audit(1779072869.917:560): apparmor="DENIED" operation="open" class="file" profile="snap.firefox.firefox" name="/proc/pressure/memory" pid=15168 comm="MemoryPoller" requested_mask="r" denied_mask="r" fsuid=1000 ouid=0
[ 8163.958631] audit: type=1400 audit(1779072874.919:561): apparmor="DENIED" operation="open" class="file" profile="snap.firefox.firefox" name="/proc/pressure/memory" pid=15168 comm="MemoryPoller" requested_mask="r" denied_mask="r" fsuid=1000 ouid=0
[ 8168.959402] audit: type=1400 audit(1779072879.920:562): apparmor="DENIED" operation="open" class="file" profile="snap.firefox.firefox" name="/proc/pressure/memory" pid=15168 comm="MemoryPoller" requested_mask="r" denied_mask="r" fsuid=1000 ouid=0
[ 8173.971545] audit: type=1400 audit(1779072884.932:563): apparmor="DENIED" operation="open" class="file" profile="snap.firefox.firefox" name="/proc/pressure/memory" pid=15168 comm="MemoryPoller" requested_mask="r" denied_mask="r" fsuid=1000 ouid=0
[ 8184.561808] audit: type=1400 audit(1779072895.522:564): apparmor="DENIED" operation="open" class="file" profile="snap.firefox.firefox" name="/proc/pressure/memory" pid=15168 comm="MemoryPoller" requested_mask="r" denied_mask="r" fsuid=1000 ouid=0
[ 8189.638829] audit: type=1400 audit(1779072900.600:565): apparmor="DENIED" operation="open" class="file" profile="snap.firefox.firefox" name="/proc/pressure/memory" pid=15168 comm="MemoryPoller" requested_mask="r" denied_mask="r" fsuid=1000 ouid=0
[ 8194.708426] audit: type=1400 audit(1779072905.669:566): apparmor="DENIED" operation="open" class="file" profile="snap.firefox.firefox" name="/proc/pressure/memory" pid=15168 comm="MemoryPoller" requested_mask="r" denied_mask="r" fsuid=1000 ouid=0
[ 8199.788388] audit: type=1400 audit(1779072910.749:567): apparmor="DENIED" operation="open" class="file" profile="snap.firefox.firefox" name="/proc/pressure/memory" pid=15168 comm="MemoryPoller" requested_mask="r" denied_mask="r" fsuid=1000 ouid=0
[ 8205.044208] audit: type=1400 audit(1779072916.005:568): apparmor="DENIED" operation="open" class="file" profile="snap.firefox.firefox" name="/proc/pressure/memory" pid=15168 comm="MemoryPoller" requested_mask="r" denied_mask="r" fsuid=1000 ouid=0
[ 8210.163041] audit: type=1400 audit(1779072921.124:569): apparmor="DENIED" operation="open" class="file" profile="snap.firefox.firefox" name="/proc/pressure/memory" pid=15168 comm="MemoryPoller" requested_mask="r" denied_mask="r" fsuid=1000 ouid=0
[ 8215.207099] audit: type=1400 audit(1779072926.168:570): apparmor="DENIED" operation="open" class="file" profile="snap.firefox.firefox" name="/proc/pressure/memory" pid=15168 comm="MemoryPoller" requested_mask="r" denied_mask="r" fsuid=1000 ouid=0
[ 8220.278901] audit: type=1400 audit(1779072931.240:571): apparmor="DENIED" operation="open" class="file" profile="snap.firefox.firefox" name="/proc/pressure/memory" pid=15168 comm="MemoryPoller" requested_mask="r" denied_mask="r" fsuid=1000 ouid=0
[ 8225.311389] audit: type=1400 audit(1779072936.272:572): apparmor="DENIED" operation="open" class="file" profile="snap.firefox.firefox" name="/proc/pressure/memory" pid=15168 comm="MemoryPoller" requested_mask="r" denied_mask="r" fsuid=1000 ouid=0
[ 8230.445696] audit: type=1400 audit(1779072941.407:573): apparmor="DENIED" operation="open" class="file" profile="snap.firefox.firefox" name="/proc/pressure/memory" pid=15168 comm="MemoryPoller" requested_mask="r" denied_mask="r" fsuid=1000 ouid=0
[ 8235.455430] audit: type=1400 audit(1779072946.416:574): apparmor="DENIED" operation="open" class="file" profile="snap.firefox.firefox" name="/proc/pressure/memory" pid=15168 comm="MemoryPoller" requested_mask="r" denied_mask="r" fsuid=1000 ouid=0
[ 8238.015838] mimodulo: loading out-of-tree module taints kernel.
[ 8238.015845] mimodulo: module verification failed: signature and/or required key missing - tainting kernel
[ 8238.016212] Modulo cargado en el kernel.
[ 8240.456770] audit: type=1400 audit(1779072951.417:575): apparmor="DENIED" operation="open" class="file" profile="snap.firefox.firefox" name="/proc/pressure/memory" pid=15168 comm="MemoryPoller" requested_mask="r" denied_mask="r" fsuid=1000 ouid=0
[ 8250.501911] audit: type=1400 audit(1779072961.463:576): apparmor="DENIED" operation="open" class="file" profile="snap.firefox.firefox" name="/proc/pressure/memory" pid=15168 comm="MemoryPoller" requested_mask="r" denied_mask="r" fsuid=1000 ouid=0
[ 8255.527352] audit: type=1400 audit(1779072966.487:577): apparmor="DENIED" operation="open" class="file" profile="snap.firefox.firefox" name="/proc/pressure/memory" pid=15168 comm="MemoryPoller" requested_mask="r" denied_mask="r" fsuid=1000 ouid=0
```
