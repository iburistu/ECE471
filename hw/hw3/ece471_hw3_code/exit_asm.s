
@ Syscall defines
.equ SYSCALL_EXIT,     1
.equ RETURN_VALUE,42

        .globl _start
_start:

        @================================
        @ Exit
        @================================
exit:

	@ YOUR CODE HERE
	mov r0,#RETURN_VALUE	@ put the number 42 inside the r0 register for returning
	mov r7,#SYSCALL_EXIT	@ put exit syscall number in r7
	swi 0x0			@ and exit
