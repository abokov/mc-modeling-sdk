// connector to Swift c++ SDK

#ifndef __SWIFT_CONNECTOR_INC__
#define __SWIFT_CONNECTOR_INC__

#include <mc-common/mc_base_types.h>

// Open Stack Swift headers...
#include <Header.h>
#include <Tenant.h>
#include <Service.h>

namespace McSwift {
  
class McSwiftConnector {
    Swift::Service *swift_service;
    Swift::Tenant * tenant;
public:
    McSwiftConnector();
    ~McSwiftConnector();
  
    bool Init(/*something should be there*/void);
    bool GetData(PositionJobData &job);
 }


#endif
