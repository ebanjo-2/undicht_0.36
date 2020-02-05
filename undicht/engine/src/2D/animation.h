#ifndef ANIMATION2D_H
#define ANIMATION2D_H

#include <graphics/texture.h>
#include <vector>


namespace undicht {


    class Animation2D {
        /** holds the data for a 2D sprite animation */
        public:



            graphics::Texture m_texture_source; // stores all 2D textures used in the animation
            std::vector<float> m_times; // the times for when to switch textures (not including when to return to the first one)
            float m_duration = 0; // the time it takes for the animation to complete

            /** returns what texture to display at the given time */
            int getTextureID(float time);

            /** @return the duration time of the animation */
            float getDuration();

            Animation2D();
            virtual ~Animation2D();

    };

} // undicht

#endif // ANIMATION2D_H
