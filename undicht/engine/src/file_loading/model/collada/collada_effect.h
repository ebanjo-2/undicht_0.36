#ifndef COLLADA_EFFECT_H_INCLUDED
#define COLLADA_EFFECT_H_INCLUDED

#include <file_loading/xml/xml_element.h>

// a class to represent an effect element in a collada file

namespace undicht{


class ColladaEffect{

public:

    XmlElement* m_effect_element;

public:
    // getting data from the effect

    /** searches the element specific to phong shading for a reference to a texture
    * fullfilling the texture_type, example: "diffuse" */
    void getPhongTextureName(std::string&loadTo, std::string texture_type);


public:
    // XmlElement to ColladaEffect

    void operator= (XmlElement &x);
    ColladaEffect(){};
    ColladaEffect(XmlElement &x){*this = x;}
};




} // undicht

#endif // COLLADA_EFFECT_H_INCLUDED
