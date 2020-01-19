#pragma once
#ifndef GAME_PLAYSCENE_HPP
#define GAME_PLAYSCENE_HPP
#include <ofEasyCam.h>
#include <ofShader.h>
#include <ofxImGui.h>
#include <vector>

#include <memory>

#include "../common/Random.hpp"
#include "../common/StateValue.hpp"
#include "../common/FirstPersonController.hpp"
#include "../common/Timer.hpp"
#include "../scene/Scene.hpp"
#include "../shader/Plane.hpp"
#include "../shader/Transform.hpp"
#include "../world/Planet.hpp"
#include "../world/World.hpp"
#include "../world/WorldIO.hpp"
#include "../world/biome/Biome.hpp"
#include "../imguiex/ListBox.hpp"
#include "../imguiex/CheckBox.hpp"
#include "../imguiex/RadioButtonGroup.hpp"
#include "../imguiex/InputField.hpp"
#include "../imguiex/Float.hpp"
#include "../imguiex/FloatXZ.hpp"
namespace objb {
	class ObjBuilder;
	class MtlBuilder;
}
namespace planet {
class PlayScene : public Scene {
       public:
        explicit PlayScene();
        ~PlayScene();
        void show() override;
        void update() override;
        void draw() override;
        void hide() override;

        std::string getNextScene() const override;
        bool isFinished() const override;

       private:
		bool isProcessing() const;
		void playUpdate();
		void playDraw();
		void exportJson(const std::string& outputFile);
		void exportObj(const std::string& outputFile);
		void exportBmp(const std::string& outputFile);

        ofEasyCam cam;
        std::shared_ptr<Planet> planet;
		Random rand;
		float cameraAngle;

		ofxImGui::Gui gui;
		StateValue<bool> playMode;
		FirstPersonController fpsCon;
		std::vector<std::shared_ptr<Biome> > biomes;
		imguiex::ListBox biomeNames;
		imguiex::RadioButtonGroup exportTypes;
		imguiex::InputField<> exportDir;
		imguiex::Float cameraSpeed;
		imguiex::FloatXZ worldSize;
		AsyncOperation asyncOp;

        static NameSet createPlaneNameSet();
        static NameSet createGunNameSet();
};
}  // namespace planet
#endif