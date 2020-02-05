#ifndef LABEL_H
#define LABEL_H

#include <UI/ui_element.h>
#include <graphics/uniform.h>
#include <UI/font.h>
#include <string>


namespace undicht {

    class Label : public UIElement {
            /** an ui element that has text on it */

        protected:

            Font* m_font;

            std::string m_caption;
            graphics::Uniform m_text_data; // a buffer containing the data for the chars
            graphics::Uniform m_font_size;

            graphics::Uniform m_color;  // the alpha value is the width of the color region (0 - 1)
            graphics::Uniform m_edge_color;

            void buildTextData();


        public:

            /// the alpha value is the width of the color region (0 - 1)
            void setColor(const glm::vec4& color);
            const graphics::Uniform& getColor();

            /// the alpha value is the width of the color region (0 - 1)
            void setEdgeColor(const glm::vec4& color);
            const graphics::Uniform& getEdgeColor();

        public:


            virtual void setFont(const Font& font);
            virtual const Font& getFont() const;

            virtual void setFontSize(float size);

            virtual void setCaption(const std::string& caption);
            virtual const std::string& getCaption() const;


        public:
            // functions returning data to render the text

            /** @return a uniform (buffer) with all the data needed to draw the characters from the font map */
            virtual const graphics::Uniform& getTextData();

            virtual const graphics::Uniform& getFontSize();

            /** @return the number of characters in the caption of the label */
            virtual int getCharCount();

            Label();
            Label(const std::string& caption, const Font& font);
            virtual ~Label();

    };


} // undicht

#endif // LABEL_H
