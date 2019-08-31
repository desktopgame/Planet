#ifndef GEL_SHADER_SCREENBUFFER_HPP
#define GEL_SHADER_SCREENBUFFER_HPP
#include "../gli.hpp"
#include "../util/Flag.hpp"
#include "Buffer.hpp"
#include "FrameBuffer.hpp"
#include "NameRule.hpp"
#include "RenderBuffer.hpp"
#include "Shader.hpp"
#include "VertexArray.hpp"

namespace gel {
class ScreenBuffer {
       public:
        explicit ScreenBuffer(Shader& shader, const NameRule nameRule,
                              int width, int height);
        void init();
        void destroy();
        void bind();
        void unbind();
        void render();

       private:
        void initRect();
        int width;
        int height;
        FrameBuffer frameBuffer;
        RenderBuffer renderBuffer;
        GLuint texture;

        Shader& shader;
        NameRule nameRule;
        VertexArray vao;
        Buffer<GLfloat> vertex;
        Buffer<GLfloat> uv;
};
}  // namespace gel
#endif