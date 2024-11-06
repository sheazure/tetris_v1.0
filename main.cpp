/*
Notes:
1.чтобы перевести координаты x и y в порядковый номер светодиода нужно  --->>>> 32 * y + x

*/



#include <iostream>
#include <Windows.h>
#include <cstring>
#include <conio.h>
#include <stdio.h>
#include <random>
#include <algorithm>
#include <string>

const int WIDTH = 32;
const int HEIGHT = 32;

char matrix[32][32];
char copy_matrix[32][32];
int block_position_y = 1;
int block_position_x = 10;
int last_block_position_x = 10;
int last_block_position_y = 1;

int current_block = 99; // менять по мере добавления блоков
int rotate_pos_block = 1;

int future_block = 99;
int score = 0;



int counter_1 = 94;
int counter_2 = 60;
int counter_blocks = 4;
int counter_a = 0; int counter_b = 0; int counter_c = 0; int counter_d = 0; int counter_e = 0; int counter_f = 0; int counter_g = 0;

char last_move = 'N';






// прототипы функций
void cleaning_field_figure(char(&ptr_matrix)[32][32], int last_pos_x, int last_pos_y, int currentBlock, int rotate);
void writing_field_figure(char(&ptr_matrix)[32][32], int currentBlock, int rotate);
void check_block_fallen();
void check_click();
void check_wall();
void print_next_block();
void clean_next_block();
void print_score();





int main() {

    srand(time(NULL));
    current_block = rand() % 7 + 1;

    switch (current_block) {
    case 1: counter_a += 4;
    case 2: counter_b += 4;
    case 3: counter_c += 4;
    case 4: counter_d += 4;
    case 5: counter_e += 4;
    case 6: counter_f += 4;
    case 7: counter_g += 4;
    }
    future_block = rand() % 7 + 1;
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
                matrix[i][j] = '2';
                continue;
            }
            matrix[i][j] = ' ';
        }

        matrix[i][0] = '2';
        matrix[i][31] = '1';

        print_next_block();
        print_score();
    }



    while (1) {
        last_move = 'N';
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

        cleaning_field_figure(matrix, last_block_position_x, last_block_position_y, current_block, rotate_pos_block);
        writing_field_figure(matrix, current_block, rotate_pos_block);

        check_wall();

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

    return 0;
}

void clear_score() {
    matrix[2][23] = ' '; matrix[2][24] = ' '; matrix[2][25] = ' '; matrix[3][23] = ' ';  matrix[3][25] = ' '; matrix[4][23] = ' '; matrix[4][24] = ' '; matrix[4][25] = ' '; matrix[5][23] = ' '; matrix[5][25] = ' '; matrix[6][23] = ' '; matrix[6][24] = ' '; matrix[6][25] = ' ';
    matrix[2][27] = ' '; matrix[2][28] = ' '; matrix[2][29] = ' '; matrix[3][27] = ' ';  matrix[3][29] = ' '; matrix[4][27] = ' '; matrix[4][28] = ' '; matrix[4][29] = ' '; matrix[5][27] = ' '; matrix[5][29] = ' '; matrix[6][27] = ' '; matrix[6][28] = ' '; matrix[6][29] = ' ';
}

void print_score() {
    if (score < 10) {
        matrix[2][23] = '3';
        matrix[2][24] = '3';
        matrix[2][25] = '3';
        matrix[3][23] = '3';
        matrix[3][25] = '3';
        matrix[4][23] = '3';
        matrix[4][25] = '3';
        matrix[5][23] = '3';
        matrix[5][25] = '3';
        matrix[6][23] = '3';
        matrix[6][24] = '3';
        matrix[6][25] = '3';
    }
    else { // вторая цифра всегда одинаковая
        switch (score / 10) {

        case 1:
            matrix[2][25] = '3'; matrix[3][25] = '3'; matrix[4][25] = '3'; matrix[5][25] = '3'; matrix[6][25] = '3';
            break;
        case 2:
            matrix[2][23] = '3'; matrix[2][24] = '3'; matrix[2][25] = '3'; matrix[3][25] = '3'; matrix[4][25] = '3'; matrix[4][24] = '3'; matrix[4][23] = '3'; matrix[5][23] = '3'; matrix[6][23] = '3'; matrix[6][24] = '3'; matrix[6][25] = '3';
            break;
        case 3:
            matrix[2][23] = '3'; matrix[2][24] = '3'; matrix[2][25] = '3'; matrix[3][25] = '3'; matrix[4][25] = '3'; matrix[4][24] = '3'; matrix[4][23] = '3'; matrix[5][25] = '3'; matrix[6][25] = '3'; matrix[6][24] = '3'; matrix[6][23] = '3';
            break;
        case 4:
            matrix[2][23] = '3'; matrix[3][23] = '3'; matrix[4][23] = '3'; matrix[4][24] = '3'; matrix[4][25] = '3'; matrix[2][25] = '3'; matrix[3][25] = '3'; matrix[5][25] = '3'; matrix[6][25] = '3';
            break;
        case 5:
            matrix[2][23] = '3'; matrix[2][24] = '3'; matrix[2][25] = '3'; matrix[3][23] = '3'; matrix[4][23] = '3'; matrix[4][24] = '3'; matrix[4][25] = '3'; matrix[5][25] = '3'; matrix[6][25] = '3'; matrix[6][24] = '3'; matrix[6][23] = '3';
            break;
        case 6:
            matrix[2][23] = '3'; matrix[2][24] = '3'; matrix[2][25] = '3'; matrix[3][23] = '3'; matrix[4][23] = '3'; matrix[4][24] = '3'; matrix[4][25] = '3'; matrix[5][23] = '3'; matrix[5][25] = '3'; matrix[6][23] = '3'; matrix[6][24] = '3'; matrix[6][25] = '3';
            break;
        case 7:
            matrix[2][23] = '3'; matrix[2][24] = '3'; matrix[2][25] = '3'; matrix[3][25] = '3'; matrix[4][25] = '3'; matrix[5][25] = '3'; matrix[6][25] = '3';
            break;
        case 8:
            matrix[2][23] = '3'; matrix[2][24] = '3'; matrix[2][25] = '3'; matrix[3][23] = '3';  matrix[3][25] = '3'; matrix[4][23] = '3'; matrix[4][24] = '3'; matrix[4][25] = '3'; matrix[5][23] = '3'; matrix[5][25] = '3'; matrix[6][23] = '3'; matrix[6][24] = '3'; matrix[6][25] = '3';
            break;
        case 9:
            matrix[2][23] = '3'; matrix[2][24] = '3'; matrix[2][25] = '3'; matrix[3][23] = '3';  matrix[3][25] = '3'; matrix[4][23] = '3'; matrix[4][24] = '3'; matrix[4][25] = '3'; matrix[5][25] = '3'; matrix[6][23] = '3'; matrix[6][24] = '3'; matrix[6][25] = '3';
            break;
        }

    }
    switch (score % 10) {
    case 0:
        matrix[2][27] = '3'; matrix[2][28] = '3'; matrix[2][29] = '3'; matrix[3][27] = '3'; matrix[3][29] = '3'; matrix[4][27] = '3'; matrix[4][29] = '3'; matrix[5][27] = '3'; matrix[5][29] = '3';  matrix[6][27] = '3'; matrix[6][28] = '3'; matrix[6][29] = '3';
        break;
    case 1:
        matrix[2][29] = '3'; matrix[3][29] = '3'; matrix[4][29] = '3'; matrix[5][29] = '3'; matrix[6][29] = '3';
        break;
    case 2:
        matrix[2][27] = '3'; matrix[2][28] = '3'; matrix[2][29] = '3'; matrix[3][29] = '3'; matrix[4][29] = '3'; matrix[4][28] = '3'; matrix[4][27] = '3'; matrix[5][27] = '3'; matrix[6][27] = '3'; matrix[6][28] = '3'; matrix[6][29] = '3';
        break;
    case 3:
        matrix[2][27] = '3'; matrix[2][28] = '3'; matrix[2][29] = '3'; matrix[3][29] = '3'; matrix[4][29] = '3'; matrix[4][28] = '3'; matrix[4][27] = '3'; matrix[5][29] = '3'; matrix[6][29] = '3'; matrix[6][28] = '3'; matrix[6][27] = '3';
        break;
    case 4:
        matrix[2][27] = '3'; matrix[3][27] = '3'; matrix[4][27] = '3'; matrix[4][28] = '3'; matrix[4][29] = '3'; matrix[2][29] = '3'; matrix[3][29] = '3'; matrix[5][29] = '3'; matrix[6][29] = '3';
        break;
    case 5:
        matrix[2][27] = '3'; matrix[2][28] = '3'; matrix[2][29] = '3'; matrix[3][27] = '3'; matrix[4][27] = '3'; matrix[4][28] = '3'; matrix[4][29] = '3'; matrix[5][29] = '3'; matrix[6][29] = '3'; matrix[6][28] = '3'; matrix[6][27] = '3';
        break;
    case 6:
        matrix[2][27] = '3'; matrix[2][28] = '3'; matrix[2][29] = '3'; matrix[3][27] = '3'; matrix[4][27] = '3'; matrix[4][28] = '3'; matrix[4][29] = '3'; matrix[5][27] = '3'; matrix[5][29] = '3'; matrix[6][27] = '3'; matrix[6][28] = '3'; matrix[6][29] = '3';
        break;
    case 7:
        matrix[2][27] = '3'; matrix[2][28] = '3'; matrix[2][29] = '3'; matrix[3][29] = '3'; matrix[4][29] = '3'; matrix[5][29] = '3'; matrix[6][29] = '3';
        break;
    case 8:
        matrix[2][27] = '3'; matrix[2][28] = '3'; matrix[2][29] = '3'; matrix[3][27] = '3';  matrix[3][29] = '3'; matrix[4][27] = '3'; matrix[4][28] = '3'; matrix[4][29] = '3'; matrix[5][27] = '3'; matrix[5][29] = '3'; matrix[6][27] = '3'; matrix[6][28] = '3'; matrix[6][29] = '3';
        break;
    case 9:
        matrix[2][27] = '3'; matrix[2][28] = '3'; matrix[2][29] = '3'; matrix[3][27] = '3';  matrix[3][29] = '3'; matrix[4][27] = '3'; matrix[4][28] = '3'; matrix[4][29] = '3'; matrix[5][29] = '3'; matrix[6][27] = '3'; matrix[6][28] = '3'; matrix[6][29] = '3';
        break;
    }

}


void clean_next_block() {
    switch (future_block) { // 26
    case 1: // cube
        matrix[15][26] = ' ';
        matrix[15][27] = ' ';
        matrix[16][26] = ' ';
        matrix[16][27] = ' ';
        break;
    case 2: // T
        matrix[15][26] = ' ';
        matrix[16][25] = ' ';
        matrix[16][26] = ' ';
        matrix[16][27] = ' ';
        break;
    case 3: // I
        matrix[15][26] = ' ';
        matrix[16][26] = ' ';
        matrix[17][26] = ' ';
        matrix[18][26] = ' ';
        break;
    case 4: // S
        matrix[15][26] = ' ';
        matrix[15][27] = ' ';
        matrix[16][25] = ' ';
        matrix[16][26] = ' ';
        break;
    case 5: // Z
        matrix[15][26] = ' ';
        matrix[15][25] = ' ';
        matrix[16][26] = ' ';
        matrix[16][27] = ' ';
        break;
    case 6: // L
        matrix[15][26] = ' ';
        matrix[16][26] = ' ';
        matrix[17][26] = ' ';
        matrix[17][27] = ' ';
        break;
    case 7: // J
        matrix[15][26] = ' ';
        matrix[16][26] = ' ';
        matrix[17][26] = ' ';
        matrix[17][25] = ' ';
        break;
    }
}

void print_next_block() { // L J
    switch (future_block) { // 26
    case 1: // cube
        matrix[15][26] = '3';
        matrix[15][27] = '3';
        matrix[16][26] = '3';
        matrix[16][27] = '3';
        break;
    case 2: // T
        matrix[15][26] = '3';
        matrix[16][25] = '3';
        matrix[16][26] = '3';
        matrix[16][27] = '3';
        break;
    case 3: // I
        matrix[15][26] = '3';
        matrix[16][26] = '3';
        matrix[17][26] = '3';
        matrix[18][26] = '3';
        break;
    case 4: // S
        matrix[15][26] = '3';
        matrix[15][27] = '3';
        matrix[16][25] = '3';
        matrix[16][26] = '3';
        break;
    case 5: // Z
        matrix[15][26] = '3';
        matrix[15][25] = '3';
        matrix[16][26] = '3';
        matrix[16][27] = '3';
        break;
    case 6: // L
        matrix[15][26] = '3';
        matrix[16][26] = '3';
        matrix[17][26] = '3';
        matrix[17][27] = '3';
        break;
    case 7: // J
        matrix[15][26] = '3';
        matrix[16][26] = '3';
        matrix[17][26] = '3';
        matrix[17][25] = '3';
        break;
    }
}

void check_wall() {
    int counter2 = 0;

    for (int i = 1; i < 31; i++) {
        for (int j = 0; j < 22; j++) {
            if (matrix[i][j] == '2') counter2++;
        }
    }

    if (counter2 < counter_2) {
        cleaning_field_figure(matrix, block_position_x, block_position_y, current_block, rotate_pos_block);
        switch (last_move) {
        case 'R':
            block_position_x--;
            break;
        case 'L':
            block_position_x++;
            break;
        case 'U':
            if (rotate_pos_block == 1) rotate_pos_block = 4;
            else rotate_pos_block--;
        case 'D':
            block_position_y--;
            break;


        }

        writing_field_figure(matrix, current_block, rotate_pos_block);


        for (int i = 1; i < 31; i++) {
            matrix[i][0] = '2';
            matrix[i][21] = '2';
        }
    }

}



void check_click() {
    if (_kbhit()) {
        switch (_getch()) {
        case 72: // up (поворот блока)
            cleaning_field_figure(matrix, last_block_position_x, last_block_position_y, current_block, rotate_pos_block);
            if (rotate_pos_block == 4) rotate_pos_block = 1;
            else rotate_pos_block++;
            last_move = 'U';

            break;

        case 80: // down        

            last_move = 'D';
            block_position_y++;

            break;
        case 75: // left
            last_move = 'L';
            block_position_x--;

            break;
        case 77: // right
            last_move = 'R';
            block_position_x++;


            break;

        default:
            last_move = 'N';
            break;

        }


    }

}



// проверка упал ли блок
void check_block_fallen() {
    int counter1 = 0;
    int counterblocks = 0;

    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            if (matrix[i][j] == '1') {
                counter1++;
            }
            if (matrix[i][j] == 'a' || matrix[i][j] == 'b' || matrix[i][j] == 'c' || matrix[i][j] == 'd' || matrix[i][j] == 'e' || matrix[i][j] == 'f' || matrix[i][j] == 'g') counterblocks++;
        }
    }

    bool event = false;


    if (counter1 < counter_1 || counterblocks < counter_blocks) {
        for (int i = 0; i < HEIGHT; i++) {
            for (int j = 0; j < WIDTH; j++) {
                matrix[i][j] = copy_matrix[i][j];
            }
        }
        counter_blocks += 4;
        block_position_x = 10;
        block_position_y = 1;
        last_block_position_x = 10;
        last_block_position_y = 1;
        rotate_pos_block = 1;
        event = true;
        clean_next_block();

        current_block = future_block;
        future_block = rand() % 7 + 1;
        print_next_block();
        switch (current_block) {
        case 1: counter_a += 4; break;
        case 2: counter_b += 4; break;
        case 3: counter_c += 4; break;
        case 4: counter_d += 4; break;
        case 5: counter_e += 4; break;
        case 6: counter_f += 4; break;
        case 7: counter_g += 4; break;
        }
    }

    if (event) {
        int counter = 0;
        for (int i = 1; i < 31; i++) { // игровое поле
            counter = 0;
            for (int j = 1; j < 21; j++) { // игровое поле
                if (matrix[i][j] == 'a' || matrix[i][j] == 'b' || matrix[i][j] == 'c' || matrix[i][j] == 'd' || matrix[i][j] == 'e' || matrix[i][j] == 'f' || matrix[i][j] == 'g') counter++;
            }
            if (counter == 20) {
                for (int h = 1; h < 21; h++) {
                    switch (matrix[i][h]) {
                    case 'a': counter_a--; break;
                    case 'b': counter_b--; break;
                    case 'c': counter_c--; break;
                    case 'd': counter_d--; break;
                    case 'e': counter_e--; break;
                    case 'f': counter_f--; break;
                    case 'g': counter_g--; break;
                    }
                    matrix[i][h] = ' ';
                }
                counter_blocks -= 20;
                clear_score();
                score++;
                print_score();
                for (int r = i - 1; r > 0; r--) {
                    for (int j = 1; j < 21; j++) {
                        matrix[r + 1][j] = matrix[r][j];
                    }
                }

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
        ptr_matrix[block_position_y][block_position_x] = 'a';
        ptr_matrix[block_position_y][block_position_x + 1] = 'a';
        ptr_matrix[block_position_y + 1][block_position_x] = 'a';
        ptr_matrix[block_position_y + 1][block_position_x + 1] = 'a';
        break;
    case 2:
        switch (rotate) {
        case 1: // T inverted
            ptr_matrix[block_position_y][block_position_x] = 'b';
            ptr_matrix[block_position_y + 1][block_position_x - 1] = 'b';
            ptr_matrix[block_position_y + 1][block_position_x] = 'b';
            ptr_matrix[block_position_y + 1][block_position_x + 1] = 'b';
            break;
        case 2: // |-    <- figure
            ptr_matrix[block_position_y][block_position_x] = 'b';
            ptr_matrix[block_position_y + 1][block_position_x] = 'b';
            ptr_matrix[block_position_y + 1][block_position_x + 1] = 'b';
            ptr_matrix[block_position_y + 2][block_position_x] = 'b';
            break;
        case 3: // T исключение главная точка верхняя центраальная
            ptr_matrix[block_position_y][block_position_x - 1] = 'b';
            ptr_matrix[block_position_y][block_position_x] = 'b';
            ptr_matrix[block_position_y + 1][block_position_x] = 'b';
            ptr_matrix[block_position_y][block_position_x + 1] = 'b';
            break;
        case 4: // -|
            ptr_matrix[block_position_y][block_position_x] = 'b';
            ptr_matrix[block_position_y + 1][block_position_x] = 'b';
            ptr_matrix[block_position_y + 1][block_position_x - 1] = 'b';
            ptr_matrix[block_position_y + 2][block_position_x] = 'b';
            break;
        }
        break;
    case 3: // I
        switch (rotate % 2) { // потому что поворотов фигуры всего 2
        case 1: // I
            ptr_matrix[block_position_y][block_position_x] = 'c';
            ptr_matrix[block_position_y + 1][block_position_x] = 'c';
            ptr_matrix[block_position_y + 2][block_position_x] = 'c';
            ptr_matrix[block_position_y + 3][block_position_x] = 'c';
            break;
        case 0: // -
            ptr_matrix[block_position_y][block_position_x - 1] = 'c';
            ptr_matrix[block_position_y][block_position_x] = 'c';
            ptr_matrix[block_position_y][block_position_x + 1] = 'c';
            ptr_matrix[block_position_y][block_position_x + 2] = 'c';
            break;


        }
        break;
    case 4: // S
        switch (rotate % 2) { // потому что поворотов фигуры всего 2
        case 1: // S главная точка центр верх
            ptr_matrix[block_position_y][block_position_x] = 'd';
            ptr_matrix[block_position_y][block_position_x + 1] = 'd';
            ptr_matrix[block_position_y + 1][block_position_x - 1] = 'd';
            ptr_matrix[block_position_y + 1][block_position_x] = 'd';
            break;
        case 0: // главная точка верхняя
            ptr_matrix[block_position_y][block_position_x] = 'd';
            ptr_matrix[block_position_y + 1][block_position_x] = 'd';
            ptr_matrix[block_position_y + 1][block_position_x + 1] = 'd';
            ptr_matrix[block_position_y + 2][block_position_x + 1] = 'd';
            break;
        }
        break;
    case 5: // Z
        switch (rotate % 2) {
        case 1: // Z главная точка центр верх
            ptr_matrix[block_position_y][block_position_x] = 'e';
            ptr_matrix[block_position_y][block_position_x - 1] = 'e';
            ptr_matrix[block_position_y + 1][block_position_x] = 'e';
            ptr_matrix[block_position_y + 1][block_position_x + 1] = 'e';
            break;
        case 0: // главная точка верх
            ptr_matrix[block_position_y][block_position_x] = 'e';
            ptr_matrix[block_position_y + 1][block_position_x] = 'e';
            ptr_matrix[block_position_y + 1][block_position_x - 1] = 'e';
            ptr_matrix[block_position_y + 2][block_position_x - 1] = 'e';
            break;
        }
        break;
    case 6: // L
        switch (rotate) {
        case 1: // L главная точка верхняя
            ptr_matrix[block_position_y][block_position_x] = 'f';
            ptr_matrix[block_position_y + 1][block_position_x] = 'f';
            ptr_matrix[block_position_y + 2][block_position_x] = 'f';
            ptr_matrix[block_position_y + 2][block_position_x + 1] = 'f';
            break;
        case 2: // L angle 90 главная позиция центральная верхняя
            ptr_matrix[block_position_y + 1][block_position_x - 1] = 'f';
            ptr_matrix[block_position_y][block_position_x - 1] = 'f';
            ptr_matrix[block_position_y][block_position_x] = 'f';
            ptr_matrix[block_position_y][block_position_x + 1] = 'f';
            break;
        case 3: // L angle 180
            ptr_matrix[block_position_y][block_position_x] = 'f';
            ptr_matrix[block_position_y][block_position_x + 1] = 'f';
            ptr_matrix[block_position_y + 1][block_position_x + 1] = 'f';
            ptr_matrix[block_position_y + 2][block_position_x + 1] = 'f';
            break;
        case 4: // главная точка центральная
            ptr_matrix[block_position_y][block_position_x - 1] = 'f';
            ptr_matrix[block_position_y][block_position_x] = 'f';
            ptr_matrix[block_position_y][block_position_x + 1] = 'f';
            ptr_matrix[block_position_y - 1][block_position_x + 1] = 'f';
            break;
        }
        break;
    case 7: // J
        switch (rotate) {
        case 1:
            ptr_matrix[block_position_y][block_position_x] = 'g';
            ptr_matrix[block_position_y + 1][block_position_x] = 'g';
            ptr_matrix[block_position_y + 2][block_position_x] = 'g';
            ptr_matrix[block_position_y + 2][block_position_x - 1] = 'g';
            break;
        case 2:
            ptr_matrix[block_position_y][block_position_x] = 'g';
            ptr_matrix[block_position_y][block_position_x - 1] = 'g';
            ptr_matrix[block_position_y - 1][block_position_x - 1] = 'g';
            ptr_matrix[block_position_y][block_position_x + 1] = 'g';
            break;
        case 3:
            ptr_matrix[block_position_y][block_position_x] = 'g';
            ptr_matrix[block_position_y][block_position_x + 1] = 'g';
            ptr_matrix[block_position_y + 1][block_position_x] = 'g';
            ptr_matrix[block_position_y + 2][block_position_x] = 'g';
            break;
        case 4:
            ptr_matrix[block_position_y][block_position_x] = 'g';
            ptr_matrix[block_position_y][block_position_x - 1] = 'g';
            ptr_matrix[block_position_y][block_position_x + 1] = 'g';
            ptr_matrix[block_position_y + 1][block_position_x + 1] = 'g';
            break;


        }
    }

}
