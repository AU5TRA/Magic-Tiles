#include "iGraphics.h"
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<windows.h>
#include"mmsystem.h"

#define reset(k) k=0;
#define scrnwidth 1200
#define scrnheight 1000
#define homepage -1
#define level 0
#define scorelist 1
#define gameplay 2
#define instructions 3
#define nickname 4
#define pause 5
#define credits 6
#define tile_no 30


int GenerateRandom(int lower, int upper);
void sound_on();
int score=0, tiles_count=0, wrong_key=0, points, t, number, speed, fy, t1, t2, t3, len;
int dx=GenerateRandom(1, 2), dy=scrnheight, ex=GenerateRandom(3, 4), ey=scrnheight, game_state=homepage;
bool musicON=true;
//char hs1[20], hs2[20], hs3[20], hs4[20], hs5[20];
char str1[100];
char hscores[5][30];

struct scores
{
    char name[20];
    int score;
} s[20];

struct player
{
    int score;
    char name[30];

} player;

void sorted()
{
    struct scores temp;
    FILE *fp;
    int i=0,l,j;
    char ch;

    fp=fopen("Highscores.txt","r");

    while(!feof(fp))
    {
        fscanf(fp,"%s %d",s[i].name,&s[i].score);
        ch=fgetc(fp);
        i++;
    }

    l=i;

    for(i=1; i<l; i++)
    {
        for(j=0; j<l-i; j++)
        {
            if(s[j+1].score>s[j].score)
            {
                temp=s[j];
                s[j]=s[j+1];
                s[j+1]=temp;
            }
        }
    }

    fclose(fp);

    fp=fopen("sortedscore.txt","w");

    for(i=0; i<l; i++)
    {
        fprintf(fp,"%s %d\n",s[i].name,s[i].score);
    }

    fclose(fp);
    //printf("\n The file is sorted successfully and saved. \n");
}
void highfunction()
{
    FILE *dp ;
    char line[120][20];
    int i=0;

    dp=fopen("sortedscore.txt","r");
    while(fgets(line[i], 120, dp))
    {
        line[i][strlen(line[i]) - 1] = '\0';
        i++;
    }

    for(int i=0; i<5; i++)
    {
        strcpy(hscores[i],line[i]);
    }
    /*strcpy(hs1,line[0]);
    strcpy(hs2,line[1]);
    strcpy(hs3,line[2]);
    strcpy(hs4,line[3]);
    strcpy(hs5,line[4]);*/
    fclose(dp);

}

void change()
{
    dy=dy-speed;
}
void change1()
{
    ey=ey-speed;
}
void change2()
{
    fy=fy+50;
}


void iDraw()
{
    iClear();
    sorted();
    highfunction();
    char p[20];
    char l[20];

    if(game_state==homepage) //home menu page
    {
        //musicON=TRUE;

        dx=GenerateRandom(1, 2), dy=scrnheight, ex=GenerateRandom(3, 4), ey=scrnheight;
        tiles_count=0;
        points=0;
        iPauseTimer(t1);
        iPauseTimer(t2);
        iPauseTimer(t3);

        iShowBMP(0,0, "images/background.bmp");

        iShowBMP(425,750, "images/magictiles.bmp");

        iShowBMP(470, 620, "images/startmenu.bmp");

        iShowBMP(480, 510, "images/scores.bmp");

        iShowBMP(400, 400, "images/instructions.bmp");

        iShowBMP(470, 290, "images/credits.bmp");

        iShowBMP(800, 190, "images/exit.bmp");


    }
    else if(game_state==instructions)
    {

        iShowBMP(0,0, "images/background.bmp");
        iSetColor(81, 18, 87);

        iText(490, 722, "RULES", GLUT_BITMAP_HELVETICA_18);

        iText(370, 630, "=>  There will be only a certain number of notes", GLUT_BITMAP_HELVETICA_18);
        iText(370, 580, "=>  Pressing the correct keys = ", GLUT_BITMAP_HELVETICA_18);
        iText(370, 530, "=>  Pressing incorrect keys = ", GLUT_BITMAP_HELVETICA_18);
        iText(370, 480, "=>  Failing to press keys = ", GLUT_BITMAP_HELVETICA_18);
        iSetColor(255, 0, 0);
        iText(585, 480, " NO PENALTY", GLUT_BITMAP_HELVETICA_18);
        iText(614, 530, " -20", GLUT_BITMAP_HELVETICA_18);
        iText(632, 580, " +10", GLUT_BITMAP_HELVETICA_18);
        iSetColor(81, 18, 87);
        iText(370, 430, "=>  Key names are written at the bottom",GLUT_BITMAP_HELVETICA_18);

        iShowBMP(800,245, "images/back.bmp");
    }
    else if(game_state==level)
    {

        iShowBMP(0,0, "images/background.bmp");

        iShowBMP(470, 750, "images/levels.bmp");

        iShowBMP(490, 600, "images/easy.bmp");

        iShowBMP(490, 500, "images/hard.bmp");

        iShowBMP(470, 400, "images/insane.bmp");

        //iShowBMP(270, 245, "images/tiles_button.bmp");

        iShowBMP(800,245, "images/back.bmp");

    }
    else if(game_state== credits)
    {
        iShowBMP(0,0, "images/background.bmp");
        iSetColor(81, 18, 87);
        iText(400, 722, "Project by:", GLUT_BITMAP_HELVETICA_18);
        iLine(400, 700, 500, 700);
        iText(400, 650, "Sheikh Iftikharun Nisa", GLUT_BITMAP_HELVETICA_18);
        iText(400, 590, "2105069, CSE, BUET", GLUT_BITMAP_HELVETICA_18);
        iText(400, 510, "Supervisor:", GLUT_BITMAP_HELVETICA_18);
        iLine(400, 490, 500, 490);
        iText(400, 450, "Arko Sir, Department of CSE" , GLUT_BITMAP_HELVETICA_18);
        iShowBMP(800,245, "images/back.bmp");

    }

    else if(game_state==scorelist)
    {
        sorted();
        highfunction();

        iShowBMP(0,0, "images/background.bmp");

        iShowBMP(450, 800, "images/highscores.bmp");

        iSetColor(81, 18, 87);

        iText(474,712,hscores[0],GLUT_BITMAP_HELVETICA_18);
        iText(474,662,hscores[1],GLUT_BITMAP_HELVETICA_18);
        iText(474,612,hscores[2],GLUT_BITMAP_HELVETICA_18);
        iText(474,562,hscores[3],GLUT_BITMAP_HELVETICA_18);
        iText(474,512,hscores[4],GLUT_BITMAP_HELVETICA_18);

        iText(440,712,"#1",GLUT_BITMAP_HELVETICA_18);
        iText(440,662,"#2",GLUT_BITMAP_HELVETICA_18);
        iText(440,612,"#3",GLUT_BITMAP_HELVETICA_18);
        iText(440,562,"#4",GLUT_BITMAP_HELVETICA_18);
        iText(440,512,"#5",GLUT_BITMAP_HELVETICA_18);
        iShowBMP(800,245, "images/back.bmp");
        iShowBMP(700, 400, "images/victor_pika.bmp");

    }


    else if(game_state==gameplay)
    {
        //musicON=FALSE;
        iSetColor(255, 255, 255);
        iFilledRectangle(0, 0, 1000, 1000);


        //iSetColor(200, 200, 200);
        //iFilledRectangle(1000, 0, 1200, 1000);
        iShowBMP(1000, 0, "images/sky.bmp");
        iSetColor(0, 0, 0);
        iLine(250, 0, 250, 1000);
        iLine(500, 0, 500, 1000);
        iLine(750, 0, 750, 1000);
        iLine(1000, 0, 1000, 1000);
        iText(112, 300, "A", GLUT_BITMAP_TIMES_ROMAN_24);
        iText(362, 300, "S", GLUT_BITMAP_TIMES_ROMAN_24);
        iText(625, 300, "D", GLUT_BITMAP_TIMES_ROMAN_24);
        iText(875, 300, "F", GLUT_BITMAP_TIMES_ROMAN_24);

        //iText(300, 200, "Press p for pause, r for resume, END for exit.");
        iShowBMP(dx, dy, "images/black_tile.bmp");
        iShowBMP(ex, ey, "images/black_tile.bmp");

        iSetColor(81, 18, 87);
        //2iText(1050, 800, "SCORE: ", GLUT_BITMAP_HELVETICA_18);

        itoa(points,p, 10);

        iSetColor(81, 18, 87);
        //iText(1050, 700, "tiles: ", GLUT_BITMAP_HELVETICA_18);
        iShowBMP(1040, 650,"images/box.bmp");
        iShowBMP(1040, 550,"images/box.bmp");
        iShowBMP2(1150, 900,"images/pause.bmp", 255);
        iShowBMP2(1040, 700,"images/score.bmp", 16777215);
        iShowBMP2(1040, 600,"images/tiles.bmp", 16777215);
        itoa(tiles_count, l, 10);
        iText(1050, 660, p, GLUT_BITMAP_HELVETICA_18);
        iText(1050, 560, l, GLUT_BITMAP_HELVETICA_18);
        if(wrong_key)
        {
            iShowBMP2(1010, 350, "images/wrong_convo.bmp", 255);
            iShowBMP2(1010, 180, "images/pika.bmp", 255);
        }
        else if(!wrong_key) iShowBMP2(1020, 200, "images/pika_happy.bmp", 255);
        if(dy<10)
        {
            dx= GenerateRandom(1, 2);
            dy=1000;
            tiles_count++;
        }
        if(ey<10)
        {
            ex= GenerateRandom(3, 4);
            ey= 1000;
            tiles_count++;

        }
        if(tiles_count==tile_no) game_state=nickname;

    }

    else if(game_state==nickname)
    {
        iResumeTimer(t3);
        //PlaySound(TEXT("final.wav"), NULL, SND_ASYNC);

        //iShowBMP(0,0, "images/background.bmp");
        iShowBMP(0, 0, "images/pause_back.bmp");
        //sound_on();
        //iShowBMP(200,fy,"balloon1.bmp");
        iSetColor(25,74,63);
        iFilledRectangle(365,370,350,330);

        iSetColor(255,255,255);
        iText(430,627,"Your Score: ",GLUT_BITMAP_HELVETICA_18);

        iSetColor(255,255,255);
        iText(560,627, itoa(points, p, 10), GLUT_BITMAP_HELVETICA_18);

        iSetColor(107, 253, 58);
        iText(430,550,"Enter Your Nickname:",GLUT_BITMAP_HELVETICA_18);

        iSetColor(255,255,255);
        iFilledRectangle(420,455,250,50);

        iSetColor(0,0,0);
        iText(430, 470, player.name, GLUT_BITMAP_HELVETICA_18);

        iSetColor(135, 170, 122);
        iFilledRectangle(590,400,80,40);
        iSetColor(139, 189, 122);
        iFilledRectangle(593,403,74,34);

        iSetColor(0,0,0);
        iText(613,410,"OK",GLUT_BITMAP_HELVETICA_18);

//balloons
        iShowBMP2(100,fy,"images/balloon3.bmp", 255);
        iShowBMP2(200,fy+150,"images/balloon4.bmp", 255);
        iShowBMP2(300,fy,"images/balloon1.bmp", 255);
        iShowBMP2(405,fy-100,"images/balloon2.bmp", 255);
        iShowBMP2(500,fy+50,"images/balloon3.bmp", 255);
        iShowBMP2(650,fy+150,"images/balloon4.bmp", 255);
        iShowBMP2(700,fy,"images/balloon1.bmp", 255);
        iShowBMP2(850,fy+50,"images/balloon3.bmp", 255);
        iShowBMP2(1000,fy,"images/balloon2.bmp", 255);
        iShowBMP2(1100,fy+200,"images/balloon4.bmp", 255);


    }
    else if(game_state==pause)
    {
        //iSetColor(246, 246, 246);
        //iFilledRectangle(0, 0, 1200, 1000);
        iShowBMP(0, 0, "images/pause_back.bmp");
        iShowBMP2(600, 500, "images/pausepikachu.bmp", 16185078);
        iShowBMP2(300, 600, "images/tired.bmp", 16777215);
        iShowBMP2(300,500, "images/already.bmp", 16777215);
        iShowBMP2(300, 400, "images/oh_man.bmp",16777215);
        iShowBMP2(900, 200, "images/resume.bmp", 16777215);

        iSetColor(135, 170, 122);
        iText(895,165,"(or press 'R' to resume)",GLUT_BITMAP_HELVETICA_18);

        iShowBMP2(925, 280, "images/home.bmp", 16777215);
    }

}


void iMouseMove(int mx, int my)
{

}



void iMouse(int button, int state, int mx, int my)
{

    printf("%d %d %d\n", mx, my, score);
    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        if(game_state==homepage && mx>=470 && mx<=660  && my>=740 && my<=780)   // selecting levels
        {
            //musicON= FALSE;
            game_state=level;
            PlaySound(TEXT("sounds/Menu_click_sound.wav"), NULL, SND_ASYNC);
            mx=0, my=0;
            musicON= TRUE;
        }
        else if(game_state==homepage && mx>=480 && mx<=645  && my>=660 && my<=700)   // selecting scorelist
        {
            //musicON= FALSE;
            game_state=scorelist;
            PlaySound(TEXT("sounds/Menu_click_sound.wav"), NULL, SND_ASYNC);
            musicON=FALSE;
        }
        else if(game_state==homepage && mx>=400 && mx<=760 && my>=580 && my<=630)  // selecting instructions
        {
            //musicON= FALSE;
            game_state=instructions;
            PlaySound(TEXT("sounds/Menu_click_sound.wav"), NULL, SND_ASYNC);
            musicON= TRUE;
        }
        else if(game_state==homepage && mx>=471 && mx<=660 && my>=500&& my<=545)  // selecting credits
        {
            //musicON= FALSE;
            game_state=credits;
            PlaySound(TEXT("sounds/Menu_click_sound.wav"), NULL, SND_ASYNC);
            musicON= TRUE;
        }
        else if(game_state==homepage && mx>=800 && mx<=920 && my>=435 && my<= 475)  // exiting
        {
            exit(0);

        }
        else if(game_state==level && mx>=494 && mx<=610 && my>=720 && my<=760)  // level easy
        {
            game_state=gameplay;
            speed= 40;
            PlaySound(TEXT("sounds/Menu_click_sound.wav"), NULL, SND_ASYNC);
            iResumeTimer(t1);
            iResumeTimer(t2);
        }
        else if(game_state==level && mx>=494 && mx<=610 && my>=650 && my<=690)  // level hard
        {
            game_state=gameplay;
            speed= 60;
            PlaySound(TEXT("sounds/Menu_click_sound.wav"), NULL, SND_ASYNC);
            iResumeTimer(t1);
            iResumeTimer(t2);
        }
        else if(game_state==level && mx>=472 && mx<=640 && my>=580 && my<=620)  //level insane
        {
            game_state=gameplay;
            speed= 100;
            PlaySound(TEXT("sounds/Menu_click_sound.wav"), NULL, SND_ASYNC);
            iResumeTimer(t1);
            iResumeTimer(t2);
        }


        else if(game_state==instructions && mx>=800 && mx<=900 && my>=475 && my<=505)  //going back from instructions
        {
            game_state=homepage;
            PlaySound(TEXT("sounds/Menu_click_sound.wav"), NULL, SND_ASYNC);
        }

        else if(game_state==scorelist && mx>=800 && mx<=900 && my>=475 && my<=505)  //going back from scorelist
        {
            game_state=homepage;
            PlaySound(TEXT("sounds/Menu_click_sound.wav"), NULL, SND_ASYNC);
        }

        else if(game_state==credits&& mx>=800 && mx<=900 && my>=475 && my<=505)   //going back from credits
        {
            game_state=homepage;
            PlaySound(TEXT("sounds/Menu_click_sound.wav"), NULL, SND_ASYNC);
        }

        else if(game_state==level && mx>=800 && mx<=900 && my>=475 && my<=505)  //going back from levels
        {
            game_state=homepage;
            PlaySound(TEXT("sounds/Menu_click_sound.wav"), NULL, SND_ASYNC);
        }

        else if(game_state==gameplay && mx>=1150 && mx<=1184 && my>=930 && my<= 960)
        {
            PlaySound(TEXT("sounds/Menu_click_sound.wav"), NULL, SND_ASYNC);
            iPauseTimer(t1);
            iPauseTimer(t2);
            game_state= pause;

        }

        else if(game_state==pause && mx>=900 && mx<=1075 && my>= 440 && my<= 485)
        {
            PlaySound(TEXT("sounds/Menu_click_sound.wav"), NULL, SND_ASYNC);
            iResumeTimer(t1);
            iResumeTimer(t2);
            game_state= gameplay;

        }

        else if(game_state==pause && mx>=930 && mx<=1040 && my>= 510 && my<= 550)
        {
            PlaySound(TEXT("sounds/Menu_click_sound.wav"), NULL, SND_ASYNC);
            game_state= homepage;


        }
    }

    if(game_state==nickname)
        if(mx>=590 && mx<=670 && my>=580 && my<=605)
        {
            //iResumeTimer(t3);
            //PlaySound(TEXT("sounds/Menu_click_sound.wav"), NULL, SND_ASYNC);
            FILE *fp;
            fp = fopen("Highscores.txt", "a");
            fprintf(fp," %s %d ",player.name, points);
            fclose(fp);

            sorted();
            highfunction();

            strcpy(player.name,"");
            points=0;
            len=0;
            game_state=homepage;

        }



    if(button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
    {
    }
}


void iKeyboard(unsigned char key)
{

    if(game_state==nickname)
    {
        if(key != '\b')
        {
            player.name[len]= key;
            len++;
            player.name[len]= '\0';
        }
        else
        {
            if(len<0)
                len=0;
            else
                len--;
            player.name[len]='\0';
        }
    }

    if(game_state==gameplay)
    {
        if((key=='a' || key== 'A') && dx==0)
        {
            dy=1;
            points=points+10;
            PlaySound(TEXT("sounds/music1.wav"), NULL, SND_ASYNC);
            wrong_key=0;
        }

        else if((key=='s' || key=='S') && dx==250)
        {
            dy=1;
            points=points+10;
            PlaySound(TEXT("sounds/music1.wav"), NULL, SND_ASYNC);
            wrong_key=0;
        }

        else if((key=='d'|| key=='D') && ex==500)
        {
            ey=1;
            points=points+10;
            PlaySound(TEXT("sounds/music2.wav"), NULL, SND_ASYNC);
            wrong_key=0;
        }

        else if((key=='f' || key=='F') && ex==750)
        {
            ey=1;
            points=points+10;
            PlaySound(TEXT("sounds/music2.wav"), NULL, SND_ASYNC);
        }
        else if(key == 'p' || key== 'P')
        {
            iPauseTimer(t1);
            iPauseTimer(t2);
            game_state= pause;
        }

        else
        {
            points= points-20;
            wrong_key=1;
        }
        if(dy==0|| ey==0) points=points-30;
    }
    if(game_state==pause)
        if(key == 'r' || key== 'R')
        {
            iResumeTimer(t1);
            iResumeTimer(t2);
            game_state=gameplay;
        }
}

void iSpecialKeyboard(unsigned char key)
{

    if(key == GLUT_KEY_END)
    {
        exit(0);
    }

}


int main()
{
    len = strlen(player.name);

    t1=iSetTimer(100, change);
    t2=iSetTimer(100, change1);
    t3=iSetTimer(100, change2);


    iInitialize(1200, 1000, "Magic Tiles");
    return 0;
}




int GenerateRandom(int lower, int upper)
{
    int num = (rand() %(upper - lower + 1)) + lower;
    if(num==1) num=0;
    else if(num==2) num= 250;
    else if(num==3) num= 500;
    else if(num==4) num= 750;
    return num;
}
