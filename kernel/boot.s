;
;boot.s -- Kernel start location. Also defines multiboot header.
;Based on Bran's kernel development tutorial file start. asm.
;Source: www.jamesmolloy.co.uk
;

MBOOT_PAGE_ALIGN	equ 1<<0 ;Load kernel and modules on a page. 
MBOOT_MEM_INFO		equ 1<<1 ;Provide kernel with memory info. 

;Multiboot magic value. NOTE: we do not use MBOOT_AOUT_KLUDGE.
;It means GRUB does not pass us a symbol table. 
MBOOT_HEADER_MAGIC	equ 0x1BADB002
MBOOT_HEADER_FLAGS	equ MBOOT_PAGE_ALIGN | MBOOT_MEM_INFO
MBOOT_CHECKSUM		equ -(MBOOT_HEADER_MAGIC + MBOOT_HEADER_FLAGS)

[BITS 32]					 ;All instructions should be 32-bit.

[GLOBAL mboot]				 ;Make 'mboot' accessible from C.
[EXTERN code]				 ;Start of the '.text' section
[EXTERN bss]				 ;Start of the .bss section
[EXTERN end]				 ;End of the last loadable section. 

mboot:
	;GRUB will search for this value on each 4-byte boundary in 
	;kernel file. 
	dd MBOOT_HEADER_MAGIC

	;How GRUB should load your file settings. 
	dd MBOOT_HEADER_FLAGS

	;To ensure that the above values are correct.
	dd MBOOT_CHECKSUM

	dd mboot				 ;Location of this descriptor
	dd code					 ;Start of kernel '.text' (code) section
	dd bss					 ;End of kernel '.data' section.
	dd end					 ;End of kernel.
	dd start				 ;Kernel entry point (initial EIP)

[GLOBAL start]				 ;Kernel entry point. 

;This is the entry point of C++ code.
[EXTERN kernel_main]				 

start:
	push ebx				 ;Load multiboot header location. 

	;Execute kernel:
	cli						 ;Disable interrupts. 
	call kernel_main		 ;Call our kernel_main() function. 
	jmp $					 ;Enter an infinite loop, to stop the
							 ;processor executing whenever rubbish
							 ;is in the memory after our kernel. 
