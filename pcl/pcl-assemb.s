	.text
	.file	"tomodulo"
	.globl	main                    # -- Begin function main
	.p2align	4, 0x90
	.type	main,@function
main:                                   # @main
	.cfi_startproc
# %bb.0:                                # %entry
	subq	$152, %rsp
	.cfi_def_cfa_offset 160
	leaq	112(%rsp), %rax
	movq	%rax, 112(%rsp)
	movabsq	$2334391967770110279, %rax # imm = 0x20656D2065766947
	movq	%rax, 57(%rsp)
	movabsq	$6998721838492708449, %rax # imm = 0x6120746E69206E61
	movq	%rax, 65(%rsp)
	movw	$25710, 73(%rsp)        # imm = 0x646E
	movabsq	$8027420514964236576, %rax # imm = 0x6F67206D61206920
	movq	%rax, 75(%rsp)
	movl	$543256174, 83(%rsp)    # imm = 0x20616E6E
	movw	$30064, 87(%rsp)        # imm = 0x7570
	movabsq	$2336920844764782708, %rax # imm = 0x206E692074692074
	movq	%rax, 89(%rsp)
	movw	$8289, 97(%rsp)         # imm = 0x2061
	movabsq	$7022850286211392882, %rax # imm = 0x61762D206C616572
	movq	%rax, 99(%rsp)
	movl	$537534578, 107(%rsp)   # imm = 0x200A2072
	movb	$0, 111(%rsp)
	leaq	57(%rsp), %rdi
	callq	writeString
	callq	readInteger
	cwtl
	movl	%eax, 24(%rsp)
	fildl	24(%rsp)
	fstpt	128(%rsp)
	movabsq	$7809634769681344628, %rax # imm = 0x6C61657220656874
	movq	%rax, 30(%rsp)
	movabsq	$8530212558323284256, %rax # imm = 0x76616720756F7920
	movq	%rax, 38(%rsp)
	movabsq	$3327647891583475813, %rax # imm = 0x2E2E2E2073692065
	movq	%rax, 46(%rsp)
	movw	$8238, 54(%rsp)         # imm = 0x202E
	movb	$0, 56(%rsp)
	leaq	30(%rsp), %rdi
	callq	writeString
	fldt	128(%rsp)
	fstpt	(%rsp)
	callq	writeReal
	movw	$10, 22(%rsp)
	leaq	22(%rsp), %rdi
	callq	writeString
	xorl	%eax, %eax
	addq	$152, %rsp
	retq
.Lfunc_end0:
	.size	main, .Lfunc_end0-main
	.cfi_endproc
                                        # -- End function

	.section	".note.GNU-stack","",@progbits
