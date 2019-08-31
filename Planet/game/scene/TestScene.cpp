#include "TestScene.hpp"
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "../../gel/gli.hpp"
#include "../world/Block.hpp"
#include "../world/BlockRegistry.hpp"
#include "../world/Space.hpp"
TestScene::TestScene(const std::shared_ptr<gel::GameDevice>& gameDevice)
    : gameDevice(gameDevice),
      shader(gel::ShaderRegistry::getInstance().get("TextureFixed")),
      plane(shader),
      angle(0) {
        plane.init(0.5f);

        shader.use();
        this->mvpMatrixID = shader.getUniformLocation("uMVPMatrix");
        this->normalMatrixID = shader.getUniformLocation("uNormalMatrix");
        glUniform1i(shader.getUniformLocation("uTexture"), 0);
        glUniform1f(shader.getUniformLocation("uShininess"), 50.0f);
        glUniform4f(shader.getUniformLocation("uDiffuse"), 0.5f, 0.5f, 0.5f,
                    1.0f);
        glUniform4f(shader.getUniformLocation("uSpecular"), 0.5f, 0.5f, 0.5f,
                    1.0f);
        glUniform4f(shader.getUniformLocation("uAmbient"), 0.5f, 0.5f, 0.5f,
                    1.0f);
        glUniform4f(shader.getUniformLocation("uLightPos"), 1, 5, 1, 1);
        glEnableClientState(GL_NORMAL_ARRAY);
        glEnableClientState(GL_VERTEX_ARRAY);
        glEnableClientState(GL_TEXTURE_COORD_ARRAY);
        shader.unuse();
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
        if (glfwGetKey(wd, GLFW_KEY_RIGHT) == GLFW_PRESS) {
                angle++;
        } else if (glfwGetKey(wd, GLFW_KEY_LEFT) == GLFW_PRESS) {
                angle--;
        }
        glClearColor(0.3f, 0.3f, 1.0f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glViewport(0, 0, 1280, 720);

        this->projection =
            glm::perspective(30.0f, 1280.0f / 720.0f, 1.0f, 1000.0f);
        this->view =
            glm::lookAt(glm::vec3(0, -3, 5), glm::vec3(), glm::vec3(0, 1, 0));
        this->model =
            glm::scale(glm::mat4(1.0f), glm::vec3(0.01f, 0.01f, 0.01f));
        ;
        this->mvp = projection * view * model;

        // bind matrix
        this->normalMatrix = view * model;
        this->normalMatrix = glm::inverse(normalMatrix);
        this->normalMatrix = glm::transpose(normalMatrix);
        shader.use();
        shader.setUniformMatrix4fv("uMVPMatrix", 1, GL_FALSE,
                                   glm::value_ptr(mvp));
        shader.setUniformMatrix4fv("uNormalMatrix", 1, GL_FALSE,
                                   glm::value_ptr(normalMatrix));
        shader.setUniform4f("uLightPos", 0, 0, 0, 1);
        shader.unuse();
        // glutSolidTeapot(1);
        // glutSolidCube(1);
        gameDevice->getModelManager()
            ->getModel("./assets/model/ColorBox.fbx")
            ->draw();
}
void TestScene::hide() {}
bool TestScene::isFinished() const { return false; }
std::string TestScene::getNextScene() const { return ""; }
