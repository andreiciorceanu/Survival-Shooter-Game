#pragma once

#include <string>

#include "core/gpu/mesh.h"
#include "utils/glm_utils.h"


namespace object2D
{
    // Create rectangle with given bottom left corner, length and color
    Mesh* CreateRectangle(const std::string& name, glm::vec3 leftBottomCorner, float width, float length, glm::vec3 color, bool fill = true);
    // Create square with given bottom left corner, length and color
    Mesh* CreateSquare(const std::string &name, glm::vec3 leftBottomCorner, float length, glm::vec3 color, bool fill = true);

    // Create circle with given bottom left corner, length and color
    Mesh* CreateCircle(std::string name, float radius,
        float centreX, float centreY, glm::vec3 color, bool fill = true);

    // Create triangle with given bottom left corner, length and color
    Mesh* CreateTriangle(std::string name, glm::vec3 leftBottomCorner,
        float width, float length, glm::vec3 color, bool fill = true);
}
