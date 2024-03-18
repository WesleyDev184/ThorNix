.option norvc
.global mvector
.section .text
.balign 4
 
# Salva/restaura todos os registradores
# Onde?  No Trap frame, cujo endereço
# se encontra guardado no registrador `mscratch`
mvector:
    # t6 <- mscratch
    # mscratch <- t6
    # (de forma atômica)
    csrrw   t6, mscratch, t6
    # t6 tem agora o endereço do trap frame
    # Salva os registradores
    sd  ra, 0(t6)
    sd  sp, 8(t6)
    sd  gp, 16(t6)
    sd  tp, 24(t6)
    sd  t0, 32(t6)
    sd  t1, 40(t6)
    sd  t2, 48(t6)
    sd  s0, 56(t6)
    sd  s1, 64(t6)
    sd  a0, 72(t6)
    sd  a1, 80(t6)
    sd  a2, 88(t6)
    sd  a3, 96(t6)
    sd  a4, 104(t6)
    sd  a5, 112(t6)
    sd  a6, 120(t6)
    sd  a7, 128(t6)
    sd  s2, 136(t6)
    sd  s3, 144(t6)
    sd  s4, 152(t6)
    sd  s5, 160(t6)
    sd  s6, 168(t6)
    sd  s7, 176(t6)
    sd  s8, 184(t6)
    sd  s9, 192(t6)
    sd  s10, 200(t6)
    sd  s11, 208(t6)
    sd  t3, 216(t6)
    sd  t4, 224(t6)
    sd  t5, 232(t6)
    mv t5, t6
    # t5 contém o endereço do trap frame
    # restaura o valor original de t6 e mscratch
    csrrw t6, mscratch, t6
    sd t6, 240(t5)
    csrr t0, mepc
    csrr t1, mhartid  # ID da CPU que gerou a exceção
    sd t1, 256(t5)
    sd t0, 264(t5)
    # Argumentos para a função de tratamento da exceção:
    # a0 = mtval
    # a1 = mcause
    # a2 = endereço do trap frame
    csrr a0, mtval
    csrr a1, mcause
    mv a2, t5
    ld sp, 248(t5) # A pilha para atendimento das exceções
    call mtrap # salta para código em C que trata a exceção
 
    # Restaura os registradores
    csrr t6, mscratch
 
    # O programa retoma sua execução no endereço em tf->epc
    ld t5, 264(t6)  # Conteúdo de mepc salvo na trap frame
    csrw mepc, t5 # mepc <- novo endereço de retorno
 
    ld  ra, 0(t6)
    ld  sp, 8(t6)
    ld  gp, 16(t6)
    ld  tp, 24(t6)
    ld  t0, 32(t6)
    ld  t1, 40(t6)
    ld  t2, 48(t6)
    ld  s0, 56(t6)
    ld  s1, 64(t6)
    ld  a0, 72(t6)
    ld  a1, 80(t6)
    ld  a2, 88(t6)
    ld  a3, 96(t6)
    ld  a4, 104(t6)
    ld  a5, 112(t6)
    ld  a6, 120(t6)
    ld  a7, 128(t6)
    ld  s2, 136(t6)
    ld  s3, 144(t6)
    ld  s4, 152(t6)
    ld  s5, 160(t6)
    ld  s6, 168(t6)
    ld  s7, 176(t6)
    ld  s8, 184(t6)
    ld  s9, 192(t6)
    ld  s10, 200(t6)
    ld  s11, 208(t6)
    ld  t3, 216(t6)
    ld  t4, 224(t6)
    ld  t5, 232(t6)
    ld  t6, 240(t6)
 
 
    mret
    