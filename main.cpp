/*
Notes: координатой блока является левый верхний его блок
*/



#include <iostream>
#include <Windows.h>
#include <cstring>
#include <conio.h>
#include <random>

const int WIDTH = 32;
const int HEIGHT = 32;

char matrix[32][32];
int block_position_x = 1;
int block_position_y = 10;


void writing_cube(char(&matrix1)[32][32]);
void cleaning_field_cube(char(&ptr_matrix)[32][32], int last_pos_x, int last_pos_y);

void writing_I(char(&ptr_matrix)[32][32]);
void cleaning_field_I(char(&ptr_matrix)[32][32], int last_pos_x, int last_pos_y);

void writing_S(char(&ptr_matrix)[32][32]);
void cleaning_field_S(char(&ptr_matrix)[32][32], int last_pos_x, int last_pos_y);

void writing_Z(char(&ptr_matrix)[32][32]);
void cleaning_field_Z(char(&ptr_matrix)[32][32], int last_pos_x, int last_pos_y);

void writing_L(char(&ptr_matrix)[32][32]);
void cleaning_field_L(char(&ptr_matrix)[32][32], int last_pos_x, int last_pos_y);

void writing_mirrorL(char(&ptr_matrix)[32][32]);
void cleaning_field_mirrorL(char(&ptr_matrix)[32][32], int last_pos_x, int last_pos_y);

void writing_T(char(&ptr_matrix)[32][32]);
void cleaning_field_T(char(&ptr_matrix)[32][32], int last_pos_x, int last_pos_y);


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



    

   
    int current_block = rand() % 7 + 1; // 1 - cube, 2 - I, 3 - S, 4 - Z, 5 - L, 6 - mirror L, 7 - T

    block_position_x = 1;
    block_position_y = 10;
    int last_block_position_x = block_position_x;
    int last_block_position_y = block_position_y;
    while (1) { // игра идет
        Sleep(10);
        system("cls");
        // очистить игровое поле
        if (matrix[block_position_x + 1][block_position_y] == '1' and block_position_x <= 2) {
            Sleep(2000);
            system("cls");
            char event;
            std::cout << "Хотите сыграть еще?(y/n): ";
            std::cin >> event;
            break;

        }

        if (matrix[block_position_x + 1][block_position_y] == '1' or matrix[block_position_x + 1][block_position_y] == '#') {
            block_position_x = 1;
            block_position_y = 10;
            last_block_position_x = 1;
            last_block_position_y = 10;
            

        }
      
        cleaning_field_cube(matrix, last_block_position_x, last_block_position_y);
        writing_cube(matrix);

 

        for (int i = 0; i < HEIGHT; ++i) {
            for (int j = 0; j < WIDTH; ++j) {
                std::cout << matrix[i][j];
            }
            std::cout << '\n';
        }
        last_block_position_x = block_position_x;
        last_block_position_y = block_position_y;
        ++block_position_x;

        

    }
    return 0;
}

void cleaning_field_cube(char(&ptr_matrix)[32][32], int last_pos_x, int last_pos_y) {
    // cleaning field after cube
    ptr_matrix[last_pos_x][last_pos_y] = ' ';
    ptr_matrix[last_pos_x][last_pos_y + 1] = ' ';
    ptr_matrix[last_pos_x + 1][last_pos_y] = ' ';
    ptr_matrix[last_pos_x + 1][last_pos_y + 1] = ' ';


}

void writing_cube(char(&ptr_matrix)[32][32]) {


    // writing cube
    ptr_matrix[block_position_x][block_position_y] = '1';
    ptr_matrix[block_position_x][block_position_y + 1] = '1';
    ptr_matrix[block_position_x + 1][block_position_y] = '1';
    ptr_matrix[block_position_x + 1][block_position_y + 1] = '1';
}
