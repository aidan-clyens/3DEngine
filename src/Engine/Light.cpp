#include "Engine/Light.h"


/* Light
 */
Light::Light() {

}

/* set_lighting
 */
void Light::set_lighting(const vec3 ambient, const vec3 diffuse, const vec3 specular) {
    m_ambient = ambient;
    m_diffuse = diffuse;
    m_specular = specular;
}

/* set_ambient
 */
void Light::set_ambient(const vec3 ambient) {
    m_ambient = ambient;
}

/* set_diffuse
 */
void Light::set_diffuse(const vec3 diffuse) {
    m_diffuse = diffuse;
}

/* set_specular
 */
void Light::set_specular(const vec3 specular) {
    m_specular = specular;
}

/* get_ambient
 */
vec3 Light::get_ambient() const {
    return m_ambient;
}

/* get_diffuse
 */
vec3 Light::get_diffuse() const {
    return m_diffuse;
}

/* get_specular
 */
vec3 Light::get_specular() const {
    return m_specular;
}

/* get_id
 */
int Light::get_id() const {
    return m_id;
}

/* DirectionalLight
 */
DirectionalLight::DirectionalLight() {

}

/* set_direction
 */
void DirectionalLight::set_direction(const vec3 direction) {
    m_vector = direction;
}

/* get_direction
 */
vec3 DirectionalLight::get_direction() const {
    return m_vector;
}

/* PointLight
 */
PointLight::PointLight() {

}

/* set_position
 */
void PointLight::set_position(const vec3 position) {
    m_vector = position;
}

/* get_position
 */
vec3 PointLight::get_position() const {
    return m_vector;
}

/* set_light_strength
 */
void PointLight::set_light_strength(float constant, float linear, float quadratic) {
    m_constant = constant;
    m_linear = linear;
    m_quadratic = quadratic;
}

/* get_constant
 */
float PointLight::get_constant() const {
    return m_constant;
}

/* get_linear
 */
float PointLight::get_linear() const {
    return m_linear;
}

/* get_quadratic
 */
float PointLight::get_quadratic() const {
    return m_quadratic;
}