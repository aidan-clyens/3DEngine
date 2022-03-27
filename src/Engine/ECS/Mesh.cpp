#include "Engine/ECS/Mesh.h"


/* Mesh
 */
Mesh::Mesh():
m_use_shader(false),
m_use_texture(false),
m_num_vertices(0),
m_material_type(MATERIAL_COLOR)
{
    // Create VBO and VAO
    glGenVertexArrays(1, &m_vertex_array_object);
    glGenBuffers(1, &m_vertex_buffer_object);
    glGenBuffers(1, &m_instance_buffer_object);

    // Initialize material lighting data
    m_material.ambient = vec3(1, 1, 1);
    m_material.diffuse = vec3(1, 1, 1);
    m_material.specular = vec3(1, 1, 1);
    m_material.shininess = 32;

    m_light.ambient = vec3(1, 1, 1);
    m_light.diffuse = vec3(1, 1, 1);
    m_light.specular = vec3(1, 1, 1);

    // Initialize transform
    m_transform.position = vec3(0, 0, 0);
    m_transform.rotation = vec3(0, 0, 0);
    m_transform.size = vec3(1, 1, 1);

    // Create transformations
    m_model = mat4(1.0);

    // Transform object
    m_model = glm::rotate(m_model, glm::radians((float)m_transform.rotation.x), vec3(1.0, 0.0, 0.0));
    m_model = glm::rotate(m_model, glm::radians((float)m_transform.rotation.y), vec3(0.0, 1.0, 0.0));
    m_model = glm::rotate(m_model, glm::radians((float)m_transform.rotation.z), vec3(0.0, 0.0, 1.0));
    m_model = glm::translate(m_model, m_transform.position);
    m_model = glm::scale(m_model, m_transform.size);
}

/* ~Mesh
 */
Mesh::~Mesh() {
    glDeleteBuffers(1, &m_vertex_buffer_object);
    glDeleteBuffers(1, &m_instance_buffer_object);
    glDeleteVertexArrays(1, &m_vertex_array_object);
}

/* render
 */
void Mesh::render() {
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
    glBufferData(GL_ARRAY_BUFFER, sizeof(mat4), &m_model, GL_STATIC_DRAW);

    glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(mat4), (void *)0);
    glEnableVertexAttribArray(3);

    glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(mat4), (void *)(sizeof(glm::vec4)));
    glEnableVertexAttribArray(4);

    glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, sizeof(mat4), (void *)(2 * sizeof(glm::vec4)));
    glEnableVertexAttribArray(5);

    glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, sizeof(mat4), (void *)(3 * sizeof(glm::vec4)));
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

/* set_transform
 */
void Mesh::set_transform(Transform transform) {
    m_transform = transform;

    // Create transformations
    m_model = mat4(1.0);

    // Transform object
    m_model = glm::rotate(m_model, glm::radians((float)m_transform.rotation.x), vec3(1.0, 0.0, 0.0));
    m_model = glm::rotate(m_model, glm::radians((float)m_transform.rotation.y), vec3(0.0, 1.0, 0.0));
    m_model = glm::rotate(m_model, glm::radians((float)m_transform.rotation.z), vec3(0.0, 0.0, 1.0));
    m_model = glm::translate(m_model, m_transform.position);
    m_model = glm::scale(m_model, m_transform.size);
}

/* set_shader
 */
void Mesh::set_shader(Shader shader) {
    m_shader = shader;
    m_use_shader = true;
}

/* set_texture
 */
void Mesh::set_texture(Texture texture) {
    m_texture = texture;
    m_use_texture = true;

    switch (m_texture.get_texture_type()) {
        case GL_TEXTURE_2D:
            m_material_type = MATERIAL_TEXTURE_2D;
            break;
        case GL_TEXTURE_CUBE_MAP:
            m_material_type = MATERIAL_TEXTURE_CUBE;
            break;
        default:
            m_material_type = MATERIAL_COLOR;
            break;
    }
}

/* set_material
 */
void Mesh::set_material(Material material) {
    m_material = material;
}

/* set_light
 */
void Mesh::set_light(Light light) {
    m_light = light;
}

/* has_shader
 */
bool Mesh::has_shader() const {
    return m_use_shader;
}

/* get_material_type
 */
eMaterialType Mesh::get_material_type() const {
    return m_material_type;
}
