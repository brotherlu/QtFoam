#include <iostream>
#include <vector>
#include <cstring>
#include <glm/glm.hpp>
#include "fileloader.h"

int main(int argc, char** argv){
    
    std::vector<glm::vec3> Verts;
    std::vector<glm::vec3> Normals;

    std::cout << argc << " " << argv[1] << std::endl;

    char* filename;

    if (argc >= 2)
	    filename = argv[1];
    else
	    std::cout << "Please input a filename" <<std::endl;

    if (argc >= 3)
	    if(strcmp(argv[2],"-b")==0)
		    loadBinSTL(filename,Verts,Normals);
    	    else if (strcmp(argv[2],"-a")==0)
		    loadSTL(filename,Verts,Normals);

    printf("%d\n",Normals.size());
    printf("%d\n",Verts.size());
    
    printf("%.4f\t%.4f\n",Verts[500].x,Normals[500].x);

    return 0;
    
    }
