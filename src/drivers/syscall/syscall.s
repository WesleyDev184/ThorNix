.global ola
.global write

ola:
  li a7, 1 # id da chamada ola
  ecall
  ret

write:
  li a7, 2 # id da chamada white
  li a0, 1
  li a1, 2
  loop:
    add a1, a1, a1
    sub a0, a0, 1
    bnez a0, loop
  ecall
  ret
