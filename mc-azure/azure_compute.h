#ifndef __AZURE_COMPUTE_INC__
#define __AZURE_COMPUTE_INC__ 1

#include <iostream>
#include <map>

namespace McAzureCompute {
// just two types as first step
enum VM_TYPE { vm_A1, vm_A2, vm_D1, vm_D2 };
enum VM_REGION ( reg_EU_WEST, reg_EU_NORTH, reg_US_EAST };

struct AzureSubscription {
    std::string subscriptin_id;
};

struct AzureVM {
      // string ? really?
      std::string public_ip;
      std::string int_ip;
      
      AzureSubscription subscr;
      
      VM_REGION region;
      VM_TYPE vm_type;
};


class AzureCompute {

public:
    AzureCompute();
    ~AzureCompute();
    
    bool CreateAzureVM(AzureVM&vm );
};

#endif
