mov    $0x3c,%esi
mov    %esi,%edi
xor    %esi,%esi
mov    %rax,-0x8(%rbp)
mov    $0x0,%al
callq  0x201200 <syscall@plt>
