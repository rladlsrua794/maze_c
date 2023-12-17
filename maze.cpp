#include <stdio.h>
#include <windows.h>
#include <conio.h>

#define WIDTH 10
#define HEIGHT 10
#define LEFT 75
#define RIGHT 77
#define UP 72
#define DOWN 80

void View_map(int x, int y);
void make_map(int map[WIDTH][HEIGHT], int x, int y);
int collision(int map[WIDTH][HEIGHT], int row, int col);
void player_move(int map[WIDTH][HEIGHT], int* row, int* col);

    int map[WIDTH][HEIGHT] = {
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {0, 0, 0, 0, 0, 0, 0, 1, 0, 1},
        {1, 0, 1, 1, 1, 1, 0, 1, 0, 1},
        {1, 0, 1, 0, 0, 1, 0, 0, 0, 1},
        {1, 0, 1, 0, 0, 1, 1, 1, 0, 1},
        {1, 1, 1, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 1, 1, 0, 1, 0, 1},
        {1, 0, 1, 0, 1, 1, 1, 1, 1, 1},
        {1, 0, 1, 0, 0, 0, 0, 0, 0, 3},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    };

    int main(void) {
        int player_x = 1;
        int player_y = 0;

        printf("클리어할 미로\n");
        View_map(0, 0);

        while (1) {
            make_map(map, WIDTH, HEIGHT);
            player_move(map, &player_x, &player_y);
        }
        return 0;
    }

    void View_map(int x, int y) {
        COORD Player;
        Player.X = x;
        Player.Y = y;

        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Player);
    }

    void make_map(int map[][HEIGHT], int x, int y) {
        for (int i = 0; i < x; i++) {
            for (int j = 0; j < y; j++) {
                if (map[i][j] == 0)
                    printf("  ");
                else if (map[i][j] == 1)
                    printf("ㅁ");
                else if (map[i][j] == 3)
                    printf("ㅣ");
                else
                    printf("ㅇ");
            }
            printf("\n");
        }
    }

    int collision(int map[WIDTH][HEIGHT], int i, int j) {
        if (map[i][j] == 1) // 미로가 벽일 경우
            return 1;
        else if (map[i][j] == 3) {
            printf("미로 클리어!");
            return 1;
        }
        else
            return 0;
    }

    void player_move(int map[WIDTH][HEIGHT], int* row, int* col) {
        int i = *row;
        int j = *col;
        int get = _getch();

        if (get == 0 || get == 0xe0) {
            get = _getch();
            switch (get) {
            case UP:
                i--;
                break;
            case DOWN:
                i++;
                break;
            case LEFT:
                j--;
                break;
            case RIGHT:
                j++;
                break;
            }
        }

        if (!collision(map, i, j)) {

            map[*row][*col] = 0;
            map[i][j] = 2; // 플레이어 위치
            *row = i;
            *col = j;
        }

        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 0, HEIGHT + 2 });
        printf("현재 위치: (%d, %d)    \n", *col, *row);
        Sleep(100);
    }
