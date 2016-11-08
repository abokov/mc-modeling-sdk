// copyrights (c) http://www.danoneverythingelse.com/bxmlnode.cpp
/*
Copyright (c) 2003 Daniel W. Howard

Permission is hereby granted, free of charge, to any
person obtaining a copy of this software and associated
documentation files (the "Software"), to deal in the
Software without restriction, including without
limitation the rights to use, copy, modify, merge,
publish, distribute, sublicense, and/or sell copies of the
Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice
shall be included in all copies or substantial portions of
the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY
KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR
PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS
OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR
OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE. IN
NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE
FOR ANY SPECIAL, INDIRECT, INCIDENTAL, OR CONSEQUENTIAL
DAMAGES, OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF
USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT,
NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN
CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
*/

#ifdef _MSC_VER
  // visual c++ only
  #define _CRT_SECURE_NO_WARNINGS
#endif

#include <cstdio>
#include <cstring>
#include <stdlib.h>
#include <list>
#include <map>


#include "xml_config.h"


namespace XmlTools {
	// see below for implementation
     void readXml(const char *file, CommonTypes::SimulationTask &task);
};

// --- Class wrapper for basil xml functions
XmlConfigFile::XmlConfigFile(const char *config_file,CommonTypes::SimulationTask &my_task) {
	Init(config_file,my_task);
}

XmlConfigFile::~XmlConfigFile() {
	// do nothing currently
}

void XmlConfigFile::Init(const char *config_file,CommonTypes::SimulationTask &my_task) {
	cfg_file.assign(config_file);
	task = my_task;
}

bool XmlConfigFile::Read(void) {
	try {
		XmlTools::readXml(cfg_file.c_str(), task);
	} catch (...) { // this is actually why do we need that class :-)
		return false;
	}
	return true;
};

// --

// declarations for bxmlnode.cpp
/* basicxmlnode: simple xml node memory representation */
struct basicxmlnode
    {
        char * tag; /* always non-NULL */
        char * text; /* body + all whitespace, always non-NULL */
        char * * attrs; /* array of strings, NULL marks end */
        char * * values; /* array of strings, NULL marks end */
        struct basicxmlnode * * children; /* similar */
        int * childreni; /* children positions in text */
};

/* readbasicxmlnode: reads simple XML file */
struct basicxmlnode * readbasicxmlnode( FILE * fpi);
void printbasicxmlnodetagnames( struct basicxmlnode * node);
void deletebasicxmlnode( struct basicxmlnode * node);
void printbasicxmlnode( struct basicxmlnode * node);



namespace XmlTools {

using namespace CommonTypes;

std::string parse_xml(basicxmlnode * head, SimulationTask &task);


void readXml(const char *file, SimulationTask &task) {
    FILE *f = fopen(file,"rt");

    basicxmlnode * head = readbasicxmlnode(f);
	fclose(f);

    if (!head) { 
		printf("read failed\n");
		return;
	}

    std:: string err_msg = parse_xml(head, task);
    deletebasicxmlnode(head);
}

std::string parse_xml(basicxmlnode * head, SimulationTask &task) {
	if (strcmp(head->tag, "simulation_data"	) !=0 ) {
		return "tag <simulation_data> not found";
	}
	
	for (int i=0; head->children[i] != NULL; i++) {
		basicxmlnode * child = head->children[i];
		if (strcmp(child->tag, "horizon") == 0 ) {
			if (child->attrs[0] == NULL )
				return std::string("emptry attribute at tag horizon : expect type='...' ");
			else if (strcmp( child->attrs[0], "type") == 0)  {
				if (strcmp( child->values[0], "days") == 0) 
					task.horizon_type = SimulationTask::days;
				else if (strcmp( child->values[0], "months") == 0) 
					task.horizon_type = SimulationTask::months;
				else if (strcmp( child->values[0], "years") == 0) 
					task.horizon_type = SimulationTask::years;
				else
					return std::string("unkwown 'type' attribute value at tag horizon : ") + std::string(child->attrs[0]);
			} else	
				return std::string("unkwown 'type' attribute value at tag horizon : ") + std::string(child->attrs[0]);

			task.horizon = atoi(child->text);
			//;;
		} else if (strcmp(child->tag, "portfolio") == 0 ) 
			for (int j=0; child->children[j] != NULL; j++) {
					basicxmlnode * child2 = child->children[j];
					PortfolioElement element;
					std::string name; 
					if (strcmp(child2->tag, "element") == 0 ) {		
						for (int k=0; child2->attrs[k] != NULL; k++) {
							if (strcmp(child2->attrs[k], "name") == 0 )
								name = child2->values[k];
							else if (strcmp(child2->attrs[k], "type") == 0) {
								std::string type = child2->values[k];
								if (strcmp (type.c_str(), "stock") ==0 )
									element.poftfolio_type = PortfolioElement::stock;
								else if (strcmp (type.c_str(), "bond") ==0 )
									element.poftfolio_type = PortfolioElement::bond;
								else 
									return std::string("unkown value of type : ")+ std::string(child2->values[k]);
							} else if (strcmp(child2->attrs[k], "amount") == 0)
								element.amount = atoi(child2->values[k]);
							else
								return std::string("unkown attr at tag element : ")+ std::string(child2->attrs[k]);
						} // for (int k=0; child2->attrs[k] != NULL; k++) {
					} else  // if (strcmp(child2->tag, "element") == 0 ) {		
						return std::string("unknown tag : ") + std::string(child2->tag);
					if ( !name.length() )
 						return std::string("bad format, expect smth like '<element name=\"IBM\" type=\"bond\" amount=\"100\">");

					for (int k=0; child2->children[k] != NULL; k++) {
						basicxmlnode * child3 = child2->children[k];
						if (strcmp(child3->tag, "history") == 0 ) 
							for (int l=0; child3->children[l] != NULL; l++) {
								basicxmlnode * child4 = child3->children[l];
								if (strcmp(child4->tag, "data") == 0 ) {
									double value = atof(child4->text);
									element.history.push_back(value);
								} else // if (strcmp(child4->text, "data") == 0 ) {
									return std::string("unknown tag : ") + std::string(child4->text);
							} // for (int l=0; child3->children[l] != NULL; l++) {
						else // if (strcmp(child3->text, "history") == 0 ) 
							return std::string("unknown tag : ") + std::string(child3->text);
					}

					task.elements[name] = element;
			} // for (int j=0; child->children[j] != NULL; i++) {
		else 
			return std::string("unkwown tag : ") + std::string(child->tag);
	};
	return std::string("");
}
	

// namespace XmlTools {

}
