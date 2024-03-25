// Codigo para tratamento de exceções
#include "../../headers/proc.h"
#include "../../headers/riscv.h"
#include "../../headers/defs.h"

void mtrap(uint64 tval, uint64 cause, trap_frame *tf)
{
  printf("<traop.c - mtrap> tratando uam exceção ....\n");
  tf->epc += 4;
}