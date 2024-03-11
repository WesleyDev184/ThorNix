#include "../../headers/types.h"
#include "../../headers/defs.h"
#include "../../headers/memlayout.h"

extern uint64 stack_start[]; // a variavel ja foi criada em outro
extern uint64 stack_end[];
extern char text_end[];

long total_pages; // total de paginas do heap
long alloc_start; // inicio da regiao alocavel do heap

#define HEAP_START stack_end
#define HEAP_END (uint8 *)(KERNEL_START + MEMORY_LENGTH)
#define TEXT_END (uint8 *)text_end
#define HEAP_SIZE ((uint64)HEAP_END - (uint64)HEAP_START)
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
        *desc = *desc | FREEPG;
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

// page_round_up(4095) = 4096
// page_round_up(5000) = 8192
// retorna o endereco da pagina seguinte
uint64 page_round_up(uint64 addr)
{
    if (addr % PAGE_SIZE == 0)
    {
        return addr;
    }

    return addr - (addr % PAGE_SIZE) + PAGE_SIZE;
}

// page_round_down(4095) = 0
// Aredonda o endereco para a pagina anterior
uint64 page_round_down(uint64 addr)
{
    return addr - (addr % PAGE_SIZE);
}

void pages_init()
{
    // Inicializa as paginas do heap
    uint8 *ptr = (uint8 *)HEAP_START;
    total_pages = HEAP_SIZE / PAGE_SIZE;
    int reserved_pages = total_pages / PAGE_SIZE;

    if (total_pages % PAGE_SIZE)
    {
        reserved_pages++;
    }

    // Paginas que podem ser alocadas
    total_pages -= reserved_pages;

    for (int i = 0; i < total_pages; i++)
    {
        ptr[i] = FREEPG;
    }
    printf("Paginas reservadas aos descritores: %d\n", reserved_pages);
    printf("Paginas alocaveis e livres: %d\n", total_pages);

    alloc_start = page_round_up((uint64)HEAP_START + reserved_pages * PAGE_SIZE);
}

void *kalloc(int pages)
{
    // Aloca paginas
    uint8 *ptr;
    uint8 *fp_desc = 0; // descritor de pagina livre
    int count = 0;

    if (pages <= 0)
    {
        return 0;
    }

    for (int i = 0; i < total_pages; i++)
    {
        ptr = (uint8 *)HEAP_START + i;

        if (free_page(*ptr))
        {
            if (count == 0)
            {
                fp_desc = ptr;
            }
            count++;
        }
        else
        {
            count = 0;
            fp_desc = 0;
        }

        // se encontrou paginas suficientes
        if (count == pages)
        {
            break;
        }
    }

    // se nao encontrou paginas suficientes
    if (count < pages)
    {
        return 0;
    }

    // marca as paginas como alocadas
    for (int i = 0; i < pages; i++)
    {
        set_free_page_flag(fp_desc + i, !FREEPG);
        set_last_page_flag(fp_desc + i, !LASTPG);
    }

    // se a ultima pagina do bloco foi alocada
    set_last_page_flag(fp_desc + pages - 1, LASTPG);

    int desc_pos = (uint64)fp_desc - (uint64)HEAP_START;

    return (void *)alloc_start + desc_pos * PAGE_SIZE;
}

void kfree(void *ptr)
{
    // libera paginas
    uint8 *desc = (uint8 *)HEAP_START + ((uint64)ptr - alloc_start) / PAGE_SIZE;

    while (!last_page(*desc))
    {
        set_free_page_flag(desc, FREEPG);
        desc++;
    }

    set_free_page_flag(desc, FREEPG);
}

void memory_init()
{
    printf("Iniciando memoria ...\n");
    pages_init();

    // printf("Descritores de paginas inicializadas\n");
    // printf("layout de memoria inicializado\n");
    // printf("inicio do codigo:\t %p\n", KERNEL_START);
    // printf("fim do codigo:\t %p\n", text_end);
    // printf("inicio do heap:\t %p\n", HEAP_START);
    // printf("fim do heap:\t %p\n", HEAP_END);
    // printf("inicio da Pilha:\t %p\n", stack_start);
    // printf("Fim da pilha:\t %p\n", stack_end);
    // printf("Inicio dos dados:\t %p\n", text_end);
    // printf("fim dos dados:\t %p\n", HEAP_START);
    printf("Regiao alocavel do heap %p\n", (uint8 *)alloc_start);

    char *p1 = kalloc(1);
    char *p2 = kalloc(1);
    char *p3 = kalloc(1);
    printf("p1: %p\n", p1);
    printf("p2: %p\n", p2);
    printf("p3: %p\n", p3);

    *p1 = 'O';
    *(p1 + 1) = 'l';
    p1[2] = 'a';
    p1[3] = '\0'; // termina a string
    printf("conteudo p1: %s\n", p1);

    p2 = "Ola";
    printf("conteudo p2: %s\n", p2);

    strcopy(p3, "Ola");
    printf("conteudo p3: %s\n", p3);

    printf("endereço p1 antes de desalocar %p\n", p1);
    kfree(p1);

    printf("nova alocacao\n");
    char *p4 = kalloc(1);
    printf("endereço p4 %p\n", p4);
}
