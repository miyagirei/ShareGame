#pragma once
#include "SceneManager.h"
class DebugUI {
public:
	void SummonDebug(SceneType& scene);
	void SceneTranceButton( SceneType& scene );
	bool EnableGrid(int x1, int x2, int y1, int y2);

private:
	void UpdateInput(); 
	bool clickedThisFrame;    
	bool IsKeyPressed(int key);
	bool IsClicked();
	bool IsDebugKeyPressed();
};
