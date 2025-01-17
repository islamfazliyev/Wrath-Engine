#pragma once
#include "raylib.h"
#include "imgui.h"
#include "../UI/menuBar.hpp"
#include "../Properties/prop.hpp"
#include <vector>
#include "../DrawSys/drawMeshTextures.hpp"


class UI;

class TileDraw
{
public:
    UI& menuBar;
    std::vector<placedCube> placedCubes;
    Vector3 previewCubePosition = { 0.0f, 0.0f, 0.0f };
    mesh meshes;

    TileDraw(UI& menu) : menuBar(menu) {}

    void Update()
    {
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
                    (unsigned char)(menuBar.editorSettings.color[0] * 255),
                        (unsigned char)(menuBar.editorSettings.color[1] * 255),
                        (unsigned char)(menuBar.editorSettings.color[2] * 255),
                        (unsigned char)(menuBar.editorSettings.color[3] * 255)
                    };

                    //Texture cubeTexture = currentTexture;
                    placedCubes.push_back({ previewCubePosition, menuBar.editorSettings.currentLayer,cubeColor, menuBar.editorSettings.currentTexture });
                }
            }

            // Check for right mouse button to remove cubes
            if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) {

                auto it = std::remove_if(placedCubes.begin(), placedCubes.end(),
                    [&](const placedCube& cube) {
                        return cube.position.x == previewCubePosition.x &&
                            cube.position.z == previewCubePosition.z &&
                            cube.position.y == previewCubePosition.y;
                    }
                );
                placedCubes.erase(it, placedCubes.end());
            }
        }
    }

private:
};