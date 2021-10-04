	.section	__TEXT,__text,regular,pure_instructions
	.build_version macos, 10, 15
	.globl	_incrementRefCounter            ## -- Begin function incrementRefCounter
	.p2align	4, 0x90
_incrementRefCounter:                   ## @incrementRefCounter
	.cfi_startproc
## %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	(%rax), %rcx
	addq	$1, %rcx
	movq	%rcx, (%rax)
	popq	%rbp
	retq
	.cfi_endproc
                                        ## -- End function
	.globl	_decrementRefCounter            ## -- Begin function decrementRefCounter
	.p2align	4, 0x90
_decrementRefCounter:                   ## @decrementRefCounter
	.cfi_startproc
## %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rcx
	movq	(%rcx), %rax
	addq	$-1, %rax
	movq	%rax, (%rcx)
                                        ## kill: def $eax killed $eax killed $rax
	popq	%rbp
	retq
	.cfi_endproc
                                        ## -- End function
	.globl	_isFalse                        ## -- Begin function isFalse
	.p2align	4, 0x90
_isFalse:                               ## @isFalse
	.cfi_startproc
## %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	cmpq	$0, 24(%rax)
	sete	%al
	andb	$1, %al
	movzbl	%al, %eax
	popq	%rbp
	retq
	.cfi_endproc
                                        ## -- End function
	.globl	_isTrue                         ## -- Begin function isTrue
	.p2align	4, 0x90
_isTrue:                                ## @isTrue
	.cfi_startproc
## %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	cmpq	$1, 24(%rax)
	sete	%al
	andb	$1, %al
	movzbl	%al, %eax
	popq	%rbp
	retq
	.cfi_endproc
                                        ## -- End function
	.globl	_newObject                      ## -- Begin function newObject
	.p2align	4, 0x90
_newObject:                             ## @newObject
	.cfi_startproc
## %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	subq	$16, %rsp
	movl	$24, %edi
	callq	_malloc
	movq	%rax, -8(%rbp)
	cmpq	$0, -8(%rbp)
	setne	%al
	xorb	$-1, %al
	andb	$1, %al
	movzbl	%al, %eax
	cltq
	cmpq	$0, %rax
	je	LBB4_2
## %bb.1:
	leaq	L___func__.newObject(%rip), %rdi
	leaq	L_.str(%rip), %rsi
	leaq	L_.str.1(%rip), %rcx
	movl	$157, %edx
	callq	___assert_rtn
LBB4_2:
	jmp	LBB4_3
LBB4_3:
	movq	-8(%rbp), %rdi
	movl	$4294967290, %esi               ## imm = 0xFFFFFFFA
	callq	_initHeader
	movq	-8(%rbp), %rax
	leaq	_ObjectVTTemplate(%rip), %rcx
	movq	%rcx, 16(%rax)
	movq	-8(%rbp), %rax
	addq	$16, %rsp
	popq	%rbp
	retq
	.cfi_endproc
                                        ## -- End function
	.p2align	4, 0x90                         ## -- Begin function initHeader
_initHeader:                            ## @initHeader
	.cfi_startproc
## %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	movq	%rdi, -16(%rbp)
	movl	%esi, -4(%rbp)
	movq	-16(%rbp), %rax
	movq	$0, (%rax)
	movl	-4(%rbp), %eax
	movq	-16(%rbp), %rcx
	movl	%eax, 8(%rcx)
	popq	%rbp
	retq
	.cfi_endproc
                                        ## -- End function
	.globl	_newNothing                     ## -- Begin function newNothing
	.p2align	4, 0x90
_newNothing:                            ## @newNothing
	.cfi_startproc
## %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	leaq	_Nothing(%rip), %rax
	popq	%rbp
	retq
	.cfi_endproc
                                        ## -- End function
	.globl	_newBoolean                     ## -- Begin function newBoolean
	.p2align	4, 0x90
_newBoolean:                            ## @newBoolean
	.cfi_startproc
## %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rcx
	leaq	_False(%rip), %rax
	leaq	_True(%rip), %rdx
	cmpq	$1, %rcx
	cmoveq	%rdx, %rax
	popq	%rbp
	retq
	.cfi_endproc
                                        ## -- End function
	.globl	_newInteger                     ## -- Begin function newInteger
	.p2align	4, 0x90
_newInteger:                            ## @newInteger
	.cfi_startproc
## %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	subq	$16, %rsp
	movq	%rdi, -16(%rbp)
	movl	$32, %edi
	callq	_malloc
	movq	%rax, -8(%rbp)
	cmpq	$0, -8(%rbp)
	setne	%al
	xorb	$-1, %al
	andb	$1, %al
	movzbl	%al, %eax
	cltq
	cmpq	$0, %rax
	je	LBB8_2
## %bb.1:
	leaq	L___func__.newInteger(%rip), %rdi
	leaq	L_.str(%rip), %rsi
	leaq	L_.str.1(%rip), %rcx
	movl	$225, %edx
	callq	___assert_rtn
LBB8_2:
	jmp	LBB8_3
LBB8_3:
	movq	-8(%rbp), %rdi
	movl	$4294967291, %esi               ## imm = 0xFFFFFFFB
	callq	_initHeader
	movq	-8(%rbp), %rax
	leaq	_IntegerVTTemplate(%rip), %rcx
	movq	%rcx, 16(%rax)
	movq	-16(%rbp), %rax
	movq	-8(%rbp), %rcx
	movq	%rax, 24(%rcx)
	movq	-8(%rbp), %rax
	addq	$16, %rsp
	popq	%rbp
	retq
	.cfi_endproc
                                        ## -- End function
	.globl	_newFloat                       ## -- Begin function newFloat
	.p2align	4, 0x90
_newFloat:                              ## @newFloat
	.cfi_startproc
## %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	subq	$16, %rsp
	movsd	%xmm0, -16(%rbp)
	movl	$32, %edi
	callq	_malloc
	movq	%rax, -8(%rbp)
	cmpq	$0, -8(%rbp)
	setne	%al
	xorb	$-1, %al
	andb	$1, %al
	movzbl	%al, %eax
	cltq
	cmpq	$0, %rax
	je	LBB9_2
## %bb.1:
	leaq	L___func__.newFloat(%rip), %rdi
	leaq	L_.str(%rip), %rsi
	leaq	L_.str.1(%rip), %rcx
	movl	$265, %edx                      ## imm = 0x109
	callq	___assert_rtn
LBB9_2:
	jmp	LBB9_3
LBB9_3:
	movq	-8(%rbp), %rdi
	movl	$4294967292, %esi               ## imm = 0xFFFFFFFC
	callq	_initHeader
	movq	-8(%rbp), %rax
	leaq	_FloatVTTemplate(%rip), %rcx
	movq	%rcx, 16(%rax)
	movsd	-16(%rbp), %xmm0                ## xmm0 = mem[0],zero
	movq	-8(%rbp), %rax
	movsd	%xmm0, 24(%rax)
	movq	-8(%rbp), %rax
	addq	$16, %rsp
	popq	%rbp
	retq
	.cfi_endproc
                                        ## -- End function
	.globl	_newString                      ## -- Begin function newString
	.p2align	4, 0x90
_newString:                             ## @newString
	.cfi_startproc
## %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	subq	$16, %rsp
	movq	%rdi, -16(%rbp)
	movl	$32, %edi
	callq	_malloc
	movq	%rax, -8(%rbp)
	cmpq	$0, -8(%rbp)
	setne	%al
	xorb	$-1, %al
	andb	$1, %al
	movzbl	%al, %eax
	cltq
	cmpq	$0, %rax
	je	LBB10_2
## %bb.1:
	leaq	L___func__.newString(%rip), %rdi
	leaq	L_.str(%rip), %rsi
	leaq	L_.str.2(%rip), %rcx
	movl	$301, %edx                      ## imm = 0x12D
	callq	___assert_rtn
LBB10_2:
	jmp	LBB10_3
LBB10_3:
	movq	-8(%rbp), %rdi
	movl	$4294967294, %esi               ## imm = 0xFFFFFFFE
	callq	_initHeader
	movq	-8(%rbp), %rax
	leaq	_StringVTTemplate(%rip), %rcx
	movq	%rcx, 16(%rax)
	movq	-16(%rbp), %rdi
	callq	_strdup
	movq	-8(%rbp), %rcx
	movq	%rax, 24(%rcx)
	movq	-8(%rbp), %rax
	addq	$16, %rsp
	popq	%rbp
	retq
	.cfi_endproc
                                        ## -- End function
	.p2align	4, 0x90                         ## -- Begin function equalsObject
_equalsObject:                          ## @equalsObject
	.cfi_startproc
## %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	movq	%rdi, -16(%rbp)
	movq	%rsi, -8(%rbp)
	movq	-16(%rbp), %rcx
	movq	-8(%rbp), %rdx
	leaq	_False(%rip), %rax
	leaq	_True(%rip), %rsi
	cmpq	%rdx, %rcx
	cmoveq	%rsi, %rax
	popq	%rbp
	retq
	.cfi_endproc
                                        ## -- End function
	.p2align	4, 0x90                         ## -- Begin function printObject
_printObject:                           ## @printObject
	.cfi_startproc
## %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rsi
	leaq	L_.str.3(%rip), %rdi
	movb	$0, %al
	callq	_printf
	leaq	_Nothing(%rip), %rax
	addq	$16, %rsp
	popq	%rbp
	retq
	.cfi_endproc
                                        ## -- End function
	.p2align	4, 0x90                         ## -- Begin function destroyObject
_destroyObject:                         ## @destroyObject
	.cfi_startproc
## %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rdi
	callq	_decrementRefCounter
	cmpl	$0, %eax
	jne	LBB13_2
## %bb.1:
	movq	-8(%rbp), %rdi
	callq	_free
LBB13_2:
	leaq	_Nothing(%rip), %rax
	addq	$16, %rsp
	popq	%rbp
	retq
	.cfi_endproc
                                        ## -- End function
	.p2align	4, 0x90                         ## -- Begin function equalsNothing
_equalsNothing:                         ## @equalsNothing
	.cfi_startproc
## %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movq	-8(%rbp), %rax
	movl	8(%rax), %eax
	movq	-16(%rbp), %rdx
	xorl	%ecx, %ecx
	cmpl	8(%rdx), %eax
	jne	LBB14_2
## %bb.1:
	movq	-8(%rbp), %rax
	cmpl	$-1, 8(%rax)
	sete	%cl
LBB14_2:
	leaq	_False(%rip), %rax
	leaq	_True(%rip), %rdx
	testb	$1, %cl
	cmovneq	%rdx, %rax
	popq	%rbp
	retq
	.cfi_endproc
                                        ## -- End function
	.p2align	4, 0x90                         ## -- Begin function printNothing
_printNothing:                          ## @printNothing
	.cfi_startproc
## %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	leaq	L_.str.4(%rip), %rdi
	movb	$0, %al
	callq	_printf
	leaq	_Nothing(%rip), %rax
	addq	$16, %rsp
	popq	%rbp
	retq
	.cfi_endproc
                                        ## -- End function
	.p2align	4, 0x90                         ## -- Begin function destroyNothing
_destroyNothing:                        ## @destroyNothing
	.cfi_startproc
## %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	movq	%rdi, -8(%rbp)
	leaq	_Nothing(%rip), %rax
	popq	%rbp
	retq
	.cfi_endproc
                                        ## -- End function
	.p2align	4, 0x90                         ## -- Begin function equalsBoolean
_equalsBoolean:                         ## @equalsBoolean
	.cfi_startproc
## %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	movq	%rdi, -16(%rbp)
	movq	%rsi, -8(%rbp)
	movq	-16(%rbp), %rax
	movq	24(%rax), %rcx
	movq	-8(%rbp), %rax
	movq	24(%rax), %rdx
	leaq	_False(%rip), %rax
	leaq	_True(%rip), %rsi
	cmpq	%rdx, %rcx
	cmoveq	%rsi, %rax
	popq	%rbp
	retq
	.cfi_endproc
                                        ## -- End function
	.p2align	4, 0x90                         ## -- Begin function printBoolean
_printBoolean:                          ## @printBoolean
	.cfi_startproc
## %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rdi
	callq	_isTrue
	cmpl	$0, %eax
	je	LBB18_2
## %bb.1:
	leaq	L_.str.5(%rip), %rdi
	movb	$0, %al
	callq	_printf
	jmp	LBB18_3
LBB18_2:
	leaq	L_.str.6(%rip), %rdi
	movb	$0, %al
	callq	_printf
LBB18_3:
	leaq	_Nothing(%rip), %rax
	addq	$16, %rsp
	popq	%rbp
	retq
	.cfi_endproc
                                        ## -- End function
	.p2align	4, 0x90                         ## -- Begin function destroyBoolean
_destroyBoolean:                        ## @destroyBoolean
	.cfi_startproc
## %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	movq	%rdi, -8(%rbp)
	leaq	_Nothing(%rip), %rax
	popq	%rbp
	retq
	.cfi_endproc
                                        ## -- End function
	.p2align	4, 0x90                         ## -- Begin function equalsInteger
_equalsInteger:                         ## @equalsInteger
	.cfi_startproc
## %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	movq	%rdi, -16(%rbp)
	movq	%rsi, -8(%rbp)
	movq	-16(%rbp), %rax
	movq	24(%rax), %rcx
	movq	-8(%rbp), %rax
	movq	24(%rax), %rdx
	leaq	_False(%rip), %rax
	leaq	_True(%rip), %rsi
	cmpq	%rdx, %rcx
	cmoveq	%rsi, %rax
	popq	%rbp
	retq
	.cfi_endproc
                                        ## -- End function
	.p2align	4, 0x90                         ## -- Begin function printInteger
_printInteger:                          ## @printInteger
	.cfi_startproc
## %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	24(%rax), %rsi
	leaq	L_.str.7(%rip), %rdi
	movb	$0, %al
	callq	_printf
	leaq	_Nothing(%rip), %rax
	addq	$16, %rsp
	popq	%rbp
	retq
	.cfi_endproc
                                        ## -- End function
	.p2align	4, 0x90                         ## -- Begin function addInteger
_addInteger:                            ## @addInteger
	.cfi_startproc
## %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	subq	$16, %rsp
	movq	%rdi, -16(%rbp)
	movq	%rsi, -8(%rbp)
	movq	-16(%rbp), %rax
	movq	24(%rax), %rdi
	movq	-8(%rbp), %rax
	addq	24(%rax), %rdi
	callq	_newInteger
	addq	$16, %rsp
	popq	%rbp
	retq
	.cfi_endproc
                                        ## -- End function
	.p2align	4, 0x90                         ## -- Begin function mulInteger
_mulInteger:                            ## @mulInteger
	.cfi_startproc
## %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	subq	$16, %rsp
	movq	%rdi, -16(%rbp)
	movq	%rsi, -8(%rbp)
	movq	-16(%rbp), %rax
	movq	24(%rax), %rdi
	movq	-8(%rbp), %rax
	imulq	24(%rax), %rdi
	callq	_newInteger
	addq	$16, %rsp
	popq	%rbp
	retq
	.cfi_endproc
                                        ## -- End function
	.p2align	4, 0x90                         ## -- Begin function subInteger
_subInteger:                            ## @subInteger
	.cfi_startproc
## %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	subq	$16, %rsp
	movq	%rdi, -16(%rbp)
	movq	%rsi, -8(%rbp)
	movq	-16(%rbp), %rax
	movq	24(%rax), %rdi
	movq	-8(%rbp), %rax
	subq	24(%rax), %rdi
	callq	_newInteger
	addq	$16, %rsp
	popq	%rbp
	retq
	.cfi_endproc
                                        ## -- End function
	.p2align	4, 0x90                         ## -- Begin function divInteger
_divInteger:                            ## @divInteger
	.cfi_startproc
## %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	subq	$16, %rsp
	movq	%rdi, -16(%rbp)
	movq	%rsi, -8(%rbp)
	movq	-16(%rbp), %rax
	movq	24(%rax), %rax
	movq	-8(%rbp), %rcx
	cqto
	idivq	24(%rcx)
	movq	%rax, %rdi
	callq	_newInteger
	addq	$16, %rsp
	popq	%rbp
	retq
	.cfi_endproc
                                        ## -- End function
	.p2align	4, 0x90                         ## -- Begin function modInteger
_modInteger:                            ## @modInteger
	.cfi_startproc
## %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	subq	$16, %rsp
	movq	%rdi, -16(%rbp)
	movq	%rsi, -8(%rbp)
	movq	-16(%rbp), %rax
	movq	24(%rax), %rax
	movq	-8(%rbp), %rcx
	cqto
	idivq	24(%rcx)
	movq	%rdx, %rdi
	callq	_newInteger
	addq	$16, %rsp
	popq	%rbp
	retq
	.cfi_endproc
                                        ## -- End function
	.p2align	4, 0x90                         ## -- Begin function equalsFloat
_equalsFloat:                           ## @equalsFloat
	.cfi_startproc
## %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	movq	%rdi, -16(%rbp)
	movq	%rsi, -8(%rbp)
	movq	-16(%rbp), %rax
	movsd	24(%rax), %xmm0                 ## xmm0 = mem[0],zero
	movq	-8(%rbp), %rax
	movsd	24(%rax), %xmm1                 ## xmm1 = mem[0],zero
	leaq	_False(%rip), %rax
	leaq	_True(%rip), %rsi
	ucomisd	%xmm1, %xmm0
	setnp	%dl
	sete	%cl
	testb	%dl, %cl
	cmovneq	%rsi, %rax
	popq	%rbp
	retq
	.cfi_endproc
                                        ## -- End function
	.p2align	4, 0x90                         ## -- Begin function printFloat
_printFloat:                            ## @printFloat
	.cfi_startproc
## %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	movsd	24(%rax), %xmm0                 ## xmm0 = mem[0],zero
	leaq	L_.str.8(%rip), %rdi
	movb	$1, %al
	callq	_printf
	leaq	_Nothing(%rip), %rax
	addq	$16, %rsp
	popq	%rbp
	retq
	.cfi_endproc
                                        ## -- End function
	.p2align	4, 0x90                         ## -- Begin function addFloat
_addFloat:                              ## @addFloat
	.cfi_startproc
## %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	subq	$16, %rsp
	movq	%rdi, -16(%rbp)
	movq	%rsi, -8(%rbp)
	movq	-16(%rbp), %rax
	movsd	24(%rax), %xmm0                 ## xmm0 = mem[0],zero
	movq	-8(%rbp), %rax
	addsd	24(%rax), %xmm0
	callq	_newFloat
	addq	$16, %rsp
	popq	%rbp
	retq
	.cfi_endproc
                                        ## -- End function
	.p2align	4, 0x90                         ## -- Begin function mulFloat
_mulFloat:                              ## @mulFloat
	.cfi_startproc
## %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	subq	$16, %rsp
	movq	%rdi, -16(%rbp)
	movq	%rsi, -8(%rbp)
	movq	-16(%rbp), %rax
	movsd	24(%rax), %xmm0                 ## xmm0 = mem[0],zero
	movq	-8(%rbp), %rax
	mulsd	24(%rax), %xmm0
	callq	_newFloat
	addq	$16, %rsp
	popq	%rbp
	retq
	.cfi_endproc
                                        ## -- End function
	.p2align	4, 0x90                         ## -- Begin function subFloat
_subFloat:                              ## @subFloat
	.cfi_startproc
## %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	subq	$16, %rsp
	movq	%rdi, -16(%rbp)
	movq	%rsi, -8(%rbp)
	movq	-16(%rbp), %rax
	movsd	24(%rax), %xmm0                 ## xmm0 = mem[0],zero
	movq	-8(%rbp), %rax
	subsd	24(%rax), %xmm0
	callq	_newFloat
	addq	$16, %rsp
	popq	%rbp
	retq
	.cfi_endproc
                                        ## -- End function
	.p2align	4, 0x90                         ## -- Begin function divFloat
_divFloat:                              ## @divFloat
	.cfi_startproc
## %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	subq	$16, %rsp
	movq	%rdi, -16(%rbp)
	movq	%rsi, -8(%rbp)
	movq	-16(%rbp), %rax
	movsd	24(%rax), %xmm0                 ## xmm0 = mem[0],zero
	movq	-8(%rbp), %rax
	divsd	24(%rax), %xmm0
	callq	_newFloat
	addq	$16, %rsp
	popq	%rbp
	retq
	.cfi_endproc
                                        ## -- End function
	.p2align	4, 0x90                         ## -- Begin function equalsString
_equalsString:                          ## @equalsString
	.cfi_startproc
## %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	subq	$32, %rsp
	movq	%rdi, -24(%rbp)
	movq	%rsi, -16(%rbp)
	movq	-24(%rbp), %rax
	movq	24(%rax), %rdi
	movq	-16(%rbp), %rax
	movq	24(%rax), %rsi
	callq	_strcmp
	movl	%eax, -4(%rbp)
	movl	-4(%rbp), %ecx
	leaq	_False(%rip), %rax
	leaq	_True(%rip), %rdx
	cmpl	$0, %ecx
	cmoveq	%rdx, %rax
	addq	$32, %rsp
	popq	%rbp
	retq
	.cfi_endproc
                                        ## -- End function
	.p2align	4, 0x90                         ## -- Begin function printString
_printString:                           ## @printString
	.cfi_startproc
## %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	___stdoutp@GOTPCREL(%rip), %rax
	movq	(%rax), %rdi
	movq	-8(%rbp), %rax
	movq	24(%rax), %rdx
	leaq	L_.str.9(%rip), %rsi
	movb	$0, %al
	callq	_fprintf
	leaq	_Nothing(%rip), %rax
	addq	$16, %rsp
	popq	%rbp
	retq
	.cfi_endproc
                                        ## -- End function
	.p2align	4, 0x90                         ## -- Begin function destroyString
_destroyString:                         ## @destroyString
	.cfi_startproc
## %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rdi
	callq	_decrementRefCounter
	cmpl	$0, %eax
	je	LBB35_2
## %bb.1:
	movq	-8(%rbp), %rax
	movq	24(%rax), %rdi
	callq	_free
	movq	-8(%rbp), %rdi
	callq	_free
LBB35_2:
	leaq	_Nothing(%rip), %rax
	addq	$16, %rsp
	popq	%rbp
	retq
	.cfi_endproc
                                        ## -- End function
	.p2align	4, 0x90                         ## -- Begin function addString
_addString:                             ## @addString
	.cfi_startproc
## %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	subq	$48, %rsp
	movq	%rdi, -48(%rbp)
	movq	%rsi, -40(%rbp)
	movq	-48(%rbp), %rax
	movq	24(%rax), %rdi
	callq	_strlen
	movl	%eax, -4(%rbp)
	movq	-40(%rbp), %rax
	movq	24(%rax), %rdi
	callq	_strlen
	movl	%eax, -32(%rbp)
	movl	-4(%rbp), %eax
	addl	-32(%rbp), %eax
	movl	%eax, -28(%rbp)
	movl	-28(%rbp), %eax
	addl	$1, %eax
	movslq	%eax, %rdi
	callq	_malloc
	movq	%rax, -24(%rbp)
	cmpq	$0, -24(%rbp)
	setne	%al
	xorb	$-1, %al
	andb	$1, %al
	movzbl	%al, %eax
	cltq
	cmpq	$0, %rax
	je	LBB36_2
## %bb.1:
	leaq	L___func__.addString(%rip), %rdi
	leaq	L_.str(%rip), %rsi
	leaq	L_.str.10(%rip), %rcx
	movl	$332, %edx                      ## imm = 0x14C
	callq	___assert_rtn
LBB36_2:
	jmp	LBB36_3
LBB36_3:
	movq	-24(%rbp), %rdi
	movq	-48(%rbp), %rax
	movq	24(%rax), %rsi
	movslq	-4(%rbp), %rdx
	movq	$-1, %rcx
	callq	___strncpy_chk
	movq	-24(%rbp), %rdi
	movslq	-4(%rbp), %rax
	addq	%rax, %rdi
	movq	-40(%rbp), %rax
	movq	24(%rax), %rsi
	movslq	-32(%rbp), %rdx
	movq	$-1, %rcx
	callq	___strncpy_chk
	movq	-24(%rbp), %rax
	movslq	-28(%rbp), %rcx
	movb	$0, (%rax,%rcx)
	movl	$32, %edi
	callq	_malloc
	movq	%rax, -16(%rbp)
	cmpq	$0, -16(%rbp)
	setne	%al
	xorb	$-1, %al
	andb	$1, %al
	movzbl	%al, %eax
	cltq
	cmpq	$0, %rax
	je	LBB36_5
## %bb.4:
	leaq	L___func__.addString(%rip), %rdi
	leaq	L_.str(%rip), %rsi
	leaq	L_.str.2(%rip), %rcx
	movl	$337, %edx                      ## imm = 0x151
	callq	___assert_rtn
LBB36_5:
	jmp	LBB36_6
LBB36_6:
	movq	-16(%rbp), %rdi
	movl	$4294967294, %esi               ## imm = 0xFFFFFFFE
	callq	_initHeader
	movq	-16(%rbp), %rax
	leaq	_StringVTTemplate(%rip), %rcx
	movq	%rcx, 16(%rax)
	movq	-24(%rbp), %rax
	movq	-16(%rbp), %rcx
	movq	%rax, 24(%rcx)
	movq	-16(%rbp), %rax
	addq	$48, %rsp
	popq	%rbp
	retq
	.cfi_endproc
                                        ## -- End function
	.section	__TEXT,__cstring,cstring_literals
L___func__.newObject:                   ## @__func__.newObject
	.asciz	"newObject"

L_.str:                                 ## @.str
	.asciz	"quack_runtime.c"

L_.str.1:                               ## @.str.1
	.asciz	"newObj"

	.section	__DATA,__data
	.p2align	3                               ## @ObjectVTTemplate
_ObjectVTTemplate:
	.quad	_equalsObject
	.quad	_printObject
	.quad	_destroyObject

	.p2align	3                               ## @Nothing
_Nothing:
	.quad	0                               ## 0x0
	.long	4294967295                      ## 0xffffffff
	.space	4
	.quad	_NothingVTTemplate

	.p2align	3                               ## @True
_True:
	.quad	0                               ## 0x0
	.long	4294967293                      ## 0xfffffffd
	.space	4
	.quad	_BooleanVTTemplate
	.quad	1                               ## 0x1

	.p2align	3                               ## @False
_False:
	.quad	0                               ## 0x0
	.long	4294967293                      ## 0xfffffffd
	.space	4
	.quad	_BooleanVTTemplate
	.quad	0                               ## 0x0

	.section	__TEXT,__cstring,cstring_literals
L___func__.newInteger:                  ## @__func__.newInteger
	.asciz	"newInteger"

	.section	__DATA,__data
	.p2align	3                               ## @IntegerVTTemplate
_IntegerVTTemplate:
	.quad	_equalsInteger
	.quad	_printInteger
	.quad	_destroyObject
	.quad	_addInteger
	.quad	_mulInteger
	.quad	_subInteger
	.quad	_divInteger
	.quad	_modInteger
	.quad	0
	.quad	0
	.quad	0
	.quad	0

	.section	__TEXT,__cstring,cstring_literals
L___func__.newFloat:                    ## @__func__.newFloat
	.asciz	"newFloat"

	.section	__DATA,__data
	.p2align	3                               ## @FloatVTTemplate
_FloatVTTemplate:
	.quad	_equalsFloat
	.quad	_printFloat
	.quad	_destroyObject
	.quad	_addFloat
	.quad	_mulFloat
	.quad	_subFloat
	.quad	_divFloat
	.quad	0
	.quad	0
	.quad	0
	.quad	0

	.section	__TEXT,__cstring,cstring_literals
L___func__.newString:                   ## @__func__.newString
	.asciz	"newString"

L_.str.2:                               ## @.str.2
	.asciz	"newStr"

	.section	__DATA,__data
	.p2align	3                               ## @StringVTTemplate
_StringVTTemplate:
	.quad	_equalsString
	.quad	_printString
	.quad	_destroyString
	.quad	_addString

	.section	__TEXT,__cstring,cstring_literals
L_.str.3:                               ## @.str.3
	.asciz	"<Object at %08lx>\n"

	.section	__DATA,__data
	.p2align	3                               ## @NothingVTTemplate
_NothingVTTemplate:
	.quad	_equalsNothing
	.quad	_printNothing
	.quad	_destroyNothing

	.section	__TEXT,__cstring,cstring_literals
L_.str.4:                               ## @.str.4
	.asciz	"Nothing\n"

	.section	__DATA,__data
	.p2align	3                               ## @BooleanVTTemplate
_BooleanVTTemplate:
	.quad	_equalsBoolean
	.quad	_printBoolean
	.quad	_destroyBoolean

	.section	__TEXT,__cstring,cstring_literals
L_.str.5:                               ## @.str.5
	.asciz	"True\n"

L_.str.6:                               ## @.str.6
	.asciz	"False\n"

L_.str.7:                               ## @.str.7
	.asciz	"%ld\n"

L_.str.8:                               ## @.str.8
	.asciz	"%lf\n"

L_.str.9:                               ## @.str.9
	.asciz	"%s\n"

L___func__.addString:                   ## @__func__.addString
	.asciz	"addString"

L_.str.10:                              ## @.str.10
	.asciz	"ptr"

.subsections_via_symbols
