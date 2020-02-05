#ifndef COLLADA_GEOMETRY_H_INCLUDED
#define COLLADA_GEOMETRY_H_INCLUDED

#include <file_loading/xml/xml_element.h>
#include <3D/textured_model.h>

// a class to represent a geometry element in a collada file

namespace undicht{


class ColladaGeometry{

public:

    XmlElement* m_geometry_element;
    XmlElement* m_mesh;
    XmlElement* m_primitive; // only one primitive for now
    XmlElement* m_vertices;

public:
    // functions to read from the geometry element

    /** stores the vertex attribute data, such as the positions, uvs, normals
    * in the vectors */
    void getVertexAttribData(std::vector<std::vector<float>>& loadTo);

    /** stores the vertex layout (like {AttrVec3f, AttrVec2f, AttrVec3f} in the loadTo vector */
    void getVertexLayout(std::vector<int>& loadTo);

    /** stores the indices defining which attributes should be used to build the vertices */
    void getAttribIndices(std::vector<int>& loadTo);

    /** the order in which the indices define the attributes
    * @example (collada defines the uv attr. to be the third, undicht expects it to be the second)*/
    void getAttrIndicesLayout(std::vector<int> &loadTo);

    /** stores the name of the material used by the geometry in the loadTo string */
    void getMaterialName(std::string& loadTo);

private:
    // functions used for reading

    /** searches both the vertices object and the primitives inputs for an input with the semantic
    * returns 0 if no input was found */
    XmlElement* findPrimitiveInput(std::string semantic, XmlElement &primitive, XmlElement &vertices);

    /** searches both the vertices object and the primitives inputs for an input with the semantic
    * @return if a input with the semantic was found, the referenced source will be returned
    * returns 0 if no input was found */
    XmlElement* findPrimitiveSource(std::string input_semantic, XmlElement &mesh_source, XmlElement &primitive, XmlElement &vertices);


public:
    // XmlElement to ColladaGeometry

    void operator= (XmlElement &x);

};




} // undicht



#endif // COLLADA_GEOMETRY_H_INCLUDED
