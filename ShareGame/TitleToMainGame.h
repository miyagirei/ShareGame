#pragma once
#include "DxLib.h"
#include "SceneType.h"

class TitleScene {
public:
	void Run(SceneType& currentScene);
	void SelectButton(SceneType& currentScene);
private:
	void UpdateInput();
	bool clickedThisFrame;
};