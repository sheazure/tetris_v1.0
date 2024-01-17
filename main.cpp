/*
Notes: координатой блока является левый верхний его блок

разобраться почему застревает квадрат после T ----- выполнено!

чтобы перевести координаты x и y в порядковый номер светодиода нужно  --->>>> 32 * y + x

План для добавления новой фигуры:
1 - Отрисовка и очистка
2 - Проверка упал ли он
3 - можно ли нажать на кнопку

21.12.2023 - доделать кнопки left и right


line 199
line 278

*/



#include <iostream>
#include <Windows.h>
#include <cstring>
#include <conio.h>
#include <stdio.h>
#include <random>
#include <algorithm>

const int WIDTH = 32;
const int HEIGHT = 32;

char matrix[32][32];
char copy_matrix[32][32];
int block_position_y = 1;
int block_position_x = 10;
int last_block_position_x = 10;
int last_block_position_y = 1;
int current_block = rand() % 7 + 1; // менять по мере добавления блоков
int rotate_pos_block = 1;

int copy_current_block = 1;

int counter_1 = 158;
string last_move = "Null";





// прототипы функций
void cleaning_field_figure(char(&ptr_matrix)[32][32], int last_pos_x, int last_pos_y, int currentBlock, int rotate);
void writing_field_figure(char(&ptr_matrix)[32][32], int currentBlock, int rotate);
void check_block_fallen();
void check_click();






int main() {

    // первое заполнение матрицы(границы)
    for (int i = 0; i < HEIGHT; ++i) {
        if (i == 0 || i == 31) {
            for (int j = 0; j < WIDTH; ++j) {
                matrix[i][j] = '1';
            }
            continue;
        }

        for (int j = 0; j < WIDTH; ++j) {
            if (j == 21) {
                matrix[i][j] = '1';
                continue;
            }
            matrix[i][j] = ' ';
        }

        matrix[i][0] = '1';
        matrix[i][31] = '1';
    }

 

    while (1) {
        
        for (int i = 0; i < HEIGHT; i++) {
            for (int j = 0; j < WIDTH; j++) {
                copy_matrix[i][j] = matrix[i][j];
            }
        }



       
        system("cls");
        // сделать выход из прогрммы
       

        // считывание нажатий клавиш для движения/поворота фигуры
        check_click();
        
        // отрисовка блока на матрице
        
        cleaning_field_figure(matrix, last_block_position_x, last_block_position_y, copy_current_block, rotate_pos_block);
        writing_field_figure(matrix, copy_current_block, rotate_pos_block);
        
        // проверка упал ли блок
        check_block_fallen();


        
        
        // вывод матрицы

        for (int i = 0; i < HEIGHT; i++) {
            for (int j = 0; j < WIDTH; j++) {
                std::cout << matrix[i][j];
            }
            std::cout << '\n';
        }

        


        last_block_position_x = block_position_x;
        last_block_position_y = block_position_y;
        // спуск вниз на 1, блок падает вниз
        block_position_y += 1;
        



    }
}


void check_click() {
    if (_kbhit()) {
        switch (_getch()) {
        case 72: // up (поворот блока)
            cleaning_field_figure(matrix, last_block_position_x, last_block_position_y, copy_current_block, rotate_pos_block);
            if (rotate_pos_block == 4) rotate_pos_block = 1;
            else rotate_pos_block++;
            
            break;

        case 80: // down           
            
            block_position_y++;   
            last_move = "down";
            break;
        case 75: // left
            block_position_x--;
            last_move = "left";
            break;
        case 77: // right
            block_position_x++;
            last_move = "right";
            
            break;

        }

        
    }
    
}



// проверка упал ли блок
void check_block_fallen() {
    int counter1 = 0;

    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            if (matrix[i][j] == '1') {
                counter1++;
            }
        }
    }

    bool event = false;

    if (counter1 < counter_1 && last_move != "Null") {
        switch (last_move)  {
        case "left":
            block_position_x++;
            break;
        case "right":
            block_position_x--;
            break;
        case "Null":
            break;
        }
    }
    if (counter1 < counter_1) {
        for (int i = 0; i < HEIGHT; i++) {
            for (int j = 0; j < WIDTH; j++) {
                matrix[i][j] = copy_matrix[i][j];
            }
        }
        counter_1 += 4;
        block_position_x = 10;
        block_position_y = 1;
        last_block_position_x = 10;
        last_block_position_y = 1;
        current_block = rand() % 7 + 1;
        rotate_pos_block = 1;
        event = true;
    }

    if (event) {
        int counter = 0;
        for (int i = 1; i < 31; i++) { // игровое поле
            counter = 0;
            for (int j = 1; j < 21; j++) { // игровое поле
                if (matrix[i][j] == '1') counter++;
            }
            if (counter == 20) {
                for (int h = 1; h < 21; h++) {
                    matrix[i][h] = ' ';
                }
                counter_1 -= 20;

            }
        }
        
    }

    
}

// функции очистки и отрисовки поля после блоков
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
        case 2: // |-
            ptr_matrix[last_pos_y][last_pos_x] = ' ';
            ptr_matrix[last_pos_y + 1][last_pos_x] = ' ';
            ptr_matrix[last_pos_y + 1][last_pos_x + 1] = ' ';
            ptr_matrix[last_pos_y + 2][last_pos_x] = ' ';
            break;
        case 3: // T главная точка центральная
            ptr_matrix[last_pos_y][last_pos_x - 1] = ' ';
            ptr_matrix[last_pos_y][last_pos_x] = ' ';
            ptr_matrix[last_pos_y + 1][last_pos_x] = ' ';
            ptr_matrix[last_pos_y][last_pos_x + 1] = ' ';
            break;
        case 4: // -|
            ptr_matrix[last_pos_y][last_pos_x] = ' ';
            ptr_matrix[last_pos_y + 1][last_pos_x] = ' ';
            ptr_matrix[last_pos_y + 1][last_pos_x - 1] = ' ';
            ptr_matrix[last_pos_y + 2][last_pos_x] = ' ';
            break;
        }
        break;
    case 3:
        switch (rotate % 2) {
        case 1:
            ptr_matrix[last_pos_y][last_pos_x] = ' ';
            ptr_matrix[last_pos_y + 1][last_pos_x] = ' ';
            ptr_matrix[last_pos_y + 2][last_pos_x] = ' ';
            ptr_matrix[last_pos_y + 3][last_pos_x] = ' ';
            break;
        case 0:
            ptr_matrix[last_pos_y][last_pos_x - 1] = ' ';
            ptr_matrix[last_pos_y][last_pos_x] = ' ';
            ptr_matrix[last_pos_y][last_pos_x + 1] = ' ';
            ptr_matrix[last_pos_y][last_pos_x + 2] = ' ';
            break;
        }
        break;
    case 4: // S
        switch (rotate % 2) { // потому что поворотов фигуры всего 2
        case 1: // S
            ptr_matrix[last_pos_y][last_pos_x] = ' ';
            ptr_matrix[last_pos_y][last_pos_x + 1] = ' ';
            ptr_matrix[last_pos_y + 1][last_pos_x - 1] = ' ';
            ptr_matrix[last_pos_y + 1][last_pos_x] = ' ';
            break;
        case 0:
            ptr_matrix[last_pos_y][last_pos_x] = ' ';
            ptr_matrix[last_pos_y + 1][last_pos_x] = ' ';
            ptr_matrix[last_pos_y + 1][last_pos_x + 1] = ' ';
            ptr_matrix[last_pos_y + 2][last_pos_x + 1] = ' ';
            break;
        }
        break;

    case 5: // Z
        switch (rotate % 2) {
        case 1: // Z главная точка центр верх
            ptr_matrix[last_pos_y][last_pos_x] = ' ';
            ptr_matrix[last_pos_y][last_pos_x - 1] = ' ';
            ptr_matrix[last_pos_y + 1][last_pos_x] = ' ';
            ptr_matrix[last_pos_y + 1][last_pos_x + 1] = ' ';
            break;
        case 0: // главная точка верх
            ptr_matrix[last_pos_y][last_pos_x] = ' ';
            ptr_matrix[last_pos_y + 1][last_pos_x] = ' ';
            ptr_matrix[last_pos_y + 1][last_pos_x - 1] = ' ';
            ptr_matrix[last_pos_y + 2][last_pos_x - 1] = ' ';
            break;
        }
        break;

    case 6:
        switch (rotate) {
        case 1: // L главная точка верхняя
            ptr_matrix[last_pos_y][last_pos_x] = ' ';
            ptr_matrix[last_pos_y + 1][last_pos_x] = ' ';
            ptr_matrix[last_pos_y + 2][last_pos_x] = ' ';
            ptr_matrix[last_pos_y + 2][last_pos_x + 1] = ' ';
            break;
        case 2: // L angle 90 главная позиция центральная верхняя
            ptr_matrix[last_pos_y + 1][last_pos_x - 1] = ' ';
            ptr_matrix[last_pos_y][last_pos_x - 1] = ' ';
            ptr_matrix[last_pos_y][last_pos_x] = ' ';
            ptr_matrix[last_pos_y][last_pos_x + 1] = ' ';
            break;
        case 3: // L angle 180
            ptr_matrix[last_pos_y][last_pos_x] = ' ';
            ptr_matrix[last_pos_y][last_pos_x + 1] = ' ';
            ptr_matrix[last_pos_y + 1][last_pos_x + 1] = ' ';
            ptr_matrix[last_pos_y + 2][last_pos_x + 1] = ' ';
            break;
        case 4: // главная точка левая нижняя
            ptr_matrix[last_pos_y][last_pos_x - 1] = ' ';
            ptr_matrix[last_pos_y][last_pos_x] = ' ';
            ptr_matrix[last_pos_y][last_pos_x + 1] = ' ';
            ptr_matrix[last_pos_y - 1][last_pos_x + 1] = ' ';
            break;
        }
        break;
    case 7: // J
        switch (rotate) {
        case 1:
            ptr_matrix[last_pos_y][last_pos_x] = ' ';
            ptr_matrix[last_pos_y + 1][last_pos_x] = ' ';
            ptr_matrix[last_pos_y + 2][last_pos_x] = ' ';
            ptr_matrix[last_pos_y + 2][last_pos_x - 1] = ' ';
            break;
        case 2:
            ptr_matrix[last_pos_y][last_pos_x] = ' ';
            ptr_matrix[last_pos_y][last_pos_x - 1] = ' ';
            ptr_matrix[last_pos_y - 1][last_pos_x - 1] = ' ';
            ptr_matrix[last_pos_y][last_pos_x + 1] = ' ';
            break;
        case 3:
            ptr_matrix[last_pos_y][last_pos_x] = ' ';
            ptr_matrix[last_pos_y][last_pos_x + 1] = ' ';
            ptr_matrix[last_pos_y + 1][last_pos_x] = ' ';
            ptr_matrix[last_pos_y + 2][last_pos_x] = ' ';
            break;
        case 4:
            ptr_matrix[last_pos_y][last_pos_x] = ' ';
            ptr_matrix[last_pos_y][last_pos_x - 1] = ' ';
            ptr_matrix[last_pos_y][last_pos_x + 1] = ' ';
            ptr_matrix[last_pos_y + 1][last_pos_x + 1] = ' ';
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
        break;
    case 3: // I
        switch (rotate % 2) { // потому что поворотов фигуры всего 2
        case 1: // I
            ptr_matrix[block_position_y][block_position_x] = '1';
            ptr_matrix[block_position_y + 1][block_position_x] = '1';
            ptr_matrix[block_position_y + 2][block_position_x] = '1';
            ptr_matrix[block_position_y + 3][block_position_x] = '1';
            break;
        case 0: // -
            ptr_matrix[block_position_y][block_position_x - 1] = '1';
            ptr_matrix[block_position_y][block_position_x] = '1';
            ptr_matrix[block_position_y][block_position_x + 1] = '1';
            ptr_matrix[block_position_y][block_position_x + 2] = '1';
            break;
            

        }
        break;
    case 4: // S
        switch (rotate % 2) { // потому что поворотов фигуры всего 2
        case 1: // S главная точка центр верх
            ptr_matrix[block_position_y][block_position_x] = '1';
            ptr_matrix[block_position_y][block_position_x + 1] = '1';
            ptr_matrix[block_position_y + 1][block_position_x - 1] = '1';
            ptr_matrix[block_position_y + 1][block_position_x] = '1';
            break;
        case 0: // главная точка верхняя
            ptr_matrix[block_position_y][block_position_x] = '1';
            ptr_matrix[block_position_y + 1][block_position_x] = '1';
            ptr_matrix[block_position_y + 1][block_position_x + 1] = '1';
            ptr_matrix[block_position_y + 2][block_position_x + 1] = '1';
            break;
        }
        break;
    case 5: // Z
        switch (rotate % 2) {
        case 1: // Z главная точка центр верх
            ptr_matrix[block_position_y][block_position_x] = '1';
            ptr_matrix[block_position_y][block_position_x - 1] = '1';
            ptr_matrix[block_position_y + 1][block_position_x] = '1';
            ptr_matrix[block_position_y + 1][block_position_x + 1] = '1';
            break;
        case 0: // главная точка верх
            ptr_matrix[block_position_y][block_position_x] = '1';
            ptr_matrix[block_position_y + 1][block_position_x] = '1';
            ptr_matrix[block_position_y + 1][block_position_x - 1] = '1';
            ptr_matrix[block_position_y + 2][block_position_x - 1] = '1';
            break;
        }
        break;
    case 6: // L
        switch (rotate) {
        case 1: // L главная точка верхняя
            ptr_matrix[block_position_y][block_position_x] = '1';
            ptr_matrix[block_position_y + 1][block_position_x] = '1';
            ptr_matrix[block_position_y + 2][block_position_x] = '1';
            ptr_matrix[block_position_y + 2][block_position_x + 1] = '1';
            break;
        case 2: // L angle 90 главная позиция центральная верхняя
            ptr_matrix[block_position_y + 1][block_position_x - 1] = '1';
            ptr_matrix[block_position_y][block_position_x - 1] = '1';
            ptr_matrix[block_position_y][block_position_x] = '1';
            ptr_matrix[block_position_y][block_position_x + 1] = '1';
            break;
        case 3: // L angle 180
            ptr_matrix[block_position_y][block_position_x] = '1';
            ptr_matrix[block_position_y][block_position_x + 1] = '1';
            ptr_matrix[block_position_y + 1][block_position_x + 1] = '1';
            ptr_matrix[block_position_y + 2][block_position_x + 1] = '1';
            break;
        case 4: // главная точка центральная
            ptr_matrix[block_position_y][block_position_x - 1] = '1';
            ptr_matrix[block_position_y][block_position_x] = '1';
            ptr_matrix[block_position_y][block_position_x + 1] = '1';
            ptr_matrix[block_position_y - 1][block_position_x + 1] = '1';
            break;
        }
        break;
    case 7: // J
        switch (rotate) {
        case 1:
            ptr_matrix[block_position_y][block_position_x] = '1';
            ptr_matrix[block_position_y + 1][block_position_x] = '1';
            ptr_matrix[block_position_y + 2][block_position_x] = '1';
            ptr_matrix[block_position_y + 2][block_position_x - 1] = '1';
            break;
        case 2:
            ptr_matrix[block_position_y][block_position_x] = '1';
            ptr_matrix[block_position_y][block_position_x - 1] = '1';
            ptr_matrix[block_position_y - 1][block_position_x - 1] = '1';
            ptr_matrix[block_position_y][block_position_x + 1] = '1';
            break;
        case 3:
            ptr_matrix[block_position_y][block_position_x] = '1';
            ptr_matrix[block_position_y][block_position_x + 1] = '1';
            ptr_matrix[block_position_y + 1][block_position_x] = '1';
            ptr_matrix[block_position_y + 2][block_position_x] = '1';
            break;
        case 4:
            ptr_matrix[block_position_y][block_position_x] = '1';
            ptr_matrix[block_position_y][block_position_x - 1] = '1';
            ptr_matrix[block_position_y][block_position_x + 1] = '1';
            ptr_matrix[block_position_y + 1][block_position_x + 1] = '1';
            break;

        
        }
    }

}
