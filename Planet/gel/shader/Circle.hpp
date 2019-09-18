#ifndef GEL_SHADER_CIRCLE_HPP
#define GEL_SHADER_CIRCLE_HPP
#include "Buffer.hpp"
#include "NameRule.hpp"
#include "Shader.hpp"
#include "VertexArray.hpp"
#include "Renderer.hpp"

namespace gel {
class Circle {
       public:
        explicit Circle(const std::shared_ptr<Shader>& shader,
                        const NameRule& nameRule);
        void init(const glm::vec4 basePoint, const glm::vec4 color,
                  float scale);
        void destroy();
        void draw();
        float lineWidth;

       private:
        glm::vec4 basePoint;
        glm::vec4 color;
		Renderer renderer;
        NameRule nameRule;
        Buffer<float> vertex;
};
}  // namespace gel
#endif