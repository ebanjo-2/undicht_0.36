#ifndef COLLADA_MATERIAL_H_INCLUDED
#define COLLADA_MATERIAL_H_INCLUDED

#include <file_loading/xml/xml_element.h>



// a class to represent a material element in a collada file

namespace undicht{


class ColladaMaterial{

public:

    XmlElement* m_material_element;

public:
    // getting data from the material

    /** stores the name of the effect used by the material in the loadTo string */
    void getEffectName(std::string& loadTo);



public:
    // XmlElement to ColladaMaterial

    void operator= (XmlElement &x);
    ColladaMaterial(){};
    ColladaMaterial(XmlElement &x){*this = x;}

};





} // undicht

#endif // COLLADA_MATERIAL_H_INCLUDED
