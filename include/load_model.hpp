#ifndef INCLUDE_LOAD_MODEL_HPP_
#define INCLUDE_LOAD_MODEL_HPP_
#include <cstdint>
#include <string>
#include <vector>

#include "./tiny_gltf.h"

struct Vec2 {
    double x;
    double y;
};

struct Vec3 {
    double x;
    double y;
    double z;
};

struct Vec4 {
    double x;
    double y;
    double z;
    double w;
};

struct Vertex {
    double x;
    double y;
    double z;
    double uv_x;
    double uv_y;
};

struct Matrix4 {
    Vec4 v1;
    Vec4 v2;
    Vec4 v3;
    Vec4 v4;
};

struct Triangle {
    Vec3 v1;
    Vec3 v2;
    Vec3 v3;
    Vec2 uv1;
    Vec2 uv2;
    Vec2 uv3;
    uint32_t texture_id;
    uint32_t metallic_roughness_texture_id;
    double metallic_factor;
    double roughness_factor;
    double alpha_cutoff;
    bool double_sided;
    Vec3 emissive_factor;
    Vec4 base_color_factor;
};

struct Vec2ForGLSL {
    float x;
    float y;
};

struct PaddedVec3ForGLSL {
    float x;
    float y;
    float z;
    float padding;
};

struct Vec4ForGLSL {
    float x;
    float y;
    float z;
    float w;
};

struct TexturedVec4ForGLSL {
    float x;
    float y;
    float z;
    uint32_t texture_id;
};

struct TriangleForGLSL {
    PaddedVec3ForGLSL v1;
    PaddedVec3ForGLSL v2;
    PaddedVec3ForGLSL v3;
    PaddedVec3ForGLSL min;
    PaddedVec3ForGLSL max;

    Vec2ForGLSL uv1;
    Vec2ForGLSL uv2;

    Vec2ForGLSL uv3;
    uint32_t texture_id;
    uint32_t metallic_roughness_texture_id;

    float metallic_factor;
    float roughness_factor;
    float alpha_cutoff;
    uint32_t double_sided;

    PaddedVec3ForGLSL emissive_factor;
    Vec4ForGLSL base_color_factor;
};


struct OurNode {
    Vec3 translation;
    Vec4 rotation;
    Vec3 scale;
    Matrix4 matrix;
    std::vector<OurNode> children;
    std::vector<Triangle> primitives;
    std::vector<tinygltf::Image> images;
};

Vec3 make_vec3(const std::vector<double> &vec);

Vec3 make_vec3(const float *vec);

Vec4 make_vec4(const std::vector<double> &vec);

Vec4 make_vec4(const Vec3 &vec, double w);

Matrix4 make_matrix4(const std::vector<double> &vec);

Matrix4 compose_matrix(const Vec3 &translation, const Vec4 &rotation,
                       const Vec3 &scale);

void print_json_node(const OurNode &node);

void print_node(const OurNode &node, size_t depth = 0);

void load_node(OurNode *parent, const tinygltf::Node &node,
               const tinygltf::Model &model, float global_scale);

OurNode load_model(std::string filename);

std::vector<TriangleForGLSL*> node_to_triangles(const OurNode &node);

#endif // INCLUDE_LOAD_MODEL_HPP_
