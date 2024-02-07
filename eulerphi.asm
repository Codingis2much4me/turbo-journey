.data
N: .word 1234

.text
main:
lw $t0, N
addi $t1, $zero, 0	#phi
addi $t2, $zero, 1	#trial
addi $t3, $zero, 1	#counter for gcd
addi $t4, $zero, 0	#storing gcd result
addi $k0, $zero, 1	#comparing gcd of N, trial

iterate:
move $t4, $zero
move $t3, $k0
beq $t2, $t0, exit
move $t6, $t2
addi $t2, $t2, 1
j gcd





gcd:
bgt $t3, $t6, mov
div $t0, $t3
mfhi $t5
div $t6, $t3
mfhi $t7
add $t8, $t7, $t5
move $t9, $t3
addi $t3, $t3, 1
beq $t8, $zero, update
j gcd

update:
move $t4, $t9
j gcd

mov:
beq $t4, $k0, phi
j iterate

phi:
addi $t1, $t1, 1
j iterate

exit:
li $v0, 1
add $a0, $zero, $t1
syscall
