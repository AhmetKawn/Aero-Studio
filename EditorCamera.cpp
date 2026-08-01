#include "EditorCamera.h"

EditorCamera::EditorCamera() {
    camera = { 0 };
    camera.zoom = 1.0f;
}

void EditorCamera::Update() {
    // Farenin sağ tuşuna basılı tutarak kamerayı hareket ettir (Pan)
    if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT)) {
        Vector2 delta = GetMouseDelta();
        delta = Vector2Scale(delta, -1.0f / camera.zoom);
        camera.target = Vector2Add(camera.target, delta);
    }

    // Fare tekerleği ile pürüzsüz Zoom yapma
    float wheel = GetMouseWheelMove();
    if (wheel != 0) {
        Vector2 mouseWorldPos = GetScreenToWorld2D(GetMousePosition(), camera);
        camera.offset = GetMousePosition();
        camera.target = mouseWorldPos;
        
        camera.zoom += (wheel * 0.1f);
        if (camera.zoom < 0.2f) camera.zoom = 0.2f;   
        if (camera.zoom > 3.0f) camera.zoom = 3.0f;   
    }
}
