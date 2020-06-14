#define _CRT_SECURE_NO_WARNINGS
#include<bangtal.h>

extern SceneID titleScene, endingScene;

extern void Title_main();
extern void Title_mouseCallback(ObjectID object, int x, int y, MouseAction action);
extern void Title_timerCallback(TimerID timer);
extern void Title_soundCallback(SoundID sound);
extern int readdata();

extern void Game1_main();
extern void Game1_mouseCallback(ObjectID object, int x, int y, MouseAction action);
extern void Game1_timerCallback(TimerID timer);
extern void Game1_soundCallback(SoundID sound);
extern void Game1_keyboardCallback(KeyCode code, KeyState state);

extern void Game2_main();
extern void Game2_mouseCallback(ObjectID object, int x, int y, MouseAction action);
extern void Game2_timerCallback(TimerID timer);

extern void Game3_main();
extern void Game3_mouseCallback(ObjectID object, int x, int y, MouseAction action);
extern void Game3_timerCallback(TimerID timer);

extern void Game4_main();
extern void Game4_mouseCallback(ObjectID object, int x, int y, MouseAction action);
extern void Game4_timerCallback(TimerID timer);
extern void Game4_soundCallback(SoundID sound);
extern void Game4_keyboardCallback(KeyCode code, KeyState state);

extern void Game5_main();
extern void Game5_mouseCallback(ObjectID object, int x, int y, MouseAction action);
extern void Game5_timerCallback(TimerID timer);
extern void Game5_soundCallback(SoundID sound);
extern void Game5_keyboardCallback(KeyCode code, KeyState state);

extern void Game6_main();
extern void Game6_mouseCallback(ObjectID object, int x, int y, MouseAction action);
extern void Game6_timerCallback(TimerID timer);
extern void Game6_soundCallback(SoundID sound);
extern void Game6_keyboardCallback(KeyCode code, KeyState state);

extern void Game62_main();
extern void Game62_mouseCallback(ObjectID object, int x, int y, MouseAction action);
extern void Game62_timerCallback(TimerID timer);
extern void Game62_keyboardCallback(KeyCode code, KeyState state);

extern void Game63_main();
extern void Game63_mouseCallback(ObjectID object, int x, int y, MouseAction action);
extern void Game63_timerCallback(TimerID timer);
extern void Game63_keyboardCallback(KeyCode code, KeyState state);

extern void Ending_main();
extern void Ending_mouseCallback(ObjectID object, int x, int y, MouseAction action);
extern void Ending_timerCallback(TimerID timer);


SoundID buttonClickSound, gameClearSound, gameOverSound, gameEnterSound;


ObjectID createObject(const char* name, SceneID scene, int x, int y, bool shown, float size) {

	ObjectID object = createObject(name);
	locateObject(object, scene, x, y);
	scaleObject(object, size);

	if (shown)
		showObject(object);

	return object;
}

void mouseCallback(ObjectID object, int x, int y, MouseAction action) {
	
	Title_mouseCallback(object, x, y, action);
	Game1_mouseCallback(object, x, y, action);
	Game2_mouseCallback(object, x, y, action);
	Game3_mouseCallback(object, x, y, action);
	Game4_mouseCallback(object, x, y, action);
	Game5_mouseCallback(object, x, y, action);
	Game6_mouseCallback(object, x, y, action);
	Game62_mouseCallback(object, x, y, action);
	Game63_mouseCallback(object, x, y, action);
	Ending_mouseCallback(object, x, y, action);

}

void timerCallback(TimerID timer) {
	
	Title_timerCallback(timer);
	Game1_timerCallback(timer);
	Game2_timerCallback(timer);
	Game3_timerCallback(timer);
	Game4_timerCallback(timer);
	Game5_timerCallback(timer);
	Game6_timerCallback(timer);
	Game62_timerCallback(timer);
	Game63_timerCallback(timer);
	Ending_timerCallback(timer);

}

void soundCallback(SoundID sound) {

	Title_soundCallback(sound);
	Game1_soundCallback(sound);
	Game4_soundCallback(sound);
	Game5_soundCallback(sound);
	Game6_soundCallback(sound);

}

void keyboardCallback(KeyCode code, KeyState state) {

	Game1_keyboardCallback(code, state);
	Game4_keyboardCallback(code, state);
	Game5_keyboardCallback(code, state);
	Game6_keyboardCallback(code, state);
	Game62_keyboardCallback(code, state);
	Game63_keyboardCallback(code, state);

}


int main() {

	setGameOption(GameOption::GAME_OPTION_ROOM_TITLE, false);
	setGameOption(GameOption::GAME_OPTION_INVENTORY_BUTTON, false);
	setGameOption(GameOption::GAME_OPTION_MESSAGE_BOX_BUTTON, false);

	setMouseCallback(mouseCallback);
	setTimerCallback(timerCallback);
	setSoundCallback(soundCallback);
	setKeyboardCallback(keyboardCallback);


	Title_main();
	Game1_main();
	Game2_main();
	Game3_main();
	Game4_main();
	Game5_main();
	Game6_main();
	Game62_main();
	Game63_main();
	Ending_main();


	buttonClickSound = createSound("sounds/공통/기본버튼클릭.wav");
	gameClearSound = createSound("sounds/공통/게임클리어.wav");
	gameOverSound = createSound("sounds/공통/게임오버.wav");
	gameEnterSound = createSound("sounds/공통/게임입장.wav");

	
	startGame(titleScene);
	

}