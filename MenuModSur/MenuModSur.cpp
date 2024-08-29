// MenuModSur.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include<string.h>
#include<conio.h>
#include<windows.h>
#include<time.h>


using namespace std;

HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
COORD CursorPosition;
int i;
int gs = 1;//first ball set
int UP_EDGE = 1;
int DOWN_EDGE = 27;
int RIGHT_EDGE = 82;
int LEFT_EDGE = 2;
char prtx = 442;
char k;
void gotoxy(int x, int y)
{
    CursorPosition.X = x;
    CursorPosition.Y = y;
    SetConsoleCursorPosition(console, CursorPosition);
}


void setcursor(bool visible, DWORD size)
{
    if (size == 0)
    {
        size = 20;
    }
    CONSOLE_CURSOR_INFO IdCursor;
    IdCursor.bVisible = visible;
    IdCursor.dwSize = size;
    SetConsoleCursorInfo(console, &IdCursor);
}



void printBorder()
{
    SetConsoleTextAttribute(console, 255);
    for (i = 2; i <= RIGHT_EDGE; i++) {
        gotoxy(i, 1);
        std::cout << '0';
        gotoxy(i, 27);
        std::cout << '0';
    }
    for (i = 2; i <= DOWN_EDGE; i++)
    {
        gotoxy(2, i);
        std::cout << 0;
        gotoxy(82, i);
        std::cout << 0;
    }
    SetConsoleTextAttribute(console, 15);
    

}

class ball
{
private:
    COORD positionBall;
    int direction;
    //ru from left to right and up 11=3 x++ y--
    //rd from left to right and down  10=2 x++ y++
    //lu from right to left and up 01=1 x-- y--
    //ld from right to left end down  00=0 x-- y++
    //1-r, 0-l, 1-u, 0-d
    // neutral direction = 4
public:
    ball();
    void setBall();

    int getBallCordX() { return positionBall.X; }
    int getBallCordY() { return positionBall.Y; }
    ball& setBallcoordX(int x) { positionBall.X = x; return *this; }
    ball& setBallcoordY(int y) { positionBall.Y = y; return *this; }
    int getBallDirection() { return direction; }
    ball& setBallDirection(int d) { direction = d; return *this; }
};


ball::ball()
{
    positionBall.X = 0;
    positionBall.Y = 0;
    direction = 4;
}



void ball::setBall()
{
    if (gs == 1)
    {
        setBallcoordX(42);
        setBallcoordY(14);
        direction = rand() % 4;
        gs = 0;
        gotoxy(getBallCordX(), getBallCordY());
        SetConsoleTextAttribute(console, 255);
        std::cout << "0";
        SetConsoleTextAttribute(console, 15);
    }
    if (gs == 0)
    {
        int l = getBallCordX();//which player missed a goal elft half or right 
        if (l < 42)// left player missed
        {
            setBallcoordX(5 + rand() % 36);
            setBallcoordY(3 + rand() % 21);
            int k = rand() % 2;
            if (k == 0) { k = 2; }
            if (k == 1) { k = 3; }
            setBallDirection(k);
        }
        if (l > 42)//right player missed
        {
            setBallcoordX(43 + rand() % 36);
            setBallcoordY(3 + rand() % 21);
            int k = rand() % 2;
            setBallDirection(k);
        }
    }

}




class Pads
{
private:
    COORD LupEnd;
    COORD LdownEnd;
    COORD RupEnd;
    COORD RdownEnd;
public:
    Pads();

    void move();

    int getLUpEndX() { return LupEnd.X; }
    int getLUpEndY() { return LupEnd.Y; }
    int getLDownEndX() { return LdownEnd.X; }
    int getLDownEndY() { return LdownEnd.Y; }

    Pads& setLUpEndX(int l) { LupEnd.X = l; return *this; }
    Pads& setLUpEndY(int l) { LupEnd.Y = l; return *this; }
    Pads& setLDownEndX(int l) { LdownEnd.X = l; return *this; }
    Pads& setLDownEndY(int l) { LdownEnd.Y = l; return *this; }

    int getRUpEndX() { return RupEnd.X; }
    int getRUpEndY() { return RupEnd.Y; }
    int getRDownEndX() { return RdownEnd.X; }
    int getRDownEndY() { return RdownEnd.Y; }

    Pads& setRUpEndX(int l) { RupEnd.X = l; return *this; }
    Pads& setRUpEndY(int l) { RupEnd.Y = l; return *this; }
    Pads& setRDownEndX(int l) { RdownEnd.X = l; return *this; }
    Pads& setRDownEndY(int l) { RdownEnd.Y = l; return *this; }

};

Pads::Pads()
{
    LupEnd.X = LEFT_EDGE + 1;
    LupEnd.Y = 12;
    LdownEnd.X = LEFT_EDGE + 1;
    LdownEnd.Y = 16;
    RupEnd.X = RIGHT_EDGE - 1;
    RupEnd.Y = 12;
    RdownEnd.X = RIGHT_EDGE - 1;
    RdownEnd.Y = 16;
}



void Pads::move()
{
    if (GetAsyncKeyState(0x57) && GetAsyncKeyState(VK_UP))// /\ /\  //
    {
        if (LupEnd.Y > (UP_EDGE + 1))
        {
            gotoxy(LupEnd.X, LupEnd.Y - 1);
            SetConsoleTextAttribute(console, 160);
            std::cout << prtx;
            SetConsoleTextAttribute(console, 15);
            gotoxy(LupEnd.X, LdownEnd.Y);
            std::cout << ' ';
            LupEnd.Y--;
            LdownEnd.Y--;
        }
        if (RupEnd.Y > (UP_EDGE + 1))
        {
            gotoxy(RupEnd.X, RupEnd.Y - 1);
            SetConsoleTextAttribute(console, 192);
            std::cout << prtx;
            SetConsoleTextAttribute(console, 15);
            gotoxy(RupEnd.X, RdownEnd.Y);
            std::cout << ' ';
            RupEnd.Y--;
            RdownEnd.Y--;
        }
    }
    if (GetAsyncKeyState(0x53) && GetAsyncKeyState(VK_DOWN)) // \/ \/ //
    {
        if (LdownEnd.Y < (DOWN_EDGE - 1))
        {
            gotoxy(LdownEnd.X, LdownEnd.Y + 1);
            SetConsoleTextAttribute(console, 160);
            std::cout << prtx;
            SetConsoleTextAttribute(console, 15);
            gotoxy(LdownEnd.X, LupEnd.Y);
            std::cout << ' ';
            LupEnd.Y++;
            LdownEnd.Y++;
        }
        if (RdownEnd.Y < (DOWN_EDGE - 1))
        {
            gotoxy(RupEnd.X, RdownEnd.Y + 1);
            SetConsoleTextAttribute(console, 192);
            std::cout << prtx;
            SetConsoleTextAttribute(console, 15);
            gotoxy(RupEnd.X, RupEnd.Y);
            std::cout << ' ';
            RupEnd.Y++;
            RdownEnd.Y++;
        }
    }
    if (GetAsyncKeyState(0x57) && GetAsyncKeyState(VK_DOWN))// /\ \/ //
    {
        if (LupEnd.Y > (UP_EDGE + 1))
        {
            gotoxy(LupEnd.X, LupEnd.Y - 1);
            SetConsoleTextAttribute(console, 160);
            std::cout << prtx;
            SetConsoleTextAttribute(console, 15);
            gotoxy(LupEnd.X, LdownEnd.Y);
            std::cout << ' ';
            LupEnd.Y--;
            LdownEnd.Y--;
        }
        if (RdownEnd.Y < (DOWN_EDGE - 1))
        {
            gotoxy(RupEnd.X, RdownEnd.Y + 1);
            SetConsoleTextAttribute(console, 192);
            std::cout << prtx;
            SetConsoleTextAttribute(console, 15);
            gotoxy(RupEnd.X, RupEnd.Y);
            std::cout << ' ';
            RupEnd.Y++;
            RdownEnd.Y++;
        }
    }
    if (GetAsyncKeyState(0x53) && GetAsyncKeyState(VK_UP))//  \/ /\ //
    {
        if (LdownEnd.Y < (DOWN_EDGE - 1))
        {
            gotoxy(LdownEnd.X, LdownEnd.Y + 1);
            SetConsoleTextAttribute(console, 160);
            std::cout << prtx;
            SetConsoleTextAttribute(console, 15);
            gotoxy(LdownEnd.X, LupEnd.Y);
            std::cout << ' ';
            LupEnd.Y++;
            LdownEnd.Y++;
        }
        if (RupEnd.Y > (UP_EDGE + 1))
        {
            gotoxy(RupEnd.X, RupEnd.Y - 1);
            SetConsoleTextAttribute(console, 192);
            std::cout << prtx;
            SetConsoleTextAttribute(console, 15);
            gotoxy(RupEnd.X, RdownEnd.Y);
            std::cout << ' ';
            RupEnd.Y--;
            RdownEnd.Y--;
        }
    }

    if (GetAsyncKeyState(0x57) && (!(GetAsyncKeyState(VK_DOWN) && (!(GetAsyncKeyState(VK_UP))))))// /\ * //
    {
        if (LupEnd.Y > (UP_EDGE + 1))
        {
            gotoxy(LupEnd.X, LupEnd.Y - 1);
            SetConsoleTextAttribute(console, 160);
            std::cout << prtx;
            SetConsoleTextAttribute(console, 15);
            gotoxy(LupEnd.X, LdownEnd.Y);
            std::cout << ' ';
            LupEnd.Y--;
            LdownEnd.Y--;
        }
    }
    if (GetAsyncKeyState(0x53) && (!(GetAsyncKeyState(VK_DOWN) && (!(GetAsyncKeyState(VK_UP))))))// \/ *//
    {
        if (LdownEnd.Y < (DOWN_EDGE - 1))
        {
            gotoxy(LdownEnd.X, LdownEnd.Y + 1);
            SetConsoleTextAttribute(console, 160);
            std::cout << prtx;
            SetConsoleTextAttribute(console, 15);
            gotoxy(LdownEnd.X, LupEnd.Y);
            std::cout << ' ';
            LupEnd.Y++;
            LdownEnd.Y++;
        }
    }
    if (GetAsyncKeyState(VK_UP) && (!(GetAsyncKeyState(0x57) && (!(GetAsyncKeyState(0x53))))))// * /\ //
    {
        if (RupEnd.Y > (UP_EDGE + 1))
        {
            gotoxy(RupEnd.X, RupEnd.Y - 1);
            SetConsoleTextAttribute(console, 192);
            std::cout << prtx;
            SetConsoleTextAttribute(console, 15);
            gotoxy(RupEnd.X, RdownEnd.Y);
            std::cout << ' ';
            RupEnd.Y--;
            RdownEnd.Y--;
        }
    }
    if (GetAsyncKeyState(VK_DOWN) && (!(GetAsyncKeyState(0x57) && (!(GetAsyncKeyState(0x53))))))// * \/ //
    {
        if (RdownEnd.Y < (DOWN_EDGE - 1))
        {
            gotoxy(RupEnd.X, RdownEnd.Y + 1);
            SetConsoleTextAttribute(console, 192);
            std::cout << prtx;
            SetConsoleTextAttribute(console, 15);
            gotoxy(RupEnd.X, RupEnd.Y);
            std::cout << ' ';
            RupEnd.Y++;
            RdownEnd.Y++;
        }
    }

    for (i = LupEnd.Y; i <= LdownEnd.Y; i++)
    {
        gotoxy(LupEnd.X, i);
        SetConsoleTextAttribute(console, 160);
        std::cout << prtx;
        SetConsoleTextAttribute(console, 15);
    }
    for (i = RupEnd.Y; i <= RdownEnd.Y; i++)
    {
        gotoxy(RupEnd.X, i);
        SetConsoleTextAttribute(console, 192);
        std::cout << prtx;
        SetConsoleTextAttribute(console, 15);
    }

}




int dvpause = 0;

void gameplay(Pads q, ball b, int hs)
{
    char replay = '0';
    int indr = 2;
    int rightscore = 0;
    int leftscore = 0;
    for (i = 12; i <= 16; i++)
    {
        gotoxy(LEFT_EDGE + 1, i);
        SetConsoleTextAttribute(console, 160);
        std::cout << prtx;
        SetConsoleTextAttribute(console, 15);
    }
    for (i = 12; i <= 16; i++)
    {
        gotoxy(RIGHT_EDGE - 1, i);
        SetConsoleTextAttribute(console, 192);
        std::cout << prtx;
        SetConsoleTextAttribute(console, 15);
    }
    b.setBall();
    while (true)
    {
        int x = b.getBallCordX();
        int y = b.getBallCordY();
        int dr = b.getBallDirection();
        int x1 = x;
        int y1 = y;
        int dr1 = dr;
        int pluy = q.getLUpEndY();
        int pldy = q.getLDownEndY();
        int pruy = q.getRUpEndY();
        int prdy = q.getRDownEndY();
        q.move();
        setcursor(0, 0);
        int pause = 0;
        int esc = 0;
        int cp = 1;     //current position

        gotoxy(13, 29);
        SetConsoleTextAttribute(console, 10);
        std::cout << "Score: " << leftscore;
        SetConsoleTextAttribute(console, 15);
        gotoxy(55, 29);
        SetConsoleTextAttribute(console, 12);
        std::cout << "Score: " << rightscore;
        SetConsoleTextAttribute(console, 15);
        if ((GetAsyncKeyState(VK_SPACE)) && (dvpause == 0))
        {
            pause = 1;
        }
        if (GetAsyncKeyState(VK_SPACE) && (dvpause == 1))
        {
            dvpause = 0;
        }
        if (pause == 1) {
            gotoxy(x, y);
            std::cout << ' ';
            char contin='0';
            gotoxy(34, 14);
            std::cout << ">>";
            while (true)
            {
                gotoxy(36, 14);
                std::cout << "CONTINUE";
                gotoxy(36, 16);
                std::cout << "QUIT";
                

                contin = _getch();
                if (((contin == 80)||(contin == 'w')) && (cp == 1))
                {
                    gotoxy(34, 14);
                    SetConsoleTextAttribute(console, 0);
                    std::cout << ">>";
                    SetConsoleTextAttribute(console, 15);
                    gotoxy(34, 16);
                    std::cout << ">>";
                    cp = 2;
                }
                if (((contin == 72)||(contin == 's')) && (cp == 2))
                {
                    gotoxy(34, 16);
                    SetConsoleTextAttribute(console, 0);
                    std::cout << ">>";
                    SetConsoleTextAttribute(console, 15);
                    gotoxy(34, 14);
                    std::cout << ">>";
                    cp = 1;
                }
                if ((contin==13)&&(cp==1)) 
                {
                    gotoxy(34, 14);
                    SetConsoleTextAttribute(console, 0);
                    std::cout << ">>CONTINUE";
                    gotoxy(36, 16);
                    std::cout << "QUIT";
                    gotoxy(x, y);
                    SetConsoleTextAttribute(console, 255);
                    std::cout << "0";
                    SetConsoleTextAttribute(console, 15);
                    pause = 0;
                    break;
                }
                if ((contin == 13) && (cp == 2))
                {
                    esc = 1;
                    break;
                   
                }
                if (contin==' ')
                {
                    dvpause = 1;
                }
            }
        }

        

        if (esc == 1)
        {
            break;
        }

        if ((x > LEFT_EDGE + 2) && (x < RIGHT_EDGE - 2) && (y > UP_EDGE + 1) && (y < DOWN_EDGE - 1))
        {
            if (dr == 3)
            {
                x1++;
                y1--;
            }
            if (dr == 2)
            {
                x1++;
                y1++;
            }
            if (dr == 1)
            {
                x1--;
                y1--;
            }
            if (dr == 0)
            {
                x1--;
                y1++;
            }
        }
        if ((y == UP_EDGE + 1) && (x == LEFT_EDGE + 2))
        {
            if ((y >= pluy) && (y <= pldy))
            {
                if (dr == 1)
                {
                    dr = 2;
                    x1++;
                    y1++;
                }
            }
            else
            {
                if (dr == 3)
                {
                    dr = 2;
                    x1++;
                    y1++;
                }
                if (dr == 1)
                {
                    dr = 0;
                    x1--;
                    y1++;
                }
            }
        }
        if ((y == UP_EDGE + 1) && (x == RIGHT_EDGE - 2))
        {
            if ((y >= pruy) && (y <= prdy))
            {
                if (dr == 3)
                {
                    dr = 0;
                    x1--;
                    y1++;
                }
            }
            else
            {
                if (dr == 3)
                {
                    dr = 2;
                    x1++;
                    y1++;
                }
                if (dr == 1)
                {
                    dr = 0;
                    x1--;
                    y1++;
                }
            }
        }
        if ((y == UP_EDGE + 1) && (!(x == LEFT_EDGE + 2)) && (!(x == RIGHT_EDGE - 2)))
        {
            if (dr == 3)
            {
                dr = 2;
                x1++;
                y1++;
            }
            if (dr == 1)
            {
                dr = 0;
                x1--;
                y1++;
            }
        }


        // // // //

        if ((y == DOWN_EDGE - 1) && (x == LEFT_EDGE + 2))
        {
            if ((y >= pluy) && (y <= pldy))
            {
                if (dr == 0)
                {
                    dr = 3;
                    x1++;
                    y1--;
                }
            }
            else
            {
                if (dr == 2)
                {
                    dr = 3;
                    x1++;
                    y1--;
                }
                if (dr == 0)
                {
                    dr = 1;
                    x1--;
                    y1--;
                }
            }
        }
        if ((y == DOWN_EDGE - 1) && (x == RIGHT_EDGE - 2))
        {
            if ((y >= pruy) && (y <= prdy))
            {
                if (dr == 2)
                {
                    dr = 1;
                    x1--;
                    y1--;
                }
            }
            else
            {
                if (dr == 2)
                {
                    dr = 3;
                    x1++;
                    y1--;
                }
                if (dr == 0)
                {
                    dr = 1;
                    x1--;
                    y1--;
                }
            }
        }
        if ((y == DOWN_EDGE - 1) && (!(x == LEFT_EDGE + 2)) && (!(x == RIGHT_EDGE - 2)))
        {
            if (dr == 2)
            {
                dr = 3;
                x1++;
                y1--;
            }
            if (dr == 0)
            {
                dr = 1;
                x1--;
                y1--;
            }
        }

        // // // //

        if ((x == LEFT_EDGE + 2) && (y > UP_EDGE + 1) && (y < DOWN_EDGE - 1))
        {
            if ((y >= pluy) && (y <= pldy))
            {
                if (dr == 1)
                {
                    dr = 3;
                    x1++;
                    y1--;
                }
                if (dr == 0)
                {
                    dr = 2;
                    x1++;
                    y1++;
                }
            }
            else
            {
                if (dr == 1)
                {
                    x1--;
                    y1--;
                }
                if (dr == 0)
                {
                    x1--;
                    y1++;
                }
            }

        }

        // // // //

        if ((x == RIGHT_EDGE - 2) && (y > UP_EDGE + 1) && (y < DOWN_EDGE - 1))
        {
            if ((y >= pruy) && (y <= prdy))
            {
                if (dr == 3)
                {
                    dr = 1;
                    x1--;
                    y1--;
                }
                if (dr == 2)
                {
                    dr = 0;
                    x1--;
                    y1++;
                }
            }
            else
            {
                if (dr == 3)
                {
                    x1++;
                    y1--;
                }
                if (dr == 2)
                {
                    x1++;
                    y1++;
                }
            }
        }

        // // // //
        gotoxy(x1, y1);
        SetConsoleTextAttribute(console, 255);
        std::cout << "0";
        SetConsoleTextAttribute(console, 15);
        gotoxy(x, y);
        std::cout << ' ';
        b.setBallcoordX(x1);
        b.setBallcoordY(y1);
        b.setBallDirection(dr);
        Sleep(hs);

        if ((x == LEFT_EDGE + 1) && (rightscore < 11))
        {
            rightscore++;
            b.setBall();
        }
        if ((x == LEFT_EDGE + 1) && (rightscore == 11))
        {
            
            gotoxy(55, 29);
            SetConsoleTextAttribute(console, 12);
            std::cout << "Score: " << rightscore;
            SetConsoleTextAttribute(console, 15);
            while (true)
            {


                gotoxy(x, y);
                std::cout << ' ';
                gotoxy(25, 14);
                std::cout << "Right player wins";
                gotoxy(25, 16);
                std::cout << "if you want to replay press r";
                gotoxy(25, 18);
                std::cout << "to go back to menu press esc";
                k = _getch();
                if (k==27)
                {
                    indr = 0;
                    break;
                }
                if (GetAsyncKeyState(0x52))
                {
                    indr = 1;
                    break;
                }
            }
            if (indr == 0)
            {
                indr = 2;
                rightscore = 0;
                leftscore = 0;
                break;
            }
            if (indr == 1)
            {
                indr = 2;
                gs = 1;
                rightscore = 0;
                leftscore = 0;
                gotoxy(25, 16);
                SetConsoleTextAttribute(console, 0);
                std::cout << "if you want to replay press r";
                gotoxy(25, 14);
                std::cout << "Right player wins";
                gotoxy(25, 18);
                std::cout << "to go back to menu press esc";
                gotoxy(13, 29);
                std::cout << "Score: " << "11";
                gotoxy(55, 29);
                std::cout << "Score: " << "11";
                SetConsoleTextAttribute(console, 15);
                b.setBall();
                continue;
            }
        }
        if ((x == RIGHT_EDGE - 1) && (leftscore < 11))
        {
            leftscore++;
            b.setBall();
        }
        if ((x == RIGHT_EDGE - 1) && (leftscore == 11))
        {
            
            gotoxy(13, 29);
            SetConsoleTextAttribute(console, 10);
            std::cout << "Score: " << leftscore;
            SetConsoleTextAttribute(console, 15);
            while (true)
            {

                
                gotoxy(x, y);
                std::cout << ' ';
                gotoxy(25, 14);
                std::cout << "Left player wins";
                gotoxy(25, 16);
                std::cout << "if you want to replay press r";
                gotoxy(25, 18);
                std::cout << "to go back to menu press esc";
                k = _getch();
                if (k==27)
                {
                    indr = 0;
                    break;
                }
                if (GetAsyncKeyState(0x52))
                {
                    indr = 1;
                    break;
                }
            }
            if (indr == 0)
            {
                indr = 2;
                rightscore = 0;
                leftscore = 0;
                break;
            }
            if (indr == 1)
            {
                indr = 2;
                rightscore = 0;
                leftscore = 0;
                gs = 1;
                gotoxy(25, 16);
                SetConsoleTextAttribute(console, 0);
                std::cout << "if you want to replay press r";
                gotoxy(25, 14);
                std::cout << "Left player wins";
                gotoxy(25, 18);
                std::cout << "to go back to menu press esc";
                gotoxy(13,29);
                std::cout << "Score: " << "11";
                gotoxy(55, 29);
                std::cout << "Score: " << "11";
                SetConsoleTextAttribute(console, 15);
                b.setBall();
                continue;
            }
        }
    }
}


int speedsettings(int s) 
{
    int s1;
    char inc;
    s1 = s;
    int s2;
    system("cls");
    while (true)
    {
        gotoxy(30, 8);
        cout << "SETTINGS";
        gotoxy(28, 9);
        cout << "------------";
        gotoxy(20, 11);
        std::cout << "press up arrow or w to insrease speed";
        gotoxy(20, 13);
        std::cout << "press down arrow or s to decrease speed";
        gotoxy(20, 15);
        std::cout << "press esc to go back to menu or enter to confirm your choice";
        gotoxy(34, 17);
        std::cout << s;
        inc = _getch();
        if ((GetAsyncKeyState(0x57)||(inc==72))&&(s<30))
        {
            
            gotoxy(34, 17);
            SetConsoleTextAttribute(console, 0);
            std::cout << s;
            SetConsoleTextAttribute(console, 15);
            
            s++;
        }
        if ((GetAsyncKeyState(0x53) || (inc == 80))&&(s>0))
        {
            
            gotoxy(34, 17);
            SetConsoleTextAttribute(console, 0);
            std::cout << s;
            SetConsoleTextAttribute(console, 15);
            
            s--;
        }
        if (inc == 27) 
        {
            s2 = s1;
            s = s1;
            break;
        }
        if (inc == 13)
        {
            s2 = s;
            break;
        }
    }
     
    return s2;
}



void htpwindow()
{
    while (true)
    {
        char co;
        system("cls");
        gotoxy(4, 3);
        cout << "INSTRUCTIONS";
        gotoxy(4, 4);
        cout << "-------------";
        gotoxy(4, 5);
        cout << "Press W or S to move left pad";
        gotoxy(4, 7);
        cout << "Press Up Arrow or Down Arrow to move right pad";
        gotoxy(4, 9);
        cout << "Press space bar to pause the game";
        gotoxy(4, 11);
        cout << "After pressing space, use W/Up Arrow and S/Down Arrow to choose ";
        gotoxy(4, 12);
        cout << "quit the game or continue. Press enter to confirm choice";
        gotoxy(4, 16);
        std::cout << "Press esc to go back to menu";
        gotoxy(4, 18);
        std::cout << "Choose settings in menu to change game speed";
        co = _getche();
        if (co == 27) { break; }
    }
}



int main()
{
    srand(time(NULL));
    printBorder();
    setcursor(0, 0);
    Pads one;
    ball two;
    two.setBall();
    int speed = 0;
    int speed1 = 50;
   
    while (true)
    {


        system("cls");
        gotoxy(34, 4);
        std::cout << "PING PONG";
        for (i = 8; i <= 73; i++)
        {
            gotoxy(i, 6);
            std::cout << '-';
        }
        gotoxy(34, 10);
        std::cout << "1) HOW TO PLAY";
        gotoxy(34, 12);
        std::cout << "2) PLAY THE GAME";
        gotoxy(34, 14);
        std::cout << "3) SETTINGS";
        gotoxy(34, 16);
        std::cout << "4) EXIT";
        gotoxy(24, 18);
        std::cout << "Press number before paragraph to choose it";
        char op = _getch();
        if (op == '2')
        {
            system("cls");
            printBorder();
            gameplay(one, two, speed1);

        }
        if (op == '1')
        {
            htpwindow();
        }
        if (op == '3') 
        {
            speed1=speedsettings(speed);
            speed = speed1;
            speed1 = 50 - speed1;
        }
        if ((op == '4'))
        {
            system("cls");
            exit(0);
        }

    }


    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
