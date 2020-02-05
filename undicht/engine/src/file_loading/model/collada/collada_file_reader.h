#ifndef COLLADA_FILE_READER_H_INCLUDED
#define COLLADA_FILE_READER_H_INCLUDED

#include <file_loading/xml/xml_file_reader.h>
#include <file_loading/model/collada/collada_geometry.h>
#include <file_loading/model/collada/collada_image.h>
#include <file_loading/model/collada/collada_material.h>
#include <file_loading/model/collada/collada_effect.h>

#include <3D/textured_model.h>
#include <3D/complex_model.h>


namespace undicht{



class ColladaFileReader : public XMLFileReader{

    std::vector<graphics::Texture> m_loaded_textures;
    std::vector<std::string> m_texture_names;

    bool m_prepared = false;

public:



    /** loads all models from the file and stores them  */
    void loadAllSubModels(ComplexTexturedModel& loadTo);

private:
    // functions to process the files content

    /** prepares the reading from the file, by calling functions such as loadRootXmlElement
    * and loadAllTextures */
    void prepare();

    void close();

    /** loads the data stored and referenced in the geometry to the model
    * the mesh, textures, ... */
    void loadModel(TexturedModel& loadTo, ColladaGeometry& source);

    void loadTexture(TexturedModel& loadTo, ColladaGeometry& source, std::string texture_type);

    /** loads all textures referenced in the file to the vector
    * & stores their names in the other vector*/
    void loadAllTextures();


};



} // undicht



#endif // COLLADA_FILE_READER_H_INCLUDED
