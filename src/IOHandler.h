#ifndef IOHANDLER
#define IOHANDLER

#include "Asset.h"

class IOHandler {
	private:
		IOHandler(void);
		bool instanced;
	public:
		static IOHandler* getHandler(void);
		static asset* load(const char* filename);
};

#endif
