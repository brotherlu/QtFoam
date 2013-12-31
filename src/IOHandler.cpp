#include "IOHandler.h"
#include "Asset.h"

#include <cstring>

IOHandler::IOHandler(void){

}

IOHandler* IOHandler::getIOHandler(void){
	instanced = true;
	return new IOHandler();
}

Asset* IOHandler::load(const char* filename){
	int length = strlen(filename);
	char* extension; 
	strncpy(extension,&filename[length-4],4);
	// see how make iohandler more generic
}
