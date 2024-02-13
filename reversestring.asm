.data
prompt: .asciiz "\nEnter a string: \n"
string: .space 41
output: .asciiz "\nYou entered the string: "

.text
main:

la $a0, prompt
li $v0, 4
syscall

la $a0, string
li $a1, 41
li $v0, 8
syscall

li $t4, 41
la $t0, ($a0)
move $t5, $t0
addi $t0, $t0, 41

print:
blt $t0, $t5, exit
lb $a0, 0($t0)
li $v0, 11
syscall
addi $t0, $t0, -1
j print


exit:
li $v0, 10
syscall