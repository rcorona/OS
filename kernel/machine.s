;Rodolfo Corona Rodriguez
;
;machine.s
;
;Contains source code for assembly operations. 

[BITS 32]

[GLOBAL outb]
;void outb(uint16_t port, uint8_t value)
outb:
	mov edx, [esp + 4]		;port
	mov eax, [esp + 8]		;value

	out dx, al				;writes value to port. 

	ret 					;returns


[GLOBAL inb]
;uint8_t inb(uint16_t port)
inb:
	mov edx, [esp + 4]		;port

	in al, dx				;Reads value from port into %al

	ret

[GLOBAL inw]
;uint16_t inw(uint16_t port)
inw:
	mov edx, [esp + 4]

	in ax, dx				;Reads value from port into ax

	ret

[GLOBAL gdt_flush]
[EXTERN gdtPtr]
;void gdt_flush()
gdt_flush:
	lgdt [gdtPtr]			;Load GDTR with 16-bit limit and 32-bit base
							;(in gdtPTR). NOTE: GDTR is 48-bits long. 
	
	mov ax, 0x10			;0x10 is the offset in the GDT to data segment entry.
	mov ds, ax				;Segment selector uses first 3 bits for the table
	mov es, ax				;indicator and the requested privilage level. 
	mov fs, ax				;Therefore the gdt index for the segment entry starts
	mov gs, ax				;in the fourth bit. 
	mov ss, ax				;So 0x10 => GDT[2] NOTE: GDT[0] = NULL DESCRIPTOR

	jmp 0x08 : flush		;0x08 holds offset in GDT to code segment entry. 
							;flush is offset within code segment to which we
							;want to jump to. This implies that the code
							;segment is switched to ours. 0x8 => GDT[1]

flush:
	ret						;returns to C code.

[GLOBAL idt_load]
[EXTERN idtPtr]
;void idt_load()
idt_load:
	lidt [idtPtr]			;Loads IDTR with 16-bit limit and 32-bit base. 
	ret

[GLOBAL memset]
;void *memset(void *ptr, int val, size_t num)
memset:
	mov eax, [esp + 4]		;ptr
	mov ecx, [esp + 8]		;val
	mov edx, [esp + 12]		;num
	
	push eax				;Stores value to return. 

memsetLoop:
	cmp edx, 0				;Checks to see if we're done.

	jle memsetDone
	
	mov [eax], cl
	add eax, 1
	add edx, -1

	jmp memsetLoop

memsetDone:
	pop eax					;Retrieves original value to be returned. 
	ret

;IRQ routines. 

;Division by 0 exception. 
[GLOBAL isr0]
isr0:
	cli
	
	push byte 0					;Dummy error code. 
	push byte 0
	
	jmp isr_common

;Debug Exception. 
[GLOBAL isr1]
isr1:
	cli
	
	push byte 0
	push byte 1

	jmp isr_common

;Non Maskable Interrupt Exception. 
[GLOBAL isr2]
isr2:
	cli

	push byte 0
	push byte 2

	jmp isr_common

;Breakpoint Exception. 
[GLOBAL isr3]
isr3:
	cli

	push byte 0
	push byte 3

	jmp isr_common

;INTO detected overflow exception. 
[GLOBAL isr4]
isr4:
	cli

	push byte 0
	push byte 4

	jmp isr_common

;Out of bounds exception. 
[GLOBAL isr5]
isr5:
	cli

	push byte 0
	push byte 5

	jmp isr_common

;Invalid opcode exception. 
[GLOBAL isr6]
isr6:
	cli

	push byte 0
	push byte 6

	jmp isr_common

;No coprocessor exception. 
[GLOBAL isr7]
isr7:
	cli

	push byte 0
	push byte 7

	jmp isr_common

;Double Fault exception. 
[GLOBAL isr8]
isr8:
	cli

	push byte 8			;No dummy pushed since an error code will already have been
						;pushed here. 

	jmp isr_common

;Coprocessor segment overrun exception. 
[GLOBAL isr9]
isr9:
	cli

	push byte 0
	push byte 9

	jmp isr_common

;Bad TSS exception. 
[GLOBAL isr10]
isr10:
	cli

	push byte 10

	jmp isr_common

;Segment not present exception. 
[GLOBAL isr11]
isr11:
	cli

	push byte 11

	jmp isr_common

;Stack fault exception. 
[GLOBAL isr12]
isr12:
	cli

	push byte 12

	jmp isr_common

;General protection fault exception. 
[GLOBAL isr13]
isr13:
	cli

	push byte 13

	jmp isr_common

;Page fault exception. 
[GLOBAL isr14]
isr14:
	cli

	push byte 14

	jmp isr_common

;Unknown interrupt exception. 
[GLOBAL isr15]
isr15:
	cli

	push byte 0
	push byte 15

	jmp isr_common

;Coprocessor fault exception. 
[GLOBAL isr16]
isr16:
	cli 

	push byte 0
	push byte 16

	jmp isr_common

;Alignment Check exception (486+)
[GLOBAL isr17]
isr17:
	cli 
	push byte 0
	push byte 17

	jmp isr_common

;Machine check exception (Pentium/586+)
[GLOBAL isr18]
isr18:
	cli
	
	push byte 0
	push byte 18

	jmp isr_common

;19 - 31 are reserved exceptions. 
[GLOBAL isr19]
isr19:
	cli

	push byte 0
	push byte 19

	jmp isr_common

[GLOBAL isr20]
isr20:
	cli

	push byte 0
	push byte 20

	jmp isr_common

[GLOBAL isr21]
isr21:
	cli 

	push byte 0
	push byte 21

	jmp isr_common

[GLOBAL isr22]
isr22:
	cli

	push byte 0
	push byte 22
	
	jmp isr_common

[GLOBAL isr23]
isr23:
	cli

	push byte 0
	push byte 23

	jmp isr_common

[GLOBAL isr24]
isr24:
	cli

	push byte 0
	push byte 24

	jmp isr_common

[GLOBAL isr25]
isr25:
	cli

	push byte 0
	push byte 25

	jmp isr_common

[GLOBAL isr26]
isr26:
	cli

	push byte 0
	push byte 26

	jmp isr_common

[GLOBAL isr27]
isr27:
	cli

	push byte 0
	push byte 27

	jmp isr_common

[GLOBAL isr28]
isr28:
	cli

	push byte 0
	push byte 28

	jmp isr_common

[GLOBAL isr29]
isr29:
	cli

	push byte 0
	push byte 29

	jmp isr_common

[GLOBAL isr30]
isr30:
	cli

	push byte 0
	push byte 30

	jmp isr_common

[GLOBAL isr31]
isr31:
	cli

	push byte 0
	push byte 31

	jmp isr_common

[EXTERN fault_handler]
;Saves processor state and sets up kernel mode segments. 
;Then calls fault handler and then restores stack frame.
isr_common:
	pusha
	push ds
	push es
	push fs
	push gs

	mov ax, 0x10		;Kernel DS segment descriptor. 
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax

	mov eax, esp
	push eax

	mov eax, fault_handler
	call eax

	pop eax

	pop gs
	pop fs
	pop es
	pop ds
	popa

	add esp, 8			;"pops" error code and ISR number. 
	
	sti					;Re-enables interrupts. 
	iret

[GLOBAL irq0]
irq0:
	cli 

	push byte 0			;Push dummy error code onto stack. 

	push byte 32		;IRQs will be mapped to IDT entries 32-47

	jmp irq_common

[GLOBAL irq1]
irq1:
	cli

	push byte 0

	push byte 33

	jmp irq_common

[GLOBAL irq2]
irq2:
	cli

	push byte 0

	push byte 34

	jmp irq_common


[GLOBAL irq3]
irq3:
	cli

	push byte 0

	push byte 35

	jmp irq_common


[GLOBAL irq4]
irq4:
	cli

	push byte 0

	push byte 36

	jmp irq_common


[GLOBAL irq5]
irq5:
	cli

	push byte 0

	push byte 37

	jmp irq_common


[GLOBAL irq6]
irq6:
	cli

	push byte 0

	push byte 38

	jmp irq_common


[GLOBAL irq7]
irq7:
	cli

	push byte 0

	push byte 39

	jmp irq_common


[GLOBAL irq8]
irq8:
	cli

	push byte 0

	push byte 40

	jmp irq_common


[GLOBAL irq9]
irq9:
	cli

	push byte 0

	push byte 41

	jmp irq_common


[GLOBAL irq10]
irq10:
	cli

	push byte 0

	push byte 42

	jmp irq_common


[GLOBAL irq11]
irq11:
	cli

	push byte 0

	push byte 43

	jmp irq_common


[GLOBAL irq12]
irq12:
	cli

	push byte 0

	push byte 44

	jmp irq_common


[GLOBAL irq13]
irq13:
	cli

	push byte 0

	push byte 45

	jmp irq_common


[GLOBAL irq14]
irq14:
	cli

	push byte 0

	push byte 46

	jmp irq_common


[GLOBAL irq15]
irq15:
	cli

	push byte 0

	push byte 47

	jmp irq_common

[EXTERN irq_handler]
;Preps stack for handling IRQ
irq_common:
	pusha				;Save register values. 

	push ds
	push es
	push fs
	push gs

	mov ax, 0x10		;Change to kernel data segment. 
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax

	mov eax, esp		;Push stack for irq_handler arguments. 
	push eax

	mov eax, irq_handler
	call eax

	pop eax

	pop gs
	pop fs
	pop es
	pop ds

	popa

	add esp, 8

	sti					;Re-enables interrupts. 
	iret
