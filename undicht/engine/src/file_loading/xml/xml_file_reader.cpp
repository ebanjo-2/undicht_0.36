#include <file_loading/xml/xml_file_reader.h>
#include <iostream>

namespace undicht{


std::string XMLFileReader::line = "";

XMLFileReader::XMLFileReader(){
    // empty constructor
}

XMLFileReader::XMLFileReader(std::string file_name){
    open(file_name);
}




////////////////////////////////////////// loading the XmlElements from the file //////////////////////////////////////

void XMLFileReader::loadStartTagData(std::string &start_tag, XmlElement &loadTo){
    /**@brief extracts the tag_name and tag_attributes
    *   the start_tag should not (!!!) contain the '<' and the '>' , however the possible '/' at the end of the tag is o.k.
    */

    // loading the tag-name
    size_t tag_name_size = start_tag.find(' ', 0);
    if(tag_name_size == std::string::npos){
        if(start_tag.back() == '/'){
            // empty-XmlElement tag
            tag_name_size = start_tag.length() - 1;
        } else {
            // no attributes in the tag
            tag_name_size = start_tag.length();
        }
    }

    loadTo.m_tag_name = start_tag.substr(0, tag_name_size);

    // loading the tag-attributes
    size_t attribute_start = tag_name_size;
    size_t attribute_end = tag_name_size;
    size_t attribute_size = 0;

    while(true){
        attribute_start = start_tag.find(' ', attribute_end) + 1;

        if(attribute_start - 1 == std::string::npos){
            break;
        }

        attribute_end = start_tag.find(' ', attribute_start);

        if(attribute_end == std::string::npos){
            if(start_tag.back() == '/'){
                // empty XmlElement tag
                attribute_end = start_tag.length() - 1;
            } else {
                attribute_end = start_tag.length() - 0;
            }
        }

        attribute_size = attribute_end - attribute_start;
        loadTo.m_tag_attributes.push_back(start_tag.substr(attribute_start, attribute_size));

    }

}

bool XMLFileReader::loadXmlElement(XmlElement &loadTo){//, std::string &line){
    /** @brief loads the next XmlElement in the xml file
    *   @return returns true when the end-tag was reached
    *   @return returns false if the end-tag was not found before the end of the file was reached
    *   @param if next_line is set, it will be used instead of reading in a new one, done for optimization
    */

    //std::string line;

    if(!line.compare("")){
        getLine(line);
    }


    size_t start_of_start_tag = line.find('<', 0);
    size_t end_of_start_tag = line.find('>', 0);

    // moving to the next start-tag
    while(line.find('/') == start_of_start_tag + 1){
        // reading the next line ( if the previous line contained an end-tag>
        getLine(line);
        start_of_start_tag = line.find('<', 0);
        end_of_start_tag = line.find('>', 0);
    }

    // loading the start tag data
    std::string start_tag = line.substr(start_of_start_tag + 1, end_of_start_tag - start_of_start_tag - 1);
    loadStartTagData(start_tag, loadTo);

    // loading the XmlElements content
    if(start_tag.back() == '/'){
        // empty XmlElement tag
        return true; // no further data will be stored in the XmlElement
    }

    size_t end_of_content = line.rfind('<'); // searching for a possible end-tag in the line
    if(end_of_content > end_of_start_tag){ // checking if the end-tag was found
        size_t content_size = end_of_content - end_of_start_tag - 1;
        loadTo.m_content = line.substr(end_of_start_tag + 1, content_size);
        return true; // no further data will be stored in the XmlElement (more of an assumption based on what some files have looked like)
    }

    // checking if the XmlElement ends in the next line
    // reading the next line
    //int save_pos = getPosition(); // saving the position before reading the next line
    getLine(line);
    if(line.find("</" + loadTo.m_tag_name) != std::string::npos){
        // checking if this line contains the XmlElements end-tag
        return true; // the end-tag was found, no further data to read
    } else {
        //setPosition(save_pos);
    }

    // reading the XmlElements subordinated to the loadTo one
    while(!eof()){
        loadTo.m_subordinated.emplace_back(XmlElement());
        loadXmlElement(loadTo.m_subordinated.back());

        // checking if the XmlElement ends in the next line
        // reading the next line
        //int save_pos = getPosition(); // saving the position before reading the next line
        getLine(line);
        if(line.find("</" + loadTo.m_tag_name) != std::string::npos){
            // checking if this line contains the XmlElements end-tag
            return true; // the end-tag was found, no further data to read
        } else {
            //setPosition(save_pos);
        }
    }

    return false; // when eof was reached
}

void XMLFileReader::loadRootXmlElement(){
    /**@brief loads the XMLFileReaders root XmlElement containing all other XmlElements */

    if(loadXmlElement(m_root_XmlElement)){
        // the end of the file was not reached after the root XmlElement
        std::cout << "CORE:XMLFileReader:Error: eof was not reached after the root-XmlElement" << "\n";
    }
}



} // undicht
