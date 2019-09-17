#include "Line.hpp"
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/raw_data.hpp>
namespace gel {
Line::Line(const std::shared_ptr<Shader>& shader, const NameRule& nameRule)
    : shader(shader),
      nameRule(nameRule),
      start(),
      end(),
      vertex(GL_ARRAY_BUFFER, GL_DYNAMIC_DRAW),
      vao(),
      lineWidth(10.0f) {}

void Line::init(const glm::vec4 start, const glm::vec4 end, glm::vec4 color) {
        this->start = start;
        this->end = end;
        this->color = color;
        vertex.init();
        vao.init();
        // emit
        auto& vSeq = vertex.modify();
        vSeq.emitVec4(start.x, start.y, start.z, start.w);
        vSeq.emitVec4(end.x, end.y, end.z, end.w);
        // update
        vertex.bind();
        vertex.update();
        vertex.unbind();
        // apply
        shader->use();
        shader->setUniform4f(nameRule.uniformPosition, 0, 0, 0, 0);
        shader->setUniform4f(nameRule.uniformColor, color.x, color.y, color.z,
                             color.w);
        vao.bind();
        GLuint vertexAttrib = shader->getAttribLocation(nameRule.attribVertex);
        vertex.bind();
		shader->setUniform4f("uPosition", 0, 0, 0, 0);
		shader->setUniformMatrix4fv("uMVPMatrix", 1, GL_FALSE, glm::value_ptr(mvp));
        glVertexAttribPointer(vertexAttrib, 4, GL_FLOAT, GL_FALSE, 0, NULL);
        glEnableVertexAttribArray(vertexAttrib);
        vao.unbind();
        vertex.unbind();
        shader->unuse();
}

void Line::update(const glm::vec4 start, const glm::vec4 end) {
        auto& vSeq = vertex.modify();
        vSeq.clear();
        vSeq.emitVec4(start.x, start.y, start.z, start.w);
        vSeq.emitVec4(end.x, end.y, end.z, end.w);
        vertex.bind();
        vertex.update();
        vertex.unbind();
}

void Line::destroy() {
        vertex.destroy();
        vao.destroy();
}

void Line::draw() {
		glEnable(GL_DEPTH_TEST);
		shader->use();
		shader->setUniform4f("uPosition", 0, 0, 0, 0);
		shader->setUniformMatrix4fv("uMVPMatrix", 1, GL_FALSE, glm::value_ptr(mvp));
		shader->unuse();
        glLineWidth(lineWidth);
        shader->use();
        vao.bind();
        glDrawArrays(GL_LINE_STRIP, 0, 2);
        vao.unbind();
        shader->unuse();
}
}  // namespace gel