#include <file_loading/model/collada/collada_geometry.h>
#include <core/types.h>

#include <array>
#include <vector>
#include <file_loading/file_reader.h>

/**@brief all possible types of arrays */
const std::vector<std::string> array_types{"float_array", "int_array", "bool_array", "Name_array", "IDREF_array"};

/**@brief all possible types of primitives */
const std::vector<std::string> primitive_types{"polylist", "triangles", "polygons", "lines", "trifans", "tristrips", "linestrips"};


namespace undicht{

    using namespace core;

    ///////////////////////////////////////////////////// functions to read from the geometry element ////////////////////////////////////////////////////


void ColladaGeometry::getVertexAttribData(std::vector<std::vector<float>>& loadTo){
    /** stores the vertex attribute data, such as the positions, uvs, normals
    * in the vectors */


    if(!m_mesh) return;
    if(!m_primitive) return;


    // loading the sources for the positions, uvs and normals
    XmlElement* position_source = findPrimitiveSource("POSITION", *m_mesh, *m_primitive, *m_vertices);
    XmlElement* uv_source = findPrimitiveSource("TEXCOORD", *m_mesh, *m_primitive, *m_vertices);
    XmlElement* normal_source = findPrimitiveSource("NORMAL", *m_mesh, *m_primitive, *m_vertices);

    // storing the attribute data
    if(position_source){
        loadTo.emplace_back(std::vector<float>());
        XmlElement* position_data = position_source->findSubordinated(array_types);
        extractFloatArray(loadTo.back(), position_data->m_content, position_data->m_content.size(), 1);
    }

    if(uv_source){
        loadTo.emplace_back(std::vector<float>());
        XmlElement* uv_data = uv_source->findSubordinated(array_types);
        extractFloatArray(loadTo.back(), uv_data->m_content, uv_data->m_content.size(), 1);
    }

    if(normal_source){
        loadTo.emplace_back(std::vector<float>());
        XmlElement* normal_data = normal_source->findSubordinated(array_types);
        extractFloatArray(loadTo.back(), normal_data->m_content, normal_data->m_content.size(), 1);
    }

}


void ColladaGeometry::getVertexLayout(std::vector<int>& loadTo){
    /** stores the vertex layout (like {UND_VEC3F, UND_VEC2F, UND_VEC3F} in the loadTo vector */

    if(!m_primitive) return;

    // loading the sources for the positions, uvs and normals
    XmlElement* position_source = findPrimitiveSource("POSITION", *m_mesh, *m_primitive, *m_vertices);
    XmlElement* uv_source = findPrimitiveSource("TEXCOORD", *m_mesh, *m_primitive, *m_vertices);
    XmlElement* normal_source = findPrimitiveSource("NORMAL", *m_mesh, *m_primitive, *m_vertices);

    if(position_source) loadTo.push_back(UND_VEC3F);
    if(uv_source) loadTo.push_back(UND_VEC2F);
    if(normal_source) loadTo.push_back(UND_VEC3F);


}



void ColladaGeometry::getAttribIndices(std::vector<int>& loadTo){
    /** stores the indices defining which attributes should be used to build the vertices */


    if(!m_primitive) return;

    XmlElement* indices_data = m_primitive->findSubordinated("p"); // p stands for primitives (i guess...)
    extractIntArray(loadTo, indices_data->m_content, indices_data->m_content.size(), 1);

}

void ColladaGeometry::getAttrIndicesLayout(std::vector<int> &loadTo){
    /** the order in which the indices define the attributes
    * @example (collada defines the uv attr. to be the third, undicht expects it to be the second)*/

    loadTo = {0, 2, 1};
}


void ColladaGeometry::getMaterialName(std::string& loadTo){
    /** stores the name of the material used by the geometry in the loadTo string */


    if(!m_primitive) return;

    // storing the material name
    loadTo =  XmlElement::getAttrValue(m_primitive->m_tag_attributes, "material");

}


    ///////////////////////////////////////////////////// functions used for reading /////////////////////////////////////////////////////////


XmlElement* ColladaGeometry::findPrimitiveInput(std::string semantic, XmlElement &primitive, XmlElement &vertices){
    /** searches both the vertices object and the primitives inputs for an input with the semantic */

    // if semantic is "POSITION" the attribute would be semantic="POSITION"
    std::string attribute = std::string("semantic=") + '"' + semantic + '"';

    XmlElement* vertices_input = vertices.findSubordinated("input", attribute);
    XmlElement* primitive_input = primitive.findSubordinated("input", attribute);

    if(vertices_input)
        return vertices_input;

    if(primitive_input)
        return primitive_input;

    return 0;
}

XmlElement* ColladaGeometry::findPrimitiveSource(std::string semantic, XmlElement &mesh_source, XmlElement &primitive, XmlElement &vertices){
    /** searches both the vertices object and the primitives inputs for an input with the semantic
    * @return if a input with the semantic was found, the referenced source will be returned
    * returns 0 if no input was found */

    XmlElement* input = findPrimitiveInput(semantic, primitive, vertices);

    if(!input)
        return 0; // no input was found

    std::string source_name = XmlElement::getAttrValue(input->m_tag_attributes, "source");
    source_name.erase(0, 1); // erasing the '#' at the start of the reference
    source_name.insert(0, std::string("id=").append(1, '"')).append(1, '"'); // making the attribute look like this: id="position_source_name"

    return mesh_source.findSubordinated("source", source_name);
}



    //////////////////////////////////////////////////////// XmlElement to ColladaGeometry ////////////////////////////////////////////////////////////////

void ColladaGeometry::operator= (XmlElement &x){

    m_geometry_element = &x;

    // getting the elements needed
    m_mesh = m_geometry_element->findSubordinated("mesh"); // there should be a mesh in every geometry

    if(!m_mesh){
        std::cout << "COLLADA:ERROR: no mesh found " << "\n";
        return;
    }

    m_primitive = m_mesh->findSubordinated(primitive_types); // only one primitive for now

    if(!m_primitive){
        std::cout << "COLLADA:ERROR: no primitives found " << "\n";
        return;
    }


    m_vertices = m_mesh->findSubordinated("vertices");

}





} // undicht
