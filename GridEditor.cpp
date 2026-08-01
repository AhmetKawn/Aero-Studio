#include "GridEditor.h"
#include <algorithm>

GridEditor::GridEditor() {
    currentColor = BLUE;
    currentTool = TOOL_PAINT;
}

void GridEditor::Update(const Camera2D& camera) {
    // Araç ve renk seçim kısayolları
    if (IsKeyPressed(KEY_ONE)) { currentColor = BLUE; currentTool = TOOL_PAINT; }
    if (IsKeyPressed(KEY_TWO)) { currentColor = RED; currentTool = TOOL_PAINT; }
    if (IsKeyPressed(KEY_THREE)) { currentColor = GREEN; currentTool = TOOL_PAINT; }
    if (IsKeyPressed(KEY_FOUR)) { currentTool = TOOL_ERASE; } // 4: Silgi
    if (IsKeyPressed(KEY_C)) { placedTiles.clear(); }          // C: Temizle

    // Sol tık ile işlem yapma (Boyama veya Silme)
    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT) || IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        Vector2 mouseWorldPos = GetScreenToWorld2D(GetMousePosition(), camera);
        int mouseTileX = WorldToTileCoord(mouseWorldPos.x);
        int mouseTileY = WorldToTileCoord(mouseWorldPos.y);

        if (currentTool == TOOL_PAINT) {
            // Aynı koordinat varsa rengini güncelle, yoksa ekle
            bool found = false;
            for (auto& tile : placedTiles) {
                if (tile.x == mouseTileX && tile.y == mouseTileY) {
                    tile.color = currentColor;
                    found = true;
                    break;
                }
            }
            if (!found) {
                placedTiles.push_back({mouseTileX, mouseTileY, currentColor});
            }
        } 
        else if (currentTool == TOOL_ERASE) {
            // Silgi modu: Eşleşen koordinattaki bloğu sil
            placedTiles.erase(
                std::remove_if(placedTiles.begin(), placedTiles.end(), [mouseTileX, mouseTileY](const PlacedTile& t) {
                    return t.x == mouseTileX && t.y == mouseTileY;
                }),
                placedTiles.end()
            );
        }
    }
}

void GridEditor::Draw(const Camera2D& camera) {
    // Izgara çizgileri (Genişletilmiş alan)
    int startX = -3000;
    int endX = 5000;
    int startY = -3000;
    int endY = 5000;

    for (int x = startX; x <= endX; x += TILE_SIZE) {
        DrawLine(x, startY, x, endY, LIGHTGRAY);
    }
    for (int y = startY; y <= endY; y += TILE_SIZE) {
        DrawLine(startX, y, endX, y, LIGHTGRAY);
    }

    // Orijin (Merkez) noktası
    DrawLine(-30, 0, 30, 0, RED);
    DrawLine(0, -30, 0, 30, GREEN);

    // Yerleştirilmiş blokları çiz
    for (const auto& tile : placedTiles) {
        DrawRectangle(tile.x * TILE_SIZE, tile.y * TILE_SIZE, TILE_SIZE, TILE_SIZE, tile.color);
    }

    // Farenin altındaki aktif imleç (Boya veya Silgi önizlemesi)
    Vector2 mouseWorldPos = GetScreenToWorld2D(GetMousePosition(), camera);
    int mouseTileX = WorldToTileCoord(mouseWorldPos.x);
    int mouseTileY = WorldToTileCoord(mouseWorldPos.y);

    Color previewColor = (currentTool == TOOL_PAINT) ? Fade(currentColor, 0.4f) : Fade(RED, 0.5f);
    DrawRectangle(mouseTileX * TILE_SIZE, mouseTileY * TILE_SIZE, TILE_SIZE, TILE_SIZE, previewColor);
}
