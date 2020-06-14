#include<bangtal.h>
#include <iostream>
#include<math.h>
#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<ctime>
using namespace std;


SceneID scene_g7;
ObjectID g7c1, g7jumpbutton, g7startbutton, g7restartbutton, g7obj[20];
TimerID g7timer1;
SoundID g7theme;

const char* g7objfile[5] =
{ "image/game4/c2.png" ,"image/game4/c3.png" ,"image/game4/c4.png" ,"image/game4/c5.png" ,"image/game4/c6.png" };


ObjectID g7createObject(const char* image, SceneID scene, int x, int y, bool shown) {
    ObjectID object = createObject(image);
    locateObject(object, scene, x, y);
    if (shown) {
        showObject(object);
    }
    return(object);
}





void g7update() {
    //g4placeobstacle(g4obj[0], scene_g4, 1300, 210, true);

    
}



void Game7_mouseCallback(ObjectID object, int x, int y, MouseAction action) {

    if (object == g7jumpbutton) {
       
    }
   
}
void Game7_timerCallback(TimerID timer) {
    

}
void Game7_soundCallback(SoundID sound) {
    if (sound == g7theme) {

    }

}
void Game7_main() {


    scene_g7 = createScene("game7", "image/game7/background.png");
    g7jumpbutton = g7createObject("image/game7/»Æ¿Œ.png", scene_g7, 800, 110, true);
   
    g7c1 = g7createObject("image/game4/c1.png", scene_g7, 210, 210, true);
  
    g7timer1 = createTimer(0.01f);
    


}