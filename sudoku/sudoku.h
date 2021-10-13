/**
 * sudoku.h
 *
 * CS50 AP
 * Sudoku
 *
 * Compile-time options for the game of Sudoku.
 */

// game's author
#define AUTHOR "Xander Endre"

// game's title
#define TITLE "Sudoku"

// banner's colors
#define FG_BANNER COLOR_BLUE
#define BG_BANNER COLOR_BLACK

// grid's colors
#define FG_GRID COLOR_BLUE
#define BG_GRID COLOR_BLACK

// border's colors
#define FG_BORDER COLOR_WHITE
#define BG_BORDER COLOR_BLUE

// logo's colors
#define FG_LOGO COLOR_WHITE
#define BG_LOGO COLOR_BLACK

// digits's colors
#define FG_DIGITS COLOR_WHITE
#define BG_DIGITS COLOR_BLACK

// new number colors
#define FG_NEWDIGITS COLOR_CYAN
#define BG_NEWDIGITS COLOR_BLACK

// error message colors
#define FG_ERROR COLOR_WHITE
#define BG_ERROR COLOR_RED

// win message colors
#define FG_WIN COLOR_GREEN
#define BG_WIN COLOR_BLACK

// nicknames for pairs of colors
enum { PAIR_BANNER = 1, PAIR_GRID, PAIR_BORDER, PAIR_LOGO, PAIR_DIGITS, PAIR_NEWDIGITS, PAIR_ERROR, PAIR_WIN };
