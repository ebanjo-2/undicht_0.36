#include <file_loading/model/collada/collada_material.h>


namespace undicht{



    //////////////////////////////////////////////// getting data from the material ////////////////////////////////////////////


void ColladaMaterial::getEffectName(std::string& loadTo){
    /** stores the name of the effect used by the material in the loadTo string */

    XmlElement* instance_effect = m_material_element->findSubordinated("instance_effect");
    loadTo = XmlElement::getAttrValue(instance_effect->m_tag_attributes, "url"); // getting the effect name

    loadTo.erase(0, 1); // deleting the '#'

}


    //////////////////////////////////////////// XmlElement to ColladaMaterial /////////////////////////////////////////////////

void ColladaMaterial::operator= (XmlElement &x){

    m_material_element = &x;

}




} // undicht
