#include "raylib.h"
#include "Globals.h"
#include "EditorCamera.h"
#include "GridEditor.h"

int main() {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Aero Studio - Pro Level Editor");

    EditorCamera editorCamera;
    GridEditor gridEditor;

    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        // Güncellemeler
        editorCamera.Update();
        gridEditor.Update(editorCamera.camera);

        // Çizimler
        BeginDrawing();
        ClearBackground(RAYWHITE);

        BeginMode2D(editorCamera.camera);
            gridEditor.Draw(editorCamera.camera);
        EndMode2D();

        // Gelişmiş Arayüz Bilgi Paneli (Sabit)
        DrawRectangle(10, 10, 360, 110, Fade(DARKGRAY, 0.85f));
        DrawText("AERO STUDIO - v1.1 Pro", 20, 20, 15, RAYWHITE);
        DrawText("Sag Tik + Surukle: Kamera Pan | Tekerlek: Zoom", 20, 45, 10, LIGHTGRAY);
        DrawText("Sol Tik: Blok Koy / Sil", 20, 60, 10, LIGHTGRAY);
        DrawText("1: Mavi | 2: Kirmizi | 3: Yesil | 4: Silgi", 20, 75, 10, YELLOW);
        DrawText("C: Tum Haritayi Temizle", 20, 95, 10, LIGHTGRAY);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
