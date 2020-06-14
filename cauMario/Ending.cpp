#include<bangtal.h>
#include<math.h>
#include<stdio.h>
#include<stdlib.h>

#define MARIO_PEACH_MOVE_SPEED      1
#define MARIO_PEACH_MOVE_TIME       0.01f
#define MARIO_PEACH_ANIMATION_TIME  0.15f

extern void enterTitle(int clearScene);
extern int savedata();
SceneID endingScene;
ObjectID marioPeach, clearText, goTitleButton;
TimerID endingAnimationTimer1, endingAnimationTimer2, endingAnimationTimer3, marioPeachMoveTimer, textMoveTimer, VanimationTimer;
SoundID bgm_Ending;
extern SoundID buttonClickSound;

int marioPeachX = 20, marioPeachY = 200, textX = 650, textY = 500;
int animationCount = 0, animation3Count = 0;
int stopPosX = 530, textStartPosX = 400;


const char* endingAnimationImage1[7]
= { "image/Ending/마리오피치/어두운1.png", "image/Ending/마리오피치/어두운2.png", "image/Ending/마리오피치/어두운3.png", "image/Ending/마리오피치/어두운4.png",
"image/Ending/마리오피치/어두운5.png", "image/Ending/마리오피치/어두운6.png", "image/Ending/마리오피치/어두운7.png" };

const char* endingAnimationImage2[7]
= { "image/Ending/마리오피치/1.png", "image/Ending/마리오피치/2.png", "image/Ending/마리오피치/3.png", "image/Ending/마리오피치/4.png",
"image/Ending/마리오피치/5.png", "image/Ending/마리오피치/6.png", "image/Ending/마리오피치/7.png" };

const char* endingAnimationImage3[12]
= { "image/Ending/클리어텍스트/1.png", "image/Ending/클리어텍스트/2.png", "image/Ending/클리어텍스트/3.png", "image/Ending/클리어텍스트/4.png",
"image/Ending/클리어텍스트/5.png", "image/Ending/클리어텍스트/6.png", "image/Ending/클리어텍스트/7.png", "image/Ending/클리어텍스트/8.png",
"image/Ending/클리어텍스트/9.png", "image/Ending/클리어텍스트/10.png", "image/Ending/클리어텍스트/11.png", "image/Ending/클리어텍스트/12.png" };


extern ObjectID createObject(const char* name, SceneID scene, int x, int y, bool shown, float size);

void startEnding() {

    playSound(bgm_Ending);
    startTimer(marioPeachMoveTimer);
    startTimer(endingAnimationTimer1);
   
}


void Ending_mouseCallback(ObjectID object, int x, int y, MouseAction action) {

    if (object == goTitleButton) {
        playSound(buttonClickSound);
        savedata();
        endGame();
    }


}
void Ending_timerCallback(TimerID timer) {

    if (timer == marioPeachMoveTimer) {
        marioPeachX += MARIO_PEACH_MOVE_SPEED;

        locateObject(marioPeach, endingScene, marioPeachX, marioPeachY);

        if (marioPeachX >= stopPosX && animationCount % 7 == 6) {

            stopTimer(endingAnimationTimer2);
            setObjectImage(marioPeach, "image/Ending/마리오피치/idle.png");

            showObject(clearText);
            startTimer(textMoveTimer);
            startTimer(endingAnimationTimer3);
            startTimer(VanimationTimer);

        }
        else {
            setTimer(marioPeachMoveTimer, MARIO_PEACH_MOVE_TIME);
            startTimer(marioPeachMoveTimer);
        }

    }

    //페이드 인
    if (timer == endingAnimationTimer1) {

        setObjectImage(marioPeach, endingAnimationImage1[animationCount % 7]);
        animationCount++;

        //한바퀴만 실행
        if (animationCount < 7) {
            setTimer(endingAnimationTimer1, 0.12f);
            startTimer(endingAnimationTimer1);
        }
        
        else {
            startTimer(endingAnimationTimer2);
        }
    }

    //걷는 애니메이션
    if (timer == endingAnimationTimer2) {
        
        setObjectImage(marioPeach, endingAnimationImage2[animationCount % 7]);
        animationCount++;

        setTimer(endingAnimationTimer2, MARIO_PEACH_ANIMATION_TIME);
        startTimer(endingAnimationTimer2);

    }

    if (timer == textMoveTimer) {
        textX -= 15;
        locateObject(clearText, endingScene, textX, textY);

        //아직 이동 다 안했으면 계속 이동
         setTimer(textMoveTimer, MARIO_PEACH_ANIMATION_TIME);
         startTimer(textMoveTimer);
    }

    if (timer == endingAnimationTimer3) {
        setObjectImage(clearText, endingAnimationImage3[animation3Count % 12]);
        animation3Count++;

        if (animation3Count < 12) {
            setTimer(endingAnimationTimer3, MARIO_PEACH_ANIMATION_TIME);
            startTimer(endingAnimationTimer3);
        }

        else {
            stopTimer(textMoveTimer);
        }
    }

    if (timer == VanimationTimer) {
        setObjectImage(marioPeach, "image/Ending/마리오피치/vPos.png");
        showObject(goTitleButton);
    }

}


void Ending_main() {

    endingScene = createScene("엔딩", "image/Ending/엔딩배경.png");

    marioPeach = createObject(endingAnimationImage1[0], endingScene, marioPeachX, marioPeachY, true, 1.0f);
    clearText = createObject(endingAnimationImage3[0], endingScene, textX, textY , false, 1.0f);
    goTitleButton = createObject("image/Ending/goTitle.png", endingScene, 460, 75, false, 0.7f);

    marioPeachMoveTimer = createTimer(MARIO_PEACH_MOVE_TIME);
    textMoveTimer = createTimer(MARIO_PEACH_MOVE_TIME);
    endingAnimationTimer1 = createTimer(0.12f);
    endingAnimationTimer2 = createTimer(MARIO_PEACH_ANIMATION_TIME);
    endingAnimationTimer3 = createTimer(0.05f);
    VanimationTimer = createTimer(2.5f);

    bgm_Ending = createSound("sounds/배경음/엔딩.mp3");

}