#ifndef _XML_CONFIG_INC__
#define	_XML_CONFIG_INC__  1


#include <string>

#include "mc-common/mc-base-types.h"

class XmlConfigFile {
	std::string cfg_file;
	BaseTypes::SimulationTask task; 
public:
	XmlConfigFile(const char *config_file, BaseTypes::SimulationTask &my_task);
	~XmlConfigFile();

	void Init(const char *config_file, BaseTypes::SimulationTask &my_task);

	bool Read(void);

};



#endif



