#include "BlockRenderer.hpp"
namespace planet {

BlockRenderer::BlockRenderer(const NameSet& nameSet)
    : nameSet(nameSet), map() {}

void BlockRenderer::put(GLuint texture, PlaneType type, float x, float y,
                        float z) {
        ref(texture)->put(type, x, y, z);
}

void BlockRenderer::putFront(GLuint texture, float x, float y, float z) {
        ref(texture)->putFront(x, y, z);
}

void BlockRenderer::putBack(GLuint texture, float x, float y, float z) {
        ref(texture)->putBack(x, y, z);
}

void BlockRenderer::putLeft(GLuint texture, float x, float y, float z) {
        ref(texture)->putLeft(x, y, z);
}

void BlockRenderer::putRight(GLuint texture, float x, float y, float z) {
        ref(texture)->putRight(x, y, z);
}

void BlockRenderer::putTop(GLuint texture, float x, float y, float z) {
        ref(texture)->putTop(x, y, z);
}

void BlockRenderer::putBottom(GLuint texture, float x, float y, float z) {
        ref(texture)->putBottom(x, y, z);
}

void BlockRenderer::clear() {
        for (auto& kv : map) {
                kv.second->clear();
        }
}

void BlockRenderer::rehash() {
        for (auto& kv : map) {
                kv.second->rehash();
        }
}

void BlockRenderer::render() {
        for (auto& kv : map) {
                kv.second->render(kv.first);
        }
}

// private
std::shared_ptr<SideRenderer> BlockRenderer::ref(GLuint texture) {
        if (map.count(texture)) {
                return map.at(texture);
        }
        auto r = std::make_shared<SideRenderer>(nameSet);
        map.insert_or_assign(texture, r);
        return r;
}
}  // namespace planet
