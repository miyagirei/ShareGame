#include "SceneManager.h"
#include "Dxlib.h"
#include "DebugUI.h"
#include "TitleToMainGame.h"
void SceneManager::Update( ) {

}

SceneManager::SceneManager( ) {
    scene = SceneType::Title;
}

bool SceneManager::isClicked( ) {
    static int prevMouse = 0;
    int mouseInput = GetMouseInput( );

    bool clicked = ( ( mouseInput & MOUSE_INPUT_LEFT ) && !( prevMouse & MOUSE_INPUT_LEFT ) );

    prevMouse = mouseInput;
    return clicked;
}


void SceneManager::SceneChange( ) {
    //DebugUI debug;
    //switch ( scene ) {
    //case SceneType::map1:
    //    testScene.Run( );
    //    break;

    //case SceneType::map2:
    //    gameLoopScene.Run( );
    //    if ( auto next = gameLoopScene.game.GetRequestedScene( ) ) {
    //        TransScene( *next );
    //    }
    //    break;

    //case SceneType::map3:

    //    ClearDrawScreen( );
    //    debug.SummonDebug( scene);
    //    DrawString( 200, 200, "map3", GetColor( 255, 255, 255 ) );
    //    ScreenFlip( );
    //    break;

    //case SceneType::onlineScene:
    //    //onlineScene.Run( );
    //    break;
    //}

    ClearDrawScreen( );
    DebugUI debug;

    switch ( scene ) {
    case SceneType::Title:
        titleScene.Run(scene);
        break;

    case SceneType::map1:
        testScene.Run( );
        break;

    case SceneType::map2:
        gameLoopScene.Run( );
        if ( auto next = gameLoopScene.game.GetRequestedScene( ) ) {
            TransScene( *next );
        }
        break;

    case SceneType::map3:
        DrawString( 200, 200, "map3", GetColor( 255, 255, 255 ) );
        break;

    case SceneType::onlineScene:
        onlineScene.Run( );
        break;
    }
    debug.SummonDebug(scene );

    ScreenFlip( );
}


void SceneManager::TransScene( SceneType next ) {
    scene = next;
}

void SceneManager::SetScene( SceneType newScene ) {
    scene = newScene;
}

SceneType SceneManager::GetScene( ) const {
    return scene;
}

