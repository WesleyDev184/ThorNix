#include "../../headers/types.h"
#include "../../headers/memlayout.h"

// Habilita interrupção de número irq. Ex.: UART é a interrupção 10
//  Cada interrupção é 1 bit da word de 32 bits
void plic_enable(int irq)
{
    uint32 *enables = (uint32 *)PLIC_ENABLE;
    *enables = *enables | (1 << irq);
}

uint32
plic_get_enable()
{
    return *(uint32 *)PLIC_ENABLE;
}

// Define prioridade para interrupção
//  O 'prio & 7' garante que a maior prioridade seja 7
// Cada dispositivo ocupa 4 bytes
void plic_priority(uint32 irq, uint8 prio)
{
    *(uint32 *)(PLIC_PRIORITY + irq * 4) = prio & 7;
}

uint32
plic_get_priority(uint32 irq)
{
    return *((uint32 *)(PLIC_PRIORITY) + irq);
}
// Define limiar para as interrupções
void plic_threshold(uint8 thresh)
{
    *(uint32 *)PLIC_THRESHOLD = thresh & 7;
}

uint32
plic_get_threshold()
{
    return *(uint32 *)PLIC_THRESHOLD;
}
// Obtém o número da interrupção que gerou o evento
uint32
plic_claim()
{
    return *(uint32 *)PLIC_CLAIM;
}
// Interrupção foi atendida pelo kernel
void plic_complete(uint32 irq)
{
    *(uint32 *)PLIC_CLAIM = irq;
}

void plic_init()
{
    plic_threshold(0);    // Todas as interrupções são atendidas
    plic_enable(10);      // Habilita interrupção UART
    plic_priority(10, 1); // Prioridade 1 para UART
}