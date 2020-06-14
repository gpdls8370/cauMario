#include <bangtal.h>
#include <stdio.h>
#include <stdlib.h>

#define PLAYER_ANIMATION_TIME		0.05f
#define monster2_ANIMATION_TIME		0.15f
#define PLAYER_SPEED				13
#define monster2_SPEED				1
#define monster2_NUMBER				13
#define ENDmonster2_STATE			3	//마지막 몬스터 레벨(게임 끝나는 레벨)
#define PLAYER_IMAGE_SIZE			100
#define monster2_IMAGE_SIZE			100
#define GAP							10

extern SceneID scene_g63, titleScene;
SceneID scene_g62;
ObjectID startButton_g62, restartButton_g62, restartButton2_g62, goMapButton_g62;
ObjectID player_g62;
ObjectID monster2[monster2_NUMBER];
ObjectID countDown2;
TimerID countDown2Timer, playTimer_g62, monster2Timer_g62, growUpTimer_g62;
extern SoundID bgm_g6, countDownSound_g6, catchSound1_g6, catchSound2_g6, gameOverSound, gameClearSound_g6, growUpSound_g6, buttonClickSound;

extern void enterTitle(int clearScene);
extern int nowGame6Stage, nowGameSceneNum;
int playerX_g62 = 100, playerY_g62 = 350;
int setMonster2X[monster2_NUMBER] = { 600,600,600,600,1100,1100,  350,350,350,850,850,850,  1070 };
int setMonster2Y[monster2_NUMBER] = { 630,450,250,50,500,200,    550,350,150,550,350,150,   310 };
int monster2X[monster2_NUMBER], monster2Y[monster2_NUMBER];
int dx_g62 = 0, dy_g62 = 0, dmx_g62 = 0, dmy_g62 = 0;

int playerState_g62 = 1;	//플레이어 상태(크기) : 처음은 1단계
int monster2State[monster2_NUMBER] = { 1,1,1,1,1,1, 2,2,2,2,2,2, 3 };	//몬스터 상태
int monster2Number[ENDmonster2_STATE] = { 6,6,1 };		//state별 몬스터 마리수
float monster2Size[monster2_NUMBER] = { 70,70,70,70,70,70, 100,100,100,100,100,100, 160 };
float playerSize_g62 = monster2Size[0];

bool monster2IsShown[monster2_NUMBER];

extern int num;
int monster2Count = 0;
int countDown2Num = 1;
int nowState_g62 = 1;
int growUpCount_g62 = 0;

extern ObjectID createObject(const char* name, SceneID scene, int x, int y, bool shown, float size);

extern int random();

void restart_g62() {

	playerX_g62 = 100, playerY_g62 = 350;
	dx_g62 = 0, dy_g62 = 0, dmx_g62 = 0, dmy_g62 = 0;

	playerState_g62 = 1;
	playerSize_g62 = monster2Size[0];

	monster2Count = 0;
	countDown2Num = 1;
	nowState_g62 = 1;
	growUpCount_g62 = 0;

	setTimer(countDown2Timer, 0.7f);
	setObjectImage(countDown2, "image/game6/3.png");

	locateObject(player_g62, scene_g62, playerX_g62, playerY_g62);
	scaleObject(player_g62, (float)playerSize_g62 / PLAYER_IMAGE_SIZE);
	showObject(player_g62);

	//몬스터 스폰
	for (int i = 0; i < monster2_NUMBER; i++) {
		monster2X[i] = setMonster2X[i], monster2Y[i] = setMonster2Y[i];
		locateObject(monster2[i], scene_g62, monster2X[i], monster2Y[i]);
		showObject(monster2[i]);
		monster2IsShown[i] = true;
	}

}

void gameClear_g62() {

	playSound(gameClearSound_g6);

	stopTimer(countDown2Timer);
	stopTimer(monster2Timer_g62);
	stopTimer(playTimer_g62);
	stopTimer(growUpTimer_g62);

	nowGame6Stage = 3;
	showMessage("2 스테이지 클리어");

	enterScene(scene_g63);
}

void gameOver_g62() {

	playSound(gameOverSound);

	hideObject(player_g62);
	stopTimer(countDown2Timer);
	stopTimer(monster2Timer_g62);
	stopTimer(playTimer_g62);
	stopTimer(growUpTimer_g62);


	for (int i = 0; i < monster2_NUMBER; i++) {
		hideObject(monster2[i]);
	}

	hideObject(restartButton2_g62);
	showObject(restartButton_g62);
	showObject(goMapButton_g62);
}

void growUp_g62() {

	playSound(growUpSound_g6);

	startTimer(growUpTimer_g62);
}

void Game62_mouseCallback(ObjectID object, int x, int y, MouseAction action) {

	if (object == startButton_g62) {		//타이머 켜지면서(오브젝트 이동 시작) 게임시작
		playSound(countDownSound_g6);
		showObject(restartButton2_g62);
		showObject(countDown2);
		startTimer(countDown2Timer);
		hideObject(startButton_g62);
		hideObject(goMapButton_g62);
	}

	else if (object == restartButton_g62 || object == restartButton2_g62) {
		stopTimer(monster2Timer_g62);
		restart_g62();
		playSound(countDownSound_g6);
		showObject(restartButton2_g62);
		showObject(countDown2);
		startTimer(countDown2Timer);
		hideObject(restartButton_g62);
		hideObject(goMapButton_g62);
	}

	else if (object == goMapButton_g62) {
		playSound(buttonClickSound);
		stopSound(bgm_g6);
		enterTitle(0);
	}
}

void Game62_keyboardCallback(KeyCode code, KeyState state)
{
	if (nowGameSceneNum == 6) {

		if (code == 84) {			// UP
			dy_g62 += (state == KeyState::KEYBOARD_PRESSED ? PLAYER_SPEED : -PLAYER_SPEED);
		}
		else if (code == 85) {		// DOWN
			dy_g62 -= (state == KeyState::KEYBOARD_PRESSED ? PLAYER_SPEED : -PLAYER_SPEED);
		}
		else if (code == 83) {		// RIGHT
			setObjectImage(player_g62, "image/game6/날개마리오우.png");
			dx_g62 += (state == KeyState::KEYBOARD_PRESSED ? PLAYER_SPEED : -PLAYER_SPEED);
		}
		else if (code == 82) {		// LEFT
			setObjectImage(player_g62, "image/game6/날개마리오좌.png");
			dx_g62 -= (state == KeyState::KEYBOARD_PRESSED ? PLAYER_SPEED : -PLAYER_SPEED);
		}
	}

}

void Game62_timerCallback(TimerID timer)
{

	if (timer == countDown2Timer) {
		countDown2Num++;
		playSound(countDownSound_g6);

		if (countDown2Num == 2) {
			setObjectImage(countDown2, "image/game6/2.png");
			setTimer(timer, 0.7f);
			startTimer(timer);
		}
		else if (countDown2Num == 3) {
			setObjectImage(countDown2, "image/game6/1.png");
			setTimer(timer, 0.7f);
			startTimer(timer);
		}
		else {
			hideObject(countDown2);
			startTimer(playTimer_g62);
			startTimer(monster2Timer_g62);
		}
	}

	//공 조작
	if (timer == playTimer_g62) {
		if (playerX_g62 + dx_g62 > 1280 - playerSize_g62 || playerX_g62 + dx_g62 < 0 || playerY_g62 + dy_g62 > 720 - playerSize_g62 || playerY_g62 + dy_g62 < 0) {}	//테두리 나가면 이동 안시키기

		else {
			playerX_g62 += dx_g62; playerY_g62 += dy_g62;
			locateObject(player_g62, scene_g62, playerX_g62, playerY_g62);
		}
		for (int i = 0; i < monster2_NUMBER; i++) {
			if (monster2IsShown[i] == true) {			//죽은(안보이는) 몬스터에는 반응x
				if (monster2X[i] - playerX_g62 <= playerSize_g62 - GAP && monster2X[i] - playerX_g62 >= -monster2Size[i] + GAP &&		//플레이어가 몬스터랑 x축 부딪히고
					monster2Y[i] - playerY_g62 <= playerSize_g62 - GAP && monster2Y[i] - playerY_g62 >= -monster2Size[i] + GAP) {		//y축도 부딪히면

					if (playerState_g62 == monster2State[i]) {		//부딪혔는데 레벨이 똑같으면
						
						hideObject(monster2[i]);					//몬스터 죽임
						monster2IsShown[i] = false;				//안보이는 상태임을 배열에 저장
						monster2Count++;
						
						if (monster2Count % 2 == 0)
							playSound(catchSound1_g6);
						else
							playSound(catchSound2_g6);

						if (monster2Count == monster2Number[playerState_g62 - 1]) {				//지금 레벨 몬스터 다 죽이면
							if (playerState_g62 != ENDmonster2_STATE) {						//클리어가 아니면
								nowState_g62 = playerState_g62;
								growUpCount_g62 = 0;
								growUp_g62();

								if (playerState_g62 == 1) //1레벨이었으면
									playerSize_g62 = monster2Size[monster2Number[playerState_g62]];			//플레이어 사이즈 다음 레벨 몬스터와 같게 만들고
								else //2레벨이었으면
									playerSize_g62 = monster2Size[monster2_NUMBER - 1];

								playerState_g62++;													//플레이어 레벨 올림
								scaleObject(player_g62, (float)playerSize_g62 / PLAYER_IMAGE_SIZE);		//플레이어 사이즈 바꿔줌
								monster2Count = 0;
							}
							else {															//	<게임클리어>
								gameClear_g62();
								return;
							}
						}
					}

					else {										//부딪혔는데 몬스터 레벨이 더 크면
						gameOver_g62();
						return;
					}
				}
			}
		}

		setTimer(timer, PLAYER_ANIMATION_TIME);
		startTimer(timer);

	}

	//몬스터 랜덤 이동
	if (timer == monster2Timer_g62) {

		for (int j = 0; j < monster2_NUMBER; j++) {
			if (monster2IsShown[j] == true) {			//죽은(안보이는) 몬스터에는 반응x

				random();

				if (num == 0)	//왼쪽 이동
					dmx_g62 -= monster2_SPEED;
				else if (num == 1)	//오른쪽 이동
					dmx_g62 += monster2_SPEED;
				else if (num == 2)	//아래 이동
					dmy_g62 -= monster2_SPEED;
				else if (num == 3)	//위 이동
					dmy_g62 += monster2_SPEED;

				for (int i = 0; i < 32; i++) {
					if (monster2X[j] + dmx_g62 > 1185 || monster2X[j] + dmx_g62 < 15 || monster2Y[j] + dmy_g62 > 635 || monster2Y[j] + dmy_g62 < 15)	//테두리 나가면 이동 안시키기
						break;

					else {
						monster2X[j] += dmx_g62, monster2Y[j] += dmy_g62;
						locateObject(monster2[j], scene_g62, monster2X[j], monster2Y[j]);			//32번 쪼개서 이동
					}
				}
				dmx_g62 = 0, dmy_g62 = 0;	//이동 끝나면 dmx_g62, dmy_g62 초기화
			}
		}
		setTimer(timer, monster2_ANIMATION_TIME);
		startTimer(timer);
	}

	if (timer == growUpTimer_g62) {

		if (growUpCount_g62 % 2 == 0) {

			if (nowState_g62 == 1)
				playerSize_g62 = monster2Size[monster2Number[nowState_g62]];
			else
				playerSize_g62 = monster2Size[monster2_NUMBER - 1];
		}

		else {
			if (nowState_g62 == 1)
				playerSize_g62 = monster2Size[0];
			else
				playerSize_g62 = monster2Size[monster2Number[1]];

		}

		scaleObject(player_g62, (float)playerSize_g62 / PLAYER_IMAGE_SIZE);

		if (growUpCount_g62 < 4) {
			growUpCount_g62++;
			setTimer(growUpTimer_g62, 0.07f);
			startTimer(growUpTimer_g62);
		}
	}
}



void Game62_main()
{
	scene_g62 = createScene("STAGE6-2 하늘 섬", "image/game6/하늘배경.png");
	player_g62 = createObject("image/game6/날개마리오우.png", scene_g62, playerX_g62, playerY_g62, true, (float)playerSize_g62 / PLAYER_IMAGE_SIZE);

	//레벨1 몬스터 스폰
	for (int i = 0; i < monster2Number[0]; i++) {
		monster2X[i] = setMonster2X[i], monster2Y[i] = setMonster2Y[i];
		monster2[i] = createObject("image/game6/날개굼바.png", scene_g62, monster2X[i], monster2Y[i], true, (float)monster2Size[i] / monster2_IMAGE_SIZE);
		monster2IsShown[i] = true;
	}
	//레벨2 몬스터 스폰	
	for (int i = monster2Number[0]; i < monster2Number[0] + monster2Number[1]; i++) {
		monster2X[i] = setMonster2X[i], monster2Y[i] = setMonster2Y[i];
		monster2[i] = createObject("image/game6/날개초록굼바.png", scene_g62, monster2X[i], monster2Y[i], true, (float)monster2Size[i] / monster2_IMAGE_SIZE);
		monster2IsShown[i] = true;
	}
	//레벨3 몬스터 스폰	
	for (int i = monster2Number[0] + monster2Number[1]; i < monster2Number[0] + monster2Number[1] + monster2Number[2]; i++) {
		monster2X[i] = setMonster2X[i], monster2Y[i] = setMonster2Y[i];
		monster2[i] = createObject("image/game6/날개금굼바.png", scene_g62, monster2X[i], monster2Y[i], true, (float)monster2Size[i] / monster2_IMAGE_SIZE);
		monster2IsShown[i] = true;
	}

	startButton_g62 = createObject("image/game6/start.png", scene_g62, 520, 350, true, 1.0f);
	restartButton_g62 = createObject("image/game6/restart.png", scene_g62, 480, 350, false, 1.0f);
	restartButton2_g62 = createObject("image/game6/restart.png", scene_g62, 10, 10, false, 0.5f);
	goMapButton_g62 = createObject("image/game6/goMap.png", scene_g62, 20, 20, true, 1.0f);
	countDown2 = createObject("image/game6/3.png", scene_g62, 570, 300, false, 0.5f);

	playTimer_g62 = createTimer(PLAYER_ANIMATION_TIME);
	monster2Timer_g62 = createTimer(monster2_ANIMATION_TIME);
	countDown2Timer = createTimer(0.7f);
	growUpTimer_g62 = createTimer(0.07f);
}