#pragma once

#include <glm/glm.hpp>


typedef glm::vec2 vec2;
typedef glm::vec3 vec3;
typedef glm::mat4 mat4;

// Enums
typedef enum {
    MATERIAL_COLOR,
    MATERIAL_TEXTURE_2D,
    MATERIAL_TEXTURE_CUBE
} eMaterialType;

typedef enum {
    LIGHT_DIRECTIONAL,
    LIGHT_POINT
} eLightType;

// Structs
typedef struct {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
} Material;

typedef struct {
    eLightType type;

    vec3 vector;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    // Used to calculate attenuation for point lights
    float constant;
    float linear;
    float quadratic;
} Light;

/* vec2_key_hash
 */
struct vec2_key_hash {
    std::size_t operator() (const vec2 &c) const {
        int x = (int)c.x;
        int y = (int)c.y;
        return x ^ y;
    }
};

/* vec2_key_equal
 */
struct vec2_key_equal {
    bool operator() (const vec3 &c0, const vec3 &c1) const {
        return c0 == c1;
    }
};

/* vec3_key_hash
 */
struct vec3_key_hash {
    std::size_t operator() (const vec3 &c) const {
        int x = (int)c.x;
        int y = (int)c.y;
        int z = (int)c.z;
        return x ^ y ^ z;
    }
};

/* vec3_key_equal
 */
struct vec3_key_equal {
    bool operator() (const vec3 &c0, const vec3 &c1) const {
        return c0 == c1;
    }
};