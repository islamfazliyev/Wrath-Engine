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
    
    

    // Store placed cubes
    std::vector<placedCube> placedCubes;

    // Preview cube position
    Vector3 previewCubePosition = { 0.0f, 0.0f, 0.0f };
    mesh meshes;
    // UI state flags
    
    Camera3D camera = SetupCamera(CameraSettings::PREVIEW);
    CameraSettings::Mode currentMode = CameraSettings::EDITOR_VIEW;
    /*Texture currentTexture;
    std::string currentTexturePath{""};*/
    // Initialize RlImGui
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

        switch (MenuBar.editorSettings.currentLayer)
        {
        case Layer::FLOOR:
            previewCubePosition.y = 0;
            break;
        case Layer::WALL:
            previewCubePosition.y = 1;
            break;
        case Layer::CEILING:
            previewCubePosition.y = 2;
            break;
        case Layer::DECORATION:
            previewCubePosition.y = 0;
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
            previewCubePosition.x = gridX - (GRID_COLS / 2);
            previewCubePosition.z = gridY - (GRID_ROWS / 2);
        }
        if (!ImGui::GetIO().WantCaptureMouse)
        {
            // Check for left mouse button click to place cube
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                // Check if this position is not already occupied
                bool positionOccupied = false;
                for (const auto& cube : placedCubes) {
                    if (cube.position.x == previewCubePosition.x && cube.position.z == previewCubePosition.z && cube.position.y == previewCubePosition.y) {
                        positionOccupied = true;
                        break;
                    }
                }

                // Place cube if position is not occupied
                if (!positionOccupied) {
                    Color cubeColor = {
                    (unsigned char)(MenuBar.editorSettings.color[0] * 255),
                        (unsigned char)(MenuBar.editorSettings.color[1] * 255),
                        (unsigned char)(MenuBar.editorSettings.color[2] * 255),
                        (unsigned char)(MenuBar.editorSettings.color[3] * 255)
                    };
                    
                    //Texture cubeTexture = currentTexture;
                    placedCubes.push_back({ previewCubePosition,MenuBar.editorSettings.currentLayer,cubeColor, MenuBar.editorSettings.currentTexture});
                }
            }

            // Check for right mouse button to remove cubes
            if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) {

                auto it = std::remove_if(placedCubes.begin(), placedCubes.end(),
                    [&previewCubePosition](const placedCube& cube) {
                        return cube.position.x == previewCubePosition.x && cube.position.z == previewCubePosition.z && cube.position.y == previewCubePosition.y;
                    }
                );
                placedCubes.erase(it, placedCubes.end());
            }
        }
        

        // Begin 3D drawing
        BeginDrawing();
        ClearBackground(RAYWHITE);

        BeginMode3D(camera);

        // Draw grid using Raylib's DrawGrid function
        DrawGrid(GRID_COLS, GRID_SPACING);

        // Draw preview wireframe cube
        DrawCubeWires(previewCubePosition, 1.2f, 1.2f, 1.2f, GREEN);

        // Draw placed cubes
        for (const auto& cube : placedCubes)
        {
            meshes.DrawCubeTextureRec(cube.texture, Rectangle{0,float(cube.texture.height),float(cube.texture.width), float(cube.texture.height)}, cube.position, 1, 1, 1, cube.color);
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