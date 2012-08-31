/*
 * nit - nyan cat git launcher
 *
 * Jason Fraley github.com/oelbrenner
 * shamelessly hacked version of:
 * https://github.com/rwos/gti
 *
 * original author:
 * Copyright 2012 by Richard Wossal <richard@r-wos.org>
 *
 * gti - a git launcher
 *
 * Permission to use, copy, modify, distribute, and sell this software
 * and its documentation for any purpose is hereby granted without fee,
 * provided that the above copyright notice appear in all copies and
 * that both that copyright notice and this permission notice appear in
 * supporting documentation.  No representations are made about the
 * suitability of this software for any purpose.  It is provided "as
 * is" without express or implied warranty.
 */

#include <stdio.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <string.h>

#define GIT_NAME "git"

int  term_width(void);
void init_space(void);
void move_to_top(void);
void line_at(int start_x, const char *s);
void draw_cat(int x);
void clear_cat(int x);

int TERM_WIDTH;

int main(int argc, char **argv)
{
    (void) argc;
    int i;
    TERM_WIDTH = term_width();
    init_space();
    for (i = -20; i < TERM_WIDTH; i++) {
        draw_cat(i);
        usleep(10*1000);
        clear_cat(i);
    }
    execvp(GIT_NAME, argv);
    /* error in exec if we land here */
    perror(GIT_NAME);
    return 1;
}

int term_width(void)
{
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    return w.ws_col;
}

void init_space(void)
{
    puts("\n\n\n\n\n\n"); /* 7 lines */
}

void move_to_top(void)
{
    printf("\033[%dA", 7);
}

void line_at(int start_x, const char *s)
{
    int x;
    size_t i;
    if (start_x > 1)
        printf("\033[%dC", start_x);
    for (x = start_x, i = 0; i < strlen(s); x++, i++) {
        if (x > 0 && x < TERM_WIDTH)
            putchar(s[i]);
    }
    putchar('\n');
}

void draw_cat(int x)
{
    move_to_top();
    line_at(x,",------,");
    line_at(x,"|   /\\_/\\"); 
    line_at(x,"|__( ^ .^)");
    line_at(x,"\"\"  \"\" ");     
}


void clear_cat(int x)
{
    move_to_top();
    line_at(x, "- -");
    line_at(x, "- -");
    line_at(x, "- -");
    line_at(x, "- -");
}

