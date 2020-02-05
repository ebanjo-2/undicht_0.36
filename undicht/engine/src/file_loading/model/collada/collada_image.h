#ifndef COLLADAIMAGE_H
#define COLLADAIMAGE_H

#include <file_loading/xml/xml_element.h>
#include <string>

namespace undicht{




class ColladaImage{
public:

    XmlElement* m_image_element;

public:

    /** loads the images source file name to the string and returns it */
    std::string& getSourceFile(std::string& loadTo);

public:
    // XmlElement to ColladaImage

    void operator= (XmlElement &x);


};



} // undicht

#endif // COLLADAIMAGE_H
