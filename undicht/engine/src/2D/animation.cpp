#include "animation.h"
#include <iostream>


namespace undicht {

    Animation2D::Animation2D() {
        //ctor
        m_texture_source.setName("texture_source");
    }

    Animation2D::~Animation2D() {
        //dtor
    }


    int Animation2D::getTextureID(float time) {
        /** returns what texture to display at the given time */

        // searching for the first time smaller then the param
        for(int i = m_times.size() - 1; i >= 0; i--) {
            if(m_times.at(i) <= time ){

                return i;
            }

        }
        return 0;
    }


    float Animation2D::getDuration() {
        /** @return the duration time of the animation */

        return m_duration;
    }


} // undicht
