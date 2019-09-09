#pragma once
#ifndef GAME_SCENE_LOADSCENE_HPP
#define GAME_SCENE_LOADSCENE_HPP
#include "../../gel/gel.hpp"
#include "../ui/CrossHairUI.hpp"
#include "../world/Planet.hpp"
#include "../world/WarpPoint.hpp"

class LoadScene : public gel::IScene {
       public:
        explicit LoadScene(const std::shared_ptr<gel::GameDevice>& gameDevice);
        ~LoadScene();
        void show() override;
        void update() override;
        void draw() override;
        void hide() override;
        std::string getNextScene() const override;
        bool isFinished() const override;

       private:
        std::shared_ptr<gel::GameDevice> gameDevice;
        bool finished;
};
#endif