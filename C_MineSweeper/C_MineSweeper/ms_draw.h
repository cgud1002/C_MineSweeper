#pragma once

void draw_frame(WINDOW* w);//�g�̕`��
void draw_box(int box_array[][14], int bom_array[][14], WINDOW* w);//�{�b�N�X�̒��g�̕`��
void start_display(int b_num, WINDOW* w);//�X�^�[�g��ʂ�\��
void clear_display(const char* time, WINDOW* w);//�N���A��ʂ�\��
void failed_display(WINDOW* w);//�Q�[���I�[�o�[��ʂ�\��
void instructions_display(WINDOW* w);//��������\��