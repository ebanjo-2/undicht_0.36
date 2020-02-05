#include "animated_sprite.h"

namespace undicht {

    AnimatedSprite::AnimatedSprite() {
        //ctor
    }

    AnimatedSprite::~AnimatedSprite() {
        //dtor
    }

    void AnimatedSprite::setAnimation(Animation2D* animation) {

        m_current_animation = animation;
    }

    void AnimatedSprite::setAnimationTime(float time) {

        m_animation_time = time;

        repeatAnimationTime();
    }

    void AnimatedSprite::addAnimationTime(float time_offset) {

        m_animation_time += time_offset;

        repeatAnimationTime();
    }

    int AnimatedSprite::getCurrentTextureID() {

        if(m_current_animation){

            return m_current_animation->getTextureID(m_animation_time);
        } else {

            return -1;
        }
    }




    void AnimatedSprite::repeatAnimationTime() {

        float max_time = m_current_animation->getDuration();

        while((m_animation_time > max_time) && ((m_animation_time - max_time) > 0)){

            m_animation_time -= max_time;
        }

    }



} // undicht
