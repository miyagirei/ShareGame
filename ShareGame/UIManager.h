#pragma once
#include <functional>
#include <string>
#include "Player.h"
#include "Board.h"

enum class AnchorType {
	TopLeft,
	Center,
};

struct Button {
	std::string label;
	std::function<void( )> onClick;
	std::function<bool( )> canShow;
	int x = 0;
	int y = 0;
	int w = 0;
	int h = 0;
	AnchorType anchor = AnchorType::TopLeft;
};

struct Text {
	std::string label;
	std::unordered_map<std::string, std::function<std::string( )>> variables = {};
	std::function<bool( )> canShow;
	int x = 0;
	int y = 0;
	int w = 0;
	int h = 0;
	AnchorType anchor = AnchorType::TopLeft;

};

class UIManager {
public:
	std::vector<Button> buttons;
	std::vector<Text> texts;

	void AddButton(Button button);
	void AddText( Text text );
	void Draw( Player& player, Board& board, int mouseX, int mouseY );
	void OnLeftClick( int mouseX, int mouseY, Player& player );

	bool WasUIClicked() const { return lastUIClicked; }

private:
	bool lastUIClicked = false;
	bool IsMouseOverButton( int mouseX, int mouseY , Button button) const;

	std::string ReplaceVariables( const std::string& src, const std::unordered_map<std::string, std::function<std::string( )>>& vars );
};

