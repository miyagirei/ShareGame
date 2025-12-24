#pragma once
#include "DxLib.h"
#include "SceneType.h"

enum class TitleState {
	Title,
	Menu
};

class TitleScene {
public:
	void Run(SceneType& currentScene);
	void SelectButton(SceneType& currentScene);
private:
	void UpdateInput();
	bool clickedThisFrame;
	TitleState state = TitleState::Title;
};