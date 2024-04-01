// Codigo para tratamento de exceções

#include "../../headers/proc.h"
#include "../../headers/riscv.h"
#include "../../headers/defs.h"

/**
 * Handles exceptions and interrupts in the system.
 *
 * @param tval The value associated with the trap.
 * @param mcause The cause of the trap.
 * @param tf Pointer to the trap frame.
 */
void mtrap(uint64 tval, uint64 mcause, trap_frame *tf)
{
  uint16 cause;
  if ((long)mcause > 0)
  {
    // Exceção síncrona
    if (mcause == 2)
    {
      printf("<traop.c - mtrap> [CPU#:%d] Instrução ilegal no endereço %p\n", tf->hartid, tf->epc);
      tf->epc += 4;
    }
    if (mcause == 9)
    {
      printf("<trap.c> Chamada de sistema -- \n");
      if (tf->a7 == 1)
      {
        printf("\t Primeira chamada de sistema ...\n");
      }
      tf->epc += 4;
    }
    else
    {
      // Nenhuma causa conhecida ou tratada anteriormente
      printf("<trap.c - mtrap> [CPU#:%d] Exceção de causa desconhecida %p\n", tf->hartid, tf->epc);
      tf->epc += 4;
    }
  }
  else
  {
    cause = mcause & 0xfff;
    // Exceção assincrona(interrupção)
    panic("<trap.c - mtrap> tratando uma interrupção assincrona ....\n");
  }
}