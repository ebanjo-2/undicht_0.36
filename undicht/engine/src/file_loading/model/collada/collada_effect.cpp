#include "file_loading/model/collada/collada_effect.h"
#include <iostream>


namespace undicht{


    //////////////////////////////////////////////// getting data from the effect ////////////////////////////////////////////


void ColladaEffect::getPhongTextureName(std::string&loadTo, std::string texture_type){
    /** searches the effects element specific to phong shading for a reference to a texture
    * fullfilling the texture_type, example: "diffuse" */

    // searching for the phong texture
    XmlElement* profile_COMMON = m_effect_element->findSubordinated("profile_COMMON");
    XmlElement* phong = profile_COMMON->findSubordinated("technique")->findSubordinated("phong");
    XmlElement* phong_param = phong->findSubordinated(texture_type);
    XmlElement* texture = phong_param->findSubordinated("texture");

    if(!texture){
        std::cout << "no " << texture_type << " texture found" << "\n";
        return;
    }


    loadTo = XmlElement::getAttrValue(texture->m_tag_attributes, "texcoord");

    // dont try to understand this mess, your head will hurt
    // but it works to get the image needed
    std::string sampler_name = XmlElement::getAttrValue(texture->m_tag_attributes, "texture");
    std::string sample_name_sid = std::string("sid=") + '"' + sampler_name + '"';
    XmlElement* sampler = profile_COMMON->findSubordinated("newparam", sample_name_sid)->findSubordinated("sampler2D");
    std::string sampler_source = sampler->findSubordinated("source")->m_content;
    std::string sampler_source_sid = std::string("sid=") + '"' + sampler_source + '"';
    XmlElement* surface = profile_COMMON->findSubordinated("newparam", sampler_source_sid)->findSubordinated("surface");
    loadTo = surface->findSubordinated("init_from")->m_content;


}


    //////////////////////////////////////////// XmlElement to ColladaEffect /////////////////////////////////////////////////

void ColladaEffect::operator= (XmlElement &x){

    m_effect_element = &x;

}



} // undicht
