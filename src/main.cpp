#include <iostream>
#include <vector>
#include <glm/glm.hpp>
#include "fileloader.h"

int main(int argc, char** argv){
    
    std::vector<glm::vec3> Verts;
    std::vector<glm::vec3> Normals;
    
    std::vector<glm::vec3> Verts1;
    std::vector<glm::vec3> Normals1;
    
    //bool res = loadSTL("tester.stl",Verts,Normals);
    bool res = loadObj("teapot.obj",Verts,Normals);
    bool res1 = loadObj("test.obj",Verts1,Normals1);
    
    printf("%d\n",Normals.size());
    printf("%d\n",Normals1.size());
    
    return 0;
    
    }
