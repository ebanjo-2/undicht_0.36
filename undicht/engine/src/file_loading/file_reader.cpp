#include "file_reader.h"
#include <iostream>

#include <stdlib.h>

// implementing the file reader class used by other file reading classes
// for example the model loading ones for .obj, .dae, ...

namespace undicht{


    ///////////////////////// constructing / destructing ///////////////////////////////////////////////

FileReader::FileReader(){
    // doing nothing
}

FileReader::FileReader(std::string file_name){
    // opening the file
    open(file_name);
}

FileReader::~FileReader(){
    // closes the m_reader;
    close();
}

    ///////////////////////// opening / closing the reader ////////////////////////////////////////////

void FileReader::open(std::string file_name){

    // closing the (potential) old file
    reset();
    close();

    // opening the File
    m_file_name = file_name;
    m_reader.open(file_name, std::fstream::in | std::fstream::out | std::ios::binary);

    if(m_reader.fail()){
        std::cout << "FILEREADER:ERROR: failed to open file: " << file_name << "\n";
        return;
    }


    m_reader.seekg(0, m_reader.end);
    m_file_length = m_reader.tellg();
    m_reader.seekg(0, m_reader.beg);

}

void FileReader::close(){
    m_reader.close();
}

    ////////////////////// getting information about current state of the reader /////////////////////

bool FileReader::eof(){
    /** whether the end of the file was reached or not*/
    return m_reader.eof();
}

bool FileReader::isOpen(){

    return m_reader.is_open();
}

bool FileReader::checkForErrors(){
    /** prints Error messages depending on the kind of error
    * returns true if there was an error */
    if(m_reader.fail()){
        std::cout << "CORE:FILE:ERROR: " << m_file_name << ": fail" << "\n";
        return true;
    }

    return false;
}

    //////////////////// getting specific information about the content of the file //////////////////

int FileReader::findChar(char c){
    /**@return returns the position of the next occurrence of c*/
    /** the readers position will be the same as before */

    // saving the old position
    int position_before = getPosition();
    char read = 0;

    while(read != c){
        *this >> read;
        if(eof()){
            break;
        }
    }

    int pos_of_c = getPosition() - 1;

    // setting the position of the reader to where it was before
    setPosition(position_before);

    return pos_of_c;
}


int FileReader::countLines(std::string start){
    // counting all lines starting with start
    int position_before = getPosition(); // saving the reading position before counting

    reset();
    int lines = 0;
    std::string s; // the start of the current line
    while(!eof()){
        s.clear();

        getLine(s);
        if(!s.compare(0, start.size(), start)){
            lines++;
        }
    }

    setPosition(position_before); // the position is the same as before counting

    return lines;
}

int FileReader::countLines(std::string start, int& first){
    /** @param updates first to the actual first occurrence */

    int position_before = getPosition();// saving the reading position before counting
    reset();

    bool first_occurance = true;
    int lines = 0;
    std::string s; // the start of the current line

    while(!eof()){

        if(first_occurance){ // the start did not appear jet
            // has to be before getLine()
            first = getPosition();
        }

        s.clear();
        getLine(s);

        if(!s.compare(0, start.size(), start)){
            lines++;
            first_occurance = false;
        }

    }

    setPosition(position_before); // the position is the same as before counting

    return lines;

}


    ////////////////////// managing the position of the reader in the file ///////////////////////////

void FileReader::setPosition(int position){
    /** the readers position will be updated */
    m_reader.seekg(position);
}

int FileReader::getPosition(){
    // returns the position
    return m_reader.tellg();
}


void FileReader::reset(){
    /** sets the position back to 0 and erases possible errors*/
    m_reader.clear();
    setPosition(0);
}


    ///////////////////////////////////// reading functions ///////////////////////////////////////////


std::string& FileReader::getLine(std::string &loadTo){
    // returns a string containing the chars from m_position to "\n"

    // reading until "\n"
    std::getline(m_reader, loadTo);

    return loadTo;
}

std::string& FileReader::getLine(std::string &loadTo, std::string start){
    // only returns the line if it starts with start

    size_t old_pos = getPosition();

    getLine(loadTo);

    if(loadTo.compare(0, start.length(), start)){
        loadTo.clear(); // the line did not start with "start"
        setPosition(old_pos);
    }

    return loadTo;
}

std::string& FileReader::read(std::string &loadTo, int num){
    // reads num chars and stores them at the end of the the loadTo array

    // to load the chars to
    char* char_buffer = new char[num];

    // reading
    m_reader.read(char_buffer, num);

    // storing the data in the string
    size_t old_size = loadTo.size();
    loadTo.resize(loadTo.size() + num);
    std::copy(char_buffer, char_buffer + num, loadTo.begin() + old_size);


    delete[] char_buffer;

    return loadTo;
}

std::string& FileReader::getAll(std::string& loadTo){
    /** reads the whole file, stores it in a ResizableArray and returns it
    * since the usage of the data in this array is managed vai an user manager
    * the returned array contains the content of the file,*/

    reset(); // moving to the beginning
    loadTo.clear();

    read(loadTo, m_file_length);

    // checking for errors
    checkForErrors();

    reset(); // moving back to the beginning


    return loadTo;
}




    //////////////////////////////////// reading via operators //////////////////////////////////////////

char& operator>> (FileReader &f, char &c){
    // extract one character from the "file"

    f.m_reader.get(c);

    return c;
}

std::string& operator>> (FileReader &f, std::string &loadTo){
    /** extract one string (one word) from the "file" (ending with ' ' or '\n')
    * the reader will be moved past the char ending the word */

    f.m_reader >> loadTo;
    f.setPosition(f.getPosition() + 1); // moving past the ' '

    return loadTo;
}



float& operator>> (FileReader &f, float& loadTo){
    // reading the float data into the reading buffer so that (in most cases) no "new" memory is needed
    f.m_reading_buffer.clear();
    f >> f.m_reading_buffer;
    loadTo = strtof(f.m_reading_buffer.data(),0);
    return loadTo;
}

int& operator>> (FileReader &f, int& loadTo){
    // reading the int data into the reading buffer so that (in most cases) no "new" memory is needed
    f.m_reading_buffer.clear();
    f >> f.m_reading_buffer;
    loadTo = strtol(f.m_reading_buffer.data(), 0, 0);
    return loadTo;
}


///////////////////////////////////////////// General file reading functions ///////////////////////////////

bool hasFileType(std::string file_name, std::string type){
    /**@brief checks if the file_name has the type (with type being the files ending, like ".obj" or ".jpg" */

    int start_of_ending = file_name.find('.', 0); // finding the file - ending

    return !file_name.compare(start_of_ending, type.length(), type);
}


/** removes the file name (*.*), and returns the remaining path */
std::string getFilePath(std::string file_name){

    size_t file_start = file_name.rfind("/");
    if(file_start != std::string::npos){
        file_name.resize(file_start + 1);
    }

    return file_name;
}

std::string replaceAll(std::string str, char to_be_replaced, char replace_with) {

    int pos = 0;

    while((pos = str.find(to_be_replaced, pos)) != std::string::npos) {
        str.at(pos) = replace_with;
    }

    return str;
}

void extractFloatArray(std::vector<float> &loadTo, std::string &src, unsigned int num, int stride){
    /**@brief float arrays might be stored as chars in a text file, this functions converts them to floats */
    /**@brief they should be only one char apart from each other though*/

    // loadTo.clear();

    src.push_back('X'); // making sure the extracting stops there
    // while reading through the array of chars,
    // this pointer points to the end of the last float extracted
    char* reading_position = ((char*)src.data());
    char* end_position = ((char*)src.data()) + src.size() - 1;

    while(reading_position < end_position){
        // the strtof function will store the end of the extracted float in the char array as an pointer
        // this way the reading position gets updated and moves forward
        loadTo.push_back(strtof(reading_position, &reading_position));

        if(loadTo.size() >= num){
            break;
        }

		reading_position += stride;

    }

    src.pop_back(); // deleting the last char

}


void extractIntArray(std::vector<int> &loadTo, std::string &src, unsigned int num, int stride){
    /**@brief extract ints from a char array*/
    /** @warning might not work correctly if the src's length equals its capacity, so make sure there is (at least) one extra char */

    // loadTo.clear();

    src.push_back('X'); // making sure the extracting stops there
    // while reading through the array of chars,
    // this pointer points to the end of the last float extracted
    char* reading_position = ((char*)src.data());
    char* end_position = ((char*)src.data()) + src.size() - 1;

    while(reading_position < end_position){
        // the strtof function will store the end of the extracted float in the char array as an pointer
        // this way the reading position gets updated and moves forward
        loadTo.push_back(strtol(reading_position, &reading_position, 0));

        if(loadTo.size() >= num){
            break;
        }

		reading_position += stride;

    }

    src.pop_back(); // deleting the last char


}



} // undicht
