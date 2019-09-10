#include "JpegPipeline.hpp"
#include "../asset/AssetDatabase.hpp"
#include "../asset/JpegTexture.hpp"
namespace gel {
JpegPipeline::JpegPipeline() {}

bool JpegPipeline::accept(const std::string& path) { return true; }
void JpegPipeline::load(const std::string& path, Thread thread) {
        AssetDatabase::getOrNewAsset<JpegTexture>(path)->load(path, thread);
}
void JpegPipeline::unload(const std::string& path) {
        AssetDatabase::getOrNewAsset<JpegTexture>(path)->unload();
}
}  // namespace gel