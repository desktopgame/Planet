#include "BlockRenderer.hpp"
namespace planet {
BlockRenderer::BlockRenderer(ofShader & shader)
 : cubeRenderer(shader) {
}
void BlockRenderer::clear() {
	cubeRenderer.clear();
}
void BlockRenderer::update() {
	cubeRenderer.updatePlane();
}
void BlockRenderer::render() {
	cubeRenderer.render();
}
CubeRenderer & BlockRenderer::getCubeRenderer() {
	return cubeRenderer;
}
}