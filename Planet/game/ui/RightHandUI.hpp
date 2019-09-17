#pragma once
#ifndef GAME_UI_RIGHTHAND_UI_HPP
#define GAME_UI_RIGHTHAND_UI_HPP
#include <glm/glm.hpp>
#include <memory>
#include "../../gel/asset/IModel.hpp"
#include "../../gel/gel.hpp"
#include "../../gel/shader/FontTable.hpp"
#include "../../gel/shader/Sprite.hpp"
class RightHandUI {
       public:
        explicit RightHandUI();
        void reset();
        void update();
        void draw(std::weak_ptr<gel::Camera> cameraRef);

       private:
        void batch(std::weak_ptr<gel::Camera> cameraRef);
        glm::vec3 startGPos;
        glm::vec3 gPos;
        glm::vec3 gRot;
        std::shared_ptr<gel::IModel> tModel;
        gel::Timer clickTimer;
		gel::FontTable fontTable;
        bool clicked;
        gel::ScreenBuffer gunScrBuffer;
		gel::Sprite hartSprite;
		gel::Sprite bulletSprite;
        bool gunCache;
};
#endif