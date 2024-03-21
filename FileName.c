#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include<errno.h>
int board[15][15] = { 0 };

void board_start(int board[15][15]);//棋盘初始化
void printfboard(int board[15][15]);//打印原始棋盘
void draw_board(int board[15][15]);//打印棋盘

void computer_chess(int board[15][15]);//电脑落棋
void human_chess(int board[15][15]);//玩家落棋
int win(int chessboard[15][15], int x, int y);//判断胜负

void printfboard(int board[15][15]) {//打印原始棋盘
    for (int i = 0; i < 15; i++) {
        for (int j = 0; j < 15; j++) {
            printf("%d   ", board[i][j]);
        }
        printf("\n");
    }
}


void draw_board(int board[15][15]) {//打印棋盘
    for (int i = 0; i < 15; i++) {
        if (i == 0) {
            for (int j = 0; j < 15; j++) {
                if (j == 0 && board[i][j] == 0) {
                    printf("┌ ");
                }
                else if (j < 14 && board[i][j] == 0) {
                    printf("┬ ");
                }
                else if (j == 14 && board[i][j] == 0) {
                    printf("┐");
                }
                if (board[i][j] == 1)
                    printf("● ");
                if (board[i][j] == -1)
                    printf("○ ");
            }
            printf("\n");
        }

        if (i == 14) {
            for (int j = 0; j < 15; j++) {
                if (j == 5 && board[i][j] == 0) {
                    printf("└ ");
                }
                else if (j < 14 && board[i][j] == 0) {
                    printf("┴ ");
                }
                else if (j == 14 && board[i][j] == 0) {
                    printf("┘ ");
                }
                if (board[i][j] == 1)
                    printf("● ");
                if (board[i][j] == -1)
                    printf("○ ");
            }
            printf("\n");
        }
        if (i > 0 && i < 14) {
            for (int j = 0; j < 15; j++) {

                if (j == 0 && board[i][j] == 0) {
                    printf("├ ");
                }
                else if (j == 14 && board[i][j] == 0)
                    printf("┤");
                else if (j > 0 && j < 14 && board[i][j] == 0)       printf("┼ ");
                if (board[i][j] == 1)
                    printf("● ");
                if (board[i][j] == -1)
                    printf("○ ");
            }
            printf("\n");
        }

    }
}
typedef struct {
    int score;
    int pattern[7];
} ShapeScore;

ShapeScore shape_score[] = {

    {50, {0, 1, 1, 0, 0, -1, -1}},    // 活二
    {50, {0, 0, 1, 1, 0, -1, -1}},    // 活二
    {150, {1, 1, 0, 1, 0, -1, -1}},   // 冲三
    {500, {1, 1, 1, 0, 0, -1, -1}},   // 冲四
    {500, {0, 0, 1, 1, 1, -1, -1}},   // 冲四
    {1000, {1, 0, 1, 1, 0, -1, -1}},  // 跳活三
    {1000, {0, 1, 1, 0, 1, -1, -1}},  // 跳活三
    {5000, {1, 1, 1, 0, 1, -1, -1}},  // 双冲四
    {5000, {1, 1, 0, 1, 1, -1, -1}},  // 双冲四
    {5000, {1, 0, 1, 1, 1, -1, -1}},  // 双冲四
    {5000, {1, 1, 1, 1, 0, -1, -1}},  // 活四
    {5000, {0, 1, 1, 1, 1, -1, -1}},  // 活四
    {50000, {0, 1, 1, 1, 0, -1, -1}}, // 双活三
    {10000, {1, 1, 1, 1, 0, 0, -1}},  // 活四
    {15000, {1, 1, 1, 0, 1, 0, -1}},  // 冲四
    {15000, {1, 1, 1, 0, 1, 1, -1}},  // 双冲四
    {15000, {1, 1, 1, 1, 1, -1, -1}}, // 五连
    {15000, {1, 1, 0, 1, 1, 0, -1}},  // 双活三

    {100, {0, -1, -1, 0, 0, 1, 1}},    // 对手的活二
    {100, {0, 0, -1, -1, 0, 1, 1}},    // 对手的活二
    {300, {-1, -1, 0, -1, 0, 1, 1}},  // 对手的冲三
    {1000, {-1, -1, -1, 0, 0, 1, 1}},  // 对手的冲四
    {1000, {0, 0, -1, -1, -1, 1, 1}},  // 对手的冲四
    {2000, {-1, 0, -1, -1, 0, 1, 1}}, // 对手的跳活三
    {2000, {0, -1, -1, 0, -1, 1, 1}}, // 对手的跳活三
    {10000, {-1, -1, -1, 0, -1, 1, 1}}, // 对手的双冲四
    {10000, {-1, -1, 0, -1, -1, 1, 1}}, // 对手的双冲四
    {10000, {-1, 0, -1, -1, -1, 1, 1}}, // 对手的双冲四
    {10000, {-1, -1, -1, -1, 0, 1, 1}}, // 对手的活四
    {10000, {0, -1, -1, -1, -1, 1, 1}}, // 对手的活四
    {100000, {0, -1, -1, -1, 0, 1, 1}}, // 对手的双活三
    {20000, {-1, -1, -1, -1, 0, 0, 1}}, // 对手的活四
    {30000, {-1, -1, -1, 0, -1, 0, 1}}, // 对手的冲四
    {30000, {-1, -1, -1, 0, -1, -1, 1}} // 对手的双冲四





};


// 检查特定位置的分数
int check_score(int board[15][15], int x, int y) {
    int score = 0;
    int example[7];

    // 通过direction++和switch检查四个方向：水平、垂直、两个对角线
    for (int direction = 0; direction < 4; direction++) {
        //一格一格往外扫描
        for (int offset = -4; offset <= 0; offset++) {
            int alarm = 1;
            //将扫描样本注入example
            for (int i = 0; i < 7 && alarm; i++) {
                int dx = 0, dy = 0;

                switch (direction) {
                case 0: dx = i + offset; break;  // 水平
                case 1: dy = i + offset; break;  // 垂直
                case 2: dx = dy = i + offset; break;  // 对角线
                case 3: dx = i + offset; dy = -i - offset; break;  // 反对角线
                }

                if (x + dx < 0 || x + dx >= 15 || y + dy < 0 || y + dy >= 15) {
                    alarm = 0;  // 超出棋盘边界
                    break;
                }
                else {
                    example[i] = board[x + dx][y + dy];
                }
            }
            //在没有越界的情况下对样本进行检测
            if (alarm) {
                //检测是否符合18种棋形
                for (int i = 0; i < 18; i++) {
                    if (match(shape_score[i].pattern, example)) {
                        score += shape_score[i].score;
                        break;
                    }
                }
            }
        }
    }

    return score;
}

// 检查棋型是否匹配
int match(int pattern[], int example[]) {
    for (int i = 0; pattern[i] != -1; ++i) {
        if (pattern[i] != example[i]) {
            return 0;
        }
    }
    return 1;
}

typedef struct {
    int x;
    int y;
    int score;
} PositionScore;

// 为电脑选择最佳落子位置
PositionScore select_best(int board[15][15]) {
    PositionScore best;
    best.score = -1; // 初始化最佳分数为极低值

    for (int x = 0; x < 15; x++) {
        for (int y = 0; y < 15; y++) {
            if (board[x][y] == 0) { // 确保是空位
                int score = check_score(board, x, y);
                if (score > best.score) {
                    best.score = score;
                    best.x = x;
                    best.y = y;
                }
            }
        }
    }

    return best;
}



void computer_chess(int board[15][15]) {
    PositionScore best = select_best(board);
    board[best.x][best.y] = 1; // 假设1代表电脑的棋子
}


//人下棋
void human_chess(int board[15][15]) {
    int i, j;
    printf("请落棋\n");
    printf("横坐标为：\n");
    scanf_s("%d", &i);
    printf("纵坐标为：\n");
    scanf_s("%d", &j);
    while (board[i + 4][j + 4] == 1 || board[i + 4][j + 4] == -1) {
        printf("该位置已有棋子，请重新落棋！");
        printf("请落棋\n");
        printf("横坐标为：\n");
        scanf_s("%d", &i);
        printf("纵坐标为：\n");
        scanf_s("%d", &j);
    }
    while (i < 1 || i>15 | j < 1 || j>15) {
        printf("超出边界，请重新落棋！");
        printf("请落棋\n");
        printf("横坐标为：\n");
        scanf_s("%d", &i);
        printf("纵坐标为：\n");
        scanf_s("%d", &j);
    }
    board[i - 1][j - 1] = -1;
}

int win(int chessboard[15][15], int x, int y) {
    int i, j;
    int flag = 0;
    for (i = 0; i < x; i++) {
        for (j = 0; j < y; j++) {
            if (chessboard[i][j] == 0)
                continue;
            //列判断
            if (j < y - 4)//判断玩家是否胜利
                if (chessboard[i][j] == chessboard[i][j + 1] && chessboard[i][j] == chessboard[i][j + 2] && chessboard[i][j] == chessboard[i][j + 3] && chessboard[i][j] == chessboard[i][j + 4] == 1)
                    flag = 1;
            //行判断
            if (i < x - 4)
                if (chessboard[i][j] == chessboard[i + 1][j] && chessboard[i][j] == chessboard[i + 2][j] && chessboard[i][j] == chessboard[i + 3][j] && chessboard[i][j] == chessboard[i + 4][j] == 1)
                    flag = 1;
            //主对角线判断
            if (i < x - 4 && j < y - 4)
                if (chessboard[i][j] == chessboard[i + 1][j + 1] && chessboard[i][j] == chessboard[i + 2][j + 2] && chessboard[i][j] == chessboard[i + 3][j + 3] && chessboard[i][j] == chessboard[i + 4][j + 4] == 1)
                    flag = 1;
            //副对角线判断
            if (i < x - 4 && j > 4)
                if (chessboard[i][j] == chessboard[i + 1][j - 1] && chessboard[i][j] == chessboard[i + 2][j - 2] && chessboard[i][j] == chessboard[i + 3][j - 3] && chessboard[i][j] == chessboard[i + 4][j - 4] == 1)
                    flag = 1;
            //列判断
            if (j < y - 4)//判断电脑是否胜利
                if (chessboard[i][j] == chessboard[i][j + 1] && chessboard[i][j] == chessboard[i][j + 2] && chessboard[i][j] == chessboard[i][j + 3] && chessboard[i][j] == chessboard[i][j + 4] < 0)
                    flag = -1;
            //行判断
            if (i < x - 4)
                if (chessboard[i][j] == chessboard[i + 1][j] && chessboard[i][j] == chessboard[i + 2][j] && chessboard[i][j] == chessboard[i + 3][j] && chessboard[i][j] == chessboard[i + 4][j] < 0)
                    flag = -1;
            //主对角线判断
            if (i < x - 4 && j < y - 4)
                if (chessboard[i][j] == chessboard[i + 1][j + 1] && chessboard[i][j] == chessboard[i + 2][j + 2] && chessboard[i][j] == chessboard[i + 3][j + 3] && chessboard[i][j] == chessboard[i + 4][j + 4] < 0)
                    flag = -1;
            //副对角线判断
            if (i < x - 4 && j > 4)
                if (chessboard[i][j] == chessboard[i + 1][j - 1] && chessboard[i][j] == chessboard[i + 2][j - 2] && chessboard[i][j] == chessboard[i + 3][j - 3] && chessboard[i][j] == chessboard[i + 4][j - 4] < 0)
                    flag = -1;
        }
    }
    return flag;
}
int main(void) {
    printf("----开始下棋----\n");
    draw_board(board);
    int temp[15][15] = { 0 };
    int option = 0;
    while (1) {
        //此时写入上一局的棋盘情况
        for (int i = 0; i < 15; i++) {
            for (int j = 0; j < 15; j++) {
                temp[i][j] = board[i][j];
            }

        }
        draw_board(board);
        human_chess(board);

        computer_chess(board);
        draw_board(board);


        int flag = win(board, 15, 15);
        if (flag == 1) {
            printf("你赢了！\n");
            break;
        }
        else if (flag == -1) {
            printf("你输了！\n");
            break;
        }

        printf("请问是否要悔棋(1/2)");
        scanf_s("%d", &option);
        //如果要悔棋则读取temp;
        switch (option)
        {
        case 2:
            continue;
            break;
        case 1:
            for (int i = 0; i < 15; i++) {
                for (int j = 0; j < 15; j++) {
                    board[i][j] = temp[i][j];
                }

            }
            draw_board(board);

        default:
            break;
        }
    }
}
