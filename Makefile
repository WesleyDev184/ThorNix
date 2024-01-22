KERNEL_FILE = kernel
OUTPUT_FOLDER = output
RISCV_BASE = riscv64-linux-gnu
COMPILER = $(RISCV_BASE)-gcc
LINKER = $(RISCV_BASE)-ld
QEMU = qemu-system-riscv64

CFLAGS = -ffreestanding -march=rv64g -mabi=lp64 -Wall -c -g -O0
LDFLAGS = -nostdlib -Ttext=0x80000000
QEMUFLAGS = -append 'console=ttyS0' -nographic -serial mon:stdio -smp 4 -machine virt -bios none

OBJ = \
 $(OUTPUT_FOLDER)/boot.o \
 $(OUTPUT_FOLDER)/main.o \
 $(OUTPUT_FOLDER)/uart.o

.PHONY: clean 

clean:
	rm -f $(OUTPUT_FOLDER)/* 
	clear

run: $(OUTPUT_FOLDER)/$(KERNEL_FILE)
	@$(QEMU) $(QEMUFLAGS) -kernel $<

$(OUTPUT_FOLDER)/%.o: %.s | $(OUTPUT_FOLDER)
	@$(COMPILER) $(CFLAGS) $< -o $@

$(OUTPUT_FOLDER)/%.o: src/%.c | $(OUTPUT_FOLDER)
	@$(COMPILER) $(CFLAGS) $< -o $@

$(OUTPUT_FOLDER)/$(KERNEL_FILE): $(OBJ) 
	@$(LINKER) $(LDFLAGS) -o $@ $^

$(OUTPUT_FOLDER):
	mkdir -p $@
