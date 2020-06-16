#include <bangtal.h>
#include <stdio.h>
#include <stdlib.h>

#define PLAYER_ANIMATION_TIME		0.05f
#define monster3_ANIMATION_TIME		0.15f
#define PLAYER_SPEED				13
#define monster3_SPEED				1
#define monster3_NUMBER				12
#define ENDmonster3_STATE			3	//마지막 몬스터 레벨(게임 끝나는 레벨)
#define PLAYER_IMAGE_SIZE			100
#define monster3_IMAGE_SIZE			100
#define GAP							13

extern SceneID titleScene;
SceneID scene_g63;
ObjectID startButton_g63, restartButton_g63, restartButton2_g63, goMapButton_g63;
ObjectID player_g63;
ObjectID monster3[monster3_NUMBER];
ObjectID countDown3;
TimerID countDown3Timer, playTimer_g63, monster3Timer_g63, growUpTimer_g63;
extern SoundID bgm_g6, countDownSound_g6, catchSound1_g6, catchSound2_g6, gameOverSound, gameClearSound, growUpSound_g6, buttonClickSound;

extern void enterTitle(int clearScene);	//클리어시 실행할 함수

extern int nowGameSceneNum;
int playerX_g63 = 600, playerY_g63 = 350;
int setMonster3X[monster3_NUMBER] = { 200,1000,200,1000,  450,750,450,750,  130,580,1040,580 };
int setMonster3Y[monster3_NUMBER] = { 550,550,150,150,    450,450,220,220,  320,570,320,40 };
int monster3X[monster3_NUMBER], monster3Y[monster3_NUMBER];
int dx_g63 = 0, dy_g63 = 0, dmx_g63 = 0, dmy_g63 = 0;

int playerState_g63 = 1;	//플레이어 상태(크기) : 처음은 1단계
int monster3State[monster3_NUMBER] = { 1,1,1,1, 2,2,2,2, 3,3,3,3 };	//몬스터 상태
int monster3Number[ENDmonster3_STATE] = { 4,4,4 };		//state별 몬스터 마리수
float monster3Size[monster3_NUMBER] = { 70,70,70,70, 100,100,100,100, 150,150,150,150 };
float playerSize_g63 = monster3Size[0];

bool monster3IsShown[monster3_NUMBER];

extern int num;
int monster3Count = 0;
int countDown3Num = 1;
int nowState_g63 = 1;
int growUpCount_g63 = 0;
bool stage5Clear = false;

extern ObjectID createObject(const char* name, SceneID scene, int x, int y, bool shown, float size);

extern int random();

void restart_g63() {

	playerX_g63 = 600, playerY_g63 = 350;
	dx_g63 = 0, dy_g63 = 0, dmx_g63 = 0, dmy_g63 = 0;

	playerState_g63 = 1;
	playerSize_g63 = monster3Size[0];

	monster3Count = 0;
	countDown3Num = 1;
	nowState_g63 = 1;
	growUpCount_g63 = 0;

	setTimer(countDown3Timer, 0.7f);
	setObjectImage(countDown3, "image/game6/3.png");

	locateObject(player_g63, scene_g63, playerX_g63, playerY_g63);
	scaleObject(player_g63, (float)playerSize_g63 / PLAYER_IMAGE_SIZE);
	showObject(player_g63);

	//몬스터 스폰
	for (int i = 0; i < monster3_NUMBER; i++) {
		monster3X[i] = setMonster3X[i], monster3Y[i] = setMonster3Y[i];
		locateObject(monster3[i], scene_g63, monster3X[i], monster3Y[i]);
		showObject(monster3[i]);
		monster3IsShown[i] = true;
	}

}


void gameClear_g63() {
	
	stopSound(bgm_g6);
	playSound(gameClearSound);

	stopTimer(countDown3Timer);
	stopTimer(monster3Timer_g63);
	stopTimer(playTimer_g63);
	stopTimer(growUpTimer_g63);

	hideObject(player_g63);

	showMessage("게임 클리어");
	stage5Clear = true;

	hideObject(restartButton2_g63);
	showObject(goMapButton_g63);

}

void gameOver_g63() {
	
	playSound(gameOverSound);

	hideObject(player_g63);			
	stopTimer(countDown3Timer);
	stopTimer(monster3Timer_g63);
	stopTimer(playTimer_g63);
	stopTimer(growUpTimer_g63);
	

	for (int i = 0; i < monster3_NUMBER; i++) {
		hideObject(monster3[i]);
	}

	hideObject(restartButton2_g63);
	showObject(restartButton_g63);
	showObject(goMapButton_g63);
}

void growUp_g63() {

	playSound(growUpSound_g6);

	startTimer(growUpTimer_g63);
}

void Game63_mouseCallback(ObjectID object, int x, int y, MouseAction action) {

	if (object == startButton_g63) {		//타이머 켜지면서(오브젝트 이동 시작) 게임시작
		playSound(countDownSound_g6);
		showObject(restartButton2_g63);
		showObject(countDown3);
		startTimer(countDown3Timer);
		hideObject(startButton_g63);
		hideObject(goMapButton_g63);
	}

	else if (object == restartButton_g63 || object == restartButton2_g63) {
		stopTimer(monster3Timer_g63);
		restart_g63();
		playSound(countDownSound_g6);
		showObject(restartButton2_g63);
		showObject(countDown3);
		startTimer(countDown3Timer);
		hideObject(restartButton_g63);
		hideObject(goMapButton_g63);
	}

	else if (object == goMapButton_g63) {
		playSound(buttonClickSound);
		stopSound(bgm_g6);

		if (stage5Clear == true)
			enterTitle(5);
		else
			enterTitle(0);
	}
}

void Game63_keyboardCallback(KeyCode code, KeyState state)
{
	if (nowGameSceneNum == 6) {
		
		if (code == 84) {			// UP
			dy_g63 += (state == KeyState::KEYBOARD_PRESSED ? PLAYER_SPEED : -PLAYER_SPEED);
		}
		else if (code == 85) {		// DOWN
			dy_g63 -= (state == KeyState::KEYBOARD_PRESSED ? PLAYER_SPEED : -PLAYER_SPEED);
		}
		else if (code == 83) {		// RIGHT
			setObjectImage(player_g63, "image/game6/날개마리오우.png");
			dx_g63 += (state == KeyState::KEYBOARD_PRESSED ? PLAYER_SPEED : -PLAYER_SPEED);
		}
		else if (code == 82) {		// LEFT
			setObjectImage(player_g63, "image/game6/날개마리오좌.png");
			dx_g63 -= (state == KeyState::KEYBOARD_PRESSED ? PLAYER_SPEED : -PLAYER_SPEED);
		}
	}
}

void Game63_timerCallback(TimerID timer)
{

	if (timer == countDown3Timer) {
		countDown3Num++;
		playSound(countDownSound_g6);

		if (countDown3Num == 2) {
			setObjectImage(countDown3, "image/game6/2.png");
			setTimer(timer, 0.7f);
			startTimer(timer);
		}
		else if (countDown3Num == 3) {
			setObjectImage(countDown3, "image/game6/1.png");
			setTimer(timer, 0.7f);
			startTimer(timer);
		}
		else {
			hideObject(countDown3);
			startTimer(playTimer_g63);
			startTimer(monster3Timer_g63);
		}
	}

	//공 조작
	if (timer == playTimer_g63) {
		if (playerX_g63 + dx_g63 > 1280 - playerSize_g63 || playerX_g63 + dx_g63 < 0 || playerY_g63 + dy_g63 > 720 - playerSize_g63 || playerY_g63 + dy_g63 < 0) {}	//테두리 나가면 이동 안시키기

		else {
			playerX_g63 += dx_g63; playerY_g63 += dy_g63;
			locateObject(player_g63, scene_g63, playerX_g63, playerY_g63);
		}
		for (int i = 0; i < monster3_NUMBER; i++) {
			if (monster3IsShown[i] == true) {			//죽은(안보이는) 몬스터에는 반응x
				if (monster3X[i] - playerX_g63 <= playerSize_g63 - GAP && monster3X[i] - playerX_g63 >= -monster3Size[i] + GAP &&		//플레이어가 몬스터랑 x축 부딪히고
					monster3Y[i] - playerY_g63 <= playerSize_g63 - GAP && monster3Y[i] - playerY_g63 >= -monster3Size[i] + GAP) {		//y축도 부딪히면

					if (playerState_g63 == monster3State[i]) {		//부딪혔는데 레벨이 똑같으면
						
						hideObject(monster3[i]);					//몬스터 죽임
						monster3IsShown[i] = false;				//안보이는 상태임을 배열에 저장
						monster3Count++;

						if (monster3Count % 2 == 0)
							playSound(catchSound1_g6);
						else
							playSound(catchSound2_g6);

						if (monster3Count == monster3Number[playerState_g63 - 1]) {				//지금 레벨 몬스터 다 죽이면
							if (playerState_g63 != ENDmonster3_STATE) {						//클리어가 아니면
								nowState_g63 = playerState_g63;
								growUpCount_g63 = 0;
								growUp_g63();

								if (playerState_g63 == 1) //1레벨이었으면
									playerSize_g63 = monster3Size[monster3Number[playerState_g63]];			//플레이어 사이즈 다음 레벨 몬스터와 같게 만들고
								else //2레벨이었으면
									playerSize_g63 = monster3Size[monster3_NUMBER - 1];

								playerState_g63++;													//플레이어 레벨 올림
								scaleObject(player_g63, (float)playerSize_g63 / PLAYER_IMAGE_SIZE);		//플레이어 사이즈 바꿔줌
								monster3Count = 0;
							}
							else {															//	<게임클리어>
								gameClear_g63();
								return;
							}
						}
					}

					else {										//부딪혔는데 몬스터 레벨이 더 크면
						gameOver_g63();
						return;
					}
				}
			}
		}

		setTimer(timer, PLAYER_ANIMATION_TIME);
		startTimer(timer);

	}

	//몬스터 랜덤 이동
	if (timer == monster3Timer_g63) {

		for (int j = 0; j < monster3_NUMBER; j++) {
			if (monster3IsShown[j] == true) {			//죽은(안보이는) 몬스터에는 반응x

				random();

				if (num == 0)	//왼쪽 이동
					dmx_g63 -= monster3_SPEED;
				else if (num == 1)	//오른쪽 이동
					dmx_g63 += monster3_SPEED;
				else if (num == 2)	//아래 이동
					dmy_g63 -= monster3_SPEED;
				else if (num == 3)	//위 이동
					dmy_g63 += monster3_SPEED;

				for (int i = 0; i < 32; i++) {
					if (monster3X[j] + dmx_g63 > 1185 || monster3X[j] + dmx_g63 < 15 || monster3Y[j] + dmy_g63 > 635 || monster3Y[j] + dmy_g63 < 15)	//테두리 나가면 이동 안시키기
						break;

					else {
						monster3X[j] += dmx_g63, monster3Y[j] += dmy_g63;
						locateObject(monster3[j], scene_g63, monster3X[j], monster3Y[j]);			//32번 쪼개서 이동
					}
				}
				dmx_g63 = 0, dmy_g63 = 0;	//이동 끝나면 dmx_g63, dmy_g63 초기화
			}
		}
		setTimer(timer, monster3_ANIMATION_TIME);
		startTimer(timer);
	}

	if (timer == growUpTimer_g63) {

		if (growUpCount_g63 % 2 == 0) {
			
			if (nowState_g63 == 1)
				playerSize_g63 = monster3Size[monster3Number[nowState_g63]];
			else 
				playerSize_g63 = monster3Size[monster3_NUMBER - 1];
		}
			
		else {
			if (nowState_g63 == 1)
				playerSize_g63 = monster3Size[0];
			else 
				playerSize_g63 = monster3Size[monster3Number[1]];

		}

		scaleObject(player_g63, (float)playerSize_g63 / PLAYER_IMAGE_SIZE);

		if (growUpCount_g63 < 4) {
			growUpCount_g63++;
			setTimer(growUpTimer_g63, 0.07f);
			startTimer(growUpTimer_g63);
		}
	}
}



void Game63_main()
{
	scene_g63 = createScene("STAGE6-3 하늘 섬", "image/game6/하늘배경.png");
	player_g63 = createObject("image/game6/날개마리오좌.png", scene_g63, playerX_g63, playerY_g63, true, (float)playerSize_g63 / PLAYER_IMAGE_SIZE);

	//레벨1 몬스터 스폰
	for (int i = 0; i < monster3Number[0]; i++) {
		monster3X[i] = setMonster3X[i], monster3Y[i] = setMonster3Y[i];
		monster3[i] = createObject("image/game6/날개굼바.png", scene_g63, monster3X[i], monster3Y[i], true, (float)monster3Size[i] / monster3_IMAGE_SIZE);
		monster3IsShown[i] = true;
	}
	//레벨2 몬스터 스폰	
	for (int i = monster3Number[0]; i < monster3Number[0] + monster3Number[1]; i++) {
		monster3X[i] = setMonster3X[i], monster3Y[i] = setMonster3Y[i];
		monster3[i] = createObject("image/game6/날개초록굼바.png", scene_g63, monster3X[i], monster3Y[i], true, (float)monster3Size[i] / monster3_IMAGE_SIZE);
		monster3IsShown[i] = true;
	}
	//레벨3 몬스터 스폰	
	for (int i = monster3Number[0] + monster3Number[1]; i < monster3Number[0] + monster3Number[1] + monster3Number[2]; i++) {
		monster3X[i] = setMonster3X[i], monster3Y[i] = setMonster3Y[i];
		monster3[i] = createObject("image/game6/날개금굼바.png", scene_g63, monster3X[i], monster3Y[i], true, (float)monster3Size[i] / monster3_IMAGE_SIZE);
		monster3IsShown[i] = true;
	}

	startButton_g63 = createObject("image/game6/start.png", scene_g63, 520, 280, true, 1.0f);
	restartButton_g63 = createObject("image/game6/restart.png", scene_g63, 480, 350, false, 1.0f);
	restartButton2_g63 = createObject("image/game6/restart.png", scene_g63, 10, 10, false, 0.5f);
	goMapButton_g63 = createObject("image/game6/goMap.png", scene_g63, 20, 20, true, 1.0f);
	countDown3 = createObject("image/game6/3.png", scene_g63, 570, 300, false, 0.5f);

	playTimer_g63 = createTimer(PLAYER_ANIMATION_TIME);
	monster3Timer_g63 = createTimer(monster3_ANIMATION_TIME);
	countDown3Timer = createTimer(0.7f);
	growUpTimer_g63 = createTimer(0.07f);

}