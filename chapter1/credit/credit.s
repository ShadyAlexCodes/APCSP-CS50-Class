	.file	"credit.c"
	.text
	.section	.rodata
	.align 8
.LC0:
	.string	"What is your credit card number: "
.LC1:
	.string	"INVALID"
.LC2:
	.string	"VISA"
.LC3:
	.string	"AMEX"
.LC4:
	.string	"MASTERCARD"
	.text
	.globl	main
	.type	main, @function
main:
.LFB5:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%r14
	pushq	%r13
	pushq	%r12
	pushq	%rbx
	subq	$144, %rsp
	.cfi_offset 14, -24
	.cfi_offset 13, -32
	.cfi_offset 12, -40
	.cfi_offset 3, -48
	movq	%fs:40, %rax
	movq	%rax, -40(%rbp)
	xorl	%eax, %eax
	movl	$0, -96(%rbp)
	movq	$0, -88(%rbp)
.L2:
	leaq	.LC0(%rip), %rdi
	movl	$0, %eax
	call	get_long@PLT
	movq	%rax, -88(%rbp)
	cmpq	$0, -88(%rbp)
	js	.L2
	movq	-88(%rbp), %rax
	movq	%rax, -80(%rbp)
	jmp	.L3
.L4:
	movq	-80(%rbp), %rcx
	movabsq	$7378697629483820647, %rdx
	movq	%rcx, %rax
	imulq	%rdx
	sarq	$2, %rdx
	movq	%rcx, %rax
	sarq	$63, %rax
	subq	%rax, %rdx
	movq	%rdx, %rax
	movq	%rax, -80(%rbp)
	addl	$1, -96(%rbp)
.L3:
	cmpq	$0, -80(%rbp)
	jg	.L4
	cmpl	$13, -96(%rbp)
	je	.L5
	cmpl	$15, -96(%rbp)
	je	.L5
	cmpl	$16, -96(%rbp)
	je	.L5
	leaq	.LC1(%rip), %rdi
	call	puts@PLT
.L5:
	movl	-96(%rbp), %eax
	movq	%rsp, %rdx
	movq	%rdx, %rbx
	movslq	%eax, %rdx
	subq	$1, %rdx
	movq	%rdx, -72(%rbp)
	movslq	%eax, %rdx
	movq	%rdx, -144(%rbp)
	movq	$0, -136(%rbp)
	movslq	%eax, %rdx
	movq	%rdx, -160(%rbp)
	movq	$0, -152(%rbp)
	cltq
	salq	$2, %rax
	leaq	3(%rax), %rdx
	movl	$16, %eax
	subq	$1, %rax
	addq	%rdx, %rax
	movl	$16, %edi
	movl	$0, %edx
	divq	%rdi
	imulq	$16, %rax, %rax
	subq	%rax, %rsp
	movq	%rsp, %rax
	addq	$3, %rax
	shrq	$2, %rax
	salq	$2, %rax
	movq	%rax, -64(%rbp)
	movl	$0, -100(%rbp)
	jmp	.L6
.L7:
	movq	-88(%rbp), %rcx
	movabsq	$7378697629483820647, %rdx
	movq	%rcx, %rax
	imulq	%rdx
	sarq	$2, %rdx
	movq	%rcx, %rax
	sarq	$63, %rax
	subq	%rax, %rdx
	movq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	addq	%rax, %rax
	subq	%rax, %rcx
	movq	%rcx, %rdx
	movl	%edx, %ecx
	movq	-64(%rbp), %rax
	movl	-100(%rbp), %edx
	movslq	%edx, %rdx
	movl	%ecx, (%rax,%rdx,4)
	movq	-88(%rbp), %rcx
	movabsq	$7378697629483820647, %rdx
	movq	%rcx, %rax
	imulq	%rdx
	sarq	$2, %rdx
	movq	%rcx, %rax
	sarq	$63, %rax
	subq	%rax, %rdx
	movq	%rdx, %rax
	movq	%rax, -88(%rbp)
	addl	$1, -100(%rbp)
.L6:
	movl	-100(%rbp), %eax
	cmpl	-96(%rbp), %eax
	jl	.L7
	movl	-96(%rbp), %eax
	movq	%rsp, %rdx
	movq	%rdx, %r12
	movslq	%eax, %rdx
	subq	$1, %rdx
	movq	%rdx, -56(%rbp)
	movslq	%eax, %rdx
	movq	%rdx, -176(%rbp)
	movq	$0, -168(%rbp)
	movslq	%eax, %rdx
	movq	%rdx, %r13
	movl	$0, %r14d
	cltq
	salq	$2, %rax
	leaq	3(%rax), %rdx
	movl	$16, %eax
	subq	$1, %rax
	addq	%rdx, %rax
	movl	$16, %edi
	movl	$0, %edx
	divq	%rdi
	imulq	$16, %rax, %rax
	subq	%rax, %rsp
	movq	%rsp, %rax
	addq	$3, %rax
	shrq	$2, %rax
	salq	$2, %rax
	movq	%rax, -48(%rbp)
	movl	$0, -104(%rbp)
	jmp	.L8
.L9:
	movq	-64(%rbp), %rax
	movl	-104(%rbp), %edx
	movslq	%edx, %rdx
	movl	(%rax,%rdx,4), %ecx
	movq	-48(%rbp), %rax
	movl	-104(%rbp), %edx
	movslq	%edx, %rdx
	movl	%ecx, (%rax,%rdx,4)
	addl	$1, -104(%rbp)
.L8:
	movl	-104(%rbp), %eax
	cmpl	-96(%rbp), %eax
	jl	.L9
	movl	$1, -108(%rbp)
	jmp	.L10
.L11:
	movq	-64(%rbp), %rax
	movl	-108(%rbp), %edx
	movslq	%edx, %rdx
	movl	(%rax,%rdx,4), %eax
	leal	(%rax,%rax), %ecx
	movq	-64(%rbp), %rax
	movl	-108(%rbp), %edx
	movslq	%edx, %rdx
	movl	%ecx, (%rax,%rdx,4)
	addl	$2, -108(%rbp)
.L10:
	movl	-108(%rbp), %eax
	cmpl	-96(%rbp), %eax
	jl	.L11
	movl	$0, -92(%rbp)
	movl	$0, -112(%rbp)
	movl	$0, -116(%rbp)
	jmp	.L12
.L13:
	movq	-64(%rbp), %rax
	movl	-116(%rbp), %edx
	movslq	%edx, %rdx
	movl	(%rax,%rdx,4), %esi
	movl	$1717986919, %edx
	movl	%esi, %eax
	imull	%edx
	sarl	$2, %edx
	movl	%esi, %eax
	sarl	$31, %eax
	movl	%edx, %ecx
	subl	%eax, %ecx
	movl	%ecx, %eax
	sall	$2, %eax
	addl	%ecx, %eax
	addl	%eax, %eax
	subl	%eax, %esi
	movl	%esi, %ecx
	movq	-64(%rbp), %rax
	movl	-116(%rbp), %edx
	movslq	%edx, %rdx
	movl	(%rax,%rdx,4), %esi
	movl	$1717986919, %edx
	movl	%esi, %eax
	imull	%edx
	sarl	$2, %edx
	movl	%esi, %eax
	sarl	$31, %eax
	movl	%edx, %esi
	subl	%eax, %esi
	movl	$1717986919, %edx
	movl	%esi, %eax
	imull	%edx
	sarl	$2, %edx
	movl	%esi, %eax
	sarl	$31, %eax
	subl	%eax, %edx
	movl	%edx, %eax
	sall	$2, %eax
	addl	%edx, %eax
	addl	%eax, %eax
	subl	%eax, %esi
	movl	%esi, %edx
	leal	(%rcx,%rdx), %eax
	movl	%eax, -92(%rbp)
	movl	-92(%rbp), %eax
	addl	%eax, -112(%rbp)
	addl	$1, -116(%rbp)
.L12:
	movl	-116(%rbp), %eax
	cmpl	-96(%rbp), %eax
	jl	.L13
	cmpl	$13, -96(%rbp)
	jne	.L14
	movq	-48(%rbp), %rax
	movl	48(%rax), %eax
	cmpl	$4, %eax
	jne	.L15
	movl	-112(%rbp), %ecx
	movl	$1717986919, %edx
	movl	%ecx, %eax
	imull	%edx
	sarl	$2, %edx
	movl	%ecx, %eax
	sarl	$31, %eax
	subl	%eax, %edx
	movl	%edx, %eax
	sall	$2, %eax
	addl	%edx, %eax
	addl	%eax, %eax
	subl	%eax, %ecx
	movl	%ecx, %edx
	testl	%edx, %edx
	jne	.L15
	leaq	.LC2(%rip), %rdi
	call	puts@PLT
	jmp	.L14
.L15:
	leaq	.LC1(%rip), %rdi
	call	puts@PLT
.L14:
	cmpl	$15, -96(%rbp)
	jne	.L16
	movq	-48(%rbp), %rax
	movl	56(%rax), %eax
	cmpl	$3, %eax
	jne	.L17
	movl	-112(%rbp), %ecx
	movl	$1717986919, %edx
	movl	%ecx, %eax
	imull	%edx
	sarl	$2, %edx
	movl	%ecx, %eax
	sarl	$31, %eax
	subl	%eax, %edx
	movl	%edx, %eax
	sall	$2, %eax
	addl	%edx, %eax
	addl	%eax, %eax
	subl	%eax, %ecx
	movl	%ecx, %edx
	testl	%edx, %edx
	jne	.L17
	movq	-48(%rbp), %rax
	movl	52(%rax), %eax
	cmpl	$4, %eax
	je	.L18
	movq	-48(%rbp), %rax
	movl	52(%rax), %eax
	cmpl	$7, %eax
	jne	.L17
.L18:
	leaq	.LC3(%rip), %rdi
	call	puts@PLT
	jmp	.L16
.L17:
	leaq	.LC1(%rip), %rdi
	call	puts@PLT
.L16:
	cmpl	$16, -96(%rbp)
	jne	.L19
	movq	-48(%rbp), %rax
	movl	60(%rax), %eax
	cmpl	$5, %eax
	jne	.L20
	movl	-112(%rbp), %ecx
	movl	$1717986919, %edx
	movl	%ecx, %eax
	imull	%edx
	sarl	$2, %edx
	movl	%ecx, %eax
	sarl	$31, %eax
	subl	%eax, %edx
	movl	%edx, %eax
	sall	$2, %eax
	addl	%edx, %eax
	addl	%eax, %eax
	subl	%eax, %ecx
	movl	%ecx, %edx
	testl	%edx, %edx
	jne	.L20
	movq	-48(%rbp), %rax
	movl	56(%rax), %eax
	cmpl	$1, %eax
	je	.L21
	movq	-48(%rbp), %rax
	movl	56(%rax), %eax
	cmpl	$2, %eax
	je	.L21
	movq	-48(%rbp), %rax
	movl	56(%rax), %eax
	cmpl	$3, %eax
	je	.L21
	movq	-48(%rbp), %rax
	movl	56(%rax), %eax
	cmpl	$4, %eax
	je	.L21
	movq	-48(%rbp), %rax
	movl	56(%rax), %eax
	cmpl	$5, %eax
	jne	.L20
.L21:
	leaq	.LC4(%rip), %rdi
	call	puts@PLT
	jmp	.L19
.L20:
	movq	-48(%rbp), %rax
	movl	60(%rax), %eax
	cmpl	$4, %eax
	jne	.L22
	movl	-112(%rbp), %ecx
	movl	$1717986919, %edx
	movl	%ecx, %eax
	imull	%edx
	sarl	$2, %edx
	movl	%ecx, %eax
	sarl	$31, %eax
	subl	%eax, %edx
	movl	%edx, %eax
	sall	$2, %eax
	addl	%edx, %eax
	addl	%eax, %eax
	subl	%eax, %ecx
	movl	%ecx, %edx
	testl	%edx, %edx
	jne	.L22
	leaq	.LC2(%rip), %rdi
	call	puts@PLT
	jmp	.L19
.L22:
	leaq	.LC1(%rip), %rdi
	call	puts@PLT
.L19:
	movl	$0, %eax
	movq	%r12, %rsp
	movq	%rbx, %rsp
	movq	-40(%rbp), %rbx
	xorq	%fs:40, %rbx
	je	.L24
	call	__stack_chk_fail@PLT
.L24:
	leaq	-32(%rbp), %rsp
	popq	%rbx
	popq	%r12
	popq	%r13
	popq	%r14
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE5:
	.size	main, .-main
	.ident	"GCC: (Ubuntu 7.4.0-1ubuntu1~18.04.1) 7.4.0"
	.section	.note.GNU-stack,"",@progbits
