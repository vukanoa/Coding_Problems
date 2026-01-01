// This is an Assembly-Solution that works in O(N^2)


/**
 * Note: The returned array must be malloced, assume caller calls free().
 */

/*
Arguments order:
RDI
RSI
RDX
RCX

RAX - return value
*/

__attribute__((naked)) int* twoSum(int* nums, int numsSize, int target, int* returnSize)
{
    __asm__(".intel_syntax noprefix;\
    /* create a stack */;\
    push rbx;\
    sub rsp, 0x40;\
    ;\
    /* store our parameters onto the stack */;\
    mov qword ptr [rsp + 0x10], rdi;\
    mov dword ptr [rsp + 0x18], esi;\
    mov dword ptr [rsp + 0x20], edx;\
    mov qword ptr [rsp + 0x28], rcx;\
    ;\
    /* malloc memory for our answer */;\
    mov rdi, 8;\
    call malloc;\
    mov qword ptr [rsp + 0x30], rax;\
    ;\
    /* outerloop iterate over all numbers */;\
    xor r8, r8;\
    outerloop%=:\
    ;\
    /* innerloop iterate over the other numbers */;\
    mov r9, r8;\
    add r9, 1;\
    innerloop%=:\
    mov rbx, qword ptr [rsp + 0x10];\
    xor rax, rax;\
    lea rbx, [rbx + r8 * 4];\
    add eax, dword ptr[rbx];\
    mov rbx, qword ptr[rsp + 0x10];\
    lea rbx, [rbx + r9 * 4];\
    add eax, dword ptr[rbx];\
    mov ebx, dword ptr[rsp + 0x20];\
    ;\
    /* if the sum equals the target, store and leave */;\
    cmp ebx, eax;\
    jne continue%=;\
    mov rax, qword ptr [rsp + 0x30];\
    mov dword ptr [rax], r8d;\
    lea rax, [rax + 4];\
    mov dword ptr [rax], r9d;\
    mov rax, qword ptr [rsp + 0x28];\
    mov dword ptr [rax], 0x2;\
    jmp leave%=;\
    continue%=:\
    inc r9;\
    cmp r9d, dword ptr[rsp + 0x18];\
    jle innerloop%=;\
    inc r8;\
    cmp r8d, dword ptr[rsp + 0x18];\
    jle outerloop%=;\
    ;\
    /* clean our stack and leave */;\
    leave%=:\
    mov rax, qword ptr[rsp + 0x30];\
    add rsp, 0x40;\
    pop rbx;\
    ret;\
    .att_syntax;" : :);
}

