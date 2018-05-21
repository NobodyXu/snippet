	.text
	.file	"multiple_inheritence.cc"
	.section	.text.startup,"ax",@progbits
	.p2align	4, 0x90         # -- Begin function __cxx_global_var_init
	.type	__cxx_global_var_init,@function
__cxx_global_var_init:                  # @__cxx_global_var_init
	.cfi_startproc
# %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	subq	$16, %rsp
	movabsq	$_ZStL8__ioinit, %rdi
	callq	_ZNSt8ios_base4InitC1Ev
	movabsq	$_ZNSt8ios_base4InitD1Ev, %rdi
	movabsq	$_ZStL8__ioinit, %rsi
	movabsq	$__dso_handle, %rdx
	callq	__cxa_atexit
	movl	%eax, -4(%rbp)          # 4-byte Spill
	addq	$16, %rsp
	popq	%rbp
	retq
.Lfunc_end0:
	.size	__cxx_global_var_init, .Lfunc_end0-__cxx_global_var_init
	.cfi_endproc
                                        # -- End function
	.text
	.globl	_ZlsRSo18auto_start_newline # -- Begin function _ZlsRSo18auto_start_newline
	.p2align	4, 0x90
	.type	_ZlsRSo18auto_start_newline,@function
_ZlsRSo18auto_start_newline:            # @_ZlsRSo18auto_start_newline
	.cfi_startproc
# %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	subq	$16, %rsp
	movq	%rsi, -8(%rbp)
	movq	%rdi, -16(%rbp)
	movq	-16(%rbp), %rdi
	movq	-8(%rbp), %rsi
	callq	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc
	movabsq	$_ZSt4endlIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_, %rsi
	movq	%rax, %rdi
	callq	_ZNSolsEPFRSoS_E
	addq	$16, %rsp
	popq	%rbp
	retq
.Lfunc_end1:
	.size	_ZlsRSo18auto_start_newline, .Lfunc_end1-_ZlsRSo18auto_start_newline
	.cfi_endproc
                                        # -- End function
	.globl	main                    # -- Begin function main
	.p2align	4, 0x90
	.type	main,@function
main:                                   # @main
	.cfi_startproc
# %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	subq	$176, %rsp
	leaq	-24(%rbp), %rdi
	movl	$0, -4(%rbp)
	callq	_ZN1CC2Ev
	xorl	%eax, %eax
	movl	%eax, %edi
	leaq	-24(%rbp), %rcx
	movq	%rcx, %rdx
	movq	%rdx, -32(%rbp)
	cmpq	$0, %rcx
	movq	%rdi, -120(%rbp)        # 8-byte Spill
	je	.LBB2_2
# %bb.1:
	leaq	-24(%rbp), %rax
	addq	$8, %rax
	movq	%rax, -120(%rbp)        # 8-byte Spill
.LBB2_2:
	movq	-120(%rbp), %rax        # 8-byte Reload
	movabsq	$_ZSt4cout, %rdi
	movabsq	$.L.str, %rsi
	leaq	-24(%rbp), %rcx
	movq	%rax, -40(%rbp)
	movq	%rcx, -48(%rbp)
	movq	-48(%rbp), %rax
	movq	%rax, -56(%rbp)
	movq	-48(%rbp), %rax
	addq	$8, %rax
	movq	%rax, -64(%rbp)
	callq	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc
	movl	$16, %edx
	movl	%edx, %esi
	movq	%rax, %rdi
	callq	_ZNSolsEm
	movabsq	$_ZSt4endlIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_, %rsi
	movq	%rax, %rdi
	callq	_ZNSolsEPFRSoS_E
	movq	-32(%rbp), %rcx
	movq	(%rcx), %rsi
	movq	%rcx, %rdi
	movq	%rax, -128(%rbp)        # 8-byte Spill
	callq	*(%rsi)
	movq	%rax, -72(%rbp)
	movq	-72(%rbp), %rsi
	movq	-128(%rbp), %rdi        # 8-byte Reload
	callq	_ZlsRSo18auto_start_newline
	movq	-40(%rbp), %rcx
	movq	(%rcx), %rsi
	movq	%rcx, %rdi
	movq	%rax, -136(%rbp)        # 8-byte Spill
	callq	*(%rsi)
	movq	%rax, -80(%rbp)
	movq	-80(%rbp), %rsi
	movq	-136(%rbp), %rdi        # 8-byte Reload
	callq	_ZlsRSo18auto_start_newline
	movq	-48(%rbp), %rcx
	movq	(%rcx), %rsi
	movq	%rcx, %rdi
	movq	%rax, -144(%rbp)        # 8-byte Spill
	callq	*(%rsi)
	movq	%rax, -88(%rbp)
	movq	-88(%rbp), %rsi
	movq	-144(%rbp), %rdi        # 8-byte Reload
	callq	_ZlsRSo18auto_start_newline
	movq	-48(%rbp), %rcx
	movq	(%rcx), %rsi
	movq	%rcx, %rdi
	movq	%rax, -152(%rbp)        # 8-byte Spill
	callq	*8(%rsi)
	movq	%rax, -96(%rbp)
	movq	-96(%rbp), %rsi
	movq	-152(%rbp), %rdi        # 8-byte Reload
	callq	_ZlsRSo18auto_start_newline
	movq	-48(%rbp), %rcx
	movq	(%rcx), %rsi
	movq	%rcx, %rdi
	movq	%rax, -160(%rbp)        # 8-byte Spill
	callq	*16(%rsi)
	movq	%rax, -104(%rbp)
	movq	-104(%rbp), %rsi
	movq	-160(%rbp), %rdi        # 8-byte Reload
	callq	_ZlsRSo18auto_start_newline
	movq	-56(%rbp), %rcx
	movq	(%rcx), %rcx
	movq	-48(%rbp), %rsi
	movq	%rsi, %rdi
	movq	%rax, -168(%rbp)        # 8-byte Spill
	callq	*%rcx
	movq	%rax, -112(%rbp)
	movq	-112(%rbp), %rsi
	movq	-168(%rbp), %rdi        # 8-byte Reload
	callq	_ZlsRSo18auto_start_newline
	movl	-4(%rbp), %edx
	movq	%rax, -176(%rbp)        # 8-byte Spill
	movl	%edx, %eax
	addq	$176, %rsp
	popq	%rbp
	retq
.Lfunc_end2:
	.size	main, .Lfunc_end2-main
	.cfi_endproc
                                        # -- End function
	.section	.text._ZN1CC2Ev,"axG",@progbits,_ZN1CC2Ev,comdat
	.weak	_ZN1CC2Ev               # -- Begin function _ZN1CC2Ev
	.p2align	4, 0x90
	.type	_ZN1CC2Ev,@function
_ZN1CC2Ev:                              # @_ZN1CC2Ev
	.cfi_startproc
# %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rdi
	movq	%rdi, %rax
	movq	%rdi, -16(%rbp)         # 8-byte Spill
	movq	%rax, %rdi
	callq	_ZN1AC2Ev
	movq	-16(%rbp), %rax         # 8-byte Reload
	addq	$8, %rax
	movq	%rax, %rdi
	callq	_ZN1BC2Ev
	movabsq	$_ZTV1C, %rax
	movq	%rax, %rdi
	addq	$56, %rdi
	addq	$16, %rax
	movq	-16(%rbp), %rcx         # 8-byte Reload
	movq	%rax, (%rcx)
	movq	%rdi, 8(%rcx)
	addq	$16, %rsp
	popq	%rbp
	retq
.Lfunc_end3:
	.size	_ZN1CC2Ev, .Lfunc_end3-_ZN1CC2Ev
	.cfi_endproc
                                        # -- End function
	.section	.text._ZN1AC2Ev,"axG",@progbits,_ZN1AC2Ev,comdat
	.weak	_ZN1AC2Ev               # -- Begin function _ZN1AC2Ev
	.p2align	4, 0x90
	.type	_ZN1AC2Ev,@function
_ZN1AC2Ev:                              # @_ZN1AC2Ev
	.cfi_startproc
# %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	movabsq	$_ZTV1A, %rax
	addq	$16, %rax
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rdi
	movq	%rax, (%rdi)
	popq	%rbp
	retq
.Lfunc_end4:
	.size	_ZN1AC2Ev, .Lfunc_end4-_ZN1AC2Ev
	.cfi_endproc
                                        # -- End function
	.section	.text._ZN1BC2Ev,"axG",@progbits,_ZN1BC2Ev,comdat
	.weak	_ZN1BC2Ev               # -- Begin function _ZN1BC2Ev
	.p2align	4, 0x90
	.type	_ZN1BC2Ev,@function
_ZN1BC2Ev:                              # @_ZN1BC2Ev
	.cfi_startproc
# %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	movabsq	$_ZTV1B, %rax
	addq	$16, %rax
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rdi
	movq	%rax, (%rdi)
	popq	%rbp
	retq
.Lfunc_end5:
	.size	_ZN1BC2Ev, .Lfunc_end5-_ZN1BC2Ev
	.cfi_endproc
                                        # -- End function
	.section	.text._ZNK1C2F1Ev,"axG",@progbits,_ZNK1C2F1Ev,comdat
	.weak	_ZNK1C2F1Ev             # -- Begin function _ZNK1C2F1Ev
	.p2align	4, 0x90
	.type	_ZNK1C2F1Ev,@function
_ZNK1C2F1Ev:                            # @_ZNK1C2F1Ev
	.cfi_startproc
# %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	movabsq	$.L__PRETTY_FUNCTION__._ZNK1C2F1Ev, %rax
	movq	%rdi, -16(%rbp)
	movq	%rax, -8(%rbp)
	movq	-8(%rbp), %rax
	popq	%rbp
	retq
.Lfunc_end6:
	.size	_ZNK1C2F1Ev, .Lfunc_end6-_ZNK1C2F1Ev
	.cfi_endproc
                                        # -- End function
	.section	.text._ZNK1C2F2Ev,"axG",@progbits,_ZNK1C2F2Ev,comdat
	.weak	_ZNK1C2F2Ev             # -- Begin function _ZNK1C2F2Ev
	.p2align	4, 0x90
	.type	_ZNK1C2F2Ev,@function
_ZNK1C2F2Ev:                            # @_ZNK1C2F2Ev
	.cfi_startproc
# %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	movabsq	$.L__PRETTY_FUNCTION__._ZNK1C2F2Ev, %rax
	movq	%rdi, -16(%rbp)
	movq	%rax, -8(%rbp)
	movq	-8(%rbp), %rax
	popq	%rbp
	retq
.Lfunc_end7:
	.size	_ZNK1C2F2Ev, .Lfunc_end7-_ZNK1C2F2Ev
	.cfi_endproc
                                        # -- End function
	.section	.text._ZNK1C2F3Ev,"axG",@progbits,_ZNK1C2F3Ev,comdat
	.weak	_ZNK1C2F3Ev             # -- Begin function _ZNK1C2F3Ev
	.p2align	4, 0x90
	.type	_ZNK1C2F3Ev,@function
_ZNK1C2F3Ev:                            # @_ZNK1C2F3Ev
	.cfi_startproc
# %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	movabsq	$.L__PRETTY_FUNCTION__._ZNK1C2F3Ev, %rax
	movq	%rdi, -16(%rbp)
	movq	%rax, -8(%rbp)
	movq	-8(%rbp), %rax
	popq	%rbp
	retq
.Lfunc_end8:
	.size	_ZNK1C2F3Ev, .Lfunc_end8-_ZNK1C2F3Ev
	.cfi_endproc
                                        # -- End function
	.section	.text._ZThn8_NK1C2F2Ev,"axG",@progbits,_ZThn8_NK1C2F2Ev,comdat
	.weak	_ZThn8_NK1C2F2Ev        # -- Begin function _ZThn8_NK1C2F2Ev
	.p2align	4, 0x90
	.type	_ZThn8_NK1C2F2Ev,@function
_ZThn8_NK1C2F2Ev:                       # @_ZThn8_NK1C2F2Ev
	.cfi_startproc
# %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	subq	$32, %rsp
	movq	%rdi, -16(%rbp)
	movq	-16(%rbp), %rdi
	addq	$-8, %rdi
	callq	_ZNK1C2F2Ev
	movq	%rax, -24(%rbp)
	movq	-24(%rbp), %rax
	movq	%rax, -8(%rbp)
	movq	-8(%rbp), %rax
	addq	$32, %rsp
	popq	%rbp
	retq
.Lfunc_end9:
	.size	_ZThn8_NK1C2F2Ev, .Lfunc_end9-_ZThn8_NK1C2F2Ev
	.cfi_endproc
                                        # -- End function
	.section	.text._ZNK1A2F1Ev,"axG",@progbits,_ZNK1A2F1Ev,comdat
	.weak	_ZNK1A2F1Ev             # -- Begin function _ZNK1A2F1Ev
	.p2align	4, 0x90
	.type	_ZNK1A2F1Ev,@function
_ZNK1A2F1Ev:                            # @_ZNK1A2F1Ev
	.cfi_startproc
# %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	movabsq	$.L__PRETTY_FUNCTION__._ZNK1A2F1Ev, %rax
	movq	%rdi, -16(%rbp)
	movq	%rax, -8(%rbp)
	movq	-8(%rbp), %rax
	popq	%rbp
	retq
.Lfunc_end10:
	.size	_ZNK1A2F1Ev, .Lfunc_end10-_ZNK1A2F1Ev
	.cfi_endproc
                                        # -- End function
	.section	.text._ZNK1B2F2Ev,"axG",@progbits,_ZNK1B2F2Ev,comdat
	.weak	_ZNK1B2F2Ev             # -- Begin function _ZNK1B2F2Ev
	.p2align	4, 0x90
	.type	_ZNK1B2F2Ev,@function
_ZNK1B2F2Ev:                            # @_ZNK1B2F2Ev
	.cfi_startproc
# %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	movabsq	$.L__PRETTY_FUNCTION__._ZNK1B2F2Ev, %rax
	movq	%rdi, -16(%rbp)
	movq	%rax, -8(%rbp)
	movq	-8(%rbp), %rax
	popq	%rbp
	retq
.Lfunc_end11:
	.size	_ZNK1B2F2Ev, .Lfunc_end11-_ZNK1B2F2Ev
	.cfi_endproc
                                        # -- End function
	.section	.text.startup,"ax",@progbits
	.p2align	4, 0x90         # -- Begin function _GLOBAL__sub_I_multiple_inheritence.cc
	.type	_GLOBAL__sub_I_multiple_inheritence.cc,@function
_GLOBAL__sub_I_multiple_inheritence.cc: # @_GLOBAL__sub_I_multiple_inheritence.cc
	.cfi_startproc
# %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	callq	__cxx_global_var_init
	popq	%rbp
	retq
.Lfunc_end12:
	.size	_GLOBAL__sub_I_multiple_inheritence.cc, .Lfunc_end12-_GLOBAL__sub_I_multiple_inheritence.cc
	.cfi_endproc
                                        # -- End function
	.type	_ZStL8__ioinit,@object  # @_ZStL8__ioinit
	.local	_ZStL8__ioinit
	.comm	_ZStL8__ioinit,1,1
	.hidden	__dso_handle
	.type	.L.str,@object          # @.str
	.section	.rodata.str1.1,"aMS",@progbits,1
.L.str:
	.asciz	"sizeof(C) = "
	.size	.L.str, 13

	.type	_ZTV1C,@object          # @_ZTV1C
	.section	.rodata._ZTV1C,"aG",@progbits,_ZTV1C,comdat
	.weak	_ZTV1C
	.p2align	3
_ZTV1C:
	.quad	0
	.quad	_ZTI1C
	.quad	_ZNK1C2F1Ev
	.quad	_ZNK1C2F2Ev
	.quad	_ZNK1C2F3Ev
	.quad	-8
	.quad	_ZTI1C
	.quad	_ZThn8_NK1C2F2Ev
	.size	_ZTV1C, 64

	.type	_ZTS1C,@object          # @_ZTS1C
	.section	.rodata._ZTS1C,"aG",@progbits,_ZTS1C,comdat
	.weak	_ZTS1C
_ZTS1C:
	.asciz	"1C"
	.size	_ZTS1C, 3

	.type	_ZTS1A,@object          # @_ZTS1A
	.section	.rodata._ZTS1A,"aG",@progbits,_ZTS1A,comdat
	.weak	_ZTS1A
_ZTS1A:
	.asciz	"1A"
	.size	_ZTS1A, 3

	.type	_ZTI1A,@object          # @_ZTI1A
	.section	.rodata._ZTI1A,"aG",@progbits,_ZTI1A,comdat
	.weak	_ZTI1A
	.p2align	3
_ZTI1A:
	.quad	_ZTVN10__cxxabiv117__class_type_infoE+16
	.quad	_ZTS1A
	.size	_ZTI1A, 16

	.type	_ZTS1B,@object          # @_ZTS1B
	.section	.rodata._ZTS1B,"aG",@progbits,_ZTS1B,comdat
	.weak	_ZTS1B
_ZTS1B:
	.asciz	"1B"
	.size	_ZTS1B, 3

	.type	_ZTI1B,@object          # @_ZTI1B
	.section	.rodata._ZTI1B,"aG",@progbits,_ZTI1B,comdat
	.weak	_ZTI1B
	.p2align	3
_ZTI1B:
	.quad	_ZTVN10__cxxabiv117__class_type_infoE+16
	.quad	_ZTS1B
	.size	_ZTI1B, 16

	.type	_ZTI1C,@object          # @_ZTI1C
	.section	.rodata._ZTI1C,"aG",@progbits,_ZTI1C,comdat
	.weak	_ZTI1C
	.p2align	4
_ZTI1C:
	.quad	_ZTVN10__cxxabiv121__vmi_class_type_infoE+16
	.quad	_ZTS1C
	.long	0                       # 0x0
	.long	2                       # 0x2
	.quad	_ZTI1A
	.quad	2                       # 0x2
	.quad	_ZTI1B
	.quad	2050                    # 0x802
	.size	_ZTI1C, 56

	.type	_ZTV1A,@object          # @_ZTV1A
	.section	.rodata._ZTV1A,"aG",@progbits,_ZTV1A,comdat
	.weak	_ZTV1A
	.p2align	3
_ZTV1A:
	.quad	0
	.quad	_ZTI1A
	.quad	_ZNK1A2F1Ev
	.size	_ZTV1A, 24

	.type	.L__PRETTY_FUNCTION__._ZNK1A2F1Ev,@object # @__PRETTY_FUNCTION__._ZNK1A2F1Ev
	.section	.rodata.str1.1,"aMS",@progbits,1
.L__PRETTY_FUNCTION__._ZNK1A2F1Ev:
	.asciz	"virtual auto_start_newline A::F1() const"
	.size	.L__PRETTY_FUNCTION__._ZNK1A2F1Ev, 41

	.type	_ZTV1B,@object          # @_ZTV1B
	.section	.rodata._ZTV1B,"aG",@progbits,_ZTV1B,comdat
	.weak	_ZTV1B
	.p2align	3
_ZTV1B:
	.quad	0
	.quad	_ZTI1B
	.quad	_ZNK1B2F2Ev
	.size	_ZTV1B, 24

	.type	.L__PRETTY_FUNCTION__._ZNK1B2F2Ev,@object # @__PRETTY_FUNCTION__._ZNK1B2F2Ev
	.section	.rodata.str1.1,"aMS",@progbits,1
.L__PRETTY_FUNCTION__._ZNK1B2F2Ev:
	.asciz	"virtual auto_start_newline B::F2() const"
	.size	.L__PRETTY_FUNCTION__._ZNK1B2F2Ev, 41

	.type	.L__PRETTY_FUNCTION__._ZNK1C2F1Ev,@object # @__PRETTY_FUNCTION__._ZNK1C2F1Ev
.L__PRETTY_FUNCTION__._ZNK1C2F1Ev:
	.asciz	"virtual auto_start_newline C::F1() const"
	.size	.L__PRETTY_FUNCTION__._ZNK1C2F1Ev, 41

	.type	.L__PRETTY_FUNCTION__._ZNK1C2F2Ev,@object # @__PRETTY_FUNCTION__._ZNK1C2F2Ev
.L__PRETTY_FUNCTION__._ZNK1C2F2Ev:
	.asciz	"virtual auto_start_newline C::F2() const"
	.size	.L__PRETTY_FUNCTION__._ZNK1C2F2Ev, 41

	.type	.L__PRETTY_FUNCTION__._ZNK1C2F3Ev,@object # @__PRETTY_FUNCTION__._ZNK1C2F3Ev
.L__PRETTY_FUNCTION__._ZNK1C2F3Ev:
	.asciz	"virtual auto_start_newline C::F3() const"
	.size	.L__PRETTY_FUNCTION__._ZNK1C2F3Ev, 41

	.section	.init_array,"aw",@init_array
	.p2align	3
	.quad	_GLOBAL__sub_I_multiple_inheritence.cc

	.ident	"clang version 6.0.0 (tags/RELEASE_600/final)"
	.section	".note.GNU-stack","",@progbits
