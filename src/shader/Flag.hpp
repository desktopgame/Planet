#ifndef GEL_UTIL_FLAG_HPP
#define GEL_UTIL_FLAG_HPP
#include <string>
namespace planet {
/**
 * Flag �͐^�U�l���P�������t���O�ł��B
 */
class Flag {
       public:
        /**
         * @param enabled
         */
        explicit Flag(bool enabled);
        /**
         * �t���O��L���ɂ��܂��B
         */
        void enable();
        /**
         * �t���O�𖳌��ɂ��܂��B
         */
        void disable();
        /**
         * �t���O���v���ƈ�v���Ȃ��Ȃ��O���X���[���܂��B
         * @param require
         * @param message
         */
        void check(bool require, const std::string& message) const;
        /**
         * @return
         */
        bool isEnabled() const;
        /**
         * @return
         */
        bool operator*() const noexcept;

        /**
         * @type T
         * @param ifTrue
         * @param ifFalse
         * @return
         */
        template <typename T>
        T value(const T& ifTrue, const T& ifFalse) const;

       private:
        bool enabled;
};

template <typename T>
inline T Flag::value(const T& ifTrue, const T& ifFalse) const {
        return enabled ? ifTrue : ifFalse;
}
}  // namespace planet
#endif