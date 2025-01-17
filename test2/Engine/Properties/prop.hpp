#pragma once
#include "raylib.h"
#include <string>

constexpr int SCREEN_WIDTH = 800;
constexpr int SCREEN_HEIGHT = 600;
constexpr int GRID_COLS = 20;
constexpr int GRID_ROWS = 15;
constexpr float GRID_SPACING = 1.0f;

namespace CameraSettings {
    enum Mode {
        EDITOR_VIEW,
        PREVIEW
    };
}

enum class Layer
{
    FLOOR,
    WALL,
    CEILING,
    DECORATION
};

struct placedCube
{
    Vector3 position;
    Layer layer;
    Color color;
    Texture texture;
};

struct EditorSettings {
    Texture currentTexture;
    std::string currentTexturePath;
    float color[4];
    Layer currentLayer;
    Color cubeColor;
};


