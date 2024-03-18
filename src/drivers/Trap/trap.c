// Codigo para tratamento de exceções
#include "../../headers/proc.h"
#include "../../headers/riscv.h"

void mtrap(uint64 tval, uint64 cause, trap_frame_t *tf)
{
  tf->epc = tf->epc + 4;
}