#include <file_loading/xml/xml_element.h>
#include <iostream>

namespace undicht{



    ///////////////////////////////////////////////// operating on xml Elements for easier data access ///////////////////////////////

std::ostream &operator<< (std::ostream &out, XmlElement& e){
    /**@brief a function to output the XmlElements content*/

    out << "name: " << e.m_tag_name << "    " << "attributes:";
    for(std::string &attr : e.m_tag_attributes){
        out << attr << " ";

    }

    out << "    " << "content: " << e.m_content;

    out << "    " << "subordinated: " << e.m_subordinated.size() << "\n";

    return out;
}

std::string XmlElement::getAttrValue(std::vector<std::string> &attributes, std::string attr_name){
    /** @brief returns the value stored in the attribute with the attribute name
    *   @example searched attribute: "name="example""  then attr_name would be "name" and "example" would be returned
    *   @return an empty string is returned if no such attribute was found
    */

    size_t attr_name_end;
    size_t attr_value_size;

    for(std::string& attribute : attributes){

        attr_name_end = attribute.find("=");
        if(!attr_name.compare(attribute.substr(0, attr_name_end))){
            attr_value_size = attribute.length() - attr_name_end - 3;
            return attribute.substr(attr_name_end + 2, attr_value_size);
        }

    }

    return "";
}

////////////////////////////////////// searching for XmlElements ///////////////////////////////////////////

XmlElement* XmlElement::findSubordinated(std::string tag_name, std::string tag_attribute){
    /** @brief searches the subordinated XmlElements for one with the tag name *
    * @param if tag_attribute is set, this will also be an criterion
    * @return a pointer to the first XmlElement found fulfilling these criteria
    * @return returns 0 if no fitting XmlElement was found
    * tag_attribute should look like this: "id=example"
    */
    for(XmlElement& e : m_subordinated){
        // searching for a subordinated XmlElement with the tag_name

        if(!e.m_tag_name.compare(tag_name)){
            if(tag_attribute.compare("")){
                // if a tag_attribute is requested
                for(std::string attr : e.m_tag_attributes){
                    if(!attr.compare(tag_attribute)){
                        return &e; // the XmlElement fulfills both criteria
                    }
                }
            } else {
                // if no tag_attribute is requested
                return &e;
            }
        }

    }
    return 0;
}


XmlElement* XmlElement::findSubordinated(const std::vector<std::string> &tag_names, std::string tag_attribute){
    /** @brief searches the subordinated XmlElements for one with the one of the tag names  *
    * @param if tag_attribute is set, this will also be an criterion
    * @return a pointer to the first XmlElement found fulfilling these criteria
    * @return returns 0 if no fitting XmlElement was found
    * tag_attribute should look like this: "id=example"
    */
    for(XmlElement& e : m_subordinated){
        // searching for a subordinated XmlElement with one of the tag_names
        for(const std::string &tag_name : tag_names){
            if(!e.m_tag_name.compare(tag_name)){
                if(tag_attribute.compare("")){
                    // if a tag_attribute is requested
                    for(std::string attr : e.m_tag_attributes){
                        if(!attr.compare(tag_attribute)){
                            return &e; // the XmlElement fulfills both criteria
                        }
                    }
                } else {
                    // if no tag_attribute is requested
                    return &e;
                }
            }
        }

    }

    return 0;
}

std::vector<XmlElement*> XmlElement::findAllSubordinated(std::string tag_name, std::string tag_attribute){
    /** @brief searches the subordinated XmlElements for those with the tag name
    * @param if tag_attribute is set, this will also be an criterion
    * @return pointers to all XmlElements with that tag_name are returned */

    std::vector<XmlElement*> XmlElements;
    for(XmlElement& e : m_subordinated){
        // searching for a subordinated XmlElement with the tag_name
        if(!e.m_tag_name.compare(tag_name)){
            if(tag_attribute.compare("")){
                // if a tag_attribute is requested
                for(std::string attr : e.m_tag_attributes){
                    if(!attr.compare(tag_attribute)){
                        XmlElements.push_back(&e); // the XmlElement fulfills both criteria
                    }
                }
            } else {
                // if no tag_attribute is requested
                XmlElements.push_back(&e);
            }
        }

    }


    return XmlElements;

}

std::vector<XmlElement*> XmlElement::findAllSubordinated(const std::vector<std::string> &tag_names, std::string tag_attribute){
    /** @brief searches the subordinated XmlElements for those with one of the tag_names
    * @param if tag_attribute is set, this will also be an criterion
    * @return pointers to all XmlElements with that tag_name are returned */

    std::vector<XmlElement*> XmlElements;
    for(XmlElement& e : m_subordinated){
        // searching for a subordinated XmlElement with one of the tag_names
        for(const std::string &tag_name : tag_names){
            if(!e.m_tag_name.compare(tag_name)){
                if(tag_attribute.compare("")){
                    // if a tag_attribute is requested
                    for(std::string attr : e.m_tag_attributes){
                        if(!attr.compare(tag_attribute)){
                            XmlElements.push_back(&e); // the XmlElement fulfills both criteria
                        }
                    }
                } else {
                    // if no tag_attribute is requested
                    XmlElements.push_back(&e);
                }
            }

        }

    }


    return XmlElements;

}

int XmlElement::countSubordinated(std::string tag_name, std::string tag_attribute){
/** @return the number of tags with the tag name having the tag_attribute (optional)*/
    int XmlElement_count = 0;
    for(XmlElement& e : m_subordinated){
        // searching for a subordinated XmlElement with the tag_name
        if(!e.m_tag_name.compare(tag_name)){
            if(tag_attribute.compare("")){
                // if a tag_attribute is requested
                for(std::string attr : e.m_tag_attributes){
                    if(!attr.compare(tag_attribute)){
                        XmlElement_count += 1; // the XmlElement fulfills both criteria
                    }
                }
            } else {
                // if no tag_attribute is requested
                XmlElement_count += 1;
            }
        }

    }
    return XmlElement_count;
}




} // undicht
