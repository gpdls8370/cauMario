#define _CRT_SECURE_NO_WARNINGS
#include<bangtal.h>
#include <iostream>
#include<math.h>
#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<ctime>
using namespace std;

#define g4_character_size_width 60 
#define g4_character_size_length 100 
#define g4_obj1_size_width 30
#define g4_obj1_size_length 100 
#define g4_obj2_size_width 70
#define g4_obj2_size_length 90 
#define g4_obj3_size_width 80 
#define g4_obj3_size_length 80 
#define g4_obj4_size_width  80   
#define g4_obj4_size_length  80

#define g4_character_jump_hight 250

#define floor_y 110

extern int nowGameSceneNum;     

extern SoundID buttonClickSound, jumpSound_g5, jumpSound2_g5;
extern void enterTitle(int clearScene);
SceneID scene_g4;
ObjectID g4c1, g4goMapButton,g4startbutton, g4restartbutton,g4obj1[4], g4obj2[4], g4obj3[4], g4obj4[4], g4obj5[4],g4floor1,g4floor2, g4background1, g4background2, g4clear;
TimerID g4timer1, g4timer2, g4obmove,g4difficult;
SoundID g4theme, g4clearsound;
extern SoundID g1deadsound;

const char* g4objfile[5] =
{ "image/game4/선인/선인 애니메이션 1.png" ,"image/game4/해골 거북이/1.png" ,"image/game4/하늘 거북이/하늘거북이 애니메이션 1.png" ,"image/game4/c5.png" ,"image/game4/c6.png"  };
int g4objnumber[20] ={ 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19 };
//0123 지네   4567 c3   891011 c4  12131415 c5  16171819 c6
int movetype, g4howfar;
int g4difficulty;
double g4score=0;
bool stage2Clear = false;

//-----------선인---------

double g4obj1x[4], g4obj1y[4];
double g4obj1difficulty;

//------------해골 거북이-------
double g4obj2x[4], g4obj2y[4];




//------------하늘 거북이-------

double g4obj3x[4], g4obj3y[4];
int g4obj3startx[4], g4obj3starty[4] ;


//------------점프 하는 놈-------

double g4obj4x[4], g4obj4y[4];


//------------마리오 점프----------
double g4c1y=110,g4gravity=20, g4c1yjump2start;
bool g4isjumping1, g4isjumping2,g4isBottom,g4jumping1process=false, g4jumping2process = false;
double g4c1jump1cache, g4c1jump2cache;
bool g4jump1_1front, g4jump1_1back, g4jump2_1front, g4jump2_1back;
bool g4jump2ban=false;

//-------------
double jump1_1xcache=-100, jump2_1xcache = -100, g4jump2_1firstpositioncache;
bool g4jumping1_1, g4jumping2_1;






//----------------애니메이션------------
//---------마리오----
const char* g4c1animationfile[10] =
{ "image/game4/마리오/마리오 애니메이션1.png","image/game4/마리오/마리오 애니메이션2.png","image/game4/마리오/마리오 애니메이션3.png","image/game4/마리오/마리오 애니메이션4.png",
"image/game4/마리오/마리오 애니메이션5.png","image/game4/마리오/마리오 애니메이션6.png" ,"image/game4/마리오/마리오 애니메이션7.png" ,"image/game4/마리오/마리오 애니메이션8.png"
,"image/game4/마리오/마리오 애니메이션9.png" ,"image/game4/마리오/마리오 애니메이션10.png" };
const char* g4c1jumpanimationfile[3] =
{ "image/game4/마리오/마리오 애니메이션 점프 1.png","image/game4/마리오/마리오 애니메이션 점프 2.png","image/game4/마리오/마리오 애니메이션 점프 3.png" };
double g4c1animationcache, g4c1animationcache1;


//-------선인------------
double g4obj1animationcache, g4obj1animationcache1;//1이 계속 증가하는 값이고 0가 나머지 잠시 저장하는 변수
const char* g4obj1animationfile[4] =
{ "image/game4/선인/선인 애니메이션 1.png","image/game4/선인/선인 애니메이션 2.png","image/game4/선인/선인 애니메이션 3.png","image/game4/선인/선인 애니메이션 2.png" };


//---------해골 거북이-----------
double g4obj2animationcache, g4obj2animationcache1;
const char* g4obj2animationfile[10] =
{ "image/game4/해골 거북이/1.png","image/game4/해골 거북이/2.png","image/game4/해골 거북이/3.png","image/game4/해골 거북이/4.png" 
,"image/game4/해골 거북이/5.png" ,"image/game4/해골 거북이/6.png" ,"image/game4/해골 거북이/7.png" ,"image/game4/해골 거북이/8.png" 
,"image/game4/해골 거북이/9.png" ,"image/game4/해골 거북이/10.png" };


//---------하늘 거북이---------
double g4obj3animationcache, g4obj3animationcache1;
const char* g4obj3animationfile[7] =
{ "image/game4/하늘 거북이/하늘거북이 애니메이션 1.png","image/game4/하늘 거북이/하늘거북이 애니메이션 2.png","image/game4/하늘 거북이/하늘거북이 애니메이션 3.png","image/game4/하늘 거북이/하늘거북이 애니메이션 4.png",
"image/game4/하늘 거북이/하늘거북이 애니메이션 5.png","image/game4/하늘 거북이/하늘거북이 애니메이션 6.png","image/game4/하늘 거북이/하늘거북이 애니메이션 7.png", };

//-----------바닥----------
int g4floor1x=0, g4floor2x=2500;
int g4background1x = 0, g4background2x = 2000;


ObjectID g4createObject(const char* image, SceneID scene, int x, int y, bool shown) {
    ObjectID object = createObject(image);
    locateObject(object, scene, x, y);
    if (shown) {
        showObject(object);
    }
    return(object);
}

void g4c1animation() {
    
    if((g4jumping1process == true)||(g4jumping2process ==true)){
    }
    else {
        g4c1animationcache = fmod(g4c1animationcache1, 10);
        if (g4c1animationcache >= 0 && g4c1animationcache < 1) {
            setObjectImage(g4c1, g4c1animationfile[0]);
        }
        else if (g4c1animationcache >= 1 && g4c1animationcache < 2) {
            setObjectImage(g4c1, g4c1animationfile[1]);
        }
        else if (g4c1animationcache >= 2 && g4c1animationcache < 3) {
            setObjectImage(g4c1, g4c1animationfile[2]);
        }
        else if (g4c1animationcache >= 3 && g4c1animationcache < 4) {
            setObjectImage(g4c1, g4c1animationfile[3]);
        }
        else if (g4c1animationcache >= 4 && g4c1animationcache < 5) {
            setObjectImage(g4c1, g4c1animationfile[4]);
        }
        else if (g4c1animationcache >= 5 && g4c1animationcache < 6) {
            setObjectImage(g4c1, g4c1animationfile[5]);
        }
        else if (g4c1animationcache >= 6 && g4c1animationcache < 7) {
            setObjectImage(g4c1, g4c1animationfile[6]);
        }
        else if (g4c1animationcache >= 7 && g4c1animationcache < 8) {
            setObjectImage(g4c1, g4c1animationfile[7]);
        }
        else if (g4c1animationcache >= 8 && g4c1animationcache < 9) {
            setObjectImage(g4c1, g4c1animationfile[8]);
        }
        else if (g4c1animationcache >= 9 && g4c1animationcache < 10) {
            setObjectImage(g4c1, g4c1animationfile[9]);
        }
        
        
    }
    g4c1animationcache1 = g4c1animationcache1 + 0.9;

}


void g4obj1animation() {
    for (int i = 0; i < 4; i++) {
        g4obj1animationcache = fmod(g4obj1animationcache1, 4);
        if (g4obj1animationcache >= 0 && g4obj1animationcache < 1) {
            setObjectImage(g4obj1[i], g4obj1animationfile[0]);
        }
        else  if (g4obj1animationcache >= 1 && g4obj1animationcache < 2) {
            setObjectImage(g4obj1[i], g4obj1animationfile[1]);
        }
        else  if (g4obj1animationcache >= 2 && g4obj1animationcache < 3) {
            setObjectImage(g4obj1[i], g4obj1animationfile[2]);
        }
        else  if (g4obj1animationcache >= 3 && g4obj1animationcache < 4) {
            setObjectImage(g4obj1[i], g4obj1animationfile[3]);
        }       

    }
    g4obj1animationcache1 = g4obj1animationcache1 + 0.7;
}

void g4obj2animation() {
    for (int i = 0; i < 4; i++) {
        g4obj2animationcache = fmod(g4obj2animationcache1, 10);
            if (g4obj2animationcache >= 0 && g4obj2animationcache < 1) {
                setObjectImage(g4obj2[i], g4obj2animationfile[0]);
            }
            else  if (g4obj2animationcache >= 1 && g4obj2animationcache < 2) {
                setObjectImage(g4obj2[i], g4obj2animationfile[1]);
            }
            else  if (g4obj2animationcache >= 2 && g4obj2animationcache < 3) {
                setObjectImage(g4obj2[i], g4obj2animationfile[2]);
            }
            else  if (g4obj2animationcache >= 3 && g4obj2animationcache < 4) {
                setObjectImage(g4obj2[i], g4obj2animationfile[3]);
            }
            else  if (g4obj2animationcache >= 4 && g4obj2animationcache < 5) {
                setObjectImage(g4obj2[i], g4obj2animationfile[4]);
            }
            else  if (g4obj2animationcache >= 5 && g4obj2animationcache < 6) {
                setObjectImage(g4obj2[i], g4obj2animationfile[5]);
            }
            else  if (g4obj2animationcache >= 6 && g4obj2animationcache < 7) {
                setObjectImage(g4obj2[i], g4obj2animationfile[6]);
            }
            else  if (g4obj2animationcache >= 7 && g4obj2animationcache < 8) {
                setObjectImage(g4obj2[i], g4obj2animationfile[7]);
            }
            else  if (g4obj2animationcache >= 8 && g4obj2animationcache < 9) {
                setObjectImage(g4obj2[i], g4obj2animationfile[8]);
            }
            else  if (g4obj2animationcache >= 9 && g4obj2animationcache < 10) {
                setObjectImage(g4obj2[i], g4obj2animationfile[9]);
            }   
    }
    g4obj2animationcache1 = g4obj2animationcache1 +0.5;
    }

void g4obj3animation() {
    for (int i = 0; i < 4; i++) {
        g4obj3animationcache = fmod(g4obj3animationcache1, 7);
        if (g4obj3animationcache >= 0 && g4obj3animationcache < 1) {
            setObjectImage(g4obj3[i], g4obj3animationfile[0]);
        }
        else  if (g4obj3animationcache >= 1 && g4obj3animationcache < 2) {
            setObjectImage(g4obj3[i], g4obj3animationfile[1]);
        }
        else  if (g4obj3animationcache >= 2 && g4obj3animationcache < 3) {
            setObjectImage(g4obj3[i], g4obj3animationfile[2]);
        }
        else  if (g4obj3animationcache >= 3 && g4obj3animationcache < 4) {
            setObjectImage(g4obj3[i], g4obj3animationfile[3]);
        }
        else  if (g4obj3animationcache >= 4 && g4obj3animationcache < 5) {
            setObjectImage(g4obj3[i], g4obj3animationfile[4]);
        }
        else  if (g4obj3animationcache >= 5 && g4obj3animationcache < 6) {
            setObjectImage(g4obj3[i], g4obj3animationfile[5]);
        }
        else  if (g4obj3animationcache >= 6 && g4obj3animationcache < 7) {
            setObjectImage(g4obj3[i], g4obj3animationfile[6]);
        }
       
    }
    g4obj3animationcache1 = g4obj3animationcache1 + 0.7;
}

void g4flooranimation() {
    if (g4floor1x < -2600) {
        g4floor1x = g4floor2x + 2500;
        
    }
    if (g4floor2x < -2600) {
        g4floor2x = g4floor1x + 2500;
        
    }
    else {
        g4floor1x = g4floor1x -11 -   g4difficulty;
        g4floor2x = g4floor2x - 11 -   g4difficulty;
        g4howfar = g4howfar + 11 +   g4difficulty;
        g4score = g4howfar* 0.01;
    }

    
}

void g4scoremessage() {
    char buf[256];
    sprintf_s(buf, "간 거리 : %0.f m", g4score, scene_g4);
    showMessage(buf);
}

void g4death() {

    for (int i = 0; i < 4; i++) {
        if ((220 < (g4obj1x[i] + g4_obj1_size_width)) && ((210 + g4_character_size_width) > g4obj1x[i]) &&
            (g4c1y < (g4obj1y[i] + g4_obj1_size_length)) && ((g4c1y + g4_character_size_length) > g4obj1y[i])) {
            stopTimer(g4timer1);
            stopTimer(g4timer2);
            stopTimer(g4obmove);
            showMessage("dead");
            playSound(g1deadsound);
            stopSound(g4theme);
            g4scoremessage();
            showObject(g4restartbutton);
            showObject(g4goMapButton);
            hideObject(g4c1);
        }

        if ((220 < (g4obj2x[i] + g4_obj2_size_width)) && (210 + g4_character_size_width > g4obj2x[i]) &&
            (g4c1y < (g4obj2y[i] + g4_obj2_size_length)) && (g4c1y + g4_character_size_length > g4obj2y[i])) {
            stopTimer(g4timer1);
            stopTimer(g4timer2);
            stopTimer(g4obmove);
            showMessage("dead");
            playSound(g1deadsound);
            stopSound(g4theme);
            g4scoremessage();
            showObject(g4restartbutton);
            showObject(g4goMapButton);
            //hideObject(g4c1);
        }


        if (g4score > 70) {
            if ((220 < (g4obj3x[i] + g4_obj3_size_width)) && (210 + g4_character_size_width > g4obj3x[i]) &&
                (g4c1y < (g4obj3y[i] + g4_obj3_size_length)) && (g4c1y + g4_character_size_length > g4obj3y[i])) {
                stopTimer(g4timer1);
                stopTimer(g4timer2);
                stopTimer(g4obmove);
                showMessage("dead");
                playSound(g1deadsound);
                stopSound(g4theme);
                g4scoremessage();
                showObject(g4restartbutton);
                showObject(g4goMapButton);
                //hideObject(g4c1);
            }
        }
        if ((210 < (g4obj4x[i] + g4_obj4_size_width)) && (210 + g4_character_size_width > g4obj4x[i]) &&
            (g4c1y < (g4obj4y[i] + g4_obj4_size_length)) && (g4c1y + g4_character_size_length > g4obj4y[i])) {
            stopTimer(g4timer1);
            stopTimer(g4timer2);
            stopTimer(g4obmove);
            showMessage("dead");
            playSound(g1deadsound);
            g4scoremessage();
            showObject(g4restartbutton);
            hideObject(g4c1);
        }
    }
}
    


void g4jumpstate() {
    if (jump1_1xcache <= 0 && jump1_1xcache >= -100) {
        g4jump1_1front = true;
        g4jump1_1back = false;
        g4jump2_1front = false;
        g4jump2_1back = false;

    }
    if (jump1_1xcache <= 100 && jump1_1xcache > 0) {
        g4jump1_1front = false;
        g4jump1_1back = true;
        g4jump2_1front = false;
        g4jump2_1back = false;

    }
    if (jump2_1xcache <= 0 && jump2_1xcache > -100) {
        g4jump1_1front = false;
        g4jump1_1back = false;
        g4jump2_1front = true;
        g4jump2_1back = false;

    }
    if (jump2_1xcache <= 100 &&jump2_1xcache > 0) {
        g4jump1_1front = false;
        g4jump1_1back = false;
        g4jump2_1front = false;
        g4jump2_1back = true;

    }
}

void g4jump1_1() {
    double g4c1ycache;
    
    if (jump1_1xcache >= 100 || jump1_1xcache < -100) {//계산 밖일때
        jump1_1xcache = -100;
        g4c1y = floor_y;
        g4jumping1_1 = false;
    }
    else {
        jump1_1xcache = jump1_1xcache +4;
    }
    g4c1ycache = -(jump1_1xcache * jump1_1xcache)/40+ 250;
    g4c1y = floor_y + g4c1ycache;

}
void g4jump2_1(double g4c1positiony) {
    double g4c1ycache;
    if (jump2_1xcache >= 100 || jump2_1xcache < -100) {//계산 밖일때
        jump2_1xcache = -100;
        g4c1y = g4c1positiony;
        g4jumping2_1 = false;
        startTimer(g4timer1);
        stopTimer(g4timer2);
    }
    else {
        jump2_1xcache = jump2_1xcache + 4;
    }
    g4c1ycache = -(jump2_1xcache * jump2_1xcache) / 40 + 250;
    g4c1y = floor_y + g4c1positiony+ g4c1ycache;

}


void g4placeobstacle(ObjectID obstacle, SceneID scene, int x, int y, bool shown) {
    if (shown) {
        showObject(obstacle);
    }
    else hideObject(obstacle);
    locateObject(obstacle, scene, x, y);
}

void g4obstaclemove(ObjectID obstacle,SceneID scene,int movetype,int objID) {
    
    if (movetype == 1) {
       g4obj1y[objID] = 110;
       if (g4obj1x[objID] < 0) {
           srand((unsigned int)time(NULL));
           int num = rand();
           int rndvalue = num % 5;
           if (objID == 1 || objID == 2 || objID == 3) {
               g4obj1x[objID] = g4obj1x[objID - 1] + 250+(500-g4difficulty *30)+rndvalue * 70;
           }
           else if (objID == 0) {
               g4obj1x[objID] = g4obj1x[3] + 250+ (500 - g4difficulty * 30)+rndvalue * 70;
           }
       }
       else {
           g4obj1x[objID] = g4obj1x[objID] - 11- g4difficulty;
       }
    }
    if (movetype == 2) {
        if (g4difficulty >= 2) {
            g4obj2y[objID] = 110;
            if (g4obj2x[objID] < 0) {
                srand((unsigned int)time(NULL));
                int num = rand();
                int rndvalue = num % 5;
                if (objID == 1 || objID == 2 || objID == 3) {
                    g4obj2x[objID] = g4obj2x[objID - 1] +400 + (500 - g4difficulty * 10) + rndvalue * 50;
                }
                else if (objID == 0) {
                    g4obj2x[objID] = g4obj2x[3] + 400 + (500 - g4difficulty * 10) + rndvalue * 50;
                }
            }
            else {
                g4obj2x[objID] = g4obj2x[objID] - 16 -  g4difficulty;
            }
        }
    }
    if (movetype == 3) {       
        if (g4difficulty >= 4) {
            if (g4obj3x[objID] < 0) {
                //srand((unsigned int)time(NULL));
                int num = rand();
                int rndvalue = num % 5;

                //g4obj3startx[objID] = 1300 + rndvalue * 20;
               // g4obj3starty[objID] = 400 + rndvalue * 30;
                if (objID == 1 || objID == 2 || objID == 3) {
                    g4obj3x[objID] = g4obj3x[objID - 1] + 700 + rndvalue * 150;
                }
                else if (objID == 0) {
                    g4obj3x[objID] = g4obj3x[3] + 700 + rndvalue * 150;
                }
                g4obj3starty[objID] = 500 + rndvalue * 30;
                g4obj3y[objID] = g4obj3starty[objID];
            }
            else {
                g4obj3x[objID] = g4obj3x[objID] - 10;
                g4obj3y[objID] = 70 * sin((0.01) * g4obj3x[objID]) + g4obj3starty[objID];
            }
        }
    }
}

void g4objselectshow() {
    for (int i = 0; i < 4; i++) {
        if ((0 < (g4obj1x[i] + g4_obj1_size_width)) && 1280 > g4obj1x[i])  {
            showObject(g4obj1[i]);
        }
        else {
            hideObject(g4obj1[i]);
        }

        if (g4score > 25) {
            if (g4score > 20 && g4score < 40) {
                if ((0 < (g4obj2x[i] + g4_obj1_size_width)) && 1500 > g4obj2x[i])
                {
                    hideObject(g4obj2[i]);
                }
            }
            else if ((0 < (g4obj2x[i] + g4_obj1_size_width)) && 1280 > g4obj2x[i]) {
                showObject(g4obj2[i]);
            }
            else {
                hideObject(g4obj2[i]);
            }
        }
        else {
            hideObject(g4obj2[i]);
        }

        if (g4score > 70) {
            if ((0 < (g4obj3x[i] + g4_obj1_size_width)) && 1280 > g4obj3x[i]) {
               // showObject(g4obj3[i]);
            }
            else {
                hideObject(g4obj3[i]);
            }
        }
        else {
            hideObject(g4obj3[i]);
        }
        

    }
}

void g4stageclear() {
    if (g4score >= 70) {
        showObject(g4clear);
        stopSound(g4theme);
        playSound(g4clearsound);
        stopTimer(g4timer1);
        stopTimer(g4timer2);
        stopTimer(g4obmove);
        //showMessage("dead");
        stage2Clear = true;
        g4scoremessage();
        hideObject(g4c1);
        showObject(g4goMapButton);
    }
}

void g4update() {
    g4jumpstate();
    if (g4jumping2_1 == true) {
        g4jump2ban = true;
    }
    else {
        if(g4c1y==110){
            g4jump2ban = false;
        }
    }

    g4c1animation();
    g4obj1animation();
    g4obj2animation();
    g4obj3animation();
    g4flooranimation();
    g4death();
    g4stageclear();
    g4objselectshow();
    //-------좌표이동
    for (int i = 0; i < 4; i++) {
        g4obstaclemove(g4obj1[i], scene_g4, 1, i);
    }
    for (int i = 0; i < 4; i++) {
        g4obstaclemove(g4obj2[i], scene_g4, 2, i);
    }
    for (int i = 0; i < 4; i++) {
        g4obstaclemove(g4obj3[i], scene_g4, 3, i);
    }
   



    //-----배치
    for (int i=0; i < 4; i++) {
        locateObject(g4obj1[i], scene_g4, g4obj1x[i], g4obj1y[i]);
    }
    for (int i = 0; i < 4; i++) {
        locateObject(g4obj2[i], scene_g4, g4obj2x[i], g4obj2y[i]);
    }
    for (int i = 0; i < 4; i++) {
        locateObject(g4obj3[i], scene_g4, g4obj3x[i], g4obj3y[i]);
    }
    for (int i = 0; i < 4; i++) {
        locateObject(g4obj4[i], scene_g4, g4obj4x[i], g4obj4y[i]);
    }    
    locateObject(g4floor1, scene_g4, g4floor1x, 0);
    locateObject(g4floor2, scene_g4, g4floor2x, 0);
    //locateObject(g4background1, scene_g4, g4background1x, 0);
    //locateObject(g4background2, scene_g4, g4background2x, 0);
    locateObject(g4c1, scene_g4, 210, g4c1y);

//-------난이도
    if (g4score > 0 && g4score < 5) {
        g4difficulty = 1;
    }
    else if (g4score > 5 && g4score < 10) {
        g4difficulty = 2;
    }
    else if (g4score > 10 && g4score < 15) {
        g4difficulty =3;
    }
    else if (g4score >15 && g4score < 20) {
        g4difficulty = 4;
    }
    else if (g4score > 20 && g4score < 25) {
        g4difficulty =5;
    }
    
}

void g4gamestart() {
    hideObject(g4goMapButton);
    playSound(g4theme);
    g4howfar = 0;
    for (int i = 0; i < 4; i++) {
        srand((unsigned int)time(NULL));          
        int num = rand();
        int rndvalue = num % 5;
        g4obj1x[i] = 1300 + 500*i+rndvalue * 20;
        g4obj1y[i] = 110;
        g4placeobstacle(g4obj1[i], scene_g4, g4obj1x[i], g4obj1y[i], true);
    }
    for (int i = 0; i < 4; i++) {
        //srand((unsigned int)time(NULL));
        int num = rand();
        int rndvalue = num % 5;
        g4obj2x[i] = 6000 + 700 * i + rndvalue * 20;
        g4obj2y[i] = 110;
        g4placeobstacle(g4obj2[i], scene_g4, g4obj2x[i], g4obj2y[i], true);
    }
   
    for (int i = 0; i < 4; i++) {
        //srand((unsigned int)time(NULL));
        int num = rand();
        int rndvalue = num % 5;
        g4obj3x[i] = 1300 + 800 * i + rndvalue * 20;
        g4obj3starty[i] = 400 + rndvalue * 30;
        g4obj3y[i] = g4obj3starty[i];
        g4placeobstacle(g4obj3[i], scene_g4, g4obj3x[i], g4obj3y[i], true);
    }
    startTimer(g4obmove);
    startTimer(g4timer1);
    startTimer(g4difficult);
}

void g4gamerestart() {
    g4gamestart();
    g4c1y = 110;
    locateObject(g4c1, scene_g4, 210,g4c1y);
    g4score = 0;
}

void Game4_mouseCallback(ObjectID object, int x, int y, MouseAction action) {

    if (object == g4startbutton) {
        playSound(buttonClickSound);
        showObject(g4c1);
        g4gamestart();
        hideObject(g4startbutton);
    }
    else if (object == g4restartbutton) {
        playSound(buttonClickSound);
        g4gamerestart();
        showObject(g4c1);
        hideObject(g4restartbutton);
    }
    else if (object == g4goMapButton) {
        playSound(buttonClickSound);
        stopTimer(g4timer1);
        stopTimer(g4timer2);
        stopTimer(g4obmove);
        stopTimer(g4difficult);
        stopSound(g4theme);

        if (stage2Clear) 
            enterTitle(2);
        
        else 
            enterTitle(0);
        
    }

}
void Game4_timerCallback(TimerID timer) {
	if (timer == g4timer1) {//점프 1
        
    /* g4jump1();
     setTimer(g4timer1, 0.01f);
     startTimer(g4timer1);
        */
        if (g4jumping1_1) {
            g4jump1_1();
           
        }
        setTimer(g4timer1, 0.01f);
        startTimer(g4timer1);
	}
    if (timer == g4timer2) {//점프 2
        /*g4jump2(); 
        setTimer(g4timer2, 0.01f);
        startTimer(g4timer2);*/
        if (g4jumping2_1) {
            g4jump2_1(g4jump2_1firstpositioncache);

        }
        setTimer(g4timer2, 0.01f);
        startTimer(g4timer2);
    }
    if (timer == g4obmove) {//장애물 움직임
        setTimer(g4obmove, 0.04f);
        startTimer(g4obmove);
        g4update();
    }
    
    
}
void Game4_soundCallback(SoundID sound) {
	if (sound == g4theme) {
        playSound(g4theme);
	}

}

void Game4_keyboardCallback(KeyCode code, KeyState state)
{
     if (code == 75) {			// 
        if (nowGameSceneNum == 4) {
            //g4jumping1_1 = (state == KeyState::KEYBOARD_PRESSED ? true : false);
            if (state == KeyState::KEYBOARD_PRESSED) {//
                
                    if (g4jumping1_1 == false) {
                        g4jumping1_1 = true;
                    }
                    else if (g4jumping1_1 == true) {
                        //if (g4jump1_1front == false) {//1단점프 앞부분에서 점프 금지
                            if (g4jump2ban == false) {//2단 점프후 점프 금지
                                if (g4jump2_1back == false) {

                                    if (g4jumping2_1 == false) {
                                        g4jump2_1firstpositioncache = g4c1y;
                                        stopTimer(g4timer1);
                                        startTimer(g4timer2);
                                        g4jumping2_1 = true;
                                    }
                                    else if (g4jumping2_1 == true) {
                                    }
                                }
                            }
                        //}
                    }
                

            }
        }
    }
}

void Game4_main() {

    setGameOption(GameOption::GAME_OPTION_INVENTORY_BUTTON, false);
    setGameOption(GameOption::GAME_OPTION_MESSAGE_BOX_BUTTON, false);

	scene_g4 = createScene("STAGE2 사막", "image/game4/배경.png");
    g4background1 = g4createObject("image/game4/배경.png", scene_g4, -500, 0, true);
    g4background2 = g4createObject("image/game4/배경.png", scene_g4, 2000, 0, true);
    g4floor1 = g4createObject("image/game4/바닥.png", scene_g4, 0, 0, true);
    g4floor2 = g4createObject("image/game4/바닥.png", scene_g4, 2500, 0, true);
    
    g4startbutton = g4createObject("image/game4/start.png", scene_g4, 520, 320, true);
    g4restartbutton = g4createObject("image/game4/restart.png", scene_g4, 500, 330, false);
 


	g4c1 = g4createObject("image/game4/마리오 애니메이션1.png", scene_g4, 210, 110, true);
    for (int i = 0; i < 4; i++) {        
        g4obj1[i] = g4createObject(g4objfile[0], scene_g4, 1300, 110, true);
    }
    for (int i = 0; i < 4; i++) {
        g4obj2[i] = g4createObject(g4objfile[1], scene_g4, 1300, 110, true);
        scaleObject(g4obj2[i], 0.5f);
    }
    for (int i = 0; i < 4; i++) {
        g4obj3[i] = g4createObject(g4objfile[2], scene_g4, 1300, 410, true);
    }
    /*for (int i = 0; i < 4; i++) {
        g4obj4[i] = g4createObject(g4objfile[3], scene_g4, 1300, 110, true);
    }*/
    
    g4goMapButton = g4createObject("image/game6/goMap.png", scene_g4, 20, 20, true);
    g4clear = g4createObject("image/game4/클리어.png", scene_g4, 300, 350, false);
    scaleObject(g4clear, 0.5f);

	g4timer1 = createTimer(0.05f);
    g4timer2 = createTimer(0.05f);
    g4obmove = createTimer(0.05f);
    g4difficult = createTimer(5.f);
    
    g4theme = createSound("sounds/배경음/사막.mp3");
    g4clearsound = createSound("sounds/공통/게임클리어.wav");

}