	.text
.globl _foo
_foo:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$24, %esp
	movl	8(%ebp), %eax
	imull	8(%ebp), %eax
	movl	%eax, -12(%ebp)
	movl	-12(%ebp), %eax
	addl	$2, %eax
	movl	%ebp, %esp
	popl	%ebp
	ret
	.subsections_via_symbols
