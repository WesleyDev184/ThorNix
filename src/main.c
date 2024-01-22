#define uart_base 0x10000000

static void putc(char c){
    volatile char *reg = (char *) uart_base;
    *reg = c;
}

void puts(char *s){
    while(*s){
        putc(*s++);
    }
}

void entry(){
   puts("Olá mundo! Disse ThorNix\n");  
}