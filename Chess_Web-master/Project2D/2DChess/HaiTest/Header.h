



#include <SFML/Graphics.hpp>

#include <SFML/Network.hpp>
#include<math.h>


#include<stack>
#include<algorithm>

#include <iostream>
#include<stdio.h>

#include<conio.h>
#include<iostream>

#include<windows.h>
#include<string>

#include <time.h>


#include <vector>
#include <iomanip>
#include <numeric>



using namespace sf;
//using namespace std;

int size = 60; //size chess


int board[14][14] =
{
  7, 7, 7, 1, 2, 3, 4, 5, 3, 2, 1, 7, 7, 7,
  7, 7, 7, 8, 8, 8, 8, 8, 8, 8, 8, 7, 7, 7,
  7, 7, 7, 0, 0, 0, 0, 0, 0, 0, 0, 7, 7, 7,
 -1,-6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,-8,-1,
 -2,-6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,-8,-2,
 -3,-6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,-8,-3,
 -5,-6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,-8,-4,
 -4,-6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,-8,-5,
 -3,-6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,-8,-3,
 -2,-6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,-8,-2,
 -1,-6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,-8,-1,
  7, 7, 7, 0, 0, 0, 0, 0, 0, 0, 0, 7, 7, 7,
  7, 7, 7, 6, 6, 6, 6, 6, 6, 6, 6, 7, 7, 7,
  7, 7, 7, 1, 2, 3, 5, 4, 3, 2, 1, 7, 7, 7
};

typedef struct QuanCo
{
    Sprite s;
    int index{};
    int cost{};
};

class GameManager
{
public:
    QuanCo f[65]; //mang luu cac quan co  f[65]
    Vector2f movablesA[196]; 
    Vector2f movables1A[196]; //lưu các giá trị đã đươc xóa các ohaanf tử trùng lặp
  
    Vector2f movablesB[196];
    Vector2f movables2B[196];// lưu các giá trị đã đươc xóa các ohaanf tử trùng lặp
   
    Vector2f positiveMove[1196];//vi tri cac nuoc co the di chuyen
    int positiveCount{};// so nuoc co the di chuyen
    std::stack<Vector2f> posS;//luu tru vi tri cac nuoc di
    std::stack<int> nS;//luu tru index cua quan di
    void move(int n, Vector2f oldPos, Vector2f newPos);//ham danh co
    void Play();// choi: moi thao tac o day
    void Undo();//ham quay lai

    void PositiveXe(int n, int x, int y, int grid[14][14]);//tim cac nuoc co the di cua Quan Xe
    void PositiveTuong(int n, int x, int y, int grid[14][14]);//tim cac nuoc co the di cua Quan Tuong
    void PositiveMa(int n, int x, int y, int grid[14][14]);//tim cac nuoc co the di cua Quan Ma
    void PositiveVua(int n, int x, int y, int grid[14][14]);//tim cac nuoc co the di cua Quan Vua

    void PositiveTotTrang(int n, int x, int y, int grid[14][14]);
    void PositiveTotDen(int n, int x, int y, int grid[14][14]);
    void PositiveTotXanh(int n, int x, int y, int grid[14][14]);
    void PositiveTotHong(int n, int x, int y, int grid[14][14]);

    void IncreasePositive(int i, int j);//tang so nuoc co the di
    void PositiveMoving(int n);//tim cac nuoc co the di ung voi index n

};

void GameManager::move(int n, Vector2f oldPos, Vector2f newPos)
{
    posS.push(oldPos); //click 1
    posS.push(newPos);//click2
    nS.push(n);

    for (int i = 0; i < 64; i++) {
        if (f[i].s.getPosition() == newPos) {
            f[i].s.setPosition(-100, -100);//di chuyen em bi aans ra khoi man hinh
            posS.push(newPos);
            posS.push(Vector2f(-100, -100));
            nS.push(i);
            break;//neu ta dat f[n].s.setPosition(newPos) len truoc ma ko co break=> bi mat not con nay
        }
    }
    f[n].s.setPosition(newPos);
}


void GameManager::Undo()
{   
    // std::stack<int> nS;//luu tru index cua quan di
    int n = nS.top();
    nS.pop();
    Vector2f p = posS.top();//kiem tra xem co = (-100,-100) => day la con bi an
    posS.pop();
    f[n].s.setPosition(posS.top());
    posS.pop();
    if (p == Vector2f(-100, -100)) Undo();// luc nay moi dy chuyen con an
}


void GameManager::PositiveTotTrang(int n, int x, int y, int grid[14][14])
{
    int k =1;
    if (k == 1)// 1 hoac -1     
    {
        if ((y == 12) && grid[x][y - k] == 0 && grid[x][y - 2 * k] == 0 && y - 2 * k >= 0 && y - 2 * k < 14) IncreasePositive(x, y - 2 * k);
        if (grid[x][y - k] == 0 && y - k >= 0 && y - k < 14)            IncreasePositive(x, y - k);
        if (grid[x + 1][y - k] * grid[x][y] < 0 && y - k >= 0 && y - k < 14 && x + 1 < 14)       IncreasePositive(x + 1, y - k);
        if (grid[x - 1][y - k] * grid[x][y] < 0 && y - k >= 0 && y - k < 14 && x - 1 >= 0)      IncreasePositive(x - 1, y - k);
    }
}
void GameManager::PositiveTotDen(int n, int x, int y, int grid[14][14]) {
    int k =1;
    if (k == 1)// 1 
    {
        if ((y == 1) && grid[x][y + k] == 0 && grid[x][y + 2 * k] == 0 && y + 2 * k >= 0 && y + 2 * k < 14) IncreasePositive(x, y + 2 * k);
        if (grid[x][y + k] == 0 && y + k >= 0 && y + k < 14)            IncreasePositive(x, y + k);
        if (grid[x + 1][y + k] * grid[x][y] < 0 && y + k >= 0 && y + k < 14 && x + 1 < 14)       IncreasePositive(x + 1, y + k);
        if (grid[x - 1][y + k] * grid[x][y] < 0 && y - k >= 0 && y - k < 14 && x - 1 >= 0)      IncreasePositive(x - 1, y + k);
    }
}
void GameManager::PositiveTotXanh(int n, int x, int y, int grid[14][14]) {
    int k = 1;
    if (k ==1)// -1
    {
        if ((x == 1) && grid[x + k][y] == 0 && grid[x + 2 * k][y] == 0 && x + 2 * k >= 0 && x + 2 * k < 14) IncreasePositive(x + 2 * k, y);
        if (grid[x + k][y] == 0 && x + k >= 0 && x + k < 14)            IncreasePositive(x + k, y);
        if (grid[x + 1][y - k] * grid[x][y] < 0 && y - k >= 0 && y - k < 14 && x + 1 < 14)       IncreasePositive(x + 1, y - k);
        if (grid[x + 1][y + k] * grid[x][y] < 0 && y - k >= 0 && y - k < 14 && x - 1 >= 0)      IncreasePositive(x + 1, y + k);
    }
}
void GameManager::PositiveTotHong(int n, int x, int y, int grid[14][14]) {
    int k=1;
    if (k ==1)// -1
    {

        {
            if ((x == 12) && grid[x - k][y] == 0 && grid[x - 2 * k][y] == 0 && x - 2 * k >= 0 && x - 2 * k < 14) IncreasePositive(x - 2 * k, y);
            if (grid[x - k][y] == 0 && x - k >= 0 && x - k < 14)            IncreasePositive(x - k, y);
            if (grid[x - 1][y + k] * grid[x][y] < 0 && x - 1 >= 0 && x - 1 < 14 && y + k < 14)       IncreasePositive(x - 1, y + k);
            if (grid[x - 1][y - k] * grid[x][y] < 0 && y - k >= 0 && y - k < 14 && x - 1 >= 0)      IncreasePositive(x - 1, y - k);
        }
    }
}
// chess mã
void GameManager::PositiveMa(int n, int x, int y, int grid[14][14])//xet vi tri co the di cua ma
{
    if (grid[x][y] != 7) {

        if ((grid[x + 2][y + 1] == 0 || grid[x][y] * grid[x + 2][y + 1] < 0) && (grid[x + 2][y + 1] != 7) && x + 2 < 14 && y + 1 < 14)  IncreasePositive(x + 2, y + 1);
        if ((grid[x + 2][y - 1] == 0 || grid[x][y] * grid[x + 2][y - 1] < 0) && (grid[x + 2][y - 1] != 7) && y - 1 >= 0 && x + 2 < 14)  IncreasePositive(x + 2, y - 1);
        if ((grid[x - 2][y + 1] == 0 || grid[x][y] * grid[x - 2][y + 1] < 0) && (grid[x - 2][y + 1] != 7) && x - 2 >= 0 && y + 1 < 14)  IncreasePositive(x - 2, y + 1);
        if ((grid[x - 2][y - 1] == 0 || grid[x][y] * grid[x - 2][y - 1] < 0) && (grid[x - 2][y - 1] != 7) && x - 2 >= 0 && y - 1 >= 0) IncreasePositive(x - 2, y - 1);
        if ((grid[x + 1][y + 2] == 0 || grid[x][y] * grid[x + 1][y + 2] < 0) && (grid[x + 1][y + 2] != 7) && x + 1 < 14 && y + 2 < 14)  IncreasePositive(x + 1, y + 2);
        if ((grid[x - 1][y + 2] == 0 || grid[x][y] * grid[x - 1][y + 2] < 0) && (grid[x - 1][y + 2] != 7) && x - 1 >= 0 && y + 2 < 14)  IncreasePositive(x - 1, y + 2);
        if ((grid[x + 1][y - 2] == 0 || grid[x][y] * grid[x + 1][y - 2] < 0) && (grid[x + 1][y - 2] != 7) && y - 2 >= 0 && x + 1 < 14)  IncreasePositive(x + 1, y - 2);
        if ((grid[x - 1][y - 2] == 0 || grid[x][y] * grid[x - 1][y - 2] < 0) && (grid[x - 1][y - 2] != 7) && x - 1 >= 0 && y - 2 >= 0) IncreasePositive(x - 1, y - 2);
    }
}
//vua //xet vi tri co the di cua vua
void GameManager::PositiveVua(int n, int x, int y, int grid[14][14]) {
    if (grid[x][y] != 7) {
        if ((grid[x + 1][y] == 0 || grid[x][y] * grid[x + 1][y] < 0) && x + 1 < 14)     IncreasePositive(x + 1, y);
        if ((grid[x - 1][y] == 0 || grid[x][y] * grid[x - 1][y] < 0) && x - 1 >= 0)     IncreasePositive(x - 1, y);
        if ((grid[x + 1][y + 1] == 0 || grid[x][y] * grid[x + 1][y + 1] < 0) && x + 1 < 14 && y + 1 < 14)  IncreasePositive(x + 1, y + 1);
        if ((grid[x - 1][y + 1] == 0 || grid[x][y] * grid[x - 1][y + 1] < 0) && x - 1 >= 0 && y + 1 < 14)  IncreasePositive(x - 1, y + 1);
        if ((grid[x][y + 1] == 0 || grid[x][y] * grid[x][y + 1] < 0) && y + 1 < 14)     IncreasePositive(x, y + 1);
        if ((grid[x - 1][y - 1] == 0 || grid[x][y] * grid[x - 1][y - 1] < 0) && x - 1 >= 0 && y - 1 >= 0) IncreasePositive(x - 1, y - 1);
        if ((grid[x + 1][y - 1] == 0 || grid[x][y] * grid[x + 1][y - 1] < 0) && y - 1 >= 0 && x + 1 < 14)  IncreasePositive(x + 1, y - 1);
        if ((grid[x][y - 1] == 0 || grid[x][y] * grid[x][y - 1] < 0) && y - 1 >= 0)     IncreasePositive(x, y - 1);
    }
}
//quan xe
void GameManager::PositiveXe(int n, int x, int y, int grid[14][14])//tu vi tri (x,y) xet ra
{

    for (int i = x + 1; i < 14; i++) {
        if (grid[i][y] != 7) {
            if (grid[i][y] != 0) {
                if (grid[i][y] * grid[x][y] < 0)       IncreasePositive(i, y);
                break;
            }
            IncreasePositive(i, y);
        }
    }
    for (int i = x - 1; i >= 0; i--) {
        if (grid[i][y] != 7) {
            if (grid[i][y] != 0) {
                if (grid[i][y] * grid[x][y] < 0)       IncreasePositive(i, y);
                break;
            }
            IncreasePositive(i, y);
        }
    }
    for (int j = y + 1; j < 14; j++) {
        if (grid[x][j] != 7) {
            if (grid[x][j] != 0) {
                if (grid[x][j] * grid[x][y] < 0)       IncreasePositive(x, j);
                break;
            }
            IncreasePositive(x, j);
        }
    }
    for (int j = y - 1; j >= 0; j--) {
        if (grid[x][j] != 7) {
            if (grid[x][j] != 0) {
                if (grid[x][j] * grid[x][y] < 0)       IncreasePositive(x, j);
                break;
            }
            IncreasePositive(x, j);
        }
    }

}
//tượng
void GameManager::PositiveTuong(int n, int x, int y, int grid[14][14])//tu vi tri (x,y) xet ra 4 huong cheo
{
    for (int i = x + 1, j = y + 1; (i < 14 && j < 14); i++, j++)
    {
        if (grid[i][j] != 7) {
            if (grid[i][j] != 0) {
                if (grid[i][j] * grid[x][y] < 0)  IncreasePositive(i, j);
                break;
            }
            IncreasePositive(i, j);
        }
    }
    for (int i = x + 1, j = y - 1; (i < 14 && j >= 0); i++, j--)
    {
        if (grid[i][j] != 7) {
            if (grid[i][j] != 0) {
                if (grid[i][j] * grid[x][y] < 0)  IncreasePositive(i, j);
                break;
            }
            IncreasePositive(i, j);
        }
    }
    for (int i = x - 1, j = y + 1; (i >= 0 && j < 14); i--, j++){
        if (grid[i][j] != 7) {
            if (grid[i][j] != 0) {
                if (grid[i][j] * grid[x][y] < 0)  IncreasePositive(i, j);
                break;
            }
            IncreasePositive(i, j);
        }
    }
    for (int i = x - 1, j = y - 1; (i >= 0 && j >= 0); i--, j--){
        if (grid[i][j] != 7) {
            if (grid[i][j] != 0) {
                if (grid[i][j] * grid[x][y] < 0)  IncreasePositive(i, j);
                break;
            }
            IncreasePositive(i, j);
        }
    }
}

//mang tatca cac nuoc di cua 1 phe A
//chuyen mang2 chieu vector2f -> mang 1 chieu ntn 
// vector2f(x,y) -> x*14 + y 
// Vector2f(i * size, j * size); -> x/size *14 + y/size 
// i *14 + j
// 
// 
//neu mà viết hàm cho mảng 2 chiều vector2f thì so sánh và xóa ntn ?
// sắp xếp mảng 2 chiều ntn ?
// -> thử làm thủ công (xử lý từng mảng vector2f tức là sẽ xóa các phần tử bằng nhau bằng cách
//dùng 2 for để tìm những ptu khác nhau thì cho vào 1 mảng vector khác. -> xóa thành công
//so sánh với vua.
//mang tat ca cac nuoc di cua 1 phe A


//ham tang so nuoc co the di (luu cac vi tri co the di)
void GameManager::IncreasePositive(int i, int j){   
    positiveMove[positiveCount] = Vector2f(i * size, j * size);
    positiveCount++;
}
//chuyển sang truy vấn mảng 1 chiều nhưng nó có thể sẽ động đến phần luật quân cờ////
///

void GameManager::PositiveMoving(int n)
{
    //float(size);
    Vector2f pos = f[n].s.getPosition();
    //int hay float?
    int x = pos.x / size;
    int y = pos.y / size;
    int grid[14][14];//mang luoi(14x14) luu lai cac vi tri ban co:
    Vector2i vtri;
    for (int i = 0; i < 14; i++)
        for (int j = 0; j < 14; j++)
            grid[i][j] = 0;// neu khong co quan co nao o O nay thi =0
    //fix loi khong cho quan co di vaof 4 vung khong dduojc di
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++)
            grid[i][j] = 7;
    }
    for (int i = 0; i < 3; i++) {
        for (int j = 11; j < 14; j++)
            grid[i][j] = 7;
    }
    for (int i = 11; i < 14; i++) {
        for (int j = 0; j < 3; j++)
            grid[i][j] = 7;
    }
    for (int i = 11; i < 14; i++) {
        for (int j = 11; j < 14; j++)
            grid[i][j] = 7;
    }
    for (int j = 0; j < 64; j++)
    {
        vtri = Vector2i(f[j].s.getPosition());
        grid[vtri.x / size][vtri.y / size] = f[j].index;// neu co = index cua quan co
    }
    if ((f[n].index) == 1 || (f[n].index) == -1)      PositiveXe(n, x, y, grid);//xe

    else if ((f[n].index) == 6) { PositiveTotTrang(n, x, y, grid); }
    else if ((f[n].index) == 8) PositiveTotDen(n, x, y, grid);
    else if ((f[n].index) == -8) PositiveTotHong(n, x, y, grid);
    else if ((f[n].index) == -6) PositiveTotXanh(n, x, y, grid);

    else if ((f[n].index) == 2 || (f[n].index) == -2) PositiveMa(n, x, y, grid);
    else if ((f[n].index) == 4 || (f[n].index) == -5) PositiveVua(n, x, y, grid);
    else if ((f[n].index) == 3 || (f[n].index) == -3) PositiveTuong(n, x, y, grid);
    else if ((f[n].index) == 5 || (f[n].index) == -4) {
        PositiveXe(n, x, y, grid);
        PositiveTuong(n, x, y, grid);
    }
}



void GameManager::Play()
{
    
    RenderWindow window(VideoMode(840, 840), "The Chess! Alpha Beta Pruning");
    Texture t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16, t17, t18, t19, t20, t21, t22, t23, t24, t25, t26;
    //ve cac quan cờ
    t1.loadFromFile("Four-handed_chess840_840_final2.png");
   
    t26.loadFromFile("CheckMate840_2.png");
    
    Sprite chieuTuong(t26);
    chieuTuong.setPosition(-1000, -1000);
    t25.loadFromFile("1601.m00.i125.n009.p.c25.231615226 game over message in vector cartoon style-ai (1).png");
   
    Sprite endgame(t25);
    endgame.setPosition(-1000, -1000);
    Sprite goiY(t26);
    Sprite sBoard(t1);
    //sBoard.scale(0,0);
    //thay doi kich co cua anh bang kick co man hinh
   // sBoard.setScale(static_cast<int>(window.getSize().x) / t1.getSize().x,
   //     static_cast<int>(window.getSize().y) / t1.getSize().y);
    int k = 0;
    for (int i = 0; i < 2; i++) {
        for (int j = 3; j < 14; j++) {
            int n;
            n = board[i][j];
            if (n == 1) {
                f[k].index = n;
                t2.loadFromFile("BlackRook60_60.png");
                f[k].s.setTexture(t2);
                f[k].s.setPosition(Vector2f(size * j, size * i));
                k++;
            }
            else if (n == 2) {
                f[k].index = n;
                t3.loadFromFile("BlackKnight60_60.png");
                f[k].s.setTexture(t3);
                f[k].s.setPosition(Vector2f(size * j, size * i));
                k++;
            }
            else if (n == 3) {
                f[k].index = n;
                t4.loadFromFile("BlackBishop60_60.png");
                f[k].s.setTexture(t4);
                f[k].s.setPosition(Vector2f(size * j, size * i));
                k++;
            }
            else if (n == 4) {
                f[k].index = n;
                t5.loadFromFile("BlackKing60_60.png");
                f[k].s.setTexture(t5);
                f[k].s.setPosition(Vector2f(size * j, size * i));
                printf("blackKing k = %d \n", k);
                k++;

            }
            else if (n == 5) {
                f[k].index = n;
                t6.loadFromFile("BlackQueen60_60.png");
                f[k].s.setTexture(t6);
                f[k].s.setPosition(Vector2f(size * j, size * i));
                k++;
            }
            else if (n == 8) {
                f[k].index = n;
                t7.loadFromFile("BlackPawn60_60.png");
                f[k].s.setTexture(t7);
                f[k].s.setPosition(Vector2f(size * j, size * i));
                //   f[k].score = 10;
               //    printf("f[k] score= %d \n", f[k].score);
                k++;
            }

        }
    }
    //*white (13)
    for (int j = 13; j >= 0; j--) {
        int i = 13;
        int n;
        n = board[i][j];
        if (n == 1) {
            f[k].index = n;
            t8.loadFromFile("WhiteRook60_60.png");
            f[k].s.setTexture(t8);
            f[k].s.setPosition(Vector2f(size * j, size * i));
            k++;
        }
        else if (n == 2) {
            f[k].index = n;
            t9.loadFromFile("WhiteKnight60_60.png");
            f[k].s.setTexture(t9);
            f[k].s.setPosition(Vector2f(size * j, size * i));
            k++;
        }
        else if (n == 3) {
            f[k].index = n;
            t10.loadFromFile("WhiteBishop60_60.png");
            f[k].s.setTexture(t10);
            f[k].s.setPosition(Vector2f(size * j, size * i));
            k++;
        }
        else if (n == 4) {
            f[k].index = n;
            t11.loadFromFile("WhiteKing60_60.png");
            f[k].s.setTexture(t11);
            f[k].s.setPosition(Vector2f(size * j, size * i));
            printf("WhiteKing k = %d \n", k);
            k++;
        }
        else if (n == 5) {
            f[k].index = n;
            t12.loadFromFile("WhiteQueen60_60.png");
            f[k].s.setTexture(t12);
            f[k].s.setPosition(Vector2f(size * j, size * i));
            k++;
        }

    }
    // WhitePawn ( i= 12)
    for (int j = 3; j < 14; j++) {
        int i = 12;
        int n;
        n = board[i][j];
        if (n == 6) {
            f[k].index = n;
            t13.loadFromFile("WhitePawn60_60.png");
            f[k].s.setTexture(t13);
            f[k].s.setPosition(Vector2f(size * j, size * i));
            // f[k].score = 10;
            k++;
        }

    }
    // left chess
    for (int i = 3; i < 14; i++) {
        int j = 0; {
            int n;
            n = board[i][j];
            if (n == -1) {
                f[k].index = n;
                t14.loadFromFile("WhiteRook60_60.png");
                f[k].s.setColor(sf::Color(92, 160, 205));
                f[k].s.setTexture(t14);
                f[k].s.setPosition(Vector2f(size * j, size * i));
                k++;
            }
            else if (n == -2) {
                f[k].index = n;
                t15.loadFromFile("WhiteKnight60_60.png");
                f[k].s.setColor(sf::Color(92, 160, 205));
                f[k].s.setTexture(t15);
                f[k].s.setPosition(Vector2f(size * j, size * i));
                k++;
            }
            else if (n == -3) {
                f[k].index = n;
                t16.loadFromFile("WhiteBishop60_60.png");
                f[k].s.setColor(sf::Color(92, 160, 205));
                f[k].s.setTexture(t16);
                f[k].s.setPosition(Vector2f(size * j, size * i));
                k++;
            }
            else if (n == -4) {
                f[k].index = n;
                t17.loadFromFile("WhiteQueen60_60.png");
                f[k].s.setColor(sf::Color(92, 160, 205));
                f[k].s.setTexture(t17);
                f[k].s.setPosition(Vector2f(size * j, size * i));
                k++;
            }
            else if (n == -5) {
                f[k].index = n;
                t18.loadFromFile("WhiteKing60_60.png");
                f[k].s.setColor(sf::Color(92, 160, 205));
                f[k].s.setTexture(t18);
                f[k].s.setPosition(Vector2f(size * j, size * i));
                printf("BlueKing k = %d \n", k);
                k++;
            }

        }
    }
    for (int i = 3; i < 14; i++) {
        int j = 1; {
            int n;
            n = board[i][j];
            if (n == -6) {
                f[k].index = n;
                t19.loadFromFile("WhitePawn60_60.png");
                f[k].s.setColor(sf::Color(92, 160, 205));
                f[k].s.setTexture(t19);
                f[k].s.setPosition(Vector2f(size * j, size * i));
                k++;
            }
        }
    }

    //right chess
    for (int i = 3; i < 14; i++) {
        int j = 13; {
            int n;
            n = board[i][j];
            if (n == -1) {
                f[k].index = n;
                t20.loadFromFile("WhiteRook60_60.png");
                f[k].s.setColor(sf::Color(237, 107, 107));
                f[k].s.setTexture(t20);
                f[k].s.setPosition(Vector2f(size * j, size * i));
                k++;
            }
            else if (n == -2) {
                f[k].index = n;
                t21.loadFromFile("WhiteKnight60_60.png");
                f[k].s.setColor(sf::Color(237, 107, 107));
                f[k].s.setTexture(t21);
                f[k].s.setPosition(Vector2f(size * j, size * i));
                k++;
            }
            else if (n == -3) {
                f[k].index = n;
                t22.loadFromFile("WhiteBishop60_60.png");
                f[k].s.setColor(sf::Color(237, 107, 107));
                f[k].s.setTexture(t22);
                f[k].s.setPosition(Vector2f(size * j, size * i));
                k++;
            }
            else if (n == -4) {
                f[k].index = n;
                t17.loadFromFile("WhiteQueen60_60.png");
                f[k].s.setColor(sf::Color(237, 107, 107));
                f[k].s.setTexture(t17);
                f[k].s.setPosition(Vector2f(size * j, size * i));
                k++;
            }
            else if (n == -5) {
                f[k].index = n;
                t23.loadFromFile("WhiteKing60_60.png");
                f[k].s.setColor(sf::Color(237, 107, 107));
                f[k].s.setTexture(t23);
                f[k].s.setPosition(Vector2f(size * j, size * i));
                printf("PinkKing k = %d \n", k);
                k++;
            }

        }
    }
    //right chess pawn
    for (int i = 3; i < 14; i++) {
        int j = 12; {
            int n;
            n = board[i][j];
            if (n == -8) {
                
                f[k].index = n;
                t24.loadFromFile("WhitePawn60_60.png");
                f[k].s.setColor(sf::Color(237, 107, 107));
                f[k].s.setTexture(t24);
                f[k].s.setPosition(Vector2f(size * j, size * i));
                printf("k tot den = %d", k);
                k++;
            }
        }
    }

    printf("k = %d\n", k);

    Vector2f oldPos, newPos;// luu vi tri click lan1 va lan2
    int n = 0, click = 0, count = 0; //n: lưu chỉ số trong mảng f, count: biến thay thế positiveMove, vì positiveMove là biến toàn cục nên thay đổi liên tục
     
    Vector2i pos;//vitri chuot khi click

    int scoreBlack = 0, scorePink = 0, scoreWhite = 0, scoreBlue = 0, tg = 0;
    bool isMove = false;
    int luotChoi = 1;


    while (window.isOpen())
    {

        Event e;
        while (window.pollEvent(e))
        {
            if (e.type == Event::Closed)
                window.close();
            ////move back bang banf phims//////
            if (e.type == Event::KeyPressed)
                if (e.key.code == Keyboard::BackSpace)
                {
                    Undo();
                }
            //  di chuyen
            if (e.type == Event::MouseButtonPressed) {
                if (e.mouseButton.button == Mouse::Left) {
                    pos = Mouse::getPosition(window);
                    click++;
                }
            }
        }
        // thứ tự lượt chơi là đen, hồng, trắng, xanh
        // luot choi tu 1 -> 4 tuong ung voi den, hong, trang, xanh
        //lươt choi bằng 1 thì quân đen đi trước
        if (luotChoi == 1) {
            if (f[3].s.getPosition() == Vector2f(-100, -100)) { //kiem tra xem con vua DEN khog, neu ko con thi luotchoi+1 -> ketthuc luot choi.
                luotChoi = 10;
                chieuTuong.setPosition(-1000, -1000);
                endgame.setPosition(0, 0);
                printf("luot choi =%d (+ 1) do mat Vua den\n", luotChoi);
            }
            else  if (click == 1) {
                chieuTuong.setPosition(-1000, -1000);
                bool isMove = false;
                for (int i = 0; i < 16; i++)
                {
                    if (f[i].s.getGlobalBounds().contains(pos.x, pos.y))
                    {
                        isMove = true;
                        n = i;
                        oldPos = f[n].s.getPosition();
                    }
                }
                if (!isMove) click = 0;
                //PositiveMoving tìm các nước có thể đi ứng với n, 
                else {
                    PositiveMoving(n); count = positiveCount; positiveCount = 0;
                }
            }
            else if (click == 2) {
                int x = pos.x / size;   int y = pos.y / size;
                newPos = Vector2f(x * size, y * size);
                int gameOver = 0;
                int QuanCoDangchieuTuong;
                int checkXemCoQuanNaoDangChieuKo = 0 ;
                //bool coTheAnQuanDangChieu = false;
                //bool xemQuanNaoDangChieu = false;
                //chi di chuyen trong vung positiveMove       
                for (int i = 0; i < count; i++) {
                    if (positiveMove[i] == newPos) {
                        move(n, oldPos, newPos); //n luc nay la vi tri khac nen phai PositiveMoving lai
                        //printf("quan co thu = %d", n);
                        //tim xem quan nao dang chieu vua 52 - vua hong
                        for (int kChieu = 0; kChieu < 32; kChieu++) {
                            PositiveMoving(kChieu); count = positiveCount; positiveCount = 0;
                            for (int i = 0; i < count; i++) {
                                if (positiveMove[i] == f[52].s.getPosition()) {
                                    QuanCoDangchieuTuong = kChieu;
                                    checkXemCoQuanNaoDangChieuKo = 52;
                                    break;
                                }
                            }
                        }
                        

                        //tim cac nuoc cua QuanCoDangchieuTuong de ve~ chieu tuong (co the ve trong ham for kChieu)
                        if (checkXemCoQuanNaoDangChieuKo == 52) {
                            PositiveMoving(QuanCoDangchieuTuong); count = positiveCount; positiveCount = 0;
                            for (int i = 0; i < count; i++) {
                                if (positiveMove[i] == f[52].s.getPosition()) {
                                    printf("chieu tuong vua hong\n");
                                    chieuTuong.setPosition(0, 0);                                 


                                        //check cac nuoc di cua B cho tung quan co
                                        int hetCo = 0;
                                        int quanCoChieuDcKhiBdiChuyen = -1000;
                                        bool vuaDiChuyenTranhChieu = false;
                                        
                                        int kA = 0;
                                        int dem = 0;
                                        int demSoNuocDiCuaVua = 0;
                                        //check xem Vua co the tu di de tranh chieu tuong khong?
                                        //cac nuoc di cua quan den + trang
                                        for (int i = 0; i < 32; i++) {
                                            PositiveMoving(i);  count = positiveCount; positiveCount = 0;
                                            for (int j = 0; j < count; j++) {
                                                movablesA[kA] = positiveMove[j];
                                                kA++;
                                            }
                                        }

                                        //xem cac nuoc di cua vua co nam trong cac nuoc di cua phe A khong
                                        PositiveMoving(52);  count = positiveCount; positiveCount = 0;
                                        demSoNuocDiCuaVua = count;
                                        printf("vua co the di so nuoc = %d\n", count);

                                            for (int i = 0; i < count; i++) {
                                                for (int j = 0; j < kA; j++) {
                                                    if (positiveMove[i] == movablesA[j] || positiveMove[i] == f[QuanCoDangchieuTuong].s.getPosition()) {
                                                        dem++;
                                                        //cong them vi tri cua quan co dang chieu tuong (vi trong mang dc di cua phe con lai khong co vi tri cua quan co nay)
                                                        break;
                                                    }
                                                }
                                            }
                                            printf("dem cac nuoc di cua vua ma  bi chieu = %d\n", dem);
                                            
                                            if (demSoNuocDiCuaVua == dem ) {
                                                printf("demSoNuocDiCuaVua = %d\n", demSoNuocDiCuaVua);
                                                for (int iB = 32; iB < 64; iB++) {
                                                    bool checkEndGame = true;
                                                    PositiveMoving(iB);  count = positiveCount; positiveCount = 0;
                                                    //nuoc co 1 quan cua B
                                                    for (int i = 0; i < count; i++) {

                                                        move(iB, f[iB].s.getPosition(), positiveMove[i]);
                                                        //tat cac nuoc di cua A khi B di chuyen 1 quan co vs 1 vitri khac nhau
                                                        for (int i = 0; i < 32; i++) {
                                                            PositiveMoving(i);  count = positiveCount; positiveCount = 0;
                                                            //so sanh tat ca cac nuoc di cua 1 quan A voi f[52].s.getPosition() 
                                                            //o day chi dang so sanh khi va chi khi vua dung yen 1 cho~
                                                            for (int i = 0; i < count; i++) {
                                                                if (positiveMove[i] == f[52].s.getPosition()) { //cho nay chua ddc logic chua dc vi la so sanh vua voi vi tri f[52]
                                                                    checkEndGame = false;
                                                                    break;
                                                                }
                                                            }
                                                        }

                                                        if (checkEndGame == true) {
                                                            hetCo = 1;
                                                        }
                                                        Undo();//phai di chuyen ve cho cu                                            
                                                    }
                                                }

                                                if (hetCo == 0) {
                                                    chieuTuong.setPosition(-1000, -1000);
                                                    endgame.setPosition(0, 0);
                                                    // luotChoi = 10;
                                                    gameOver = 10;
                                                }
                                            }
                                   // }

                                }
                            }
                        }
                           //tim xem quan nao dang chieu vua 35 - vua xanh
                           for (int kChieu = 0; kChieu < 32; kChieu++) {
                               PositiveMoving(kChieu); count = positiveCount; positiveCount = 0;
                               for (int i = 0; i < count; i++) {
                                   if (positiveMove[i] == f[35].s.getPosition()) {
                                       QuanCoDangchieuTuong = kChieu;
                                       checkXemCoQuanNaoDangChieuKo = 35;
                                       break;
                                   }
                               }
                           }
                           //tim cac nuoc cua QuanCoDangchieuTuong de ve~ chieu tuong
                           if (checkXemCoQuanNaoDangChieuKo == 35) {
                               PositiveMoving(QuanCoDangchieuTuong); count = positiveCount; positiveCount = 0;
                               for (int i = 0; i < count; i++) {

                                   if (positiveMove[i] == f[35].s.getPosition()) {
                                       printf("chieu tuong vua xanh\n");
                                       chieuTuong.setPosition(0, 0);
                                      
                                       //check cac nuoc di cua B cho tung quan co
                                       int hetCo = 0;
                                       int quanCoChieuDcKhiBdiChuyen = -1000;
                                       bool vuaDiChuyenTranhChieu = false;

                                       int kA = 0;
                                       int dem = 0;
                                       int demSoNuocDiCuaVua = 0;
                                       //check xem Vua co the tu di de tranh chieu tuong khong?
                                       //cac nuoc di cua quan den + trang
                                       for (int i = 0; i < 32; i++) {
                                           PositiveMoving(i);  count = positiveCount; positiveCount = 0;
                                           for (int j = 0; j < count; j++) {
                                               movablesA[kA] = positiveMove[j];
                                               kA++;
                                           }
                                       }

                                       //xem cac nuoc di cua vua co nam trong cac nuoc di cua phe A khong
                                       PositiveMoving(35);  count = positiveCount; positiveCount = 0;
                                       demSoNuocDiCuaVua = count;
                                       printf("vua co the di so nuoc = %d\n", count);

                                       for (int i = 0; i < count; i++) {
                                           for (int j = 0; j < kA; j++) {
                                               if (positiveMove[i] == movablesA[j] || positiveMove[i] == f[QuanCoDangchieuTuong].s.getPosition()) {
                                                   dem++;
                                                   //cong them vi tri cua quan co dang chieu tuong (vi trong mang dc di cua phe con lai khong co vi tri cua quan co nay)
                                                   break;
                                               }
                                           }
                                       }
                                       printf("dem cac nuoc di cua vua ma  bi chieu = %d\n", dem);

                                       if (demSoNuocDiCuaVua == dem) {
                                           printf("demSoNuocDiCuaVua = %d\n", demSoNuocDiCuaVua);
                                           for (int iB = 32; iB < 64; iB++) {
                                               bool checkEndGame = true;
                                               PositiveMoving(iB);  count = positiveCount; positiveCount = 0;
                                               //nuoc co 1 quan cua B
                                               for (int i = 0; i < count; i++) {

                                                   move(iB, f[iB].s.getPosition(), positiveMove[i]);
                                                   //tat cac nuoc di cua A khi B di chuyen 1 quan co vs 1 vitri khac nhau
                                                   for (int i = 0; i < 32; i++) {
                                                       PositiveMoving(i);  count = positiveCount; positiveCount = 0;
                                                       //so sanh tat ca cac nuoc di cua 1 quan A voi f[52].s.getPosition() 
                                                       //o day chi dang so sanh khi va chi khi vua dung yen 1 cho~
                                                       for (int i = 0; i < count; i++) {
                                                           if (positiveMove[i] == f[35].s.getPosition()) { //cho nay chua ddc logic chua dc vi la so sanh vua voi vi tri f[52]
                                                               checkEndGame = false;
                                                               break;
                                                           }
                                                       }
                                                   }

                                                   if (checkEndGame == true) {
                                                       hetCo = 1;
                                                   }
                                                   Undo();//phai di chuyen ve cho cu                                            
                                               }
                                           }

                                           if (hetCo == 0) {
                                               chieuTuong.setPosition(-1000, -1000);
                                               endgame.setPosition(0, 0);
                                               // luotChoi = 10;
                                               gameOver = 10;
                                           }
                                       }
                                   }
                               }
                           }                                             
                       luotChoi = 2;
                    }
                }
                count = 0;
                click = 0;
                printf("luot choi %d\n", luotChoi);
                if (gameOver == 10) {
                    luotChoi = 10;
                    endgame.setPosition(0, 0);
                    printf("luotChoi %d\n", luotChoi);
                }
            }
        }
        //lươt choi bằng 2 thì quân hồng được đi
        else if (luotChoi == 2) {

            if (f[52].s.getPosition() == Vector2f(-100, -100) ) { //kiem tra xem con vua khog, neu ko con thi luotchoi+1 -> ketthuc luot choi.
                luotChoi = 10;
                chieuTuong.setPosition(-1000, -1000);
                endgame.setPosition(0, 0);
                printf("luot choi =%d (+ 1) do mat Vua hong\n", luotChoi);
            }
            else  if (click == 1) {
                chieuTuong.setPosition(-1000, -1000);
                bool isMove = false;
                for (int i = 48; i < 64; i++)
                {
                    if (f[i].s.getGlobalBounds().contains(pos.x, pos.y))
                    {
                        isMove = true;
                        n = i;
                        oldPos = f[n].s.getPosition();
                    }
                }
                if (!isMove) click = 0;
                else { PositiveMoving(n); count = positiveCount; positiveCount = 0; }
            }
            else if (click == 2) {
                int x = pos.x / size;   int y = pos.y / size;
                newPos = Vector2f(x * size, y * size);                
               
                int gameOver = 0;
                int QuanCoDangchieuTuong;
                int checkXemCoQuanNaoDangChieuKo = 0;
                //chi di chuyen trong vung positiveMove
                for (int i = 0; i < count; i++) {
                    if (positiveMove[i] == newPos) {
                        move(n, oldPos, newPos);

                        //tim xem quan nao dang chieu vua 3 - vua den
                        for (int kChieu = 32; kChieu < 64; kChieu++) {
                            PositiveMoving(kChieu); count = positiveCount; positiveCount = 0;
                            for (int i = 0; i < count; i++) {
                                if (positiveMove[i] == f[3].s.getPosition()) {
                                    QuanCoDangchieuTuong = kChieu;
                                    checkXemCoQuanNaoDangChieuKo = 3;
                                    break;
                                }
                            }
                        }

                        //tim cac nuoc cua QuanCoDangchieuTuong de ve~ chieu tuong
                        if (checkXemCoQuanNaoDangChieuKo == 3) {
                            PositiveMoving(QuanCoDangchieuTuong); count = positiveCount; positiveCount = 0;
                            for (int i = 0; i < count; i++) {
                                if (positiveMove[i] == f[3].s.getPosition()) {
                                    printf("chieu tuong vua den\n");
                                    chieuTuong.setPosition(0, 0);

                                    int hetCo = 0;
                                    int quanCoChieuDcKhiBdiChuyen = -1000;
                                    bool vuaDiChuyenTranhChieu = false;

                                    int kA = 0;
                                    int dem = 0;
                                    int demSoNuocDiCuaVua = 0;
                                    //check xem Vua co the tu di de tranh chieu tuong khong?
                                    //cac nuoc di cua quan hong + xanh
                                    for (int i = 32; i < 64; i++) {
                                        PositiveMoving(i);  count = positiveCount; positiveCount = 0;
                                        for (int j = 0; j < count; j++) {
                                            movablesA[kA] = positiveMove[j];
                                            kA++;
                                        }
                                    }

                                    //xem cac nuoc di cua vua co nam trong cac nuoc di cua phe A khong
                                    PositiveMoving(3);  count = positiveCount; positiveCount = 0;
                                    demSoNuocDiCuaVua = count;
                                    printf("vua co the di so nuoc = %d\n", count);

                                    for (int i = 0; i < count; i++) {
                                        for (int j = 0; j < kA; j++) {
                                            if (positiveMove[i] == movablesA[j] || positiveMove[i] == f[QuanCoDangchieuTuong].s.getPosition()) {
                                                dem++;
                                                //cong them vi tri cua quan co dang chieu tuong (vi trong mang dc di cua phe con lai khong co vi tri cua quan co nay)
                                                break;
                                            }
                                        }
                                    }
                                    printf("dem cac nuoc di cua vua ma  bi chieu = %d\n", dem);

                                    if (demSoNuocDiCuaVua == dem) {
                                        printf("demSoNuocDiCuaVua = %d\n", demSoNuocDiCuaVua);
                                        for (int iB = 0; iB < 32; iB++) {
                                            bool checkEndGame = true;
                                            PositiveMoving(iB);  count = positiveCount; positiveCount = 0;
                                            //nuoc co 1 quan cua B
                                            for (int i = 0; i < count; i++) {

                                                move(iB, f[iB].s.getPosition(), positiveMove[i]);
                                                //tat cac nuoc di cua A khi B di chuyen 1 quan co vs 1 vitri khac nhau
                                                for (int i = 32; i < 64; i++) {
                                                    PositiveMoving(i);  count = positiveCount; positiveCount = 0;
                                                    //so sanh tat ca cac nuoc di cua 1 quan A voi f[3].s.getPosition() 
                                                    //o day chi dang so sanh khi va chi khi vua dung yen 1 cho~
                                                    for (int i = 0; i < count; i++) {
                                                        if (positiveMove[i] == f[3].s.getPosition()) { //cho nay chua ddc logic chua dc vi la so sanh vua voi vi tri f[3]
                                                            checkEndGame = false;
                                                            break;
                                                        }
                                                    }
                                                }

                                                if (checkEndGame == true) {
                                                    hetCo = 1;
                                                }
                                                Undo();//phai di chuyen ve cho cu                                            
                                            }
                                        }

                                        if (hetCo == 0) {
                                            chieuTuong.setPosition(-1000, -1000);
                                            endgame.setPosition(0, 0);
                                            // luotChoi = 10;
                                            gameOver = 10;
                                        }
                                    }
                                    
                                }
                            }
                        }
                        //tim xem quan nao dang chieu vua 19 - vua trang
                        for (int kChieu = 32; kChieu < 64; kChieu++) {
                            PositiveMoving(kChieu); count = positiveCount; positiveCount = 0;
                            for (int i = 0; i < count; i++) {
                                if (positiveMove[i] == f[19].s.getPosition()) {
                                    QuanCoDangchieuTuong = kChieu;
                                    checkXemCoQuanNaoDangChieuKo = 19;
                                    break;
                                }
                            }
                        }

                        //tim cac nuoc cua QuanCoDangchieuTuong de ve~ chieu tuong
                        if (checkXemCoQuanNaoDangChieuKo == 19) {
                            PositiveMoving(QuanCoDangchieuTuong); count = positiveCount; positiveCount = 0;
                            for (int i = 0; i < count; i++) {
                                if (positiveMove[i] == f[19].s.getPosition()) {
                                    printf("chieu tuong vua den\n");
                                    chieuTuong.setPosition(0, 0);

                                    int hetCo = 0;
                                    int quanCoChieuDcKhiBdiChuyen = -1000;
                                    bool vuaDiChuyenTranhChieu = false;

                                    int kA = 0;
                                    int dem = 0;
                                    int demSoNuocDiCuaVua = 0;
                                    //check xem Vua co the tu di de tranh chieu tuong khong?
                                    //cac nuoc di cua quan hong + xanh
                                    for (int i = 32; i < 64; i++) {
                                        PositiveMoving(i);  count = positiveCount; positiveCount = 0;
                                        for (int j = 0; j < count; j++) {
                                            movablesA[kA] = positiveMove[j];
                                            kA++;
                                        }
                                    }

                                    //xem cac nuoc di cua vua co nam trong cac nuoc di cua phe A khong
                                    PositiveMoving(19);  count = positiveCount; positiveCount = 0;
                                    demSoNuocDiCuaVua = count;
                                    printf("vua co the di so nuoc = %d\n", count);

                                    for (int i = 0; i < count; i++) {
                                        for (int j = 0; j < kA; j++) {
                                            if (positiveMove[i] == movablesA[j] || positiveMove[i] == f[QuanCoDangchieuTuong].s.getPosition()) {
                                                dem++;
                                                //cong them vi tri cua quan co dang chieu tuong (vi trong mang dc di cua phe con lai khong co vi tri cua quan co nay)
                                                break;
                                            }
                                        }
                                    }
                                    printf("dem cac nuoc di cua vua ma  bi chieu = %d\n", dem);

                                    if (demSoNuocDiCuaVua == dem) {
                                        printf("demSoNuocDiCuaVua = %d\n", demSoNuocDiCuaVua);
                                        for (int iB = 0; iB < 32; iB++) {
                                            bool checkEndGame = true;
                                            PositiveMoving(iB);  count = positiveCount; positiveCount = 0;
                                            //nuoc co 1 quan cua B
                                            for (int i = 0; i < count; i++) {

                                                move(iB, f[iB].s.getPosition(), positiveMove[i]);
                                                //tat cac nuoc di cua A khi B di chuyen 1 quan co vs 1 vitri khac nhau
                                                for (int i = 32; i < 64; i++) {
                                                    PositiveMoving(i);  count = positiveCount; positiveCount = 0;
                                                    //so sanh tat ca cac nuoc di cua 1 quan A voi f[3].s.getPosition() 
                                                    //o day chi dang so sanh khi va chi khi vua dung yen 1 cho~
                                                    for (int i = 0; i < count; i++) {
                                                        if (positiveMove[i] == f[19].s.getPosition()) { //cho nay chua ddc logic chua dc vi la so sanh vua voi vi tri f[3]
                                                            checkEndGame = false;
                                                            break;
                                                        }
                                                    }
                                                }

                                                if (checkEndGame == true) {
                                                    hetCo = 1;
                                                }
                                                Undo();//phai di chuyen ve cho cu                                            
                                            }
                                        }

                                        if (hetCo == 0) {
                                            chieuTuong.setPosition(-1000, -1000);
                                            endgame.setPosition(0, 0);
                                            // luotChoi = 10;
                                            gameOver = 10;
                                        }
                                    }

                                }
                            }
                        }

                        luotChoi = 3;
                    }
                }
                
                count = 0;
                click = 0;
                printf("luot choi %d\n", luotChoi);
                //kiem tra xem con vua den + vua trang ko, neu ko con thi endgame
                if (f[3].s.getPosition() == Vector2f(-100, -100) || f[19].s.getPosition() == Vector2f(-100, -100)) {
                    luotChoi = 10;
                    endgame.setPosition(0, 0);
                    printf("end game  %d", luotChoi);
                } 
                else if (gameOver == 10) {
                    luotChoi = 10;
                    endgame.setPosition(0, 0);
                    printf("luotChoi %d\n", luotChoi);
                }
            }
        }
        ////lươt choi bằng 3 thì quân trắng được đi
        else if (luotChoi == 3) {
            if (f[19].s.getPosition() == Vector2f(-100, -100)) { //kiem tra xem con vua trang khog, neu ko con thi luotchoi+1 -> ketthuc luot choi.
                luotChoi = 10;
                //chieuTuong.setPosition(-1000, -1000);
                endgame.setPosition(0, 0);
                printf("luot choi = %d (+ 1) do mat Vua trang\n", luotChoi);
            }
            else  if (click == 1) {
                chieuTuong.setPosition(-1000, -1000);
                bool isMove = false;
                for (int i = 16; i < 32; i++)
                {
                    if (f[i].s.getGlobalBounds().contains(pos.x, pos.y))
                    {
                        isMove = true;
                        n = i;
                        oldPos = f[n].s.getPosition();
                    }
                }
                if (!isMove) click = 0;
                else { PositiveMoving(n); count = positiveCount; positiveCount = 0; }
            }
            else if (click == 2) {
                int x = pos.x / size;   int y = pos.y / size;
                newPos = Vector2f(x * size, y * size);

                int gameOver = 0;
                int QuanCoDangchieuTuong;
                int checkXemCoQuanNaoDangChieuKo = 0;
                //chi di chuyen trong vung positiveMove
                for (int i = 0; i < count; i++) {
                    if (positiveMove[i] == newPos) {
                        move(n, oldPos, newPos);

                        //tim xem quan nao dang chieu vua 52 - vua hong
                        for (int kChieu = 0; kChieu < 32; kChieu++) {
                            PositiveMoving(kChieu); count = positiveCount; positiveCount = 0;
                            for (int i = 0; i < count; i++) {
                                if (positiveMove[i] == f[52].s.getPosition()) {
                                    QuanCoDangchieuTuong = kChieu;
                                    checkXemCoQuanNaoDangChieuKo = 52;
                                    break;
                                }
                            }
                        }

                        if (checkXemCoQuanNaoDangChieuKo == 52) {
                            PositiveMoving(QuanCoDangchieuTuong); count = positiveCount; positiveCount = 0;
                            for (int i = 0; i < count; i++) {
                                if (positiveMove[i] == f[52].s.getPosition()) {
                                    printf("chieu tuong vua hong\n");
                                    chieuTuong.setPosition(0, 0);

                                         //check cac nuoc di cua B cho tung quan co
                                    int hetCo = 0;
                                    int quanCoChieuDcKhiBdiChuyen = -1000;
                                    bool vuaDiChuyenTranhChieu = false;

                                    int kA = 0;
                                    int dem = 0;
                                    int demSoNuocDiCuaVua = 0;
                                    //check xem Vua co the tu di de tranh chieu tuong khong?
                                    //cac nuoc di cua quan den + trang
                                    for (int i = 0; i < 32; i++) {
                                        PositiveMoving(i);  count = positiveCount; positiveCount = 0;
                                        for (int j = 0; j < count; j++) {
                                            movablesA[kA] = positiveMove[j];
                                            kA++;
                                        }
                                    }

                                    //xem cac nuoc di cua vua co nam trong cac nuoc di cua phe A khong
                                    PositiveMoving(52);  count = positiveCount; positiveCount = 0;
                                    demSoNuocDiCuaVua = count;
                                    printf("vua co the di so nuoc = %d\n", count);

                                    for (int i = 0; i < count; i++) {
                                        for (int j = 0; j < kA; j++) {
                                            if (positiveMove[i] == movablesA[j] || positiveMove[i] == f[QuanCoDangchieuTuong].s.getPosition()) {
                                                dem++;
                                                //cong them vi tri cua quan co dang chieu tuong (vi trong mang dc di cua phe con lai khong co vi tri cua quan co nay)
                                                break;
                                            }
                                        }
                                    }
                                    printf("dem cac nuoc di cua vua ma  bi chieu = %d\n", dem);

                                    if (demSoNuocDiCuaVua == dem) {
                                        printf("demSoNuocDiCuaVua = %d\n", demSoNuocDiCuaVua);
                                        for (int iB = 32; iB < 64; iB++) {
                                            bool checkEndGame = true;
                                            PositiveMoving(iB);  count = positiveCount; positiveCount = 0;
                                            //nuoc co 1 quan cua B
                                            for (int i = 0; i < count; i++) {

                                                move(iB, f[iB].s.getPosition(), positiveMove[i]);
                                                //tat cac nuoc di cua A khi B di chuyen 1 quan co vs 1 vitri khac nhau
                                                for (int i = 0; i < 32; i++) {
                                                    PositiveMoving(i);  count = positiveCount; positiveCount = 0;
                                                    //so sanh tat ca cac nuoc di cua 1 quan A voi f[52].s.getPosition() 
                                                    //o day chi dang so sanh khi va chi khi vua dung yen 1 cho~
                                                    for (int i = 0; i < count; i++) {
                                                        if (positiveMove[i] == f[52].s.getPosition()) { //cho nay chua ddc logic chua dc vi la so sanh vua voi vi tri f[52]
                                                            checkEndGame = false;
                                                            break;
                                                        }
                                                    }
                                                }

                                                if (checkEndGame == true) {
                                                    hetCo = 1;
                                                }
                                                Undo();//phai di chuyen ve cho cu                                            
                                            }
                                        }

                                        if (hetCo == 0) {
                                            chieuTuong.setPosition(-1000, -1000);
                                            endgame.setPosition(0, 0);
                                            // luotChoi = 10;
                                            gameOver = 10;
                                        }
                                    }
                                    // }

                                }
                            }
                        }
                        //tim xem quan nao dang chieu vua 35 - vua xanh
                        for (int kChieu = 0; kChieu < 32; kChieu++) {
                            PositiveMoving(kChieu); count = positiveCount; positiveCount = 0;
                            for (int i = 0; i < count; i++) {
                                if (positiveMove[i] == f[35].s.getPosition()) {
                                    QuanCoDangchieuTuong = kChieu;
                                    checkXemCoQuanNaoDangChieuKo = 35;
                                    break;
                                }
                            }
                        }
                        //tim cac nuoc cua QuanCoDangchieuTuong de ve~ chieu tuong
                        if (checkXemCoQuanNaoDangChieuKo == 35) {
                            PositiveMoving(QuanCoDangchieuTuong); count = positiveCount; positiveCount = 0;
                            for (int i = 0; i < count; i++) {

                                if (positiveMove[i] == f[35].s.getPosition()) {
                                    printf("chieu tuong vua xanh\n");
                                    chieuTuong.setPosition(0, 0);

                                    //check cac nuoc di cua B cho tung quan co
                                    int hetCo = 0;
                                    int quanCoChieuDcKhiBdiChuyen = -1000;
                                    bool vuaDiChuyenTranhChieu = false;

                                    int kA = 0;
                                    int dem = 0;
                                    int demSoNuocDiCuaVua = 0;
                                    //check xem Vua co the tu di de tranh chieu tuong khong?
                                    //cac nuoc di cua quan den + trang
                                    for (int i = 0; i < 32; i++) {
                                        PositiveMoving(i);  count = positiveCount; positiveCount = 0;
                                        for (int j = 0; j < count; j++) {
                                            movablesA[kA] = positiveMove[j];
                                            kA++;
                                        }
                                    }

                                    //xem cac nuoc di cua vua co nam trong cac nuoc di cua phe A khong
                                    PositiveMoving(35);  count = positiveCount; positiveCount = 0;
                                    demSoNuocDiCuaVua = count;
                                    printf("vua co the di so nuoc = %d\n", count);

                                    for (int i = 0; i < count; i++) {
                                        for (int j = 0; j < kA; j++) {
                                            if (positiveMove[i] == movablesA[j] || positiveMove[i] == f[QuanCoDangchieuTuong].s.getPosition()) {
                                                dem++;
                                                //cong them vi tri cua quan co dang chieu tuong (vi trong mang dc di cua phe con lai khong co vi tri cua quan co nay)
                                                break;
                                            }
                                        }
                                    }
                                    printf("dem cac nuoc di cua vua ma  bi chieu = %d\n", dem);

                                    if (demSoNuocDiCuaVua == dem) {
                                        printf("demSoNuocDiCuaVua = %d\n", demSoNuocDiCuaVua);
                                        for (int iB = 32; iB < 64; iB++) {
                                            bool checkEndGame = true;
                                            PositiveMoving(iB);  count = positiveCount; positiveCount = 0;
                                            //nuoc co 1 quan cua B
                                            for (int i = 0; i < count; i++) {

                                                move(iB, f[iB].s.getPosition(), positiveMove[i]);
                                                //tat cac nuoc di cua A khi B di chuyen 1 quan co vs 1 vitri khac nhau
                                                for (int i = 0; i < 32; i++) {
                                                    PositiveMoving(i);  count = positiveCount; positiveCount = 0;
                                                    //so sanh tat ca cac nuoc di cua 1 quan A voi f[52].s.getPosition() 
                                                    //o day chi dang so sanh khi va chi khi vua dung yen 1 cho~
                                                    for (int i = 0; i < count; i++) {
                                                        if (positiveMove[i] == f[35].s.getPosition()) { //cho nay chua ddc logic chua dc vi la so sanh vua voi vi tri f[52]
                                                            checkEndGame = false;
                                                            break;
                                                        }
                                                    }
                                                }

                                                if (checkEndGame == true) {
                                                    hetCo = 1;
                                                }
                                                Undo();//phai di chuyen ve cho cu                                            
                                            }
                                        }

                                        if (hetCo == 0) {
                                            chieuTuong.setPosition(-1000, -1000);
                                            endgame.setPosition(0, 0);
                                            // luotChoi = 10;
                                            gameOver = 10;
                                        }
                                    }
                                }
                            }
                        }

                        


                        luotChoi = 4;
                    }
                }
                //kiem tra xem con vua hoongf + vua vua xanh ko, neu ko con thi endgame
                if (f[35].s.getPosition() == Vector2f(-100, -100) || f[52].s.getPosition() == Vector2f(-100, -100)) {
                    luotChoi = 10;
                    endgame.setPosition(0, 0);
                    printf("end game %d", luotChoi);
                }
                
                count = 0;
                click = 0;
                printf("luot choi %d\n", luotChoi);
               // printf("luot choi %d\n", luotChoi);
                 if (gameOver == 10) {
                    luotChoi = 10;
                    endgame.setPosition(0, 0);
                    printf("luotChoi %d\n", luotChoi);
                }
            }
        }
        ////lươt choi bằng 4 thì quân xanh được đi
        else if (luotChoi == 4) {
            if (f[35].s.getPosition() == Vector2f(-100, -100)) { //kiem tra xem con vua khog, neu ko con thi luotchoi+1 -> ketthuc luot choi.
                luotChoi = 10;
                chieuTuong.setPosition(-1000, -1000);
                endgame.setPosition(0, 0);
                printf("luot choi =%d (+ 1) do mat Vua Xanh", luotChoi);
            }
            else   if (click == 1) {
                chieuTuong.setPosition(-1000, -1000);
                bool isMove = false;
                for (int i = 32; i < 48; i++)
                {
                    if (f[i].s.getGlobalBounds().contains(pos.x, pos.y))
                    {
                        isMove = true;
                        n = i;
                        oldPos = f[n].s.getPosition();
                    }
                }
                if (!isMove) click = 0;
                else { PositiveMoving(n); count = positiveCount; positiveCount = 0; }
            }
            else if (click == 2) {
                int x = pos.x / size;   int y = pos.y / size;
                newPos = Vector2f(x * size, y * size);

                int gameOver = 0;
                int QuanCoDangchieuTuong;
                int checkXemCoQuanNaoDangChieuKo = 0;
                //chi di chuyen trong vung positiveMove
                for (int i = 0; i < count; i++) {
                    if (positiveMove[i] == newPos) {
                        move(n, oldPos, newPos);

                        //tim xem quan nao dang chieu vua 3 - vua den
                        for (int kChieu = 32; kChieu < 64; kChieu++) {
                            PositiveMoving(kChieu); count = positiveCount; positiveCount = 0;
                            for (int i = 0; i < count; i++) {
                                if (positiveMove[i] == f[3].s.getPosition()) {
                                    QuanCoDangchieuTuong = kChieu;
                                    checkXemCoQuanNaoDangChieuKo = 3;
                                    break;
                                }
                            }
                        }

                        //tim cac nuoc cua QuanCoDangchieuTuong de ve~ chieu tuong
                        if (checkXemCoQuanNaoDangChieuKo == 3) {
                            PositiveMoving(QuanCoDangchieuTuong); count = positiveCount; positiveCount = 0;
                            for (int i = 0; i < count; i++) {
                                if (positiveMove[i] == f[3].s.getPosition()) {
                                    printf("chieu tuong vua den\n");
                                    chieuTuong.setPosition(0, 0);

                                    int hetCo = 0;
                                    int quanCoChieuDcKhiBdiChuyen = -1000;
                                    bool vuaDiChuyenTranhChieu = false;

                                    int kA = 0;
                                    int dem = 0;
                                    int demSoNuocDiCuaVua = 0;
                                    //check xem Vua co the tu di de tranh chieu tuong khong?
                                    //cac nuoc di cua quan hong + xanh
                                    for (int i = 32; i < 64; i++) {
                                        PositiveMoving(i);  count = positiveCount; positiveCount = 0;
                                        for (int j = 0; j < count; j++) {
                                            movablesA[kA] = positiveMove[j];
                                            kA++;
                                        }
                                    }

                                    //xem cac nuoc di cua vua co nam trong cac nuoc di cua phe A khong
                                    PositiveMoving(3);  count = positiveCount; positiveCount = 0;
                                    demSoNuocDiCuaVua = count;
                                    printf("vua co the di so nuoc = %d\n", count);

                                    for (int i = 0; i < count; i++) {
                                        for (int j = 0; j < kA; j++) {
                                            if (positiveMove[i] == movablesA[j] || positiveMove[i] == f[QuanCoDangchieuTuong].s.getPosition()) {
                                                dem++;
                                                //cong them vi tri cua quan co dang chieu tuong (vi trong mang dc di cua phe con lai khong co vi tri cua quan co nay)
                                                break;
                                            }
                                        }
                                    }
                                    printf("dem cac nuoc di cua vua ma  bi chieu = %d\n", dem);

                                    if (demSoNuocDiCuaVua == dem) {
                                        printf("demSoNuocDiCuaVua = %d\n", demSoNuocDiCuaVua);
                                        for (int iB = 0; iB < 32; iB++) {
                                            bool checkEndGame = true;
                                            PositiveMoving(iB);  count = positiveCount; positiveCount = 0;
                                            //nuoc co 1 quan cua B
                                            for (int i = 0; i < count; i++) {

                                                move(iB, f[iB].s.getPosition(), positiveMove[i]);
                                                //tat cac nuoc di cua A khi B di chuyen 1 quan co vs 1 vitri khac nhau
                                                for (int i = 32; i < 64; i++) {
                                                    PositiveMoving(i);  count = positiveCount; positiveCount = 0;
                                                    //so sanh tat ca cac nuoc di cua 1 quan A voi f[3].s.getPosition() 
                                                    //o day chi dang so sanh khi va chi khi vua dung yen 1 cho~
                                                    for (int i = 0; i < count; i++) {
                                                        if (positiveMove[i] == f[3].s.getPosition()) { //cho nay chua ddc logic chua dc vi la so sanh vua voi vi tri f[3]
                                                            checkEndGame = false;
                                                            break;
                                                        }
                                                    }
                                                }

                                                if (checkEndGame == true) {
                                                    hetCo = 1;
                                                }
                                                Undo();//phai di chuyen ve cho cu                                            
                                            }
                                        }

                                        if (hetCo == 0) {
                                            chieuTuong.setPosition(-1000, -1000);
                                            endgame.setPosition(0, 0);
                                            // luotChoi = 10;
                                            gameOver = 10;
                                        }
                                    }

                                }
                            }
                        }
                        //tim xem quan nao dang chieu vua 19 - vua trang
                        for (int kChieu = 32; kChieu < 64; kChieu++) {
                            PositiveMoving(kChieu); count = positiveCount; positiveCount = 0;
                            for (int i = 0; i < count; i++) {
                                if (positiveMove[i] == f[19].s.getPosition()) {
                                    QuanCoDangchieuTuong = kChieu;
                                    checkXemCoQuanNaoDangChieuKo = 19;
                                    break;
                                }
                            }
                        }

                        //tim cac nuoc cua QuanCoDangchieuTuong de ve~ chieu tuong
                        if (checkXemCoQuanNaoDangChieuKo == 19) {
                            PositiveMoving(QuanCoDangchieuTuong); count = positiveCount; positiveCount = 0;
                            for (int i = 0; i < count; i++) {
                                if (positiveMove[i] == f[19].s.getPosition()) {
                                    printf("chieu tuong vua den\n");
                                    chieuTuong.setPosition(0, 0);

                                    int hetCo = 0;
                                    int quanCoChieuDcKhiBdiChuyen = -1000;
                                    bool vuaDiChuyenTranhChieu = false;

                                    int kA = 0;
                                    int dem = 0;
                                    int demSoNuocDiCuaVua = 0;
                                    //check xem Vua co the tu di de tranh chieu tuong khong?
                                    //cac nuoc di cua quan hong + xanh
                                    for (int i = 32; i < 64; i++) {
                                        PositiveMoving(i);  count = positiveCount; positiveCount = 0;
                                        for (int j = 0; j < count; j++) {
                                            movablesA[kA] = positiveMove[j];
                                            kA++;
                                        }
                                    }

                                    //xem cac nuoc di cua vua co nam trong cac nuoc di cua phe A khong
                                    PositiveMoving(19);  count = positiveCount; positiveCount = 0;
                                    demSoNuocDiCuaVua = count;
                                    printf("vua co the di so nuoc = %d\n", count);

                                    for (int i = 0; i < count; i++) {
                                        for (int j = 0; j < kA; j++) {
                                            if (positiveMove[i] == movablesA[j] || positiveMove[i] == f[QuanCoDangchieuTuong].s.getPosition()) {
                                                dem++;
                                                //cong them vi tri cua quan co dang chieu tuong (vi trong mang dc di cua phe con lai khong co vi tri cua quan co nay)
                                                break;
                                            }
                                        }
                                    }
                                    printf("dem cac nuoc di cua vua ma  bi chieu = %d\n", dem);

                                    if (demSoNuocDiCuaVua == dem) {
                                        printf("demSoNuocDiCuaVua = %d\n", demSoNuocDiCuaVua);
                                        for (int iB = 0; iB < 32; iB++) {
                                            bool checkEndGame = true;
                                            PositiveMoving(iB);  count = positiveCount; positiveCount = 0;
                                            //nuoc co 1 quan cua B
                                            for (int i = 0; i < count; i++) {

                                                move(iB, f[iB].s.getPosition(), positiveMove[i]);
                                                //tat cac nuoc di cua A khi B di chuyen 1 quan co vs 1 vitri khac nhau
                                                for (int i = 32; i < 64; i++) {
                                                    PositiveMoving(i);  count = positiveCount; positiveCount = 0;
                                                    //so sanh tat ca cac nuoc di cua 1 quan A voi f[3].s.getPosition() 
                                                    //o day chi dang so sanh khi va chi khi vua dung yen 1 cho~
                                                    for (int i = 0; i < count; i++) {
                                                        if (positiveMove[i] == f[19].s.getPosition()) { //cho nay chua ddc logic chua dc vi la so sanh vua voi vi tri f[3]
                                                            checkEndGame = false;
                                                            break;
                                                        }
                                                    }
                                                }

                                                if (checkEndGame == true) {
                                                    hetCo = 1;
                                                }
                                                Undo();//phai di chuyen ve cho cu                                            
                                            }
                                        }

                                        if (hetCo == 0) {
                                            chieuTuong.setPosition(-1000, -1000);
                                            endgame.setPosition(0, 0);
                                            // luotChoi = 10;
                                            gameOver = 10;
                                        }
                                    }

                                }
                            }
                        }

                        luotChoi = 1;
                    }
                }
                //kiem tra xem con vua den + vua trang ko, neu ko con thi endgame
                if (f[3].s.getPosition() == Vector2f(-100, -100) || f[19].s.getPosition() == Vector2f(-100, -100)) {
                    luotChoi = 10;
                    endgame.setPosition(0, 0);

                }
                
                count = 0;
                click = 0;
                printf("luot choi %d\n", luotChoi);
               // printf("scoreBlue = %d", scoreBlue);
                if (gameOver == 10) {
                    luotChoi = 10;
                    endgame.setPosition(0, 0);
                    printf("luotChoi %d\n", luotChoi);
                }

            }
        }

        ////// draw  ///////
        window.clear();
        window.draw(sBoard);
        //gợi ý nước cờ
        // thieu count!!!
     //   for (int i = 0; i < count; i++) {
    //        goiY.setPosition(positiveMove[i]);
    //        window.draw(goiY);
    //    }
        
        //de y ham vẽ (nên đaawt trong hay ngoài hàm)
        for (k = 0; k < 64; k++) {
            window.draw(f[k].s);
        }
        window.draw(chieuTuong);
        window.draw(endgame);
        window.display();

    }
}
