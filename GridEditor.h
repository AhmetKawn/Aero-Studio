#pragma once
#include "raylib.h"
#include "Globals.h"
#include <vector>

enum EditorTool {
    TOOL_PAINT = 0,
    TOOL_ERASE
};

struct PlacedTile {
    int x, y;
    Color color;
};

class GridEditor {
public:
    std::vector<PlacedTile> placedTiles;
    Color currentColor;
    EditorTool currentTool;

    GridEditor();
    void Update(const Camera2D& camera);
    void Draw(const Camera2D& camera);
};
