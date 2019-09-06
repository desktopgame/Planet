#include "TestScene.hpp"
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "../../gel/gli.hpp"
#include "../../gel/shader/IRModel.hpp"
#include "../world/Block.hpp"
#include "../world/BlockRegistry.hpp"
#include "../world/Space.hpp"
TestScene::TestScene(const std::shared_ptr<gel::GameDevice>& gameDevice)
    : gameDevice(gameDevice),
      shader(gel::ShaderRegistry::getInstance().get("TextureFixed")),
      plane(shader),
      angleX(180),
      angleY(0) {
        plane.init(0.5f);
        glEnableClientState(GL_NORMAL_ARRAY);
        glEnableClientState(GL_VERTEX_ARRAY);
        glEnableClientState(GL_TEXTURE_COORD_ARRAY);
}

void TestScene::show() {
        glfwSetInputMode(gel::Game::getInstance()->getWindow(), GLFW_CURSOR,
                         GLFW_CURSOR_NORMAL);
        glEnable(GL_TEXTURE_2D);
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_BLEND);
        glDisable(GL_CULL_FACE);
}
void TestScene::update() {}
void TestScene::draw() {
        GLFWwindow* wd = gel::Game::getInstance()->getWindow();
        if (glfwGetKey(wd, GLFW_KEY_UP) == GLFW_PRESS) {
                angleX += 0.5f;
        } else if (glfwGetKey(wd, GLFW_KEY_DOWN) == GLFW_PRESS) {
                angleX -= 0.5f;
        }
        if (glfwGetKey(wd, GLFW_KEY_RIGHT) == GLFW_PRESS) {
                angleY += 0.5f;
        } else if (glfwGetKey(wd, GLFW_KEY_LEFT) == GLFW_PRESS) {
                angleY -= 0.5f;
        }
        if (angleX > 360) angleX -= 360;
        if (angleY > 360) angleY -= 360;
        glClearColor(0.3f, 0.3f, 1.0f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glViewport(0, 0, 1280, 720);
        auto rotate = glm::rotate(glm::mat4(1.0f), angleY, glm::vec3(0, 1, 0));
        rotate = glm::rotate(rotate, angleX, glm::vec3(1, 0, 0));
        auto scale = glm::scale(rotate, glm::vec3(0.02f, 0.02f, 0.02f));
        this->projection =
            glm::perspective(30.0f, 1280.0f / 720.0f, 1.0f, 1000.0f);
        this->view =
            glm::lookAt(glm::vec3(0, -3, 5), glm::vec3(), glm::vec3(0, 1, 0));
        this->model = scale;
        ;
        this->mvp = projection * view * model;
        gel::Shader& ss = gel::ShaderRegistry::getInstance().get("ColorFixed");
        ss.use();
        ss.setUniform4f("uLightPos", 0, 0, 0, 1);
        ss.unuse();
        shader.use();
        shader.setUniform4f("uLightPos", 0, 0, 0, 1);
        shader.unuse();

        // bind matrix
        auto drawModel = gameDevice->getModelManager()->getModel(
            "./assets/model/Gun1028.fbx");
        auto ir = drawModel->getIRModel();
        ir->setModelMatrix(model);
        ir->setViewMatrix(view);
        ir->setProjectionMatrix(projection);
        drawModel->draw();
}
void TestScene::hide() {}
bool TestScene::isFinished() const { return false; }
std::string TestScene::getNextScene() const { return ""; }
