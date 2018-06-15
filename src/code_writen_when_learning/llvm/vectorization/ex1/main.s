	.text
	.file	"main.cc"
	.section	.rodata.cst16,"aM",@progbits,16
	.p2align	4               # -- Begin function _Z3fooPiS_i
.LCPI0_0:
	.long	5                       # 0x5
	.long	5                       # 0x5
	.long	5                       # 0x5
	.long	5                       # 0x5
	.text
	.globl	_Z3fooPiS_i
	.p2align	4, 0x90
	.type	_Z3fooPiS_i,@function
_Z3fooPiS_i:                            # @_Z3fooPiS_i
	.cfi_startproc
# BB#0:
                                        # kill: %EDX<def> %EDX<kill> %RDX<def>
	testl	%edx, %edx
	jle	.LBB0_1
# BB#2:
	movl	%edx, %r9d
	cmpl	$7, %edx
	ja	.LBB0_7
# BB#3:
	xorl	%r8d, %r8d
	xorl	%eax, %eax
	jmp	.LBB0_4
.LBB0_1:
	xorl	%eax, %eax
	retq
.LBB0_7:
	andl	$7, %edx
	movq	%r9, %r8
	subq	%rdx, %r8
	leaq	16(%rdi), %rax
	leaq	16(%rsi), %rcx
	pxor	%xmm0, %xmm0
	movdqa	.LCPI0_0(%rip), %xmm2   # xmm2 = [5,5,5,5]
	movq	%r8, %r10
	pxor	%xmm1, %xmm1
	.p2align	4, 0x90
.LBB0_8:                                # =>This Inner Loop Header: Depth=1
	movdqu	-16(%rax), %xmm3
	movdqu	(%rax), %xmm4
	movdqu	-16(%rcx), %xmm5
	movdqu	(%rcx), %xmm6
	movdqa	%xmm3, %xmm7
	pcmpgtd	%xmm5, %xmm7
	movdqa	%xmm4, %xmm5
	pcmpgtd	%xmm6, %xmm5
	paddd	%xmm2, %xmm3
	pand	%xmm7, %xmm3
	paddd	%xmm3, %xmm0
	paddd	%xmm2, %xmm4
	pand	%xmm5, %xmm4
	paddd	%xmm4, %xmm1
	addq	$32, %rax
	addq	$32, %rcx
	addq	$-8, %r10
	jne	.LBB0_8
# BB#9:
	paddd	%xmm0, %xmm1
	pshufd	$78, %xmm1, %xmm0       # xmm0 = xmm1[2,3,0,1]
	paddd	%xmm1, %xmm0
	pshufd	$229, %xmm0, %xmm1      # xmm1 = xmm0[1,1,2,3]
	paddd	%xmm0, %xmm1
	movd	%xmm1, %eax
	testl	%edx, %edx
	je	.LBB0_10
.LBB0_4:
	leaq	(%rdi,%r8,4), %rcx
	leaq	(%rsi,%r8,4), %rdx
	subq	%r8, %r9
	.p2align	4, 0x90
.LBB0_5:                                # =>This Inner Loop Header: Depth=1
	movl	(%rcx), %esi
	cmpl	(%rdx), %esi
	jg	.LBB0_6
# BB#11:                                #   in Loop: Header=BB0_5 Depth=1
	xorl	%esi, %esi
	jmp	.LBB0_12
	.p2align	4, 0x90
.LBB0_6:                                #   in Loop: Header=BB0_5 Depth=1
	addl	$5, %esi
.LBB0_12:                               #   in Loop: Header=BB0_5 Depth=1
	addl	%esi, %eax
	addq	$4, %rcx
	addq	$4, %rdx
	decq	%r9
	jne	.LBB0_5
.LBB0_10:
	retq
.Lfunc_end0:
	.size	_Z3fooPiS_i, .Lfunc_end0-_Z3fooPiS_i
	.cfi_endproc
                                        # -- End function

	.ident	"clang version 5.0.2-svn328729-1~exp1~20180406211310.92 (branches/release_50)"
	.section	".note.GNU-stack","",@progbits
