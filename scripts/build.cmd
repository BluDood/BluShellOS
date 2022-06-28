@echo off
call scripts/purge.cmd
echo Building ISO...
i686-elf-gcc -std=gnu99 -ffreestanding -g -c start.s -o start.o
i686-elf-gcc -std=gnu99 -ffreestanding -g -c kernel.c -o kernel.o
i686-elf-gcc -ffreestanding -nostdlib -g -T linker.ld start.o kernel.o -o kernel.elf -lgcc
copy kernel.elf isoroot\boot
genisoimage -R -b boot/grub/stage2_eltorito -no-emul-boot -boot-load-size 4 -boot-info-table -o blushell.iso isoroot
call scripts/purge.cmd
call scripts/start.cmd