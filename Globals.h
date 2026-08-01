#pragma once
#include "raylib.h"
#include <cmath>

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;
const int TILE_SIZE = 40;

// C++ tamsayı bölmesi sıfıra doğru kestiği için negatif koordinatlarda 
// hata oluşmasını önleyen hassas dünya-kare dönüşüm fonksiyonu
inline int WorldToTileCoord(float worldPos) {
    return (int)std::floor(worldPos / (float)TILE_SIZE);
}
