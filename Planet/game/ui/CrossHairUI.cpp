#include "CrossHairUI.hpp"
#include "../../gel/asset/AssetDatabase.hpp"
CrossHairUI::CrossHairUI()
    : path("./assets/image/CrossHair.png"),
      sprite(gel::ShaderRegistry::get("Texture2D")) {
        auto wsize = gel::Game::getInstance()->getWindowSize();
        sprite.init(gel::AssetDatabase::getAsset<gel::ITexture>(path)->getID(),
                    glm::vec2((wsize.x - 32) / 2, (wsize.y - 32) / 2),
                    glm::vec2(32, 32), 1);
}

CrossHairUI::~CrossHairUI() { sprite.destroy(); }

void CrossHairUI::draw() {
        sprite.draw();
}