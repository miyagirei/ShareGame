#include "HexagonUtility.h"
#include "Dxlib.h"
#include <cmath>

double M_PI = 3.14159265358979323846;
constexpr int HEX_VERTICES = 6;

void DrawHexagon(int cx, int cy, int radius, unsigned int color, bool fill) {
    int vx[HEX_VERTICES], vy[HEX_VERTICES];
    for (int i = 0; i < HEX_VERTICES; ++i) {
        double angle = M_PI / 3.0 * i + M_PI / 6.0; 
        vx[i] = static_cast<int>(std::lround(cx + radius * std::cos(angle)));
        vy[i] = static_cast<int>(std::lround(cy + radius * std::sin(angle)));
    }
    if (fill) {
        for (int i = 0; i < HEX_VERTICES; ++i) {
            int j = (i + 1) % HEX_VERTICES;
            DrawTriangle(cx, cy, vx[i], vy[i], vx[j], vy[j], color, 1); 
        }
    }
    else {
        for (int i = 0; i < HEX_VERTICES; ++i) {
            int j = (i + 1) % HEX_VERTICES;
            DrawLine(vx[i], vy[i], vx[j], vy[j], color);
        }
    }
}