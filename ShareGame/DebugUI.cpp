#include "DebugUI.h"
#include "DxLib.h"

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

bool DebugUI::IsClicked() {
	static int prevMouse = 0;
	int mouseInput = GetMouseInput();

	bool clicked = ((mouseInput & MOUSE_INPUT_LEFT) && !(prevMouse & MOUSE_INPUT_LEFT));
	//if (clicked) DrawString(100, 100, "clicked", GetColor(255, 255, 255));

	prevMouse = mouseInput;
	return clicked;
}

void DebugUI::SummonDebug() {
	if (IsDebugKeyPressed()) {

		int gridx1 = 30, gridx2 = 200, gridy1 = 100, gridy2 = 150;
		if (EnableGrid(gridx1, gridy1, gridx2, gridy2)) {
			for (int x = 0; x <= 1000; x += GRID_SIZE) {
				DrawLine(x, 0, x, 1000, GetColor(255, 255, 255));
			}

			for (int y = 0; y <= 1000; y += GRID_SIZE) {
				DrawLine(0, y, 1000, y, GetColor(255, 255, 255));
			}
		}
		DrawFormatString(60, 120, GetColor(0, 0, 0), "グリッド表示");
		DrawFormatString(30, 15, GetColor(255, 255, 255), "デバッグモード");
		DrawBox(30, 40, 200, 90, GetColor(192, 192, 192), TRUE);
		DrawFormatString(60, 60, GetColor(0, 0, 0),"シーン切り替え");

	}
}

void DebugUI::SceneTranceButton() {

}

bool DebugUI::EnableGrid(int x1, int y1, int x2, int y2) {
	int mouseX, mouseY;
	GetMousePoint(&mouseX, &mouseY);

	DrawBox(x1, y1, x2, y2, GetColor(192, 192, 192), TRUE);

	static bool isEnabled = false;

	if (IsClicked()) {
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