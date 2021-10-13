/**
 * sudoku.c
 *
 * CS50 AP
 * Sudoku
 *
 * Implements the game of Sudoku.
 */

#include <ctype.h>
#include <ncurses.h>
#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sudoku.h"
#include <time.h>

// macro for processing control characters
#define CTRL(x) ((x) & ~0140)

// size of each int (in bytes) in *.bin files
#define INTSIZE 4

// wrapper for our game's globals
struct
{
    // the current level
    char *level;

    // the game's board
    int board[9][9];

    // Store the Inital Board
    int initialBoard[9][9];

    int previous[3];

    // the board's number
    int number;

    // the board's top-left coordinates
    int top, left;

    // the cursor's current location between (0,0) and (8,8)
    int y, x;

    bool won;
} g;

// prototypes
void draw_grid(void);
void draw_borders(void);
void draw_logo(void);
void draw_numbers(void);
void hide_banner(void);
bool load_board(void);
void handle_signal(int signum);
void log_move(int ch);
void redraw_all(void);
bool restart_game(void);
void show_banner(char *b);
void show_cursor(void);
void shutdown(void);
bool startup(void);

// newly-added prototypes
void check(void);
bool checkrows(int val);
bool checkcols(int val);
bool checkboxes(int val);
bool check_ind_box(int x, int y, int val); // Check the row, check the column, check the box. Return a boolean value.
bool checkwin(void);
void reposition(int ch);
void update_numbers(int ch, bool zero);
void undo_move(void);
void delay(int number_of_seconds);

int main(int argc, char *argv[])
{
    // ensure that number of arguments is as expected
    if (argc != 2 && argc != 3)
    {
        fprintf(stderr, "Usage: sudoku n00b|l33t [#]\n");
        return 1;
    }
    // ensure that level is valid
    if (strcmp(argv[1], "debug") == 0)
    {
        g.level = "debug";
    }
    else if (strcmp(argv[1], "n00b") == 0)
    {
        g.level = "n00b";
    }
    else if (strcmp(argv[1], "l33t") == 0)
    {
        g.level = "l33t";
    }
    else
    {
        fprintf(stderr, "Usage: sudoku n00b|l33t [#]\n");
        return 2;
    }

    // n00b and l33t levels have 1024 boards; debug level has 9
    int max = (strcmp(g.level, "debug") == 0) ? 9 : 1024;

    // ensure that #, if provided, is in [1, max]
    if (argc == 3)
    {
        // ensure n is integral
        char c;
        if (sscanf(argv[2], " %d %c", &g.number, &c) != 1)
        {
            fprintf(stderr, "Usage: sudoku n00b|l33t [#]\n");
            return 3;
        }

        // ensure n is in [1, max]
        if (g.number < 1 || g.number > max)
        {
            fprintf(stderr, "That board # does not exist!\n");
            return 4;
        }

        // seed PRNG with # so that we get same sequence of boards
        srand(g.number);
    }
    else
    {
        // seed PRNG with current time so that we get any sequence of boards
        srand(time(NULL));

        // choose a random n in [1, max]
        g.number = rand() % max + 1;
    }

    // start up ncurses
    if (!startup())
    {
        fprintf(stderr, "Error starting up ncurses!\n");
        return 5;
    }

    // register handler for SIGWINCH (SIGnal WINdow CHanged)
    signal(SIGWINCH, (void (*)(int)) handle_signal);

    // start the first game
    if (!restart_game())
    {
        shutdown();
        fprintf(stderr, "Could not load board from disk!\n");
        return 6;
    }
    redraw_all();

    // let the user play!
    int ch;

    do
    {
        // refresh the screen
        refresh();

        // get user's input
        ch = getch();

        // capitalize input to simplify cases
        ch = toupper(ch);

        // process user's input
        switch (ch)
        {
            // start a new game
            case 'N':
                g.number = rand() % max + 1;
                if (!restart_game())
                {
                    shutdown();
                    fprintf(stderr, "Could not load board from disk!\n");
                    return 6;
                }
                break;

            // restart current game
            case 'R':
                if (!restart_game())
                {
                    shutdown();
                    fprintf(stderr, "Could not load board from disk!\n");
                    return 6;
                }
                break;

            // let user manually redraw screen with ctrl-L
            case CTRL('l'):
                redraw_all();
                break;

            case KEY_UP:
            case 'W':
                reposition(ch);
            break;

            case KEY_DOWN:
            case 'S':
                reposition(ch);
            break;

            case KEY_RIGHT:
            case 'D':
                reposition(ch);
            break;


            case KEY_LEFT:
            case 'A':
                reposition(ch);
            break;

            /*
                @author Xander Endre

                Description: Set position equal to a numerical value 1 - 9.

                ** Uses triple dot notation to iterate through 1 to 9.
            */
            case '1' ... '9':
                update_numbers(ch, false);
            break;

            case '0':
            case KEY_BACKSPACE:
            case KEY_DC:
                update_numbers(ch, true);
            break;


            // let user manually redraw screen with ctrl-L
            case CTRL('Z'):
            case 'U':
                undo_move();
//                redraw_all();
            break;


        }

        // log input (and board's state) if any was received this iteration
        if (ch != ERR) {
            log_move(ch);
        }

        if(checkwin()) {
            g.won = true;

        }

    }
    while (ch != 'Q');

    // shut down ncurses
    shutdown();

    // tidy up the screen (using ANSI escape sequences)
    printf("\033[2J");
    printf("\033[%d;%dH", 0, 0);

    // that's all folks
    printf("\nkthxbai!\n\n");
    return 0;
}

/*
 * Draw's the game's board.
 */
void draw_grid(void)
{
    // get window's dimensions
    int maxy, maxx;
    getmaxyx(stdscr, maxy, maxx);

    // determine where top-left corner of board belongs
    g.top = maxy/2 - 7;
    g.left = maxx/2 - 30;

    // enable color if possible
    if (has_colors())
        attron(COLOR_PAIR(PAIR_GRID));

    // print grid
    for (int i = 0 ; i < 3 ; ++i )
    {
        mvaddstr(g.top + 0 + 4 * i, g.left, "+-------+-------+-------+");
        mvaddstr(g.top + 1 + 4 * i, g.left, "|       |       |       |");
        mvaddstr(g.top + 2 + 4 * i, g.left, "|       |       |       |");
        mvaddstr(g.top + 3 + 4 * i, g.left, "|       |       |       |");
    }
    mvaddstr(g.top + 4 * 3, g.left, "+-------+-------+-------+" );

    // remind user of level and #
    char reminder[maxx+1];
    sprintf(reminder, "   playing %s #%d", g.level, g.number);
    mvaddstr(g.top + 14, g.left + 25 - strlen(reminder), reminder);

    // disable color if possible
    if (has_colors())
    {
        attroff(COLOR_PAIR(PAIR_GRID));
    }
}


/*
 * Draws game's borders.
 */
void draw_borders(void)
{
    // get window's dimensions
    int maxy, maxx;
    getmaxyx(stdscr, maxy, maxx);

    // enable color if possible (else b&w highlighting)
    if (has_colors())
    {
        attron(A_PROTECT);
        attron(COLOR_PAIR(PAIR_BORDER));
    }
    else
    {
        attron(A_REVERSE);
    }

    // draw borders
    for (int i = 0; i < maxx; i++)
    {
        mvaddch(0, i, ' ');
        mvaddch(maxy-1, i, ' ');
    }

    // draw header
    char header[maxx+1];
    sprintf(header, "%s by %s", TITLE, AUTHOR);
    mvaddstr(0, (maxx - strlen(header)) / 2, header);

    // draw footer
    mvaddstr(maxy-1, 1, "[N]ew Game   [R]estart Game");
    mvaddstr(maxy-1, maxx-13, "[Q]uit Game");

    // disable color if possible (else b&w highlighting)
    if (has_colors())
    {
        attroff(COLOR_PAIR(PAIR_BORDER));
    }
    else
    {
        attroff(A_REVERSE);
    }
}


/*
 * Draws game's logo.  Must be called after draw_grid has been
 * called at least once.
 */
void draw_logo(void)
{
    // determine top-left coordinates of logo
    int top = g.top + 2;
    int left = g.left + 30;

    // enable color if possible
    if (has_colors())
    {
        attron(COLOR_PAIR(PAIR_LOGO));
    }

    // draw logo
    mvaddstr(top + 0, left, "               _       _          ");
    mvaddstr(top + 1, left, "              | |     | |         ");
    mvaddstr(top + 2, left, " ___ _   _  __| | ___ | | ___   _ ");
    mvaddstr(top + 3, left, "/ __| | | |/ _` |/ _ \\| |/ / | | |");
    mvaddstr(top + 4, left, "\\__ \\ |_| | (_| | (_) |   <| |_| |");
    mvaddstr(top + 5, left, "|___/\\__,_|\\__,_|\\___/|_|\\_\\\\__,_|");

    // sign logo
    char signature[3+strlen(AUTHOR)+1];
    sprintf(signature, "by %s", AUTHOR);
    mvaddstr(top + 7, left + 35 - strlen(signature) - 1, signature);

    // disable color if possible
    if (has_colors())
    {
        attroff(COLOR_PAIR(PAIR_LOGO));
    }
}


/*
 * Draw's game's numbers.  Must be called after draw_grid has been
 * called at least once.
 */
void draw_numbers(void)
{

    // enable color if possible
    if (has_colors())
    {
        if(checkwin()) {
            attron(COLOR_PAIR(PAIR_WIN));
            show_banner("u won bish.");
        }
        else {
        attron(COLOR_PAIR(PAIR_DIGITS));
        hide_banner();
        }


    }
    // iterate over board's numbers
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {            // determine char
        if(checkwin()) {
            attron(COLOR_PAIR(PAIR_WIN));
        }
        else if(g.initialBoard[i][j] == 0){
                attroff(COLOR_PAIR(PAIR_DIGITS));
                attroff(COLOR_PAIR(PAIR_WIN));
                attron(COLOR_PAIR(PAIR_NEWDIGITS));
        }
        else {
            attron(COLOR_PAIR(PAIR_DIGITS));
        }

            char c = (g.board[i][j] == 0) ? '.' : g.board[i][j] + '0';
            mvaddch(g.top + i + 1 + i/3, g.left + 2 + 2*(j + j/3), c);
            refresh();

        }
    }
    // disable color if possible
    if (has_colors())
    {
        attroff(COLOR_PAIR(PAIR_BANNER));
    }
}



/*
 * Designed to handles signals (e.g., SIGWINCH).
 */
void handle_signal(int signum)
{
    // handle a change in the window (i.e., a resizing)
    if (signum == SIGWINCH)
    {
        redraw_all();
    }

    // re-register myself so this signal gets handled in future too
    signal(signum, (void (*)(int)) handle_signal);
}


/*
 * Hides banner.
 */
void hide_banner(void)
{
    // get window's dimensions
    int maxy, maxx;
    getmaxyx(stdscr, maxy, maxx);

    // overwrite banner with spaces
    for (int i = 0; i < maxx; i++)
    {
        mvaddch(g.top + 16, i, ' ');
    }
}


/*
 * Loads current board from disk, returning true iff successful.
 */
bool load_board(void)
{
    // open file with boards of specified level
    char filename[strlen(g.level) + 5];
    sprintf(filename, "%s.bin", g.level);
    FILE *fp = fopen(filename, "rb");
    if (fp == NULL)
    {
        return false;
    }

    // determine file's size
    fseek(fp, 0, SEEK_END);
    int size = ftell(fp);

    // ensure file is of expected size
    if (size % (81 * INTSIZE) != 0)
    {
        fclose(fp);
        return false;
    }

    // compute offset of specified board
    int offset = ((g.number - 1) * 81 * INTSIZE);

    // seek to specified board
    fseek(fp, offset, SEEK_SET);

    // read board into memory
    if (fread(g.board, 81 * INTSIZE, 1, fp) != 1)
    {
        fclose(fp);
        return false;
    }

    // w00t
    fclose(fp);

    /*
        @author Xander Endre

        Description: Store a copy of the initial board
    */

    // Every Column
    for(int i = 0; i < 9; i++) {
        // Every Row
        for(int j = 0; j < 9; j++) {
            g.initialBoard[j][i] = g.board[j][i];
        }
    }

    return true;
}


/*
 * Logs input and board's state to log.txt to facilitate automated tests.
 */
void log_move(int ch)
{
    // open log
    FILE *fp = fopen("log.txt", "a");
    if (fp == NULL)
    {
        return;
    }

    // log input
    fprintf(fp, "%d\n", ch);

    // log board
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            fprintf(fp, "%d", g.board[i][j]);
        }
        fprintf(fp, "\n");
    }

    // that's it
    fclose(fp);
}


/*
 * (Re)draws everything on the screen.
 */
void redraw_all(void)
{
    // reset ncurses
    endwin();
    refresh();

    // clear screen
    clear();

    // re-draw everything
    draw_borders();
    draw_grid();
    draw_logo();
    draw_numbers();

    // show cursor
    show_cursor();
}


/*
 * (Re)starts current game, returning true iff succesful.
 */
bool restart_game(void)
{
    g.won = false;
    // reload current game
    if (!load_board())
    {
        return false;
    }

    // redraw board
    draw_grid();
    draw_numbers();

    // get window's dimensions
    int maxy, maxx;
    getmaxyx(stdscr, maxy, maxx);

    // move cursor to board's center
    g.y = g.x = 4;
    show_cursor();

    // remove log, if any
    remove("log.txt");

    // w00t
    return true;
}


/*
 * Shows cursor at (g.y, g.x).
 */
void show_cursor(void)
{
    // restore cursor's location
    move(g.top + g.y + 1 + g.y/3, g.left + 2 + 2*(g.x + g.x/3));
}


/*
 * Shows a banner.  Must be called after show_grid has been
 * called at least once.
 */
void show_banner(char *b)
{
    // enable color if possible
    if (has_colors())
    {
        attroff(COLOR_PAIR(PAIR_BANNER));
        attron(COLOR_PAIR(PAIR_ERROR));
    }

    // determine where top-left corner of board belongs
    mvaddstr(g.top + 16, g.left + 64 - strlen(b), b);

    // disable color if possible
    if (has_colors())
    {
        attroff(COLOR_PAIR(PAIR_BANNER));
        attroff(COLOR_PAIR(PAIR_ERROR));
    }
}


/*
 * Shuts down ncurses.
 */
void shutdown(void)
{
    endwin();
}


/*
 * Starts up ncurses.  Returns true iff successful.
 */
bool startup(void)
{
    g.won = false;
    // initialize ncurses
    if (initscr() == NULL)
    {
        return false;
    }

    // prepare for color if possible
    if (has_colors())
    {
        // enable color
        if (start_color() == ERR || attron(A_PROTECT) == ERR)
        {
            endwin();
            return false;
        }

        // initialize pairs of colors
        if (init_pair(PAIR_BANNER, FG_BANNER, BG_BANNER) == ERR ||
            init_pair(PAIR_GRID, FG_GRID, BG_GRID) == ERR ||
            init_pair(PAIR_BORDER, FG_BORDER, BG_BORDER) == ERR ||
            init_pair(PAIR_LOGO, FG_LOGO, BG_LOGO) == ERR ||
            init_pair(PAIR_DIGITS, FG_DIGITS, BG_DIGITS) == ERR ||
            init_pair(PAIR_NEWDIGITS, FG_NEWDIGITS, BG_NEWDIGITS) == ERR ||
            init_pair(PAIR_ERROR, FG_ERROR, BG_ERROR) == ERR ||
            init_pair(PAIR_WIN, FG_WIN, BG_WIN) == ERR)
        {
            endwin();
            return false;
        }
    }

    // don't echo keyboard input
    if (noecho() == ERR)
    {
        endwin();
        return false;
    }

    // disable line buffering and certain signals
    if (raw() == ERR)
    {
        endwin();
        return false;
    }

    // enable arrow keys
    if (keypad(stdscr, true) == ERR)
    {
        endwin();
        return false;
    }

    // wait 1000 ms at a time for input
    timeout(1000);

    // w00t
    return true;
}


     /*
        @author Xander Endre

        Description: Reposition the cursor
    */

    void reposition(int ch)
    {

            /*
                @author Xander Endre

                Description: Move Keystroke/Position to the up one placement
            */
            if(ch == KEY_UP || ch == 'W') {
                // Check if position is greater than 0
                if (g.y > 0)
                {
                    // Y Axis Reversed -- Moves up one position
                    g.y -= 1;
                    // Shows Cursor
                    show_cursor();
                }
                // Wrapping to the bottom of the page
                else {
                    // Reset Position to 8
                    g.y = 8;
                    // Show Cursor
                    show_cursor();
                }
            }

            /*
                @author Xander Endre

                Description: Move Keystroke/Position to the down one placement
            */
            if(ch == KEY_DOWN || ch == 'S') {

                // Check if the position is less than 8
                if (g.y < 8)
                {
                    // Y Axis Reversed -- Moves down one position
                    g.y += 1;
                    // Show Cursor
                    show_cursor();
                }
                // Wrapping to the top of page
                else {
                    // Reset Position
                    g.y = 0;
                    // Show Cursor
                    show_cursor();
                }
            }

            /*
                @author Xander Endre

                Description: Move Keystroke/Position to the right one placement
            */
            if(ch == KEY_RIGHT || ch == 'D') {
                // Check if the position is greater than 0
                if (g.x < 8)
                {
                    // Moves right one position
                    g.x += 1;
                    // Show Cursor
                    show_cursor();
                }
                // Wrapping to the top of page
                else {
                    // Reset Position
                    g.x = 0;
                    // Show Cursor
                    show_cursor();
                }
            }

            /*
                @author Xander Endre

                Description: Move Keystroke/Position to the left one placement
            */
            if(ch == KEY_LEFT || ch == 'A') {
                // Check if the position is greater than 0
                if (g.x > 0)
                {
                    // Moves right one position
                    g.x -= 1;
                    // Show Cursor
                    show_cursor();
                }
                // Wrapping to the top of page
                else {
                    // Reset Position
                    g.x = 8;
                    // Show Cursor
                    show_cursor();
                }
            }
    }


    /*
        @author Xander Endre

        Description: Reposition the cursor
    */

    void update_numbers(int ch, bool zero) {

            /*
                @author Xander Endre

                Description: Set position equal to to 0
            */
            if((ch == KEY_DC || ch == KEY_BACKSPACE || ch == '0') && zero) {
                if(!g.won) {
                // Check if the board position exists on the original board
                    if(g.initialBoard[g.y][g.x] == 0)
                    {

                            g.previous[0] = g.y;
                            g.previous[1] = g.x;
                            g.previous[2] = g.board[g.y][g.x];

                            // Set the board position equal to zero (The program will deal with converting the 0 to a period)
                            g.board[g.y][g.x] = 0;

                            // Draws the new number
                            draw_numbers();
                            // Refreshes the show_cursor position since draw numbers moves it around
                            show_cursor();


                    }
                }
            }
            if(!zero)
            {
                if(!g.won) {
                    // Check if the board position exists
                    if(g.initialBoard[g.y][g.x] == 0) {

                        ch = ch - '0';
                        if(checkcols(ch) && checkrows(ch) && check_ind_box(g.y, g.x, ch)) {

                                // Start by storing the previous moves incase of an undo
                                g.previous[0] = g.y;
                                g.previous[1] = g.x;
                                g.previous[2] = g.board[g.y][g.x];

                                // Set the board position equal to the entered number
                                g.board[g.y][g.x] = ch;

                                hide_banner();
                                // Draws the new number
                                draw_numbers();
                            }
                    }
                        // Refreshes the show_cursor position since draw numbers moves it around
                        show_cursor();
                }
            }
        }


    /*
        @author Xander Endre

        Description: Reposition the cursor
    */
    bool checkrows(int val) {
        // board[0] -- up and down.. board[x][0] -- left and right..
            for(int i = 0; i < 9; i++) {
                if(g.board[g.y][i] == val) {
                    show_banner("You cannot go there!");
                    return false;
                }
            }

       return true;
    }

        /*
        @author Xander Endre

        Description: Reposition the cursor
    */
    bool checkcols(int val) {
        // board[0] -- up and down.. board[x][0] -- left and right..
            for(int i = 0; i < 9; i++) {
                if(g.board[i][g.x] == val) {
                    show_banner("You cannot go there!");
                    return false;
                }
            }

       return true;
    }

    /*
        @author Xander Endre

        Description: Reposition the cursor
    */
    bool check_ind_box(int x, int y, int val) {
        // cehck individual box

        int leftSide = x - (x % 3);
        int topSide = y - (y % 3);

            for(int i = leftSide; i < leftSide + 3; i++) {
                for(int j = topSide; j < topSide + 3; j++) {
                   if(g.board[i][j] == val) {
                        show_banner("You cannot go there!");
                        return false;
                }
            }
        }
       return true;
    }


    bool checkwin(void) {
        for(int i = 0; i < 9; i++) // Loop through each row and column
        {
            int row[9] = {0}; // Creates a temporary variable for the current row
            int col[9] = {0}; // Creates a temporary variable for the current col

            for(int j = 0; j < 9; j++) //Go right the the row and down the col
            {
                row[g.board[i][j]-1]++; // Fill the Rows
                col[g.board[j][i]-1]++; // Fill the Coms
            }

            for (int k = 0; k < 9; k++) // Making sure there is only one occurence..
            {
                if(col[k] != 1) {
                    return false;
                }

                if(row[k] != 1) {
                    return false;
                }
            }

        }
        // Looking at each individual square

        for(int i = 0; i < 9; i += 3) // lLoop each grid horizontally
        {
            for(int j = 0; j < 9; j += 3) // Loop over each grid vertically
            {
                int sum = 0; // Some way of tracking the total sum
                for(int k = i; k < i + 3; k++) // Loop over each square in the grid horizontally
                {
                    for(int l = j; l < j + 3; l++) // loop over each square in a grid vertically
                    {
                        sum += g.board[k][l];
                    }
                }
                if(sum != 45) {
                    return false;
                }
            }
        }
        return true; // none of the false conditions occured!
    }

    void undo_move(void) {
        g.won = false;

        g.x = g.previous[1];
        g.y = g.previous[0];
        g.board[g.y][g.x] = g.previous[2];

        draw_numbers();
        show_cursor();

    }

    void delay(int number_of_seconds)
{
    // Converting time into milli_seconds
    int milli_seconds = 1000 * number_of_seconds;

    // Storing start time
    clock_t start_time = clock();

    // looping till required time is not achieved
    while (clock() < start_time + milli_seconds)
        ;
}