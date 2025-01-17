#include "raylib.h"
#include <vector>
#include <cmath>
#include <imgui.h>
#include <rlImgui.h>
#include <rlgl.h>
#include "DrawSys/drawMeshTextures.hpp"
#include "UI/menuBar.hpp"
#include <iostream>
#include <algorithm>
#include <string>
#include "Properties/prop.hpp"
#include "TileEditor/tile.hpp"

Camera3D SetupCamera(CameraSettings::Mode mode)
{
    Camera3D camera = { 0 };
    switch (mode)
    {
    case CameraSettings::EDITOR_VIEW:
        camera.position = Vector3{ 0.0f, 20.0f, 0.0f };  // Directly above the grid
        camera.target = Vector3{ 0.0f, 0.0f, 0.0f };
        camera.up = Vector3{ 0.0f, 0.0f, -1.0f };
        camera.fovy = 45.0f;
        camera.projection = CAMERA_PERSPECTIVE;
        break;
    case CameraSettings::PREVIEW:
        camera.position = Vector3{ 10.0f, 10.0f, 10.0f };  // Angled perspective
        camera.target = Vector3{ 0.0f, 0.0f, 0.0f };
        camera.up = Vector3{ 0.0f, 1.0f, 0.0f };
        camera.fovy = 45.0f;
        camera.projection = CAMERA_PERSPECTIVE;
        break;
    }
    return camera;
}

//float color[4];
//Layer currentLayer = Layer::FLOOR;

int main() {

    // Initialize window
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Cube Placement with Preview");
    SetTargetFPS(60);
    UI MenuBar;
    TileDraw tileDraw(MenuBar);
    
    
    
    Camera3D camera = SetupCamera(CameraSettings::PREVIEW);
    CameraSettings::Mode currentMode = CameraSettings::EDITOR_VIEW;
    
    rlImGuiSetup(true);
    
    while (!WindowShouldClose()) {
        if (MenuBar.EditorWindow && !MenuBar.PreviewWindow)
        {
            currentMode = CameraSettings::EDITOR_VIEW;
            camera = SetupCamera(CameraSettings::EDITOR_VIEW);
        }
        if (!MenuBar.EditorWindow && MenuBar.PreviewWindow)
        {
            currentMode = CameraSettings::PREVIEW;
            camera = SetupCamera(CameraSettings::PREVIEW);
        }
        if (currentMode == CameraSettings::PREVIEW)
        {
            UpdateCamera(&camera, CAMERA_FREE);
        }

        switch ((int)MenuBar.editorSettings.currentLayer)
        {
        case 0:
            tileDraw.previewCubePosition.y = 0;
            break;
        case 1:
            tileDraw.previewCubePosition.y = 1;
            break;
        case 2:
            tileDraw.previewCubePosition.y = 2;
            break;
        case 3:
            tileDraw.previewCubePosition.y = 0;
            break;
        default:
            break;
        }
        // Get mouse position
        Vector2 mousePos = GetMousePosition();

            // Convert mouse position to grid coordinates
        int gridX = static_cast<int>((mousePos.x / SCREEN_WIDTH) * GRID_COLS);
        int gridY = static_cast<int>((mousePos.y / SCREEN_HEIGHT) * GRID_ROWS);
        if (currentMode == CameraSettings::EDITOR_VIEW)
        {

            // Update preview cube position based on grid
            tileDraw.previewCubePosition.x = gridX - (GRID_COLS / 2);
            tileDraw.previewCubePosition.z = gridY - (GRID_ROWS / 2);
        }
        
        tileDraw.Update();

        // Begin 3D drawing
        BeginDrawing();
        ClearBackground(RAYWHITE);

        BeginMode3D(camera);

        // Draw grid using Raylib's DrawGrid function
        DrawGrid(GRID_COLS, GRID_SPACING);

        // Draw preview wireframe cube
        DrawCubeWires(tileDraw.previewCubePosition, 1.2f, 1.2f, 1.2f, GREEN);

        // Draw placed cubes
        for (const auto& cube : tileDraw.placedCubes)
        {
            tileDraw.meshes.DrawCubeTextureRec(cube.texture, Rectangle{0,float(cube.texture.height),float(cube.texture.width), float(cube.texture.height)}, cube.position, 1, 1, 1, cube.color);
            DrawCubeWires(cube.position, 1.0f, 1.0f, 1.0f, DARKBLUE);
        }

        EndMode3D();

        // Draw grid coordinates and instructions
        DrawText(TextFormat("Grid X: %d, Grid Y: %d", gridX, gridY), 10, 10, 20, BLACK);
        DrawText("Left Click: Place Cube", 10, 40, 20, BLACK);
        DrawText("Right Click: Remove Cube", 10, 70, 20, BLACK);

        // ImGui Rendering
        rlImGuiBegin();
        
        MenuBar.BeginMenu();
        MenuBar.BeginWindows();
        rlImGuiEnd();
        EndDrawing();
    }

    // Cleanup RlImGui
    rlImGuiShutdown();

    // Close window and OpenGL context
    CloseWindow();

    return 0;
}