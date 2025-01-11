#include <imgui.h>
//#include "Header/UI.hpp"
#include "../Properties/prop.hpp"
#include "string"

//Show show;

extern placedCube PlacedCube;

class UI
{
public:
    bool EditorWindow = true;
    bool PreviewWindow = false;
    bool CubeProperties = false;
    bool States = false;
    bool Layers = false;
    EditorSettings editorSettings;

	void BeginMenu()
	{
        if (ImGui::BeginMainMenuBar())
        {
            if (ImGui::BeginMenu("View"))
            {
                if (ImGui::MenuItem("Editor Window", NULL, &EditorWindow))
                {
                    PreviewWindow = false;
                    EditorWindow = true;
                }
                if (ImGui::MenuItem("Preview Window", NULL, &PreviewWindow))
                {
                    PreviewWindow = true;
                    EditorWindow = false;
                }
                ImGui::EndMenu();
            }

            if (ImGui::BeginMenu("Edit"))
            {
                if (ImGui::MenuItem("Clear All Cubes"))
                {
                    //placedCubes.clear(); // Clear all cubes
                }
                ImGui::EndMenu();
            }
            if (ImGui::BeginMenu("Windows"))
            {
                if (ImGui::MenuItem("Cube Properties", NULL, &CubeProperties))
                {
                    CubeProperties = true;
                }
                if (ImGui::MenuItem("Stats"))
                {
                    States = true;
                }
                if (ImGui::MenuItem("Layer", NULL, &Layers))
                {
                    Layers = true;
                }
                ImGui::EndMenu();

            }
            ImGui::EndMainMenuBar();
        }
	}

    void BeginWindows()
    {
        if (CubeProperties)
        {
            //rlImGuiBegin();
            editorSettings.cubeColor = {
                (unsigned char)(editorSettings.color[0] * 255),
                    (unsigned char)(editorSettings.color[1] * 255),
                    (unsigned char)(editorSettings.color[2] * 255),
                    (unsigned char)(editorSettings.color[3] * 255)
            };
            static char buffer[256] = "";
            ImGui::Begin("Cube Properties", NULL);
            ImGui::BeginChild("Color");
            ImGui::ColorPicker4("color", editorSettings.color);
            ImGui::EndChild();
            ImGui::BeginChild("Texture");
            ImGui::InputText("Texture Path", buffer, sizeof(buffer));
            if (ImGui::Button("Apply"))
            {
                editorSettings.currentTexturePath = std::string(buffer);
                editorSettings.currentTexture = LoadTexture(buffer);
            }

            ImGui::EndChild();
            ImGui::End();
            //rlImGuiEnd();
        }
        if (Layers)
        {
            int layerInt = 0;
            ImGui::Begin("Layers");
            ImGui::SliderInt("Layer", &layerInt, 0, 4);
            switch (layerInt)
            {
            case 0:
                editorSettings.currentLayer = Layer::FLOOR;
                break;  

            case 1:
                editorSettings.currentLayer = Layer::WALL;
                break;

            case 2:
                editorSettings.currentLayer = Layer::CEILING;
                break;

            case 3:
                editorSettings.currentLayer = Layer::DECORATION;
                break;
            }
            ImGui::End();
        }
    }
};

