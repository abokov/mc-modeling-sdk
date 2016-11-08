#ifndef _XML_CONFIG_INC__
#define	_XML_CONFIG_INC__  1


#include <string>

#include <CommonTypes.h>

class XmlConfigFile {
	std::string cfg_file;
	CommonTypes::SimulationTask task; 
public:
	XmlConfigFile(const char *config_file, CommonTypes::SimulationTask &my_task);
	~XmlConfigFile();

	void Init(const char *config_file, CommonTypes::SimulationTask &my_task);

	bool Read(void);

};



#endif



