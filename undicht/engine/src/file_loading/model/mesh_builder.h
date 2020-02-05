#ifndef MESH_BUILDER_H_INCLUDED
#define MESH_BUILDER_H_INCLUDED

#include <vector>
#include <3D/textured_model.h>

// a class with functions used to build meshes with the data from files
// most filetypes store the vertex attributes seperated,
// so that they have to be arranged to make the vertices using indices


namespace undicht{


class MeshBuilder{
public:

    /** @brief builds vertices
    *  by using the attribute indices to figure out which
    * attribute data should be used for each vertex */
    void buildVertices(std::vector<float>& loadTo, std::vector<std::vector<float>>& attribute_data,
                        std::vector<int>& attribute_indices, std::vector<int>& vertex_layout,
                        std::vector<int>& attr_indices_layout);


};



} // undicht



#endif // MESH_BUILDER_H_INCLUDED
