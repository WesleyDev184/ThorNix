#include "headers/defs.h"
#include "headers/console.h"
#include "headers/types.h"
#include "headers/riscv.h"
#include "headers/memlayout.h"

extern void mvector(void);

int main()
{
    // execulta o main no modo supervisor
    int c;
    int progress = 0;
    int i;
    puts(CLEAR_SCREEN CURSOR_UP_LEFT); /* Clear screen and move cursor to 1,1 */
    welcomeScreen();

    for (;;)
    {
        c = uart_getc();
        if (c == -1)
            continue;

        switch (c)
        {
        case 'G':
            i = snakeGame();
            printf("Score: %d\n", i);
            break;

        case 'E':
            // Força uma exceção
            r_mstatus(); // Tenta ler o registrador no modo Supervisor
            break;
        case 'S':
            i = sleep(3);
            printf("Sleep retornou %d\n", i);
            break;
        case 'O':
            // system call Ola
            ola();
            break;
        case 'W':
            write("Deixei toda esperança, ó vós que entrais!\n", 12);
            break;
        case '\r':           /* Enter - 13 */
            uart_putc('\r'); /* Carriage return */
            uart_putc('\n'); /* New line */
            break;

        case 127:            /* Backspace - '\b' */
            uart_putc('\b'); /* move the cursor to the left */
            uart_putc(' ');  /* delete the last character */
            uart_putc('\b'); /* move the cursor to the left again */
            break;

        case 110: /* 'n' */
            progress++;
            displayProgressBar(progress);
            break;

        default:
            uart_putc(c);
        }
    }
}

// ponto de entrada do kernel depois do boot
void entry()
{
    memory_init();

    // CSR mtvec <- "mvector"
    // quando uma exceção ocorrer, o processador irá pular para o endereço de "mvector"
    w_mtvec((uint64)mvector);

    // Estamos no modo Maquina(M), um modo mais privilegiado
    // Muda para o modo supervisor(U), um modo menos privilegiado
    uint64 x = r_mstatus();
    // Zera os bits de MPP
    x = x & ~MSTATUS_MPP_MASK;
    // Seta o bit de MPP para 1
    x = x | MSTATUS_MPP_S;
    w_mstatus(x);

    // CSR mepc <- "main"
    // mepc é um registrador que armazena o endereço da próxima instrução a ser executada
    w_mepc((uint64)main);

    /*
        Habilita as interrupções
        mstatus.MPIE <- 1
    */

    x = x | (1 << 7); // campo Mpie em 1
    w_mstatus(x);

    // Habilita as interrupções do timer
    x = r_mie();
    x = x | (1 << 7);  // Habilita o temporizador
    x = x | (1 << 11); // Habilita a interrupção externa
    w_mie(x);

    // configura o temporizador
    // intervalo de 1 segundo
    uint64 *mtimecmp = (uint64 *)CLINT_MTIMECMP(0); // Processador 0
    uint64 *mtime = (uint64 *)CLINT_MTIME;
    *mtimecmp = *mtime + 10000000;

    uart_init();
    printf("Uart initialized ...\n");
    plic_init();
    printf("Plic initialized ...\n");

    asm volatile("mret"); // Salta para o endereço armazenado em mepc
}