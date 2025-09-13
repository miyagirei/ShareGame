#include "Dxlib.h"
#include "Camera.h"

Camera::Camera(int screenW, int screenH)
    : pos{ 0.0, 0.0 }, scaleFactor(10.0),
    screenWidth(screenW), screenHeight(screenH) {
}

void Camera::initialize() {
    pos = Position{ 0.0, 0.0 };
    scaleFactor = 10.0;
}

void Camera::setPosition(const Position& p) {
    pos = p;
}

Position Camera::getPosition() const {
    return pos;
}

Position Camera::convertScreenToFieldPosition(int x, int y) const {
    int cx = x - screenWidth / 2;
    int cy = y - screenHeight / 2;
    Position newPos = pos;
    newPos = getMovedPos(newPos, Vector2{ cx / scaleFactor, cy / scaleFactor });
    return newPos;
}

int Camera::convertFieldPositionToScreenX(const Position& p) const {
    int tx = static_cast<int>((p.x - pos.x) * scaleFactor);
    return tx + screenWidth / 2;
}

int Camera::convertFieldPositionToScreenY(const Position& p) const {
    int ty = static_cast<int>((p.y - pos.y) * scaleFactor);
    return ty + screenHeight / 2;
}

int Camera::convertSizeToScreenSize(double size) const {
    return static_cast<int>(size * scaleFactor);
}

bool Camera::isOutOfScreen(const Position& p, double radius) const {
    int sx = convertFieldPositionToScreenX(p);
    int sy = convertFieldPositionToScreenY(p);
    int sr = convertSizeToScreenSize(radius);

    bool out_right = sx > screenWidth - sr;
    bool out_bottom = sy > screenHeight - sr;
    bool out_left = sx < sr;
    bool out_top = sy < sr;

    return out_right || out_bottom || out_left || out_top;
}

bool Camera::isFullOutOfScreen(const Position& p, double radius) const {
    int sx = convertFieldPositionToScreenX(p);
    int sy = convertFieldPositionToScreenY(p);
    int sr = convertSizeToScreenSize(radius);

    bool full_out_right = sx > screenWidth + sr;
    bool full_out_bottom = sy > screenHeight + sr;
    bool full_out_left = sx < -sr;
    bool full_out_top = sy < -sr;

    return full_out_right || full_out_bottom || full_out_left || full_out_top;
}

Position Camera::getMovedPos(const Position& p, const Vector2& v) const {
    return Position{ p.x + v.x, p.y + v.y };
}