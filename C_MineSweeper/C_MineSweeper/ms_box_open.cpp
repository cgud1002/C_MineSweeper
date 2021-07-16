#include <stdio.h>
#include <curses.h>
#include <Windows.h>
#include <math.h>
#include <time.h>
#include <direct.h>

#include "ms_box_open.h"


/*box_open系は、選択したボックスがからの場合、上下左右のボックスも開ける
再帰の関数を使い、選択したボックスが数字であればそこで処理が終了*/
void box_open(int x, int y, int box_array[][14], int bom_array[][14]) {//選択したボックスを開ける処理

    box_array[x][y] = 1;

    if (x < 12) {
        box_open_up(x + 1, y, box_array, bom_array);
    }
    if (x > 1) {
        box_open_down(x - 1, y, box_array, bom_array);
    }
    if (y < 12) {
        box_open_right(x, y + 1, box_array, bom_array);
    }
    if (y > 1) {
        box_open_left(x, y - 1, box_array, bom_array);
    }

}

void box_open_up(int x, int y, int box_array[][14], int bom_array[][14]) {//選択した上のボックスを開ける処理

    if (box_array[x][y] == 0) {
        if (bom_array[x][y] == 0) {
            box_array[x][y] = 1;
            if (x < 12) {
                box_open_up(x + 1, y, box_array, bom_array);
            }
            if (y < 12) {
                box_open_right(x, y + 1, box_array, bom_array);
            }
            if (y > 1) {
                box_open_left(x, y - 1, box_array, bom_array);
            }
        }
        else if (bom_array[x][y] > 0) {
            box_array[x][y] = 1;
        }
    }
}

void box_open_down(int x, int y, int box_array[][14], int bom_array[][14]) {//選択した下のボックスを開ける処理


    if (box_array[x][y] == 0) {
        if (bom_array[x][y] == 0) {
            box_array[x][y] = 1;
            if (x > 1) {
                box_open_down(x - 1, y, box_array, bom_array);
            }
            if (y < 12) {
                box_open_right(x, y + 1, box_array, bom_array);
            }
            if (y > 1) {
                box_open_left(x, y - 1, box_array, bom_array);
            }
        }
        else if (bom_array[x][y] > 0) {
            box_array[x][y] = 1;
        }
    }
}

void box_open_right(int x, int y, int box_array[][14], int bom_array[][14]) {//選択した左のボックスを開ける処理


    if (box_array[x][y] == 0) {
        if (bom_array[x][y] == 0) {
            box_array[x][y] = 1;
            if (x < 12) {
                box_open_up(x + 1, y, box_array, bom_array);
            }
            if (x > 1) {
                box_open_down(x - 1, y, box_array, bom_array);
            }
            if (y < 12) {
                box_open_right(x, y + 1, box_array, bom_array);
            }
        }
        else if (bom_array[x][y] > 0) {
            box_array[x][y] = 1;
        }
    }
}

void box_open_left(int x, int y, int box_array[][14], int bom_array[][14]) {//選択した右のボックスを開ける処理

    if (box_array[x][y] == 0) {
        if (bom_array[x][y] == 0) {
            box_array[x][y] = 1;
            if (x < 12) {
                box_open_up(x + 1, y, box_array, bom_array);
            }
            if (x > 1) {
                box_open_down(x - 1, y, box_array, bom_array);
            }
            if (y > 1) {
                box_open_left(x, y - 1, box_array, bom_array);
                box_open_left(x, y - 1, box_array, bom_array);
            }
        }
        else if (bom_array[x][y] > 0) {
            box_array[x][y] = 1;
        }

    }
}