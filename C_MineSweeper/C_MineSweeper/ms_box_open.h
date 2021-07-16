#pragma once

void box_open(int x, int y, int box_array[][14], int bom_array[][14]);//選択したボックスを開ける処理
void box_open_up(int x, int y, int box_array[][14], int bom_array[][14]); // 選択した上のボックスを開ける処理
void box_open_down(int x, int y, int box_array[][14], int bom_array[][14]);// 選択した下のボックスを開ける処理
void box_open_right(int x, int y, int box_array[][14], int bom_array[][14]);// 選択した右のボックスを開ける処理
void box_open_left(int x, int y, int box_array[][14], int bom_array[][14]);// 選択した左のボックスを開ける処理