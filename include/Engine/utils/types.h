#pragma once

#include <glm/glm.hpp>


typedef glm::vec2 vec2;
typedef glm::vec3 vec3;
typedef glm::mat4 mat4;

// Structs
/* vec2_key_hash
 */
struct vec2_key_hash : public std::unary_function<vec2, std::size_t> {
    std::size_t operator() (const vec2 &c) const {
        int x = (int)c.x;
        int y = (int)c.y;
        return x ^ y;
    }
};

/* vec2_key_equal
 */
struct vec2_key_equal : public std::binary_function<vec2, vec2, bool> {
    bool operator() (const vec3 &c0, const vec3 &c1) const {
        return c0 == c1;
    }
};

/* vec3_key_hash
 */
struct vec3_key_hash : public std::unary_function<vec3, std::size_t> {
    std::size_t operator() (const vec3 &c) const {
        int x = (int)c.x;
        int y = (int)c.y;
        int z = (int)c.z;
        return x ^ y ^ z;
    }
};

/* vec3_key_equal
 */
struct vec3_key_equal : public std::binary_function<vec3, vec3, bool> {
    bool operator() (const vec3 &c0, const vec3 &c1) const {
        return c0 == c1;
    }
};