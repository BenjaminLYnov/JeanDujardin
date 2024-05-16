#ifndef PLANE_H
#define PLANE_H

#include "Shader/Shader.h"
#include "lib/Math/Vertex.h"
#include "lib/Math/MathMatrix.h"
#include "lib/Math/Transform.h"
#include "lib/Math/Noise.h"

#include <GL/glew.h>
#include <array>

const int POINTS_PER_TRIANGLE = 3;
const int TRIANGLES_PER_SQUARE = 2;

template<typename T>
class Mat4;

template<typename T, int gridSize = 10>
struct Plane 
{
    using vertex_type = Vertex<T>;

    Plane(const Transform<T>& _transform, const T& size) 
        : transform(_transform)
        , m_vao(0)
        , m_vbo(0)
        , m_program(0)
    {
        T sqSize = size / gridSize;
        T originOffset = size / 2;

        Point3d<T> normal = { 0.f, 1.f, 0.f };

        for (size_t i = 0; i < gridSize; i++)
        {
            for (size_t j = 0; j < gridSize; j++)
            {
                int coordinatesInGrid = (POINTS_PER_TRIANGLE * TRIANGLES_PER_SQUARE) * (i + gridSize * j);

                Color4<T> color = { 0.3f, 0.3f + 0.35f*((float)i / (float)gridSize) + 0.35f*((float)j / (float)gridSize), 0.3f, 1.f };

                // points of the square
                Point3d<T> ul = {
                    i * sqSize - originOffset,
                    perlin(i * sqSize, j * sqSize),
                    j * sqSize - originOffset
                };
                Point3d<T> ur = { 
                    (i+1) * sqSize - originOffset, 
                    perlin((i + 1) * sqSize, j * sqSize),
                    j * sqSize - originOffset 
                };
                Point3d<T> ll = {
                    i * sqSize - originOffset,
                    perlin(i * sqSize, (j + 1) * sqSize),
                    (j + 1) * sqSize - originOffset
                };
                Point3d<T> lr = { 
                    (i + 1) * sqSize - originOffset, 
                    perlin((i + 1) * sqSize, (j + 1) * sqSize),
                    (j+1) * sqSize - originOffset 
                };

                // vertices of the square
                vertex_type t1v1 = { ul, normal, color };
                vertex_type t1v2 = { ur, normal, color };
                vertex_type t1v3 = { lr, normal, color };

                vertex_type t2v1 = { ul, normal, color };
                vertex_type t2v2 = { lr, normal, color };
                vertex_type t2v3 = { ll, normal, color };

                // insert vertices in array
                m_points[coordinatesInGrid + 0] = t1v1;
                m_points[coordinatesInGrid + 1] = t1v2;
                m_points[coordinatesInGrid + 2] = t1v3;

                m_points[coordinatesInGrid + 3] = t2v1;
                m_points[coordinatesInGrid + 4] = t2v2;
                m_points[coordinatesInGrid + 5] = t2v3;
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
            {GL_VERTEX_SHADER, "ressources/plane.vert"},
            {GL_FRAGMENT_SHADER, "ressources/plane.frag"},
            {GL_NONE, nullptr}
        };

        m_program = Shader::loadShaders(shaders);

        glUseProgram(m_program);

        // only works for T = float :shrug:
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertex_type), 0);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(vertex_type), reinterpret_cast<char*>(nullptr) + sizeof(vertex_type::position));
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(vertex_type), reinterpret_cast<char*>(nullptr) + sizeof(vertex_type::position) * 2);
        glEnableVertexAttribArray(2);
    }

    void render(const Mat4<T>& view, const Mat4<T>& projection) 
    {
        glBindVertexArray(m_vao);

        Mat4F model(transform);

        Mat4F MVP = projection * view * model;

        GLuint mvpLocation = glGetUniformLocation(m_program, "MVP");
        glUniformMatrix4fv(mvpLocation, 1, 0, MVP.data());

        glDrawArrays(GL_TRIANGLES, 0, int(m_points.size()));
    }

private:
    std::array<vertex_type, (gridSize * gridSize * POINTS_PER_TRIANGLE * TRIANGLES_PER_SQUARE)> m_points;
    GLuint m_vao;
    GLuint m_vbo;
    GLuint m_program;

public:
    Transform<T> transform;

};

using PlaneF = Plane<float, 100>;

#endif // !PLANE_H