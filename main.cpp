/*
Notes: координатой блока является левый верхний его блок
*/



#include <iostream>
#include <Windows.h>
#include <cstring>
#include <conio.h>
#include <stdio.h>
#include <random>

const int WIDTH = 32;
const int HEIGHT = 32;

char matrix[32][32];
int block_position_y = 1;
int block_position_x = 10;


void cleaning_field_figure(char(&ptr_matrix)[32][32], int last_pos_x, int last_pos_y, int currentBlock);
void writing_field_figure(char(&ptr_matrix)[32][32], int currentBlock);


int main() {


    for (int i = 0; i < HEIGHT; ++i) {
        if (i == 0 || i == 31) {
            for (int j = 0; j < WIDTH; ++j) {
                matrix[i][j] = '#';
            }
            continue;
        }

        for (int j = 0; j < WIDTH; ++j) {
            if (j == 21) {
                matrix[i][j] = '#';
                continue;
            }
            matrix[i][j] = ' ';
        }

        matrix[i][0] = '#';
        matrix[i][31] = '#';
    }
    int last_block_position_x = 10;
    int last_block_position_y = 1;
    int current_block = 1;
    int rotate_pos_block = 1;
    while (1) {
        
        system("cls");

        if (matrix[block_position_y + 1][block_position_x] == '1' || matrix[block_position_y + 1][block_position_x] == '#' || matrix[block_position_y + 1][block_position_x + 1] == '1' || matrix[block_position_y + 1][block_position_x + 1] == '#') {
            block_position_x = 10;
            block_position_y = 1;
            last_block_position_x = 10;
            last_block_position_y = 1;
        }

        cleaning_field_figure(matrix, last_block_position_x, last_block_position_y, 1);
        writing_field_figure(matrix, 1);
        


        for (int i = 0; i < HEIGHT; i++) {
            for (int j = 0; j < WIDTH; j++) {
                std::cout << matrix[i][j];
            }
            std::cout << '\n';
        }
        
        last_block_position_x = block_position_x;
        last_block_position_y = block_position_y;
        block_position_y += 1;
        if (_kbhit()) {
            switch (_getch()) {
            case 80: // down
                switch (current_block) {
                case 1:
                    if (matrix[block_position_y][block_position_x] == '#' || matrix[block_position_y][block_position_x] == '1' || matrix[block_position_y][block_position_x + 1] == '#' || matrix[block_position_y][block_position_x + 1] == '1') {

                    }
                    else {
                        block_position_y += 1;
                    }
                    break;
                }
                break;

            case 75: // left
                // проверка нет ли ничего слева
                switch (current_block) {
                case 1: // cube
                    if (matrix[block_position_y][block_position_x - 1] == '1' || matrix[block_position_y][block_position_x - 1] == '#' || matrix[block_position_y + 1][block_position_x - 1] == '1' || matrix[block_position_y + 1][block_position_x - 1] == '#') {

                    }
                    else {
                        block_position_x -= 1;
                        break;
                    }
                }
                break;

            case 77: // right
                // проверка нет ли ничего справа
                switch (current_block) {
                // проверка нет ли ничего справа
                case 1: // cube
                    if (matrix[block_position_y][block_position_x + 2] == '1' || matrix[block_position_y][block_position_x + 2] == '#' || matrix[block_position_y + 1][block_position_x + 2] == '1' || matrix[block_position_y + 1][block_position_x + 2] == '#') {

                    }
                    else {
                        block_position_x += 1;
                        break;
                    }
                }
                break;
                
            }
        }


       
    }
}


void cleaning_field_figure(char(&ptr_matrix)[32][32], int last_pos_x, int last_pos_y, int currentBlock) {
    // cleaning field after figure
    switch (currentBlock) {
    case 1:
        ptr_matrix[last_pos_y][last_pos_x] = ' ';
        ptr_matrix[last_pos_y][last_pos_x + 1] = ' ';
        ptr_matrix[last_pos_y + 1][last_pos_x] = ' ';
        ptr_matrix[last_pos_y + 1][last_pos_x + 1] = ' ';
        break;
    }
    
}

void writing_field_figure(char(&ptr_matrix)[32][32], int currentBlock) {


    // writing figure
    switch (currentBlock) {
    case 1:
        ptr_matrix[block_position_y][block_position_x] = '1';
        ptr_matrix[block_position_y][block_position_x + 1] = '1';
        ptr_matrix[block_position_y + 1][block_position_x] = '1';
        ptr_matrix[block_position_y + 1][block_position_x + 1] = '1';
        break;
    }
    
    
}
