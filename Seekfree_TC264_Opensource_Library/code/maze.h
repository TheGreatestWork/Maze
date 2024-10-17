/*
 * maze.h
 *
 */

#ifndef CODE_MAZE_H_
#define CODE_MAZE_H_

typedef enum
{
    gru = 1,        //上
    grl = 2,        //左
    grd = 3,        //下
    grr = 4         //右（逆时针方向）
}MAZE_DIR;

struct LEFT_EDGE
{
    int row;  //行坐标
    int col;  //列坐标
    int dir;  //生长方向
};

struct RIGHT_EDGE
{
    int row;  //行坐标
    int col;  //列坐标
    int dir;  //生长方向
};

void image_get(void);
void maze(void);
void tft_display(void);

#endif /* CODE_MAZE_H_ */
