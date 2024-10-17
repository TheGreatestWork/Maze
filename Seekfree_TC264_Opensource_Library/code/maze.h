/*
 * maze.h
 *
 */

#ifndef CODE_MAZE_H_
#define CODE_MAZE_H_

typedef enum
{
    gru = 1,        //��
    grl = 2,        //��
    grd = 3,        //��
    grr = 4         //�ң���ʱ�뷽��
}MAZE_DIR;

struct LEFT_EDGE
{
    int row;  //������
    int col;  //������
    int dir;  //��������
};

struct RIGHT_EDGE
{
    int row;  //������
    int col;  //������
    int dir;  //��������
};

void image_get(void);
void maze(void);
void tft_display(void);

#endif /* CODE_MAZE_H_ */
