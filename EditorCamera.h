#pragma once
#include "raylib.h"
#include "raymath.h"

class EditorCamera {
public:
    Camera2D camera;

    EditorCamera();
    void Update();
};
