#define _CRT_SECURE_NO_WARNINGS
#include<bangtal.h>
#include <stdio.h>

#define MARIO_ANIMATION_TIME	0.1f



extern SceneID scene_g1, scene1_g2, scene1_g3, scene_g4, scene_g5, scene_g6, scene_g62, scene_g63;

extern SoundID buttonClickSound, gameClearSound, gameOverSound, gameEnterSound;
extern SoundID bgm_g3, g4theme, bgm_g2, bgm_g1, bgm_g5, bgm_g6;

SceneID titleScene;
ObjectID GameIcon[6], GamePopup[6], GameEnterButton[6], maintitle, titlestartbutton, savebutton, explainbutton, explainwindow;
ObjectID Mario, key1, key2, coinImage, xText;
ObjectID coinText[3];
TimerID marioAnimationTimer, titleanimationtimer;
SoundID bgm_title;

int IconX[6] = { 30,22,570,560,1050,1170 };
int IconY[6] = { 115,385,215,565,275,465 };

bool stageLocked[6] = { 0,1,0,1,1,1 };
bool stageBlack[6] = { 0,0,1,1,1,0 };		//0,0,1,1,1,0
int stageUnlockCost[6] = { 0, 30, 0,30,150,0 };	//6번째 : 열쇠 2개 필요
int coin; //점수  코인개수
int key;

int coinNum100, coinNum10, coinNum1;

int nowMarioOn = 0;
int nowGameSceneNum = 0;	//0은 타이틀
extern int nowGame6Stage;
extern bool stage2Clear, stage5Clear;

char path[256];

int marioAnimationCount = 0;
const char* marioAnimationImage[9] =
{ "image/Title/마리오애니/1.png","image/Title/마리오애니/2.png","image/Title/마리오애니/3.png","image/Title/마리오애니/4.png",
"image/Title/마리오애니/5.png","image/Title/마리오애니/6.png","image/Title/마리오애니/7.png","image/Title/마리오애니/8.png","image/Title/마리오애니/9.png" };

int titleanimationx = 0;

extern ObjectID createObject(const char* name, SceneID scene, int x, int y, bool shown, float size);

typedef struct {

	int coin;         //HP

	bool stageBlack[6];

	bool stageLocked[6];

	bool stage2Clear;

	bool stage5Clear;

	int key;

}SaveData_t;

int savedata() {
	SaveData_t Data = { coin,
		stageBlack[0],stageBlack[1],stageBlack[2],stageBlack[3],stageBlack[4],stageBlack[5],
		stageLocked[0],stageLocked[1],stageLocked[2],stageLocked[3],stageLocked[4],stageLocked[5],
		stage2Clear,stage5Clear,key };
	FILE* fp = fopen("c:savedata.dat", "wb");

	if (fp == NULL) {

		return 0;

	}

	fwrite(&Data, sizeof(Data), 1, fp); // SaveData_t구조체 내용을 출력

	fclose(fp);

	return 0;



}

int readdata() {
	SaveData_t Data;

	FILE* fp = fopen("c:savedata.dat", "rb");

	if (fp == NULL) {

		return 0;

	}

	fread(&Data, sizeof(Data), 1, fp);

	fclose(fp);
	coin = Data.coin;
	for (int i = 0; i < 6; i++) {
		stageBlack[i] = Data.stageBlack[i];
	}
	for (int i = 0; i < 6; i++) {
		stageLocked[i] = Data.stageLocked[i];
	}
	stage2Clear = Data.stage2Clear;
	stage5Clear = Data.stage5Clear;

	key = Data.key;

	//printf("HP=%d\nMP=%d\n소지금=%d\n경험치=%d\n",Data.HP, Data.MP, Data.Money, Data.Exp);



	return 0;


	//char buf[256];
	//sprintf_s(buf, "최고 기록 %d", Data.highscore_g1, scene_g1);
	//showMessage(buf);
}

void titleanimation() {
	if (titleanimationx < 1300) {
		titleanimationx = titleanimationx + 25;
		locateObject(maintitle, titleScene, titleanimationx, 0);
	}
	else {
		stopTimer(titleanimationtimer);
	}
}

void showCoinCount() {

	coinNum100 = coin / 100;
	coinNum10 = coin / 10 - coinNum100 * 10;
	coinNum1 = coin - coinNum10 * 10 - coinNum100 * 100;


	if (coin >= 100) {	//3자리 숫자면
		sprintf(path, "image/Title/숫자/%d.png", coinNum100);	//백의 자리
		setObjectImage(coinText[0], path);
		showObject(coinText[0]);

		sprintf(path, "image/Title/숫자/%d.png", coinNum10);	//십의 자리
		setObjectImage(coinText[1], path);
		showObject(coinText[1]);

		sprintf(path, "image/Title/숫자/%d.png", coinNum1);	//일의 자리
		setObjectImage(coinText[2], path);
		showObject(coinText[2]);
	}

	else if (coin >= 10) {	//2자리 숫자면
		sprintf(path, "image/Title/숫자/%d.png", coinNum10);	//십의 자리
		setObjectImage(coinText[0], path);
		showObject(coinText[0]);

		sprintf(path, "image/Title/숫자/%d.png", coinNum1);	//일의 자리
		setObjectImage(coinText[1], path);
		showObject(coinText[1]);

		hideObject(coinText[2]);
	}

	else {
		sprintf(path, "image/Title/숫자/%d.png", coinNum1);	//일의 자리
		setObjectImage(coinText[0], path);
		showObject(coinText[0]);

		hideObject(coinText[1]);
		hideObject(coinText[2]);
	}
}

void exitTitle() {

	setGameOption(GameOption::GAME_OPTION_ROOM_TITLE, true);
	stopTimer(marioAnimationTimer);
	stopSound(bgm_title);

}

void hideUI() {

	for (int i = 0; i < 6; i++) {
		hideObject(GameEnterButton[i]);
		hideObject(GamePopup[i]);
	}
}

//0은 클리어x 2스테이지(사막), 5스테이지(하늘) 받음 
void enterTitle(int clearScene) {

	setGameOption(GameOption::GAME_OPTION_ROOM_TITLE, false);
	showCoinCount();

	hideUI();
	setTimer(marioAnimationTimer, MARIO_ANIMATION_TIME);
	startTimer(marioAnimationTimer);

	playSound(bgm_title);

	//사막지대 클리어했으면
	if (clearScene == 2) {
		setObjectImage(GameIcon[1], "image/Title/초록아이콘.png");
		setObjectImage(GameIcon[2], "image/Title/파란아이콘.png");
		setObjectImage(GameIcon[3], "image/Title/파란아이콘.png");
		stageBlack[2] = false;
		stageBlack[3] = false;

		key = 1;
		setObjectImage(key1, "image/Title/key.png");
	}

	//하늘지대 클리어했으면
	else if (clearScene == 5) {
		setObjectImage(GameIcon[4], "image/Title/초록아이콘.png");

		key = 2;
		setObjectImage(key2, "image/Title/key.png");
	}

	enterScene(titleScene);
}

//0번 2번은 실행 안됨
void stageUnlock(int stage) {

	if (stage != 5) {
		if (coin >= stageUnlockCost[stage]) {

			coin -= stageUnlockCost[stage];		//돈 내고
			showCoinCount();
			stageLocked[stage] = false;			//열림으로 바꿔주고

			sprintf(path, "image/Title/팝업/%d-2.png", stage + 1);
			setObjectImage(GamePopup[stage], path);
			setObjectImage(GameEnterButton[stage], "image/Title/enter.png");
			locateObject(GameEnterButton[stage], titleScene, 950, 100);

			if (stage == 4)
				locateObject(GameEnterButton[stage], titleScene, 70, 100);

		}

		else
			showMessage("돈이 부족합니다");
	}

	//쿠파성
	else {
		if (key == 2) {

			stageLocked[5] = false;

			setObjectImage(GamePopup[5], "image/Title/팝업/6-2.png");
			setObjectImage(GameEnterButton[5], "image/Title/enter.png");
			locateObject(GameEnterButton[stage], titleScene, 70, 100);
		}

		else
			showMessage("열쇠가 부족합니다");
	}
}

void Title_mouseCallback(ObjectID object, int x, int y, MouseAction action) {


	//검은아이콘(클릭불가)이 아니면 팝업창 띄움
	for (int i = 0; i < 6; i++) {

		if (object == GameIcon[i] && stageBlack[i] == false) {
			playSound(buttonClickSound);
			hideUI();
			showObject(GamePopup[i]);
			showObject(GameEnterButton[i]);

			locateObject(Mario, titleScene, IconX[i], IconY[i]);
			nowMarioOn = i;
		}

		else if (object == GameIcon[i] && stageBlack[i] == true) {
			playSound(buttonClickSound);
			showMessage("이전 스테이지를 클리어 해주세요");
		}
	}

	////팝업창 클릭시 사라짐//////
	for (int i = 0; i < 6; i++) {
		if (object == GamePopup[i]) {
			playSound(buttonClickSound);
			hideObject(GamePopup[i]);
			hideObject(GameEnterButton[i]);
		}
	}

	if (object == Mario) {

		if (stageBlack[nowMarioOn] == false) {
			playSound(buttonClickSound);
			hideUI();
			showObject(GamePopup[nowMarioOn]);
			showObject(GameEnterButton[nowMarioOn]);
		}
	}


	///////게임 입장 버튼//////
	//평원
	else if (object == GameEnterButton[0]) {
		nowGameSceneNum = 3;

		hideObject(GamePopup[0]);
		hideObject(GameEnterButton[0]);

		playSound(bgm_g3, true);
		playSound(buttonClickSound);
		exitTitle();
		enterScene(scene1_g3);
	}

	//사막
	else if (object == GameEnterButton[1]) {

		playSound(buttonClickSound);

		//잠겨있으면 해금
		if (stageLocked[1]) {
			stageUnlock(1);
		}

		//열려있으면 이동
		else {
			if (stage2Clear == false) {
				nowGameSceneNum = 4;

				hideObject(GamePopup[1]);
				hideObject(GameEnterButton[1]);

				playSound(g4theme, true);
				exitTitle();
				enterScene(scene_g4);
			}

			else
				showMessage("이미 클리어 한 스테이지입니다");
		}
	}

	//바다 (바로 입장가능)
	else if (object == GameEnterButton[2]) {


		nowGameSceneNum = 2;

		hideObject(GamePopup[2]);
		hideObject(GameEnterButton[2]);

		playSound(bgm_g2);
		playSound(buttonClickSound);
		exitTitle();
		enterScene(scene1_g2);

	}

	//귀신의집
	else if (object == GameEnterButton[3]) {

		playSound(buttonClickSound);

		if (stageLocked[3]) {
			stageUnlock(3);

			if (stageLocked[3] == false) {	//열렸으면
				stageBlack[4] = false;
				setObjectImage(GameIcon[4], "image/Title/빨간아이콘.png");
			}
		}

		else {
			nowGameSceneNum = 1;

			hideObject(GamePopup[3]);
			hideObject(GameEnterButton[3]);

			playSound(bgm_g1);
			exitTitle();
			enterScene(scene_g1);
		}
	}

	//하늘섬
	else if (object == GameEnterButton[4]) {

		playSound(buttonClickSound);

		if (stageLocked[4]) {
			stageUnlock(4);
		}

		else {
			if (stage5Clear == false) {

				nowGameSceneNum = 6;

				hideObject(GamePopup[4]);
				hideObject(GameEnterButton[4]);

				exitTitle();
				playSound(bgm_g6);

				switch (nowGame6Stage) {
				case 1:
					enterScene(scene_g6);
					break;
				case 2:
					enterScene(scene_g62);
					break;
				case 3:
					enterScene(scene_g63);
					break;
				}
			}
			else
				showMessage("이미 클리어 한 스테이지입니다");
		}

	}

	//쿠파성
	else if (object == GameEnterButton[5]) {

		playSound(buttonClickSound);

		if (stageLocked[5]) {
			stageUnlock(5);
		}

		else {
			nowGameSceneNum = 5;

			hideObject(GamePopup[5]);
			hideObject(GameEnterButton[5]);

			exitTitle();
			playSound(bgm_g5);
			enterScene(scene_g5);
		}
	}

	else if (object == titlestartbutton) {
		playSound(buttonClickSound);
		startTimer(titleanimationtimer);
		hideObject(titlestartbutton);

	}
	else if (object == savebutton) {
		playSound(buttonClickSound);
		savedata();
		showMessage("저장 완료!");
	}
	else if (object == explainbutton) {
		playSound(buttonClickSound);
		showObject(explainwindow);
	}
	else if (object == explainwindow) {
		hideObject(explainwindow);
	}

}

void Title_timerCallback(TimerID timer) {

	if (timer == marioAnimationTimer) {

		setObjectImage(Mario, marioAnimationImage[marioAnimationCount % 9]);
		marioAnimationCount++;

		setTimer(marioAnimationTimer, MARIO_ANIMATION_TIME);
		startTimer(marioAnimationTimer);
	}
	if (timer == titleanimationtimer) {
		titleanimation();
		setTimer(titleanimationtimer, 0.01f);
		startTimer(titleanimationtimer);
	}

}


void Title_soundCallback(SoundID sound) {
	if (sound == bgm_title) {
		playSound(bgm_title);
	}
}


void Title_main() {
	readdata();
	titleScene = createScene("전체 맵", "image/Title/worldmap.png");

	//-------게임 버튼
	for (int i = 0; i < 6; i++)
		GameIcon[i] = createObject("image/Title/검은아이콘.png", titleScene, IconX[i] + 10, IconY[i] - 15, true, 1.0f);

	setObjectImage(GameIcon[0], "image/Title/파란아이콘.png");
	setObjectImage(GameIcon[1], "image/Title/빨간아이콘.png");
	setObjectImage(GameIcon[5], "image/Title/빨간아이콘.png");


	//---------게임버튼끝

	Mario = createObject("image/Title/마리오애니/1.png", titleScene, IconX[0], IconY[0], true, 1.4f);

	key1 = createObject("image/Title/noKey.png", titleScene, 250, 650, true, 1.0f);
	key2 = createObject("image/Title/noKey.png", titleScene, 300, 650, true, 1.0f);


	coinImage = createObject("image/Title/coin.png", titleScene, 5, 637, true, 1.0f);
	xText = createObject("image/Title/숫자/x.png", titleScene, 50, 630, true, 1.0f);

	for (int i = 0; i < 3; i++) {
		coinText[i] = createObject("image/Title/숫자/2.png", titleScene, 90 + 30 * i, 630, false, 1.0f);
	}

	savebutton = createObject("image/Title/save.png", titleScene, 1050, 650, true, 1.0f);
	explainbutton = createObject("image/Title/howto.png", titleScene, 1000, 20, true, 0.9f);
	explainwindow = createObject("image/Title/설명서.png", titleScene, 50, 50, false, 0.6f);

	GamePopup[0] = createObject("image/Title/팝업/1.png", titleScene, 884, 0, false, 1.0f);
	GamePopup[1] = createObject("image/Title/팝업/2.png", titleScene, 884, 0, false, 1.0f);
	GamePopup[2] = createObject("image/Title/팝업/3.png", titleScene, 884, 0, false, 1.0f);
	GamePopup[3] = createObject("image/Title/팝업/4.png", titleScene, 884, 0, false, 1.0f);
	GamePopup[4] = createObject("image/Title/팝업/5.png", titleScene, 0, 0, false, 1.0f);
	GamePopup[5] = createObject("image/Title/팝업/6.png", titleScene, 0, 0, false, 1.0f);

	GameEnterButton[0] = createObject("image/Title/enter.png", titleScene, 950, 100, false, 1.0f);
	GameEnterButton[1] = createObject("image/Title/unlock.png", titleScene, 950, 70, false, 1.0f);
	GameEnterButton[2] = createObject("image/Title/enter.png", titleScene, 950, 100, false, 1.0f);
	GameEnterButton[3] = createObject("image/Title/unlock.png", titleScene, 950, 70, false, 1.0f);
	GameEnterButton[4] = createObject("image/Title/unlock.png", titleScene, 70, 70, false, 1.0f);
	GameEnterButton[5] = createObject("image/Title/unlock.png", titleScene, 70, 70, false, 1.0f);


	if (stage2Clear == true) {
		enterTitle(2);
		//setObjectImage(GameIcon[1], "image/Title/초록아이콘.png");
		//setObjectImage(GameIcon[2], "image/Title/파란아이콘.png");
		//setObjectImage(GameIcon[3], "image/Title/파란아이콘.png");
		//stageBlack[2] = false;
		//stageBlack[3] = false;

		//key = 1;
		//setObjectImage(key1, "image/Title/key.png");
	}

	//하늘지대 클리어했으면
	else if (stage5Clear == true) {
		//setObjectImage(GameIcon[4], "image/Title/초록아이콘.png");
		enterTitle(5);
		//key = 2;
		//setObjectImage(key2, "image/Title/key.png");
	}

	for (int i = 0; i < 6; i++) {

		if (i != 0 && i != 2) {

			if (stageLocked[i] == false) {
				sprintf(path, "image/Title/팝업/%d-2.png", i + 1);
				setObjectImage(GamePopup[i], path);
				setObjectImage(GameEnterButton[i], "image/Title/enter.png");
				locateObject(GameEnterButton[i], titleScene, 950, 100);

				if (i == 3) {
					setObjectImage(GameIcon[4], "image/Title/빨간아이콘.png");
				}

				if (i == 4 || i == 5)
					locateObject(GameEnterButton[i], titleScene, 70, 100);
			}
		}

	}



	maintitle = createObject("image/Title/title.png", titleScene, 0, 0, true, 1.0f);
	titlestartbutton = createObject("image/Title/start.png", titleScene, 900, 110, true, 1.0f);
	marioAnimationTimer = createTimer(MARIO_ANIMATION_TIME);
	titleanimationtimer = createTimer(0.01f);
	startTimer(marioAnimationTimer);

	bgm_title = createSound("sounds/배경음/메인맵.mp3");
	playSound(bgm_title, true);


	showCoinCount();

}