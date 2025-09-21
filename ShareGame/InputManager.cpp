#include "InputManager.h"

std::unordered_map<int, bool> InputManager::currentKeys;
std::unordered_map<int, bool> InputManager::previousKeys;

std::unordered_map<int, bool> InputManager::currentMouse;
std::unordered_map<int, bool> InputManager::previousMouse;

void InputManager::Update( ) { 
	previousKeys = currentKeys;
	previousMouse = currentMouse;

	for ( int key = 0; key < 256; key++ ) { 
		currentKeys[ key ] = ( CheckHitKey( key ) != 0 );
	}

	int mouseInput = GetMouseInput( );
	currentMouse[ MOUSE_INPUT_LEFT ] = ( mouseInput & MOUSE_INPUT_LEFT ) != 0;
	currentMouse[ MOUSE_INPUT_RIGHT ] = ( mouseInput & MOUSE_INPUT_RIGHT ) != 0;
	currentMouse[ MOUSE_INPUT_MIDDLE ] = ( mouseInput & MOUSE_INPUT_MIDDLE ) != 0;
}

bool InputManager::GetKey( int keyCode ) {
	return currentKeys[ keyCode ];
}

bool InputManager::GetKeyDown( int keyCode ) { 
	return currentKeys[ keyCode ] && !previousKeys[ keyCode ];
}

bool InputManager::GetKeyUp( int keyCode ) { 
	return currentKeys[ keyCode ] && !previousKeys[ keyCode ];
}

bool InputManager::GetMouse( int button ) { 
	return currentMouse[ button ];
}

bool InputManager::GetMouseDown( int button ) { 
	return currentMouse[ button ] && !previousMouse[ button ];
}

bool InputManager::GetMouseUp( int button ) {
	return !currentMouse[ button ] && previousMouse[ button ];
}