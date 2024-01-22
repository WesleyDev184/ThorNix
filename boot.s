.global _start
.equ STACK_SIZE, 4096 # tamanho da pilha
# mhartid e o registrador que contem o id da cpu

_start:
  csrr t0, mhartid # copia o id da cpu para o registrador t0
  bnez t0, park # se o id da cpu for diferente de 0, vai para park
  la sp, stack_end # carrega o endereco de stack_end para o registrador sp
  j entry # salta para a funcao entry

park:
  wfi # espera por uma interrupcao externa
  j park # volta para o loop infinito

.skip STACK_SIZE # pula STACK_SIZE bytes

stack_end:
