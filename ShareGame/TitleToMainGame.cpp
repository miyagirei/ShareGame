#include "OnlineScene.h"
#include "Dxlib.h"
#include "TitleToMainGame.h"
#include "SceneType.h"
#include "SceneManager.h"

extern SceneManager sceneManager;

bool isMultiClicked = false;

void TitleScene::UpdateInput() {
    static int prevMouse = 0;
    int mouseInput = GetMouseInput();

    clickedThisFrame = ((mouseInput & MOUSE_INPUT_LEFT) && !(prevMouse & MOUSE_INPUT_LEFT));

    prevMouse = mouseInput;
}

void TitleScene::Run(SceneType& currentScene) {
	DrawString(280, 150, "ShareGame", GetColor(255, 255, 255));
    DrawString(260, 250, "Click to Start", GetColor(255, 255, 255));

    if ((GetMouseInput() & MOUSE_INPUT_LEFT)) {
        currentScene = SceneType::menu;
    }
}

void TitleScene::SelectButton(SceneType& currentScene) {

    int width, height;
    int mx, my;
    GetMousePoint(&mx, &my);
    GetWindowSize(&width, &height);
    UpdateInput();

    int singleX1 = (width / 2) - 60, singleY1 = height - 300, singleX2 = (width / 2) + 60, singleY2 = height - 270;
    int multiX1 = (width / 2) - 60, multiY1 = height - 250, multiX2 = (width / 2) + 60, multiY2 = height - 220;

    int hostX1 = (width / 2) - 20, hostY1 = height - 210, hostX2 = (width / 2) + 100, hostY2 = height - 180;
    int clientX1 = (width / 2) - 20, clientY1 = height - 170, clientX2 = (width / 2) + 100, clientY2 = height - 140;
    static int settingX1 = (width / 2) - 60, settingY1 = height - 200, settingX2 = (width / 2) + 60, settingY2 = height - 170;
    if (isMultiClicked) {
        settingY1 = clientY2 + 20;
        settingY2 = clientY2 + 50;
    }
    else {
        settingY1 = height - 200;
        settingY2 = height - 170;
    }
    

    DrawString(width / 2 - 50, 100, "Mode Select", GetColor(255, 255, 255));
    //single
    DrawBox(singleX1, singleY1, singleX2, singleY2, GetColor(255, 255, 255), FALSE);
    DrawString(singleX1 + 12, singleY1 + 8, "Single Play", GetColor(255, 255, 255));
    //multi
    DrawBox(multiX1, multiY1, multiX2, multiY2, GetColor(255, 255, 255), FALSE);
    DrawString(multiX1 + 16, multiY1 + 8, "Multi Play", GetColor(255, 255, 255));
    //setting
    DrawBox(settingX1, settingY1, settingX2, settingY2, GetColor(255, 255, 255), FALSE);
    DrawString(settingX1 + 30, settingY1 + 8, "Setting", GetColor(255, 255, 255));

    //singleplay
    if (singleX1 < mx && mx < singleX2 && singleY1 < my && my < singleY2) {
        DrawBox(singleX1, singleY1, singleX2, singleY2, GetColor(255, 255, 0), FALSE);
        DrawString(singleX1 + 12, singleY1 + 8, "Single Play", GetColor(255, 255, 0));
        if (clickedThisFrame) {
            currentScene = SceneType::map2;
        }
    }
    //multiplay
    else if (multiX1 < mx && mx < multiX2 && multiY1 < my && my < multiY2) {
        DrawBox(multiX1, multiY1, multiX2, multiY2, GetColor(255, 255, 0), FALSE);
        DrawString(multiX1 + 16, multiY1 + 8, "Multi Play", GetColor(255, 255, 0));
        if (clickedThisFrame) {
            isMultiClicked = !isMultiClicked;
        }
    }
    //setting
    else if (settingX1 < mx && mx < settingX2 && settingY1 < my && my < settingY2) {
        DrawBox(settingX1, settingY1, settingX2, settingY2, GetColor(255, 255, 0), FALSE);
        DrawString(settingX1 + 30, settingY1 + 8, "Setting", GetColor(255, 255, 0));
        if (clickedThisFrame) {

        }
    }

    if (isMultiClicked) {
        DrawBox(hostX1, hostY1, hostX2, hostY2, GetColor(255, 255, 255), FALSE);
        DrawString(hostX1 + 45, hostY1 + 8, "Host", GetColor(255, 255, 255));
        DrawBox(clientX1, clientY1, clientX2, clientY2, GetColor(255, 255, 255), FALSE);
        DrawString(clientX1 + 35, clientY1 + 8, "Client", GetColor(255, 255, 255));
        if (hostX1 < mx && mx < hostX2 && hostY1 < my && my < hostY2) {
            DrawBox(hostX1, hostY1, hostX2, hostY2, GetColor(255, 255, 0), FALSE);
            DrawString(hostX1 + 45, hostY1 + 8, "Host", GetColor(255, 255, 0));
            if (clickedThisFrame) {
                sceneManager.GetOnlineScene().SetHost(true);
                currentScene = SceneType::onlineScene;
            }
        }
        else if (clientX1 < mx && mx < clientX2 && clientY1 < my && my < clientY2) {
            DrawBox(clientX1, clientY1, clientX2, clientY2, GetColor(255, 255, 0), FALSE);
            DrawString(clientX1 + 35, clientY1 + 8, "Client", GetColor(255, 255, 0));
            if (clickedThisFrame) {
                sceneManager.GetOnlineScene().SetHost(false);
                currentScene = SceneType::onlineScene;
            }
        }
    }
    clickedThisFrame = false;
}