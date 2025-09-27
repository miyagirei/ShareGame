#pragma once
#include <functional>
#include <string>
#include "Player.h"
#include "Board.h"

struct Button {
	std::string label;
	std::function<void( )> onClick;
	std::function<bool( )> canShow;
	int x = 0;
	int y = 0;
	int w = 0;
	int h = 0;
};

class UIManager {
public:
	std::vector<Button> buttons;

	void AddButton(Button button);
	void Draw( Player& player, Board& board, int mouseX, int mouseY );
	void OnLeftClick( int mouseX, int mouseY, Player& player );

	bool WasUIClicked() const { return lastUIClicked; }

private:
	bool lastUIClicked = false;
	bool IsMouseOverButton( int mouseX, int mouseY , Button button) const;
};

