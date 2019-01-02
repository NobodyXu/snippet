# Register use for syscall
#         syscall_num 1st arg   2nd   3rd   4th   5th   6th
# x86_64     rax        rdi     rsi   rdx   r10   r8    r9    -
mov    %rdi,%rax
mov    %rsi,%rdi
mov    %rdx,%rsi
mov    %rcx,%rdx
mov    %r8,%r10
mov    %r9,%r8
mov    0x8(%rsp),%r9
syscall
cmp    $0xfffffffffffff001,%rax
jae    0x7ffff7b0f902 <syscall+34>
retq
mov    0x2c255f(%rip),%rcx        # 0x7ffff7dd1e68
neg    %eax
mov    %eax,%fs:(%rcx)
or     $0xffffffffffffffff,%rax
retq

