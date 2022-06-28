#include <stddef.h>
#include <stdint.h>
 
#if defined(__linux__)
	#error "This code must be compiled with a cross-compiler"
#elif !defined(__i386__)
	#error "This code must be compiled with an x86-elf compiler"
#endif
 
volatile uint16_t* vga_buffer = (uint16_t*)0xB8000;
const int VGA_COLS = 80;
const int VGA_ROWS = 24;

int term_col = 0;
int term_row = 0;
uint8_t term_color = 0x1F;
 
void term_init() {
	for (int col = 0; col < VGA_COLS; col ++) {
		for (int row = 0; row < VGA_ROWS; row ++) {
			const size_t index = (VGA_COLS * row) + col;
			vga_buffer[index] = ((uint16_t)term_color << 8) | ' ';
		}
	}
}
 
void term_putc(char c) {
	switch (c) {
		case '\n': 
			{
				term_col = 0;
				term_row ++;
				break;
			}
	
		default: 
			{
				const size_t index = (VGA_COLS * term_row) + term_col;
				vga_buffer[index] = ((uint16_t)term_color << 8) | c;
				term_col ++;
				break;
			}
	}
 
	if (term_col >= VGA_COLS) {
		term_col = 0;
		term_row ++;
	}
 
	if (term_row >= VGA_ROWS) {
		term_col = 0;
		term_row = 0;
	}
}

void term_setpos(int col, int row) {
	term_col = col;
	term_row = row;
}

void term_setbg(uint8_t color) {
	term_color = color;
}
 
void term_print(const char* str) {
	for (size_t i = 0; str[i] != '\0'; i ++) {
		term_putc(str[i]);
	}
}

void kernel_main() {
	term_init();
	term_print("\n");
	term_print(" BluDood Inc. BluShell Kernel 1.0 Setup\n");
	term_print(" ============================");
	term_setbg(0xF0);
	for (int i = 0; i <= 80; i++) {
		term_setpos(i, VGA_ROWS);
		if (i == 60) {
			term_print("|");
		} else {
			term_print(" ");
		}
	}
	const char* bottom = "stay sussy";
	for (size_t i = 0; bottom[i] != '\0'; i ++) {
		term_setpos(i, VGA_ROWS);
		term_putc(bottom[i]);
	}
	term_setbg(0x1F);
	term_setpos(3, 4);
	term_print("Welcome to Setup.");
	term_setpos(3, 6);
	term_print("The Setup program prepared BluDood Inc. BluShell 1.0 to");
	term_setpos(3, 7);
	term_print("run on your computer.");
	term_setpos(5, 9);
	term_print("  * To set up BluShell now, press Enter.");
	term_setpos(5, 11);
	term_print("  * To learn more about Setup before continuingm press F1.");
	term_setpos(5, 13);
	term_print("  * To quit Setup without installing BluShell, press F3.");
	term_setpos(3, 15);
	term_print("Note: BluShell is not functional. Nothing works :troll:");
	term_setpos(3, 17);
	term_print("Socials:");
	term_setpos(5, 19);
	term_print("Email: bludood@bludood.com");
	term_setpos(5, 21);
	term_print("Twitter: @ItsBluDood");
}