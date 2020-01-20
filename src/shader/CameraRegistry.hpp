#pragma once
#ifndef SHADER_CAMERAREGISTRY_HPP
#define SHADER_CAMERAREGISTRY_HPP
#include <ofVec2f.h>

#include <memory>
#include <string>
#include <unordered_map>
namespace planet {

class Camera;
/**
 * CameraRegistry �́A�J�����𖼑O�ƕR�t���ĊǗ����郌�W�X�g���ł��B
 */
class CameraRegistry {
       public:
        /**
         * �w��̖��O�ɕR�t������J������Ԃ��܂��B
         * @param name
         * @return
         */
        static std::shared_ptr<Camera> create(const std::string& name);

        /**
         * �w��̖��O�ɕR�t����ꂽ�J������Ԃ��܂��B
         * @param name
         * @return
         */
        static std::shared_ptr<Camera> get(const std::string& name);

        /**
         * �w��̖��O�ɕR�t����ꂽ�J���������݂���Ȃ炻���Ԃ��A
         * ���Ȃ��Ȃ�쐬���ĕԂ��܂��B
         * @param name
         * @return
         */
        static std::shared_ptr<Camera> ref(const std::string& name);

        /**
         * �w��̖��O�̃J���������݂���Ȃ� true ��Ԃ��܂��B
         * @param name
         * @return
         */
        static bool has(const std::string& name);
        /**
         * ���C���J������Ԃ��܂��B
         * @return
         */
        static std::shared_ptr<Camera> main();
        /**
         * �f�t�H���g�̉�ʃT�C�Y��ݒ肵�܂��B
         * @param defaultScreenSize
         * @param forceUpdate
         */
        static void setDefaultScreenSize(glm::vec2 defaultScreenSize,
                                         bool forceUpdate);
        /**
         * �f�t�H���g�̉�ʃT�C�Y��Ԃ��܂��B
         * @return
         */
        static glm::vec2 getDefaultScreenSize();

       private:
        static std::unordered_map<std::string, std::shared_ptr<Camera> >
            cameraMap;
        static glm::vec2 defaultScreenSize;
        CameraRegistry() = delete;
        ~CameraRegistry() = delete;
};
}  // namespace planet
#endif