[bits 64]

section .rodata
  door_pk dd 15733400
  card_pk dd 6408062
  fmt db "%ld", 0xA, 0

extern printf

section .text
global main

main:
  push 1
  pop rsi                       ; key in esi := 1
  mov ecx, esi                  ; card_num := 1

  mov ebx, 20201227
  push 7
  pop rdi

  mov ebp, [rel door_pk]
  mov r8d, [rel card_pk]

loop:
  ; key
  mov eax, esi
  mul ebp
  shl rax, 32
  shrd rax, rdx, 32
  xor edx, edx
  div rbx
  mov esi, edx

  ; card_num
  mov eax, ecx
  mul edi
  div ebx
  mov ecx, edx

  cmp ecx, r8d
  jne loop

  ;; done
  ; key is already in rsi
  lea rdi, [rel fmt]
  xor eax, eax
  call printf wrt ..plt

  mov rax, 60                   ; exit
  xor rdi, rdi                  ; =0, exit code
  syscall
