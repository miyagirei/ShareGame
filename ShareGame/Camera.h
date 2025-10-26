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
    double offsetX;
    double offsetY;
    double zoom;

    Camera(int screenW, int screenH);
    Camera();
    void Update(int x , int y);

    void initialize();
    void setPosition(const Position& p);
    Position getPosition() const;

    Position convertScreenToFieldPosition(int x, int y) const;
    int convertFieldPositionToScreenX(const Position& p) const;
    int convertFieldPositionToScreenY(const Position& p) const;
    int convertSizeToScreenSize(double size) const;

    bool isOutOfScreen(const Position& p, double radius) const;
    bool isFullOutOfScreen(const Position& p, double radius) const;

    void updateByMouseWheel(); 
    double GetZoom( ) const;
private:
    Position getMovedPos(const Position& p, const Vector2& v) const;

    Position pos;       
    Position lastMousePos;
    double scaleFactor; 
    int screenWidth;    
    int screenHeight;   
};