/**
 * Type out characters, selecting a fun attribute if the user hits one of the f keys
 */

#include <ncurses.h>
#include <stdbool.h>

int CurrentAttr = A_NORMAL;

void SetAttr(int newAttr) {
	attroff(CurrentAttr);
	attron(newAttr);
	CurrentAttr = newAttr;
}

void main(void) {
	initscr();
	cbreak();
	noecho();
	keypad(stdscr, TRUE);

	printw("F1: Exit, F12: Normal, F2-10: Memes\n");
	printw("Type Characters.\n");
	
	int userInput = '?';
	do {
		userInput = getch();

		bool printChar = true;

		if (userInput == KEY_F(1)) {
			break;
		}
		else if (userInput >= KEY_F(2) && userInput <= KEY_F(10)) {
			SetAttr(NCURSES_BITS(1U, 8 + (userInput - KEY_F(2))));
			printChar = false;
		}
		else if (userInput == KEY_F(12)) {
			SetAttr(A_NORMAL);
			printChar = false;
		}
		
		if (printChar) {
			printw("%c", userInput);
			refresh();
		}
	} while (userInput != KEY_F(1));

	endwin();
}


/* Documentation 

1109 #define A_NORMAL    (1U - 1U)
1110 #define A_ATTRIBUTES    NCURSES_BITS(~(1U - 1U),0)
1111 #define A_CHARTEXT  (NCURSES_BITS(1U,0) - 1U)
1112 #define A_COLOR     NCURSES_BITS(((1U) << 8) - 1U,0)
1113 #define A_STANDOUT  NCURSES_BITS(1U,8)
1114 #define A_UNDERLINE NCURSES_BITS(1U,9)
1115 #define A_REVERSE   NCURSES_BITS(1U,10)
1116 #define A_BLINK     NCURSES_BITS(1U,11)
1117 #define A_DIM       NCURSES_BITS(1U,12)
1118 #define A_BOLD      NCURSES_BITS(1U,13)
1119 #define A_ALTCHARSET    NCURSES_BITS(1U,14)
1120 #define A_INVIS     NCURSES_BITS(1U,15)
1121 #define A_PROTECT   NCURSES_BITS(1U,16)
1122 #define A_HORIZONTAL    NCURSES_BITS(1U,17)
1123 #define A_LEFT      NCURSES_BITS(1U,18)
1124 #define A_LOW       NCURSES_BITS(1U,19)
1125 #define A_RIGHT     NCURSES_BITS(1U,20)
1126 #define A_TOP       NCURSES_BITS(1U,21)
1127 #define A_VERTICAL  NCURSES_BITS(1U,22)
*/

