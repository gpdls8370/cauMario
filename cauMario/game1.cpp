#define _CRT_SECURE_NO_WARNINGS
#include<bangtal.h>
#include <iostream>
#include<math.h>
#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<ctime>

#define g1_character_size_x 30 
#define g1_character_size_y 40 
#define g1_obj1_size_width 20 
#define g1_obj1_size_hight 20 

extern void enterTitle(int clearScene);
extern int coin;
extern SoundID buttonClickSound;
SceneID scene_g1;
ObjectID g1c1, g1obj1[6][10],g1startbutton, g1restartbutton, g1goMapButton;//[세로][가로][j][i]
TimerID g1timer1, g1c1move,g1levelupgrade,g1score, g1difficult;
SoundID bgm_g1,g1deadsound;

extern int nowGameSceneNum,coin;

int highscore_g1=0;
int getCoin;


int obj1x[6][10] = { 0 }, obj1y[6][10] = { 0 };
double obj1speed=5;
double g1obj1moveblockx[6][10], g1obj1moveblocky[6][10];



int speed = 6;
double changex, changey;

int g1c1x=500, g1c1y=200;
int g1dx = 0, g1dy = 0;

ObjectID g1obj1_1[30];
int g1difficulty=0, obj1_1x[30], obj1_1y[30];//g1difficulty는 추가된 오브젝트 개수
int obj1_1speed = 7;
double g1obj1_1moveblockx[30], g1obj1_1moveblocky[30];

//---애니메이션----
//---마리오---
int g1c1heading;
double g1c1animationcache, g1c1animationcache1;//1이 계속 증가하는 값이고 0가 나머지 잠시 저장하는 변수
const char* g1c1animationfilefront[10] =
{ "image/game1/마리오앞/1.png","image/game1/마리오앞/2.png","image/game1/마리오앞/3.png","image/game1/마리오앞/4.png","image/game1/마리오앞/5.png",
"image/game1/마리오앞/6.png","image/game1/마리오앞/7.png","image/game1/마리오앞/8.png","image/game1/마리오앞/9.png","image/game1/마리오앞/10.png" };

const char* g1c1animationfileback[6] =
{ "image/game1/마리오뒤/1.png", "image/game1/마리오뒤/2.png", "image/game1/마리오뒤/3.png", 
"image/game1/마리오뒤/4.png", "image/game1/마리오뒤/5.png", "image/game1/마리오뒤/6.png" };

const char* g1c1animationfileleft[10] =
{ "image/game1/마리오왼쪽/1.png", "image/game1/마리오왼쪽/2.png", "image/game1/마리오왼쪽/3.png", "image/game1/마리오왼쪽/4.png", "image/game1/마리오왼쪽/5.png",
 "image/game1/마리오왼쪽/6.png",  "image/game1/마리오왼쪽/7.png",  "image/game1/마리오왼쪽/8.png",  "image/game1/마리오왼쪽/9.png",  "image/game1/마리오왼쪽/10.png" };

const char* g1c1animationfileright[10] =
{ "image/game1/마리오오른쪽/1.png","image/game1/마리오오른쪽/2.png","image/game1/마리오오른쪽/3.png","image/game1/마리오오른쪽/4.png","image/game1/마리오오른쪽/5.png",
"image/game1/마리오오른쪽/6.png", "image/game1/마리오오른쪽/7.png", "image/game1/마리오오른쪽/8.png", "image/game1/마리오오른쪽/9.png", "image/game1/마리오오른쪽/10.png"};











ObjectID g1createObject(const char* image, SceneID scene, int x, int y, bool shown) {
	ObjectID object = createObject(image);
	locateObject(object, scene, x, y);
	if (shown) {
		showObject(object);
	}
	return(object);
}

void g1c1animation() {
	if (g1c1heading == 0) {//앞
		g1c1animationcache = fmod(g1c1animationcache1, 10);
		if (g1c1animationcache >= 0 && g1c1animationcache < 1) {
			setObjectImage(g1c1, g1c1animationfilefront[0]);
		}
		else  if (g1c1animationcache >= 1 && g1c1animationcache < 2) {
			setObjectImage(g1c1, g1c1animationfilefront[1]);
		}
		else  if (g1c1animationcache >= 2 && g1c1animationcache < 3) {
			setObjectImage(g1c1, g1c1animationfilefront[2]);
		}
		else  if (g1c1animationcache >= 3 && g1c1animationcache < 4) {
			setObjectImage(g1c1, g1c1animationfilefront[3]);
		}
		else  if (g1c1animationcache >= 4 && g1c1animationcache < 5) {
			setObjectImage(g1c1, g1c1animationfilefront[4]);
		}
		else  if (g1c1animationcache >= 5 && g1c1animationcache < 6) {
			setObjectImage(g1c1, g1c1animationfilefront[5]);
		}
		else  if (g1c1animationcache >= 6 && g1c1animationcache < 7) {
			setObjectImage(g1c1, g1c1animationfilefront[6]);
		}
		else  if (g1c1animationcache >= 7 && g1c1animationcache < 8) {
			setObjectImage(g1c1, g1c1animationfilefront[7]);
		}
		else  if (g1c1animationcache >= 8 && g1c1animationcache < 9) {
			setObjectImage(g1c1, g1c1animationfilefront[8]);
		}
		else  if (g1c1animationcache >= 9 && g1c1animationcache < 10) {
			setObjectImage(g1c1, g1c1animationfilefront[9]);
		}

		

	}
	else if (g1c1heading == 1) {//뒤
		g1c1animationcache = fmod(g1c1animationcache1, 6);
		if (g1c1animationcache >= 0 && g1c1animationcache < 1) {
			setObjectImage(g1c1, g1c1animationfileback[0]);
		}
		else  if (g1c1animationcache >= 1 && g1c1animationcache < 2) {
			setObjectImage(g1c1, g1c1animationfileback[1]);
		}
		else  if (g1c1animationcache >= 2 && g1c1animationcache < 3) {
			setObjectImage(g1c1, g1c1animationfileback[2]);
		}
		else  if (g1c1animationcache >= 3 && g1c1animationcache < 4) {
			setObjectImage(g1c1, g1c1animationfileback[3]);
		}
		else  if (g1c1animationcache >= 4 && g1c1animationcache < 5) {
			setObjectImage(g1c1, g1c1animationfileback[4]);
		}
		else  if (g1c1animationcache >= 5 && g1c1animationcache < 6) {
			setObjectImage(g1c1, g1c1animationfileback[5]);
		}
		

		

	}
	else if (g1c1heading == 2) {//왼쪽
		g1c1animationcache = fmod(g1c1animationcache1, 10);
		if (g1c1animationcache >= 0 && g1c1animationcache < 1) {
			setObjectImage(g1c1, g1c1animationfileleft[0]);
		}
		else  if (g1c1animationcache >= 1 && g1c1animationcache < 2) {
			setObjectImage(g1c1, g1c1animationfileleft[1]);
		}
		else  if (g1c1animationcache >= 2 && g1c1animationcache < 3) {
			setObjectImage(g1c1, g1c1animationfileleft[2]);
		}
		else  if (g1c1animationcache >= 3 && g1c1animationcache < 4) {
			setObjectImage(g1c1, g1c1animationfileleft[3]);
		}
		else  if (g1c1animationcache >= 4 && g1c1animationcache < 5) {
			setObjectImage(g1c1, g1c1animationfileleft[4]);
		}
		else  if (g1c1animationcache >= 5 && g1c1animationcache < 6) {
			setObjectImage(g1c1, g1c1animationfileleft[5]);
		}
		else  if (g1c1animationcache >= 6 && g1c1animationcache < 7) {
			setObjectImage(g1c1, g1c1animationfileleft[6]);
		}
		else  if (g1c1animationcache >= 7 && g1c1animationcache < 8) {
			setObjectImage(g1c1, g1c1animationfileleft[7]);
		}
		else  if (g1c1animationcache >= 8 && g1c1animationcache < 9) {
			setObjectImage(g1c1, g1c1animationfileleft[8]);
		}
		else  if (g1c1animationcache >= 9 && g1c1animationcache < 10) {
			setObjectImage(g1c1, g1c1animationfileleft[9]);
		}

		

	}
	else if (g1c1heading == 3) {//오른쪽
		g1c1animationcache = fmod(g1c1animationcache1, 10);
		if (g1c1animationcache >= 0 && g1c1animationcache < 1) {
			setObjectImage(g1c1, g1c1animationfileright[0]);
		}
		else  if (g1c1animationcache >= 1 && g1c1animationcache < 2) {
			setObjectImage(g1c1, g1c1animationfileright[1]);
		}
		else  if (g1c1animationcache >= 2 && g1c1animationcache < 3) {
			setObjectImage(g1c1, g1c1animationfileright[2]);
		}
		else  if (g1c1animationcache >= 3 && g1c1animationcache < 4) {
			setObjectImage(g1c1, g1c1animationfileright[3]);
		}
		else  if (g1c1animationcache >= 4 && g1c1animationcache < 5) {
			setObjectImage(g1c1, g1c1animationfileright[4]);
		}
		else  if (g1c1animationcache >= 5 && g1c1animationcache < 6) {
			setObjectImage(g1c1, g1c1animationfileright[5]);
		}
		else  if (g1c1animationcache >= 6 && g1c1animationcache < 7) {
			setObjectImage(g1c1, g1c1animationfileright[6]);
		}
		else  if (g1c1animationcache >= 7 && g1c1animationcache < 8) {
			setObjectImage(g1c1, g1c1animationfileright[7]);
		}
		else  if (g1c1animationcache >= 8 && g1c1animationcache < 9) {
			setObjectImage(g1c1, g1c1animationfileright[8]);
		}
		else  if (g1c1animationcache >= 9 && g1c1animationcache < 10) {
			setObjectImage(g1c1, g1c1animationfileright[9]);
		}
	}
		g1c1animationcache1 = g1c1animationcache1 + 0.5;

	
}

void g1obj1firstposition() {// 리턴 해주어야 하나?.. i가 가로j가 세로
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 6; j++) {			
			obj1x[j][i] =0;
			obj1y[j][i] =0;
		}
	}
	for (int i = 0; i < 10; i++) {
		obj1x[0][i] = i * 128 ;
		obj1y[0][i] = 721; //-------------
		
	}
	for (int j = 0; j < 6; j++) {
		//|           |
		//|           |
		obj1x[j][0] = 0 - g1_obj1_size_width;
		obj1y[j][0] = 720 - j * 120;
		
		obj1x[j][9] = 1281;
		obj1y[j][9] = 720 - j * 120;
		
	}
	for (int i = 0; i < 10; i++) {
		obj1x[5][i] = i * 128;
		obj1y[5][i] = 0 - g1_obj1_size_hight; //-------------
		
	}
}
void g1obj1_1firstposition() {
	srand((unsigned int)time(NULL) );
	for (int i = 0; i < 30; i++) {

		
		int num = rand();
		int g1obj1_1place = num % 4;
		int g1obj1_1placernd = num % 7;
		if (g1obj1_1place == 0) { //동
			obj1_1x[i] = 1281;
			obj1_1y[i] = 30+50* g1obj1_1placernd;
		}
		else if (g1obj1_1place == 1) {//서
			obj1_1x[i] = -15;
			obj1_1y[i] = 30 + 50 * g1obj1_1placernd;
		}
		else if (g1obj1_1place == 2) {//남
			obj1_1x[i] = 50 + 150 * g1obj1_1placernd;
			obj1_1y[i] = -15;
		}
		else if (g1obj1_1place == 3) {//북
			obj1_1x[i] = 50 + 150 * g1obj1_1placernd;
			obj1_1y[i] = 721;
		}
		

	}
}

void g1clearobj() {
	
	for (int i = g1difficulty; i < 30; i++) {
		hideObject(g1obj1_1[i]);
		

	}
	
}

void g1obj1movepinpoint() {//중앙의 540*360 안의 사각형을 무조건 지나면서 이동
	srand((unsigned int)time(NULL));
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 6; j++) {
			if (obj1x[j][i] == 0 && obj1y[j][i] == 0) {//pass 요거는 가장자리에 있는 거 만 포인트를 정해주고 안쪽에 있는거는 무시
			}
			else if (obj1x[j][i] > 0 && obj1y[j][i]<720 && obj1x[j][i] < 1280 && obj1y[j][i] > 0) {//화면 안에 있을때는 할 필요 없음
			}
			else {
				
				int num = rand();
				int rndvaluex = (num % 18)*30;//가로 540
				int rndvaluey = (num % 12)*30;//세로 360
				double distance;
				double ratio;

				distance = sqrt((rndvaluex+270 - obj1x[j][i]) * (rndvaluex+270 - obj1x[j][i]) + (rndvaluey+180 - obj1y[j][i]) * (rndvaluey+180 - obj1y[j][i]));
				ratio = distance / obj1speed;
				g1obj1moveblockx[j][i] = (rndvaluex+270 - obj1x[j][i]) / ratio;
				g1obj1moveblocky[j][i] = (rndvaluey+180 - obj1y[j][i]) / ratio;
				
			}
		}
	}
	for (int i = 0; i < 30; i++) {

		if (obj1_1x[i] > 0 && obj1_1y[i] < 720 && obj1_1x[i] < 1280 && obj1_1y[i] > 0) {
		}
		else {
			
			int num = rand();
			int rndvaluex = (num % 9) * 60;//가로 540
			int rndvaluey = (num % 6) * 60;//세로 360
			double distance;
			double ratio;

			distance = sqrt((rndvaluex + 270 - obj1_1x[i]) * (rndvaluex + 270 - obj1_1x[i]) + (rndvaluey + 180 - obj1_1y[i]) * (rndvaluey + 180 - obj1_1y[i]));
			ratio = distance / obj1_1speed;
			g1obj1_1moveblockx[i] = (rndvaluex + 270 - obj1_1x[i]) / ratio;
			g1obj1_1moveblocky[i] = (rndvaluey + 180 - obj1_1y[i]) / ratio;

		}
	}
}
void g1obj1move() {
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 6; j++) {
			if (obj1x[j][i] == 0 && obj1y[j][i]==0) {//pass
			}
			else {
				obj1x[j][i] += g1obj1moveblockx[j][i];
				obj1y[j][i] += g1obj1moveblocky[j][i];
				if (g1obj1moveblockx[j][i] > 0) {
					setObjectImage(g1obj1[j][i], "image/game1/부끄부끄/130-1.png");
				}
				else {
					setObjectImage(g1obj1[j][i], "image/game1/부끄부끄/130+1.png");
				}
			}
		}
	}
	for (int i = 0; i < 30; i++) {
		obj1_1x[i] += g1obj1_1moveblockx[i];
		obj1_1y[i] += g1obj1_1moveblocky[i];
		if (g1obj1_1moveblockx[i] > 0) {
			setObjectImage(g1obj1_1[i], "image/game1/부끄부끄/131-1.png");
		}
		else {
			setObjectImage(g1obj1_1[i], "image/game1/부끄부끄/131+1.png");
		}
	}
	
}

void g1obj1locate() {
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 6; j++) {
			if (obj1x[j][i] == 0 && obj1y[j][i] == 0) {//pass
			}
			else {
				
				locateObject(g1obj1[j][i], scene_g1, obj1x[j][i], obj1y[j][i]);
			}
		}
	}
	for (int i = 0; i < 30; i++) {
		
		locateObject(g1obj1_1[i], scene_g1, obj1_1x[i], obj1_1y[i]);
	}

}

void score(){
	stopTimer(g1score);
	double g1result;
	g1result = getTimer(g1score);
	highscore_g1 = 9999 - g1result;
	char buf[256];
	//sprintf_s(buf, "버틴시간 : %0.f초\n", (9999-g1result), scene_g1);
	//showMessage(buf);

	getCoin = (int)(9999 - g1result) * 2;

	sprintf_s(buf, "%d 코인 획득!\n", getCoin, scene_g1);
	showMessage(buf);

	coin += getCoin;

}

void g1death() {
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 6; j++) {
			if ((g1c1x < (obj1x[j][i] + g1_obj1_size_width)) && (g1c1x + g1_character_size_x > obj1x[j][i]) && (g1c1y < (obj1y[j][i] + g1_obj1_size_hight)) && (g1c1y + g1_character_size_y > obj1y[j][i])) {
				stopTimer(g1timer1);
				stopTimer(g1c1move);
				stopTimer(g1difficult);
				playSound(g1deadsound);
				showMessage("end");
				score();
				//savedata_g1();
				showObject(g1restartbutton);
				showObject(g1goMapButton);
			}
			
		}
	}
	for (int i = 0; i < g1difficulty; i++) {

		if ((g1c1x < (obj1_1x[i] + 10)) && (g1c1x + g1_character_size_x > obj1_1x[i]) && (g1c1y < (obj1_1y[i] + 10)) && (g1c1y + g1_character_size_y > obj1_1y[i])) {
			stopTimer(g1timer1);
			stopTimer(g1c1move);
			stopTimer(g1difficult);
			playSound(g1deadsound);
			showMessage("end1");
			score();
			//savedata_g1();
			showObject(g1restartbutton);
			showObject(g1goMapButton);
		}
	}
}
	
void g1update() {
	g1obj1movepinpoint();
	g1obj1move();
	g1obj1locate();
	g1death();
}

void g1restart() {
	g1difficulty = 0;
	g1c1x = 540, g1c1y = 360;
	locateObject(g1c1, scene_g1, g1c1x, g1c1y);
	g1clearobj();

	g1obj1firstposition();
	g1obj1_1firstposition();

	g1obj1locate();
	startTimer(g1c1move);
	startTimer(g1timer1);
	startTimer(g1difficult);
}


//g1difficulty++;
//setTimer(g1levelupgrade, 0.01f);


void Game1_mouseCallback(ObjectID object, int x, int y, MouseAction action) {


		if (object == g1startbutton) {
			
			playSound(buttonClickSound); 
			g1difficulty = 0;
			g1c1x = 540, g1c1y = 360;
			locateObject(g1c1, scene_g1, g1c1x, g1c1y);
			g1clearobj();
			startTimer(g1c1move);
			//g1objmovepinpoint();
			startTimer(g1timer1);
			setTimer(g1difficult, 1.0f);
			startTimer(g1difficult);
			hideObject(g1goMapButton);
			hideObject(g1startbutton);
			hideObject(g1restartbutton);
			///savedata_g1();

			playSound(buttonClickSound);

			setTimer(g1score, 9999);
			//showTimer(g1score);
			startTimer(g1score);
			

		}
		else if (object == g1restartbutton) {
			
			playSound(buttonClickSound);
			g1restart();
			hideObject(g1goMapButton);
			hideObject(g1restartbutton);
			setTimer(g1score, 9999);
			//showTimer(g1score);
			startTimer(g1score);
			startTimer(g1difficult);
		}
		else if (object == g1goMapButton) {
			playSound(buttonClickSound);
			g1c1x = 540, g1c1y = 360;
			locateObject(g1c1, scene_g1, g1c1x, g1c1y);

			g1obj1firstposition();
			g1obj1_1firstposition();

			g1obj1locate();

			hideObject(g1restartbutton);
			showObject(g1startbutton);

			stopTimer(g1timer1);
			stopTimer(g1c1move);
			stopTimer(g1levelupgrade);
			stopTimer(g1score);
			stopTimer(g1difficult);
			stopSound(bgm_g1); 
			//readdata_g1();
			enterTitle(0);

		}
	}
		

void Game1_timerCallback(TimerID timer) {// 크리에이트 타이머!!!!!!!!!!!
	if (timer == g1timer1) {//장애물움직이는거 전용
		
		setTimer(g1timer1, 0.01f);
		startTimer(g1timer1);
		g1update();
		
		
		

	}
	if (timer == g1c1move) {//캐릭터움직이는거 전용
	/*else if (g1c1x < 0 - g1_character_size_x + 1 || g1c1x > 1280 || g1c1y < 0 - g1_character_size_y + 1 || g1c1y > 720) {
		stopTimer(g1timer1);
		stopTimer(g1c1move);
		stopTimer(g1difficult);
		playSound(g1deadsound);
		showMessage("out of bounds");
		score();
		showObject(g1restartbutton);
	}*/
		
		g1c1x += g1dx; g1c1y += g1dy;

		if (g1c1x < 0 + g1_character_size_x-40 + 1 || g1c1x > 1250 || g1c1y < 0 + g1_character_size_y -50 + 1 || g1c1y > 680){
			g1c1x -= g1dx; g1c1y -= g1dy;
		}

		g1c1animation();
		locateObject(g1c1, scene_g1, g1c1x, g1c1y);
		setTimer(g1c1move, 0.01f);
		startTimer(g1c1move);
		
	}
	if (timer == g1levelupgrade) {//캐릭터움직이는거 전용		
		startTimer(g1levelupgrade);
	}
	if (timer == g1score) {
		
	}
	if (timer == g1difficult) {
		g1obj1_1[g1difficulty] = g1createObject("image/game1/부끄부끄/131-1.png", scene_g1, obj1_1x[g1difficulty], obj1_1y[g1difficulty], true);
		scaleObject(g1obj1_1[g1difficulty], 0.2f);

		g1difficulty++;
		setTimer(g1difficult, 2.f);
		startTimer(g1difficult);
	}
}
void Game1_soundCallback(SoundID sound) {
	if (sound == bgm_g1) {
		
			playSound(bgm_g1);
		
	}

}
void Game1_keyboardCallback(KeyCode code, KeyState state)
{
	if (nowGameSceneNum == 1) {

		if (code == 84) {			// UP
			g1dy += (state == KeyState::KEYBOARD_PRESSED ? speed : -speed);
			//g1c1heading = 1;
		}
		else if (code == 85) {		// DOWN
			g1dy -= (state == KeyState::KEYBOARD_PRESSED ? speed : -speed);
			//g1c1heading = 0;
		}
		else if (code == 83) {		// RIGHT
			g1dx += (state == KeyState::KEYBOARD_PRESSED ? speed : -speed);
			g1c1heading = 3;
		}
		else if (code == 82) {		// LEFT
			g1dx -= (state == KeyState::KEYBOARD_PRESSED ? speed : -speed);
			g1c1heading = 2;
		}
	}
}

	


void Game1_main() {

	setGameOption(GameOption::GAME_OPTION_INVENTORY_BUTTON, false);
	setGameOption(GameOption::GAME_OPTION_MESSAGE_BOX_BUTTON, false);
	
	
	scene_g1 = createScene("STGAE4 유령의 집", "image/game1/배경.png");

	g1c1 = g1createObject("image/game1/마리오오른쪽/마리오 애니메이션1.png", scene_g1, g1c1x, g1c1y, true);	
	scaleObject(g1c1, 0.5f);
	
	
	g1obj1firstposition();
	g1obj1_1firstposition();

	g1startbutton = g1createObject("image/game1/start.png", scene_g1, 520, 320, true);
	g1restartbutton = g1createObject("image/game1/restart.png", scene_g1, 500, 330, false);


	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 6; j++) {
			g1obj1[j][i] = g1createObject("image/game1/부끄부끄/130-1.png", scene_g1, obj1x[j][i], obj1y[j][i], true);
			scaleObject(g1obj1[j][i], 0.2f);
		}
	}
	
	g1goMapButton = g1createObject("image/game6/goMap.png", scene_g1, 20, 20, true);
	
	g1timer1 = createTimer(0.01f);
	g1c1move = createTimer(0.01f);
	g1score = createTimer(100);
	g1difficult = createTimer(4.f);
	bgm_g1 = createSound("sounds/배경음/유령의집.mp3");
	g1deadsound = createSound("sounds/공통/죽을때.mp3");
}