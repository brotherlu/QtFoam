#include "IOHandler.h"
#include "fileloader.h"

#include <glm/glm.hpp>
#include <cctype>
#include <cstring>
#include <vector>

static IOHandler& IOHandler::getIOHandler(){
	if (instanced)
		return instance;
	instanced = true;
	instance = new IOHandler();
	return instance;
}

static void IOHandler::load(const char* filename,
		std::vector<glm::vec3>& Verts,
		std::vector<glm::vec3>& Norms){
	
	int length = strlen(filename);
	char* extension; 
	
	strncpy(extension,&filename[length-4],4);
	
	for(unsigned int i=0; i<=4;++i)
		extension[i] = tolower(extension[i]);

	if(strcmp(extension,".stl")==0){
		getSTL(filename,Verts,Norms);
	}

}
