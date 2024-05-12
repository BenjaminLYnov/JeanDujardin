#ifndef PLANE_H
#define PLANE_H

#include "Shader/Shader.h"
#include "lib/Math/Vertex.h"

#include <GL/glew.h>

#include <array>

const int POINTS_PER_TRIANGLE = 3;
const int TRIANGLES_PER_SQUARE = 2;

template<typename T>
class Mat4;

template<typename T, int gridSize = 10>
struct Plane {
    using vertex_type = Vertex<T>;

    Plane(const Transform<T>& transform, const T& size) :
        m_transform = m_vao(0), m_vbo(0), m_program(0)
    {
        T sqSize = size / gridSize;
        T originOffset = size / 2;
        for (size_t i = 0; i < gridSize; i++)
        {
            for (size_t j = 0; j < length; j++)
            {

            }
        }
        load();
    }

    ~Plane() {}

    void load()
    {
        glGenVertexArrays(1, &m_vao);
        glBindVertexArray(m_vao);

        glGenBuffers(1, &m_vbo);
        glBindBuffer(GL_ARRAY_BUFFER, m_vbo);

        glBufferData(GL_ARRAY_BUFFER, sizeof(m_points), m_points.data(), GL_STATIC_DRAW);

        ShaderInfo shaders[] = {
            {GL_VERTEX_SHADER, "Plane.vert"},
            {GL_FRAGMENT_SHADER, "Plane.frag"},
            {GL_NONE, nullptr}
        };

        m_program = Shader::loadShaders(shaders);

        glUseProgram(m_program);

        // only works for T = float :shrug:
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertex_type), 0);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(vertex_type), reinterpret_cast<char*>(nullptr) + sizeof(vertex_type::position));
        glEnableVertexAttribArray(1);
    }

    void render(const Mat4<T>& MVP) {
        glBindVertexArray(m_vao);

        GLuint mvpLocation = glGetUniformLocation(m_program, "MVP");
        glUniformMatrix4fv(mvpLocation, 1, 0, MVP.data());

        glDrawArrays(GL_TRIANGLES, 0, int(m_points.size()));
    }

private:
    std::array<vertex_type, (gridSize * gridSize * POINTS_PER_TRIANGLE * TRIANGLES_PER_SQUARE)> m_points;
    GLuint m_vao;
    GLuint m_vbo;
    GLuint m_program;
};

#endif // !PLANE_H