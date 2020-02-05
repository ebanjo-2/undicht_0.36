#ifndef ANIMATEDSPRITE_H
#define ANIMATEDSPRITE_H

#include <2D/animation.h>
#include <2D/sprite.h>

namespace undicht {


    class AnimatedSprite : public Sprite {
            /** a sprite that can show animations */
        public:

            Animation2D* m_current_animation = 0;
            float m_animation_time = 0;

            void setAnimation(Animation2D* animation);

            void setAnimationTime(float time);

            void addAnimationTime(float time_offset);

            int getCurrentTextureID();

            AnimatedSprite();
            virtual ~AnimatedSprite();

        private:

            /** sets m_animation_time so that it is within the current animations duration time */
            void repeatAnimationTime();

    };


} // undicht

#endif // ANIMATEDSPRITE_H
