#include "JavaInterface.h"


namespace JavaJNI {

// convert java_obj into CreditVector
JavaInterface::JavaInterface(JavaJNIEntryData &jni_data, PositionVector &val):JavaInterfaceCommon(jni_data) {
	convert_position_vector(val);
}



// same thing in another direction : update Java-data! 
// save data from PositionVector onto jni_data
// but actually we update only one field - because there's no need in this for others
JavaInterface::JavaInterface(PositionVector &val, JavaJNIEntryData &jni_data):JavaInterfaceCommon(jni_data) {
	update_from_position_vector(val);
}



JavaInterface::~JavaInterface() {
}


void JavaInterface::convert_position_vector(PositionVector & position_vector) {
 // do something...
try {
	jobjectArray arr = jni_entry.GetParamObjArray();
	jsize len = jni_entry.GetJniEnv()->GetArrayLength(jni_entry.GetParamObjArray());
	//!!! sic!
	position_vector.resize(len);

	for (int i=0;i<len;i++) {
		JavaJNIObjectClass position_object(jni_entry, jni_entry.GetJniEnv()->GetObjectArrayElement(arr, i), "Position");

	//	std::string name, type;
	//	double units, amount, simulatedValue;
		position_vector[i].SetName( get_java_field_string(position_object, "name").c_str());
		position_vector[i].SetType( get_java_field_string(position_object, "type").c_str());

		position_vector[i].SetUnits(get_java_field_double(position_object, "units"));
		position_vector[i].SetAmount(get_java_field_double(position_object, "amount"));
		position_vector[i].SetSimulatedValue(get_java_field_double(position_object, "simulatedValue"));
	};
} catch (JavaAccessException ex) {
	printf("Error : %s\n", ex.Describe());
}

};


// same thing in another direction : update Java-data! 
// save data from PositionVector onto jni_data
// but actually we update only one field - because there's no need in this for others
void JavaInterface::update_from_position_vector(PositionVector & position_vector) {
 // do something...
try {
	jobjectArray arr = jni_entry.GetParamObjArray();
	jsize len = jni_entry.GetJniEnv()->GetArrayLength(jni_entry.GetParamObjArray());

	for (int i=0;i<len;i++) {
		JavaJNIObjectClass position_object(jni_entry, jni_entry.GetJniEnv()->GetObjectArrayElement(arr, i), "Position");

		// UPDATE only SimulatedValue
		double val = position_vector[i].GetSimulatedValue(); 
		call_java_method_param_double(position_object, "setSimulatedValue", val);

	};
} catch (JavaAccessException ex) {
	printf("Error : %s\n", ex.Describe());
}
}



}

