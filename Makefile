BOOT_FILE = boot.s
MAIN_FILE = src/main.c
KEREL_FILE = kernel

RISCV_BASE = riscv64-linux-gnu
COMPILER = $(RISCV_BASE)-gcc
LINKER = $(RISCV_BASE)-ld
OBJCOPY = $(RISCV_BASE)-objcopy
OBJDUMP = $(RISCV_BASE)-objdump

CFLAGS = -ffreestanding -march=rv64g -mabi=lp64 -Wall -c -g -O0
LDFLAGS = -nostdlib -Ttext=0x00000000

# Output folder
OUTPUT_FOLDER = output

kernel: boot.o main.o
	@$(LINKER) $(LDFLAGS) $(OUTPUT_FOLDER)/boot.o $(OUTPUT_FOLDER)/main.o -o $(OUTPUT_FOLDER)/$(KEREL_FILE)

boot.o: $(BOOT_FILE)
	@$(COMPILER) $(CFLAGS) $(BOOT_FILE) -o $(OUTPUT_FOLDER)/boot.o

main.o: $(MAIN_FILE)
	@$(COMPILER) $(CFLAGS) $(MAIN_FILE) -o $(OUTPUT_FOLDER)/main.o

clean:
	rm -f $(OUTPUT_FOLDER)/*.o && clear
