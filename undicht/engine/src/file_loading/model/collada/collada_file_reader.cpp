#include "file_loading/model/collada/collada_file_reader.h"
#include "file_loading/model/mesh_builder.h"

#include <file_loading/image/image_reader.h>
#include <core/event_logger.h>

using namespace undicht::core;


namespace undicht{



void ColladaFileReader::loadAllSubModels(ComplexTexturedModel& loadTo){
    /** loads all models from the file and stores them */

    prepare();


    XmlElement library_geometries = *m_root_XmlElement.m_subordinated.at(0).findSubordinated("library_geometries"); // only using the first library_geometries
    std::vector<XmlElement*> geometries = library_geometries.findAllSubordinated("geometry");

    // loading all geometries to the models
    for(XmlElement* & geometry_element : geometries){

        ColladaGeometry geometry;
        geometry = *geometry_element;

        // loadTo.emplace_back(Model3D());
        int sub_model = loadTo.addSubModel(TexturedModel());
        // loadTo.getSubModel(sub_model).initToDefault();
        loadModel(loadTo.getSubModel(sub_model), geometry);

    }

    EventLogger::storeNote(Note(UND_MESSAGE, "loaded " + toStr(loadTo.m_sub_models.size()) + " submodels from file " + m_file_name, UND_CODE_ORIGIN));


}
    ///////////////////////////////////////////// functions to process the files content //////////////////////////////////////////////


void ColladaFileReader::prepare(){
    /** prepares the reading from the file, by calling functions such as loadRootXmlElement
    * and loadAllTextures */

    if(!m_prepared){
        loadRootXmlElement();
        loadAllTextures();
    }

    m_prepared = true;
}

void ColladaFileReader::close(){

    m_reader.close();
    m_prepared = false;
    m_root_XmlElement = XmlElement();
}

void ColladaFileReader::loadModel(TexturedModel& loadTo, ColladaGeometry& source){
    /** loads the data stored and referenced in the geometry to the model
    * the mesh, textures, ... */

    // to store the mesh data
    std::vector<std::vector<float>> attribute_data;
    std::vector<int> vertex_layout;
    std::vector<int> attribute_indices;
    std::vector<int> attr_indices_layout;
    std::vector<float> vertices;

    // getting the data from the geometry
    source.getVertexAttribData(attribute_data);
    source.getVertexLayout(vertex_layout);
    source.getAttribIndices(attribute_indices);
    source.getAttrIndicesLayout(attr_indices_layout);


    // building the vertices
    MeshBuilder mesh_builder;
    mesh_builder.buildVertices(vertices, attribute_data, attribute_indices, vertex_layout, attr_indices_layout);


    // loading the data to the models mesh
    //loadTo.setUsesIndices(false);
    loadTo.m_mesh.setData(vertices);
    loadTo.m_mesh.setLayout(vertex_layout);


    loadTexture(loadTo, source, "diffuse");

}

void ColladaFileReader::loadTexture(TexturedModel& loadTo, ColladaGeometry& source, std::string texture_type){

    // getting the name of a texture is pretty complicated
    // and not as straight forward as it could be
    // the next 40 lines are just to get that name

    std::string material_name;
    std::string effect_name;
    std::string image_name;
    std::string texture_source;

    XmlElement* material_lib;
    XmlElement* material;
    ColladaMaterial col_material;

    XmlElement* effect_lib;
    XmlElement* effect;
    ColladaEffect col_effect;

    // getting the material name
    source.getMaterialName(material_name);
    material_name.insert(0, std::string("id=") + '"');
    material_name.insert(material_name.end(), '"');

    // getting the effect name
    material_lib = m_root_XmlElement.m_subordinated.at(0).findSubordinated("library_materials");
    material = material_lib->findSubordinated("material", material_name);
    if(!material) return;
    col_material = *material;
    col_material.getEffectName(effect_name);
    effect_name.insert(0, std::string("id=") + '"');
    effect_name.insert(effect_name.end(), '"');

    // getting the image name
    effect_lib = m_root_XmlElement.m_subordinated.at(0).findSubordinated("library_effects");
    effect = effect_lib->findSubordinated("effect", effect_name);
    if(!effect) return;
    col_effect = *effect;
    col_effect.getPhongTextureName(image_name, texture_type);// finally

    // searching for the right texture
    for(unsigned int i = 0; i < m_loaded_textures.size(); i++){
        if(!image_name.compare(m_texture_names.at(i))){
            loadTo.m_color = m_loaded_textures.at(i);
        }
    }



}

void ColladaFileReader::loadAllTextures(){
    /** loads all textures referenced in the file to the vector
    * & stores their names in the other vector */

    std::string file_path = m_file_name.substr(0, m_file_name.rfind('/') + 1);

    XmlElement library_images = *m_root_XmlElement.m_subordinated.at(0).findSubordinated("library_images"); // only using the first library_geometries
    std::vector<XmlElement*> images = library_images.findAllSubordinated("image");

    ImageReader image_reader;

    std::string image_source_file;

    for(XmlElement* e : images){
        ColladaImage collada_image;

        collada_image = *e;

        m_loaded_textures.emplace_back(graphics::Texture());

        image_reader.loadImage(m_loaded_textures.back(), file_path + collada_image.getSourceFile(image_source_file));
        m_texture_names.push_back(XmlElement::getAttrValue(collada_image.m_image_element->m_tag_attributes, "id"));

        m_loaded_textures.back().generateMipMaps();

    }
}




} // undicht
