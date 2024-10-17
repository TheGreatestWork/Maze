/*
 * maze.c
 *
 */

#include "zf_common_headfile.h"

#define AMOUNT 200//��ѭ������

#define LIN 94      //ͼ���С������
#define ROW 60      //ͼ���С����

#define BLACK 0   //��ɫ
#define WHITE 255     //��ɫ

uint8 image[ROW][LIN];
uint8 threshold = 150;//ͼ���ֵ����ֵ

struct LEFT_EDGE  L_edge[AMOUNT];       //��߽�ṹ��
struct RIGHT_EDGE R_edge[AMOUNT];       //�ұ߽�ṹ��

int grodir[5] = {0, gru, grl, grd, grr};//��������
int lledir[5][2] = {{0, 0}, {0, -1}, {1, 0}, {0, 1}, {-1, 0}};
int lupdir[5][2] = {{0, 0}, {-1, 0}, {0, -1}, {1, 0}, {0, 1}};
int rridir[5][2] = {{0, 0}, {0, 1}, {-1, 0}, {0, -1}, {1, 0}};
int rupdir[5][2] = {{0, 0}, {-1, 0}, {0, -1}, {1, 0}, {0, 1}};

int ldir_num[AMOUNT/10][4], rdir_num[AMOUNT/10][4];//����ͳ������������Ϣ


//-------------------------------------------------------------------------------------------------------------------
// �������      ͼ�������ʼ��
// ����˵��
// ���ز���      void
// ʹ��ʾ��      image_get();
// ��ע��Ϣ
//-------------------------------------------------------------------------------------------------------------------
void image_get(void)
{
    int i = 0, j = 0, row = 0, line = 0;
    for(i = 0; i < MT9V03X_H; i+=2)//ѹ��ͼ��60*94��+��ֵ������
    {
        for(j = 0; j < MT9V03X_W; j+=2)
        {
            if(mt9v03x_image[i][j] >= threshold){image[row][line] = WHITE;}
            else{image[row][line] = BLACK;}
            line++;
        }
        image[row][0] = BLACK;
        image[row][LIN-1] = BLACK;
        line = 0;
        row++;
    }
}

//--------------------------------------------------------------------------------- ----------------------------------
// �������      �Թ���ɨ��
// ����˵��
// ���ز���      void
// ʹ��ʾ��      maze();
// ��ע��Ϣ
//-------------------------------------------------------------------------------------------------------------------
void maze(void)
{
    int i = 0;
    int il = 1, ir = 1;
    int count = 0;
    int kl = 1, kr = 1;//kl��kr��ȡֵ��Χ1~4������������
    int gap = 10;
    static int n = LIN/2;
    int lindex = 0, rindex = 0;
    memset(ldir_num, 0, sizeof(ldir_num));
    memset(rdir_num, 0, sizeof(rdir_num));
/*****************************************************************************************************************************************/
    for(i = 0; i < LIN; i++)//�ȴ�ͼ������е��м�������Ѱ������㣬�õ������Թ������
    {
        if(image[ROW-2][n-i] == BLACK)
        {
            L_edge[0].col = n-i+1;
            L_edge[0].row = ROW-2;
            L_edge[0].dir = grodir[kl];
            ldir_num[(int)(il/gap)][kl]++;
            break;
        }
    }
    for(i = 0; i < LIN; i++)
    {
        if(image[ROW-2][n+i] == BLACK)
        {
            R_edge[0].col = n+i-1;
            R_edge[0].row = ROW-2;
            R_edge[0].dir = grodir[kr];
            rdir_num[(int)(ir/gap)][kr]++;
            break;
        }
    }
    n = (L_edge[0].col + R_edge[0].col)/2;
/*****************************************************************************************************************************************/
    while(count < AMOUNT)
    {
        if(lindex == 1 && rindex == 1){break;}
        if(lindex == 0)
        {
            if(image[L_edge[il-1].row + lledir[L_edge[il-1].dir][0]][L_edge[il-1].col + lledir[L_edge[il-1].dir][1]] == BLACK)//�����Ƿ�Ϊǽ
            {
                if(image[L_edge[il-1].row + lupdir[L_edge[il-1].dir][0]][L_edge[il-1].col + lupdir[L_edge[il-1].dir][1]] == BLACK)//ǰ���Ƿ�Ϊǽ
                {
                    kl--;//��ת
                    if(kl > 4){kl = 1;}
                    if(kl < 1){kl = 4;}
                    L_edge[il-1].dir = grodir[kl];
                    il--;
                }
                else//ǰ��
                {
                    L_edge[il].dir = L_edge[il-1].dir;
                    L_edge[il].row = L_edge[il-1].row+lupdir[L_edge[il-1].dir][0];
                    L_edge[il].col = L_edge[il-1].col+lupdir[L_edge[il-1].dir][1];
                    ldir_num[(int)(il/gap)][kl]++;
                }
            }
            else//��ת��ǰ��
            {
                kl++;
                if(kl > 4){kl = 1;}
                if(kl < 1){kl = 4;}
                L_edge[il-1].dir = grodir[kl];
                L_edge[il].dir = L_edge[il-1].dir;
                L_edge[il].row = L_edge[il-1].row+lupdir[L_edge[il-1].dir][0];
                L_edge[il].col = L_edge[il-1].col+lupdir[L_edge[il-1].dir][1];
                ldir_num[(int)(il/gap)][kl]++;
            }
            if(L_edge[il].row == 1){lindex = 1;}
        }
        if(rindex == 0)
        {
            if(image[R_edge[ir-1].row + rridir[R_edge[ir-1].dir][0]][R_edge[ir-1].col + rridir[R_edge[ir-1].dir][1]] == BLACK)//�����Ƿ�Ϊǽ
            {
                if(image[R_edge[ir-1].row + rupdir[R_edge[ir-1].dir][0]][R_edge[ir-1].col + rupdir[R_edge[ir-1].dir][1]] == BLACK)//ǰ���Ƿ�Ϊǽ
                {
                    kr++;//��ת
                    if(kr > 4){kr = 1;}
                    if(kr < 1){kr = 4;}
                    R_edge[ir-1].dir = grodir[kr];
                    ir--;
                }
                else//ǰ��
                {
                    R_edge[ir].dir = R_edge[ir-1].dir;
                    R_edge[ir].row = R_edge[ir-1].row+rupdir[R_edge[ir-1].dir][0];
                    R_edge[ir].col = R_edge[ir-1].col+rupdir[R_edge[ir-1].dir][1];
                    rdir_num[(int)(ir/gap)][kr]++;
                }
            }
            else//��ת��ǰ��
            {
                kr--;
                if(kr > 4){kr = 1;}
                if(kr < 1){kr = 4;}
                R_edge[ir-1].dir = grodir[kr];
                R_edge[ir].dir = R_edge[ir-1].dir;
                R_edge[ir].row = R_edge[ir-1].row+rupdir[R_edge[ir-1].dir][0];
                R_edge[ir].col = R_edge[ir-1].col+rupdir[R_edge[ir-1].dir][1];
                rdir_num[(int)(ir/gap)][kr]++;
            }
            if(R_edge[ir].row == 1){rindex = 1;}
        }
        if((L_edge[il].row == R_edge[ir].row && L_edge[il].col == R_edge[ir].col) ||
           (L_edge[il].row == R_edge[ir-1].row && L_edge[il].col == R_edge[ir-1].col))
        {
            break;
        }
        if(lindex == 0){il+=1;}
        if(rindex == 0){ir+=1;}
        count++;
    }
/*****************************************************************************************************************************************/
    for(; il < AMOUNT; il++)
    {
        L_edge[il].row = 0;
        L_edge[il].col = 0;
        L_edge[il].dir = 0;
    }
    for(; ir < AMOUNT; ir++)
    {
        R_edge[ir].row = 0;
        R_edge[ir].col = 0;
        R_edge[ir].dir = 0;
    }
}

extern int tim;//������ʾʱ�䣬������main.c�ļ���
//--------------------------------------------------------------------------------- ----------------------------------
// �������
// ����˵��
// ���ز���      void
// ʹ��ʾ��      tft_display();
// ��ע��Ϣ
//-------------------------------------------------------------------------------------------------------------------
void tft_display(void)
{
    tft180_show_gray_image(0, 0, image[0], LIN, ROW, LIN, ROW, 0);//����ͷ
    for(int i = 0; i < AMOUNT; i++)//���ߴ�ӡ
    {
        tft180_draw_point((uint16)L_edge[i].col, (uint16)L_edge[i].row, RGB565_RED);
        tft180_draw_point((uint16)R_edge[i].col, (uint16)R_edge[i].row, RGB565_BLUE);
    }
    tft180_show_string(0, 80, "time:");
    tft180_show_float (40, 80, (float)tim/1000, 2, 3);
    tft180_show_string(80, 80, "ms");
}
