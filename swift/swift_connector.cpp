
#include "swift_connector.h"

namespace McSwift {
using namespace Swift;

McSwiftConnector::McSwiftConnector() {
    service = new Service();
    tenant = new Tenant();
    account = new Account ();
};

McSwiftConnector::~McSwiftConnector() {
try { // better to catch everything
  
    delete account;
    delete service;
    delete tenant;
  
  
} catch (...) {
  // add some handling there
};
}
  
bool McSwiftConnector::Init(/*something should be there*/void) {
/*
    AuthenticationInfo _authInfo;
    account->uthenticate(const AuthenticationInfo &_authInfo, bool _allowReauthenticate = true);
    // somehow create tenant and then service....
    
*/
    return false;
};

bool McSwiftConnector::GetData(PositionJobData &job) {
    return false;
};



} // namespace McSwift
