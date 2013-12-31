#ifndef IOHANDLER
#define IOHANDLER

class Asset;

class IOHandler {
	private:
		IOHandler(void);
		bool instanced;
	public:
		static IOHandler* getHandler(void);
		static asset* load(const char* filename);
};

#endif
