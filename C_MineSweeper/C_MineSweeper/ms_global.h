#pragma once

WINDOW* win;
time_t start_time, end_time;

//爆弾の座標の構造体
struct Bomb {
    int bomb;
};

//グローバル変数
unsigned int game_flag = 0;

//ボックスの座標宣言
int m = 1;
int n = 1;

//キー判定のフラグ
bool key_flag = true;
