#include "object2D.h"

#include <vector>
#include "core/engine.h"
#include "utils/gl_utils.h"


Mesh* object2D::CreateRectangle(
    const std::string& name,
    glm::vec3 leftBottomCorner,
    float width,
    float length,
    glm::vec3 color,
    bool fill)
{
    glm::vec3 corner = leftBottomCorner;

    std::vector<VertexFormat> vertices =
    {
        VertexFormat(corner, color),
        VertexFormat(corner + glm::vec3(width, 0, 0), color),
        VertexFormat(corner + glm::vec3(width, length, 0), color),
        VertexFormat(corner + glm::vec3(0, length, 0), color)
    };

    Mesh* rectangle = new Mesh(name);
    std::vector<unsigned int> indices = { 0, 1, 2, 3 };

    if (!fill) {
        rectangle->SetDrawMode(GL_LINE_LOOP);
    }
    else {
        // Draw 2 triangles. Add the remaining 2 indices
        indices.push_back(0);
        indices.push_back(2);
        indices.push_back(4);
        indices.push_back(2);
    }

    rectangle->InitFromData(vertices, indices);
    return rectangle;
}


Mesh* object2D::CreateCircle(std::string name, float radius, float centreX,
    float centreY, glm::vec3 color, bool fill)
{
    glm::vec3 centerCircle = glm::vec3(centreX, centreY, 0.0f);
    std::vector<unsigned int> indices;
    std::vector<VertexFormat> vertices;
    vertices.push_back(VertexFormat(glm::vec3(centreX, centreY, 0), color));
    int i;
    int triangleAmount = 360; // number of triangles used to draw circle

    float twicePi = 2.0f * M_PI;

    for (i = 0; i <= triangleAmount; i++) {
        indices.push_back(0);
        indices.push_back(i);
        indices.push_back(i + 1);

        float x = radius * cos(RADIANS(i));
        float y = radius * sin(RADIANS(i));
        vertices.push_back(VertexFormat(glm::vec3(centreX + x, centreY + y, 0.0f), color));
    }
    indices.push_back(0);
    indices.push_back(triangleAmount - 1);
    indices.push_back(1);

    Mesh* circle = new Mesh(name);

    if (!fill) {
        circle->SetDrawMode(GL_LINE_LOOP);
    }

    // Initializes the mesh object and upload data to GPU using the provided data buffers
    circle->InitFromData(vertices, indices);
    return circle;
}


Mesh* object2D::CreateTriangle(std::string name, glm::vec3 leftBottomCorner,
    float width, float length, glm::vec3 color, bool fill)
{
    glm::vec3 corner = leftBottomCorner;

    std::vector<VertexFormat> vertices =
    {
        // VertexFormat is a structure for vertex with 2 parameters (position, color).
        VertexFormat(corner, color),
        VertexFormat(corner + glm::vec3(width / 2, length / 2, 0), color),
        VertexFormat(corner + glm::vec3(0, length, 0), color)
    };

    Mesh* triangle = new Mesh(name);
    std::vector<unsigned int> indices = { 0, 1, 2 };

    if (!fill) {
        triangle->SetDrawMode(GL_LINE_LOOP);
    }
    // Initializes the mesh object and upload data to GPU using the provided data buffers
    triangle->InitFromData(vertices, indices);
    return triangle;
}

Mesh* object2D::CreateSquare(
    const std::string& name,
    glm::vec3 leftBottomCorner,
    float length,
    glm::vec3 color,
    bool fill)
{
    glm::vec3 corner = leftBottomCorner;

    std::vector<VertexFormat> vertices =
    {
        VertexFormat(corner, color),
        VertexFormat(corner + glm::vec3(length, 0, 0), color),
        VertexFormat(corner + glm::vec3(length, length, 0), color),
        VertexFormat(corner + glm::vec3(0, length, 0), color)
    };

    Mesh* square = new Mesh(name);
    std::vector<unsigned int> indices = { 0, 1, 2, 3 };

    if (!fill) {
        square->SetDrawMode(GL_LINE_LOOP);
    }
    else {
        // Draw 2 triangles. Add the remaining 2 indices
        indices.push_back(0);
        indices.push_back(2);
    }

    square->InitFromData(vertices, indices);
    return square;
}