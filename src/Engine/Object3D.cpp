#include "Engine/Object3D.h"


float vertices[] = {
    // positions          // normals           // texture coords
    // back face
    -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,
    0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f,
    0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f,
    0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f,
    -0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,

    // front face
    -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
    0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f,
    0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
    0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
    -0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
    -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,

    // left face
    -0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
    -0.5f, 0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
    -0.5f, -0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
    -0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f,

    // right face
    0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
    0.5f, 0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
    0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
    0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
    0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
    0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,

    // bottom face
    -0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,
    0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 1.0f,
    0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f,
    0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f,
    -0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,

    // top face
    -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
    0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
    0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
    0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
    -0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
    -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f
};


/* Object3D
 */
Object3D::Object3D(glm::vec3 pos, glm::vec3 rotation, glm::vec3 size):
m_position(pos),
m_rotation(rotation),
m_size(size),
m_use_texture(false)
{
    // Enable faces
    for (int i = 0; i < OBJECT3D_CUBE_NUM_FACES; i++) {
        m_faces_enabled[i] = true;
    }

    m_vertex_buffer_size = sizeof(float) * 8 * OBJECT3D_CUBE_NUM_VERTICES;
    m_num_vertices = OBJECT3D_CUBE_NUM_VERTICES;
    p_vertex_buffer = new float[m_vertex_buffer_size];

    memcpy(p_vertex_buffer, vertices, m_vertex_buffer_size);

    // Create VBO and VAO
    glGenVertexArrays(1, &m_vertex_array_object);
    glGenBuffers(1, &m_vertex_buffer_object);

    // Initialize material lighting data
    m_material.ambient = glm::vec3(1, 1, 1);
    m_material.diffuse = glm::vec3(1, 1, 1);
    m_material.specular = glm::vec3(1, 1, 1);
    m_material.shininess = 32;

    m_light.ambient = glm::vec3(1, 1, 1);
    m_light.diffuse = glm::vec3(1, 1, 1);
    m_light.specular = glm::vec3(1, 1, 1);
}

/* ~Object3D
 */
Object3D::~Object3D() {
    glDeleteBuffers(1, &m_vertex_buffer_object);
    glDeleteVertexArrays(1, &m_vertex_array_object);

    delete p_vertex_buffer;
}

/* render
 */
void Object3D::render() {
    glBindVertexArray(m_vertex_array_object);
    glBindBuffer(GL_ARRAY_BUFFER, m_vertex_buffer_object);
    glBufferData(GL_ARRAY_BUFFER, m_vertex_buffer_size, p_vertex_buffer, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

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
    return m_position;
}

/* get_rotation
 */
glm::vec3 Object3D::get_rotation() const {
    return m_rotation;
}

/* get_size
 */
glm::vec3 Object3D::get_size() const {
    return m_size;
}

/* set_position
 */
void Object3D::set_position(glm::vec3 position) {
    m_position = position;
}

/* set_rotation
 */
void Object3D::set_rotation(glm::vec3 rotation) {
    m_rotation = rotation;
}

/* set_shader
 */
void Object3D::set_shader(Shader shader) {
    m_shader = shader;
}

/* set_texture
 */
void Object3D::set_texture(Texture2D texture) {
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

/* set_face_enabled
 */
void Object3D::set_face_enabled(eCubeFace face, bool enabled) {
    m_faces_enabled[(int)face] = enabled;
}