#ifndef XML_ELEMENT_H_INCLUDED
#define XML_ELEMENT_H_INCLUDED


#include <vector>
#include <string>

// a class representing an Element in a xml file

namespace undicht{



class XmlElement{
/**@brief represents an XmlElement in a xml file*/
public:
    std::string m_tag_name;
    std::vector<std::string> m_tag_attributes;
    std::string m_content;
    // there is a hierarchy of XmlElements, so one XmlElement can contain multiple others
    std::vector<XmlElement> m_subordinated;

    /** @brief searches the subordinated XmlElements for one with the tag name */
    /** @param if tag_attribute is set, this will also be an criterion*/
    /** @return a pointer to the first XmlElement found fulfilling these criteria*/
    /** @return returns 0 if no fitting XmlElement was found*/
    XmlElement* findSubordinated(std::string tag_name, std::string tag_attribute = "");

    /** @brief searches the subordinated XmlElements for one with one of the tag names */
    /** @param if tag_attribute is set, this will also be an criterion*/
    /** @return a pointer to the first XmlElement found fulfilling these criteria*/
    /** @return returns 0 if no fitting XmlElement was found*/
    XmlElement* findSubordinated(const std::vector<std::string> &tag_names, std::string tag_attribute = "");

    /** @brief searches the subordinated XmlElements for those with the tag name */
    /** @param if tag_attribute is set, this will also be an criterion*/
    /** @return pointers to all XmlElements with that tag_name are returned */
    std::vector<XmlElement*> findAllSubordinated(std::string tag_name, std::string tag_attribute = "");

    /** @brief searches the subordinated XmlElements for those with one of the tag_names */
    /** @param if tag_attribute is set, this will also be an criterion*/
    /** @return pointers to all XmlElements with that tag_name are returned */
    std::vector<XmlElement*> findAllSubordinated(const std::vector<std::string> &tag_names, std::string tag_attribute = "");

    /** @return the number of tags with the tag name having the tag_attribute (optional)*/
    int countSubordinated(std::string tag_name, std::string tag_attribute = "");

    /**@brief a function to output the XmlElements content*/
    friend std::ostream& operator<< (std::ostream& out, XmlElement &e);

    /** @brief returns the value stored in the attribute with the attribute name
    *   @example searched attribute: "name="example""  then attr_name would be "name" and "example" would be returned
    *   @return an empty string is returned if no such attribute was found
    */
    static std::string getAttrValue(std::vector<std::string> &attributes, std::string attr_name);

    XmlElement(){};
    virtual ~XmlElement(){};
};


} // undicht



#endif // XML_ELEMENT_H_INCLUDED
