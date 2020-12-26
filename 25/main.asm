[bits 64]

door_pk equ 15733400
card_pk equ 6408062

section .text
global main

main:
  push 1
  pop rsi                       ; key in esi := 1
  mov ecx, esi                  ; card_num := 1

  mov ebx, 20201227             ; two more constants
  push 7
  pop rdi

  mov ebp, door_pk              ; public keys from the task
  mov r8d, card_pk

loop:

;; key
  mov eax, esi                  ; prep for mul
  mul ebp                       ; now we have 64 bit in edx:eax
  shl rax, 32                   ; rax = edx << 32 + eax
  shrd rax, rdx, 32             ; ^
  xor edx, edx                  ; div will use rdx:rax as 128 bit divident
  div rbx
  mov esi, edx                  ; esi is the remainder now

;; card_num
  mov eax, ecx                  ; prep for mul
  mul edi                       ; * 7
  div ebx                       ; key*7 never gets to 128 bit, so it's safe
  mov ecx, edx                  ; ecx is the remainder now

  cmp ecx, r8d                  ; loop end condition
  jne loop

;; done, key in esi
  mov eax, esi                  ; number to print

  push 0xa                      ; base
  pop rcx                       ; EOL=base=0A
  push rcx                      ; we have 0A in ECX and on stack
  mov rsi, rsp                  ; rsi points to EOL, we'll add characters there

digit:
  xor edx, edx
  div ecx                       ; edx - remainder, least significant digit
  add edx, '0'                  ; chr(code)
  dec rsi                       ; moving in reverse to print digits from left to right
  mov [rsi], dl

  test eax, eax
  jnz digit

;; done, string is pointed by rsi
  inc eax                       ; eax = 0 after loop, now 1 -> syswrite id
  mov edi, eax                  ; 1 -> stdout
  lea edx, [rsp+rdi]            ; rdi = 1, so pointer to pushed EOL
  sub edx, esi                  ; len = end - start
  syscall

  push 60                       ; 60=exit
  pop rax
  xor edi, edi                  ; =0, exit code
  syscall
