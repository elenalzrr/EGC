#include "object2D_tema.h"

#include <vector>

#include "core/engine.h"
#include "utils/gl_utils.h"

Mesh* object2D_tema::CreateSquare(const std::string& name, glm::vec3 leftBottomCorner, float length, glm::vec3 color, bool fill)
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
		indices.push_back(0);
		indices.push_back(2);
	}

	square->InitFromData(vertices, indices);
	return square;
}
Mesh* object2D_tema::CreateRectangle(const std::string& name, glm::vec3 leftBottomCorner, float length, float width, glm::vec3 color, bool fill)
{
	glm::vec3 corner = glm::vec3(0, 0, 0);

	std::vector<VertexFormat> vertices =
	{
		VertexFormat(corner, color),
		VertexFormat(corner + glm::vec3(length, 0, 0), color),
		VertexFormat(corner + glm::vec3(length, width, 0), color),
		VertexFormat(corner + glm::vec3(0, width, 0), color)
	};

	Mesh* square = new Mesh(name);
	std::vector<unsigned int> indices = { 0, 1, 2, 3 };

	if (!fill) {
		square->SetDrawMode(GL_LINE_LOOP);
	}
	else {
		indices.push_back(0);
		indices.push_back(2);
	}

	square->InitFromData(vertices, indices);
	return square;
}
Mesh* object2D_tema::CreatePro(const std::string& name)
{
	glm::vec3 corner = glm::vec3(0, 0, 0);

	std::vector<VertexFormat> vertices =
	{
		VertexFormat(corner, glm::vec3(0.03f, 0.12f, 0.60f)),
		VertexFormat(corner + glm::vec3(0.3f, 0, 0),  glm::vec3(0.03f, 0.12f, 0.60f)),
		VertexFormat(corner + glm::vec3(0.3f, 0.4f, 0),  glm::vec3(0.03f, 0.12f, 0.60f)),
		VertexFormat(corner + glm::vec3(0, 0.4f, 0),  glm::vec3(0.03f, 0.12f, 0.60f))
	};

	Mesh* square = new Mesh(name);
	std::vector<unsigned int> indices = { 0, 1, 2, 3 };


	indices.push_back(0);
	indices.push_back(2);

	square->InitFromData(vertices, indices);
	return square;
}
Mesh* object2D_tema::CreateCircle(const std::string& name, glm::vec3 origin, float radius, glm::vec3 color, bool fill) {
	std::vector<VertexFormat> vertices;

	vertices.push_back(VertexFormat(origin, color));
	for (int i = 0; i < 360; ++i) {
		vertices.push_back(VertexFormat(glm::vec3(origin.x + sin(RADIANS(i)) * radius,
			origin.y + cos(RADIANS(i)) * radius, 0), color));

	}

	std::vector<unsigned int> indices;
	for (int i = 0; i < 360; ++i) {
		indices.push_back(0);
		indices.push_back(i);
		indices.push_back(i + 1);
	}
	indices.push_back(0);
	indices.push_back(359);
	indices.push_back(1);

	Mesh* circle = new Mesh(name);
	if (!fill) {
		circle->SetDrawMode(GL_LINE_LOOP);
	}
	circle->InitFromData(vertices, indices);
	return circle;
}
