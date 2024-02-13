.data
array1: .word 5
prompt1: .asciiz "\nEnter 5 integers for 1st vector\n"
array2: .word 5
prompt2: .asciiz "\nEnter 5 integers for 2nd vector\n"
promptans: .asciiz "\nThe dot product is : \n"


.text
main:

la $a0, prompt1
li $v0, 4
syscall

addi $t0, $zero, 0		#counter variable.
addi $t1, $zero, 5

la $t2, array1
la $t3, array2

move $t4, $t2			#copy of addresses of arrays.
move $t5, $t3


take_input1:
beq $t0, $t1, print
li $v0, 5
syscall
sw $v0, 0($t2)			#storing each integer in memory
addi $t2, $t2, 4
addi $t0, $t0, 1
j take_input1

print: 
la $a0, prompt2
li $v0, 4
syscall

addi $t0, $t0, -5			#resetting counter

take_input2:
beq $t0, $t1, update
li $v0, 5
syscall
sw $v0, 0($t3)
addi $t3, $t3, 4
addi $t0, $t0, 1
j take_input2

update:
move $t1, $zero			#using $t1 for storing sum.
j dotprod

dotprod:
beq $t2, $t4, displaysum
lw $t6, 0($t4)
lw $t7, 0($t5)
mult $t6, $t7
mflo $t0
add $t1, $t1, $t0
addi $t4, $t4, 4
addi $t5, $t5, 4
j dotprod

displaysum:
la $a0, promptans
li $v0, 4
syscall
move $a0, $t1
li $v0, 1
syscall

exit:
li $v0, 10
syscall