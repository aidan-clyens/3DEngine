#pragma once

// Includes
#include "Engine/utils/types.h"


/* Light
 */
class Light {
    public:
        Light();

        void set_lighting(const vec3 ambient, const vec3 diffuse, const vec3 specular);

        void set_ambient(const vec3 ambient);
        void set_diffuse(const vec3 diffuse);
        void set_specular(const vec3 specular);

        vec3 get_ambient() const;
        vec3 get_diffuse() const;
        vec3 get_specular() const;

        int get_id() const;

    protected:
        int m_id;

        vec3 m_vector;

        vec3 m_ambient;
        vec3 m_diffuse;
        vec3 m_specular;
};

/* DirectionalLight
 */
class DirectionalLight : public Light {
    public:
        DirectionalLight();

        void set_direction(const vec3 direction);

        vec3 get_direction() const;
};

/* PointLight
 */
class PointLight : public Light {
    public:
        PointLight();

        void set_position(const vec3 position);
        vec3 get_position() const;

        void set_light_strength(float constant, float linear, float quadratic);

        float get_constant() const;
        float get_linear() const;
        float get_quadratic() const;

    private:
        // Used to calculate attenuation for point lights
        float m_constant;
        float m_linear;
        float m_quadratic;
};
