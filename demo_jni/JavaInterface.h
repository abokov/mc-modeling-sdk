#ifndef ___JAVA_INTERFACE_INC____
#define ___JAVA_INTERFACE_INC____ 1

#include <sstream>
#include <jni.h>


#include <JavaInterface.h>

#include <core/PositionProcessor.h>


namespace JavaJNI {

class JavaInterface:JavaInterfaceCommon {

	// java data onto c++
	void convert_position_vector(PositionVector & job_data);

	// c++ data onto java
	void update_from_position_vector(PositionVector & job_data);
protected:
	// convert java_obj into PositionVector 
	JavaInterface(JavaJNIEntryData &jni_data, PositionVector &val);

	// same thing in another direction : update Java-data! 
	// save data from PositionVector onto jni_data
	// but actually we update only one field - because there's no need in this for others
	JavaInterface(PositionVector &val, JavaJNIEntryData &jni_data);

	~JavaInterface();

public: 

	static void Convert(JavaJNIEntryData &jni_data, PositionVector &obj) { // not sure about this 
		JavaInterface convert(jni_data, obj);
	};

	static void UpdateJava(PositionVector &obj, JavaJNIEntryData &jni_data) { // not sure about this 
		JavaInterface (obj, jni_data);
	};
};





};


#endif

