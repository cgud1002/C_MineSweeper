#include <stdio.h>
#include <curses.h>
#include <Windows.h>
#include <math.h>
#include <time.h>
#include <direct.h>

#include "ms_draw.h"
#include "ms_box_open.h"

//関数の宣言
int  key_check();//キー判定
void select_frame(int m, int n, WINDOW* w);//選択した枠をオレンジ色にする
void set_bom(int bom_array[][14], int b_num);//爆弾をセット
void set_bom_num(int bom_array[][14]);//付近の爆弾の個数をセットする
void count_bom(int i, int j, int bom_array[][14]);//付近の爆弾の個数をカウントする
void select_judge(int box_array[][14], int bom_array[][14]);//選択したボックスが爆弾なのか、数字なのか、空なのかを判別
void clear_judge(int array[][14], int b_num); //クリア判定
void make_flag(int array[][14]);//フラグを立てる
void file(int b_num, const char* fileName, const char* time);//ファイル操作

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


int main(int argc, char* argv[])
{
    WINDOW* win;
    time_t start_time, end_time;

    //文字列の保存用
    char t[256];

    //キー入力の変数宣言
    int key = 0;

    //iniファイルの読み込み(上手くいかない場合はパスを変更する)
    int bom_num;
    char filename[256];
    bom_num = GetPrivateProfileInt("bomb", "num", -1, "..//C_MineSweeper//setting.ini");
    GetPrivateProfileString("file", "name", "orz", filename, 124, "..//C_MineSweeper//setting.ini");

    //表示するかしないかの変数宣言
    int box_display[14][14] = { {0} ,{0} };

    //爆弾の位置とまわりの爆弾の個数の宣言
    //爆弾がある箇所は(-1),まわりの爆弾の個数はその数を格納
    int bom[14][14] = { {0} ,{0} };

    //初期化
    if (initscr() == NULL) {
        return 1;
    }

    //エコー／バッファリング禁止 
    noecho();
    cbreak();

    //爆弾の作成
    set_bom(bom, bom_num);

    //爆弾の個数の作成
    set_bom_num(bom);

    //ウィンドウ作成 
    win = newwin(LINES, COLS, 0, 0);

    while (true) {

        // 画面をクリア
        erase();

        //キーチェック
        key = key_check();


        /*---------以下、ゲームフラグの分岐によって描画------*/

        switch (game_flag) {

        case 0://ゲームの説明
            //タイトル
            start_display(bom_num, win);

            if (key == 5) {
                game_flag = 1;
                //処理開始前の時間を取得
                start_time = time(NULL);
            }
            break;


        case 1://ゲームをしているときの画面
            instructions_display(win);

            //キーに応じて処理
            switch (key) {

            case 1:
                if (n > 1) {
                    n--;
                }
                break;
            case 2:
                if (n < 12) {
                    n++;
                }
                break;
            case 3:
                if (m > 1) {
                    m--;
                }
                break;
            case 4:
                if (m < 12) {
                    m++;
                }
                break;
            case 5:
                select_judge(box_display, bom);
                break;
            case 6:
                make_flag(box_display);
                break;
            }


            clear_judge(box_display, bom_num);

            //処理終了後の時間を取得
            end_time = time(NULL);


            //枠の描写
            draw_frame(win);
            //セレクトしている場所をオレンジ色で描写
            select_frame(m, n, win);
            //ボックスの描写
            draw_box(box_display, bom, win);
            break;

        case 2://ゲームオーバーの画面
            failed_display(win);
            Sleep(100);
            if (key == 5) {
                game_flag = 1;
            }
            break;

        case 3://ゲームクリアの画面
            clear_display(t, win);
            int timer = end_time - start_time;
            sprintf_s(t, "%d", timer);
            file(bom_num, "clear_time.txt", t);
            if (key == 5) {
                memset(box_display, 0, 196 * sizeof(box_display[0][0]));//初期化
                memset(bom, 0, 196 * sizeof(bom[0][0]));//初期化
                //爆弾の作成
                set_bom(bom, bom_num);

                //爆弾の個数の作成
                set_bom_num(bom);

                game_flag = 0;
            }
            break;

        }

        /*--------------------画面を更新----------------------*/

        wrefresh(win);
        wclear(win);

    }
    return 0;
}


void select_frame(int x, int y, WINDOW* w) {//選択した枠をオレンジ色にする

 //文字色を黄色に設定
 //色2:黄色
    init_pair(2, COLOR_YELLOW, COLOR_BLACK);
    wcolor_set(w, 2, NULL);

    //選択している枠の描画
    mvwaddstr(w, m * 2 + 1, n * 4 + 1, "+");
    mvwaddstr(w, m * 2 + 3, n * 4 + 1, "+");
    mvwaddstr(w, m * 2 + 1, n * 4 + 5, "+");
    mvwaddstr(w, m * 2 + 3, n * 4 + 5, "+");

    mvwaddstr(w, m * 2 + 2, n * 4 + 1, "|");
    mvwaddstr(w, m * 2 + 2, n * 4 + 5, "|");

    mvwaddstr(w, m * 2 + 1, n * 4 + 3, "-");
    mvwaddstr(w, m * 2 + 3, n * 4 + 3, "-");

    mvwaddstr(w, 20, 110, " ");//カーソル邪魔
}

int  key_check() {//キー判定
    if ((GetKeyState(VK_LEFT) & 0x8000) && key_flag) {//左のキー入力
        key_flag = false;
        return 1;
    }
    else if ((GetKeyState(VK_RIGHT) & 0x8000) && key_flag) {//右キーの入力
        key_flag = false;
        return 2;
    }
    else if ((GetKeyState(VK_UP) & 0x8000) && key_flag) {//上キーの入力
        key_flag = false;
        return 3;
    }
    else if ((GetKeyState(VK_DOWN) & 0x8000) && key_flag) {//下キーの入力
        key_flag = false;
        return 4;
    }
    else if ((GetKeyState(VK_RETURN) & 0x8000) && key_flag) {//エンターキーの入力
        key_flag = false;
        return 5;

    }
    else if ((GetKeyState(VK_SPACE) & 0x8000) && key_flag) {//シフトキーの入力
        key_flag = false;
        return 6;

    }
    else if (!(GetKeyState(VK_LEFT) & 0x8000) && !(GetKeyState(VK_RIGHT) & 0x8000) && !(GetKeyState(VK_UP) & 0x8000) && !(GetKeyState(VK_DOWN) & 0x8000) && !(GetKeyState(VK_RETURN) & 0x8000)) {
        key_flag = true;
        return 0;
    }

}

void set_bom(int bom_array[][14], int b_num) {//爆弾をセット

    Bomb x, y;
    srand((unsigned int)time(NULL));//乱数の初期化

    x.bomb = 0;
    y.bomb = 0;

    int count = 0;

    while (count < b_num) {

        x.bomb = rand() % 12 + 1;
        y.bomb = rand() % 12 + 1;

        if (bom_array[y.bomb][x.bomb] == 0) {
            bom_array[y.bomb][x.bomb] = -1;
            count++;
        }
    }


}

void set_bom_num(int bom_array[][14]) {//付近の爆弾の個数をセットする

    for (int i = 1; i <= 12; i++) {
        for (int j = 1; j <= 12; j++) {
            if (bom_array[i][j] != -1) {
                count_bom(i, j, bom_array);
            }
        }
    }
}

void count_bom(int i, int j, int bom_array[][14]) {//付近の爆弾の個数をカウントする

    int bom_num2 = 0;

    for (int k = -1; k <= 1; k++) {
        for (int l = -1; l <= 1; l++) {
            if (bom_array[i + k][j + l] == -1) {
                bom_num2++;
            }
        }
    }
    bom_array[i][j] = bom_num2;
}

void select_judge(int box_array[][14], int bom_array[][14]) {//選択したボックスが爆弾なのか、数字なのか、空なのかを判別

    if (box_array[m][n] == 0) {//選択したboxが空白だった場合のみ処理
        if (bom_array[m][n] == -1) {
            game_flag = 2;
        }
        else if (bom_array[m][n] == 0) {
            box_open(m, n, box_array, bom_array);
        }
        else {
            box_array[m][n] = 1;
        }
    }
}


void clear_judge(int array[][14], int b_num) {//クリア判定

    int bom_count = 0;

    int null_box = 144 - b_num;

    for (int i = 1; i <= 12; i++) {
        for (int j = 1; j <= 12; j++) {
            if (array[i][j] == 1) {
                bom_count++;
            }
        }
    }

    if (bom_count == null_box) {
        game_flag = 3;
    }

}

void make_flag(int array[][14]) {

    if (array[m][n] == 0) {
        array[m][n] = 2;
    }
    else if (array[m][n] == 2) {
        array[m][n] = 0;
    }
}

void file(int b_num, const char* fileName, const char *time) {
    //ファイルポインタの宣言
    FILE* fp;
    errno_t error;
    error = fopen_s(&fp, fileName, "w");
    if (error != 0)
        fprintf_s(stderr, "failed to open");
    else {
        fprintf_s(fp, "%s\n", "リザルト");
        fprintf_s(fp, "%s %d %s\n", "挑戦した爆弾の個数：", b_num, "個");
        fprintf_s(fp, "%s %s %s\n", "今回のクリアタイム：",  time, "秒");
        fclose(fp);   
    }
}

