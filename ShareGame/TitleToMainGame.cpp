#include "Dxlib.h"
#include "TitleToMainGame.h"
#include "SceneType.h"

void TitleScene::Run(SceneType& currentScene) {
	DrawString(280, 150, "ShareGame", GetColor(255, 255, 255));
    DrawString(260, 250, "Click to Start", GetColor(255, 255, 255));

    if ((GetMouseInput() & MOUSE_INPUT_LEFT)) {
        currentScene = SceneType::map2;
    }
}