#include "procedure_geometry.h"
#include "bone_geometry.h"
#include "config.h"
// #include <GL/glew.h>

void create_floor(std::vector<glm::vec4>& floor_vertices, std::vector<glm::uvec3>& floor_faces)
{
	floor_vertices.push_back(glm::vec4(kFloorXMin, kFloorY, kFloorZMax, 1.0f));
	floor_vertices.push_back(glm::vec4(kFloorXMax, kFloorY, kFloorZMax, 1.0f));
	floor_vertices.push_back(glm::vec4(kFloorXMax, kFloorY, kFloorZMin, 1.0f));
	floor_vertices.push_back(glm::vec4(kFloorXMin, kFloorY, kFloorZMin, 1.0f));
	floor_faces.push_back(glm::uvec3(0, 1, 2));
	floor_faces.push_back(glm::uvec3(2, 3, 0));
}

// FIXME: create cylinders and lines for the bones
// Hints: Generate a lattice in [-0.5, 0, 0] x [0.5, 1, 0] We wrap this
// around in the vertex shader to produce a very smooth cylinder.  We only
// need to send a small number of points.  Controlling the grid size gives a
// nice wireframe.

void create_cylinder_circle(std::vector<glm::vec4>& vertices, std::vector<glm::uvec2>& faces, glm::mat4 LtW, glm::vec3 position, int& face_i)
{
	int num_verts = 360;
	int initial_face_i = face_i;

   	for (int i=0; i < num_verts; i++) {
			float theta = 2.0f * 3.141593f * float(i) / (num_verts / 4);
	    glm::vec4 v = glm::vec4(cosf(theta)*kCylinderRadius + position.x, position.y, sinf(theta)*kCylinderRadius + position.z, 1.0f);

			// Account for local to world trnaslation
			v = LtW * v;

			vertices.push_back(v);

			if (face_i != initial_face_i){
				faces.push_back(glm::uvec2(face_i - 1, face_i));
			}
			face_i++;
   	}
}

void create_cylinder_lines(std::vector<glm::vec4>& vertices, std::vector<glm::uvec2>& faces, glm::mat4 LtW, glm::vec3 position, float length, int interval, int& face_i)
{
		int num_verts = 360;
		int initial_face_i = face_i;

   	for (int i=0; i < num_verts; i += interval) {
			float theta = 2.0f * 3.141593f * float(i) / (num_verts / 4);
	    glm::vec4 v = glm::vec4(cosf(theta)*kCylinderRadius + position.x, position.y, sinf(theta)*kCylinderRadius + position.z, 1.0f);
			glm::vec4 v2 = glm::vec4(cosf(theta)*kCylinderRadius + position.x, position.y + length, sinf(theta)*kCylinderRadius + position.z, 1.0f);

			// Account for local to world trnaslation
			v = LtW * v;
			v2 = LtW * v2;

			vertices.push_back(v);
			vertices.push_back(v2);

			faces.push_back(glm::uvec2(face_i - 1, face_i));
			face_i+=2;
   	}
}

void create_cylinder(std::vector<glm::vec4>& vertices, std::vector<glm::uvec2>& faces, glm::mat4 LocalToWorld, float length)
{
	// float length = 2.0f; // Get from bone.
	// glm::mat4 LocalToWorld = glm::mat4(1.0f); // Get from bone

	int face_counter = 0;

	create_cylinder_circle(vertices, faces, LocalToWorld, glm::vec3(0.0f, 0.0f, 0.0f), face_counter);
	create_cylinder_circle(vertices, faces, LocalToWorld, glm::vec3(0.0f, length * 0.5f, 0.0f), face_counter);
	create_cylinder_circle(vertices, faces, LocalToWorld, glm::vec3(0.0f, length, 0.0f), face_counter);

	int line_interval = 10;

	create_cylinder_lines(vertices, faces, LocalToWorld, glm::vec3(0.0f, 0.0f, 0.0f), length, line_interval, face_counter);
}
