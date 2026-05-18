# TP #4: Módulos de Kernel

## 1. Introducción a los Módulos de Kernel
Antes de comenzar a definir que son los Módulos de Kernel y demás debemos primero repasar los conceptos desarrollados en trabajos prácticos anteriores, tales como el [Trabajo Práctico N°3](https://github.com/ErnestMonja/Sistemas-de-Computacion/tree/main/TP3%20-%20Modo%20Real%20vs%20Protegido%20y%20UEFI): En este trabajo, vimos que se podía ejecutar código directamente sobre la `CPU` de una computadora mediante herramientas de emulación como `QEMU`. Supongamos ahora que quisieramos conectar una impresora nueva a nuestra computadora: se tiene que el Kernel de Linux no sabe cómo comunicarse con esa impresora, lo que antiguamente se resolvía tomando todo el código fuente de Linux, agregarle el código de la comunicación de la impresora, recompilar todo el sistema operativo y reiniciar la computadora, siendo esto un proceso muy tedioso y poco práctico de implementar (Véase: [Kernel o Núcleo Monolítico](https://es.wikipedia.org/wiki/N%C3%BAcleo_monol%C3%ADtico)), que se relaciona a los conceptos estudiados en el [Trabajo Práctico N°3](https://github.com/ErnestMonja/Sistemas-de-Computacion/tree/main/TP3%20-%20Modo%20Real%20vs%20Protegido%20y%20UEFI). 

Estos problemas se resuelven hoy en día utilizando los `Módulos de Kernel` de Linux, siendo estos fragmentos de código que terminan en formato `.ko` que tienen el fin de añadir o quitar una funcionalidad al Kernel sin necesidad de tener que recompilar y reiniciar todo el sistema operativo para, por ejemplo, conectar la impresora mencionada anteriormente. Se tiene entonces que estas son una manera de implementar código `On-Demand` para el Sistema Operativo de forma más eficiente. 

Con estos conceptos en mente, la idea fundamental de este Trabajo Práctico consiste en descargar y compilar un archivo de Módulo del Kernel de Linux desarrollado por la cátedra de Sistemas de Computación (Véase: [Repositorio de Kernel Modules](https://gitlab.com/sistemas-de-computacion-unc/kenel-modules)), el cual fue añadido a este Repositorio. Para ello, se descargaron los archivos del GitLab, se descomprimieron y se ejecutaron los siguientes comandos en la terminal de Linux:

```bash
cd part1
cd module
make
```

Los primeros 2 comandos, buscan encontrar la ubicación en memoria del archivo `Makefile` y luego el comando `make` toma el código en el archivo `mimodulo.c` y lo traduce a lenguaje de máquina y creando así el archivo `mimodulo.ko` el cual consiste en el módulo de Kernel a instanciar en la computadora. Para insertar este módulo al Kernel, se utiliza la siguiente instrucción:

```bash
sudo insmod mimodulo.ko
```

Se tiene que los Módulos del Kernel no imprimen texto directamente en tu terminal, sino más bien se comunican escribiendo en el `ring buffer` del kernel. Para ver estos mensajes, se utiliza el siguiente comando en la terminal:

```bash
sudo dmesg
```

El cual tiene la siguiente salida por la consola:

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
[    0.000001] kvm-clock: using sched offset of 5570437010 cycles
[    0.000003] clocksource: kvm-clock: mask: 0xffffffffffffffff max_cycles: 0x1cd42e4dffb, max_idle_ns: 881590591483 ns
[    0.000006] tsc: Detected 3693.056 MHz processor
[    0.001213] e820: update [mem 0x00000000-0x00000fff] usable ==> reserved
[    0.001215] e820: remove [mem 0x000a0000-0x000fffff] usable
[    0.001219] last_pfn = 0x120000 max_arch_pfn = 0x400000000
[    0.001299] MTRR map: 3 entries (3 fixed + 0 variable; max 19), built from 8 variable MTRRs
[    0.001302] x86/PAT: Configuration [0-7]: WB  WC  UC- UC  WB  WP  UC- WT  
[    0.001353] CPU MTRRs all blank - virtualized system.
[    0.001355] last_pfn = 0xe0000 max_arch_pfn = 0x400000000
[    0.004036] found SMP MP-table at [mem 0x0009fbf0-0x0009fbff]
[    0.004200] RAMDISK: [mem 0x2ea41000-0x33517fff]
[    0.004479] ACPI: Early table checksum verification disabled
[    0.004482] ACPI: RSDP 0x00000000000E0000 000024 (v02 VBOX  )
[    0.004485] ACPI: XSDT 0x00000000DFFF0030 00003C (v01 VBOX   VBOXXSDT 00000001 ASL  00000061)
[    0.004489] ACPI: FACP 0x00000000DFFF00F0 0000F4 (v04 VBOX   VBOXFACP 00000001 ASL  00000061)
[    0.004492] ACPI: DSDT 0x00000000DFFF02F0 002353 (v02 VBOX   VBOXBIOS 00000002 VBOX 0002A122)
[    0.004494] ACPI: FACS 0x00000000DFFF0200 000040
[    0.004496] ACPI: FACS 0x00000000DFFF0200 000040
[    0.004497] ACPI: APIC 0x00000000DFFF0240 00005C (v02 VBOX   VBOXAPIC 00000001 ASL  00000061)
[    0.004499] ACPI: SSDT 0x00000000DFFF02A0 000045 (v01 VBOX   VBOXCPUT 00000002 VBOX 0002A122)
[    0.004500] ACPI: Reserving FACP table memory at [mem 0xdfff00f0-0xdfff01e3]
[    0.004500] ACPI: Reserving DSDT table memory at [mem 0xdfff02f0-0xdfff2642]
[    0.004501] ACPI: Reserving FACS table memory at [mem 0xdfff0200-0xdfff023f]
[    0.004501] ACPI: Reserving FACS table memory at [mem 0xdfff0200-0xdfff023f]
[    0.004502] ACPI: Reserving APIC table memory at [mem 0xdfff0240-0xdfff029b]
[    0.004502] ACPI: Reserving SSDT table memory at [mem 0xdfff02a0-0xdfff02e4]
[    0.005075] No NUMA configuration found
[    0.005076] Faking a node at [mem 0x0000000000000000-0x000000011fffffff]
[    0.005081] NODE_DATA(0) allocated [mem 0x11ffd12c0-0x11fffbfff]
[    0.005492] Zone ranges:
[    0.005493]   DMA      [mem 0x0000000000001000-0x0000000000ffffff]
[    0.005494]   DMA32    [mem 0x0000000001000000-0x00000000ffffffff]
[    0.005495]   Normal   [mem 0x0000000100000000-0x000000011fffffff]
[    0.005496]   Device   empty
[    0.005497] Movable zone start for each node
[    0.005498] Early memory node ranges
[    0.005498]   node   0: [mem 0x0000000000001000-0x000000000009efff]
[    0.005499]   node   0: [mem 0x0000000000100000-0x00000000dffeffff]
[    0.005500]   node   0: [mem 0x0000000100000000-0x000000011fffffff]
[    0.005500] Initmem setup node 0 [mem 0x0000000000001000-0x000000011fffffff]
[    0.005526] On node 0, zone DMA: 1 pages in unavailable ranges
[    0.005910] On node 0, zone DMA: 97 pages in unavailable ranges
[    0.102209] On node 0, zone Normal: 16 pages in unavailable ranges
[    0.103135] ACPI: PM-Timer IO Port: 0x4008
[    0.103617] IOAPIC[0]: apic_id 2, version 32, address 0xfec00000, GSI 0-23
[    0.103620] ACPI: INT_SRC_OVR (bus 0 bus_irq 0 global_irq 2 dfl dfl)
[    0.103622] ACPI: INT_SRC_OVR (bus 0 bus_irq 9 global_irq 9 low level)
[    0.103624] ACPI: Using ACPI (MADT) for SMP configuration information
[    0.103628] CPU topo: Max. logical packages:   1
[    0.103629] CPU topo: Max. logical dies:       1
[    0.103629] CPU topo: Max. dies per package:   1
[    0.103631] CPU topo: Max. threads per core:   1
[    0.103632] CPU topo: Num. cores per package:     2
[    0.103632] CPU topo: Num. threads per package:   2
[    0.103633] CPU topo: Allowing 2 present CPUs plus 0 hotplug CPUs
[    0.103713] PM: hibernation: Registered nosave memory: [mem 0x00000000-0x00000fff]
[    0.103724] PM: hibernation: Registered nosave memory: [mem 0x0009f000-0x000fffff]
[    0.103725] PM: hibernation: Registered nosave memory: [mem 0xdfff0000-0xffffffff]
[    0.103727] [mem 0xe0000000-0xfebfffff] available for PCI devices
[    0.103728] Booting paravirtualized kernel on KVM
[    0.103729] clocksource: refined-jiffies: mask: 0xffffffff max_cycles: 0xffffffff, max_idle_ns: 1910969940391419 ns
[    0.103735] setup_percpu: NR_CPUS:8192 nr_cpumask_bits:2 nr_cpu_ids:2 nr_node_ids:1
[    0.106823] percpu: Embedded 84 pages/cpu s221184 r8192 d114688 u1048576
[    0.106826] pcpu-alloc: s221184 r8192 d114688 u1048576 alloc=1*2097152
[    0.106828] pcpu-alloc: [0] 0 1 
[    0.106905] kvm-guest: PV spinlocks enabled
[    0.106907] PV qspinlock hash table entries: 256 (order: 0, 4096 bytes, linear)
[    0.106910] Kernel command line: BOOT_IMAGE=/boot/vmlinuz-6.17.0-22-generic root=UUID=154e4895-b405-436c-ac14-63ad0b84fe4c ro quiet splash
[    0.106950] Unknown kernel command line parameters "splash", will be passed to user space.
[    0.106964] random: crng init done
[    0.106965] printk: log buffer data + meta data: 262144 + 917504 = 1179648 bytes
[    0.113019] Dentry cache hash table entries: 524288 (order: 10, 4194304 bytes, linear)
[    0.116061] Inode-cache hash table entries: 262144 (order: 9, 2097152 bytes, linear)
[    0.116189] software IO TLB: area num 2.
[    0.169124] Fallback order for Node 0: 0 
[    0.169128] Built 1 zonelists, mobility grouping on.  Total pages: 1048462
[    0.169129] Policy zone: Normal
[    0.169137] mem auto-init: stack:all(zero), heap alloc:on, heap free:off
[    0.176763] SLUB: HWalign=64, Order=0-3, MinObjects=0, CPUs=2, Nodes=1
[    0.188545] ftrace: allocating 61414 entries in 240 pages
[    0.188547] ftrace: allocated 240 pages with 4 groups
[    0.189854] Dynamic Preempt: voluntary
[    0.190025] rcu: Preemptible hierarchical RCU implementation.
[    0.190026] rcu: 	RCU restricting CPUs from NR_CPUS=8192 to nr_cpu_ids=2.
[    0.190027] 	Trampoline variant of Tasks RCU enabled.
[    0.190028] 	Rude variant of Tasks RCU enabled.
[    0.190028] 	Tracing variant of Tasks RCU enabled.
[    0.190028] rcu: RCU calculated value of scheduler-enlistment delay is 100 jiffies.
[    0.190029] rcu: Adjusting geometry for rcu_fanout_leaf=16, nr_cpu_ids=2
[    0.190041] RCU Tasks: Setting shift to 1 and lim to 1 rcu_task_cb_adjust=1 rcu_task_cpu_ids=2.
[    0.190042] RCU Tasks Rude: Setting shift to 1 and lim to 1 rcu_task_cb_adjust=1 rcu_task_cpu_ids=2.
[    0.190043] RCU Tasks Trace: Setting shift to 1 and lim to 1 rcu_task_cb_adjust=1 rcu_task_cpu_ids=2.
[    0.193016] NR_IRQS: 524544, nr_irqs: 440, preallocated irqs: 16
[    0.193364] rcu: srcu_init: Setting srcu_struct sizes based on contention.
[    0.217051] Console: colour VGA+ 80x25
[    0.217053] printk: legacy console [tty0] enabled
[    0.217098] ACPI: Core revision 20250404
[    0.218367] APIC: Switch to symmetric I/O mode setup
[    0.224429] ..TIMER: vector=0x30 apic1=0 pin1=2 apic2=-1 pin2=-1
[    0.224553] clocksource: tsc-early: mask: 0xffffffffffffffff max_cycles: 0x6a776ec4191, max_idle_ns: 881591142850 ns
[    0.224559] Calibrating delay loop (skipped) preset value.. 7386.11 BogoMIPS (lpj=3693056)
[    0.225557] Last level iTLB entries: 4KB 512, 2MB 512, 4MB 256
[    0.225557] Last level dTLB entries: 4KB 2048, 2MB 2048, 4MB 1024, 1GB 0
[    0.225557] mitigations: Enabled attack vectors: user_kernel, user_user, guest_host, guest_guest, SMT mitigations: auto
[    0.225557] Speculative Return Stack Overflow: IBPB-extending microcode not applied!
[    0.225557] Speculative Return Stack Overflow: WARNING: See https://kernel.org/doc/html/latest/admin-guide/hw-vuln/srso.html for mitigation options.
[    0.225557] Transient Scheduler Attacks: Vulnerable: No microcode
[    0.225557] Spectre V2 : Mitigation: Retpolines
[    0.225557] Speculative Return Stack Overflow: Vulnerable: Safe RET, no microcode
[    0.225557] Spectre V1 : Mitigation: usercopy/swapgs barriers and __user pointer sanitization
[    0.225557] Spectre V2 : Spectre v2 / SpectreRSB: Filling RSB on context switch and VMEXIT
[    0.225557] active return thunk: srso_alias_return_thunk
[    0.225557] x86/fpu: Supporting XSAVE feature 0x001: 'x87 floating point registers'
[    0.225557] x86/fpu: Supporting XSAVE feature 0x002: 'SSE registers'
[    0.225557] x86/fpu: Supporting XSAVE feature 0x004: 'AVX registers'
[    0.225557] x86/fpu: xstate_offset[2]:  576, xstate_sizes[2]:  256
[    0.225557] x86/fpu: Enabled xstate features 0x7, context size is 832 bytes, using 'standard' format.
[    0.225557] Freeing SMP alternatives memory: 52K
[    0.225557] pid_max: default: 32768 minimum: 301
[    0.225557] LSM: initializing lsm=lockdown,capability,landlock,yama,apparmor,ima,evm
[    0.225557] landlock: Up and running.
[    0.225557] Yama: becoming mindful.
[    0.225557] AppArmor: AppArmor initialized
[    0.225557] Mount-cache hash table entries: 8192 (order: 4, 65536 bytes, linear)
[    0.225557] Mountpoint-cache hash table entries: 8192 (order: 4, 65536 bytes, linear)
[    0.341187] APIC calibration not consistent with PM-Timer: 131ms instead of 100ms
[    0.341191] APIC delta adjusted to PM-Timer: 6274432 (8267136)
[    0.341369] smpboot: CPU0: AMD Ryzen 5 5600X 6-Core Processor (family: 0x19, model: 0x21, stepping: 0x0)
[    0.341557] Performance Events: PMU not available due to virtualization, using software events only.
[    0.341557] signal: max sigframe size: 1776
[    0.341557] rcu: Hierarchical SRCU implementation.
[    0.341557] rcu: 	Max phase no-delay instances is 400.
[    0.341724] Timer migration: 1 hierarchy levels; 8 children per group; 1 crossnode level
[    0.346423] NMI watchdog: Perf NMI watchdog permanently disabled
[    0.346616] smp: Bringing up secondary CPUs ...
[    0.347097] smpboot: x86: Booting SMP configuration:
[    0.347099] .... node  #0, CPUs:      #1
[    0.350653] smp: Brought up 1 node, 2 CPUs
[    0.350657] smpboot: Total of 2 processors activated (14772.22 BogoMIPS)
[    0.350926] Memory: 3918304K/4193848K available (22217K kernel code, 4652K rwdata, 16296K rodata, 5268K init, 4212K bss, 269444K reserved, 0K cma-reserved)
[    0.351726] devtmpfs: initialized
[    0.351761] x86/mm: Memory block size: 128MB
[    0.354631] clocksource: jiffies: mask: 0xffffffff max_cycles: 0xffffffff, max_idle_ns: 1911260446275000 ns
[    0.354670] posixtimers hash table entries: 1024 (order: 2, 16384 bytes, linear)
[    0.354726] futex hash table entries: 512 (32768 bytes on 1 NUMA nodes, total 32 KiB, linear).
[    0.354814] pinctrl core: initialized pinctrl subsystem
[    0.355609] PM: RTC time: 16:24:16, date: 2026-05-18
[    0.360027] NET: Registered PF_NETLINK/PF_ROUTE protocol family
[    0.360903] DMA: preallocated 512 KiB GFP_KERNEL pool for atomic allocations
[    0.360950] DMA: preallocated 512 KiB GFP_KERNEL|GFP_DMA pool for atomic allocations
[    0.360996] DMA: preallocated 512 KiB GFP_KERNEL|GFP_DMA32 pool for atomic allocations
[    0.361009] audit: initializing netlink subsys (disabled)
[    0.361677] audit: type=2000 audit(1779121464.174:1): state=initialized audit_enabled=0 res=1
[    0.362206] thermal_sys: Registered thermal governor 'fair_share'
[    0.362208] thermal_sys: Registered thermal governor 'bang_bang'
[    0.362209] thermal_sys: Registered thermal governor 'step_wise'
[    0.362211] thermal_sys: Registered thermal governor 'user_space'
[    0.362212] thermal_sys: Registered thermal governor 'power_allocator'
[    0.362578] cpuidle: using governor ladder
[    0.362632] cpuidle: using governor menu
[    0.364810] acpiphp: ACPI Hot Plug PCI Controller Driver version: 0.5
[    0.365218] PCI: Using configuration type 1 for base access
[    0.365220] PCI: Using configuration type 1 for extended access
[    0.365281] mtrr: your CPUs had inconsistent variable MTRR settings
[    0.365283] mtrr: probably your BIOS does not setup all CPUs.
[    0.365284] mtrr: corrected configuration.
[    0.365639] kprobes: kprobe jump-optimization is enabled. All kprobes are optimized if possible.
[    0.366581] HugeTLB: registered 2.00 MiB page size, pre-allocated 0 pages
[    0.366583] HugeTLB: 28 KiB vmemmap can be freed for a 2.00 MiB page
[    0.380213] ACPI: Added _OSI(Module Device)
[    0.380215] ACPI: Added _OSI(Processor Device)
[    0.380217] ACPI: Added _OSI(Processor Aggregator Device)
[    0.380557] ACPI: 2 ACPI AML tables successfully acquired and loaded
[    0.380865] ACPI: Interpreter enabled
[    0.380879] ACPI: PM: (supports S0 S5)
[    0.380881] ACPI: Using IOAPIC for interrupt routing
[    0.381879] PCI: Using host bridge windows from ACPI; if necessary, use "pci=nocrs" and report a bug
[    0.381881] PCI: Using E820 reservations for host bridge windows
[    0.382031] ACPI: Enabled 2 GPEs in block 00 to 07
[    0.394416] ACPI: PCI Root Bridge [PCI0] (domain 0000 [bus 00-ff])
[    0.394423] acpi PNP0A03:00: _OSC: OS supports [ExtendedConfig ASPM ClockPM Segments MSI EDR HPX-Type3]
[    0.395393] acpi PNP0A03:00: _OSC: platform does not support [PCIeCapability LTR DPC]
[    0.395557] acpi PNP0A03:00: _OSC: not requesting control; platform does not support [PCIeCapability]
[    0.395557] acpi PNP0A03:00: _OSC: OS requested [PCIeHotplug SHPCHotplug PME AER PCIeCapability LTR DPC]
[    0.395557] acpi PNP0A03:00: _OSC: platform willing to grant [PCIeHotplug SHPCHotplug PME AER]
[    0.395557] acpi PNP0A03:00: _OSC: platform retains control of PCIe features (AE_SUPPORT)
[    0.395982] PCI host bridge to bus 0000:00
[    0.395986] pci_bus 0000:00: root bus resource [io  0x0000-0x0cf7 window]
[    0.395989] pci_bus 0000:00: root bus resource [io  0x0d00-0xffff window]
[    0.395991] pci_bus 0000:00: root bus resource [mem 0x000a0000-0x000bffff window]
[    0.395993] pci_bus 0000:00: root bus resource [mem 0xe0000000-0xfdffffff window]
[    0.395995] pci_bus 0000:00: root bus resource [bus 00-ff]
[    0.396619] pci 0000:00:00.0: [8086:1237] type 00 class 0x060000 conventional PCI endpoint
[    0.397594] pci 0000:00:01.0: [8086:7000] type 00 class 0x060100 conventional PCI endpoint
[    0.398606] pci 0000:00:01.1: [8086:7111] type 00 class 0x01018a conventional PCI endpoint
[    0.399189] pci 0000:00:01.1: BAR 4 [io  0xd000-0xd00f]
[    0.399262] pci 0000:00:01.1: BAR 0 [io  0x01f0-0x01f7]: legacy IDE quirk
[    0.399264] pci 0000:00:01.1: BAR 1 [io  0x03f6]: legacy IDE quirk
[    0.399266] pci 0000:00:01.1: BAR 2 [io  0x0170-0x0177]: legacy IDE quirk
[    0.399267] pci 0000:00:01.1: BAR 3 [io  0x0376]: legacy IDE quirk
[    0.399679] pci 0000:00:02.0: [15ad:0405] type 00 class 0x030000 conventional PCI endpoint
[    0.401095] pci 0000:00:02.0: BAR 0 [io  0xd010-0xd01f]
[    0.401113] pci 0000:00:02.0: BAR 1 [mem 0xe0000000-0xe7ffffff pref]
[    0.401129] pci 0000:00:02.0: BAR 2 [mem 0xf0000000-0xf01fffff]
[    0.401260] pci 0000:00:02.0: Video device with shadowed ROM at [mem 0x000c0000-0x000dffff]
[    0.401557] pci 0000:00:03.0: [8086:100e] type 00 class 0x020000 conventional PCI endpoint
[    0.402071] pci 0000:00:03.0: BAR 0 [mem 0xf0200000-0xf021ffff]
[    0.402102] pci 0000:00:03.0: BAR 2 [io  0xd020-0xd027]
[    0.402557] pci 0000:00:04.0: [80ee:cafe] type 00 class 0x088000 conventional PCI endpoint
[    0.402576] pci 0000:00:04.0: BAR 0 [io  0xd040-0xd05f]
[    0.402593] pci 0000:00:04.0: BAR 1 [mem 0xf0400000-0xf07fffff]
[    0.402610] pci 0000:00:04.0: BAR 2 [mem 0xf0800000-0xf0803fff pref]
[    0.402958] pci 0000:00:05.0: [8086:2415] type 00 class 0x040100 conventional PCI endpoint
[    0.403604] pci 0000:00:05.0: BAR 0 [io  0xd100-0xd1ff]
[    0.403621] pci 0000:00:05.0: BAR 1 [io  0xd200-0xd23f]
[    0.403998] pci 0000:00:06.0: [106b:003f] type 00 class 0x0c0310 conventional PCI endpoint
[    0.404621] pci 0000:00:06.0: BAR 0 [mem 0xf0804000-0xf0804fff]
[    0.405146] pci 0000:00:07.0: [8086:7113] type 00 class 0x068000 conventional PCI endpoint
[    0.405893] pci 0000:00:07.0: quirk: [io  0x4000-0x403f] claimed by PIIX4 ACPI
[    0.405910] pci 0000:00:07.0: quirk: [io  0x4100-0x410f] claimed by PIIX4 SMB
[    0.422239] pci 0000:00:0d.0: [8086:2829] type 00 class 0x010601 conventional PCI endpoint
[    0.422850] pci 0000:00:0d.0: BAR 0 [io  0xd240-0xd247]
[    0.422868] pci 0000:00:0d.0: BAR 1 [io  0xd248-0xd24b]
[    0.422884] pci 0000:00:0d.0: BAR 2 [io  0xd250-0xd257]
[    0.422900] pci 0000:00:0d.0: BAR 3 [io  0xd258-0xd25b]
[    0.422917] pci 0000:00:0d.0: BAR 4 [io  0xd260-0xd26f]
[    0.422933] pci 0000:00:0d.0: BAR 5 [mem 0xf0806000-0xf0807fff]
[    0.482818] ACPI: PCI: Interrupt link LNKA configured for IRQ 11
[    0.483334] ACPI: PCI: Interrupt link LNKB configured for IRQ 10
[    0.483579] ACPI: PCI: Interrupt link LNKC configured for IRQ 9
[    0.483752] ACPI: PCI: Interrupt link LNKD configured for IRQ 11
[    0.484652] iommu: Default domain type: Translated
[    0.484652] iommu: DMA domain TLB invalidation policy: lazy mode
[    0.485039] SCSI subsystem initialized
[    0.485731] libata version 3.00 loaded.
[    0.485731] ACPI: bus type USB registered
[    0.485751] usbcore: registered new interface driver usbfs
[    0.485776] usbcore: registered new interface driver hub
[    0.485785] usbcore: registered new device driver usb
[    0.485814] pps_core: LinuxPPS API ver. 1 registered
[    0.485816] pps_core: Software ver. 5.3.6 - Copyright 2005-2007 Rodolfo Giometti <giometti@linux.it>
[    0.485820] PTP clock support registered
[    0.486742] EDAC MC: Ver: 3.0.0
[    0.489400] NetLabel: Initializing
[    0.489402] NetLabel:  domain hash size = 128
[    0.489404] NetLabel:  protocols = UNLABELED CIPSOv4 CALIPSO
[    0.489441] NetLabel:  unlabeled traffic allowed by default
[    0.489664] mctp: management component transport protocol core
[    0.489664] NET: Registered PF_MCTP protocol family
[    0.489664] PCI: Using ACPI for IRQ routing
[    0.489664] PCI: pci_cache_line_size set to 64 bytes
[    0.489910] e820: reserve RAM buffer [mem 0x0009fc00-0x0009ffff]
[    0.489913] e820: reserve RAM buffer [mem 0xdfff0000-0xdfffffff]
[    0.490584] pci 0000:00:02.0: vgaarb: setting as boot VGA device
[    0.490587] pci 0000:00:02.0: vgaarb: bridge control possible
[    0.490589] pci 0000:00:02.0: vgaarb: VGA device added: decodes=io+mem,owns=io+mem,locks=none
[    0.490592] vgaarb: loaded
[    0.490811] clocksource: Switched to clocksource kvm-clock
[    0.494239] VFS: Disk quotas dquot_6.6.0
[    0.494257] VFS: Dquot-cache hash table entries: 512 (order 0, 4096 bytes)
[    0.495303] AppArmor: AppArmor Filesystem Enabled
[    0.495322] pnp: PnP ACPI init
[    0.496836] pnp: PnP ACPI: found 2 devices
[    0.523995] clocksource: acpi_pm: mask: 0xffffff max_cycles: 0xffffff, max_idle_ns: 2085701024 ns
[    0.524098] NET: Registered PF_INET protocol family
[    0.525096] IP idents hash table entries: 65536 (order: 7, 524288 bytes, linear)
[    0.543137] tcp_listen_portaddr_hash hash table entries: 2048 (order: 3, 32768 bytes, linear)
[    0.543137] Table-perturb hash table entries: 65536 (order: 6, 262144 bytes, linear)
[    0.543137] TCP established hash table entries: 32768 (order: 6, 262144 bytes, linear)
[    0.543137] TCP bind hash table entries: 32768 (order: 8, 1048576 bytes, linear)
[    0.543137] TCP: Hash tables configured (established 32768 bind 32768)
[    0.543137] MPTCP token hash table entries: 4096 (order: 5, 98304 bytes, linear)
[    0.543137] UDP hash table entries: 2048 (order: 5, 131072 bytes, linear)
[    0.543137] UDP-Lite hash table entries: 2048 (order: 5, 131072 bytes, linear)
[    0.543137] NET: Registered PF_UNIX/PF_LOCAL protocol family
[    0.543137] NET: Registered PF_XDP protocol family
[    0.543137] pci_bus 0000:00: resource 4 [io  0x0000-0x0cf7 window]
[    0.543137] pci_bus 0000:00: resource 5 [io  0x0d00-0xffff window]
[    0.543137] pci_bus 0000:00: resource 6 [mem 0x000a0000-0x000bffff window]
[    0.543137] pci_bus 0000:00: resource 7 [mem 0xe0000000-0xfdffffff window]
[    0.549638] pci 0000:00:00.0: Limiting direct PCI/PCI transfers
[    0.552561] PCI: CLS 0 bytes, default 64
[    0.552688] PCI-DMA: Using software bounce buffering for IO (SWIOTLB)
[    0.552690] software IO TLB: mapped [mem 0x00000000dbff0000-0x00000000dfff0000] (64MB)
[    0.552746] clocksource: tsc: mask: 0xffffffffffffffff max_cycles: 0x6a776ec4191, max_idle_ns: 881591142850 ns
[    0.552767] clocksource: Switched to clocksource tsc
[    0.552799] platform rtc_cmos: registered platform RTC device (no PNP device found)
[    0.552843] Trying to unpack rootfs image as initramfs...
[    0.573397] Initialise system trusted keyrings
[    0.573407] Key type blacklist registered
[    0.573505] workingset: timestamp_bits=36 max_order=20 bucket_order=0
[    0.573786] squashfs: version 4.0 (2009/01/31) Phillip Lougher
[    0.573896] fuse: init (API version 7.44)
[    0.575501] integrity: Platform Keyring initialized
[    0.575505] integrity: Machine keyring initialized
[    0.576107] Key type asymmetric registered
[    0.576107] Asymmetric key parser 'x509' registered
[    0.576107] Block layer SCSI generic (bsg) driver version 0.4 loaded (major 242)
[    0.584963] io scheduler mq-deadline registered
[    0.585626] ledtrig-cpu: registered to indicate activity on CPUs
[    0.586078] ACPI: AC: AC Adapter [AC] (on-line)
[    0.586166] input: Power Button as /devices/LNXSYSTM:00/LNXPWRBN:00/input/input0
[    0.586512] ACPI: button: Power Button [PWRF]
[    0.586570] input: Sleep Button as /devices/LNXSYSTM:00/LNXSLPBN:00/input/input1
[    0.586644] ACPI: button: Sleep Button [SLPF]
[    0.587352] Serial: 8250/16550 driver, 32 ports, IRQ sharing enabled
[    0.589198] Linux agpgart interface v0.103
[    0.592663] loop: module loaded
[    0.596729] scsi host0: ata_piix
[    0.597200] scsi host1: ata_piix
[    0.597253] ata1: PATA max UDMA/33 cmd 0x1f0 ctl 0x3f6 bmdma 0xd000 irq 14 lpm-pol 0
[    0.597256] ata2: PATA max UDMA/33 cmd 0x170 ctl 0x376 bmdma 0xd008 irq 15 lpm-pol 0
[    0.597380] ACPI: bus type drm_connector registered
[    0.597651] tun: Universal TUN/TAP device driver, 1.6
[    0.597708] PPP generic driver version 2.4.2
[    0.599259] ohci-pci 0000:00:06.0: OHCI PCI host controller
[    0.599266] ohci-pci 0000:00:06.0: new USB bus registered, assigned bus number 1
[    0.600193] ohci-pci 0000:00:06.0: irq 22, io mem 0xf0804000
[    0.850067] ata1.00: ATAPI: VBOX CD-ROM, 1.0, max UDMA/133
[    0.851183] usb usb1: New USB device found, idVendor=1d6b, idProduct=0001, bcdDevice= 6.17
[    0.851188] usb usb1: New USB device strings: Mfr=3, Product=2, SerialNumber=1
[    0.851190] usb usb1: Product: OHCI PCI host controller
[    0.851192] usb usb1: Manufacturer: Linux 6.17.0-22-generic ohci_hcd
[    0.851193] usb usb1: SerialNumber: 0000:00:06.0
[    0.851193] Freeing initrd memory: 76636K
[    0.851203] hub 1-0:1.0: USB hub found
[    0.851482] hub 1-0:1.0: 12 ports detected
[    0.852278] scsi 0:0:0:0: CD-ROM            VBOX     CD-ROM           1.0  PQ: 0 ANSI: 5
[    0.852591] i8042: PNP: PS/2 Controller [PNP0303:PS2K,PNP0f03:PS2M] at 0x60,0x64 irq 1,12
[    0.854424] serio: i8042 KBD port at 0x60,0x64 irq 1
[    0.854431] serio: i8042 AUX port at 0x60,0x64 irq 12
[    0.854710] mousedev: PS/2 mouse device common for all mice
[    0.856012] rtc_cmos rtc_cmos: registered as rtc0
[    0.856354] rtc_cmos rtc_cmos: setting system clock to 2026-05-18T16:24:17 UTC (1779121457)
[    0.856455] rtc_cmos rtc_cmos: alarms up to one day, 114 bytes nvram
[    0.856587] i2c_dev: i2c /dev entries driver
[    0.856633] device-mapper: core: CONFIG_IMA_DISABLE_HTABLE is disabled. Duplicate IMA measurements will not be recorded in the IMA log.
[    0.856648] device-mapper: uevent: version 1.0.3
[    0.856867] device-mapper: ioctl: 4.50.0-ioctl (2025-04-28) initialised: dm-devel@lists.linux.dev
[    0.856873] amd_pstate: the _CPC object is not present in SBIOS or ACPI disabled
[    0.857056] drop_monitor: Initializing network drop monitor service
[    0.857776] input: AT Translated Set 2 keyboard as /devices/platform/i8042/serio0/input/input2
[    0.857828] NET: Registered PF_INET6 protocol family
[    0.859243] sr 0:0:0:0: [sr0] scsi3-mmc drive: 32x/32x xa/form2 tray
[    0.859246] cdrom: Uniform CD-ROM driver Revision: 3.20
[    0.859248] Segment Routing with IPv6
[    0.859257] In-situ OAM (IOAM) with IPv6
[    0.859278] NET: Registered PF_PACKET protocol family
[    0.859319] Key type dns_resolver registered
[    0.861329] IPI shorthand broadcast: enabled
[    0.864152] sched_clock: Marking stable (832461316, 31102625)->(898380083, -34816142)
[    0.864914] registered taskstats version 1
[    0.865726] Loading compiled-in X.509 certificates
[    0.866572] Loaded X.509 cert 'Build time autogenerated kernel key: 10e561fe75970ebe98357e1cb1b79397dec08fd7'
[    0.866848] Loaded X.509 cert 'Canonical Ltd. Live Patch Signing 2025 Kmod: d541cef61dc7e793b7eb7e899970a2eef0b5dc8c'
[    0.867128] Loaded X.509 cert 'Canonical Ltd. Live Patch Signing: 14df34d1a87cf37625abec039ef2bf521249b969'
[    0.867404] Loaded X.509 cert 'Canonical Ltd. Kernel Module Signing: 88f752e560a1e0737e31163a466ad7b70a850c19'
[    0.867406] blacklist: Loading compiled-in revocation X.509 certificates
[    0.867487] Loaded X.509 cert 'Canonical Ltd. Secure Boot Signing: 61482aa2830d0ab2ad5af10b7250da9033ddcef0'
[    0.867500] Loaded X.509 cert 'Canonical Ltd. Secure Boot Signing (2017): 242ade75ac4a15e50d50c84b0d45ff3eae707a03'
[    0.867508] Loaded X.509 cert 'Canonical Ltd. Secure Boot Signing (ESM 2018): 365188c1d374d6b07c3c8f240f8ef722433d6a8b'
[    0.867517] Loaded X.509 cert 'Canonical Ltd. Secure Boot Signing (2019): c0746fd6c5da3ae827864651ad66ae47fe24b3e8'
[    0.867526] Loaded X.509 cert 'Canonical Ltd. Secure Boot Signing (2021 v1): a8d54bbb3825cfb94fa13c9f8a594a195c107b8d'
[    0.867536] Loaded X.509 cert 'Canonical Ltd. Secure Boot Signing (2021 v2): 4cf046892d6fd3c9a5b03f98d845f90851dc6a8c'
[    0.867565] Loaded X.509 cert 'Canonical Ltd. Secure Boot Signing (2021 v3): 100437bb6de6e469b581e61cd66bce3ef4ed53af'
[    0.867575] Loaded X.509 cert 'Canonical Ltd. Secure Boot Signing (Ubuntu Core 2019): c1d57b8f6b743f23ee41f4f7ee292f06eecadfb9'
[    0.868682] sr 0:0:0:0: Attached scsi CD-ROM sr0
[    0.868992] sr 0:0:0:0: Attached scsi generic sg0 type 5
[    0.877023] Demotion targets for Node 0: null
[    0.877336] Key type .fscrypt registered
[    0.877339] Key type fscrypt-provisioning registered
[    0.877424] Key type big_key registered
[    0.899366] Key type encrypted registered
[    0.899370] AppArmor: AppArmor sha256 policy hashing enabled
[    0.899380] ima: No TPM chip found, activating TPM-bypass!
[    0.899384] Loading compiled-in module X.509 certificates
[    0.899789] Loaded X.509 cert 'Build time autogenerated kernel key: 10e561fe75970ebe98357e1cb1b79397dec08fd7'
[    0.899793] ima: Allocated hash algorithm: sha256
[    0.899808] ima: No architecture policies found
[    0.899823] evm: Initialising EVM extended attributes:
[    0.899825] evm: security.selinux
[    0.899827] evm: security.SMACK64
[    0.899829] evm: security.SMACK64EXEC
[    0.899830] evm: security.SMACK64TRANSMUTE
[    0.899831] evm: security.SMACK64MMAP
[    0.899832] evm: security.apparmor
[    0.899833] evm: security.ima
[    0.899834] evm: security.capability
[    0.899836] evm: HMAC attrs: 0x1
[    0.900473] PM:   Magic number: 10:418:439
[    0.904603] RAS: Correctable Errors collector initialized.
[    0.912519] clk: Disabling unused clocks
[    0.912522] PM: genpd: Disabling unused power domains
[    0.914830] Freeing unused decrypted memory: 2028K
[    0.916288] Freeing unused kernel image (initmem) memory: 5268K
[    0.916307] Write protecting the kernel read-only data: 38912k
[    0.917312] Freeing unused kernel image (text/rodata gap) memory: 308K
[    0.917588] Freeing unused kernel image (rodata/data gap) memory: 88K
[    0.961012] x86/mm: Checked W+X mappings: passed, no W+X pages found.
[    0.961018] Run /init as init process
[    0.961019]   with arguments:
[    0.961021]     /init
[    0.961022]     splash
[    0.961024]   with environment:
[    0.961025]     HOME=/
[    0.961026]     TERM=linux
[    1.125969] input: ImExPS/2 Generic Explorer Mouse as /devices/platform/i8042/serio1/input/input4
[    1.127926] ACPI: video: Video Device [GFX0] (multi-head: yes  rom: no  post: no)
[    1.128022] input: Video Bus as /devices/LNXSYSTM:00/LNXSYBUS:00/PNP0A03:00/LNXVIDEO:00/input/input5
[    1.138655] e1000: Intel(R) PRO/1000 Network Driver
[    1.138658] e1000: Copyright (c) 1999-2006 Intel Corporation.
[    1.164471] ahci 0000:00:0d.0: SSS flag set, parallel bus scan disabled
[    1.165290] ahci 0000:00:0d.0: AHCI vers 0001.0100, 32 command slots, 3 Gbps, SATA mode
[    1.165293] ahci 0000:00:0d.0: 2/2 ports implemented (port mask 0x3)
[    1.165295] ahci 0000:00:0d.0: flags: 64bit ncq stag only ccc 
[    1.173321] scsi host2: ahci
[    1.173835] scsi host3: ahci
[    1.173950] ata3: SATA max UDMA/133 abar m8192@0xf0806000 port 0xf0806100 irq 21 lpm-pol 1
[    1.173968] ata4: SATA max UDMA/133 abar m8192@0xf0806000 port 0xf0806180 irq 21 lpm-pol 1
[    1.192030] usb 1-1: new full-speed USB device number 2 using ohci-pci
[    1.447760] usb 1-1: New USB device found, idVendor=80ee, idProduct=0021, bcdDevice= 1.00
[    1.447767] usb 1-1: New USB device strings: Mfr=1, Product=3, SerialNumber=0
[    1.447770] usb 1-1: Product: USB Tablet
[    1.447772] usb 1-1: Manufacturer: VirtualBox
[    1.459506] hid: raw HID events driver (C) Jiri Kosina
[    1.486636] ata3: SATA link up 3.0 Gbps (SStatus 123 SControl 300)
[    1.486969] ata3.00: ATA-6: VBOX HARDDISK, 1.0, max UDMA/133
[    1.486973] ata3.00: 52428800 sectors, multi 128: LBA48 NCQ (depth 32)
[    1.487340] ata3.00: configured for UDMA/133
[    1.487498] scsi 2:0:0:0: Direct-Access     ATA      VBOX HARDDISK    1.0  PQ: 0 ANSI: 5
[    1.487747] scsi 2:0:0:0: Attached scsi generic sg1 type 0
[    1.487842] sd 2:0:0:0: [sda] 52428800 512-byte logical blocks: (26.8 GB/25.0 GiB)
[    1.487852] sd 2:0:0:0: [sda] Write Protect is off
[    1.487854] sd 2:0:0:0: [sda] Mode Sense: 00 3a 00 00
[    1.487868] sd 2:0:0:0: [sda] Write cache: enabled, read cache: enabled, doesn't support DPO or FUA
[    1.487893] sd 2:0:0:0: [sda] Preferred minimum I/O size 512 bytes
[    1.504719]  sda: sda1 sda2
[    1.504971] sd 2:0:0:0: [sda] Attached SCSI disk
[    1.631635] e1000 0000:00:03.0 eth0: (PCI:33MHz:32-bit) 08:00:27:dd:25:c2
[    1.631647] e1000 0000:00:03.0 eth0: Intel(R) PRO/1000 Network Connection
[    2.351347] clocksource: Long readout interval, skipping watchdog check: cs_nsec: 1118179644 wd_nsec: 1118179522
[    2.457547] ata4: SATA link up 3.0 Gbps (SStatus 123 SControl 300)
[    2.457875] ata4.00: ATA-6: VBOX HARDDISK, 1.0, max UDMA/133
[    2.457878] ata4.00: 204800 sectors, multi 128: LBA48 NCQ (depth 32)
[    2.458457] ata4.00: configured for UDMA/133
[    2.458804] scsi 3:0:0:0: Direct-Access     ATA      VBOX HARDDISK    1.0  PQ: 0 ANSI: 5
[    2.459298] sd 3:0:0:0: [sdb] 204800 512-byte logical blocks: (105 MB/100 MiB)
[    2.459311] sd 3:0:0:0: [sdb] Write Protect is off
[    2.459314] sd 3:0:0:0: [sdb] Mode Sense: 00 3a 00 00
[    2.459325] sd 3:0:0:0: [sdb] Write cache: enabled, read cache: enabled, doesn't support DPO or FUA
[    2.459346] sd 3:0:0:0: [sdb] Preferred minimum I/O size 512 bytes
[    2.459530] sd 3:0:0:0: Attached scsi generic sg2 type 0
[    2.851711] sd 3:0:0:0: [sdb] Attached SCSI disk
[    2.855523] e1000 0000:00:03.0 enp0s3: renamed from eth0
[    2.880950] usbcore: registered new interface driver usbhid
[    2.880953] usbhid: USB HID core driver
[    2.886792] input: VirtualBox USB Tablet as /devices/pci0000:00/0000:00:06.0/usb1/1-1/1-1:1.0/0003:80EE:0021.0001/input/input6
[    2.886911] hid-generic 0003:80EE:0021.0001: input,hidraw0: USB HID v1.10 Mouse [VirtualBox USB Tablet] on usb-0000:00:06.0-1/input0
[    4.269805] EXT4-fs (sda2): mounted filesystem 154e4895-b405-436c-ac14-63ad0b84fe4c ro with ordered data mode. Quota mode: none.
[    4.528342] systemd[1]: Inserted module 'autofs4'
[    4.555616] systemd[1]: systemd 255.4-1ubuntu8.15 running in system mode (+PAM +AUDIT +SELINUX +APPARMOR +IMA +SMACK +SECCOMP +GCRYPT -GNUTLS +OPENSSL +ACL +BLKID +CURL +ELFUTILS +FIDO2 +IDN2 -IDN +IPTC +KMOD +LIBCRYPTSETUP +LIBFDISK +PCRE2 -PWQUALITY +P11KIT +QRENCODE +TPM2 +BZIP2 +LZ4 +XZ +ZLIB +ZSTD -BPF_FRAMEWORK -XKBCOMMON +UTMP +SYSVINIT default-hierarchy=unified)
[    4.555621] systemd[1]: Detected virtualization oracle.
[    4.555690] systemd[1]: Detected architecture x86-64.
[    4.558438] systemd[1]: Hostname set to <UbuntuSdC>.
[    4.907418] systemd[1]: Queued start job for default target graphical.target.
[    4.922097] systemd[1]: Created slice system-modprobe.slice - Slice /system/modprobe.
[    4.922383] systemd[1]: Created slice user.slice - User and Session Slice.
[    4.922437] systemd[1]: Started systemd-ask-password-wall.path - Forward Password Requests to Wall Directory Watch.
[    4.922587] systemd[1]: Set up automount proc-sys-fs-binfmt_misc.automount - Arbitrary Executable File Formats File System Automount Point.
[    4.922605] systemd[1]: Reached target integritysetup.target - Local Integrity Protected Volumes.
[    4.922622] systemd[1]: Reached target remote-fs.target - Remote File Systems.
[    4.922628] systemd[1]: Reached target slices.target - Slice Units.
[    4.922635] systemd[1]: Reached target snapd.mounts-pre.target - Mounting snaps.
[    4.922643] systemd[1]: Reached target swap.target - Swaps.
[    4.922652] systemd[1]: Reached target veritysetup.target - Local Verity Protected Volumes.
[    4.923205] systemd[1]: Listening on syslog.socket - Syslog Socket.
[    4.923293] systemd[1]: Listening on systemd-fsckd.socket - fsck to fsckd communication Socket.
[    4.923363] systemd[1]: Listening on systemd-initctl.socket - initctl Compatibility Named Pipe.
[    4.923457] systemd[1]: Listening on systemd-journald-dev-log.socket - Journal Socket (/dev/log).
[    4.923552] systemd[1]: Listening on systemd-journald.socket - Journal Socket.
[    4.923683] systemd[1]: Listening on systemd-oomd.socket - Userspace Out-Of-Memory (OOM) Killer Socket.
[    4.923696] systemd[1]: systemd-pcrextend.socket - TPM2 PCR Extension (Varlink) was skipped because of an unmet condition check (ConditionSecurity=measured-uki).
[    4.924217] systemd[1]: Listening on systemd-udevd-control.socket - udev Control Socket.
[    4.924427] systemd[1]: Listening on systemd-udevd-kernel.socket - udev Kernel Socket.
[    4.925910] systemd[1]: Mounting dev-hugepages.mount - Huge Pages File System...
[    4.927051] systemd[1]: Mounting dev-mqueue.mount - POSIX Message Queue File System...
[    4.927702] systemd[1]: Mounting sys-kernel-debug.mount - Kernel Debug File System...
[    4.936413] systemd[1]: Mounting sys-kernel-tracing.mount - Kernel Trace File System...
[    4.944491] systemd[1]: Starting systemd-journald.service - Journal Service...
[    4.945108] systemd[1]: Starting keyboard-setup.service - Set the console keyboard layout...
[    4.946996] systemd[1]: Starting kmod-static-nodes.service - Create List of Static Device Nodes...
[    4.951861] systemd[1]: Starting modprobe@configfs.service - Load Kernel Module configfs...
[    4.954010] systemd[1]: Starting modprobe@dm_mod.service - Load Kernel Module dm_mod...
[    4.966477] systemd-journald[235]: Collecting audit messages is disabled.
[    4.971291] systemd[1]: Starting modprobe@drm.service - Load Kernel Module drm...
[    4.971952] systemd[1]: Starting modprobe@efi_pstore.service - Load Kernel Module efi_pstore...
[    4.985327] systemd[1]: Starting modprobe@fuse.service - Load Kernel Module fuse...
[    4.986817] systemd[1]: Starting modprobe@loop.service - Load Kernel Module loop...
[    4.986953] systemd[1]: systemd-fsck-root.service - File System Check on Root Device was skipped because of an unmet condition check (ConditionPathExists=!/run/initramfs/fsck-root).
[    4.996598] systemd[1]: Starting systemd-modules-load.service - Load Kernel Modules...
[    4.996610] systemd[1]: systemd-pcrmachine.service - TPM2 PCR Machine ID Measurement was skipped because of an unmet condition check (ConditionSecurity=measured-uki).
[    5.004876] systemd[1]: Starting systemd-remount-fs.service - Remount Root and Kernel File Systems...
[    5.004909] systemd[1]: systemd-tpm2-setup-early.service - TPM2 SRK Setup (Early) was skipped because of an unmet condition check (ConditionSecurity=measured-uki).
[    5.008206] systemd[1]: Starting systemd-udev-trigger.service - Coldplug All udev Devices...
[    5.013441] systemd[1]: Started systemd-journald.service - Journal Service.
[    5.041667] lp: driver loaded but no devices found
[    5.044735] EXT4-fs (sda2): re-mounted 154e4895-b405-436c-ac14-63ad0b84fe4c r/w.
[    5.049194] ppdev: user-space parallel port driver
[    5.166078] systemd-journald[235]: Received client request to flush runtime journal.
[    5.187628] systemd-journald[235]: File /var/log/journal/f74464dae0f64b65a6b2fd9e00edcb0c/system.journal corrupted or uncleanly shut down, renaming and replacing.
[    5.296356] loop0: detected capacity change from 0 to 8
[    5.305707] loop1: detected capacity change from 0 to 151464
[    5.309623] loop2: detected capacity change from 0 to 151512
[    5.316625] loop3: detected capacity change from 0 to 136816
[    5.322217] loop4: detected capacity change from 0 to 136904
[    5.331340] loop5: detected capacity change from 0 to 515416
[    5.335588] loop6: detected capacity change from 0 to 33792
[    5.347622] loop7: detected capacity change from 0 to 1088256
[    5.349936] loop8: detected capacity change from 0 to 37864
[    5.352569] loop9: detected capacity change from 0 to 1241248
[    5.525116] audit: type=1400 audit(1779121462.168:2): apparmor="STATUS" operation="profile_load" profile="unconfined" name="1password" pid=358 comm="apparmor_parser"
[    5.525455] audit: type=1400 audit(1779121462.168:3): apparmor="STATUS" operation="profile_load" profile="unconfined" name="Discord" pid=359 comm="apparmor_parser"
[    5.530837] audit: type=1400 audit(1779121462.173:4): apparmor="STATUS" operation="profile_load" profile="unconfined" name="QtWebEngineProcess" pid=361 comm="apparmor_parser"
[    5.533493] audit: type=1400 audit(1779121462.176:5): apparmor="STATUS" operation="profile_load" profile="unconfined" name="balena-etcher" pid=362 comm="apparmor_parser"
[    5.535746] audit: type=1400 audit(1779121462.178:6): apparmor="STATUS" operation="profile_load" profile="unconfined" name=4D6F6E676F444220436F6D70617373 pid=360 comm="apparmor_parser"
[    5.538229] audit: type=1400 audit(1779121462.180:7): apparmor="STATUS" operation="profile_load" profile="unconfined" name="brave" pid=363 comm="apparmor_parser"
[    5.539398] audit: type=1400 audit(1779121462.182:8): apparmor="STATUS" operation="profile_load" profile="unconfined" name="buildah" pid=364 comm="apparmor_parser"
[    5.542202] audit: type=1400 audit(1779121462.184:9): apparmor="STATUS" operation="profile_load" profile="unconfined" name="ch-checkns" pid=366 comm="apparmor_parser"
[    5.543415] audit: type=1400 audit(1779121462.186:10): apparmor="STATUS" operation="profile_load" profile="unconfined" name="cam" pid=365 comm="apparmor_parser"
[    5.544612] audit: type=1400 audit(1779121462.186:11): apparmor="STATUS" operation="profile_load" profile="unconfined" name="ch-run" pid=367 comm="apparmor_parser"
[    6.215063] piix4_smbus 0000:00:07.0: SMBus Host Controller at 0x4100, revision 0
[    6.269166] vboxguest: host-version: 7.2.6r172322 0x8000000f
[    6.274281] vbg_heartbeat_init: Setting up heartbeat to trigger every 2000 milliseconds
[    6.284400] input: VirtualBox mouse integration as /devices/pci0000:00/0000:00:04.0/input/input7
[    6.530375] intel_rapl_common: Found RAPL domain package
[    6.530398] intel_rapl_common: Found RAPL domain core
[    6.530702] vmwgfx 0000:00:02.0: vgaarb: deactivate vga console
[    6.530805] Console: switching to colour dummy device 80x25
[    6.531841] vmwgfx 0000:00:02.0: [drm] FIFO at 0x00000000f0000000 size is 2048 KiB
[    6.531854] vmwgfx 0000:00:02.0: [drm] VRAM at 0x00000000e0000000 size is 131072 KiB
[    6.531894] vmwgfx 0000:00:02.0: [drm] Running on SVGA version 2.
[    6.531912] vmwgfx 0000:00:02.0: [drm] Capabilities: rect copy, cursor, cursor bypass, cursor bypass 2, alpha cursor, extended fifo, pitchlock, irq mask, gmr, traces, gmr2, screen object 2, command buffers, command buffers 2, gbobject, 
[    6.531914] vmwgfx 0000:00:02.0: [drm] *ERROR* vmwgfx seems to be running on an unsupported hypervisor.
[    6.531917] vmwgfx 0000:00:02.0: [drm] *ERROR* This configuration is likely broken.
[    6.531919] vmwgfx 0000:00:02.0: [drm] *ERROR* Please switch to a supported graphics device to avoid problems.
[    6.531922] vmwgfx 0000:00:02.0: [drm] DMA map mode: Caching DMA mappings.
[    6.532166] vmwgfx 0000:00:02.0: [drm] Legacy memory limits: VRAM = 131072 KiB, FIFO = 2048 KiB, surface = 393216 KiB
[    6.532169] vmwgfx 0000:00:02.0: [drm] MOB limits: max mob size = 131072 KiB, max mob pages = 32768
[    6.532171] vmwgfx 0000:00:02.0: [drm] Max GMR ids is 8192
[    6.532173] vmwgfx 0000:00:02.0: [drm] Max number of GMR pages is 1048576
[    6.532174] vmwgfx 0000:00:02.0: [drm] Maximum display memory size is 131072 KiB
[    6.552947] vmwgfx 0000:00:02.0: [drm] Screen Target display unit initialized
[    6.553525] vmwgfx 0000:00:02.0: [drm] Fifo max 0x00200000 min 0x00001000 cap 0x00000355
[    6.553977] vmwgfx 0000:00:02.0: [drm] Using command buffers with DMA pool.
[    6.553983] vmwgfx 0000:00:02.0: [drm] Available shader model: Legacy.
[    6.554868] [drm] Initialized vmwgfx 2.21.0 for 0000:00:02.0 on minor 0
[    6.555825] fbcon: vmwgfxdrmfb (fb0) is primary device
[    6.555878] Console: switching to colour frame buffer device 160x50
[    6.555883] vmwgfx 0000:00:02.0: [drm] fb0: vmwgfxdrmfb frame buffer device
[    7.102822] snd_intel8x0 0000:00:05.0: allow list rate for 1028:0177 is 48000
[    7.991516] NET: Registered PF_QIPCRTR protocol family
[    8.580669] e1000: enp0s3 NIC Link is Up 1000 Mbps Full Duplex, Flow Control: RX
[   12.200335] rfkill: input handler disabled
[   30.375291] systemd-journald[235]: File /var/log/journal/f74464dae0f64b65a6b2fd9e00edcb0c/user-1000.journal corrupted or uncleanly shut down, renaming and replacing.
[   30.637068] rfkill: input handler enabled
[   32.696815] rfkill: input handler disabled
[   51.478450] kauditd_printk_skb: 150 callbacks suppressed
[   51.478454] audit: type=1400 audit(1779121509.610:162): apparmor="DENIED" operation="open" class="file" profile="snap.firefox.firefox" name="/etc/vulkan/implicit_layer.d/" pid=2727 comm="glxtest" requested_mask="r" denied_mask="r" fsuid=1000 ouid=0
[   51.482544] audit: type=1400 audit(1779121509.614:163): apparmor="DENIED" operation="open" class="file" profile="snap.firefox.firefox" name="/etc/vulkan/implicit_layer.d/" pid=2727 comm="glxtest" requested_mask="r" denied_mask="r" fsuid=1000 ouid=0
[   51.483218] audit: type=1400 audit(1779121509.614:164): apparmor="DENIED" operation="open" class="file" profile="snap.firefox.firefox" name="/etc/vulkan/icd.d/" pid=2727 comm="glxtest" requested_mask="r" denied_mask="r" fsuid=1000 ouid=0
[   51.686347] audit: type=1400 audit(1779121509.818:165): apparmor="DENIED" operation="open" class="file" profile="snap.firefox.firefox" name="/etc/vulkan/icd.d/" pid=2727 comm="glxtest" requested_mask="r" denied_mask="r" fsuid=1000 ouid=0
[   51.687040] audit: type=1400 audit(1779121509.818:166): apparmor="DENIED" operation="open" class="file" profile="snap.firefox.firefox" name="/etc/vulkan/implicit_layer.d/" pid=2727 comm="glxtest" requested_mask="r" denied_mask="r" fsuid=1000 ouid=0
[   51.689285] audit: type=1400 audit(1779121509.821:167): apparmor="DENIED" operation="open" class="file" profile="snap.firefox.firefox" name="/etc/vulkan/implicit_layer.d/" pid=2727 comm="glxtest" requested_mask="r" denied_mask="r" fsuid=1000 ouid=0
[   51.689427] audit: type=1400 audit(1779121509.821:168): apparmor="DENIED" operation="open" class="file" profile="snap.firefox.firefox" name="/etc/vulkan/icd.d/" pid=2727 comm="glxtest" requested_mask="r" denied_mask="r" fsuid=1000 ouid=0
[   51.690034] audit: type=1400 audit(1779121509.821:169): apparmor="DENIED" operation="open" class="file" profile="snap.firefox.firefox" name="/etc/vulkan/implicit_layer.d/" pid=2727 comm="glxtest" requested_mask="r" denied_mask="r" fsuid=1000 ouid=0
[   51.692394] audit: type=1400 audit(1779121509.824:170): apparmor="DENIED" operation="open" class="file" profile="snap.firefox.firefox" name="/etc/vulkan/implicit_layer.d/" pid=2727 comm="glxtest" requested_mask="r" denied_mask="r" fsuid=1000 ouid=0
[   51.692517] audit: type=1400 audit(1779121509.824:171): apparmor="DENIED" operation="open" class="file" profile="snap.firefox.firefox" name="/etc/vulkan/implicit_layer.d/" pid=2727 comm="glxtest" requested_mask="r" denied_mask="r" fsuid=1000 ouid=0
[   62.858360] kauditd_printk_skb: 8 callbacks suppressed
[   62.858363] audit: type=1400 audit(1779121520.990:180): apparmor="DENIED" operation="open" class="file" profile="snap.firefox.firefox" name="/proc/pressure/memory" pid=2642 comm="MemoryPoller" requested_mask="r" denied_mask="r" fsuid=1000 ouid=0
[   68.305295] audit: type=1400 audit(1779121526.437:181): apparmor="DENIED" operation="open" class="file" profile="snap.firefox.firefox" name="/proc/pressure/memory" pid=2642 comm="MemoryPoller" requested_mask="r" denied_mask="r" fsuid=1000 ouid=0
[   73.466057] audit: type=1400 audit(1779121531.599:182): apparmor="DENIED" operation="open" class="file" profile="snap.firefox.firefox" name="/proc/pressure/memory" pid=2642 comm="MemoryPoller" requested_mask="r" denied_mask="r" fsuid=1000 ouid=0
[   78.466435] audit: type=1400 audit(1779121536.600:183): apparmor="DENIED" operation="open" class="file" profile="snap.firefox.firefox" name="/proc/pressure/memory" pid=2642 comm="MemoryPoller" requested_mask="r" denied_mask="r" fsuid=1000 ouid=0
[   83.772584] audit: type=1400 audit(1779121541.906:184): apparmor="DENIED" operation="open" class="file" profile="snap.firefox.firefox" name="/proc/pressure/memory" pid=2642 comm="MemoryPoller" requested_mask="r" denied_mask="r" fsuid=1000 ouid=0
[   92.623725] audit: type=1400 audit(1779121550.758:185): apparmor="DENIED" operation="open" class="file" profile="snap.firefox.firefox" name="/proc/pressure/memory" pid=2642 comm="MemoryPoller" requested_mask="r" denied_mask="r" fsuid=1000 ouid=0
[   92.852241] audit: type=1400 audit(1779121550.986:186): apparmor="DENIED" operation="open" class="file" profile="snap.firefox.firefox" name="/etc/vulkan/implicit_layer.d/" pid=2642 comm="CanvasRenderer" requested_mask="r" denied_mask="r" fsuid=1000 ouid=0
[   92.852769] audit: type=1400 audit(1779121550.986:187): apparmor="DENIED" operation="open" class="file" profile="snap.firefox.firefox" name="/etc/vulkan/implicit_layer.d/" pid=2642 comm="CanvasRenderer" requested_mask="r" denied_mask="r" fsuid=1000 ouid=0
[   92.852885] audit: type=1400 audit(1779121550.986:188): apparmor="DENIED" operation="open" class="file" profile="snap.firefox.firefox" name="/etc/vulkan/icd.d/" pid=2642 comm="CanvasRenderer" requested_mask="r" denied_mask="r" fsuid=1000 ouid=0
[   92.860998] audit: type=1400 audit(1779121550.994:189): apparmor="DENIED" operation="open" class="file" profile="snap.firefox.firefox" name="/etc/vulkan/icd.d/" pid=2642 comm="CanvasRenderer" requested_mask="r" denied_mask="r" fsuid=1000 ouid=0
[   92.861497] audit: type=1400 audit(1779121550.994:190): apparmor="DENIED" operation="open" class="file" profile="snap.firefox.firefox" name="/etc/vulkan/implicit_layer.d/" pid=2642 comm="CanvasRenderer" requested_mask="r" denied_mask="r" fsuid=1000 ouid=0
[   92.862011] audit: type=1400 audit(1779121550.994:191): apparmor="DENIED" operation="open" class="file" profile="snap.firefox.firefox" name="/etc/vulkan/implicit_layer.d/" pid=2642 comm="CanvasRenderer" requested_mask="r" denied_mask="r" fsuid=1000 ouid=0
[   92.862119] audit: type=1400 audit(1779121550.994:192): apparmor="DENIED" operation="open" class="file" profile="snap.firefox.firefox" name="/etc/vulkan/icd.d/" pid=2642 comm="CanvasRenderer" requested_mask="r" denied_mask="r" fsuid=1000 ouid=0
[   92.862571] audit: type=1400 audit(1779121550.994:193): apparmor="DENIED" operation="open" class="file" profile="snap.firefox.firefox" name="/etc/vulkan/implicit_layer.d/" pid=2642 comm="CanvasRenderer" requested_mask="r" denied_mask="r" fsuid=1000 ouid=0
[   92.862679] audit: type=1400 audit(1779121550.994:194): apparmor="DENIED" operation="open" class="file" profile="snap.firefox.firefox" name="/etc/vulkan/implicit_layer.d/" pid=2642 comm="CanvasRenderer" requested_mask="r" denied_mask="r" fsuid=1000 ouid=0
[   97.635003] kauditd_printk_skb: 8 callbacks suppressed
[   97.635006] audit: type=1400 audit(1779121555.767:203): apparmor="DENIED" operation="open" class="file" profile="snap.firefox.firefox" name="/proc/pressure/memory" pid=2642 comm="MemoryPoller" requested_mask="r" denied_mask="r" fsuid=1000 ouid=0
[  102.635918] audit: type=1400 audit(1779121560.771:204): apparmor="DENIED" operation="open" class="file" profile="snap.firefox.firefox" name="/proc/pressure/memory" pid=2642 comm="MemoryPoller" requested_mask="r" denied_mask="r" fsuid=1000 ouid=0
[  119.363628] audit: type=1400 audit(1779121577.499:205): apparmor="DENIED" operation="open" class="file" profile="snap.firefox.firefox" name="/proc/pressure/memory" pid=2642 comm="MemoryPoller" requested_mask="r" denied_mask="r" fsuid=1000 ouid=0
[  124.407387] audit: type=1400 audit(1779121582.543:206): apparmor="DENIED" operation="open" class="file" profile="snap.firefox.firefox" name="/proc/pressure/memory" pid=2642 comm="MemoryPoller" requested_mask="r" denied_mask="r" fsuid=1000 ouid=0
[  129.457168] audit: type=1400 audit(1779121587.592:207): apparmor="DENIED" operation="open" class="file" profile="snap.firefox.firefox" name="/proc/pressure/memory" pid=2642 comm="MemoryPoller" requested_mask="r" denied_mask="r" fsuid=1000 ouid=0
[  134.458128] audit: type=1400 audit(1779121592.593:208): apparmor="DENIED" operation="open" class="file" profile="snap.firefox.firefox" name="/proc/pressure/memory" pid=2642 comm="MemoryPoller" requested_mask="r" denied_mask="r" fsuid=1000 ouid=0
[  139.464670] audit: type=1400 audit(1779121597.599:209): apparmor="DENIED" operation="open" class="file" profile="snap.firefox.firefox" name="/proc/pressure/memory" pid=2642 comm="MemoryPoller" requested_mask="r" denied_mask="r" fsuid=1000 ouid=0
[  144.533859] audit: type=1400 audit(1779121602.669:210): apparmor="DENIED" operation="open" class="file" profile="snap.firefox.firefox" name="/proc/pressure/memory" pid=2642 comm="MemoryPoller" requested_mask="r" denied_mask="r" fsuid=1000 ouid=0
[  149.630051] audit: type=1400 audit(1779121607.765:211): apparmor="DENIED" operation="open" class="file" profile="snap.firefox.firefox" name="/proc/pressure/memory" pid=2642 comm="MemoryPoller" requested_mask="r" denied_mask="r" fsuid=1000 ouid=0
[  154.646323] audit: type=1400 audit(1779121612.782:212): apparmor="DENIED" operation="open" class="file" profile="snap.firefox.firefox" name="/proc/pressure/memory" pid=2642 comm="MemoryPoller" requested_mask="r" denied_mask="r" fsuid=1000 ouid=0
[  159.697385] audit: type=1400 audit(1779121617.832:213): apparmor="DENIED" operation="open" class="file" profile="snap.firefox.firefox" name="/proc/pressure/memory" pid=2642 comm="MemoryPoller" requested_mask="r" denied_mask="r" fsuid=1000 ouid=0
[  171.136711] audit: type=1400 audit(1779121629.272:214): apparmor="DENIED" operation="open" class="file" profile="snap.firefox.firefox" name="/proc/pressure/memory" pid=2642 comm="MemoryPoller" requested_mask="r" denied_mask="r" fsuid=1000 ouid=0
[  176.138285] audit: type=1400 audit(1779121634.274:215): apparmor="DENIED" operation="open" class="file" profile="snap.firefox.firefox" name="/proc/pressure/memory" pid=2642 comm="MemoryPoller" requested_mask="r" denied_mask="r" fsuid=1000 ouid=0
[  181.140646] audit: type=1400 audit(1779121639.276:216): apparmor="DENIED" operation="open" class="file" profile="snap.firefox.firefox" name="/proc/pressure/memory" pid=2642 comm="MemoryPoller" requested_mask="r" denied_mask="r" fsuid=1000 ouid=0
[  186.184154] audit: type=1400 audit(1779121644.320:217): apparmor="DENIED" operation="open" class="file" profile="snap.firefox.firefox" name="/proc/pressure/memory" pid=2642 comm="MemoryPoller" requested_mask="r" denied_mask="r" fsuid=1000 ouid=0
[  191.185526] audit: type=1400 audit(1779121649.321:218): apparmor="DENIED" operation="open" class="file" profile="snap.firefox.firefox" name="/proc/pressure/memory" pid=2642 comm="MemoryPoller" requested_mask="r" denied_mask="r" fsuid=1000 ouid=0
[  196.453368] audit: type=1400 audit(1779121654.589:219): apparmor="DENIED" operation="open" class="file" profile="snap.firefox.firefox" name="/proc/pressure/memory" pid=2642 comm="MemoryPoller" requested_mask="r" denied_mask="r" fsuid=1000 ouid=0
[  201.591558] audit: type=1400 audit(1779121659.727:220): apparmor="DENIED" operation="open" class="file" profile="snap.firefox.firefox" name="/proc/pressure/memory" pid=2642 comm="MemoryPoller" requested_mask="r" denied_mask="r" fsuid=1000 ouid=0
[  206.641028] audit: type=1400 audit(1779121664.777:221): apparmor="DENIED" operation="open" class="file" profile="snap.firefox.firefox" name="/proc/pressure/memory" pid=2642 comm="MemoryPoller" requested_mask="r" denied_mask="r" fsuid=1000 ouid=0
[  211.727941] audit: type=1400 audit(1779121669.864:222): apparmor="DENIED" operation="open" class="file" profile="snap.firefox.firefox" name="/proc/pressure/memory" pid=2642 comm="MemoryPoller" requested_mask="r" denied_mask="r" fsuid=1000 ouid=0
[  216.789785] audit: type=1400 audit(1779121674.926:223): apparmor="DENIED" operation="open" class="file" profile="snap.firefox.firefox" name="/proc/pressure/memory" pid=2642 comm="MemoryPoller" requested_mask="r" denied_mask="r" fsuid=1000 ouid=0
[  221.792299] audit: type=1400 audit(1779121679.928:224): apparmor="DENIED" operation="open" class="file" profile="snap.firefox.firefox" name="/proc/pressure/memory" pid=2642 comm="MemoryPoller" requested_mask="r" denied_mask="r" fsuid=1000 ouid=0
[  226.807364] audit: type=1400 audit(1779121684.943:225): apparmor="DENIED" operation="open" class="file" profile="snap.firefox.firefox" name="/proc/pressure/memory" pid=2642 comm="MemoryPoller" requested_mask="r" denied_mask="r" fsuid=1000 ouid=0
[  231.810233] audit: type=1400 audit(1779121689.946:226): apparmor="DENIED" operation="open" class="file" profile="snap.firefox.firefox" name="/proc/pressure/memory" pid=2642 comm="MemoryPoller" requested_mask="r" denied_mask="r" fsuid=1000 ouid=0
[  237.009121] audit: type=1400 audit(1779121695.145:227): apparmor="DENIED" operation="open" class="file" profile="snap.firefox.firefox" name="/proc/pressure/memory" pid=2642 comm="MemoryPoller" requested_mask="r" denied_mask="r" fsuid=1000 ouid=0
[  256.188309] audit: type=1400 audit(1779121714.324:228): apparmor="DENIED" operation="open" class="file" profile="snap.firefox.firefox" name="/proc/pressure/memory" pid=2642 comm="MemoryPoller" requested_mask="r" denied_mask="r" fsuid=1000 ouid=0
[  267.303207] audit: type=1400 audit(1779121725.438:229): apparmor="DENIED" operation="open" class="file" profile="snap.firefox.firefox" name="/proc/pressure/memory" pid=2642 comm="MemoryPoller" requested_mask="r" denied_mask="r" fsuid=1000 ouid=0
[  290.247385] audit: type=1400 audit(1779121748.384:230): apparmor="DENIED" operation="open" class="file" profile="snap.firefox.firefox" name="/proc/pressure/memory" pid=2642 comm="MemoryPoller" requested_mask="r" denied_mask="r" fsuid=1000 ouid=0
[  295.838249] audit: type=1400 audit(1779121753.975:231): apparmor="DENIED" operation="open" class="file" profile="snap.firefox.firefox" name="/proc/pressure/memory" pid=2642 comm="MemoryPoller" requested_mask="r" denied_mask="r" fsuid=1000 ouid=0
[  300.839154] audit: type=1400 audit(1779121758.976:232): apparmor="DENIED" operation="open" class="file" profile="snap.firefox.firefox" name="/proc/pressure/memory" pid=2642 comm="MemoryPoller" requested_mask="r" denied_mask="r" fsuid=1000 ouid=0
[  305.843865] audit: type=1400 audit(1779121763.981:233): apparmor="DENIED" operation="open" class="file" profile="snap.firefox.firefox" name="/proc/pressure/memory" pid=2642 comm="MemoryPoller" requested_mask="r" denied_mask="r" fsuid=1000 ouid=0
[  310.856333] audit: type=1400 audit(1779121768.992:234): apparmor="DENIED" operation="open" class="file" profile="snap.firefox.firefox" name="/proc/pressure/memory" pid=2642 comm="MemoryPoller" requested_mask="r" denied_mask="r" fsuid=1000 ouid=0
[  315.882177] audit: type=1400 audit(1779121774.018:235): apparmor="DENIED" operation="open" class="file" profile="snap.firefox.firefox" name="/proc/pressure/memory" pid=2642 comm="MemoryPoller" requested_mask="r" denied_mask="r" fsuid=1000 ouid=0
[  320.884828] audit: type=1400 audit(1779121779.021:236): apparmor="DENIED" operation="open" class="file" profile="snap.firefox.firefox" name="/proc/pressure/memory" pid=2642 comm="MemoryPoller" requested_mask="r" denied_mask="r" fsuid=1000 ouid=0
[  325.525000] set_capacity_and_notify: 7 callbacks suppressed
[  325.525003] loop16: detected capacity change from 0 to 100888
[  325.904013] audit: type=1400 audit(1779121784.040:237): apparmor="DENIED" operation="open" class="file" profile="snap.firefox.firefox" name="/proc/pressure/memory" pid=2642 comm="MemoryPoller" requested_mask="r" denied_mask="r" fsuid=1000 ouid=0
[  326.113548] audit: type=1400 audit(1779121784.249:238): apparmor="STATUS" operation="profile_load" profile="unconfined" name="/snap/snapd/26865/usr/lib/snapd/snap-confine" pid=4280 comm="apparmor_parser"
[  326.445574] audit: type=1400 audit(1779121784.580:239): apparmor="STATUS" operation="profile_replace" info="same as current profile, skipping" profile="unconfined" name="snap-update-ns.firefox" pid=4282 comm="apparmor_parser"
[  326.653871] audit: type=1400 audit(1779121784.790:240): apparmor="STATUS" operation="profile_replace" info="same as current profile, skipping" profile="unconfined" name="snap-update-ns.firmware-updater" pid=4283 comm="apparmor_parser"
[  326.844052] audit: type=1400 audit(1779121784.979:241): apparmor="STATUS" operation="profile_replace" info="same as current profile, skipping" profile="unconfined" name="snap-update-ns.snap-store" pid=4284 comm="apparmor_parser"
[  327.091201] audit: type=1400 audit(1779121785.226:242): apparmor="STATUS" operation="profile_replace" info="same as current profile, skipping" profile="unconfined" name="snap-update-ns.snapd-desktop-integration" pid=4285 comm="apparmor_parser"
[  327.158552] audit: type=1400 audit(1779121785.293:243): apparmor="STATUS" operation="profile_replace" info="same as current profile, skipping" profile="unconfined" name="snap.firefox.firefox" pid=4287 comm="apparmor_parser"
[  327.173524] audit: type=1400 audit(1779121785.308:244): apparmor="STATUS" operation="profile_replace" info="same as current profile, skipping" profile="unconfined" name="snap.firefox.geckodriver" pid=4288 comm="apparmor_parser"
[  327.219090] audit: type=1400 audit(1779121785.355:245): apparmor="STATUS" operation="profile_replace" info="same as current profile, skipping" profile="unconfined" name="snap.firefox.hook.configure" pid=4289 comm="apparmor_parser"
[  327.224505] audit: type=1400 audit(1779121785.361:246): apparmor="STATUS" operation="profile_replace" info="same as current profile, skipping" profile="unconfined" name="snap.firefox.hook.disconnect-plug-host-hunspell" pid=4290 comm="apparmor_parser"
[  331.272595] kauditd_printk_skb: 11 callbacks suppressed
[  331.272599] audit: type=1400 audit(1779121789.409:258): apparmor="DENIED" operation="open" class="file" profile="snap.firefox.firefox" name="/proc/pressure/memory" pid=2642 comm="MemoryPoller" requested_mask="r" denied_mask="r" fsuid=1000 ouid=0
[  331.482835] loop17: detected capacity change from 0 to 8
[  333.580283] audit: type=1400 audit(1779121791.717:259): apparmor="STATUS" operation="profile_replace" profile="unconfined" name="/snap/snapd/26865/usr/lib/snapd/snap-confine" pid=4682 comm="apparmor_parser"
[  333.884559] audit: type=1400 audit(1779121792.021:260): apparmor="STATUS" operation="profile_replace" profile="unconfined" name="snap-update-ns.snap-store" pid=4684 comm="apparmor_parser"
[  334.028406] audit: type=1400 audit(1779121792.165:261): apparmor="STATUS" operation="profile_replace" profile="unconfined" name="snap.snap-store.hook.configure" pid=4685 comm="apparmor_parser"
[  334.317338] audit: type=1400 audit(1779121792.454:262): apparmor="STATUS" operation="profile_replace" profile="unconfined" name="snap.snap-store.show-updates" pid=4686 comm="apparmor_parser"
[  334.591471] audit: type=1400 audit(1779121792.728:263): apparmor="STATUS" operation="profile_replace" profile="unconfined" name="snap.snap-store.snap-store" pid=4687 comm="apparmor_parser"
[  334.813254] audit: type=1400 audit(1779121792.949:264): apparmor="STATUS" operation="profile_replace" profile="unconfined" name="snap-update-ns.firefox" pid=4688 comm="apparmor_parser"
[  335.324836] audit: type=1400 audit(1779121793.462:265): apparmor="STATUS" operation="profile_replace" profile="unconfined" name="snap.firefox.firefox" pid=4689 comm="apparmor_parser"
[  335.839562] audit: type=1400 audit(1779121793.976:266): apparmor="STATUS" operation="profile_replace" profile="unconfined" name="snap.firefox.geckodriver" pid=4690 comm="apparmor_parser"
[  335.963404] audit: type=1400 audit(1779121794.100:267): apparmor="STATUS" operation="profile_replace" profile="unconfined" name="snap.firefox.hook.configure" pid=4691 comm="apparmor_parser"
[  336.507526] kauditd_printk_skb: 3 callbacks suppressed
[  336.507530] audit: type=1400 audit(1779121794.644:271): apparmor="STATUS" operation="profile_replace" profile="unconfined" name="snap-update-ns.snapd-desktop-integration" pid=4695 comm="apparmor_parser"
[  336.648586] audit: type=1400 audit(1779121794.785:272): apparmor="STATUS" operation="profile_replace" profile="unconfined" name="snap.snapd-desktop-integration.hook.configure" pid=4696 comm="apparmor_parser"
[  336.943049] audit: type=1400 audit(1779121795.078:273): apparmor="STATUS" operation="profile_replace" profile="unconfined" name="snap.snapd-desktop-integration.snapd-desktop-integration" pid=4697 comm="apparmor_parser"
[  336.953459] audit: type=1400 audit(1779121795.091:274): apparmor="STATUS" operation="profile_replace" profile="unconfined" name="snap-update-ns.mesa-2404" pid=4698 comm="apparmor_parser"
[  337.026260] audit: type=1400 audit(1779121795.164:275): apparmor="STATUS" operation="profile_replace" profile="unconfined" name="snap.mesa-2404.component-monitor" pid=4699 comm="apparmor_parser"
[  337.095275] audit: type=1400 audit(1779121795.232:276): apparmor="STATUS" operation="profile_replace" profile="unconfined" name="snap.mesa-2404.hook.connect-plug-kernel-gpu-2404" pid=4700 comm="apparmor_parser"
[  337.174271] audit: type=1400 audit(1779121795.311:277): apparmor="STATUS" operation="profile_replace" profile="unconfined" name="snap.mesa-2404.hook.disconnect-plug-kernel-gpu-2404" pid=4701 comm="apparmor_parser"
[  337.247457] audit: type=1400 audit(1779121795.385:278): apparmor="STATUS" operation="profile_replace" profile="unconfined" name="snap.mesa-2404.hook.install" pid=4703 comm="apparmor_parser"
[  337.320336] audit: type=1400 audit(1779121795.456:279): apparmor="STATUS" operation="profile_replace" profile="unconfined" name="snap.mesa-2404.hook.post-refresh" pid=4704 comm="apparmor_parser"
[  337.544167] audit: type=1400 audit(1779121795.682:280): apparmor="STATUS" operation="profile_replace" profile="unconfined" name="snap-update-ns.firmware-updater" pid=4706 comm="apparmor_parser"
[  748.388408] mimodulo: loading out-of-tree module taints kernel.
[  748.388413] mimodulo: module verification failed: signature and/or required key missing - tainting kernel
[  748.388785] Modulo cargado en el kernel.
```

Vemos que los ultimas 3 líneas de salida nos indican que el módulo fue correctamente cargado en el Kernel a pesar de que:
 - El código fuente del módulo no pertenece al árbol oficial del código fuente de Linux (De acuerdo a: `mimodulo: loading out-of-tree module taints kernel.`).
 - El Kernel advierte que no puede verificar la autenticidad del autor ni garantizar que el código no haya sido alterado maliciosamente (De acuerdo a: `mimodulo: module verification failed: signature and/or required key missing - tainting kernel`).

Analizamos inicialmente que una de las ventajas principales de los módulos, es que pueden ser tanto añadidos como removidos con relativa facilidad y de acuerdo a la demanda que el Software o el Usuario (Como lo es en este caso) desee. Por lo tanto, exploremos que pasa si removemos este módulo del Kernel mediante los siguientes comandos:

```bash
sudo rmmod mimodulo
sudo dmesg
```

Obtendremos como salida de la consola lo siguiente:

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
[    0.000001] kvm-clock: using sched offset of 5570437010 cycles
[    0.000003] clocksource: kvm-clock: mask: 0xffffffffffffffff max_cycles: 0x1cd42e4dffb, max_idle_ns: 881590591483 ns
[    0.000006] tsc: Detected 3693.056 MHz processor
[    0.001213] e820: update [mem 0x00000000-0x00000fff] usable ==> reserved
[    0.001215] e820: remove [mem 0x000a0000-0x000fffff] usable
[    0.001219] last_pfn = 0x120000 max_arch_pfn = 0x400000000
[    0.001299] MTRR map: 3 entries (3 fixed + 0 variable; max 19), built from 8 variable MTRRs
[    0.001302] x86/PAT: Configuration [0-7]: WB  WC  UC- UC  WB  WP  UC- WT  
[    0.001353] CPU MTRRs all blank - virtualized system.
[    0.001355] last_pfn = 0xe0000 max_arch_pfn = 0x400000000
[    0.004036] found SMP MP-table at [mem 0x0009fbf0-0x0009fbff]
[    0.004200] RAMDISK: [mem 0x2ea41000-0x33517fff]
[    0.004479] ACPI: Early table checksum verification disabled
[    0.004482] ACPI: RSDP 0x00000000000E0000 000024 (v02 VBOX  )
[    0.004485] ACPI: XSDT 0x00000000DFFF0030 00003C (v01 VBOX   VBOXXSDT 00000001 ASL  00000061)
[    0.004489] ACPI: FACP 0x00000000DFFF00F0 0000F4 (v04 VBOX   VBOXFACP 00000001 ASL  00000061)
[    0.004492] ACPI: DSDT 0x00000000DFFF02F0 002353 (v02 VBOX   VBOXBIOS 00000002 VBOX 0002A122)
[    0.004494] ACPI: FACS 0x00000000DFFF0200 000040
[    0.004496] ACPI: FACS 0x00000000DFFF0200 000040
[    0.004497] ACPI: APIC 0x00000000DFFF0240 00005C (v02 VBOX   VBOXAPIC 00000001 ASL  00000061)
[    0.004499] ACPI: SSDT 0x00000000DFFF02A0 000045 (v01 VBOX   VBOXCPUT 00000002 VBOX 0002A122)
[    0.004500] ACPI: Reserving FACP table memory at [mem 0xdfff00f0-0xdfff01e3]
[    0.004500] ACPI: Reserving DSDT table memory at [mem 0xdfff02f0-0xdfff2642]
[    0.004501] ACPI: Reserving FACS table memory at [mem 0xdfff0200-0xdfff023f]
[    0.004501] ACPI: Reserving FACS table memory at [mem 0xdfff0200-0xdfff023f]
[    0.004502] ACPI: Reserving APIC table memory at [mem 0xdfff0240-0xdfff029b]
[    0.004502] ACPI: Reserving SSDT table memory at [mem 0xdfff02a0-0xdfff02e4]
[    0.005075] No NUMA configuration found
[    0.005076] Faking a node at [mem 0x0000000000000000-0x000000011fffffff]
[    0.005081] NODE_DATA(0) allocated [mem 0x11ffd12c0-0x11fffbfff]
[    0.005492] Zone ranges:
[    0.005493]   DMA      [mem 0x0000000000001000-0x0000000000ffffff]
[    0.005494]   DMA32    [mem 0x0000000001000000-0x00000000ffffffff]
[    0.005495]   Normal   [mem 0x0000000100000000-0x000000011fffffff]
[    0.005496]   Device   empty
[    0.005497] Movable zone start for each node
[    0.005498] Early memory node ranges
[    0.005498]   node   0: [mem 0x0000000000001000-0x000000000009efff]
[    0.005499]   node   0: [mem 0x0000000000100000-0x00000000dffeffff]
[    0.005500]   node   0: [mem 0x0000000100000000-0x000000011fffffff]
[    0.005500] Initmem setup node 0 [mem 0x0000000000001000-0x000000011fffffff]
[    0.005526] On node 0, zone DMA: 1 pages in unavailable ranges
[    0.005910] On node 0, zone DMA: 97 pages in unavailable ranges
[    0.102209] On node 0, zone Normal: 16 pages in unavailable ranges
[    0.103135] ACPI: PM-Timer IO Port: 0x4008
[    0.103617] IOAPIC[0]: apic_id 2, version 32, address 0xfec00000, GSI 0-23
[    0.103620] ACPI: INT_SRC_OVR (bus 0 bus_irq 0 global_irq 2 dfl dfl)
[    0.103622] ACPI: INT_SRC_OVR (bus 0 bus_irq 9 global_irq 9 low level)
[    0.103624] ACPI: Using ACPI (MADT) for SMP configuration information
[    0.103628] CPU topo: Max. logical packages:   1
[    0.103629] CPU topo: Max. logical dies:       1
[    0.103629] CPU topo: Max. dies per package:   1
[    0.103631] CPU topo: Max. threads per core:   1
[    0.103632] CPU topo: Num. cores per package:     2
[    0.103632] CPU topo: Num. threads per package:   2
[    0.103633] CPU topo: Allowing 2 present CPUs plus 0 hotplug CPUs
[    0.103713] PM: hibernation: Registered nosave memory: [mem 0x00000000-0x00000fff]
[    0.103724] PM: hibernation: Registered nosave memory: [mem 0x0009f000-0x000fffff]
[    0.103725] PM: hibernation: Registered nosave memory: [mem 0xdfff0000-0xffffffff]
[    0.103727] [mem 0xe0000000-0xfebfffff] available for PCI devices
[    0.103728] Booting paravirtualized kernel on KVM
[    0.103729] clocksource: refined-jiffies: mask: 0xffffffff max_cycles: 0xffffffff, max_idle_ns: 1910969940391419 ns
[    0.103735] setup_percpu: NR_CPUS:8192 nr_cpumask_bits:2 nr_cpu_ids:2 nr_node_ids:1
[    0.106823] percpu: Embedded 84 pages/cpu s221184 r8192 d114688 u1048576
[    0.106826] pcpu-alloc: s221184 r8192 d114688 u1048576 alloc=1*2097152
[    0.106828] pcpu-alloc: [0] 0 1 
[    0.106905] kvm-guest: PV spinlocks enabled
[    0.106907] PV qspinlock hash table entries: 256 (order: 0, 4096 bytes, linear)
[    0.106910] Kernel command line: BOOT_IMAGE=/boot/vmlinuz-6.17.0-22-generic root=UUID=154e4895-b405-436c-ac14-63ad0b84fe4c ro quiet splash
[    0.106950] Unknown kernel command line parameters "splash", will be passed to user space.
[    0.106964] random: crng init done
[    0.106965] printk: log buffer data + meta data: 262144 + 917504 = 1179648 bytes
[    0.113019] Dentry cache hash table entries: 524288 (order: 10, 4194304 bytes, linear)
[    0.116061] Inode-cache hash table entries: 262144 (order: 9, 2097152 bytes, linear)
[    0.116189] software IO TLB: area num 2.
[    0.169124] Fallback order for Node 0: 0 
[    0.169128] Built 1 zonelists, mobility grouping on.  Total pages: 1048462
[    0.169129] Policy zone: Normal
[    0.169137] mem auto-init: stack:all(zero), heap alloc:on, heap free:off
[    0.176763] SLUB: HWalign=64, Order=0-3, MinObjects=0, CPUs=2, Nodes=1
[    0.188545] ftrace: allocating 61414 entries in 240 pages
[    0.188547] ftrace: allocated 240 pages with 4 groups
[    0.189854] Dynamic Preempt: voluntary
[    0.190025] rcu: Preemptible hierarchical RCU implementation.
[    0.190026] rcu: 	RCU restricting CPUs from NR_CPUS=8192 to nr_cpu_ids=2.
[    0.190027] 	Trampoline variant of Tasks RCU enabled.
[    0.190028] 	Rude variant of Tasks RCU enabled.
[    0.190028] 	Tracing variant of Tasks RCU enabled.
[    0.190028] rcu: RCU calculated value of scheduler-enlistment delay is 100 jiffies.
[    0.190029] rcu: Adjusting geometry for rcu_fanout_leaf=16, nr_cpu_ids=2
[    0.190041] RCU Tasks: Setting shift to 1 and lim to 1 rcu_task_cb_adjust=1 rcu_task_cpu_ids=2.
[    0.190042] RCU Tasks Rude: Setting shift to 1 and lim to 1 rcu_task_cb_adjust=1 rcu_task_cpu_ids=2.
[    0.190043] RCU Tasks Trace: Setting shift to 1 and lim to 1 rcu_task_cb_adjust=1 rcu_task_cpu_ids=2.
[    0.193016] NR_IRQS: 524544, nr_irqs: 440, preallocated irqs: 16
[    0.193364] rcu: srcu_init: Setting srcu_struct sizes based on contention.
[    0.217051] Console: colour VGA+ 80x25
[    0.217053] printk: legacy console [tty0] enabled
[    0.217098] ACPI: Core revision 20250404
[    0.218367] APIC: Switch to symmetric I/O mode setup
[    0.224429] ..TIMER: vector=0x30 apic1=0 pin1=2 apic2=-1 pin2=-1
[    0.224553] clocksource: tsc-early: mask: 0xffffffffffffffff max_cycles: 0x6a776ec4191, max_idle_ns: 881591142850 ns
[    0.224559] Calibrating delay loop (skipped) preset value.. 7386.11 BogoMIPS (lpj=3693056)
[    0.225557] Last level iTLB entries: 4KB 512, 2MB 512, 4MB 256
[    0.225557] Last level dTLB entries: 4KB 2048, 2MB 2048, 4MB 1024, 1GB 0
[    0.225557] mitigations: Enabled attack vectors: user_kernel, user_user, guest_host, guest_guest, SMT mitigations: auto
[    0.225557] Speculative Return Stack Overflow: IBPB-extending microcode not applied!
[    0.225557] Speculative Return Stack Overflow: WARNING: See https://kernel.org/doc/html/latest/admin-guide/hw-vuln/srso.html for mitigation options.
[    0.225557] Transient Scheduler Attacks: Vulnerable: No microcode
[    0.225557] Spectre V2 : Mitigation: Retpolines
[    0.225557] Speculative Return Stack Overflow: Vulnerable: Safe RET, no microcode
[    0.225557] Spectre V1 : Mitigation: usercopy/swapgs barriers and __user pointer sanitization
[    0.225557] Spectre V2 : Spectre v2 / SpectreRSB: Filling RSB on context switch and VMEXIT
[    0.225557] active return thunk: srso_alias_return_thunk
[    0.225557] x86/fpu: Supporting XSAVE feature 0x001: 'x87 floating point registers'
[    0.225557] x86/fpu: Supporting XSAVE feature 0x002: 'SSE registers'
[    0.225557] x86/fpu: Supporting XSAVE feature 0x004: 'AVX registers'
[    0.225557] x86/fpu: xstate_offset[2]:  576, xstate_sizes[2]:  256
[    0.225557] x86/fpu: Enabled xstate features 0x7, context size is 832 bytes, using 'standard' format.
[    0.225557] Freeing SMP alternatives memory: 52K
[    0.225557] pid_max: default: 32768 minimum: 301
[    0.225557] LSM: initializing lsm=lockdown,capability,landlock,yama,apparmor,ima,evm
[    0.225557] landlock: Up and running.
[    0.225557] Yama: becoming mindful.
[    0.225557] AppArmor: AppArmor initialized
[    0.225557] Mount-cache hash table entries: 8192 (order: 4, 65536 bytes, linear)
[    0.225557] Mountpoint-cache hash table entries: 8192 (order: 4, 65536 bytes, linear)
[    0.341187] APIC calibration not consistent with PM-Timer: 131ms instead of 100ms
[    0.341191] APIC delta adjusted to PM-Timer: 6274432 (8267136)
[    0.341369] smpboot: CPU0: AMD Ryzen 5 5600X 6-Core Processor (family: 0x19, model: 0x21, stepping: 0x0)
[    0.341557] Performance Events: PMU not available due to virtualization, using software events only.
[    0.341557] signal: max sigframe size: 1776
[    0.341557] rcu: Hierarchical SRCU implementation.
[    0.341557] rcu: 	Max phase no-delay instances is 400.
[    0.341724] Timer migration: 1 hierarchy levels; 8 children per group; 1 crossnode level
[    0.346423] NMI watchdog: Perf NMI watchdog permanently disabled
[    0.346616] smp: Bringing up secondary CPUs ...
[    0.347097] smpboot: x86: Booting SMP configuration:
[    0.347099] .... node  #0, CPUs:      #1
[    0.350653] smp: Brought up 1 node, 2 CPUs
[    0.350657] smpboot: Total of 2 processors activated (14772.22 BogoMIPS)
[    0.350926] Memory: 3918304K/4193848K available (22217K kernel code, 4652K rwdata, 16296K rodata, 5268K init, 4212K bss, 269444K reserved, 0K cma-reserved)
[    0.351726] devtmpfs: initialized
[    0.351761] x86/mm: Memory block size: 128MB
[    0.354631] clocksource: jiffies: mask: 0xffffffff max_cycles: 0xffffffff, max_idle_ns: 1911260446275000 ns
[    0.354670] posixtimers hash table entries: 1024 (order: 2, 16384 bytes, linear)
[    0.354726] futex hash table entries: 512 (32768 bytes on 1 NUMA nodes, total 32 KiB, linear).
[    0.354814] pinctrl core: initialized pinctrl subsystem
[    0.355609] PM: RTC time: 16:24:16, date: 2026-05-18
[    0.360027] NET: Registered PF_NETLINK/PF_ROUTE protocol family
[    0.360903] DMA: preallocated 512 KiB GFP_KERNEL pool for atomic allocations
[    0.360950] DMA: preallocated 512 KiB GFP_KERNEL|GFP_DMA pool for atomic allocations
[    0.360996] DMA: preallocated 512 KiB GFP_KERNEL|GFP_DMA32 pool for atomic allocations
[    0.361009] audit: initializing netlink subsys (disabled)
[    0.361677] audit: type=2000 audit(1779121464.174:1): state=initialized audit_enabled=0 res=1
[    0.362206] thermal_sys: Registered thermal governor 'fair_share'
[    0.362208] thermal_sys: Registered thermal governor 'bang_bang'
[    0.362209] thermal_sys: Registered thermal governor 'step_wise'
[    0.362211] thermal_sys: Registered thermal governor 'user_space'
[    0.362212] thermal_sys: Registered thermal governor 'power_allocator'
[    0.362578] cpuidle: using governor ladder
[    0.362632] cpuidle: using governor menu
[    0.364810] acpiphp: ACPI Hot Plug PCI Controller Driver version: 0.5
[    0.365218] PCI: Using configuration type 1 for base access
[    0.365220] PCI: Using configuration type 1 for extended access
[    0.365281] mtrr: your CPUs had inconsistent variable MTRR settings
[    0.365283] mtrr: probably your BIOS does not setup all CPUs.
[    0.365284] mtrr: corrected configuration.
[    0.365639] kprobes: kprobe jump-optimization is enabled. All kprobes are optimized if possible.
[    0.366581] HugeTLB: registered 2.00 MiB page size, pre-allocated 0 pages
[    0.366583] HugeTLB: 28 KiB vmemmap can be freed for a 2.00 MiB page
[    0.380213] ACPI: Added _OSI(Module Device)
[    0.380215] ACPI: Added _OSI(Processor Device)
[    0.380217] ACPI: Added _OSI(Processor Aggregator Device)
[    0.380557] ACPI: 2 ACPI AML tables successfully acquired and loaded
[    0.380865] ACPI: Interpreter enabled
[    0.380879] ACPI: PM: (supports S0 S5)
[    0.380881] ACPI: Using IOAPIC for interrupt routing
[    0.381879] PCI: Using host bridge windows from ACPI; if necessary, use "pci=nocrs" and report a bug
[    0.381881] PCI: Using E820 reservations for host bridge windows
[    0.382031] ACPI: Enabled 2 GPEs in block 00 to 07
[    0.394416] ACPI: PCI Root Bridge [PCI0] (domain 0000 [bus 00-ff])
[    0.394423] acpi PNP0A03:00: _OSC: OS supports [ExtendedConfig ASPM ClockPM Segments MSI EDR HPX-Type3]
[    0.395393] acpi PNP0A03:00: _OSC: platform does not support [PCIeCapability LTR DPC]
[    0.395557] acpi PNP0A03:00: _OSC: not requesting control; platform does not support [PCIeCapability]
[    0.395557] acpi PNP0A03:00: _OSC: OS requested [PCIeHotplug SHPCHotplug PME AER PCIeCapability LTR DPC]
[    0.395557] acpi PNP0A03:00: _OSC: platform willing to grant [PCIeHotplug SHPCHotplug PME AER]
[    0.395557] acpi PNP0A03:00: _OSC: platform retains control of PCIe features (AE_SUPPORT)
[    0.395982] PCI host bridge to bus 0000:00
[    0.395986] pci_bus 0000:00: root bus resource [io  0x0000-0x0cf7 window]
[    0.395989] pci_bus 0000:00: root bus resource [io  0x0d00-0xffff window]
[    0.395991] pci_bus 0000:00: root bus resource [mem 0x000a0000-0x000bffff window]
[    0.395993] pci_bus 0000:00: root bus resource [mem 0xe0000000-0xfdffffff window]
[    0.395995] pci_bus 0000:00: root bus resource [bus 00-ff]
[    0.396619] pci 0000:00:00.0: [8086:1237] type 00 class 0x060000 conventional PCI endpoint
[    0.397594] pci 0000:00:01.0: [8086:7000] type 00 class 0x060100 conventional PCI endpoint
[    0.398606] pci 0000:00:01.1: [8086:7111] type 00 class 0x01018a conventional PCI endpoint
[    0.399189] pci 0000:00:01.1: BAR 4 [io  0xd000-0xd00f]
[    0.399262] pci 0000:00:01.1: BAR 0 [io  0x01f0-0x01f7]: legacy IDE quirk
[    0.399264] pci 0000:00:01.1: BAR 1 [io  0x03f6]: legacy IDE quirk
[    0.399266] pci 0000:00:01.1: BAR 2 [io  0x0170-0x0177]: legacy IDE quirk
[    0.399267] pci 0000:00:01.1: BAR 3 [io  0x0376]: legacy IDE quirk
[    0.399679] pci 0000:00:02.0: [15ad:0405] type 00 class 0x030000 conventional PCI endpoint
[    0.401095] pci 0000:00:02.0: BAR 0 [io  0xd010-0xd01f]
[    0.401113] pci 0000:00:02.0: BAR 1 [mem 0xe0000000-0xe7ffffff pref]
[    0.401129] pci 0000:00:02.0: BAR 2 [mem 0xf0000000-0xf01fffff]
[    0.401260] pci 0000:00:02.0: Video device with shadowed ROM at [mem 0x000c0000-0x000dffff]
[    0.401557] pci 0000:00:03.0: [8086:100e] type 00 class 0x020000 conventional PCI endpoint
[    0.402071] pci 0000:00:03.0: BAR 0 [mem 0xf0200000-0xf021ffff]
[    0.402102] pci 0000:00:03.0: BAR 2 [io  0xd020-0xd027]
[    0.402557] pci 0000:00:04.0: [80ee:cafe] type 00 class 0x088000 conventional PCI endpoint
[    0.402576] pci 0000:00:04.0: BAR 0 [io  0xd040-0xd05f]
[    0.402593] pci 0000:00:04.0: BAR 1 [mem 0xf0400000-0xf07fffff]
[    0.402610] pci 0000:00:04.0: BAR 2 [mem 0xf0800000-0xf0803fff pref]
[    0.402958] pci 0000:00:05.0: [8086:2415] type 00 class 0x040100 conventional PCI endpoint
[    0.403604] pci 0000:00:05.0: BAR 0 [io  0xd100-0xd1ff]
[    0.403621] pci 0000:00:05.0: BAR 1 [io  0xd200-0xd23f]
[    0.403998] pci 0000:00:06.0: [106b:003f] type 00 class 0x0c0310 conventional PCI endpoint
[    0.404621] pci 0000:00:06.0: BAR 0 [mem 0xf0804000-0xf0804fff]
[    0.405146] pci 0000:00:07.0: [8086:7113] type 00 class 0x068000 conventional PCI endpoint
[    0.405893] pci 0000:00:07.0: quirk: [io  0x4000-0x403f] claimed by PIIX4 ACPI
[    0.405910] pci 0000:00:07.0: quirk: [io  0x4100-0x410f] claimed by PIIX4 SMB
[    0.422239] pci 0000:00:0d.0: [8086:2829] type 00 class 0x010601 conventional PCI endpoint
[    0.422850] pci 0000:00:0d.0: BAR 0 [io  0xd240-0xd247]
[    0.422868] pci 0000:00:0d.0: BAR 1 [io  0xd248-0xd24b]
[    0.422884] pci 0000:00:0d.0: BAR 2 [io  0xd250-0xd257]
[    0.422900] pci 0000:00:0d.0: BAR 3 [io  0xd258-0xd25b]
[    0.422917] pci 0000:00:0d.0: BAR 4 [io  0xd260-0xd26f]
[    0.422933] pci 0000:00:0d.0: BAR 5 [mem 0xf0806000-0xf0807fff]
[    0.482818] ACPI: PCI: Interrupt link LNKA configured for IRQ 11
[    0.483334] ACPI: PCI: Interrupt link LNKB configured for IRQ 10
[    0.483579] ACPI: PCI: Interrupt link LNKC configured for IRQ 9
[    0.483752] ACPI: PCI: Interrupt link LNKD configured for IRQ 11
[    0.484652] iommu: Default domain type: Translated
[    0.484652] iommu: DMA domain TLB invalidation policy: lazy mode
[    0.485039] SCSI subsystem initialized
[    0.485731] libata version 3.00 loaded.
[    0.485731] ACPI: bus type USB registered
[    0.485751] usbcore: registered new interface driver usbfs
[    0.485776] usbcore: registered new interface driver hub
[    0.485785] usbcore: registered new device driver usb
[    0.485814] pps_core: LinuxPPS API ver. 1 registered
[    0.485816] pps_core: Software ver. 5.3.6 - Copyright 2005-2007 Rodolfo Giometti <giometti@linux.it>
[    0.485820] PTP clock support registered
[    0.486742] EDAC MC: Ver: 3.0.0
[    0.489400] NetLabel: Initializing
[    0.489402] NetLabel:  domain hash size = 128
[    0.489404] NetLabel:  protocols = UNLABELED CIPSOv4 CALIPSO
[    0.489441] NetLabel:  unlabeled traffic allowed by default
[    0.489664] mctp: management component transport protocol core
[    0.489664] NET: Registered PF_MCTP protocol family
[    0.489664] PCI: Using ACPI for IRQ routing
[    0.489664] PCI: pci_cache_line_size set to 64 bytes
[    0.489910] e820: reserve RAM buffer [mem 0x0009fc00-0x0009ffff]
[    0.489913] e820: reserve RAM buffer [mem 0xdfff0000-0xdfffffff]
[    0.490584] pci 0000:00:02.0: vgaarb: setting as boot VGA device
[    0.490587] pci 0000:00:02.0: vgaarb: bridge control possible
[    0.490589] pci 0000:00:02.0: vgaarb: VGA device added: decodes=io+mem,owns=io+mem,locks=none
[    0.490592] vgaarb: loaded
[    0.490811] clocksource: Switched to clocksource kvm-clock
[    0.494239] VFS: Disk quotas dquot_6.6.0
[    0.494257] VFS: Dquot-cache hash table entries: 512 (order 0, 4096 bytes)
[    0.495303] AppArmor: AppArmor Filesystem Enabled
[    0.495322] pnp: PnP ACPI init
[    0.496836] pnp: PnP ACPI: found 2 devices
[    0.523995] clocksource: acpi_pm: mask: 0xffffff max_cycles: 0xffffff, max_idle_ns: 2085701024 ns
[    0.524098] NET: Registered PF_INET protocol family
[    0.525096] IP idents hash table entries: 65536 (order: 7, 524288 bytes, linear)
[    0.543137] tcp_listen_portaddr_hash hash table entries: 2048 (order: 3, 32768 bytes, linear)
[    0.543137] Table-perturb hash table entries: 65536 (order: 6, 262144 bytes, linear)
[    0.543137] TCP established hash table entries: 32768 (order: 6, 262144 bytes, linear)
[    0.543137] TCP bind hash table entries: 32768 (order: 8, 1048576 bytes, linear)
[    0.543137] TCP: Hash tables configured (established 32768 bind 32768)
[    0.543137] MPTCP token hash table entries: 4096 (order: 5, 98304 bytes, linear)
[    0.543137] UDP hash table entries: 2048 (order: 5, 131072 bytes, linear)
[    0.543137] UDP-Lite hash table entries: 2048 (order: 5, 131072 bytes, linear)
[    0.543137] NET: Registered PF_UNIX/PF_LOCAL protocol family
[    0.543137] NET: Registered PF_XDP protocol family
[    0.543137] pci_bus 0000:00: resource 4 [io  0x0000-0x0cf7 window]
[    0.543137] pci_bus 0000:00: resource 5 [io  0x0d00-0xffff window]
[    0.543137] pci_bus 0000:00: resource 6 [mem 0x000a0000-0x000bffff window]
[    0.543137] pci_bus 0000:00: resource 7 [mem 0xe0000000-0xfdffffff window]
[    0.549638] pci 0000:00:00.0: Limiting direct PCI/PCI transfers
[    0.552561] PCI: CLS 0 bytes, default 64
[    0.552688] PCI-DMA: Using software bounce buffering for IO (SWIOTLB)
[    0.552690] software IO TLB: mapped [mem 0x00000000dbff0000-0x00000000dfff0000] (64MB)
[    0.552746] clocksource: tsc: mask: 0xffffffffffffffff max_cycles: 0x6a776ec4191, max_idle_ns: 881591142850 ns
[    0.552767] clocksource: Switched to clocksource tsc
[    0.552799] platform rtc_cmos: registered platform RTC device (no PNP device found)
[    0.552843] Trying to unpack rootfs image as initramfs...
[    0.573397] Initialise system trusted keyrings
[    0.573407] Key type blacklist registered
[    0.573505] workingset: timestamp_bits=36 max_order=20 bucket_order=0
[    0.573786] squashfs: version 4.0 (2009/01/31) Phillip Lougher
[    0.573896] fuse: init (API version 7.44)
[    0.575501] integrity: Platform Keyring initialized
[    0.575505] integrity: Machine keyring initialized
[    0.576107] Key type asymmetric registered
[    0.576107] Asymmetric key parser 'x509' registered
[    0.576107] Block layer SCSI generic (bsg) driver version 0.4 loaded (major 242)
[    0.584963] io scheduler mq-deadline registered
[    0.585626] ledtrig-cpu: registered to indicate activity on CPUs
[    0.586078] ACPI: AC: AC Adapter [AC] (on-line)
[    0.586166] input: Power Button as /devices/LNXSYSTM:00/LNXPWRBN:00/input/input0
[    0.586512] ACPI: button: Power Button [PWRF]
[    0.586570] input: Sleep Button as /devices/LNXSYSTM:00/LNXSLPBN:00/input/input1
[    0.586644] ACPI: button: Sleep Button [SLPF]
[    0.587352] Serial: 8250/16550 driver, 32 ports, IRQ sharing enabled
[    0.589198] Linux agpgart interface v0.103
[    0.592663] loop: module loaded
[    0.596729] scsi host0: ata_piix
[    0.597200] scsi host1: ata_piix
[    0.597253] ata1: PATA max UDMA/33 cmd 0x1f0 ctl 0x3f6 bmdma 0xd000 irq 14 lpm-pol 0
[    0.597256] ata2: PATA max UDMA/33 cmd 0x170 ctl 0x376 bmdma 0xd008 irq 15 lpm-pol 0
[    0.597380] ACPI: bus type drm_connector registered
[    0.597651] tun: Universal TUN/TAP device driver, 1.6
[    0.597708] PPP generic driver version 2.4.2
[    0.599259] ohci-pci 0000:00:06.0: OHCI PCI host controller
[    0.599266] ohci-pci 0000:00:06.0: new USB bus registered, assigned bus number 1
[    0.600193] ohci-pci 0000:00:06.0: irq 22, io mem 0xf0804000
[    0.850067] ata1.00: ATAPI: VBOX CD-ROM, 1.0, max UDMA/133
[    0.851183] usb usb1: New USB device found, idVendor=1d6b, idProduct=0001, bcdDevice= 6.17
[    0.851188] usb usb1: New USB device strings: Mfr=3, Product=2, SerialNumber=1
[    0.851190] usb usb1: Product: OHCI PCI host controller
[    0.851192] usb usb1: Manufacturer: Linux 6.17.0-22-generic ohci_hcd
[    0.851193] usb usb1: SerialNumber: 0000:00:06.0
[    0.851193] Freeing initrd memory: 76636K
[    0.851203] hub 1-0:1.0: USB hub found
[    0.851482] hub 1-0:1.0: 12 ports detected
[    0.852278] scsi 0:0:0:0: CD-ROM            VBOX     CD-ROM           1.0  PQ: 0 ANSI: 5
[    0.852591] i8042: PNP: PS/2 Controller [PNP0303:PS2K,PNP0f03:PS2M] at 0x60,0x64 irq 1,12
[    0.854424] serio: i8042 KBD port at 0x60,0x64 irq 1
[    0.854431] serio: i8042 AUX port at 0x60,0x64 irq 12
[    0.854710] mousedev: PS/2 mouse device common for all mice
[    0.856012] rtc_cmos rtc_cmos: registered as rtc0
[    0.856354] rtc_cmos rtc_cmos: setting system clock to 2026-05-18T16:24:17 UTC (1779121457)
[    0.856455] rtc_cmos rtc_cmos: alarms up to one day, 114 bytes nvram
[    0.856587] i2c_dev: i2c /dev entries driver
[    0.856633] device-mapper: core: CONFIG_IMA_DISABLE_HTABLE is disabled. Duplicate IMA measurements will not be recorded in the IMA log.
[    0.856648] device-mapper: uevent: version 1.0.3
[    0.856867] device-mapper: ioctl: 4.50.0-ioctl (2025-04-28) initialised: dm-devel@lists.linux.dev
[    0.856873] amd_pstate: the _CPC object is not present in SBIOS or ACPI disabled
[    0.857056] drop_monitor: Initializing network drop monitor service
[    0.857776] input: AT Translated Set 2 keyboard as /devices/platform/i8042/serio0/input/input2
[    0.857828] NET: Registered PF_INET6 protocol family
[    0.859243] sr 0:0:0:0: [sr0] scsi3-mmc drive: 32x/32x xa/form2 tray
[    0.859246] cdrom: Uniform CD-ROM driver Revision: 3.20
[    0.859248] Segment Routing with IPv6
[    0.859257] In-situ OAM (IOAM) with IPv6
[    0.859278] NET: Registered PF_PACKET protocol family
[    0.859319] Key type dns_resolver registered
[    0.861329] IPI shorthand broadcast: enabled
[    0.864152] sched_clock: Marking stable (832461316, 31102625)->(898380083, -34816142)
[    0.864914] registered taskstats version 1
[    0.865726] Loading compiled-in X.509 certificates
[    0.866572] Loaded X.509 cert 'Build time autogenerated kernel key: 10e561fe75970ebe98357e1cb1b79397dec08fd7'
[    0.866848] Loaded X.509 cert 'Canonical Ltd. Live Patch Signing 2025 Kmod: d541cef61dc7e793b7eb7e899970a2eef0b5dc8c'
[    0.867128] Loaded X.509 cert 'Canonical Ltd. Live Patch Signing: 14df34d1a87cf37625abec039ef2bf521249b969'
[    0.867404] Loaded X.509 cert 'Canonical Ltd. Kernel Module Signing: 88f752e560a1e0737e31163a466ad7b70a850c19'
[    0.867406] blacklist: Loading compiled-in revocation X.509 certificates
[    0.867487] Loaded X.509 cert 'Canonical Ltd. Secure Boot Signing: 61482aa2830d0ab2ad5af10b7250da9033ddcef0'
[    0.867500] Loaded X.509 cert 'Canonical Ltd. Secure Boot Signing (2017): 242ade75ac4a15e50d50c84b0d45ff3eae707a03'
[    0.867508] Loaded X.509 cert 'Canonical Ltd. Secure Boot Signing (ESM 2018): 365188c1d374d6b07c3c8f240f8ef722433d6a8b'
[    0.867517] Loaded X.509 cert 'Canonical Ltd. Secure Boot Signing (2019): c0746fd6c5da3ae827864651ad66ae47fe24b3e8'
[    0.867526] Loaded X.509 cert 'Canonical Ltd. Secure Boot Signing (2021 v1): a8d54bbb3825cfb94fa13c9f8a594a195c107b8d'
[    0.867536] Loaded X.509 cert 'Canonical Ltd. Secure Boot Signing (2021 v2): 4cf046892d6fd3c9a5b03f98d845f90851dc6a8c'
[    0.867565] Loaded X.509 cert 'Canonical Ltd. Secure Boot Signing (2021 v3): 100437bb6de6e469b581e61cd66bce3ef4ed53af'
[    0.867575] Loaded X.509 cert 'Canonical Ltd. Secure Boot Signing (Ubuntu Core 2019): c1d57b8f6b743f23ee41f4f7ee292f06eecadfb9'
[    0.868682] sr 0:0:0:0: Attached scsi CD-ROM sr0
[    0.868992] sr 0:0:0:0: Attached scsi generic sg0 type 5
[    0.877023] Demotion targets for Node 0: null
[    0.877336] Key type .fscrypt registered
[    0.877339] Key type fscrypt-provisioning registered
[    0.877424] Key type big_key registered
[    0.899366] Key type encrypted registered
[    0.899370] AppArmor: AppArmor sha256 policy hashing enabled
[    0.899380] ima: No TPM chip found, activating TPM-bypass!
[    0.899384] Loading compiled-in module X.509 certificates
[    0.899789] Loaded X.509 cert 'Build time autogenerated kernel key: 10e561fe75970ebe98357e1cb1b79397dec08fd7'
[    0.899793] ima: Allocated hash algorithm: sha256
[    0.899808] ima: No architecture policies found
[    0.899823] evm: Initialising EVM extended attributes:
[    0.899825] evm: security.selinux
[    0.899827] evm: security.SMACK64
[    0.899829] evm: security.SMACK64EXEC
[    0.899830] evm: security.SMACK64TRANSMUTE
[    0.899831] evm: security.SMACK64MMAP
[    0.899832] evm: security.apparmor
[    0.899833] evm: security.ima
[    0.899834] evm: security.capability
[    0.899836] evm: HMAC attrs: 0x1
[    0.900473] PM:   Magic number: 10:418:439
[    0.904603] RAS: Correctable Errors collector initialized.
[    0.912519] clk: Disabling unused clocks
[    0.912522] PM: genpd: Disabling unused power domains
[    0.914830] Freeing unused decrypted memory: 2028K
[    0.916288] Freeing unused kernel image (initmem) memory: 5268K
[    0.916307] Write protecting the kernel read-only data: 38912k
[    0.917312] Freeing unused kernel image (text/rodata gap) memory: 308K
[    0.917588] Freeing unused kernel image (rodata/data gap) memory: 88K
[    0.961012] x86/mm: Checked W+X mappings: passed, no W+X pages found.
[    0.961018] Run /init as init process
[    0.961019]   with arguments:
[    0.961021]     /init
[    0.961022]     splash
[    0.961024]   with environment:
[    0.961025]     HOME=/
[    0.961026]     TERM=linux
[    1.125969] input: ImExPS/2 Generic Explorer Mouse as /devices/platform/i8042/serio1/input/input4
[    1.127926] ACPI: video: Video Device [GFX0] (multi-head: yes  rom: no  post: no)
[    1.128022] input: Video Bus as /devices/LNXSYSTM:00/LNXSYBUS:00/PNP0A03:00/LNXVIDEO:00/input/input5
[    1.138655] e1000: Intel(R) PRO/1000 Network Driver
[    1.138658] e1000: Copyright (c) 1999-2006 Intel Corporation.
[    1.164471] ahci 0000:00:0d.0: SSS flag set, parallel bus scan disabled
[    1.165290] ahci 0000:00:0d.0: AHCI vers 0001.0100, 32 command slots, 3 Gbps, SATA mode
[    1.165293] ahci 0000:00:0d.0: 2/2 ports implemented (port mask 0x3)
[    1.165295] ahci 0000:00:0d.0: flags: 64bit ncq stag only ccc 
[    1.173321] scsi host2: ahci
[    1.173835] scsi host3: ahci
[    1.173950] ata3: SATA max UDMA/133 abar m8192@0xf0806000 port 0xf0806100 irq 21 lpm-pol 1
[    1.173968] ata4: SATA max UDMA/133 abar m8192@0xf0806000 port 0xf0806180 irq 21 lpm-pol 1
[    1.192030] usb 1-1: new full-speed USB device number 2 using ohci-pci
[    1.447760] usb 1-1: New USB device found, idVendor=80ee, idProduct=0021, bcdDevice= 1.00
[    1.447767] usb 1-1: New USB device strings: Mfr=1, Product=3, SerialNumber=0
[    1.447770] usb 1-1: Product: USB Tablet
[    1.447772] usb 1-1: Manufacturer: VirtualBox
[    1.459506] hid: raw HID events driver (C) Jiri Kosina
[    1.486636] ata3: SATA link up 3.0 Gbps (SStatus 123 SControl 300)
[    1.486969] ata3.00: ATA-6: VBOX HARDDISK, 1.0, max UDMA/133
[    1.486973] ata3.00: 52428800 sectors, multi 128: LBA48 NCQ (depth 32)
[    1.487340] ata3.00: configured for UDMA/133
[    1.487498] scsi 2:0:0:0: Direct-Access     ATA      VBOX HARDDISK    1.0  PQ: 0 ANSI: 5
[    1.487747] scsi 2:0:0:0: Attached scsi generic sg1 type 0
[    1.487842] sd 2:0:0:0: [sda] 52428800 512-byte logical blocks: (26.8 GB/25.0 GiB)
[    1.487852] sd 2:0:0:0: [sda] Write Protect is off
[    1.487854] sd 2:0:0:0: [sda] Mode Sense: 00 3a 00 00
[    1.487868] sd 2:0:0:0: [sda] Write cache: enabled, read cache: enabled, doesn't support DPO or FUA
[    1.487893] sd 2:0:0:0: [sda] Preferred minimum I/O size 512 bytes
[    1.504719]  sda: sda1 sda2
[    1.504971] sd 2:0:0:0: [sda] Attached SCSI disk
[    1.631635] e1000 0000:00:03.0 eth0: (PCI:33MHz:32-bit) 08:00:27:dd:25:c2
[    1.631647] e1000 0000:00:03.0 eth0: Intel(R) PRO/1000 Network Connection
[    2.351347] clocksource: Long readout interval, skipping watchdog check: cs_nsec: 1118179644 wd_nsec: 1118179522
[    2.457547] ata4: SATA link up 3.0 Gbps (SStatus 123 SControl 300)
[    2.457875] ata4.00: ATA-6: VBOX HARDDISK, 1.0, max UDMA/133
[    2.457878] ata4.00: 204800 sectors, multi 128: LBA48 NCQ (depth 32)
[    2.458457] ata4.00: configured for UDMA/133
[    2.458804] scsi 3:0:0:0: Direct-Access     ATA      VBOX HARDDISK    1.0  PQ: 0 ANSI: 5
[    2.459298] sd 3:0:0:0: [sdb] 204800 512-byte logical blocks: (105 MB/100 MiB)
[    2.459311] sd 3:0:0:0: [sdb] Write Protect is off
[    2.459314] sd 3:0:0:0: [sdb] Mode Sense: 00 3a 00 00
[    2.459325] sd 3:0:0:0: [sdb] Write cache: enabled, read cache: enabled, doesn't support DPO or FUA
[    2.459346] sd 3:0:0:0: [sdb] Preferred minimum I/O size 512 bytes
[    2.459530] sd 3:0:0:0: Attached scsi generic sg2 type 0
[    2.851711] sd 3:0:0:0: [sdb] Attached SCSI disk
[    2.855523] e1000 0000:00:03.0 enp0s3: renamed from eth0
[    2.880950] usbcore: registered new interface driver usbhid
[    2.880953] usbhid: USB HID core driver
[    2.886792] input: VirtualBox USB Tablet as /devices/pci0000:00/0000:00:06.0/usb1/1-1/1-1:1.0/0003:80EE:0021.0001/input/input6
[    2.886911] hid-generic 0003:80EE:0021.0001: input,hidraw0: USB HID v1.10 Mouse [VirtualBox USB Tablet] on usb-0000:00:06.0-1/input0
[    4.269805] EXT4-fs (sda2): mounted filesystem 154e4895-b405-436c-ac14-63ad0b84fe4c ro with ordered data mode. Quota mode: none.
[    4.528342] systemd[1]: Inserted module 'autofs4'
[    4.555616] systemd[1]: systemd 255.4-1ubuntu8.15 running in system mode (+PAM +AUDIT +SELINUX +APPARMOR +IMA +SMACK +SECCOMP +GCRYPT -GNUTLS +OPENSSL +ACL +BLKID +CURL +ELFUTILS +FIDO2 +IDN2 -IDN +IPTC +KMOD +LIBCRYPTSETUP +LIBFDISK +PCRE2 -PWQUALITY +P11KIT +QRENCODE +TPM2 +BZIP2 +LZ4 +XZ +ZLIB +ZSTD -BPF_FRAMEWORK -XKBCOMMON +UTMP +SYSVINIT default-hierarchy=unified)
[    4.555621] systemd[1]: Detected virtualization oracle.
[    4.555690] systemd[1]: Detected architecture x86-64.
[    4.558438] systemd[1]: Hostname set to <UbuntuSdC>.
[    4.907418] systemd[1]: Queued start job for default target graphical.target.
[    4.922097] systemd[1]: Created slice system-modprobe.slice - Slice /system/modprobe.
[    4.922383] systemd[1]: Created slice user.slice - User and Session Slice.
[    4.922437] systemd[1]: Started systemd-ask-password-wall.path - Forward Password Requests to Wall Directory Watch.
[    4.922587] systemd[1]: Set up automount proc-sys-fs-binfmt_misc.automount - Arbitrary Executable File Formats File System Automount Point.
[    4.922605] systemd[1]: Reached target integritysetup.target - Local Integrity Protected Volumes.
[    4.922622] systemd[1]: Reached target remote-fs.target - Remote File Systems.
[    4.922628] systemd[1]: Reached target slices.target - Slice Units.
[    4.922635] systemd[1]: Reached target snapd.mounts-pre.target - Mounting snaps.
[    4.922643] systemd[1]: Reached target swap.target - Swaps.
[    4.922652] systemd[1]: Reached target veritysetup.target - Local Verity Protected Volumes.
[    4.923205] systemd[1]: Listening on syslog.socket - Syslog Socket.
[    4.923293] systemd[1]: Listening on systemd-fsckd.socket - fsck to fsckd communication Socket.
[    4.923363] systemd[1]: Listening on systemd-initctl.socket - initctl Compatibility Named Pipe.
[    4.923457] systemd[1]: Listening on systemd-journald-dev-log.socket - Journal Socket (/dev/log).
[    4.923552] systemd[1]: Listening on systemd-journald.socket - Journal Socket.
[    4.923683] systemd[1]: Listening on systemd-oomd.socket - Userspace Out-Of-Memory (OOM) Killer Socket.
[    4.923696] systemd[1]: systemd-pcrextend.socket - TPM2 PCR Extension (Varlink) was skipped because of an unmet condition check (ConditionSecurity=measured-uki).
[    4.924217] systemd[1]: Listening on systemd-udevd-control.socket - udev Control Socket.
[    4.924427] systemd[1]: Listening on systemd-udevd-kernel.socket - udev Kernel Socket.
[    4.925910] systemd[1]: Mounting dev-hugepages.mount - Huge Pages File System...
[    4.927051] systemd[1]: Mounting dev-mqueue.mount - POSIX Message Queue File System...
[    4.927702] systemd[1]: Mounting sys-kernel-debug.mount - Kernel Debug File System...
[    4.936413] systemd[1]: Mounting sys-kernel-tracing.mount - Kernel Trace File System...
[    4.944491] systemd[1]: Starting systemd-journald.service - Journal Service...
[    4.945108] systemd[1]: Starting keyboard-setup.service - Set the console keyboard layout...
[    4.946996] systemd[1]: Starting kmod-static-nodes.service - Create List of Static Device Nodes...
[    4.951861] systemd[1]: Starting modprobe@configfs.service - Load Kernel Module configfs...
[    4.954010] systemd[1]: Starting modprobe@dm_mod.service - Load Kernel Module dm_mod...
[    4.966477] systemd-journald[235]: Collecting audit messages is disabled.
[    4.971291] systemd[1]: Starting modprobe@drm.service - Load Kernel Module drm...
[    4.971952] systemd[1]: Starting modprobe@efi_pstore.service - Load Kernel Module efi_pstore...
[    4.985327] systemd[1]: Starting modprobe@fuse.service - Load Kernel Module fuse...
[    4.986817] systemd[1]: Starting modprobe@loop.service - Load Kernel Module loop...
[    4.986953] systemd[1]: systemd-fsck-root.service - File System Check on Root Device was skipped because of an unmet condition check (ConditionPathExists=!/run/initramfs/fsck-root).
[    4.996598] systemd[1]: Starting systemd-modules-load.service - Load Kernel Modules...
[    4.996610] systemd[1]: systemd-pcrmachine.service - TPM2 PCR Machine ID Measurement was skipped because of an unmet condition check (ConditionSecurity=measured-uki).
[    5.004876] systemd[1]: Starting systemd-remount-fs.service - Remount Root and Kernel File Systems...
[    5.004909] systemd[1]: systemd-tpm2-setup-early.service - TPM2 SRK Setup (Early) was skipped because of an unmet condition check (ConditionSecurity=measured-uki).
[    5.008206] systemd[1]: Starting systemd-udev-trigger.service - Coldplug All udev Devices...
[    5.013441] systemd[1]: Started systemd-journald.service - Journal Service.
[    5.041667] lp: driver loaded but no devices found
[    5.044735] EXT4-fs (sda2): re-mounted 154e4895-b405-436c-ac14-63ad0b84fe4c r/w.
[    5.049194] ppdev: user-space parallel port driver
[    5.166078] systemd-journald[235]: Received client request to flush runtime journal.
[    5.187628] systemd-journald[235]: File /var/log/journal/f74464dae0f64b65a6b2fd9e00edcb0c/system.journal corrupted or uncleanly shut down, renaming and replacing.
[    5.296356] loop0: detected capacity change from 0 to 8
[    5.305707] loop1: detected capacity change from 0 to 151464
[    5.309623] loop2: detected capacity change from 0 to 151512
[    5.316625] loop3: detected capacity change from 0 to 136816
[    5.322217] loop4: detected capacity change from 0 to 136904
[    5.331340] loop5: detected capacity change from 0 to 515416
[    5.335588] loop6: detected capacity change from 0 to 33792
[    5.347622] loop7: detected capacity change from 0 to 1088256
[    5.349936] loop8: detected capacity change from 0 to 37864
[    5.352569] loop9: detected capacity change from 0 to 1241248
[    5.525116] audit: type=1400 audit(1779121462.168:2): apparmor="STATUS" operation="profile_load" profile="unconfined" name="1password" pid=358 comm="apparmor_parser"
[    5.525455] audit: type=1400 audit(1779121462.168:3): apparmor="STATUS" operation="profile_load" profile="unconfined" name="Discord" pid=359 comm="apparmor_parser"
[    5.530837] audit: type=1400 audit(1779121462.173:4): apparmor="STATUS" operation="profile_load" profile="unconfined" name="QtWebEngineProcess" pid=361 comm="apparmor_parser"
[    5.533493] audit: type=1400 audit(1779121462.176:5): apparmor="STATUS" operation="profile_load" profile="unconfined" name="balena-etcher" pid=362 comm="apparmor_parser"
[    5.535746] audit: type=1400 audit(1779121462.178:6): apparmor="STATUS" operation="profile_load" profile="unconfined" name=4D6F6E676F444220436F6D70617373 pid=360 comm="apparmor_parser"
[    5.538229] audit: type=1400 audit(1779121462.180:7): apparmor="STATUS" operation="profile_load" profile="unconfined" name="brave" pid=363 comm="apparmor_parser"
[    5.539398] audit: type=1400 audit(1779121462.182:8): apparmor="STATUS" operation="profile_load" profile="unconfined" name="buildah" pid=364 comm="apparmor_parser"
[    5.542202] audit: type=1400 audit(1779121462.184:9): apparmor="STATUS" operation="profile_load" profile="unconfined" name="ch-checkns" pid=366 comm="apparmor_parser"
[    5.543415] audit: type=1400 audit(1779121462.186:10): apparmor="STATUS" operation="profile_load" profile="unconfined" name="cam" pid=365 comm="apparmor_parser"
[    5.544612] audit: type=1400 audit(1779121462.186:11): apparmor="STATUS" operation="profile_load" profile="unconfined" name="ch-run" pid=367 comm="apparmor_parser"
[    6.215063] piix4_smbus 0000:00:07.0: SMBus Host Controller at 0x4100, revision 0
[    6.269166] vboxguest: host-version: 7.2.6r172322 0x8000000f
[    6.274281] vbg_heartbeat_init: Setting up heartbeat to trigger every 2000 milliseconds
[    6.284400] input: VirtualBox mouse integration as /devices/pci0000:00/0000:00:04.0/input/input7
[    6.530375] intel_rapl_common: Found RAPL domain package
[    6.530398] intel_rapl_common: Found RAPL domain core
[    6.530702] vmwgfx 0000:00:02.0: vgaarb: deactivate vga console
[    6.530805] Console: switching to colour dummy device 80x25
[    6.531841] vmwgfx 0000:00:02.0: [drm] FIFO at 0x00000000f0000000 size is 2048 KiB
[    6.531854] vmwgfx 0000:00:02.0: [drm] VRAM at 0x00000000e0000000 size is 131072 KiB
[    6.531894] vmwgfx 0000:00:02.0: [drm] Running on SVGA version 2.
[    6.531912] vmwgfx 0000:00:02.0: [drm] Capabilities: rect copy, cursor, cursor bypass, cursor bypass 2, alpha cursor, extended fifo, pitchlock, irq mask, gmr, traces, gmr2, screen object 2, command buffers, command buffers 2, gbobject, 
[    6.531914] vmwgfx 0000:00:02.0: [drm] *ERROR* vmwgfx seems to be running on an unsupported hypervisor.
[    6.531917] vmwgfx 0000:00:02.0: [drm] *ERROR* This configuration is likely broken.
[    6.531919] vmwgfx 0000:00:02.0: [drm] *ERROR* Please switch to a supported graphics device to avoid problems.
[    6.531922] vmwgfx 0000:00:02.0: [drm] DMA map mode: Caching DMA mappings.
[    6.532166] vmwgfx 0000:00:02.0: [drm] Legacy memory limits: VRAM = 131072 KiB, FIFO = 2048 KiB, surface = 393216 KiB
[    6.532169] vmwgfx 0000:00:02.0: [drm] MOB limits: max mob size = 131072 KiB, max mob pages = 32768
[    6.532171] vmwgfx 0000:00:02.0: [drm] Max GMR ids is 8192
[    6.532173] vmwgfx 0000:00:02.0: [drm] Max number of GMR pages is 1048576
[    6.532174] vmwgfx 0000:00:02.0: [drm] Maximum display memory size is 131072 KiB
[    6.552947] vmwgfx 0000:00:02.0: [drm] Screen Target display unit initialized
[    6.553525] vmwgfx 0000:00:02.0: [drm] Fifo max 0x00200000 min 0x00001000 cap 0x00000355
[    6.553977] vmwgfx 0000:00:02.0: [drm] Using command buffers with DMA pool.
[    6.553983] vmwgfx 0000:00:02.0: [drm] Available shader model: Legacy.
[    6.554868] [drm] Initialized vmwgfx 2.21.0 for 0000:00:02.0 on minor 0
[    6.555825] fbcon: vmwgfxdrmfb (fb0) is primary device
[    6.555878] Console: switching to colour frame buffer device 160x50
[    6.555883] vmwgfx 0000:00:02.0: [drm] fb0: vmwgfxdrmfb frame buffer device
[    7.102822] snd_intel8x0 0000:00:05.0: allow list rate for 1028:0177 is 48000
[    7.991516] NET: Registered PF_QIPCRTR protocol family
[    8.580669] e1000: enp0s3 NIC Link is Up 1000 Mbps Full Duplex, Flow Control: RX
[   12.200335] rfkill: input handler disabled
[   30.375291] systemd-journald[235]: File /var/log/journal/f74464dae0f64b65a6b2fd9e00edcb0c/user-1000.journal corrupted or uncleanly shut down, renaming and replacing.
[   30.637068] rfkill: input handler enabled
[   32.696815] rfkill: input handler disabled
[   51.478450] kauditd_printk_skb: 150 callbacks suppressed
[   51.478454] audit: type=1400 audit(1779121509.610:162): apparmor="DENIED" operation="open" class="file" profile="snap.firefox.firefox" name="/etc/vulkan/implicit_layer.d/" pid=2727 comm="glxtest" requested_mask="r" denied_mask="r" fsuid=1000 ouid=0
[   51.482544] audit: type=1400 audit(1779121509.614:163): apparmor="DENIED" operation="open" class="file" profile="snap.firefox.firefox" name="/etc/vulkan/implicit_layer.d/" pid=2727 comm="glxtest" requested_mask="r" denied_mask="r" fsuid=1000 ouid=0
[   51.483218] audit: type=1400 audit(1779121509.614:164): apparmor="DENIED" operation="open" class="file" profile="snap.firefox.firefox" name="/etc/vulkan/icd.d/" pid=2727 comm="glxtest" requested_mask="r" denied_mask="r" fsuid=1000 ouid=0
[   51.686347] audit: type=1400 audit(1779121509.818:165): apparmor="DENIED" operation="open" class="file" profile="snap.firefox.firefox" name="/etc/vulkan/icd.d/" pid=2727 comm="glxtest" requested_mask="r" denied_mask="r" fsuid=1000 ouid=0
[   51.687040] audit: type=1400 audit(1779121509.818:166): apparmor="DENIED" operation="open" class="file" profile="snap.firefox.firefox" name="/etc/vulkan/implicit_layer.d/" pid=2727 comm="glxtest" requested_mask="r" denied_mask="r" fsuid=1000 ouid=0
[   51.689285] audit: type=1400 audit(1779121509.821:167): apparmor="DENIED" operation="open" class="file" profile="snap.firefox.firefox" name="/etc/vulkan/implicit_layer.d/" pid=2727 comm="glxtest" requested_mask="r" denied_mask="r" fsuid=1000 ouid=0
[   51.689427] audit: type=1400 audit(1779121509.821:168): apparmor="DENIED" operation="open" class="file" profile="snap.firefox.firefox" name="/etc/vulkan/icd.d/" pid=2727 comm="glxtest" requested_mask="r" denied_mask="r" fsuid=1000 ouid=0
[   51.690034] audit: type=1400 audit(1779121509.821:169): apparmor="DENIED" operation="open" class="file" profile="snap.firefox.firefox" name="/etc/vulkan/implicit_layer.d/" pid=2727 comm="glxtest" requested_mask="r" denied_mask="r" fsuid=1000 ouid=0
[   51.692394] audit: type=1400 audit(1779121509.824:170): apparmor="DENIED" operation="open" class="file" profile="snap.firefox.firefox" name="/etc/vulkan/implicit_layer.d/" pid=2727 comm="glxtest" requested_mask="r" denied_mask="r" fsuid=1000 ouid=0
[   51.692517] audit: type=1400 audit(1779121509.824:171): apparmor="DENIED" operation="open" class="file" profile="snap.firefox.firefox" name="/etc/vulkan/implicit_layer.d/" pid=2727 comm="glxtest" requested_mask="r" denied_mask="r" fsuid=1000 ouid=0
[   62.858360] kauditd_printk_skb: 8 callbacks suppressed
[   62.858363] audit: type=1400 audit(1779121520.990:180): apparmor="DENIED" operation="open" class="file" profile="snap.firefox.firefox" name="/proc/pressure/memory" pid=2642 comm="MemoryPoller" requested_mask="r" denied_mask="r" fsuid=1000 ouid=0
[   68.305295] audit: type=1400 audit(1779121526.437:181): apparmor="DENIED" operation="open" class="file" profile="snap.firefox.firefox" name="/proc/pressure/memory" pid=2642 comm="MemoryPoller" requested_mask="r" denied_mask="r" fsuid=1000 ouid=0
[   73.466057] audit: type=1400 audit(1779121531.599:182): apparmor="DENIED" operation="open" class="file" profile="snap.firefox.firefox" name="/proc/pressure/memory" pid=2642 comm="MemoryPoller" requested_mask="r" denied_mask="r" fsuid=1000 ouid=0
[   78.466435] audit: type=1400 audit(1779121536.600:183): apparmor="DENIED" operation="open" class="file" profile="snap.firefox.firefox" name="/proc/pressure/memory" pid=2642 comm="MemoryPoller" requested_mask="r" denied_mask="r" fsuid=1000 ouid=0
[   83.772584] audit: type=1400 audit(1779121541.906:184): apparmor="DENIED" operation="open" class="file" profile="snap.firefox.firefox" name="/proc/pressure/memory" pid=2642 comm="MemoryPoller" requested_mask="r" denied_mask="r" fsuid=1000 ouid=0
[   92.623725] audit: type=1400 audit(1779121550.758:185): apparmor="DENIED" operation="open" class="file" profile="snap.firefox.firefox" name="/proc/pressure/memory" pid=2642 comm="MemoryPoller" requested_mask="r" denied_mask="r" fsuid=1000 ouid=0
[   92.852241] audit: type=1400 audit(1779121550.986:186): apparmor="DENIED" operation="open" class="file" profile="snap.firefox.firefox" name="/etc/vulkan/implicit_layer.d/" pid=2642 comm="CanvasRenderer" requested_mask="r" denied_mask="r" fsuid=1000 ouid=0
[   92.852769] audit: type=1400 audit(1779121550.986:187): apparmor="DENIED" operation="open" class="file" profile="snap.firefox.firefox" name="/etc/vulkan/implicit_layer.d/" pid=2642 comm="CanvasRenderer" requested_mask="r" denied_mask="r" fsuid=1000 ouid=0
[   92.852885] audit: type=1400 audit(1779121550.986:188): apparmor="DENIED" operation="open" class="file" profile="snap.firefox.firefox" name="/etc/vulkan/icd.d/" pid=2642 comm="CanvasRenderer" requested_mask="r" denied_mask="r" fsuid=1000 ouid=0
[   92.860998] audit: type=1400 audit(1779121550.994:189): apparmor="DENIED" operation="open" class="file" profile="snap.firefox.firefox" name="/etc/vulkan/icd.d/" pid=2642 comm="CanvasRenderer" requested_mask="r" denied_mask="r" fsuid=1000 ouid=0
[   92.861497] audit: type=1400 audit(1779121550.994:190): apparmor="DENIED" operation="open" class="file" profile="snap.firefox.firefox" name="/etc/vulkan/implicit_layer.d/" pid=2642 comm="CanvasRenderer" requested_mask="r" denied_mask="r" fsuid=1000 ouid=0
[   92.862011] audit: type=1400 audit(1779121550.994:191): apparmor="DENIED" operation="open" class="file" profile="snap.firefox.firefox" name="/etc/vulkan/implicit_layer.d/" pid=2642 comm="CanvasRenderer" requested_mask="r" denied_mask="r" fsuid=1000 ouid=0
[   92.862119] audit: type=1400 audit(1779121550.994:192): apparmor="DENIED" operation="open" class="file" profile="snap.firefox.firefox" name="/etc/vulkan/icd.d/" pid=2642 comm="CanvasRenderer" requested_mask="r" denied_mask="r" fsuid=1000 ouid=0
[   92.862571] audit: type=1400 audit(1779121550.994:193): apparmor="DENIED" operation="open" class="file" profile="snap.firefox.firefox" name="/etc/vulkan/implicit_layer.d/" pid=2642 comm="CanvasRenderer" requested_mask="r" denied_mask="r" fsuid=1000 ouid=0
[   92.862679] audit: type=1400 audit(1779121550.994:194): apparmor="DENIED" operation="open" class="file" profile="snap.firefox.firefox" name="/etc/vulkan/implicit_layer.d/" pid=2642 comm="CanvasRenderer" requested_mask="r" denied_mask="r" fsuid=1000 ouid=0
[   97.635003] kauditd_printk_skb: 8 callbacks suppressed
[   97.635006] audit: type=1400 audit(1779121555.767:203): apparmor="DENIED" operation="open" class="file" profile="snap.firefox.firefox" name="/proc/pressure/memory" pid=2642 comm="MemoryPoller" requested_mask="r" denied_mask="r" fsuid=1000 ouid=0
[  102.635918] audit: type=1400 audit(1779121560.771:204): apparmor="DENIED" operation="open" class="file" profile="snap.firefox.firefox" name="/proc/pressure/memory" pid=2642 comm="MemoryPoller" requested_mask="r" denied_mask="r" fsuid=1000 ouid=0
[  119.363628] audit: type=1400 audit(1779121577.499:205): apparmor="DENIED" operation="open" class="file" profile="snap.firefox.firefox" name="/proc/pressure/memory" pid=2642 comm="MemoryPoller" requested_mask="r" denied_mask="r" fsuid=1000 ouid=0
[  124.407387] audit: type=1400 audit(1779121582.543:206): apparmor="DENIED" operation="open" class="file" profile="snap.firefox.firefox" name="/proc/pressure/memory" pid=2642 comm="MemoryPoller" requested_mask="r" denied_mask="r" fsuid=1000 ouid=0
[  129.457168] audit: type=1400 audit(1779121587.592:207): apparmor="DENIED" operation="open" class="file" profile="snap.firefox.firefox" name="/proc/pressure/memory" pid=2642 comm="MemoryPoller" requested_mask="r" denied_mask="r" fsuid=1000 ouid=0
[  134.458128] audit: type=1400 audit(1779121592.593:208): apparmor="DENIED" operation="open" class="file" profile="snap.firefox.firefox" name="/proc/pressure/memory" pid=2642 comm="MemoryPoller" requested_mask="r" denied_mask="r" fsuid=1000 ouid=0
[  139.464670] audit: type=1400 audit(1779121597.599:209): apparmor="DENIED" operation="open" class="file" profile="snap.firefox.firefox" name="/proc/pressure/memory" pid=2642 comm="MemoryPoller" requested_mask="r" denied_mask="r" fsuid=1000 ouid=0
[  144.533859] audit: type=1400 audit(1779121602.669:210): apparmor="DENIED" operation="open" class="file" profile="snap.firefox.firefox" name="/proc/pressure/memory" pid=2642 comm="MemoryPoller" requested_mask="r" denied_mask="r" fsuid=1000 ouid=0
[  149.630051] audit: type=1400 audit(1779121607.765:211): apparmor="DENIED" operation="open" class="file" profile="snap.firefox.firefox" name="/proc/pressure/memory" pid=2642 comm="MemoryPoller" requested_mask="r" denied_mask="r" fsuid=1000 ouid=0
[  154.646323] audit: type=1400 audit(1779121612.782:212): apparmor="DENIED" operation="open" class="file" profile="snap.firefox.firefox" name="/proc/pressure/memory" pid=2642 comm="MemoryPoller" requested_mask="r" denied_mask="r" fsuid=1000 ouid=0
[  159.697385] audit: type=1400 audit(1779121617.832:213): apparmor="DENIED" operation="open" class="file" profile="snap.firefox.firefox" name="/proc/pressure/memory" pid=2642 comm="MemoryPoller" requested_mask="r" denied_mask="r" fsuid=1000 ouid=0
[  171.136711] audit: type=1400 audit(1779121629.272:214): apparmor="DENIED" operation="open" class="file" profile="snap.firefox.firefox" name="/proc/pressure/memory" pid=2642 comm="MemoryPoller" requested_mask="r" denied_mask="r" fsuid=1000 ouid=0
[  176.138285] audit: type=1400 audit(1779121634.274:215): apparmor="DENIED" operation="open" class="file" profile="snap.firefox.firefox" name="/proc/pressure/memory" pid=2642 comm="MemoryPoller" requested_mask="r" denied_mask="r" fsuid=1000 ouid=0
[  181.140646] audit: type=1400 audit(1779121639.276:216): apparmor="DENIED" operation="open" class="file" profile="snap.firefox.firefox" name="/proc/pressure/memory" pid=2642 comm="MemoryPoller" requested_mask="r" denied_mask="r" fsuid=1000 ouid=0
[  186.184154] audit: type=1400 audit(1779121644.320:217): apparmor="DENIED" operation="open" class="file" profile="snap.firefox.firefox" name="/proc/pressure/memory" pid=2642 comm="MemoryPoller" requested_mask="r" denied_mask="r" fsuid=1000 ouid=0
[  191.185526] audit: type=1400 audit(1779121649.321:218): apparmor="DENIED" operation="open" class="file" profile="snap.firefox.firefox" name="/proc/pressure/memory" pid=2642 comm="MemoryPoller" requested_mask="r" denied_mask="r" fsuid=1000 ouid=0
[  196.453368] audit: type=1400 audit(1779121654.589:219): apparmor="DENIED" operation="open" class="file" profile="snap.firefox.firefox" name="/proc/pressure/memory" pid=2642 comm="MemoryPoller" requested_mask="r" denied_mask="r" fsuid=1000 ouid=0
[  201.591558] audit: type=1400 audit(1779121659.727:220): apparmor="DENIED" operation="open" class="file" profile="snap.firefox.firefox" name="/proc/pressure/memory" pid=2642 comm="MemoryPoller" requested_mask="r" denied_mask="r" fsuid=1000 ouid=0
[  206.641028] audit: type=1400 audit(1779121664.777:221): apparmor="DENIED" operation="open" class="file" profile="snap.firefox.firefox" name="/proc/pressure/memory" pid=2642 comm="MemoryPoller" requested_mask="r" denied_mask="r" fsuid=1000 ouid=0
[  211.727941] audit: type=1400 audit(1779121669.864:222): apparmor="DENIED" operation="open" class="file" profile="snap.firefox.firefox" name="/proc/pressure/memory" pid=2642 comm="MemoryPoller" requested_mask="r" denied_mask="r" fsuid=1000 ouid=0
[  216.789785] audit: type=1400 audit(1779121674.926:223): apparmor="DENIED" operation="open" class="file" profile="snap.firefox.firefox" name="/proc/pressure/memory" pid=2642 comm="MemoryPoller" requested_mask="r" denied_mask="r" fsuid=1000 ouid=0
[  221.792299] audit: type=1400 audit(1779121679.928:224): apparmor="DENIED" operation="open" class="file" profile="snap.firefox.firefox" name="/proc/pressure/memory" pid=2642 comm="MemoryPoller" requested_mask="r" denied_mask="r" fsuid=1000 ouid=0
[  226.807364] audit: type=1400 audit(1779121684.943:225): apparmor="DENIED" operation="open" class="file" profile="snap.firefox.firefox" name="/proc/pressure/memory" pid=2642 comm="MemoryPoller" requested_mask="r" denied_mask="r" fsuid=1000 ouid=0
[  231.810233] audit: type=1400 audit(1779121689.946:226): apparmor="DENIED" operation="open" class="file" profile="snap.firefox.firefox" name="/proc/pressure/memory" pid=2642 comm="MemoryPoller" requested_mask="r" denied_mask="r" fsuid=1000 ouid=0
[  237.009121] audit: type=1400 audit(1779121695.145:227): apparmor="DENIED" operation="open" class="file" profile="snap.firefox.firefox" name="/proc/pressure/memory" pid=2642 comm="MemoryPoller" requested_mask="r" denied_mask="r" fsuid=1000 ouid=0
[  256.188309] audit: type=1400 audit(1779121714.324:228): apparmor="DENIED" operation="open" class="file" profile="snap.firefox.firefox" name="/proc/pressure/memory" pid=2642 comm="MemoryPoller" requested_mask="r" denied_mask="r" fsuid=1000 ouid=0
[  267.303207] audit: type=1400 audit(1779121725.438:229): apparmor="DENIED" operation="open" class="file" profile="snap.firefox.firefox" name="/proc/pressure/memory" pid=2642 comm="MemoryPoller" requested_mask="r" denied_mask="r" fsuid=1000 ouid=0
[  290.247385] audit: type=1400 audit(1779121748.384:230): apparmor="DENIED" operation="open" class="file" profile="snap.firefox.firefox" name="/proc/pressure/memory" pid=2642 comm="MemoryPoller" requested_mask="r" denied_mask="r" fsuid=1000 ouid=0
[  295.838249] audit: type=1400 audit(1779121753.975:231): apparmor="DENIED" operation="open" class="file" profile="snap.firefox.firefox" name="/proc/pressure/memory" pid=2642 comm="MemoryPoller" requested_mask="r" denied_mask="r" fsuid=1000 ouid=0
[  300.839154] audit: type=1400 audit(1779121758.976:232): apparmor="DENIED" operation="open" class="file" profile="snap.firefox.firefox" name="/proc/pressure/memory" pid=2642 comm="MemoryPoller" requested_mask="r" denied_mask="r" fsuid=1000 ouid=0
[  305.843865] audit: type=1400 audit(1779121763.981:233): apparmor="DENIED" operation="open" class="file" profile="snap.firefox.firefox" name="/proc/pressure/memory" pid=2642 comm="MemoryPoller" requested_mask="r" denied_mask="r" fsuid=1000 ouid=0
[  310.856333] audit: type=1400 audit(1779121768.992:234): apparmor="DENIED" operation="open" class="file" profile="snap.firefox.firefox" name="/proc/pressure/memory" pid=2642 comm="MemoryPoller" requested_mask="r" denied_mask="r" fsuid=1000 ouid=0
[  315.882177] audit: type=1400 audit(1779121774.018:235): apparmor="DENIED" operation="open" class="file" profile="snap.firefox.firefox" name="/proc/pressure/memory" pid=2642 comm="MemoryPoller" requested_mask="r" denied_mask="r" fsuid=1000 ouid=0
[  320.884828] audit: type=1400 audit(1779121779.021:236): apparmor="DENIED" operation="open" class="file" profile="snap.firefox.firefox" name="/proc/pressure/memory" pid=2642 comm="MemoryPoller" requested_mask="r" denied_mask="r" fsuid=1000 ouid=0
[  325.525000] set_capacity_and_notify: 7 callbacks suppressed
[  325.525003] loop16: detected capacity change from 0 to 100888
[  325.904013] audit: type=1400 audit(1779121784.040:237): apparmor="DENIED" operation="open" class="file" profile="snap.firefox.firefox" name="/proc/pressure/memory" pid=2642 comm="MemoryPoller" requested_mask="r" denied_mask="r" fsuid=1000 ouid=0
[  326.113548] audit: type=1400 audit(1779121784.249:238): apparmor="STATUS" operation="profile_load" profile="unconfined" name="/snap/snapd/26865/usr/lib/snapd/snap-confine" pid=4280 comm="apparmor_parser"
[  326.445574] audit: type=1400 audit(1779121784.580:239): apparmor="STATUS" operation="profile_replace" info="same as current profile, skipping" profile="unconfined" name="snap-update-ns.firefox" pid=4282 comm="apparmor_parser"
[  326.653871] audit: type=1400 audit(1779121784.790:240): apparmor="STATUS" operation="profile_replace" info="same as current profile, skipping" profile="unconfined" name="snap-update-ns.firmware-updater" pid=4283 comm="apparmor_parser"
[  326.844052] audit: type=1400 audit(1779121784.979:241): apparmor="STATUS" operation="profile_replace" info="same as current profile, skipping" profile="unconfined" name="snap-update-ns.snap-store" pid=4284 comm="apparmor_parser"
[  327.091201] audit: type=1400 audit(1779121785.226:242): apparmor="STATUS" operation="profile_replace" info="same as current profile, skipping" profile="unconfined" name="snap-update-ns.snapd-desktop-integration" pid=4285 comm="apparmor_parser"
[  327.158552] audit: type=1400 audit(1779121785.293:243): apparmor="STATUS" operation="profile_replace" info="same as current profile, skipping" profile="unconfined" name="snap.firefox.firefox" pid=4287 comm="apparmor_parser"
[  327.173524] audit: type=1400 audit(1779121785.308:244): apparmor="STATUS" operation="profile_replace" info="same as current profile, skipping" profile="unconfined" name="snap.firefox.geckodriver" pid=4288 comm="apparmor_parser"
[  327.219090] audit: type=1400 audit(1779121785.355:245): apparmor="STATUS" operation="profile_replace" info="same as current profile, skipping" profile="unconfined" name="snap.firefox.hook.configure" pid=4289 comm="apparmor_parser"
[  327.224505] audit: type=1400 audit(1779121785.361:246): apparmor="STATUS" operation="profile_replace" info="same as current profile, skipping" profile="unconfined" name="snap.firefox.hook.disconnect-plug-host-hunspell" pid=4290 comm="apparmor_parser"
[  331.272595] kauditd_printk_skb: 11 callbacks suppressed
[  331.272599] audit: type=1400 audit(1779121789.409:258): apparmor="DENIED" operation="open" class="file" profile="snap.firefox.firefox" name="/proc/pressure/memory" pid=2642 comm="MemoryPoller" requested_mask="r" denied_mask="r" fsuid=1000 ouid=0
[  331.482835] loop17: detected capacity change from 0 to 8
[  333.580283] audit: type=1400 audit(1779121791.717:259): apparmor="STATUS" operation="profile_replace" profile="unconfined" name="/snap/snapd/26865/usr/lib/snapd/snap-confine" pid=4682 comm="apparmor_parser"
[  333.884559] audit: type=1400 audit(1779121792.021:260): apparmor="STATUS" operation="profile_replace" profile="unconfined" name="snap-update-ns.snap-store" pid=4684 comm="apparmor_parser"
[  334.028406] audit: type=1400 audit(1779121792.165:261): apparmor="STATUS" operation="profile_replace" profile="unconfined" name="snap.snap-store.hook.configure" pid=4685 comm="apparmor_parser"
[  334.317338] audit: type=1400 audit(1779121792.454:262): apparmor="STATUS" operation="profile_replace" profile="unconfined" name="snap.snap-store.show-updates" pid=4686 comm="apparmor_parser"
[  334.591471] audit: type=1400 audit(1779121792.728:263): apparmor="STATUS" operation="profile_replace" profile="unconfined" name="snap.snap-store.snap-store" pid=4687 comm="apparmor_parser"
[  334.813254] audit: type=1400 audit(1779121792.949:264): apparmor="STATUS" operation="profile_replace" profile="unconfined" name="snap-update-ns.firefox" pid=4688 comm="apparmor_parser"
[  335.324836] audit: type=1400 audit(1779121793.462:265): apparmor="STATUS" operation="profile_replace" profile="unconfined" name="snap.firefox.firefox" pid=4689 comm="apparmor_parser"
[  335.839562] audit: type=1400 audit(1779121793.976:266): apparmor="STATUS" operation="profile_replace" profile="unconfined" name="snap.firefox.geckodriver" pid=4690 comm="apparmor_parser"
[  335.963404] audit: type=1400 audit(1779121794.100:267): apparmor="STATUS" operation="profile_replace" profile="unconfined" name="snap.firefox.hook.configure" pid=4691 comm="apparmor_parser"
[  336.507526] kauditd_printk_skb: 3 callbacks suppressed
[  336.507530] audit: type=1400 audit(1779121794.644:271): apparmor="STATUS" operation="profile_replace" profile="unconfined" name="snap-update-ns.snapd-desktop-integration" pid=4695 comm="apparmor_parser"
[  336.648586] audit: type=1400 audit(1779121794.785:272): apparmor="STATUS" operation="profile_replace" profile="unconfined" name="snap.snapd-desktop-integration.hook.configure" pid=4696 comm="apparmor_parser"
[  336.943049] audit: type=1400 audit(1779121795.078:273): apparmor="STATUS" operation="profile_replace" profile="unconfined" name="snap.snapd-desktop-integration.snapd-desktop-integration" pid=4697 comm="apparmor_parser"
[  336.953459] audit: type=1400 audit(1779121795.091:274): apparmor="STATUS" operation="profile_replace" profile="unconfined" name="snap-update-ns.mesa-2404" pid=4698 comm="apparmor_parser"
[  337.026260] audit: type=1400 audit(1779121795.164:275): apparmor="STATUS" operation="profile_replace" profile="unconfined" name="snap.mesa-2404.component-monitor" pid=4699 comm="apparmor_parser"
[  337.095275] audit: type=1400 audit(1779121795.232:276): apparmor="STATUS" operation="profile_replace" profile="unconfined" name="snap.mesa-2404.hook.connect-plug-kernel-gpu-2404" pid=4700 comm="apparmor_parser"
[  337.174271] audit: type=1400 audit(1779121795.311:277): apparmor="STATUS" operation="profile_replace" profile="unconfined" name="snap.mesa-2404.hook.disconnect-plug-kernel-gpu-2404" pid=4701 comm="apparmor_parser"
[  337.247457] audit: type=1400 audit(1779121795.385:278): apparmor="STATUS" operation="profile_replace" profile="unconfined" name="snap.mesa-2404.hook.install" pid=4703 comm="apparmor_parser"
[  337.320336] audit: type=1400 audit(1779121795.456:279): apparmor="STATUS" operation="profile_replace" profile="unconfined" name="snap.mesa-2404.hook.post-refresh" pid=4704 comm="apparmor_parser"
[  337.544167] audit: type=1400 audit(1779121795.682:280): apparmor="STATUS" operation="profile_replace" profile="unconfined" name="snap-update-ns.firmware-updater" pid=4706 comm="apparmor_parser"
[  748.388408] mimodulo: loading out-of-tree module taints kernel.
[  748.388413] mimodulo: module verification failed: signature and/or required key missing - tainting kernel
[  748.388785] Modulo cargado en el kernel.
[  826.135791] Modulo descargado del kernel.
```

Nuevamente se observan las mismas advertencias que arroja el Kernel de Linux para el caso de la carga del módulo, sin embargo la última línea demuestra la correcta descarga del módulo del Kernel.

Se propone además, para confirmar que este módulo ya no se encuentre en la memorria, ejecutar los siguientes comandos:

```bash
lsmod | grep mod
cat /proc/modules | grep mod
```

