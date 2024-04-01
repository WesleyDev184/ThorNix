#define UART 0x10000000
#define KERNEL_START 0x80000000L
#define MEMORY_LENGTH 128 * 1024 * 1024
#define PAGE_SIZE 4096

// clint
#define CLINT 0x2000000
#define CLINT_MTIME (CLINT + 0xbff8)
#define CLINT_MTIMECMP(hartid) (CLINT + 0x4000 + 8 * (hartid))