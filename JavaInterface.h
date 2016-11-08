
#ifndef ___JAVA_INTERFACE_INC____
#define ___JAVA_INTERFACE_INC____ 1

#include <sstream>
#include <jni.h>

namespace JavaJNI {


template <class T> inline std::string to_string (const T& t) {
	std::stringstream ss;
	ss << t;
	return ss.str();
}

class JavaJNIEntryData {
	JNIEnv *jni_env;
	jobject java_this;
	jobject java_param_obj;
	jobjectArray java_param_obj_arr;

	void CopyObject(const JavaJNIEntryData &val) {
		jni_env = val.jni_env;
		java_this = val.java_this;
		java_param_obj = val.java_param_obj;
		java_param_obj_arr = val.java_param_obj_arr;
	}
public:
	JavaJNIEntryData(JNIEnv *val_jni_env, jobject val_java_this, jobject val_java_param_obj, jobjectArray val_java_param_obj_arr = NULL ):
	 		jni_env(val_jni_env), java_this(val_java_this), java_param_obj(val_java_param_obj), java_param_obj_arr(val_java_param_obj_arr)  {
	}

	JavaJNIEntryData(const JavaJNIEntryData &val) {
		CopyObject(val);
	}


	~JavaJNIEntryData() {
	}


	const JavaJNIEntryData& operator=(const JavaJNIEntryData& obj) {
		CopyObject(obj);
		return *this;
	}


	inline JNIEnv * GetJniEnv(void) const {
		return jni_env;
	};
	
	inline const jobject GetThis(void) const {
		return java_this;
	};

	inline const jobject GetParamObj(void) const {
		return java_param_obj;
	};

	inline const jobjectArray GetParamObjArray(void) const {
		return java_param_obj_arr;
	};
};

class JavaJNIObjectClass {
	jobject java_obj;
	jclass java_class;
	std::string class_name;
public:
	JavaJNIObjectClass(JavaJNIEntryData &jni_entry, jobject obj, const char *name) {
		java_obj = obj;
		java_class = jni_entry.GetJniEnv()->GetObjectClass(obj);
		class_name = name;
	};

	inline const jobject GetObject(void) const {
		return java_obj;
	}

	inline const jclass GetClass(void) const {
		return java_class;
	}

	inline const char * GetName(void) const {
		return class_name.c_str();
	}
};


class JavaInterfaceCommon {
protected:
	JavaJNIEntryData jni_entry;

//---------------------------------------------------------------------------------------------------
//		common methods...
//---------------------------------------------------------------------------------------------------
// call java
	jmethodID get_method_id(JavaJNIObjectClass, const char *method_name, const char *method_signature);

	//  call 'method_name' which returns int
	int call_java_method_int(JavaJNIObjectClass, const char *method_name);

	//  call 'method_name' which returns double
	double call_java_method_double(JavaJNIObjectClass, const char *method_name);

	//  call 'method_name' which returns complex object
	jobject call_java_method_jobject(JavaJNIObjectClass, const char *method_name, const char *field_sig);

	//  call 'method_name' which have int parameter
	void call_java_method_param_int(JavaJNIObjectClass, const char *method_name, int param);

	//  call 'method_name' which have double parameter
	void call_java_method_param_double(JavaJNIObjectClass, const char *method_name, double param);



// access to fields
	jfieldID get_field_id(JavaJNIObjectClass, const char *field_name, const char *field_signature);

	//  read value of 'public int field_name'
	int get_java_field_int(JavaJNIObjectClass, const char *field_name);

	//  read value of 'public double field_name'
	double get_java_field_double(JavaJNIObjectClass, const char *field_name);

	//  read value of 'public string field_name'
	std::string get_java_field_string(JavaJNIObjectClass, const char *field_name);

	//  read value of 'public AnyClass field_name'
	jobject get_java_field_jobject(JavaJNIObjectClass, const char *field_name, const char *field_sig);


protected:
	// convert java_obj into CreditJobData
	JavaInterfaceCommon(JavaJNIEntryData &jni_data):jni_entry(jni_data) {
	}

	~JavaInterfaceCommon() {
	}
};


class JavaAccessException {
	std::string descr;
public:
	JavaAccessException(const char *class_id, const char * field_id, const char * reason1, const char *reason2="");

	inline const char * Describe(void) const {
		return descr.c_str();
	}
};



}


#endif

