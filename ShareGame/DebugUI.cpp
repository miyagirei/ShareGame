#include "DebugUI.h"
#include "DxLib.h"
#include "MapCreate.h"
#include "SceneType.h"

extern MapCreate map;

const int GRID_SIZE = 10;

bool DebugUI::IsKeyPressed(int key) {
	static char prevKeyState[256] = { 0 };
	char nowKeyState[256];

	GetHitKeyStateAll(nowKeyState);

	bool pressed = (nowKeyState[key] && !prevKeyState[key]);

	memcpy(prevKeyState, nowKeyState, 256);

	return pressed;
}

bool DebugUI::IsDebugKeyPressed() {

	static bool isF5Enabled = false;

	if (IsKeyPressed(KEY_INPUT_F5)) {
		isF5Enabled = !isF5Enabled;
	}

	return isF5Enabled;
}

void DebugUI::UpdateInput() {
	static int prevMouse = 0;
	int mouseInput = GetMouseInput();

	clickedThisFrame = ((mouseInput & MOUSE_INPUT_LEFT) && !(prevMouse & MOUSE_INPUT_LEFT));

	prevMouse = mouseInput;
}

void DebugUI::SummonDebug() {
	if (IsDebugKeyPressed()) {
		UpdateInput();

		//grid
		int gridx1 = 30, gridx2 = 170, gridy1 = 80, gridy2 = 110;
		if (EnableGrid(gridx1, gridy1, gridx2, gridy2)) {
			for (int x = 0; x <= 1000; x += GRID_SIZE) {
				DrawLine(x, 0, x, 1000, GetColor(255, 255, 255));
			}

			for (int y = 0; y <= 1000; y += GRID_SIZE) {
				DrawLine(0, y, 1000, y, GetColor(255, 255, 255));
			}
		}
		DrawFormatString(50, 88, GetColor(0, 0, 0), "グリッド表示");
		DrawFormatString(30, 15, GetColor(255, 255, 255), "デバッグモード");

		//SceneTrance
		DrawBox(30, 40, 170, 70, GetColor(192, 192, 192), TRUE);
		DrawFormatString(42, 48, GetColor(0, 0, 0),"シーン切り替え");

		int prevScenex1 = 5, prevScenex2 = 25, prevSceney1 = 40, prevSceney2 = 70;
		DrawBox(prevScenex1, prevSceney1, prevScenex2, prevSceney2, GetColor(192, 192, 192), TRUE);
		DrawTriangle(6, 55, 22, 42, 22, 68, GetColor(0, 0, 0), TRUE);

		int nextScenex1 = 175, nextScenex2 = 195, nextSceney1 = 40, nextSceney2 = 70;
		DrawBox(nextScenex1, nextSceney1, nextScenex2, nextSceney2, GetColor(192, 192, 192), TRUE);
		DrawTriangle(193, 55, 178, 42, 178, 68, GetColor(0, 0, 0), TRUE);

		SceneTranceButton();
	}
}

void DebugUI::SceneTranceButton() {

	int prevScenex1 = 5, prevScenex2 = 25, prevSceney1 = 40, prevSceney2 = 70;
	DrawBox(prevScenex1, prevSceney1, prevScenex2, prevSceney2, GetColor(192, 192, 192), TRUE);
	DrawTriangle(6, 55, 22, 42, 22, 68, GetColor(0, 0, 0), TRUE);

	int nextScenex1 = 175, nextScenex2 = 195, nextSceney1 = 40, nextSceney2 = 70;
	DrawBox(nextScenex1, nextSceney1, nextScenex2, nextSceney2, GetColor(192, 192, 192), TRUE);
	DrawTriangle(193, 55, 178, 42, 178, 68, GetColor(0, 0, 0), TRUE);

	// クリック判定
	int mx, my;
	GetMousePoint(&mx, &my);

	if (clickedThisFrame) {
		if (mx >= prevScenex1 && mx <= prevScenex2 &&
			my >= prevSceney1 && my <= prevSceney2) {
			if (map.GetScene() == SceneType::map1) map.SetScene( SceneType::map3);
			else map.SetScene(static_cast<SceneType>(static_cast<int>(map.GetScene()) - 1));
			DrawString(250, 50, "Prevボタン押下", GetColor(255, 0, 0));
		}

		if (mx >= nextScenex1 && mx <= nextScenex2 &&
			my >= nextSceney1 && my <= nextSceney2) {
			if (map.GetScene() == SceneType::map3) map.SetScene( SceneType::map1);
			else map.SetScene( static_cast< SceneType >( static_cast< int >( map.GetScene( ) ) + 1 ) );
			DrawString(250, 70, "Nextボタン押下", GetColor(0, 255, 0));
		}
	}
	DrawFormatString(400, 20, GetColor(255, 255, 0), "Mouse: (%d, %d)", mx, my);
}

bool DebugUI::EnableGrid(int x1, int y1, int x2, int y2) {
	int mouseX, mouseY;
	GetMousePoint(&mouseX, &mouseY);

	DrawBox(x1, y1, x2, y2, GetColor(192, 192, 192), TRUE);

	static bool isEnabled = false;

	if (clickedThisFrame) {
		if (mouseX >= x1 && mouseX <= x2 &&
			mouseY >= y1 && mouseY <= y2) {
			isEnabled = !isEnabled;
		}
	}

	if (isEnabled) {
		DrawBox(x1, y1, x2, y2, GetColor(255, 255, 0), TRUE);
	}

	return isEnabled;
}