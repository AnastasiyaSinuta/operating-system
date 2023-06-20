section .data
    not_vm_msg db "Not a virtual machine", 0x0A
    in_vm_msg db "Virtual Machine", 0x0A

section .text
    global _start

_start:
    ; Проверяем значение регистра EFLAGS для определения виртуальной машины
    mov eax, 1
    cpuid
    test ecx, 0x80000000 ; Проверяем бит "Virtual Machine Extensions"
    jz not_in_vm ; Если бит не установлен, переходим к not_in_vm
    
    ; Бит установлен, значит, это виртуальная машина
    mov eax, 4 ; Системный вызов для вывода в терминал
    mov ebx, 1 ; Файловый дескриптор стандартного вывода (stdout)
    mov ecx, in_vm_msg ; Указатель на сообщение
    mov edx, 18 ; Длина сообщения
    int 0x80 ; Вызов системного вызова
    jmp exit

    not_in_vm:
    ; Бит не установлен, значит, это не виртуальная машина
    mov eax, 4
    mov ebx, 1
    mov ecx, not_vm_msg
    mov edx, 19
    int 0x80

    exit:
    ; Выход из программы
    mov eax, 1 ; Системный вызов для выхода из программы
    xor ebx, ebx
    int 0x80