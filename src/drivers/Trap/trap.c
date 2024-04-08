// Codigo para tratamento de exceções

#include "../../headers/proc.h"
#include "../../headers/riscv.h"
#include "../../headers/defs.h"
#include "../../headers/memlayout.h"

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
  uint64 *mtimecmp = (uint64 *)CLINT_MTIMECMP(0);
  uint64 *mtime = (uint64 *)CLINT_MTIME;

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

      if (tf->a7 == 2)
      {
        for (int i = 0; i < tf->a1; i++)
        {
          uart_putc(((char *)tf->a0)[i]);
        }
        printf("\n");
      }

      // tratamento do syscall sleep (a0 = time in seconds)
      if (tf->a7 == 3)
      {
        printf("\t Sleeping...\n");
        int sec = tf->a0;
        int start = *mtime;
        int end = start + sec * 10000000;
        while (*mtime < end)
          ;
        tf->a0 = (end - start) / 10000000;
      }

      // tratamento do syscall snakeGame
      if (tf->a7 == 4)
      {
        printf("\t Chamando o jogo da cobrinha...\n");
        tf->a0 = snakeGameMain();
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
    switch (cause)
    {
    case 7:
      // printf("<trap.c - \u23F0 > [CPU#:%d] Interrupção de temporizador\n", tf->hartid);
      *mtimecmp = *(uint64 *)CLINT_MTIME + 10000000;
      break;

    default:
      panic("<trap.c - mtrap> Exceção de causa desconhecida\n");
      break;
    }
  }
}