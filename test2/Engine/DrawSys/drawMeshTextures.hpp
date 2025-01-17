#pragma once
#include "raylib.h"
#include "rlgl.h" 


class mesh
{
public:
    void DrawCubeTextureRec(Texture2D texture, Rectangle source, Vector3 position, float width, float height, float length, Color color)
    {
        float x = position.x;
        float y = position.y;
        float z = position.z;
        float texWidth = (float)texture.width;
        float texHeight = (float)texture.height;

        // Set desired texture to be enabled while drawing following vertex data
        rlSetTexture(texture.id);

        // We calculate the normalized texture coordinates for the desired texture-source-rectangle
        // It means converting from (tex.width, tex.height) coordinates to [0.0f, 1.0f] equivalent 
        rlBegin(RL_QUADS);
        rlColor4ub(color.r, color.g, color.b, color.a);

        // Front face
        rlNormal3f(0.0f, 0.0f, 1.0f);
        rlTexCoord2f(source.x / texWidth, (source.y + source.height) / texHeight);
        rlVertex3f(x - width / 2, y - height / 2, z + length / 2);
        rlTexCoord2f((source.x + source.width) / texWidth, (source.y + source.height) / texHeight);
        rlVertex3f(x + width / 2, y - height / 2, z + length / 2);
        rlTexCoord2f((source.x + source.width) / texWidth, source.y / texHeight);
        rlVertex3f(x + width / 2, y + height / 2, z + length / 2);
        rlTexCoord2f(source.x / texWidth, source.y / texHeight);
        rlVertex3f(x - width / 2, y + height / 2, z + length / 2);

        // Back face
        rlNormal3f(0.0f, 0.0f, -1.0f);
        rlTexCoord2f((source.x + source.width) / texWidth, (source.y + source.height) / texHeight);
        rlVertex3f(x - width / 2, y - height / 2, z - length / 2);
        rlTexCoord2f((source.x + source.width) / texWidth, source.y / texHeight);
        rlVertex3f(x - width / 2, y + height / 2, z - length / 2);
        rlTexCoord2f(source.x / texWidth, source.y / texHeight);
        rlVertex3f(x + width / 2, y + height / 2, z - length / 2);
        rlTexCoord2f(source.x / texWidth, (source.y + source.height) / texHeight);
        rlVertex3f(x + width / 2, y - height / 2, z - length / 2);

        // Top face
        rlNormal3f(0.0f, 1.0f, 0.0f);
        rlTexCoord2f(source.x / texWidth, source.y / texHeight);
        rlVertex3f(x - width / 2, y + height / 2, z - length / 2);
        rlTexCoord2f(source.x / texWidth, (source.y + source.height) / texHeight);
        rlVertex3f(x - width / 2, y + height / 2, z + length / 2);
        rlTexCoord2f((source.x + source.width) / texWidth, (source.y + source.height) / texHeight);
        rlVertex3f(x + width / 2, y + height / 2, z + length / 2);
        rlTexCoord2f((source.x + source.width) / texWidth, source.y / texHeight);
        rlVertex3f(x + width / 2, y + height / 2, z - length / 2);

        // Bottom face
        rlNormal3f(0.0f, -1.0f, 0.0f);
        rlTexCoord2f((source.x + source.width) / texWidth, source.y / texHeight);
        rlVertex3f(x - width / 2, y - height / 2, z - length / 2);
        rlTexCoord2f(source.x / texWidth, source.y / texHeight);
        rlVertex3f(x + width / 2, y - height / 2, z - length / 2);
        rlTexCoord2f(source.x / texWidth, (source.y + source.height) / texHeight);
        rlVertex3f(x + width / 2, y - height / 2, z + length / 2);
        rlTexCoord2f((source.x + source.width) / texWidth, (source.y + source.height) / texHeight);
        rlVertex3f(x - width / 2, y - height / 2, z + length / 2);

        // Right face
        rlNormal3f(1.0f, 0.0f, 0.0f);
        rlTexCoord2f((source.x + source.width) / texWidth, (source.y + source.height) / texHeight);
        rlVertex3f(x + width / 2, y - height / 2, z - length / 2);
        rlTexCoord2f((source.x + source.width) / texWidth, source.y / texHeight);
        rlVertex3f(x + width / 2, y + height / 2, z - length / 2);
        rlTexCoord2f(source.x / texWidth, source.y / texHeight);
        rlVertex3f(x + width / 2, y + height / 2, z + length / 2);
        rlTexCoord2f(source.x / texWidth, (source.y + source.height) / texHeight);
        rlVertex3f(x + width / 2, y - height / 2, z + length / 2);

        // Left face
        rlNormal3f(-1.0f, 0.0f, 0.0f);
        rlTexCoord2f(source.x / texWidth, (source.y + source.height) / texHeight);
        rlVertex3f(x - width / 2, y - height / 2, z - length / 2);
        rlTexCoord2f((source.x + source.width) / texWidth, (source.y + source.height) / texHeight);
        rlVertex3f(x - width / 2, y - height / 2, z + length / 2);
        rlTexCoord2f((source.x + source.width) / texWidth, source.y / texHeight);
        rlVertex3f(x - width / 2, y + height / 2, z + length / 2);
        rlTexCoord2f(source.x / texWidth, source.y / texHeight);
        rlVertex3f(x - width / 2, y + height / 2, z - length / 2);

        rlEnd();

        rlSetTexture(0);
    }
};

