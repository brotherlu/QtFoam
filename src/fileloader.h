/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 * 
 */

/*
 * OBJ Loader Based on: https://code.google.com/p/opengl-tutorial-org/source/browse/common/objloader.cpp
 */

#ifndef _FILELOADER_
#define _FILELOADER_

#include <cstdio>
#include <string>
#include <cstring>
#include <vector>

#include <glm/glm.hpp>

/**
 * WaveFront OBJ file loader
 *  
 * @param[in]   path    File Location
 * @param[in]   vertices    Container for the vertices
 * @param[in]   faces   Container for the faces
 * @return      bool true if operation successfull or false if unsuccessful
 * */

bool loadObj(
            const char* path,
            std::vector<glm::vec3 >& out_vertices,
            std::vector<glm::vec2 >& out_uvs,
            std::vector<glm::vec3 >& out_normals){
    
    /// Temporary file holders
    std::vector<glm::vec3 > temp_verts;
    std::vector<glm::vec2 > temp_uvs;
    std::vector<glm::vec3 > temp_normals;
    
    /// Faces
    std::vector<unsigned int> vertexIndices, uvIndices, normIndex;
    
    /// Load Wavefront OBJ files
    FILE* file = fopen(path,"r");
    
    /// Check if the file is open
    if(file!=NULL){
        /// Cycle through the file 
        while(1){
            /// Create a data buffer
            char line[128];
            /// Scan the first line to see if it is readable
            int res = fscanf(file,"%s",line);
            /// Check if the file is open
            if(res==EOF)
                break;
            /// Start comparing the value of the line
            if(strcmp(line,"v") == 0){ /// if the line is for verts
                glm::vec3 vert;
                fscanf(file,"%f %f %f\n",&vert.x,&vert.y,&vert.z);
                temp_verts.push_back(vert);
            } else if (strcmp(line,"vt")==0){   /// if the line is a uv coordinate
                glm::vec2 uv;
                fscanf(file,"%f %f\n",&uv.x,&uv.y);
                temp_uvs.push_back(uv);
            } else if (strcmp(line,"f")==0){    /// if the line is a face
                unsigned int vx[3],uv[3],n[3];
                fscanf(file,"%d/%d/%d %d/%d/%d %d/%d/%d\n",&vx[0],&uv[0],&n[0],&vx[1],&uv[1],&n[1],&vx[2],&uv[2],&n[2]);
                vertexIndices.push_back(vx[0]);
                vertexIndices.push_back(vx[1]);
                vertexIndices.push_back(vx[2]);
                uvIndices.push_back(uv[0]);
                uvIndices.push_back(uv[1]);
                uvIndices.push_back(uv[2]);
                normIndex.push_back(n[0]);
                normIndex.push_back(n[1]);
                normIndex.push_back(n[2]);
            } else {
                /// IF there is nothing recognized then skip it by dumping the muck
                char dump[1000];
                fgets(dump,1000,file);
                
                } 
            }
            
            /// Populate the referenced containers
            for(unsigned int i=0; i< vertexIndices.size();++i){
                unsigned int vertexIndex = vertexIndices[i];
                unsigned int uvIndex = uvIndices[i];
                unsigned int normalIndex = normIndex[i];
                
                glm::vec3 vertex = temp_verts[vertexIndex-1]; 
                glm::vec2 uv = temp_uvs[uvIndex-1]; 
                glm::vec3 normal = temp_normals[normalIndex-1];
                
                out_vertices.push_back(vertex);
                out_uvs.push_back(uv);
                out_normals.push_back(normal);
            }
            
            return 1;
    } else { return 0; }
    }

/**
 * STL ASCII Loader
 * 
 * @param[in]   path    Path to the file location
 * @param[in]   vertices    Container for the vertices
 * @param[in]   faces    Container for the faces
 * @return      bool true if the file is accessible false if the file does not exist
 * **/

bool loadSTL(const char* path){
    // Load ASCII STL files
    return false;
    }

/**
 * STL Binary Loader
 * 
 * @param[in]   path    Path to the file location
 * @return      Geometry
 * */

bool loadBinSTL(const char* path){
    // Load Binary STL files
    return false;
    }

#endif