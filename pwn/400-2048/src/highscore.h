#ifndef __HIGHSCORE_H__
#define __HIGHSCORE_H__

#include "2048.h"
#include "render.h"
#include "io.h"
#include <ctime>
#include <cstddef>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <ncurses.h>

bool setHighScore(int, int);
bool eraseHighScore();
int loadHighScore(char **);

#endif // __2048_H__
