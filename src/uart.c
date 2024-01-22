#include "headers/memlayout.h"
#include "headers/types.h"

#define RBR 0 // Receiver buffer register
#define THR 0//REGISTRADOR DE TRANSMISSAO DE DADOS
#define IER 1 //REG PARA INTERRUPÇAÕ
#define FCR 2 // CONTROLE DE FIFO
#define LCR 3 //LINE CONTROL REGISTER
#define LSR 5// LINE STATUS REGISTER

char
read_reg(uint8 reg){
   char c;
   volatile char * base = (char *) UART;
   c=*(base + reg);
   return c;
}

void
write_reg(uint8 reg,char c){
    volatile char * base = (char *) UART;
    *(base + reg) =c;
}
void
uart_init(){
    //habilita o FIFO
    write_reg(FCR,1);
    //DADOS DE 8 BITS
    write_reg(LCR,3);
    //HABILITA INTERRUPÇÃO
    write_reg(IER,1);
}
int
uart_getc(){
    char c;
    if((read_reg(LSR)&1)==0 ){
        return -1;
    }
    c = read_reg(RBR);
    return c;
}
void uart_putc(char c){
    while((read_reg(LSR) & (1<<5))==0);
    write_reg(THR,c);
}