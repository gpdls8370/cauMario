#include <bangtal.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

extern void enterTitle(int clearScene);
extern SoundID buttonClickSound;
SceneID scene1_g2, scene2_g2;
ObjectID startbutton_g2, restartbutton_g2, endbutton_g2, heart1_g2, heart2_g2, heart3_g2, hiteffect_g2, damaged_g2;
ObjectID target[20] = { 0, };
TimerID appear, hitting, damageTime_g2;
SoundID bgm_g2, normalHit_g2, normalHit1_g2, normalHit2_g2, normalHit3_g2, normalHit4_g2, fail_g2;
int arrX[20] = { 0, }, arrY[20] = { 0, };
int count_g2 = 0, clear_g2 = 0, life_g2 = 3, targetNum = 4, NhitCount_g2 = 0, score_g2 = 0;
char info_g2[50] = { 0, };
float duration_g2 = 1.0f;
bool lock = false;

extern int coin;

ObjectID createObject_g2(const char* image, SceneID scene, int x, int y, bool shown) {

	ObjectID object = createObject(image);

	locateObject(object, scene, x, y);

	if (shown) {
		showObject(object);
	}

	return object;
}

void normalHitPlay_g2() {		// 평타 효과음 재생
	switch (NhitCount_g2) {
	case 0:
		playSound(normalHit_g2, false);
		NhitCount_g2++;
		break;
	case 1:
		playSound(normalHit1_g2, false);
		NhitCount_g2++;
		break;
	case 2:
		playSound(normalHit2_g2, false);
		NhitCount_g2++;
		break;
	case 3:
		playSound(normalHit3_g2, false);
		NhitCount_g2++;
		break;
	case 4:
		playSound(normalHit4_g2, false);
		NhitCount_g2 = 0;
		break;
	}
}

int overlapCheck_g2(int x, int num) {

	for (int i = 0; i < num; i++) {
		if (x + 100 - arrX[i] > -50 && x + 100 - arrX[i] < 50) return 1;
	}
	return 0;
}

void locationMaker_g2(int num) {		// 표적 위치 저장할 정수 배열 만들기 (표적 개수 입력)

	int i, x, y, temp;

	srand(time(NULL));

	x = rand() % 1000;
	y = rand() % 500;

	for (i = 0; i < num; i++) {
		if (i != 0) {
			do {
				x = rand() % 1000;
			} while (overlapCheck_g2(x, i));
			y = rand() % 500;
			
		}

		arrX[i] = 100 + x;
		arrY[i] = 100 + y;

		target[i] = createObject_g2("image/game2/target.png", scene2_g2, arrX[i], arrY[i], false);
	}
}

void clearing_g2() {

	for (int i = 0; i < 20; i++) target[i] = 0;
	for (int i = 0; i < 20; i++) arrX[i] = 0;
	for (int i = 0; i < 20; i++) arrY[i] = 0;

	clear_g2 = 0;
	count_g2 = 0;

	locationMaker_g2(targetNum);
	setTimer(appear, duration_g2);
	startTimer(appear);
}

void ending_g2() {		// 게임 종료

	for (int j = 0; j < targetNum; j++) {	// 다 쓴 타켓 치우기
		hideObject(target[j]);
	}

	sprintf_s(info_g2, "%d 코인 획득!", score_g2);
	showMessage(info_g2);

	coin += score_g2;

	showObject(restartbutton_g2);
	showObject(endbutton_g2);

}

void minusHeart_g2() {			// 오답 시 목숨 감소
	life_g2--;
	playSound(fail_g2);
	if (life_g2 == 2) hideObject(heart3_g2);
	else if (life_g2 == 1) hideObject(heart2_g2);
	else if (life_g2 == 0) {
		hideObject(heart1_g2);
		ending_g2();
	}
}

void judge_g2(ObjectID object, int i) {

	if (object == target[i]) {

		if (clear_g2 == i) {

			normalHitPlay_g2();

			hideObject(target[i]);

			clear_g2++;

			score_g2++;

			locateObject(hiteffect_g2, scene2_g2, arrX[i], arrY[i]);
			showObject(hiteffect_g2);

			setTimer(hitting, 0.5f);
			startTimer(hitting);

			if (clear_g2 == targetNum) {		// 스테이지마다 난이도 상승 조건들

				for (int j = 0; j < targetNum; j++) {	// 다 쓴 타켓 치우기
					hideObject(target[j]);
				}

				if (targetNum < 7) {	// 타겟 수 증가 (최대 7개)
					targetNum++;
				}

				if (duration_g2 > 0.5f) {	// 타겟 등장 주기 감소 (최소 0.5초)
					duration_g2 -= 0.05f;
				}

				clearing_g2();
			}
		}

		else {

			showObject(damaged_g2);
			setTimer(damageTime_g2, 0.2f);
			startTimer(damageTime_g2);

			minusHeart_g2();
		}
	}
}


void Game2_mouseCallback(ObjectID object, int x, int y, MouseAction action) {

	if (lock == true) {
		return;
	}
	
	if (object == startbutton_g2) {

		playSound(buttonClickSound);
		enterScene(scene2_g2);

		locationMaker_g2(targetNum);
		setTimer(appear, duration_g2);
		startTimer(appear);

		showObject(heart1_g2);
		showObject(heart2_g2);
		showObject(heart3_g2);

	}

	else if (object == restartbutton_g2) {
		playSound(buttonClickSound);

		targetNum = 4;
		score_g2 = 0;
		life_g2 = 3;
		duration_g2 = 1.0f;

		showObject(heart1_g2);
		showObject(heart2_g2);
		showObject(heart3_g2);

		hideObject(restartbutton_g2);
		hideObject(endbutton_g2);

		clearing_g2();
	}

	else if (object == endbutton_g2) {
		playSound(buttonClickSound);

		targetNum = 4;
		score_g2 = 0;
		life_g2 = 3;
		duration_g2 = 1.0f;

		hideObject(restartbutton_g2);
		hideObject(endbutton_g2);

		for (int i = 0; i < 20; i++) target[i] = 0;
		for (int i = 0; i < 20; i++) arrX[i] = 0;
		for (int i = 0; i < 20; i++) arrY[i] = 0;

		clear_g2 = 0;
		count_g2 = 0;

		stopSound(bgm_g2);

		enterTitle(0);
	}
	else {											// 무슨 타켓을 클릭했는지 검사
		for (int i = 0; i < targetNum; i++) {
			judge_g2(object, i);
		}
	}

}

void Game2_timerCallback(TimerID timer) {

	if (timer == appear) {
	
		showObject(target[count_g2]);

		count_g2++;
		lock = true;

		if (count_g2 != targetNum) {
			setTimer(appear, duration_g2);
			startTimer(appear);
		}
		else lock = false;
	}

	if (timer == hitting) {
		hideObject(hiteffect_g2);
	}

	if (timer == damageTime_g2) {
		hideObject(damaged_g2);
	}

}
void Game2_main() {

	scene1_g2 = createScene("STAGE3 바다", "image/game2/배경.png");
	scene2_g2 = createScene("STAGE3 바다", "image/game2/배경1.png");

	startbutton_g2 = createObject_g2("image/game2/시작.png", scene1_g2, 530, 350, true);
	restartbutton_g2 = createObject_g2("image/game2/다시시작.png", scene2_g2, 500, 350, false);
	endbutton_g2 = createObject_g2("image/game2/goMap.png", scene2_g2, 10, 10, false);
	scaleObject(endbutton_g2, 1.3f);

	hiteffect_g2 = createObject_g2("image/game2/hit.png", scene2_g2, 610, 400, false);
	damaged_g2 = createObject_g2("image/game2/damage.png", scene2_g2, 0, 0, false);

	heart1_g2 = createObject_g2("image/game2/heart.png", scene2_g2, 830, 650, true);
	scaleObject(heart1_g2, 0.05f);
	heart2_g2 = createObject_g2("image/game2/heart.png", scene2_g2, 900, 650, true);
	scaleObject(heart2_g2, 0.05f);
	heart3_g2 = createObject_g2("image/game2/heart.png", scene2_g2, 970, 650, true);
	scaleObject(heart3_g2, 0.05f);

	bgm_g2 = createSound("sounds/배경음/바다.mp3");
	normalHit_g2 = createSound("image/game2/normalHit.mp3");
	normalHit1_g2 = createSound("image/game2/normalHit1.mp3");
	normalHit2_g2 = createSound("image/game2/normalHit2.mp3");
	normalHit3_g2 = createSound("image/game2/normalHit3.mp3");
	normalHit4_g2 = createSound("image/game2/normalHit4.mp3");
	fail_g2 = createSound("sounds/공통/오답.mp3");

	appear = createTimer(duration_g2);
	hitting = createTimer(0.5f);
	damageTime_g2 = createTimer(0.2f);

	
}