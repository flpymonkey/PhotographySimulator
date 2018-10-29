#ifndef PROCEDURE_GEOMETRY_H
#define PROCEDURE_GEOMETRY_H

#include <vector>
#include <glm/glm.hpp>

class LineMesh;

void create_floor(std::vector<glm::vec4>& floor_vertices, std::vector<glm::uvec3>& floor_faces);
// FIXME: Add functions to generate the bone mesh.
void create_cylinder_circle(std::vector<glm::vec4>& vertices, std::vector<glm::uvec2>& faces, glm::vec3 position, int face_i);
void create_cylinder_line(std::vector<glm::vec4>& vertices, std::vector<glm::uvec2>& faces, glm::vec3 position, float i, int face_i);
void create_cylinder(std::vector<glm::vec4>& vertices, std::vector<glm::uvec2>& faces);

#endif
