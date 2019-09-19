#ifndef GAME_SCENE_TUTORIALSCENE_HPP
#define GAME_SCENE_TUTORIALSCENE_HPP
#include <vector>
#include "../../gel/gel.hpp"

class TutorialScene : public gel::IScene {
       public:
        explicit TutorialScene();
        ~TutorialScene();
        void show() override;
        void update() override;
        void draw() override;
        void hide() override;
        std::string getNextScene() const override;
        bool isFinished() const override;

       private:
        gel::MouseTrigger mouseTrigger;
        std::vector<gel::Sprite> sprites;
        int page;
        bool finished;
        float elapsed;

        float wait;
        bool waitStart;
};
#endif