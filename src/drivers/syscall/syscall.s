.global ola
.global write
.global sleep
.global snakeGame

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

sleep:
  # a0 = tempo
  li a7, 3 # id da chamada sleep
  ecall
  ret

snakeGame:
  li a7, 4 # id da chamada snakeGame
  ecall
  ret
