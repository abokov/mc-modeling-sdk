
#include "hist_prices.h"

namespace BondData {
const double TreasureBond [] = {
#include "30_year_treasury_bond.inc"
};

const double Russel2000 [] = {
#include "russel_2000.inc"
};

const double S_and_P_100 [] = {
#include "s_and_p_100.inc"
};

const double S_and_P_500 [] = {
#include "s_and_p_500.inc"
};

const double IBM [] = {
#include "ibm.inc"
};

const double Yahoo [] = {
#include "yahoo.inc"
};

const double Microsoft [] = {
#include "microsoft.inc"
};

const double Google [] = {
#include "google.inc"
};

const double Amazon [] = {
#include "amazon.inc"
};

const double DeutscheBank [] = {
#include "deutsche_bank.inc"
};

const double AIG [] = {
#include "aig.inc"
};

const double Oracle [] = {
#include "oracle.inc"
};

const double Sun [] = {
#include "sun.inc"
};

const double Symantec [] = {
#include "symantec.inc"
};

const double Borland [] = {
#include "borland.inc"
};

const double ING [] = {
#include "ing.inc"
};


const double Macys [] = {
#include "macys.inc"
};

const double Ford [] = {
#include "ford.inc"
};

const double GeneralMotors [] = {
#include "gm.inc"
};

const double Toyota [] = {
#include "toyota.inc"
};

const double CocaCola [] = {
#include "cocacola.inc"    
};

const double WaltDisney [] = {
#include "waltdisney.inc"    
};

const double BritishAmericanTobacco [] = {
#include "bti.inc"
};

const double Sony [] = {
#include "sony.inc"
};

const double Boeing [] = {
#include "boeing.inc"
};


const double Skyline [] = {
#include "skyline.inc"    
};

const double DreamWorks [] = {
#include "dreamworks.inc"
};

const double TimeWarner [] = {
#include "timewarner.inc"
};

const double WesternUnion [] = {
#include "westernunion.inc"
};

// dude, you're looser :-)
const double LehmanBrothers [] = {
#include "lehmanbrothers.inc"
};

const double Cisco [] = {
#include "cisco.inc"
};

const double Pfizer [] = {
#include "pfizer.inc"
};

const double VMWare [] = {
#include "vmware.inc"
};

const double BankOfAmerica [] = {
#include "bank_of_america.inc"
};

const double Citigroup [] = {
#include "citigroup.inc"
};

const double JPMorganChase [] = {
#include "jpmorganchase.inc"
};


}


#define GET_VALUES(val) \
        case StockOptions::val: \
        *ptr = BondData::val; size = sizeof(BondData::val)/sizeof(double); \
        break;


void GetParamByFond(StockOptions::FondTypes t,const double **ptr, long &size) {
    switch (t) {
        GET_VALUES(TreasureBond)
        GET_VALUES(Russel2000)
        GET_VALUES(S_and_P_100)
        GET_VALUES(S_and_P_500)
        GET_VALUES(IBM)
        GET_VALUES(Yahoo)
        GET_VALUES(Microsoft)
        GET_VALUES(Google)
        GET_VALUES(Amazon)
        GET_VALUES(DeutscheBank)
        GET_VALUES(AIG)
        GET_VALUES(Oracle)
        GET_VALUES(Sun)
        GET_VALUES(Symantec)
        GET_VALUES(Borland)
        GET_VALUES(ING)
        GET_VALUES(Macys)
        GET_VALUES(Ford)
        GET_VALUES(GeneralMotors)
        GET_VALUES(Toyota)
        GET_VALUES(CocaCola)
        GET_VALUES(WaltDisney)
        GET_VALUES(BritishAmericanTobacco)
        GET_VALUES(Sony)
        GET_VALUES(Boeing)
        GET_VALUES(Skyline)
        GET_VALUES(DreamWorks)
        GET_VALUES(TimeWarner)
        GET_VALUES(WesternUnion)
        GET_VALUES(LehmanBrothers)
        GET_VALUES(Cisco)
        GET_VALUES(Pfizer)
        GET_VALUES(VMWare)
        GET_VALUES(BankOfAmerica)
        GET_VALUES(Citigroup)
        GET_VALUES(JPMorganChase)
    };
}

#undef GET_VALUES


#define GET_NAME(val) \
        case StockOptions::val: return #val;

//return name for fond - for Cisco it retursn "Cisco", for VMWare returns "VMWare", etc
const char *  GetTypeName(StockOptions::FondTypes fond) {
    switch (fond) {
        GET_NAME(TreasureBond)
        GET_NAME(Russel2000)
        GET_NAME(S_and_P_100)
        GET_NAME(S_and_P_500)
        GET_NAME(IBM)
        GET_NAME(Yahoo)
        GET_NAME(Microsoft)
        GET_NAME(Google)
        GET_NAME(Amazon)
        GET_NAME(DeutscheBank)
        GET_NAME(AIG)
        GET_NAME(Oracle)
        GET_NAME(Sun)
        GET_NAME(Symantec)
        GET_NAME(Borland)
        GET_NAME(ING)
        GET_NAME(Macys)
        GET_NAME(Ford)
        GET_NAME(GeneralMotors)
        GET_NAME(Toyota)
        GET_NAME(CocaCola)
        GET_NAME(WaltDisney)
        GET_NAME(BritishAmericanTobacco)
        GET_NAME(Sony)
        GET_NAME(Boeing)
        GET_NAME(Skyline)
        GET_NAME(DreamWorks)
        GET_NAME(TimeWarner)
        GET_NAME(WesternUnion)
        GET_NAME(LehmanBrothers)
        GET_NAME(Cisco)
        GET_NAME(Pfizer)
        GET_NAME(VMWare)
        GET_NAME(BankOfAmerica)
        GET_NAME(Citigroup)
        GET_NAME(JPMorganChase)
    }
	return "__unkwown__";
}

#undef GET_NAME




void init_vector(std::vector<double> &vec, const double arr[], size_t size)  {
	for (size_t i=0; i<size; i++) 
		vec.push_back(arr[i]);
}



static std::map<StockOptions::FondTypes, BaseTypes::double_vector> fond_storage;

namespace StockOptions {
BaseTypes::double_vector &  GetHistory(FondTypes fond) {
    std::map<FondTypes, BaseTypes::double_vector>::iterator iter = fond_storage.find(fond);
    if (iter == fond_storage.end()) {
        BaseTypes::double_vector vec;
        const double *ptr; long size;
		GetParamByFond(fond, &ptr, size);
		init_vector(vec, ptr, size);
        fond_storage[fond] = vec;
        iter = fond_storage.find(fond);
    };
    return iter->second;
}
}


