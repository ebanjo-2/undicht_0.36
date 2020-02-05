#ifndef FILE_READER_H_INCLUDED
#define FILE_READER_H_INCLUDED

#include <string>
#include <fstream>
#include <vector>


// a class providing some usefull features to read from files

namespace undicht{




// provides some reading functions, other file formats (like .obj) have classes that inherit from this one
class FileReader{

public:
    // private members of the reader

    std::fstream m_reader;

    /**used to temporarily store data needed by some reading functions */
    //undicht::ResizeableArray<char> m_reading_buffer;
    std::string m_reading_buffer;

public:

    // information about the file

    std::string m_file_name;

    // the length of the file as the number of chars
    int m_file_length = 0;

public:
    // constructing / destructing

    FileReader();
    FileReader(std::string file_name);
    virtual ~FileReader(); // closes the m_reader;

public:
    // opening / closing the reader

    void open(std::string file_name);
    virtual void close(); // m_reader.close()

public:
    // getting information about current state of the reader

    bool eof();
    bool isOpen();
    /* returns true if there was an error */
    bool checkForErrors(); // prints Error messages depending on the kind of error

public:
    // getting specific information about the content of the file

    /**@return returns the position of the next occurrence of c*/
    /** the readers position will be the same as before */
    int findChar(char c);


    int countLines(std::string start);
    int countLines(std::string start, int& first); // updates first to the actual first occurrence


public:
    // managing the position of the reader in the file

    void setPosition(int position);// if m_everything_read is false the readers position will be updated as well as m_position

    int getPosition(); // updates and returns the position

    /** sets the position back to 0 and erases possible errors*/
    void reset();


public:
    // reading functions

    /** returns a string containing the chars from m_position to "\n" */
    std::string& getLine(std::string &loadTo);

    /** only returns the line if it starts with start
    * if not, the reader will be reset to where it was before */
    std::string& getLine(std::string &loadTo, std::string start);

    /** reads num chars and stores them at the end of the the loadTo string */
    std::string &read(std::string &loadTo, int num);

    /** reads the whole file, stores it in a string and returns it
    * @return the string in which the content is stored */
    std::string& getAll(std::string& loadTo);



public:

    // reading via operators
    friend char& operator>> (FileReader &f, char &c);// extract one character from the "file"

    /** extract one string (one word) from the "file" (ending with ' ' or '\n')
    * the reader will be moved past the char ending the word */
    friend std::string& operator>> (FileReader &f, std::string &loadTo);

    /** reads a "word" from the file and tries to interpret it as a float */
    friend float& operator>> (FileReader &f, float& loadTo);

    /** reads a "word" from the file and tries to interpret it as an int */
    friend int& operator>> (FileReader &f, int& loadTo);

};

/**@brief checks if the file_name has the type (with type being the file's ending, like ".obj" or ".jpg" */
bool hasFileType(std::string file_name, std::string type);

/** removes the file name (*.*), and returns the remaining path */
std::string getFilePath(std::string file_name);

/** replaces all chars in the string */
std::string replaceAll(std::string str, char to_be_replaced, char replace_with);

/**@brief float arrays might be stored as chars in a text file, this functions converts them to floats
    * @param num is the number of floats to extract
    * @param stride is the distance in chars between each float, default is 1 (example: " ")*/
void extractFloatArray(std::vector<float> &loadTo, std::string &src, unsigned int num, int stride = 1);

/**@brief extract ints from a char array
    * @param num is the number of ints to extract
    * @param stride is the distance in chars between each int, default is 1 (example: " ") */
void extractIntArray(std::vector<int> &loadTo, std::string &src, unsigned int num, int stride = 1);



} // undicht



#endif // FILE_READER_H_INCLUDED
