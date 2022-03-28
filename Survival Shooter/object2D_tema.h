#pragma once

#include <string>

#include "core/gpu/mesh.h"
#include "utils/glm_utils.h"


namespace object2D_tema
{
	Mesh* CreateSquare(const std::string& name, glm::vec3 leftBottomCorner, float length, glm::vec3 color, bool fill);
	Mesh* CreateRectangle(const std::string& name, glm::vec3 leftBottomCorner, float length, float width, glm::vec3 color, bool fill);
	Mesh* CreatePro(const std::string& name);
	Mesh* CreateCircle(const std::string& name, glm::vec3 origin, float radius, glm::vec3 color, bool fill);
}
