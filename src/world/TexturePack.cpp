#include "TexturePack.hpp"

#include <algorithm>

#include "../common/Stopwatch.hpp"
#include "../io/Directory.hpp"
#include "../io/Path.hpp"
#include "../shader/NameSet.hpp"
#include "Block.hpp"
#include "BlockPack.hpp"
#include "Plane.hpp"
namespace planet {

std::vector<std::shared_ptr<TexturePack> > TexturePack::texturePacks;

std::shared_ptr<TexturePack> TexturePack::load(const TextureInfoCollection & textureInfoCollection) {
	auto tp = new TexturePack();
	auto ret = std::shared_ptr<TexturePack>(tp);
	// load texturesets
	for (int i = 0; i < textureInfoCollection.getTextureInfoCount(); i++) {
		auto tinfo = textureInfoCollection.getTextureInfo(i);
		TextureSet set(ret, tinfo.reference);
		if (tinfo.mappingRule.all) {
			set.top = set.bottom = set.front = set.back = set.left = set.right = 
				(tinfo.baseFileName + *tinfo.mappingRule.all);
		}
		if (tinfo.mappingRule.top) {
			set.top = (tinfo.baseFileName + *tinfo.mappingRule.top);
		}
		if (tinfo.mappingRule.bottom) {
			set.bottom = (tinfo.baseFileName + *tinfo.mappingRule.bottom);
		}
		if (tinfo.mappingRule.front) {
			set.front = (tinfo.baseFileName + *tinfo.mappingRule.front);
		}
		if (tinfo.mappingRule.back) {
			set.back = (tinfo.baseFileName + *tinfo.mappingRule.back);
		}
		if (tinfo.mappingRule.left) {
			set.left = (tinfo.baseFileName + *tinfo.mappingRule.left);
		}
		if (tinfo.mappingRule.right) {
			set.right = (tinfo.baseFileName + *tinfo.mappingRule.right);
		}
		ret->addTextureSet(set);
	}
	// load textures
	for (TextureSet set : ret->textureSets) {
		auto topFile = Path::build(std::vector<std::string> { textureInfoCollection.getBaseDirectory(), set.top });
		auto topTex = std::make_shared<Texture>();
		topTex->load(topFile + ".png");
		auto bottomFile = Path::build(std::vector<std::string> { textureInfoCollection.getBaseDirectory(), set.bottom});
		auto bottomTex = std::make_shared<Texture>();
		bottomTex->load(bottomFile + ".png");
		auto leftFile = Path::build(std::vector<std::string> { textureInfoCollection.getBaseDirectory(), set.left });
		auto leftTex = std::make_shared<Texture>();
		leftTex->load(leftFile + ".png");
		auto rightFile = Path::build(std::vector<std::string> { textureInfoCollection.getBaseDirectory(), set.right });
		auto rightTex = std::make_shared<Texture>();
		rightTex->load(rightFile + ".png");
		auto frontFile = Path::build(std::vector<std::string> { textureInfoCollection.getBaseDirectory(), set.front });
		auto frontTex = std::make_shared<Texture>();
		frontTex->load(frontFile + ".png");
		auto backFile = Path::build(std::vector<std::string> { textureInfoCollection.getBaseDirectory(), set.back });
		auto backTex = std::make_shared<Texture>();
		backTex->load(backFile + ".png");

		tp->images.insert_or_assign(set.top, topTex);
		tp->images.insert_or_assign(set.bottom, bottomTex);
		tp->images.insert_or_assign(set.left, leftTex);
		tp->images.insert_or_assign(set.right, rightTex);
		tp->images.insert_or_assign(set.front, frontTex);
		tp->images.insert_or_assign(set.back, backTex);
	}
	return registerTexturePack(ret);
}

std::shared_ptr<TexturePack> TexturePack::make(const std::string& name) {
        auto tp = new TexturePack();
        tp->name = name;
        return registerTexturePack(std::shared_ptr<TexturePack>(tp));
}

std::shared_ptr<TexturePack> TexturePack::getCurrent() {
        for (auto tp : texturePacks) {
                if (tp->isSelected()) {
                        return tp;
                }
        }
        return nullptr;
}

void TexturePack::addTextureSet(const TextureSet& set) {
        this->textureSets.emplace_back(set);
}

int TexturePack::getTextureSetIndexForName(const std::string& name) const {
        int i = 0;
        for (const TextureSet& set : textureSets) {
                if (set.getName() == name) {
                        return i;
                }
                ++i;
        }
        return -1;
}

const TextureSet& TexturePack::getTextureSet(int index) const {
        return textureSets.at(index);
}

void TexturePack::removeTextureSet(int index) {
        textureSets.erase(textureSets.begin() + index);
}

int TexturePack::getTextureSetCount() const {
        return static_cast<int>(textureSets.size());
}

CubeMapDesc TexturePack::getSkybox() const { return skybox; }

std::shared_ptr<Texture> TexturePack::getImage(const std::string& name) const {
        return images.at(name);
}

bool TexturePack::isSelected() const { return selected; }

void TexturePack::select() {
        if (selected) {
                return;
        }
        for (auto tp : TexturePack::texturePacks) {
                tp->selected = false;
        }
        this->selected = true;
        resolve();
}

void TexturePack::resolve() {
        if (!isSelected()) {
                throw std::logic_error("this pack is not selected");
        }
		auto bp = BlockPack::getCurrent();
        for (int i = 0; i < bp->getBlockCount(); i++) {
				auto block = bp->getBlock(i);
                int textureSetIndex =
                    getTextureSetIndexForName(block->getTextureReference());
                if (textureSetIndex == -1) {
                        continue;
                }
                block->setTextureSetIndex(textureSetIndex);
        }
}

// protected
TexturePack::TexturePack()
    : selected(false), name(), textureSets(), images(), skybox() {}

std::shared_ptr<TexturePack> TexturePack::registerTexturePack(
    const std::shared_ptr<TexturePack> pack) {
        bool empty = texturePacks.empty();
        texturePacks.emplace_back(pack);
        if (empty) {
                pack->select();
        }
        return pack;
}

// private
}  // namespace planet
