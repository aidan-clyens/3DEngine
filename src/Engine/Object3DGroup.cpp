#include "Engine/Object3DGroup.h"


/* Object3DGroup
 */
Object3DGroup::Object3DGroup(Object3D *instance, std::vector<Transform> transforms):
Object3D(glm::vec3(0, 0, 0), glm::vec3(0, 0, 0), glm::vec3(1, 1, 1)),
m_instance(instance)
{
    for (int i = 0; i < transforms.size(); i++) {
        // Create transformations
        glm::mat4 model = glm::mat4(1.0);

        // Transform object
        model = glm::translate(model, transforms[i].position);
        model = glm::rotate(model, glm::radians((float)transforms[i].rotation.x), glm::vec3(1.0, 0.0, 0.0));
        model = glm::rotate(model, glm::radians((float)transforms[i].rotation.y), glm::vec3(0.0, 1.0, 0.0));
        model = glm::rotate(model, glm::radians((float)transforms[i].rotation.z), glm::vec3(0.0, 0.0, 1.0));

        m_models.push_back(model);
    }

    m_num_vertices = instance->m_num_vertices;

    m_vertex_buffer.stride = instance->m_vertex_buffer.stride;
    m_vertex_buffer.size = instance->m_vertex_buffer.size;
    m_vertex_buffer.data = new float[m_vertex_buffer.size];

    m_normal_buffer.stride = instance->m_normal_buffer.stride;
    m_normal_buffer.size = instance->m_normal_buffer.size;
    m_normal_buffer.data = new float[m_normal_buffer.size];

    m_uv_buffer.stride = instance->m_uv_buffer.stride;
    m_uv_buffer.size = instance->m_uv_buffer.size;
    m_uv_buffer.data = new float[m_uv_buffer.size];

    memcpy(m_vertex_buffer.data, instance->m_vertex_buffer.data, m_vertex_buffer.size);
    memcpy(m_normal_buffer.data, instance->m_normal_buffer.data, m_normal_buffer.size);
    memcpy(m_uv_buffer.data, instance->m_uv_buffer.data, m_uv_buffer.size);

    this->set_shader(instance->m_shader);
    this->set_texture(instance->m_texture);
    this->set_material(instance->m_material);
    this->set_light(instance->m_light);
}

/* ~Object3DGroup
 */
Object3DGroup::~Object3DGroup() {
    delete m_vertex_buffer.data;
    delete m_normal_buffer.data;
    delete m_uv_buffer.data;

    delete m_instance;
}

/* render
 */
void Object3DGroup::render() {
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
    glBufferData(GL_ARRAY_BUFFER, m_models.size() * sizeof(glm::mat4), &m_models.data()[0], GL_STATIC_DRAW);

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

    glDrawArraysInstanced(GL_TRIANGLES, 0, m_num_vertices, m_models.size());

    if (m_use_texture) {
        m_texture.disable();
    }

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}