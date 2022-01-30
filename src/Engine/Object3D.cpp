#include "Engine/Object3D.h"


/* Object3D
 */
Object3D::Object3D(glm::vec3 pos, glm::vec3 rotation, glm::vec3 size):
m_use_texture(false),
m_num_vertices(0)
{
    // Create VBO and VAO
    glGenVertexArrays(1, &m_vertex_array_object);
    glGenBuffers(1, &m_vertex_buffer_object);
    glGenBuffers(1, &m_instance_buffer_object);

    // Initialize material lighting data
    m_material.ambient = glm::vec3(1, 1, 1);
    m_material.diffuse = glm::vec3(1, 1, 1);
    m_material.specular = glm::vec3(1, 1, 1);
    m_material.shininess = 32;

    m_light.ambient = glm::vec3(1, 1, 1);
    m_light.diffuse = glm::vec3(1, 1, 1);
    m_light.specular = glm::vec3(1, 1, 1);

    // Initialize transform
    m_transform.position = pos;
    m_transform.rotation = rotation;
    m_transform.size = size;

    // Create transformations
    m_model = glm::mat4(1.0);

    // Transform object
    m_model = glm::translate(m_model, m_transform.position);
    m_model = glm::rotate(m_model, glm::radians((float)m_transform.rotation.x), glm::vec3(1.0, 0.0, 0.0));
    m_model = glm::rotate(m_model, glm::radians((float)m_transform.rotation.y), glm::vec3(0.0, 1.0, 0.0));
    m_model = glm::rotate(m_model, glm::radians((float)m_transform.rotation.z), glm::vec3(0.0, 0.0, 1.0));
}

/* ~Object3D
 */
Object3D::~Object3D() {
    glDeleteBuffers(1, &m_vertex_buffer_object);
    glDeleteBuffers(1, &m_instance_buffer_object);
    glDeleteVertexArrays(1, &m_vertex_array_object);
}

/* render
 */
void Object3D::render() {
    if (m_num_vertices == 0)
        return;

    glBindVertexArray(m_vertex_array_object);

    // Vertex buffer object
    glBindBuffer(GL_ARRAY_BUFFER, m_vertex_buffer_object);
    glBufferData(GL_ARRAY_BUFFER, m_vertex_buffer.size + m_normal_buffer.size + m_uv_buffer.size, nullptr, GL_STATIC_DRAW);
    glBufferSubData(GL_ARRAY_BUFFER, 0, m_vertex_buffer.size, m_vertex_buffer.data);
    glBufferSubData(GL_ARRAY_BUFFER, m_vertex_buffer.size, m_normal_buffer.size, m_normal_buffer.data);
    glBufferSubData(GL_ARRAY_BUFFER, m_vertex_buffer.size + m_normal_buffer.size, m_uv_buffer.size, m_vertex_buffer.data);

    glVertexAttribPointer(0, m_vertex_buffer.stride, GL_FLOAT, GL_FALSE, m_vertex_buffer.stride * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, m_normal_buffer.stride, GL_FLOAT, GL_FALSE, m_normal_buffer.stride * sizeof(float), (void *)(m_vertex_buffer.size));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, m_uv_buffer.stride, GL_FLOAT, GL_FALSE, m_uv_buffer.stride * sizeof(float), (void *)(m_vertex_buffer.size + m_normal_buffer.size));
    glEnableVertexAttribArray(2);

    // Instance buffer object
    glBindBuffer(GL_ARRAY_BUFFER, m_instance_buffer_object);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::mat4), &m_model, GL_STATIC_DRAW);

    glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void *)0);
    glEnableVertexAttribArray(3);

    glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void *)(sizeof(glm::vec4)));
    glEnableVertexAttribArray(4);

    glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void *)(2 * sizeof(glm::vec4)));
    glEnableVertexAttribArray(5);

    glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void *)(3 * sizeof(glm::vec4)));
    glEnableVertexAttribArray(6);

    glVertexAttribDivisor(3, 1);
    glVertexAttribDivisor(4, 1);
    glVertexAttribDivisor(5, 1);
    glVertexAttribDivisor(6, 1);

    if (m_use_texture) {
        m_texture.enable();
    }

    glDrawArrays(GL_TRIANGLES, 0, m_num_vertices);

    if (m_use_texture) {
        m_texture.disable();
    }

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

/* get_position
 */
glm::vec3 Object3D::get_position() const {
    return m_transform.position;
}

/* get_rotation
 */
glm::vec3 Object3D::get_rotation() const {
    return m_transform.rotation;
}

/* get_size
 */
glm::vec3 Object3D::get_size() const {
    return m_transform.size;
}

/* get_transform
 */
Transform Object3D::get_transform() const {
    return m_transform;
}

/* set_position
 */
void Object3D::set_position(glm::vec3 position) {
    m_transform.position = position;

    // Create transformations
    m_model = glm::mat4(1.0);

    // Transform object
    m_model = glm::translate(m_model, m_transform.position);
    m_model = glm::rotate(m_model, glm::radians((float)m_transform.rotation.x), glm::vec3(1.0, 0.0, 0.0));
    m_model = glm::rotate(m_model, glm::radians((float)m_transform.rotation.y), glm::vec3(0.0, 1.0, 0.0));
    m_model = glm::rotate(m_model, glm::radians((float)m_transform.rotation.z), glm::vec3(0.0, 0.0, 1.0));
}

/* set_rotation
 */
void Object3D::set_rotation(glm::vec3 rotation) {
    m_transform.rotation = rotation;

    // Create transformations
    m_model = glm::mat4(1.0);

    // Transform object
    m_model = glm::translate(m_model, m_transform.position);
    m_model = glm::rotate(m_model, glm::radians((float)m_transform.rotation.x), glm::vec3(1.0, 0.0, 0.0));
    m_model = glm::rotate(m_model, glm::radians((float)m_transform.rotation.y), glm::vec3(0.0, 1.0, 0.0));
    m_model = glm::rotate(m_model, glm::radians((float)m_transform.rotation.z), glm::vec3(0.0, 0.0, 1.0));
}

/* set_transform
 */
void Object3D::set_transform(Transform transform) {
    m_transform = transform;

    // Create transformations
    m_model = glm::mat4(1.0);

    // Transform object
    m_model = glm::translate(m_model, m_transform.position);
    m_model = glm::rotate(m_model, glm::radians((float)m_transform.rotation.x), glm::vec3(1.0, 0.0, 0.0));
    m_model = glm::rotate(m_model, glm::radians((float)m_transform.rotation.y), glm::vec3(0.0, 1.0, 0.0));
    m_model = glm::rotate(m_model, glm::radians((float)m_transform.rotation.z), glm::vec3(0.0, 0.0, 1.0));
}

/* set_shader
 */
void Object3D::set_shader(Shader shader) {
    m_shader = shader;
}

/* set_texture
 */
void Object3D::set_texture(Texture texture) {
    m_texture = texture;
    m_use_texture = true;
}

/* set_material
 */
void Object3D::set_material(Material material) {
    m_material = material;
}

/* set_light
 */
void Object3D::set_light(Light light) {
    m_light = light;
}