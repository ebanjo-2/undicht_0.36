#ifndef XML_FILE_H_INCLUDED
#define XML_FILE_H_INCLUDED

#include <file_loading/file_reader.h>
#include <file_loading/xml/xml_element.h>
#include <vector>
#include <string>
#include <iostream>

namespace undicht{



class XMLFileReader : public FileReader{
/**@brief some functions for accessing data in xml based files */
private:
    static std::string line; // for optimization purposes

private:
    /**@brief extracts the tag_name and tag_attributes
    *   the start_tag should not (!!!) contain the '<' and the '>' , however the possible '/' at the end of the tag is o.k.
    */
    void loadStartTagData(std::string &start_tag, XmlElement &loadTo);

    /** @brief loads the next XmlElement in the xml file
    *   @return returns true when the end-tag was reached
    *   @return returns false if the end-tag was not found before the end of the file was reached
    *   @param if next_line is set, it will be used instead of reading in a new one, done for optimization
    */
    bool loadXmlElement(XmlElement &loadTo);//, std::string &line = empty_string);


public:

    XmlElement m_root_XmlElement; // contains all other XmlElements in the file

    /**@brief loads the xmlfiles root XmlElement containing all other XmlElements */
    void loadRootXmlElement();

    XMLFileReader();
    XMLFileReader(std::string file_name);

    virtual ~XMLFileReader(){};
};




} // undicht


#endif // XML_FILE_H_INCLUDED
