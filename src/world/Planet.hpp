#pragma once
#ifndef WORLD_PLANET_HPP
#define WORLD_PLANET_HPP
#include <memory>
#include <ofShader.h>

#include "../common/GLM.hpp"
#include "BlockTable.hpp"
namespace planet {

class WorldGenerateService;
class World;
class Biome;
class Camera;

class Planet {
       public:
        explicit Planet(ofShader& shader, Camera& camera);

        void generate(glm::vec3 size, std::shared_ptr<Biome> biome);

        void update();
        void drawToBuffer();
        void render();

        std::shared_ptr<World> getWorld() const;
        BlockTable getBlockTable() const;

       private:
		ofShader& shader;
		Camera& camera;
        BlockTable blockTable;
        std::shared_ptr<World> world;
};
}  // namespace planet
#endif