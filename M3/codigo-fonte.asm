    .data
	Matriz_A:    .space 400            # Reserva espa�o para 100 inteiros (Matriz A)
	Matriz_B:    .space 400            # Reserva espa�o para 100 inteiros (Matriz B)
	Matriz_C:    .space 400            # Reserva espa�o para 100 inteiros (Matriz C)
	tamanho:     .word 0               # Armazena o tamanho N da matriz NxN
	modo:        .word 0               # Armazena o modo de percorrimento das matrizes (0 ou 1)
	msg_tamanho: .asciz "Entre com o tamanho do �ndice das matrizes (m�x. = 10): "
	msg_modo:    .asciz "Escolha o modo de percorrer as matrizes (0 para linha-coluna, 1 para coluna-linha): "
	msg_erro:    .asciz "Valor inv�lido, tente novamente.\n"

    .text
    .globl _start
_start:
    # Solicita e valida o tamanho das matrizes
    la a0, msg_tamanho
    call print_string
    call read_int
    mv t0, a0                     # Armazena entrada em t0
    li t1, 2                      # Limite inferior (tamanho m�nimo)
    li t2, 10                     # Limite superior (tamanho m�ximo)
    blt t0, t1, invalid_input     # Verifica se t0 < t1
    bgt t0, t2, invalid_input     # Verifica se t0 > t2
    sw t0, tamanho, t2         	  # Armazena tamanho v�lido
    

    # Inicializa e imprime Matriz_A, Matriz_B e Matriz_C
    li t3, 0                      # �ndice para inicializa��o das matrizes
    la t4, Matriz_A
    la t5, Matriz_B
    la t6, Matriz_C
    mul t0,t0,t0		 # tamanho * tamanho 
init_loop:
    beq t3, t0, read_mode         # Encerra a inicializa��o quando atingir o tamanho
    sw zero, 0(t4)                # Define todos os elementos de Matriz_A como 0
    li t2, 1
    sw t2, 0(t5)                  # Define todos os elementos de Matriz_B como 1
    sw t3, 0(t6)                  # Preenche Matriz_C com valores crescentes
    addi t4, t4, 4                # Avan�a para o pr�ximo inteiro em Matriz_A
    addi t5, t5, 4                # Avan�a para o pr�ximo inteiro em Matriz_B
    addi t6, t6, 4                # Avan�a para o pr�ximo inteiro em Matriz_C
    addi t3, t3, 1                # Incrementa o �ndice
    j init_loop                   # Repete o loop

read_mode:  
    # Solicita e valida o modo de percorrimento
    la a0, msg_modo
    call print_string
    call read_int
    mv t0, a0                     # Armazena entrada em t0
    li t1, 0                      # Modo linha-coluna
    li t2, 1                      # Modo coluna-linha
    blt t0, t1, invalid_input     # Verifica se t0 < t1
    bgt t0, t2, invalid_input     # Verifica se t0 > t2
    sw t0, modo, t3             # Armazena modo v�lido

    # Chama a fun��o de soma de matrizes baseada no modo
    lw t0, modo
    beqz t0, soma_linha_coluna
    j soma_coluna_linha

soma_linha_coluna:
    # Implementa��o da soma das matrizes linha por linha
    li t0, 0
    li t2, 0
    lw t1, tamanho          	# Carrega o tamanho da matriz
    mul t1, t1, t1         	# tamanho * tamanho

soma_lcl:
    beq t2, t1, imprimir_matriz    # Se t0 == t1, vai para impress�o das matrizes
    la t3, Matriz_A		  # Carrega o endereco da label 
    la t4, Matriz_B
    la t5, Matriz_C
    add t3, t3, t0                # Endere�o de Matriz_A[t0]
    add t4, t4, t0                # Endere�o de Matriz_B[t0]
    add t5, t5, t0                # Endere�o de Matriz_C[t0]
    lw t6, 0(t3)                  # t6 = Matriz_A[t0]
    lw t3, 0(t4)                  # t3 = Matriz_B[t0]
    add t6, t6, t3                # t6 = t6 + t3
    sw t6, 0(t5)                  # Matriz_C[t0] = t6
    addi t0, t0, 4                # Incrementa �ndice
    addi t2, t2, 1
    j soma_lcl                    # Continua o loop

soma_coluna_linha:
    li t0, 0                     # �ndice da coluna inicial
    lw t1, tamanho               # Carrega o tamanho da matriz NxN em t1

col_loop:
    beq t0, t1, imprimir_matriz  # Se t0 == t1, finaliza e vai para impress�o das matrizes
    li t2, 0                     # �ndice da linha inicial para a coluna t0

linha_loop:
    beq t2, t1, proxima_col      # Se t2 == t1, terminou todas as linhas nesta coluna, v� para a pr�xima coluna
    lw t5, tamanho
    mul t3, t5, t2
    add t3, t3, t0
    li t4, 4
    mul t3, t3, t4

    la t4, Matriz_A              # Endere�o base de Matriz_A
    la t5, Matriz_B              # Endere�o base de Matriz_B
    la t6, Matriz_C              # Endere�o base de Matriz_C

    add t4, t4, t3               # Ajusta t4 para a linha correta
    add t5, t5, t3               # Ajusta t5 para a linha correta
    add t6, t6, t3               # Ajusta t6 para a linha correta

    lw t3, 0(t4)                 # Carrega elemento de Matriz_A na posi��o (t2, t0)
    lw t4, 0(t5)                 # Carrega elemento de Matriz_B na posi��o (t2, t0)
    add t3, t3, t4               # Soma os elementos de A e B
    sw t3, 0(t6)                 # Armazena resultado em Matriz_C na posi��o (t2, t0)

    addi t2, t2, 1               # Incrementa o �ndice da linha
    j linha_loop                 # Volta para continuar com a pr�xima linha nesta coluna

proxima_col:
    addi t0, t0, 1               # Incrementa o �ndice da coluna
    j col_loop                   # Volta para continuar com a pr�xima coluna

imprimir_matriz:
    # Fun��o para imprimir a matriz C em formato matricial
    li t0, 0                     # �ndice de linha inicial
    lw t1, tamanho	         # Carrega o tamanho N da matriz NxN
    li t3, 0                     # �ndice geral para elementos

print_row_loop:
    beq t0, t1, end_program      # Termina o programa quando todas as linhas forem impressas
    li t2, 0                     # Reseta o �ndice de coluna para cada nova linha

print_col_loop:
    bge t2, t1, print_newline    # Vai para a nova linha quando todas as colunas desta linha forem impressas
    la t5, Matriz_C              # Endere�o base de Matriz_
    add t5, t5, t3               # Calcula o endere�o efetivo de Matriz_C[t3]
    lw a0, 0(t5)                 # Carrega o elemento Matriz_C[t3]
    li a7, 1                     # Syscall para imprimir inteiro
    ecall                        # Executa a syscall
    li a7, 11                    # Syscall para imprimir caractere (espa�o)
    li a0, ' '                   # ASCII para espa�o
    ecall                        # Imprime um espa�o
    addi t2, t2, 1               # Incrementa o �ndice de coluna
    addi t3, t3, 4               # Incrementa o �ndice geral
    j print_col_loop             # Repete para a pr�xima coluna

print_newline:
    li a7, 11                    # Syscall para imprimir caractere (nova linha)
    li a0, 10                    # ASCII para nova linha (LF)
    ecall                        # Imprime uma nova linha
    addi t0, t0, 1               # Incrementa o �ndice de linha
    j print_row_loop             # Repete para a pr�xima linha


invalid_input:
    la a0, msg_erro               # Mensagem de erro
    call print_string             # Imprime mensagem de erro
    j _start                      # Retorna ao in�cio do programa

end_program:
    li a7, 10                     # Syscall para terminar o programa
    ecall                         # Executa a syscall

print_string:
    li a7, 4                      # Syscall para imprimir string
    ecall                         # Executa a syscall
    ret                           # Retorna da fun��o

read_int:
    li a7, 5                      # Syscall para ler um inteiro
    ecall                         # Executa a syscall
    mv a0, a0                     # Move o resultado lido para o registrador de retorno a0
    ret                           # Retorna da fun��o
