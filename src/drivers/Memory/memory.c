#include "../../headers/types.h"
#include "../../headers/defs.h"
#include "../../headers/memlayout.h"

extern uint64 *stack_start; // a variavel ja foi criada em outro
extern uint64 *stack_end;

extern char text_end[];
long total_pages; // total de paginas do heap
long alloc_start; // inicio da regiao alocavel do heap

#define HEAP_START stack_end
#define HEAP_END (uint8 *)(KERNEL_START + MEMORY_LENGTH)
#define TEXT_END (uint8 *)text_end
#define HEAP_SIZE (uint64 *)HEAP_END - (uint64 *)HEAP_START
#define FREEPG 0X1 // PAGINA LIVRE
#define LASTPG 0X2 // ULTIMA PAGINA DO BLOCO ALOCADO?

int free_page(uint8 desc)
{
    if (desc & FREEPG)
        return 1;
    return 0;
}
int last_page(uint8 desc)
{
    if (desc &= LASTPG)
        return 1;
    return 0;
}

void set_free_page_flag(uint8 *desc, uint8 flag)
{
    // SETA A FLAG DE PAGINA LIVRE PARA 1
    if (flag)
    {
        *desc | FREEPG;
    }
    else
    {
        *desc = *desc & ~FREEPG;
    }
}

void set_last_page_flag(uint8 *desc, uint8 flag)
{
    // seta a flag de ultima pagina para 1
    if (flag)
    {
        *desc = *desc | LASTPG;
    }
    else
    {
        *desc = *desc & ~LASTPG;
    }
}