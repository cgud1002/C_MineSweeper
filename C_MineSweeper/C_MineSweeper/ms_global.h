#pragma once

WINDOW* win;
time_t start_time, end_time;

//���e�̍��W�̍\����
struct Bomb {
    int bomb;
};

//�O���[�o���ϐ�
unsigned int game_flag = 0;

//�{�b�N�X�̍��W�錾
int m = 1;
int n = 1;

//�L�[����̃t���O
bool key_flag = true;
