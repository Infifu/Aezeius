.intel_syntax noprefix
.global gdt_flush

gdt_flush:
    mov eax, [esp+4]
    lgdt [eax]

    mov eax, cr0
    or eax, 1
    mov cr0, eax

    jmp 0x08:start_protected_mode


start_protected_mode:
    mov eax,0x10
    mov ds,ax
    mov es,ax
    mov fs,ax
    mov gs,ax
    mov ss,ax
    ret