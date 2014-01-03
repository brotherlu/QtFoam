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
 * @param[in]   out_vertices    Container for the vertices
 * @param[in]   out_uvs    Container for the uv coordinates
 * @param[in]   out_normals   Container for the normals
 * @return      bool true if operation successfull or false if unsuccessful
 * */

bool loadObj(
            const char* path,
            std::vector<glm::vec3 >& out_vertices,
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
            } else if (strcmp(line,"vn")==0){   /// if the line is a normal coordinate
                glm::vec3 norm;
                fscanf(file,"%f %f %f\n",&norm.x,&norm.y,&norm.z);
                temp_normals.push_back(norm);
            } else if (strcmp(line,"vt")==0){   /// if the line is a uv coordinate
                glm::vec2 uv;
                fscanf(file,"%f %f\n",&uv.x,&uv.y);
                temp_uvs.push_back(uv);
            } else if (strcmp(line,"f")==0){    /// if the line is a face
                /// Collect all the three columns of the face definitions
                char buff1[256];
                char buff2[256];
                char buff3[256];
                /// Populate the buffers
                fscanf(file,"%s %s %s\n",&buff1,&buff2,&buff3);
                /// Check for the data format
                /// formats are [d d d] || [d/d d/d d/d] || [d//d d//d d//d] || [d/d/d d/d/d d/d/d]
                unsigned int temp[3];
                unsigned int form2 = sscanf(buff1,"%d/%d",&temp[0],&temp[1]);
                unsigned int form3 = sscanf(buff1,"%d//%d",&temp[0],&temp[2]);
                unsigned int form4 = sscanf(buff1,"%d/%d/%d",&temp[0],&temp[1],&temp[2]);
                
                /// Create temporary data holders 
                unsigned int vx[3],uv[3],n[3];
                
                ///  Form 4 condition
                if(form4 == 3){
                    vx[0] = temp[0];
                    uv[0] = temp[1];
                    n[0] = temp[2];
                    sscanf(buff2,"%d/%d/%d",&vx[1],&uv[1],&n[1]);
                    sscanf(buff3,"%d/%d/%d",&vx[2],&uv[2],&n[2]);
                /// Form 3 Condition
                } else if(form3 == 2) {
                    vx[0] = temp[0];
                    n[0] = temp[2];
                    sscanf(buff2,"%d//%d",&vx[1],&n[1]);
                    sscanf(buff3,"%d//%d",&vx[2],&n[2]);
                /// Form 2 Condition
                } else if(form2 == 2) {
                    vx[0] = temp[0];
                    uv[0] = temp[1];
                    sscanf(buff2,"%d/%d",&vx[1],&uv[1]);
                    sscanf(buff3,"%d/%d",&vx[2],&uv[2]);
                /// Form 1 Condition
                } else{
                    sscanf(buff1,"%d",&vx[0]);
                    sscanf(buff2,"%d",&vx[1]);
                    sscanf(buff3,"%d",&vx[2]);
                }

                vertexIndices.push_back(vx[0]);
                vertexIndices.push_back(vx[1]);
                vertexIndices.push_back(vx[2]);
                
                if(form4==3 || form2 == 2){
                    uvIndices.push_back(uv[0]);
                    uvIndices.push_back(uv[1]);
                    uvIndices.push_back(uv[2]);
                }
                
                if(form4==3 || form3 == 2){
                    normIndex.push_back(n[0]);
                    normIndex.push_back(n[1]);
                    normIndex.push_back(n[2]);
                }
    
            } else {
                /// IF there is nothing recognized then skip it by dumping the muck
                char dump[1000];
                fgets(dump,1000,file);
                
                } 
            }
            
            /// Populate the referenced containers
            for(unsigned int i=0; i< vertexIndices.size();++i){
                unsigned int vertexIndex = vertexIndices[i];
                glm::vec3 vertex = temp_verts[vertexIndex-1]; 
                out_vertices.push_back(vertex);
            }
            
            /// Populate the out normals
            for(unsigned int i=0; i< normIndex.size();++i){
                unsigned int normalIndex = normIndex[i];
                glm::vec3 normal = temp_normals[normalIndex-1];
                out_normals.push_back(normal);
            }

            return 1;
    } else { return 0; }
    }

/**
 * STL ASCII Loader
 * 
 * @param[in]   path    Path to the file location
 * @param[in]   out_vertices    Container for the vertices
 * @param[in]   out_normals    Container for the normals
 * @return      bool true if the file is accessible false if the file does not exist
 * **/

bool loadSTL(
            const char* path,
            std::vector<glm::vec3 >& out_vertices,
            std::vector<glm::vec3 >& out_normals){

    /// Temporary file holders
    std::vector<glm::vec3 > temp_verts;
    std::vector<glm::vec3 > temp_normals;

    /// Load Wavefront OBJ files
    FILE* file = fopen(path,"r");

    /// Check if the file is open
    if(file!=NULL){
        /// Cycle through the file
        while(1){
            /// Create a data buffer
            char line[256];
            /// Scan the first line to see if it is readable
            int res = fscanf(file,"%s",line);
            /// Check if the file is open
            if(feof(file))
                break;

            /// Start comparing the value of the line
            if(strcmp(line,"facet")==0){ /// Check for normal
                glm::vec3 norm;
                fscanf(file,"%f %f %f\n",&norm.x,&norm.y,&norm.z);
                temp_normals.push_back(norm);
                temp_normals.push_back(norm);
                temp_normals.push_back(norm);
            } else if(strcmp(line,"vertex")==0){    /// Check for vertex
                glm::vec3 vert;
                fscanf(file,"%f %f %f\n",&vert.x,&vert.y,&vert.z);
                temp_verts.push_back(vert);
            } else {
                /// Clear if line does not match
                char dump[1000];
                fgets(dump,1000,file);
            }
        }
    }

    for(unsigned int i=0;i<temp_verts.size();i+=3){

        glm::vec3 temp;

        /// if normals are zero then we calculate our own
        if(temp_normals[i].x == 0 && temp_normals[i].y==0 && temp_normals[i].z ==0){
            temp_normals[i] = glm::normalize(glm::cross(temp_verts[i+2] - temp_verts[i],temp_verts[i+1] - temp_verts[i]));
        }
    }

    out_vertices = temp_verts;
    out_normals = temp_normals;

    fclose(file);

    return 1;
    }

/**
 * STL Binary Loader
 *
 * @param[in]   path    Path to the file location
 * @param[in]   out_vertices    Container for the vertices
 * @param[in]   out_normals    Container for the normals
 * @return      bool true if the file is accessible false if the file does not exist
 * */

bool loadBinSTL(
            const char* path,
            std::vector<glm::vec3 >& out_vertices,
            std::vector<glm::vec3 >& out_normals){

    /// Temporary file holders
    std::vector<glm::vec3 > temp_verts;
    std::vector<glm::vec3 > temp_normals;

    /// Load Wavefront OBJ files
    FILE* file = fopen(path,"rb");

    unsigned int triCount;

    /// Check if the file is open
    if(file!=NULL){
            /// Skip the first 80 characters
            fseek(file,80,SEEK_CUR);
            /// Get the length of the file
            fread(&triCount,sizeof(unsigned int),1,file);
            /// Loop through the triangles
            for(unsigned int i=0;i<triCount;++i){
                float buffer[12];
                fread(&buffer,sizeof(float)*12,1,file);
                /// Add normal
                glm::vec3 norm;
                norm.x = buffer[0];
                norm.y = buffer[1];
                norm.z = buffer[2];

                /// Add verts
                glm::vec3 vert1,vert2,vert3;
                vert1.x=buffer[3];
                vert1.y=buffer[4];
                vert1.z=buffer[5];
                vert2.x=buffer[6];
                vert2.y=buffer[7];
                vert2.z=buffer[8];
                vert3.x=buffer[9];
                vert3.y=buffer[10];
                vert3.z=buffer[11];

                /// if normals are zero then we calculate our own
                if(norm.x == 0 && norm.y == 0 && norm.z == 0){
                    norm = glm::normalize(glm::cross(vert3 - vert1,vert2 - vert1));
                }

                /// Add vertex thrice to be consistent with output of obj file
                for(unsigned int i=0;i<3;++i)
                    temp_normals.push_back(norm);

                temp_verts.push_back(vert1);
                temp_verts.push_back(vert2);
                temp_verts.push_back(vert3);
                /// Skip the next two bytes
                fseek(file,2,SEEK_CUR);
            }
    }

    out_vertices = temp_verts;
    out_normals = temp_normals;

    fclose(file);

    return false;
    }

bool checkSTL(const char* File){

    char buffer[256];
    FILE* f = fopen(File,"r");
    fscanf(f,"%s",buffer);
    fclose(f);

    if(strcmp(buffer,"solid")==0){
        return true;
    } else{
        return false;
    }
}

void getSTL(const char* filename,
		std::vector<glm::vec3>& verts,
		std::vector<glm::vec3>& norms){
	if(checkSTL(filename))
		loadSTL(filename,verts,norms);
	else
		loadBinSTL(filename,verts,norms);
}

#endif
