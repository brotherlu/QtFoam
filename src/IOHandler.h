#ifndef IOHANDLER
#define IOHANDLER

#include <vector>
#include <glm/glm.hpp>

class IOHandler {
	public:
		static IOHandler& getIOHandler();
		void load(const char* filename,
				std::vector<glm::vec3>& Verts,
				std::vector<glm::vec3>& Norms);

	private:
		IOHandler();
		static bool instanced;
		static IOHandler* instance;
};

#endif
