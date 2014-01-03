#ifndef ASSET
#define ASSET

#include <glm/glm.hpp>
#include <QListWidgetItem>

class Asset : public QListWidgetItem{
	public:
		Asset(std::vector<glm::vec3>& verts,std::vector<glm::vec3> norms){
			_v = verts;
			_n = norms;
		}
		std::vector<glm::vec3> _v;
		std::vector<glm::vec3> _n;
};

#endif
