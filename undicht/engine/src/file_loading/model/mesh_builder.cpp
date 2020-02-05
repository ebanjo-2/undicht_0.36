#include <file_loading/model/mesh_builder.h>
#include <core/types.h>

namespace undicht{

using namespace core;


void MeshBuilder::buildVertices(std::vector<float>& loadTo, std::vector<std::vector<float>>& attribute_data,
                                std::vector<int>& attribute_indices, std::vector<int>& vertex_layout,
                                std::vector<int>& attr_indices_layout){
    /** @brief builds vertices
    *  by using the attribute indices to figure out which
    * attribute data should be used for each vertex */

    unsigned int attribs_per_vertex = vertex_layout.size(); // the number of attributes per vertex
    unsigned int attr_length = 0; // the number of floats of the current atribute
    unsigned int attr_data_number; // which attribute data array is being processed
    unsigned int attr_number; // at which position the attribute is stored in the vertex
    unsigned int vertex_number; // the current vertex being processed
    unsigned int attr_id; // the attribute data to be used to build the next vertex (where to find the first element in the vector)

    // going through all attribute_indices to build the vertices
    for(unsigned int index_id = 0; index_id < attribute_indices.size(); index_id++){

        // getting some information about the current attribute
        vertex_number = index_id / attribs_per_vertex; // they are both ints (!)
        attr_number = index_id % attribs_per_vertex;
        attr_data_number = attr_indices_layout.at(attr_number);
        attr_id = attribute_indices.at(vertex_number * attribs_per_vertex + attr_data_number);

        if(vertex_layout.at(attr_number) == UND_VEC3F) attr_length = 3;
        if(vertex_layout.at(attr_number) == UND_VEC2F) attr_length = 2;

        // storing the attribute data for the vertex
        if(attribute_data.at(attr_number).size() >= ((attr_id + 1) * attr_length)){

            std::vector<float>::iterator data_start = attribute_data.at(attr_number).begin() + attr_id * attr_length;
            std::vector<float>::iterator data_end = data_start + attr_length;


            loadTo.insert(loadTo.end(), data_start, data_end);

        } else {
            // file is broken

            std::cout << "MESH BUILDING:ERROR: vertex attribute data is to short" << "\n";
            return;
        }

    }

    /* std::cout << "vertices: " << "\n";
    for(float& f : loadTo){
        std::cout << f << " ";
    }

    std::cout << "\n"; */



}





} // undicht
