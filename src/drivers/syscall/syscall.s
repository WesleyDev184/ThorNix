.global ola
.global write

ola:
  li a7, 1 # id da chamada ola
  ecall
  ret

write:
  # a0 = string
  # a1 = tamanho
  li a7, 2 # id da chamada white
  ecall
  ret
