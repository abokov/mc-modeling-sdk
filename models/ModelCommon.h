#ifndef ___MODEL_COMMON_INC____
#define ___MODEL_COMMON_INC____ 1

namespace MonteCarloModel {

//template<class RetValue,class EntryData> class ModelCommon {
template<class ModelValue, class EntryData > class ModelCommonTemplate {
	ModelValue model_value_result;
	EntryData init_value;

protected:

	// core functionality - child classes have implement this one - take EntryData and put model value into result
	// Calculate uses init_value in most cases..
	virtual	void Calculate(const EntryData &, ModelValue &result) = 0;
public:

	inline void SetInitValue(const EntryData & val) {
		init_value = val;
	}

	inline EntryData & GetInitValue(void) {
		return 	init_value;
	}


	// faster, but we have const pointer onto ModelValye object
	inline const ModelValue& GetModelValuePtr(const EntryData & val) {
		Calculate(val, model_value_result);
		return model_value_result;
	}

	// slow, but we have copy of ModelValye object
	inline ModelValue GetModelValue(const EntryData & val) {
		Calculate(val, model_value_result);
		return model_value_result;
	}

        virtual void UpdateBrownMotion(const EntryData &val) = 0;

        virtual std::string Print(void) = 0;

};

// entry data - long, return long
typedef ModelCommonTemplate<long, long>  ModelCommonLong;

// entry data - double, return double
typedef ModelCommonTemplate<double, double>  ModelCommonDouble;


}

#endif




