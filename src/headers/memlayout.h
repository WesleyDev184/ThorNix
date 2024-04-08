// MMIO mappings
#define UART 0x10000000
#define KERNEL_START 0x80000000L
#define MEMORY_LENGTH 128 * 1024 * 1024
#define PAGE_SIZE 4096

// CLINT
#define CLINT 0x2000000
#define CLINT_MTIME (CLINT + 0xbff8)
#define CLINT_MTIMECMP(hartid) (CLINT + 0x4000 + 8 * (hartid))

// PLIC
#define PLIC 0x0c000000L
#define PLIC_PRIORITY (PLIC + 0x0)

// #define PLIC_PENDING (PLIC + 0x1000)
#define PLIC_ENABLE (PLIC + 0x2000)
#define PLIC_THRESHOLD (PLIC + 0x200000) // THRESHOLD
#define PLIC_CLAIM (PLIC + 0x200004)

// IRQs Globais obtidos do deviceTree da VM virt
#define UART_IRQ 10