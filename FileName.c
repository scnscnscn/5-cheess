#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include<errno.h>
int board[15][15] = { 0 };

void board_start(int board[15][15]);//���̳�ʼ��
void printfboard(int board[15][15]);//��ӡԭʼ����
void draw_board(int board[15][15]);//��ӡ����

void computer_chess(int board[15][15]);//��������
void human_chess(int board[15][15]);//�������
int win(int chessboard[15][15], int x, int y);//�ж�ʤ��

void printfboard(int board[15][15]) {//��ӡԭʼ����
    for (int i = 0; i < 15; i++) {
        for (int j = 0; j < 15; j++) {
            printf("%d   ", board[i][j]);
        }
        printf("\n");
    }
}


void draw_board(int board[15][15]) {//��ӡ����
    for (int i = 0; i < 15; i++) {
        if (i == 0) {
            for (int j = 0; j < 15; j++) {
                if (j == 0 && board[i][j] == 0) {
                    printf("�� ");
                }
                else if (j < 14 && board[i][j] == 0) {
                    printf("�� ");
                }
                else if (j == 14 && board[i][j] == 0) {
                    printf("��");
                }
                if (board[i][j] == 1)
                    printf("�� ");
                if (board[i][j] == -1)
                    printf("�� ");
            }
            printf("\n");
        }

        if (i == 14) {
            for (int j = 0; j < 15; j++) {
                if (j == 5 && board[i][j] == 0) {
                    printf("�� ");
                }
                else if (j < 14 && board[i][j] == 0) {
                    printf("�� ");
                }
                else if (j == 14 && board[i][j] == 0) {
                    printf("�� ");
                }
                if (board[i][j] == 1)
                    printf("�� ");
                if (board[i][j] == -1)
                    printf("�� ");
            }
            printf("\n");
        }
        if (i > 0 && i < 14) {
            for (int j = 0; j < 15; j++) {

                if (j == 0 && board[i][j] == 0) {
                    printf("�� ");
                }
                else if (j == 14 && board[i][j] == 0)
                    printf("��");
                else if (j > 0 && j < 14 && board[i][j] == 0)       printf("�� ");
                if (board[i][j] == 1)
                    printf("�� ");
                if (board[i][j] == -1)
                    printf("�� ");
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

    {50, {0, 1, 1, 0, 0, -1, -1}},    // ���
    {50, {0, 0, 1, 1, 0, -1, -1}},    // ���
    {150, {1, 1, 0, 1, 0, -1, -1}},   // ����
    {500, {1, 1, 1, 0, 0, -1, -1}},   // ����
    {500, {0, 0, 1, 1, 1, -1, -1}},   // ����
    {1000, {1, 0, 1, 1, 0, -1, -1}},  // ������
    {1000, {0, 1, 1, 0, 1, -1, -1}},  // ������
    {5000, {1, 1, 1, 0, 1, -1, -1}},  // ˫����
    {5000, {1, 1, 0, 1, 1, -1, -1}},  // ˫����
    {5000, {1, 0, 1, 1, 1, -1, -1}},  // ˫����
    {5000, {1, 1, 1, 1, 0, -1, -1}},  // ����
    {5000, {0, 1, 1, 1, 1, -1, -1}},  // ����
    {50000, {0, 1, 1, 1, 0, -1, -1}}, // ˫����
    {10000, {1, 1, 1, 1, 0, 0, -1}},  // ����
    {15000, {1, 1, 1, 0, 1, 0, -1}},  // ����
    {15000, {1, 1, 1, 0, 1, 1, -1}},  // ˫����
    {15000, {1, 1, 1, 1, 1, -1, -1}}, // ����
    {15000, {1, 1, 0, 1, 1, 0, -1}},  // ˫����

    {100, {0, -1, -1, 0, 0, 1, 1}},    // ���ֵĻ��
    {100, {0, 0, -1, -1, 0, 1, 1}},    // ���ֵĻ��
    {300, {-1, -1, 0, -1, 0, 1, 1}},  // ���ֵĳ���
    {1000, {-1, -1, -1, 0, 0, 1, 1}},  // ���ֵĳ���
    {1000, {0, 0, -1, -1, -1, 1, 1}},  // ���ֵĳ���
    {2000, {-1, 0, -1, -1, 0, 1, 1}}, // ���ֵ�������
    {2000, {0, -1, -1, 0, -1, 1, 1}}, // ���ֵ�������
    {10000, {-1, -1, -1, 0, -1, 1, 1}}, // ���ֵ�˫����
    {10000, {-1, -1, 0, -1, -1, 1, 1}}, // ���ֵ�˫����
    {10000, {-1, 0, -1, -1, -1, 1, 1}}, // ���ֵ�˫����
    {10000, {-1, -1, -1, -1, 0, 1, 1}}, // ���ֵĻ���
    {10000, {0, -1, -1, -1, -1, 1, 1}}, // ���ֵĻ���
    {100000, {0, -1, -1, -1, 0, 1, 1}}, // ���ֵ�˫����
    {20000, {-1, -1, -1, -1, 0, 0, 1}}, // ���ֵĻ���
    {30000, {-1, -1, -1, 0, -1, 0, 1}}, // ���ֵĳ���
    {30000, {-1, -1, -1, 0, -1, -1, 1}} // ���ֵ�˫����





};


// ����ض�λ�õķ���
int check_score(int board[15][15], int x, int y) {
    int score = 0;
    int example[7];

    // ͨ��direction++��switch����ĸ�����ˮƽ����ֱ�������Խ���
    for (int direction = 0; direction < 4; direction++) {
        //һ��һ������ɨ��
        for (int offset = -4; offset <= 0; offset++) {
            int alarm = 1;
            //��ɨ������ע��example
            for (int i = 0; i < 7 && alarm; i++) {
                int dx = 0, dy = 0;

                switch (direction) {
                case 0: dx = i + offset; break;  // ˮƽ
                case 1: dy = i + offset; break;  // ��ֱ
                case 2: dx = dy = i + offset; break;  // �Խ���
                case 3: dx = i + offset; dy = -i - offset; break;  // ���Խ���
                }

                if (x + dx < 0 || x + dx >= 15 || y + dy < 0 || y + dy >= 15) {
                    alarm = 0;  // �������̱߽�
                    break;
                }
                else {
                    example[i] = board[x + dx][y + dy];
                }
            }
            //��û��Խ�������¶��������м��
            if (alarm) {
                //����Ƿ����18������
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

// ��������Ƿ�ƥ��
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

// Ϊ����ѡ���������λ��
PositionScore select_best(int board[15][15]) {
    PositionScore best;
    best.score = -1; // ��ʼ����ѷ���Ϊ����ֵ

    for (int x = 0; x < 15; x++) {
        for (int y = 0; y < 15; y++) {
            if (board[x][y] == 0) { // ȷ���ǿ�λ
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
    board[best.x][best.y] = 1; // ����1������Ե�����
}


//������
void human_chess(int board[15][15]) {
    int i, j;
    printf("������\n");
    printf("������Ϊ��\n");
    scanf_s("%d", &i);
    printf("������Ϊ��\n");
    scanf_s("%d", &j);
    while (board[i + 4][j + 4] == 1 || board[i + 4][j + 4] == -1) {
        printf("��λ���������ӣ����������壡");
        printf("������\n");
        printf("������Ϊ��\n");
        scanf_s("%d", &i);
        printf("������Ϊ��\n");
        scanf_s("%d", &j);
    }
    while (i < 1 || i>15 | j < 1 || j>15) {
        printf("�����߽磬���������壡");
        printf("������\n");
        printf("������Ϊ��\n");
        scanf_s("%d", &i);
        printf("������Ϊ��\n");
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
            //���ж�
            if (j < y - 4)//�ж�����Ƿ�ʤ��
                if (chessboard[i][j] == chessboard[i][j + 1] && chessboard[i][j] == chessboard[i][j + 2] && chessboard[i][j] == chessboard[i][j + 3] && chessboard[i][j] == chessboard[i][j + 4] == 1)
                    flag = 1;
            //���ж�
            if (i < x - 4)
                if (chessboard[i][j] == chessboard[i + 1][j] && chessboard[i][j] == chessboard[i + 2][j] && chessboard[i][j] == chessboard[i + 3][j] && chessboard[i][j] == chessboard[i + 4][j] == 1)
                    flag = 1;
            //���Խ����ж�
            if (i < x - 4 && j < y - 4)
                if (chessboard[i][j] == chessboard[i + 1][j + 1] && chessboard[i][j] == chessboard[i + 2][j + 2] && chessboard[i][j] == chessboard[i + 3][j + 3] && chessboard[i][j] == chessboard[i + 4][j + 4] == 1)
                    flag = 1;
            //���Խ����ж�
            if (i < x - 4 && j > 4)
                if (chessboard[i][j] == chessboard[i + 1][j - 1] && chessboard[i][j] == chessboard[i + 2][j - 2] && chessboard[i][j] == chessboard[i + 3][j - 3] && chessboard[i][j] == chessboard[i + 4][j - 4] == 1)
                    flag = 1;
            //���ж�
            if (j < y - 4)//�жϵ����Ƿ�ʤ��
                if (chessboard[i][j] == chessboard[i][j + 1] && chessboard[i][j] == chessboard[i][j + 2] && chessboard[i][j] == chessboard[i][j + 3] && chessboard[i][j] == chessboard[i][j + 4] < 0)
                    flag = -1;
            //���ж�
            if (i < x - 4)
                if (chessboard[i][j] == chessboard[i + 1][j] && chessboard[i][j] == chessboard[i + 2][j] && chessboard[i][j] == chessboard[i + 3][j] && chessboard[i][j] == chessboard[i + 4][j] < 0)
                    flag = -1;
            //���Խ����ж�
            if (i < x - 4 && j < y - 4)
                if (chessboard[i][j] == chessboard[i + 1][j + 1] && chessboard[i][j] == chessboard[i + 2][j + 2] && chessboard[i][j] == chessboard[i + 3][j + 3] && chessboard[i][j] == chessboard[i + 4][j + 4] < 0)
                    flag = -1;
            //���Խ����ж�
            if (i < x - 4 && j > 4)
                if (chessboard[i][j] == chessboard[i + 1][j - 1] && chessboard[i][j] == chessboard[i + 2][j - 2] && chessboard[i][j] == chessboard[i + 3][j - 3] && chessboard[i][j] == chessboard[i + 4][j - 4] < 0)
                    flag = -1;
        }
    }
    return flag;
}
int main(void) {
    printf("----��ʼ����----\n");
    draw_board(board);
    int temp[15][15] = { 0 };
    int option = 0;
    while (1) {
        //��ʱд����һ�ֵ��������
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
            printf("��Ӯ�ˣ�\n");
            break;
        }
        else if (flag == -1) {
            printf("�����ˣ�\n");
            break;
        }

        printf("�����Ƿ�Ҫ����(1/2)");
        scanf_s("%d", &option);
        //���Ҫ�������ȡtemp;
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
