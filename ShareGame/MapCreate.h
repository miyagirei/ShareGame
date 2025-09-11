#pragma once

//‰¼
enum mapNum {
	map1, //init
	map2, //2
	map3 //3
};

class MapCreate {
public:
	MapCreate( );

	mapNum scene;
	void SceneChange( );
private:
	bool isClicked( );
};