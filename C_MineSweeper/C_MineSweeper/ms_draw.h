#pragma once

void draw_frame(WINDOW* w);//枠の描画
void draw_box(int box_array[][14], int bom_array[][14], WINDOW* w);//ボックスの中身の描画
void start_display(int b_num, WINDOW* w);//スタート画面を表示
void clear_display(const char* time, WINDOW* w);//クリア画面を表示
void failed_display(WINDOW* w);//ゲームオーバー画面を表示
void instructions_display(WINDOW* w);//説明文を表示