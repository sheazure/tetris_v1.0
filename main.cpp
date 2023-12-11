/*
Notes: координатой блока является левый верхний его блок
в считывании клавиш надо сделать при прокрутке блока чтобы смещалась его главная точка
разобраться почему застревает квадрат после T




План для добавления новой фигуры:
1 - Отрисовка и очистка
2 - Проверка упал ли он
3 - можно ли нажать на кнопку


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


void cleaning_field_figure(char(&ptr_matrix)[32][32], int last_pos_x, int last_pos_y, int currentBlock, int rotate);
void writing_field_figure(char(&ptr_matrix)[32][32], int currentBlock, int rotate);


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
    int current_block = rand() % 2 + 1;
    int rotate_pos_block = 1;
    while (1) {
        // сделать выход из прогрммы
        // сделать проверку какой сейчас блок и исходя из этого выдать ему соответствующие координаты

        if (_kbhit()) {
            switch (_getch()) {
            case 80: // полностью переписать




            case 72: // вращение
                if (current_block == 1) break;
                cleaning_field_figure(matrix, last_block_position_x, last_block_position_y, current_block, rotate_pos_block);
                if (rotate_pos_block == 4) {
                    rotate_pos_block = 1;
                }
                else {
                    rotate_pos_block += 1;
                }
                break;
             
            }

        }
        
        
        system("cls");
        

        // проверка упал ли блок
        switch (current_block) {
        case 1:
            if (matrix[block_position_y + 1][block_position_x] == '1' || matrix[block_position_y + 1][block_position_x] == '#' || matrix[block_position_y + 1][block_position_x + 1] == '1' || matrix[block_position_y + 1][block_position_x + 1] == '#') {
                block_position_x = 10;
                block_position_y = 1;
                last_block_position_x = 10;
                last_block_position_y = 1;
                current_block = rand() % 2 + 1;
            }
            

        case 2:
            switch (rotate_pos_block) {
            case 1: // inverted T
                if (matrix[block_position_y + 1][block_position_x - 1] == '1' || matrix[block_position_y + 1][block_position_x - 1] == '#' || matrix[block_position_y + 1][block_position_x] == '1' || matrix[block_position_y + 1][block_position_x] == '#' || matrix[block_position_y + 1][block_position_x + 1] == '1' || matrix[block_position_y + 1][block_position_x + 1] == '#') {
                    
                    block_position_x = 10;
                    block_position_y = 1;
                    last_block_position_x = 10;
                    last_block_position_y = 1;
                    current_block = rand() % 2 + 1;
                    
                }
                break;

            case 2: // |-
                if (matrix[block_position_y + 2][block_position_x] == '1' || matrix[block_position_y + 1][block_position_x + 1] == '1' || matrix[block_position_y + 2][block_position_x] == '#') {
                    
                    block_position_x = 10;
                    block_position_y = 1;
                    last_block_position_x = 10;
                    last_block_position_y = 1;
                    current_block = rand() % 2 + 1;
                    
                }
                break;

            case 3: // T
                if (matrix[block_position_y][block_position_x - 1] == '1' || matrix[block_position_y + 1][block_position_x] == '1' || matrix[block_position_y + 1][block_position_x] == '#' || matrix[block_position_y][block_position_x + 1] == '1') {
                    block_position_x = 10;
                    block_position_y = 1;
                    last_block_position_x = 10;
                    last_block_position_y = 1;
                    current_block = rand() % 2 + 1;
                }
                break;
            case 4: // -|
                if (matrix[block_position_y + 2][block_position_x] == '1' || matrix[block_position_y + 2][block_position_x] == '#' || matrix[block_position_y + 1][block_position_x - 1] == '1') {
                    
                    block_position_x = 10;
                    block_position_y = 1;
                    last_block_position_x = 10;
                    last_block_position_y = 1;
                    current_block = rand() % 2 + 1;
                    
                }
                break;
            }
        }

        // отрисовка блока
        
        cleaning_field_figure(matrix, last_block_position_x, last_block_position_y, current_block, rotate_pos_block);
        writing_field_figure(matrix, current_block, rotate_pos_block);

        

        // вывод матрицы
        for (int i = 0; i < HEIGHT; i++) {
            for (int j = 0; j < WIDTH; j++) {
                std::cout << matrix[i][j];
            }
            std::cout << '\n';
        }
        
        last_block_position_x = block_position_x;
        last_block_position_y = block_position_y;
        // спуск вниз наа 1
        block_position_y += 1;
  
        
    }
}


void cleaning_field_figure(char(&ptr_matrix)[32][32], int last_pos_x, int last_pos_y, int currentBlock, int rotate) {
    // cleaning field after figure
    switch (currentBlock) {
    case 1:
        ptr_matrix[last_pos_y][last_pos_x] = ' ';
        ptr_matrix[last_pos_y][last_pos_x + 1] = ' ';
        ptr_matrix[last_pos_y + 1][last_pos_x] = ' ';
        ptr_matrix[last_pos_y + 1][last_pos_x + 1] = ' ';
        break;
    case 2:
        switch (rotate) {
        case 1: // T inverted
            ptr_matrix[last_pos_y][last_pos_x] = ' ';
            ptr_matrix[last_pos_y + 1][last_pos_x - 1] = ' ';
            ptr_matrix[last_pos_y + 1][last_pos_x] = ' ';
            ptr_matrix[last_pos_y + 1][last_pos_x + 1] = ' ';
            break;
        case 2:
            ptr_matrix[last_pos_y][last_pos_x] = ' ';
            ptr_matrix[last_pos_y + 1][last_pos_x] = ' ';
            ptr_matrix[last_pos_y + 1][last_pos_x + 1] = ' ';
            ptr_matrix[last_pos_y + 2][last_pos_x] = ' ';
            break;
        case 3:
            ptr_matrix[last_pos_y][last_pos_x - 1] = ' ';
            ptr_matrix[last_pos_y][last_pos_x] = ' ';
            ptr_matrix[last_pos_y + 1][last_pos_x] = ' ';
            ptr_matrix[last_pos_y][last_pos_x + 1] = ' ';
            break;
        case 4:
            ptr_matrix[last_pos_y][last_pos_x] = ' ';
            ptr_matrix[last_pos_y + 1][last_pos_x] = ' ';
            ptr_matrix[last_pos_y + 1][last_pos_x - 1] = ' ';
            ptr_matrix[last_pos_y + 2][last_pos_x] = ' ';
            break;
        }

    }
    
}

void writing_field_figure(char(&ptr_matrix)[32][32], int currentBlock, int rotate) {


    // writing figure
    switch (currentBlock) {
    case 1:
        ptr_matrix[block_position_y][block_position_x] = '1';
        ptr_matrix[block_position_y][block_position_x + 1] = '1';
        ptr_matrix[block_position_y + 1][block_position_x] = '1';
        ptr_matrix[block_position_y + 1][block_position_x + 1] = '1';
        break;
    case 2:
        switch (rotate) {
        case 1: // T inverted
            ptr_matrix[block_position_y][block_position_x] = '1';
            ptr_matrix[block_position_y + 1][block_position_x - 1] = '1';
            ptr_matrix[block_position_y + 1][block_position_x] = '1';
            ptr_matrix[block_position_y + 1][block_position_x + 1] = '1';
            break;
        case 2: // |-    <- figure
            ptr_matrix[block_position_y][block_position_x] = '1';
            ptr_matrix[block_position_y + 1][block_position_x] = '1';
            ptr_matrix[block_position_y + 1][block_position_x + 1] = '1';
            ptr_matrix[block_position_y + 2][block_position_x] = '1';
            break;
        case 3: // T исключение главная точка верхняя центраальная
            ptr_matrix[block_position_y][block_position_x - 1] = '1';
            ptr_matrix[block_position_y][block_position_x] = '1';
            ptr_matrix[block_position_y + 1][block_position_x] = '1';
            ptr_matrix[block_position_y][block_position_x + 1] = '1';
            break;
        case 4: // -|
            ptr_matrix[block_position_y][block_position_x] = '1';
            ptr_matrix[block_position_y + 1][block_position_x] = '1';
            ptr_matrix[block_position_y + 1][block_position_x - 1] = '1';
            ptr_matrix[block_position_y + 2][block_position_x] = '1';
            break;
        }
    }
        
    
    
}
