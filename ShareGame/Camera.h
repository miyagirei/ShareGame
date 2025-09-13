#pragma once
#include "Camera.h"

struct Position {
    double x;
    double y;
};

struct Vector2 {
    double x;
    double y;
};

class Camera {
public:
    Camera(int screenW, int screenH);

    void initialize();
    void setPosition(const Position& p);
    Position getPosition() const;

    Position convertScreenToFieldPosition(int x, int y) const;
    int convertFieldPositionToScreenX(const Position& pos) const;
    int convertFieldPositionToScreenY(const Position& pos) const;
    int convertSizeToScreenSize(double size) const;

    bool isOutOfScreen(const Position& pos, double radius) const;
    bool isFullOutOfScreen(const Position& pos, double radius) const;

private:
    Position pos;     
    double scaleFactor; 

    int screenWidth;    
    int screenHeight;   

    Position getMovedPos(const Position& p, const Vector2& v) const;
};