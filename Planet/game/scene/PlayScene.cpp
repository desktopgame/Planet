#include "PlayScene.hpp"
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/raw_data.hpp>
#include <iostream>
#include "../../gel/asset/AssetDatabase.hpp"
#include "../../gel/shader/IRModel.hpp"
#include "../ui/StatusModel.hpp"
#include "../world/BlockRegistry.hpp"
#include "../world/gen/Generator.hpp"
PlayScene::PlayScene()
    : planet(gel::ShaderRegistry::get("Texture3D")),
      eKeyTrigger('E'),
      crossHair(),
      noiseScreenBuffer(gel::ShaderRegistry::get("Noise"),
                   gel::NameRule()),
	  crtScreenBuffer(gel::ShaderRegistry::get("CRT"),
		gel::NameRule()),
      skybox(gel::ShaderRegistry::get("SkyBox"), gel::NameRule()),
      warp(gel::ShaderRegistry::get("Color"), gel::NameRule()),
      random(),
      rhUI(),
      statusUI(),
	backButton(gel::ShaderRegistry::get("Texture2D")),
    bulletModel(gel::AssetDatabase::getAsset<gel::IModel>("./assets/model/Sphere.fbx")){
	noiseScreenBuffer.init(gel::Game::getInstance()->getWindowWidth(),
                          gel::Game::getInstance()->getWindowHeight());
	crtScreenBuffer.init(gel::Game::getInstance()->getWindowWidth(),
		gel::Game::getInstance()->getWindowHeight());
        gel::CubeMapDesc desc;
        desc.front = "./assets/image/skybox/SkyBoxSide.png";
        desc.back = "./assets/image/skybox/SkyBoxSide.png";
        desc.left = "./assets/image/skybox/SkyBoxSide.png";
        desc.right = "./assets/image/skybox/SkyBoxSide.png";
        desc.top = "./assets/image/skybox/SkyBoxTop.png";
        desc.bottom = "./assets/image/skybox/SkyBoxBottom.png";
        skybox.init(desc, glm::vec3(128, 64, 128), 64, 64);
        statusUI.init();
		backButton.init(
			gel::AssetDatabase::getAsset<gel::ITexture>("./assets/image/BackButton.png")->getID(),
			gel::AssetDatabase::getAsset<gel::ITexture>("./assets/image/BackButton.png")->getID(),
			(gel::getGame()->getWindowSize() - glm::vec2(600, 200)) / 2.0f,
			glm::vec2(600,200));
        rhUI.onStartAnimation().connect([this]() {
                auto model = statusUI.getModel();
                auto ammo = model->getAmmo();
                if (ammo > 0) {
                        model->setAmmo(ammo - 1);
                        auto camera = planet.getCamera();
                        this->bStart = camera->transform
                                           .position ;
                        this->bFwd = camera->transform.forward();
                }
        });
        rhUI.onEndAnimation().connect([this]() {
                // beamLine.update(glm::vec4(0, 0, 0, 1), glm::vec4(0, 0, 0,
                // 1));
        });
}

PlayScene::~PlayScene() {
        noiseScreenBuffer.destroy();
		crtScreenBuffer.destroy();
        skybox.destroy();
}

void PlayScene::show() {
        auto camera = planet.getCamera();
        glm::vec2 windowSize = gel::Game::getInstance()->getWindowSize();
        camera->screenWidth = windowSize.x;
        camera->screenHeight = windowSize.y;
        camera->calculate();
        rhUI.reset();
        this->gameTime = 0.0f;
        this->score = 0;
        glfwSetInputMode(gel::Game::getInstance()->getWindow(), GLFW_CURSOR,
                         GLFW_CURSOR_DISABLED);
        glEnable(GL_TEXTURE_2D);
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_BLEND);
        glDisable(GL_CULL_FACE);
        glEnableClientState(GL_NORMAL_ARRAY);
        glEnableClientState(GL_VERTEX_ARRAY);
        glEnableClientState(GL_TEXTURE_COORD_ARRAY);
        goNextPlanet();
}
void PlayScene::update() {
        // open/close inventory
        eKeyTrigger.update();
        if (eKeyTrigger.isEnabled()) {
                planet.pause(!planet.isPause());
        }
        rhUI.update();
		if (planet.isPause()) {
			backButton.update();
		} else {
			planet.update();
			updateBullet();
		}
}
void PlayScene::draw() {
        float delta = gel::Game::getInstance()->getDeltaTime();
        this->gameTime += delta;
        configureShader(delta);
		if (planet.isPause()) {
			crtScreenBuffer.bind();
			skybox.draw();
			planet.draw();
			warp.draw();
			drawBullet();
			crtScreenBuffer.unbind();
			crtScreenBuffer.render();
			backButton.draw();
			if (backButton.isActive()) {
				planet.pause(false);
			}
		} else {
			noiseScreenBuffer.bind();
			// draw game layer
			skybox.draw();
			planet.draw();
			warp.draw();
			drawBullet();
			noiseScreenBuffer.unbind();
			noiseScreenBuffer.render();
			crossHair.draw();
			rhUI.draw(planet.getCamera());
			statusUI.draw();
			if (noiseTime > 3.0f) {
				warp.destroy();
				goNextPlanet();
			}
		}
}

void PlayScene::hide() {}
std::string PlayScene::getNextScene() const { return ""; }
bool PlayScene::isFinished() const { return false; }

// private
void PlayScene::configureShader(float delta) {
        auto camera = planet.getCamera();
        // apply matrix
        auto skyboxShader = gel::ShaderRegistry::get("SkyBox");

        skyboxShader->use();
        skyboxShader->setUniformMatrix4fv(
            "uProjectionMatrix", 1, GL_FALSE,
            glm::value_ptr(camera->getProjection()));
        skyboxShader->setUniformMatrix4fv("uViewMatrix", 1, GL_FALSE,
                                          glm::value_ptr(camera->getView()));
        skyboxShader->unuse();
        auto circleShader = gel::ShaderRegistry::get("Color");
        circleShader->use();
        circleShader->setUniformMatrix4fv("uMVPMatrix", 1, GL_FALSE,
                                          glm::value_ptr(camera->getMVP()));
        circleShader->unuse();
        auto noiseShader = gel::ShaderRegistry::get("Noise");
        noiseShader->use();
        // check warp
        auto player = planet.getPlayer();
		noiseShader->setUniform1f("Time", gameTime);
        if (warp.isHit(player->transform.position)) {
                noiseShader->setUniform1i("enabled", 1);
                this->noiseTime += delta;
        } else {
                noiseShader->setUniform1i("enabled", 0);
                this->noiseTime = 0.0f;
        }
        noiseShader->unuse();
		auto colorShader = gel::ShaderRegistry::get("ColorFixed");
        colorShader->use();
        colorShader->setUniformMatrix4fv("uMVPMatrix", 1, GL_FALSE,
                                         glm::value_ptr(camera->getMVP()));
        colorShader->setUniformMatrix4fv("uNormalMatrix", 1, GL_FALSE,
                                         glm::value_ptr(camera->getNormal()));
        colorShader->setUniform4f("uLightPos", 64, 48, 64, 1.0f);
        colorShader->unuse();
        auto texShader = gel::ShaderRegistry::get("TextureFixed");
        texShader->use();
        texShader->setUniformMatrix4fv("uMVPMatrix", 1, GL_FALSE,
                                       glm::value_ptr(camera->getMVP()));
        texShader->setUniformMatrix4fv("uNormalMatrix", 1, GL_FALSE,
                                       glm::value_ptr(camera->getNormal()));
        texShader->setUniform4f("uLightPos", 64, 48, 64, 1.0f);
        texShader->unuse();
		auto crtShader = gel::ShaderRegistry::get("CRT");
		crtShader->use();
		crtShader->setUniform1f("Time", gameTime);
		crtShader->unuse();
}

void PlayScene::goNextPlanet() {
        this->noiseTime = 0.0f;
        this->score++;
        planet.generate();
        int x = random.generate(32, 96);
        int z = random.generate(32, 96);
        int y = planet.getWorld().getGroundY(x, z);
        warp.init(glm::vec4((float)x * 0.5f, y, (float)z * 0.5f, 1.0f));
}

void PlayScene::updateBullet()
{
	auto step = bFwd;
	step.x *= 2;
	step.y *= 2;
	step.z *= 2;
	this->bStart += step;
}

void PlayScene::drawBullet()
{
	if (bStart.x < 0 || bStart.x > 128) {
		return;
	}
	if (bStart.y < 0 || bStart.z > 64) {
		return;
	}
	if (bStart.z < 0 || bStart.z > 128) {
		return;
	}
	auto irModel = bulletModel->getIRModel();
	auto camera = planet.getCamera();
	auto mat = glm::mat4(1.0f);
	const float scale = 0.005f;
	mat = glm::translate(mat, bStart);
	mat = glm::scale(mat, glm::vec3(scale, scale, scale));
	irModel->setModelMatrix(mat);
	irModel->setViewMatrix(camera->getView());
	irModel->setProjectionMatrix(camera->getProjection());
	irModel->draw();
}
