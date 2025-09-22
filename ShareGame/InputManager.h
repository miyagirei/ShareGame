#pragma once
#include <DxLib.h>
#include <unordered_map>

class InputManager {
public:
	static void Update( );

	static bool GetKey( int keyCode );
	static bool GetKeyDown( int keyCode );
	static bool GetKeyUp( int keyCode );
	
	static bool GetMouse( int button );
	static bool GetMouseDown( int button );
	static bool GetMouseUp( int button );

private:
	static std::unordered_map<int, bool> currentKeys;
	static std::unordered_map<int, bool> previousKeys;

	static std::unordered_map<int, bool> currentMouse;
	static std::unordered_map<int, bool> previousMouse;
};

