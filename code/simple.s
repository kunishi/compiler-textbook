	.text
.globl _main
_main:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$24, %esp
	movl	$1, -12(%ebp)
	movl	-12(%ebp), %eax
	addl	$20, %eax
	movl	%eax, -16(%ebp)
	movl	%ebp, %esp
	popl	%ebp
	ret
	.subsections_via_symbols
