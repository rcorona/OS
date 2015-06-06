all:
	cd kernel; make
	sudo cp kernel/kernel isodir/boot/kernel
	grub-mkrescue -o myos.iso isodir

run:
	make all
	bochs/bochs_gdb/bochs -f bochs/bochs_gdb/bochsrc.txt -q

debug:
	make all
	bochs/bochs/bochs -f bochs/bochs/bochsrc.txt -q

debugGDB:
	make all
	bochs/bochs_gdb/bochs -f bochs/bochs_gdb/bochsrcGDB.txt -q
clean: 
	cd kernel; make clean
