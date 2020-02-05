#include <file_loading/model/collada/collada_image.h>


namespace undicht{


    //////////////////////////////////////////////// getting data from the image ////////////////////////////////////////////


std::string& ColladaImage::getSourceFile(std::string& loadTo){
    /** loads the images source file name to the string and returns it */

    XmlElement* source = m_image_element->findSubordinated("init_from");

    if(!source) return loadTo;

    loadTo = source->m_content;

    return loadTo;
}

    //////////////////////////////////////////// XmlElement to ColladaImage /////////////////////////////////////////////////

void ColladaImage::operator= (XmlElement &x){

    m_image_element = &x;

}




} // undicht
