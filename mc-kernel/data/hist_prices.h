#ifndef __PRICES_HISTORY_INC___
#define __PRICES_HISTORY_INC___ 1

#include "mc-common/mc-base-types.h"

namespace StockOptions {
enum FondTypes {
TreasureBond=1,
Russel2000,
S_and_P_100,
S_and_P_500,
IBM,
Yahoo,
Microsoft,
Google,
Amazon,
DeutscheBank,
AIG,
Oracle,
Sun,
Symantec,
Borland,
ING,
Macys,
Ford,
GeneralMotors,
Toyota,
CocaCola,
WaltDisney,
BritishAmericanTobacco,
Sony,
Boeing,
Skyline,
DreamWorks,
TimeWarner,
WesternUnion,
LehmanBrothers,
Cisco,
Pfizer,
VMWare,
BankOfAmerica,
Citigroup,
JPMorganChase
};

// returns history for fond
BaseTypes::double_vector &  GetHistory(FondTypes fond);

};


//return name for fond - for Cisco it retursn "Cisco", for VMWare returns "VMWare", etc
const char *  GetTypeName(StockOptions::FondTypes fond);




#endif

