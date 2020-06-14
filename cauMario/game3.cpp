#include <bangtal.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

extern SceneID titleScene;
extern SoundID buttonClickSound;
SceneID scene1_g3, scene2_g3;
ObjectID startbutton_g3, restartbutton_g3, endbutton_g3, normal, blue, red, yellow, heart1_g3, heart2_g3, heart3_g3, damaged_g3;
ObjectID enemy[150] = { 0, };
TimerID enemyMove, damageTime_g3;
SoundID bgm_g3, finalHit_g3, finalHit1_g3, normalHit_g3, normalHit1_g3, normalHit2_g3, normalHit3_g3, normalHit4_g3, fail_g3;
int pattern[150] = { 0, }, Elife[150] = { 0, }, locate[150] = { 0, };
int count_g3 = 0, clear_g3 = 0, life_g3 = 3, location = 60, NhitCount_g3 = 0, FhitCount_g3 = 0, score_g3 = 0;
char name[30] = { 0, }, info_g3[30] = { 0, };
float duration_g3 = 0.8f;

extern int coin;

extern void enterTitle(int clearScene);

ObjectID createObject_g3(const char* image, SceneID scene, int x, int y, bool shown) {

	ObjectID object = createObject(image);

	locateObject(object, scene, x, y);

	if (shown) {
		showObject(object);
	}

	return object;
}

void patternMaker_g3() {		// 적 특성 저장할 정수 배열 만들기

	int i, x, y, temp;

	srand(time(NULL));

	//1~4까지는 목숨하나 몹 차례대로 N,B,R,Y
	//5~8까지는 목숨 여러개 몹 차례대로 N,B,R,Y

	for (i = 0; i < 32; i++) {
		if (i < 5) pattern[i] = 1;
		else if (i < 10) pattern[i] = 2;
		else if (i < 15) pattern[i] = 3;
		else if (i < 20) pattern[i] = 4;
		else if (i < 22) pattern[i] = 5;
		else if (i < 24) pattern[i] = 6;
		else if (i < 26) pattern[i] = 7;
		else if (i < 28) pattern[i] = 8;
		else if (i < 32) pattern[i] = 0;
	}

	for (i = 0; i < 300; i++) {
		x = rand() % 32;
		y = rand() % 32;

		if (x != y) {
			temp = pattern[x];
			pattern[x] = pattern[y];
			pattern[y] = temp;
		}
	}
}

void enemyLife_g3() {			// 적 목숨 랜덤 설정

	srand(time(NULL));

	for (int i = 0; i < 32; i++) {
		if (pattern[i] == 5 || pattern[i] == 6 || pattern[i] == 7 || pattern[i] == 8) {
			Elife[i] = rand() % 3 + 2;
		}
	}
}

void createEnemy_g3() {		// 적 오브젝트 생성

	int i;

	for (i = 0; i < 32; i++) {

		if (pattern[i] != 0) {
			sprintf_s(name, "image/game3/%d.png", pattern[i]);
			enemy[i] = createObject_g3(name, scene2_g3, 610, 720, false);
		}
	}
}

void ending_g3() {		//게임 클리어 후 처리

	stopTimer(enemyMove);

	for (int i = 0; i < 32; i++) {
		if (pattern[i] != 0) hideObject(enemy[i]);
	}

	sprintf_s(info_g3, "%d 코인 획득!", score_g3);
	showMessage(info_g3);

	coin += score_g3;

	showObject(restartbutton_g3);
	showObject(endbutton_g3);

}

void minusHeart_g3() {			// 오답 시 목숨 감소

	life_g3--;
	showObject(damaged_g3);
	playSound(fail_g3);

	setTimer(damageTime_g3, 0.2f);
	startTimer(damageTime_g3);

	if (life_g3 == 2) hideObject(heart3_g3);
	else if (life_g3 == 1) hideObject(heart2_g3);
	else if (life_g3 == 0) {
		hideObject(heart1_g3);
		ending_g3();
	}
}

void zeroCheck_g3() {			// 다음 오브젝트가 없을 때 변수 clear 증가 함수
	if (clear_g3 != 32 && pattern[clear_g3] == 0) {
		clear_g3++;
		if (pattern[clear_g3] != 0) return;
		zeroCheck_g3();
	}
}

void normalHitPlay_g3() {		// 평타 효과음 재생
	switch (NhitCount_g3) {
	case 0:
		playSound(normalHit_g3, false);
		NhitCount_g3++;
		break;
	case 1:
		playSound(normalHit1_g3, false);
		NhitCount_g3++;
		break;
	case 2:
		playSound(normalHit2_g3, false);
		NhitCount_g3++;
		break;
	case 3:
		playSound(normalHit3_g3, false);
		NhitCount_g3++;
		break;
	case 4:
		playSound(normalHit4_g3, false);
		NhitCount_g3 = 0;
		break;
	}
}

void finalHitPlay_g3() {		// 막타 효과음 재생
	switch (FhitCount_g3) {
	case 0:
		playSound(finalHit_g3, false);
		FhitCount_g3++;
		break;
	case 1:
		playSound(finalHit1_g3, false);
		FhitCount_g3 = 0;
		break;
	}
}


void judge_g3(int num1, int num2) {	// 클릭 시 정,오답 확인

	if (clear_g3 == 32) return;
	else if (life_g3 == 0) return;
	else if (pattern[clear_g3] == num1) {
		hideObject(enemy[clear_g3]);
		clear_g3++;
		zeroCheck_g3();
		normalHitPlay_g3();
		score_g3++;
	}
	else if (pattern[clear_g3] == num2) {
		Elife[clear_g3]--;
		if (Elife[clear_g3] != 0) {
			normalHitPlay_g3();
		}
		if (Elife[clear_g3] == 0) {
			hideObject(enemy[clear_g3]);
			clear_g3++;
			zeroCheck_g3();
			finalHitPlay_g3();
			score_g3++;
		}
	}
	else {
		minusHeart_g3();
	}
}

void Game3_mouseCallback(ObjectID object, int x, int y, MouseAction action) {

	if (object == startbutton_g3) {
		playSound(buttonClickSound);
		enterScene(scene2_g3);

		patternMaker_g3();
		enemyLife_g3();
		createEnemy_g3();

		zeroCheck_g3();

		showObject(heart1_g3);
		showObject(heart2_g3);
		showObject(heart3_g3);


		setTimer(enemyMove, duration_g3);
		startTimer(enemyMove);
	}

	else if (object == restartbutton_g3) {
		playSound(buttonClickSound);
		for (int i = 0; i < 150; i++) enemy[i] = 0;
		for (int i = 0; i < 150; i++) pattern[i] = 0;
		for (int i = 0; i < 150; i++) Elife[i] = 0;
		for (int i = 0; i < 150; i++) locate[i] = 0;
		for (int i = 0; i < 30; i++) name[i] = 0;
		count_g3 = 0;
		clear_g3 = 0;
		life_g3 = 3;
		score_g3 = 0;
		duration_g3 = 1.0f;

		patternMaker_g3();
		enemyLife_g3();
		createEnemy_g3();

		showObject(heart1_g3);
		showObject(heart2_g3);
		showObject(heart3_g3);

		hideObject(restartbutton_g3);
		hideObject(endbutton_g3);

		zeroCheck_g3();

		setTimer(enemyMove, duration_g3);
		startTimer(enemyMove);
	}

	else if (object == endbutton_g3) {
		playSound(buttonClickSound);

		for (int i = 0; i < 150; i++) enemy[i] = 0;
		for (int i = 0; i < 150; i++) pattern[i] = 0;
		for (int i = 0; i < 150; i++) Elife[i] = 0;
		for (int i = 0; i < 150; i++) locate[i] = 0;
		for (int i = 0; i < 30; i++) name[i] = 0;
		count_g3 = 0;
		clear_g3 = 0;
		life_g3 = 3;
		score_g3 = 0;

		hideObject(restartbutton_g3);
		hideObject(endbutton_g3);

		stopSound(bgm_g3);

		enterTitle(0);
	}

	else if (object == normal) {

		judge_g3(1, 5);
	}

	else if (object == blue) {

		judge_g3(2, 6);
	}

	else if (object == red) {

		judge_g3(3, 7);
	}

	else if (object == yellow) {

		judge_g3(4, 8);
	}
}

void Game3_timerCallback(TimerID timer) {

	if (timer == enemyMove) {

		if (pattern[count_g3] != 0) {
			showObject(enemy[count_g3]);
		}

		for (int i = 0; i < count_g3 + 1; i++) {
			if (pattern[i] != 0 && i >= clear_g3) {
				locate[i] += location;
				locateObject(enemy[i], scene2_g3, 610, 720 - locate[i]);
				if (locate[i] > 640) {
					life_g3 = 0;
					hideObject(heart1_g3);
					hideObject(heart2_g3);
					hideObject(heart3_g3);
					ending_g3();
					return;
				}
			}
		}

		count_g3++;

		if (clear_g3 == 32) {

			for (int i = 0; i < 150; i++) enemy[i] = 0;
			for (int i = 0; i < 150; i++) pattern[i] = 0;
			for (int i = 0; i < 150; i++) Elife[i] = 0;
			for (int i = 0; i < 150; i++) locate[i] = 0;
			for (int i = 0; i < 30; i++) name[i] = 0;
			count_g3 = 0;
			clear_g3 = 0;
			duration_g3 -= 0.1f;
			patternMaker_g3();
			enemyLife_g3();
			createEnemy_g3();
			zeroCheck_g3();
		}

		setTimer(enemyMove, duration_g3);
		startTimer(enemyMove);
	}

	if (timer == damageTime_g3) {
		hideObject(damaged_g3);
	}
}

void Game3_main() {

	scene1_g3 = createScene("STAGE1 평원", "image/game3/cover.png");
	scene2_g3 = createScene("STAGE1 평원", "image/game3/cover2.png");

	startbutton_g3 = createObject_g3("image/game3/시작.png", scene1_g3, 520, 350, true);
	restartbutton_g3 = createObject_g3("image/game3/다시시작.png", scene2_g3, 480, 380, false);
	endbutton_g3 = createObject_g3("image/game3/goMap.png", scene2_g3, 10, 10, false);
	scaleObject(endbutton_g3, 1.3f);

	heart1_g3 = createObject_g3("image/game3/heart.png", scene2_g3, 830, 650, true);
	scaleObject(heart1_g3, 0.05f);
	heart2_g3 = createObject_g3("image/game3/heart.png", scene2_g3, 900, 650, true);
	scaleObject(heart2_g3, 0.05f);
	heart3_g3 = createObject_g3("image/game3/heart.png", scene2_g3, 970, 650, true);
	scaleObject(heart3_g3, 0.05f);

	normal = createObject_g3("image/game3/N.png", scene2_g3, 370, 40, true);
	blue = createObject_g3("image/game3/B.png", scene2_g3, 470, 40, true);
	red = createObject_g3("image/game3/R.png", scene2_g3, 730, 40, true);
	yellow = createObject_g3("image/game3/Y.png", scene2_g3, 830, 40, true);

	damaged_g3 = createObject_g3("image/game3/damage.png", scene2_g3, 0, 0, false);
	
	bgm_g3 = createSound("sounds/배경음/평원.mp3");
	normalHit_g3 = createSound("image/game3/normalHit.mp3");
	normalHit1_g3 = createSound("image/game3/normalHit1.mp3");
	normalHit2_g3 = createSound("image/game3/normalHit2.mp3");
	normalHit3_g3 = createSound("image/game3/normalHit3.mp3");
	normalHit4_g3 = createSound("image/game3/normalHit4.mp3");
	finalHit_g3 = createSound("image/game3/finalHit.mp3");
	finalHit1_g3 = createSound("image/game3/finalHit1.mp3");
	fail_g3 = createSound("sounds/공통/오답.mp3");

	enemyMove = createTimer(duration_g3);
	damageTime_g3 = createTimer(0.2f);
}