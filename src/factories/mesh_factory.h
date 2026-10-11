#pragma once
#include "../config.h"
#include "../components/render_component.h"

struct StaticMesh {
    unsigned int VAO, VBO, vertexCount;
};


class MeshFactory{

    public:
    // ~MeshFactory();
    StaticMesh make_cube_mesh(
        glm::vec3 size
    );
    StaticMesh make_obj_mesh(
        const char* filepath, glm::mat4 preTransform
    );
    unsigned int make_texture(const char* filepath);
    glm::vec3 read_vec3(std::vector<std::string> words, float w);
    glm::vec2 read_vec2(std::vector<std::string> words);

    void read_face(std::vector<std::string> words);
    void read_corner(std::string description);

    private:

    std::unordered_map<ObjectType, unsigned int> VAOs;
    std::unordered_map<ObjectType, unsigned int> vertexCounts;
    std::unordered_map<ObjectType, unsigned int> VBOs;
    std::unordered_map<ObjectType, unsigned int> textures;

    std::vector<glm::vec3> v;
    std::vector<glm::vec2> vt;
    std::vector<glm::vec3> vn;
    std::vector<float> vertices;

    glm::mat4 preTransform;
};