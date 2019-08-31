#ifndef GEL_SHADER_PLANE_HPP
#define GEL_SHADER_PLANE_HPP
#include "../util/Flag.hpp"
#include "Buffer.hpp"
#include "NameRule.hpp"
#include "Shader.hpp"
#include "VertexArray.hpp"
namespace gel {
enum class PlaneType { Forward, Backward, Left, Right, Top, Bottom };
class Plane {
       public:
        explicit Plane(Shader& shader, const NameRule& nameRule);
        explicit Plane(Shader& shader);
        void init(float size);
        void destroy();
        void draw();
        void render(Buffer<float> posBuf, int count);
        void bind();
        void unbind();
        void setType(const PlaneType type);
        PlaneType getType() const;

       private:
        void initBuffers();
        static void addNormals(Buffer<GLfloat>& buf, int count, float x,
                               float y, float z, float w);
        Buffer<GLushort>& getIndexBufferFromType(const PlaneType type);
        Shader& shader;
        VertexArray vao;
        PlaneType type;
        NameRule nameRule;
        Flag initFlag;
        float size;

        GLuint vertexAttrib;
        GLuint normalAttrib;
        GLuint uvAttrib;
        Buffer<GLushort> fwdIndexBuf;
        Buffer<GLushort> backIndexBuf;
        Buffer<GLushort> leftIndexBuf;
        Buffer<GLushort> rightIndexBuf;
        Buffer<GLushort> topIndexBuf;
        Buffer<GLushort> bottomIndexBuf;
        Buffer<float> vertexBuf;
        Buffer<float> uvBuf;
        Buffer<float> normalBuf;
};
}  // namespace gel
#endif