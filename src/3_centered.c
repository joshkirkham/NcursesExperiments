/* Prints a bunch of memes in fancy little text boxes */

#include <ncurses.h>
#include <string.h>

struct BoxSize {
	int x;
	int y;
	int width;
	int height;
};


/**
 * Print a nice text box centered on the window. Center each line too.
 * Does not do line wrapping, because that's too hard.
 * Specify your width and height as params because i'm too lazy to parse
 * the string and find them for you.
 * Returns a BoxSize for printing a nice border if you desire.
 */
struct BoxSize PrintCenteredTextBox(char* string, int height, int width) {

	int WindowX;
	int WindowY;
	getmaxyx(stdscr, WindowY, WindowX);
	width = (width > WindowX)? WindowX : width;
	height = (height > WindowY)? WindowY : height;
	
	// Calculate the bounding box coordinates
	int centerX = WindowX / 2;
	int centerY = WindowY / 2;
	int textRowTop = centerY - height / 2;
	if (height % 2 == 0) {++textRowTop;}
	int textRowBottom = centerY + height / 2;
	int textColLeft = centerX - width / 2;
	if (width % 2 == 0) {++textColLeft;}
	int textColRight = centerX + width / 2;


	int currentY = textRowTop;
	char* currentLine = strtok(string, "\n");

	// Print each line
	while (currentY <= textRowBottom && currentLine != NULL) {
		int lineLen = strlen(currentLine);

		// Cut of the end of the line if it's too long
		if (lineLen > width) {
			currentLine[width] = '\0';
		}

		// Pad the line for centering if it's too short
		int padding = (width - lineLen) / 2;
		if (padding < 0) { padding = 0; }

		mvprintw(currentY, textColLeft + padding, currentLine);

		currentLine = strtok(NULL, "\n");
		++currentY;
	}

	struct BoxSize boxSize = {
		.x = textColLeft - 1,
		.y = textRowTop - 1,
		.width = width + 2,
		.height = height + 2
	};
	return boxSize;
}

void PrintBox(struct BoxSize size) {
	mvvline(size.y, size.x, ACS_VLINE, size.height);
	mvvline(size.y, size.x + size.width - 1, ACS_VLINE, size.height);
	mvhline(size.y, size.x, ACS_HLINE, size.width);
	mvhline(size.y + size.height - 1, size.x, ACS_HLINE, size.width);
	mvaddch(size.y, size.x, ACS_ULCORNER);
	mvaddch(size.y, size.x + size.width - 1, ACS_URCORNER);
	mvaddch(size.y + size.height - 1, size.x, ACS_LLCORNER);
	mvaddch(size.y + size.height - 1, size.x + size.width - 1, ACS_LRCORNER);
}

void PrintMeme(char* str, int width, int height) {
	struct BoxSize bs;
	clear();
	bs = PrintCenteredTextBox(str, width, height);
	PrintBox(bs);
	refresh();
	getch();
}

void main(void) {
	char copypasta[] = "Lamp oil? Rope? Bombs?\nYou want it? It's yours, my friend!\n"\
		"As long as you have enough Rupees!";
	char copypasta2[] = "Sorry, Link, I can't give credit.\n"\
		"Come back when you're a little richer.";
	char test[] = "Try and print this string in a buffer that is too small to print.\n"\
				"*************************\n******************\n*************\n";

	initscr();
	cbreak();
	noecho();

	PrintMeme("Hello, World!", 1, 20);
	PrintMeme(copypasta, 3, 50);
	PrintMeme(copypasta2, 2, 50);
	PrintMeme(test, 10, 10);

	// Don't try and print the same strings again. You used strtok on them. 
	// I totally didn't spend 30 minutes trying to figure that out...
	
	endwin();

}
