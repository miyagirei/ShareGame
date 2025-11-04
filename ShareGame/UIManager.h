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
	std::string group = "default";
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
	std::string group = "default";
};

class UIManager {
private:
	std::vector<Button> buttons;
	std::vector<Text> texts;
	std::unordered_map<std::string, bool> groupVisibility;
	std::unordered_map<std::string, std::function<bool()>> groupConditions;
public:

	void AddButton(Button button);
	void AddText( Text text );
	void Draw( Player& player, Board& board, int mouseX, int mouseY );
	void Update( );
	void OnLeftClick( int mouseX, int mouseY, Player& player );

	bool WasUIClicked() const { return lastUIClicked; }

	void SetGroupVisibleCondition( const std::string& group, std::function<bool()> condition );
	bool IsGroupVisible( const std::string& groupName ) const;

private:

	bool lastUIClicked = false;
	bool IsMouseOverButton( int mouseX, int mouseY , Button button) const;

	std::string ReplaceVariables( const std::string& src, const std::unordered_map<std::string, std::function<std::string( )>>& vars );
};

