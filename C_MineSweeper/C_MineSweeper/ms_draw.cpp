#include <stdio.h>
#include <curses.h>
#include <Windows.h>
#include <math.h>
#include <time.h>
#include <direct.h>

#include "ms_draw.h"

//�g�̕`��
void draw_frame(WINDOW* w) {

    start_color();
    //�F1:���F
    init_pair(1, COLOR_WHITE, COLOR_BLACK);
    wcolor_set(w, 1, NULL);

    for (int i = 1; i <= 13; i++) {
        for (int j = 1; j <= 13; j++) {
            mvwaddstr(w, i * 2 + 1, j * 4 + 1, "+");
        }
    }
    for (int i = 1; i <= 12; i++) {
        for (int j = 1; j <= 13; j++) {
            mvwaddstr(w, i * 2 + 2, j * 4 + 1, "|");
        }
    }
    for (int i = 1; i <= 13; i++) {
        for (int j = 1; j <= 12; j++) {
            mvwaddstr(w, i * 2 + 1, j * 4 + 3, "-");
        }
    }
}

//�{�b�N�X�̒��g�̕`��
void draw_box(int box_array[][14], int bom_array[][14], WINDOW* w) {

    //�F1:���F
    init_pair(1, COLOR_WHITE, COLOR_BLACK);
    wcolor_set(w, 1, NULL);

    for (int i = 1; i <= 12; i++) {
        for (int j = 1; j <= 12; j++) {
            if (box_array[i][j] == 0) {
                mvwaddstr(w, i * 2 + 2, j * 4 + 3, "*");
            }
            else if (box_array[i][j] == 1) {
                if (bom_array[i][j] == 0) {
                    mvwaddstr(w, i * 2 + 2, j * 4 + 2, " ");
                }
                else {
                    char s[256];
                    sprintf_s(s, "%d", bom_array[i][j]);
                    mvwaddstr(w, i * 2 + 2, j * 4 + 3, s);
                }
            }
            else {
                mvwaddstr(w, i * 2 + 2, j * 4 + 2, "��");
            }
        }
    }

}

void start_display(int b_num, WINDOW* w) {//�X�^�[�g���

    mvwaddstr(w, 10, 2, "*       *");
    mvwaddstr(w, 11, 2, "* *   * *");
    mvwaddstr(w, 12, 2, "*  * *  *");
    mvwaddstr(w, 13, 2, "*   *   *");
    mvwaddstr(w, 14, 2, "*       *");

    mvwaddstr(w, 10, 12, "  *****  ");
    mvwaddstr(w, 11, 12, "    *    ");
    mvwaddstr(w, 12, 12, "    *    ");
    mvwaddstr(w, 13, 12, "    *    ");
    mvwaddstr(w, 14, 12, "  *****  ");

    mvwaddstr(w, 10, 22, "*       *");
    mvwaddstr(w, 11, 22, "* *     *");
    mvwaddstr(w, 12, 22, "*   *   *");
    mvwaddstr(w, 13, 22, "*     * *");
    mvwaddstr(w, 14, 22, "*       *");

    mvwaddstr(w, 10, 32, " ******* ");
    mvwaddstr(w, 11, 32, " *       ");
    mvwaddstr(w, 12, 32, " ******* ");
    mvwaddstr(w, 13, 32, " *       ");
    mvwaddstr(w, 14, 32, " ******* ");

    mvwaddstr(w, 9, 42, "     .   ");
    mvwaddstr(w, 10, 42, "    :    ");
    mvwaddstr(w, 11, 42, "   ***   ");
    mvwaddstr(w, 12, 42, " ******* ");
    mvwaddstr(w, 13, 42, " ******* ");
    mvwaddstr(w, 14, 42, "   ***  ");

    mvwaddstr(w, 10, 52, " ******* ");
    mvwaddstr(w, 11, 52, " *       ");
    mvwaddstr(w, 12, 52, " ******* ");
    mvwaddstr(w, 13, 52, "       * ");
    mvwaddstr(w, 14, 52, " ******* ");

    mvwaddstr(w, 10, 62, "*       *");
    mvwaddstr(w, 11, 62, "*   *   *");
    mvwaddstr(w, 12, 62, "*  * *  *");
    mvwaddstr(w, 13, 62, "* *   * *");
    mvwaddstr(w, 14, 62, "*       *");

    mvwaddstr(w, 10, 72, " ******* ");
    mvwaddstr(w, 11, 72, " *       ");
    mvwaddstr(w, 12, 72, " ******* ");
    mvwaddstr(w, 13, 72, " *       ");
    mvwaddstr(w, 14, 72, " ******* ");

    mvwaddstr(w, 10, 81, " ******* ");
    mvwaddstr(w, 11, 81, " *       ");
    mvwaddstr(w, 12, 81, " ******* ");
    mvwaddstr(w, 13, 81, " *       ");
    mvwaddstr(w, 14, 81, " ******* ");

    mvwaddstr(w, 10, 90, " ******* ");
    mvwaddstr(w, 11, 90, " *      *");
    mvwaddstr(w, 12, 90, " ******* ");
    mvwaddstr(w, 13, 90, " *       ");
    mvwaddstr(w, 14, 90, " *       ");

    mvwaddstr(w, 10, 100, " ******* ");
    mvwaddstr(w, 11, 100, " *       ");
    mvwaddstr(w, 12, 100, " ******* ");
    mvwaddstr(w, 13, 100, " *       ");
    mvwaddstr(w, 14, 100, " ******* ");

    mvwaddstr(w, 10, 109, " ******  ");
    mvwaddstr(w, 11, 109, " *     * ");
    mvwaddstr(w, 12, 109, " ******  ");
    mvwaddstr(w, 13, 109, " *    *  ");
    mvwaddstr(w, 14, 109, " *     * ");

    char mine[256];
    sprintf_s(mine, "%d", b_num);
    mvwaddstr(w, 20, 50, "�n���̐��F");
    mvwaddstr(w, 20, 61, mine);
    mvwaddstr(w, 20, 63, "��");
    mvwaddstr(w, 22, 43, "���@press Enter key to start�@��");

}


void clear_display(const char* time, WINDOW* w) {//�N���A���

    mvwaddstr(w, 10, 7, " ******  ");
    mvwaddstr(w, 11, 7, "*        ");
    mvwaddstr(w, 12, 7, "*  ***** ");
    mvwaddstr(w, 13, 7, "*      * ");
    mvwaddstr(w, 14, 7, " ******  ");

    mvwaddstr(w, 10, 17, "   ***   ");
    mvwaddstr(w, 11, 17, "  *   *  ");
    mvwaddstr(w, 12, 17, " ******* ");
    mvwaddstr(w, 13, 17, "*       *");
    mvwaddstr(w, 14, 17, "*       *");

    mvwaddstr(w, 10, 27, "*       *");
    mvwaddstr(w, 11, 27, "* *   * *");
    mvwaddstr(w, 12, 27, "*  * *  *");
    mvwaddstr(w, 13, 27, "*   *   *");
    mvwaddstr(w, 14, 27, "*       *");

    mvwaddstr(w, 10, 37, " ******* ");
    mvwaddstr(w, 11, 37, " *       ");
    mvwaddstr(w, 12, 37, " ******* ");
    mvwaddstr(w, 13, 37, " *       ");
    mvwaddstr(w, 14, 37, " ******* ");


    mvwaddstr(w, 10, 57, "  ****** ");
    mvwaddstr(w, 11, 57, " *      *");
    mvwaddstr(w, 12, 57, " *       ");
    mvwaddstr(w, 13, 57, " *      *");
    mvwaddstr(w, 14, 57, "  ****** ");

    mvwaddstr(w, 10, 67, " *       ");
    mvwaddstr(w, 11, 67, " *       ");
    mvwaddstr(w, 12, 67, " *       ");
    mvwaddstr(w, 13, 67, " *       ");
    mvwaddstr(w, 14, 67, " ******* ");

    mvwaddstr(w, 10, 77, " ******* ");
    mvwaddstr(w, 11, 77, " *       ");
    mvwaddstr(w, 12, 77, " ******* ");
    mvwaddstr(w, 13, 77, " *       ");
    mvwaddstr(w, 14, 77, " ******* ");

    mvwaddstr(w, 10, 87, "   ***   ");
    mvwaddstr(w, 11, 87, "  *   *  ");
    mvwaddstr(w, 12, 87, " ******* ");
    mvwaddstr(w, 13, 87, "*       *");
    mvwaddstr(w, 14, 87, "*       *");

    mvwaddstr(w, 10, 97, " ******  ");
    mvwaddstr(w, 11, 97, " *     * ");
    mvwaddstr(w, 12, 97, " ******  ");
    mvwaddstr(w, 13, 97, " *    *  ");
    mvwaddstr(w, 14, 97, " *     * ");

    mvwaddstr(w, 10, 107, "   **    ");
    mvwaddstr(w, 11, 107, "   **    ");
    mvwaddstr(w, 12, 107, "   **    ");
    mvwaddstr(w, 13, 107, "         ");
    mvwaddstr(w, 14, 107, "   **    ");

    //���Ԃ�\��
    mvwaddstr(w, 20, 48, "�N���A�^�C���F");
    mvwaddstr(w, 20, 65, time);
    mvwaddstr(w, 20, 68, "�b");


    mvwaddstr(w, 25, 38, "���@press Enter key to back to the title�@��");

}

void instructions_display(WINDOW* w) {//�������

    mvwaddstr(w, 4, 82, "�`���[���`");
    mvwaddstr(w, 6, 60, "�E�}�X�ڂ��J���Ă����A�n���ȊO���ׂĂ��J���ƃN���A�I");
    mvwaddstr(w, 8, 60, "�E�n���̃}�X���J���Ă��܂��ƃQ�[���I�[�o�[");
    mvwaddstr(w, 10, 60, "�E�n��������Ɨ\�z�����ꏊ�ɂ͊��𗧂Ă悤�I");
    mvwaddstr(w, 12, 60, "�E���� -> �אڂ���}�X�ڂɒn���������邩");
    mvwaddstr(w, 14, 60, "�E�I�𒆂̃}�X�� -> �I�����W�F");
    mvwaddstr(w, 16, 60, "�E�f�t�H���g�̃}�X�� -> �u*�v");
    mvwaddstr(w, 18, 60, "�E�t���O�𗧂Ă��}�X�� -> �u���v");

    mvwaddstr(w, 22, 81, "�`������@�`");
    mvwaddstr(w, 24, 60, "�EEnter�L�[ -> �}�X�ڂ��J����");
    mvwaddstr(w, 26, 60, "�ESpace�L�[ -> �}�X�ڂɊ�(��)�𗧂Ă�/�O��");
    mvwaddstr(w, 28, 60, "�E�\���L�[ -> �ړ�");

}

void failed_display(WINDOW* w) {

    mvwaddstr(w, 10, 7, " ******  ");
    mvwaddstr(w, 11, 7, "*        ");
    mvwaddstr(w, 12, 7, "*  ***** ");
    mvwaddstr(w, 13, 7, "*      * ");
    mvwaddstr(w, 14, 7, " ******  ");

    mvwaddstr(w, 10, 17, "   ***   ");
    mvwaddstr(w, 11, 17, "  *   *  ");
    mvwaddstr(w, 12, 17, " ******* ");
    mvwaddstr(w, 13, 17, "*       *");
    mvwaddstr(w, 14, 17, "*       *");

    mvwaddstr(w, 10, 27, "*       *");
    mvwaddstr(w, 11, 27, "* *   * *");
    mvwaddstr(w, 12, 27, "*  * *  *");
    mvwaddstr(w, 13, 27, "*   *   *");
    mvwaddstr(w, 14, 27, "*       *");

    mvwaddstr(w, 10, 37, " ******* ");
    mvwaddstr(w, 11, 37, " *       ");
    mvwaddstr(w, 12, 37, " ******* ");
    mvwaddstr(w, 13, 37, " *       ");
    mvwaddstr(w, 14, 37, " ******* ");


    mvwaddstr(w, 10, 57, " ******* ");
    mvwaddstr(w, 11, 57, "*       *");
    mvwaddstr(w, 12, 57, "*       *");
    mvwaddstr(w, 13, 57, "*       *");
    mvwaddstr(w, 14, 57, " ******* ");

    mvwaddstr(w, 10, 67, "*       * ");
    mvwaddstr(w, 11, 67, " *     *  ");
    mvwaddstr(w, 12, 67, "  *   *   ");
    mvwaddstr(w, 13, 67, "   * *    ");
    mvwaddstr(w, 14, 67, "    *     ");

    mvwaddstr(w, 10, 77, " ******* ");
    mvwaddstr(w, 11, 77, " *       ");
    mvwaddstr(w, 12, 77, " ******* ");
    mvwaddstr(w, 13, 77, " *       ");
    mvwaddstr(w, 14, 77, " ******* ");

    mvwaddstr(w, 10, 87, " ******  ");
    mvwaddstr(w, 11, 87, " *     * ");
    mvwaddstr(w, 12, 87, " ******  ");
    mvwaddstr(w, 13, 87, " *    *  ");
    mvwaddstr(w, 14, 87, " *     * ");


    mvwaddstr(w, 13, 97, "   **   **   **");
    mvwaddstr(w, 14, 97, "   **   **   **");
    mvwaddstr(w, 20, 35, "���@press Enter key to continue the game�@��");
}