#include <iostream>
#include <vector>
#include <cstring>
#include <glm/glm.hpp>

#include "IOHandler.h"

int main(int argc, char** argv){
    
    std::vector<glm::vec3> Verts;
    std::vector<glm::vec3> Normals;

    std::cout << argc << " " << argv[1] << std::endl;

    IOHandler A = IOHandler::getIOHandler();
    
/*
    if (argc >= 2)
	    getSTL(argv[1],Verts,Normals);
    else
	    std::cout << "Please input a filename" <<std::endl;
*/
    printf("%d\n",Normals.size());
    printf("%d\n",Verts.size());
    
    printf("%.4f\t%.4f\n",Verts[500].x,Normals[500].x);

    return 0;
    
    }
