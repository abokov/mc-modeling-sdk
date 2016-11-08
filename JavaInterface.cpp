
#include "JavaInterface.h"

namespace JavaJNI {


jmethodID JavaInterfaceCommon::get_method_id(JavaJNIObjectClass obj, const char *method_name, const char *method_signature) {
	jmethodID mid = jni_entry.GetJniEnv()->GetMethodID(obj.GetClass(), method_name, method_signature); 
	if (mid == NULL) 
		throw JavaAccessException(obj.GetName(), method_name, method_signature, " GetMethodId() == NULL");
	return mid;
}

//  call 'method_name' which returns int
int JavaInterfaceCommon::call_java_method_int(JavaJNIObjectClass java_class, const char *method_name) {
	jmethodID mid = get_method_id(java_class, method_name, "()I"); 
	return jni_entry.GetJniEnv()->CallIntMethod(java_class.GetObject(), mid);
}

//  call 'method_name' which returns double
double JavaInterfaceCommon::call_java_method_double(JavaJNIObjectClass java_class, const char *method_name) {
	jmethodID mid = get_method_id(java_class, method_name, "()D"); 
	return jni_entry.GetJniEnv()->CallDoubleMethod(java_class.GetObject(), mid);
}

//  call 'method_name' which returns complex object
jobject JavaInterfaceCommon::call_java_method_jobject(JavaJNIObjectClass java_class, const char *method_name, const char *method_sig) {
	jmethodID mid = get_method_id(java_class, method_name, method_sig); 
	return jni_entry.GetJniEnv()->CallObjectMethod(java_class.GetObject(), mid);
}


//  call 'method_name' which have int parameter
void JavaInterfaceCommon::call_java_method_param_int(JavaJNIObjectClass java_class, const char *method_name, int param) {
	jmethodID mid = get_method_id(java_class, method_name, "(I)V"); 
	jni_entry.GetJniEnv()->CallVoidMethod(java_class.GetObject(), mid, param);
}

//  call 'method_name' which have double parameter
void JavaInterfaceCommon::call_java_method_param_double(JavaJNIObjectClass java_class, const char *method_name, double param) {
	jmethodID mid = get_method_id(java_class, method_name, "(D)V"); 
	jni_entry.GetJniEnv()->CallVoidMethod(java_class.GetObject(), mid, param);
}




jfieldID JavaInterfaceCommon::get_field_id(JavaJNIObjectClass obj, const char *field_name, const char *field_signature) {
	jfieldID fid = jni_entry.GetJniEnv()->GetFieldID(obj.GetClass(), field_name, field_signature); 
	if (fid == NULL) 
		throw JavaAccessException(obj.GetName(), field_name, field_signature, " GetFieldId() == NULL");
	return fid;
}


//  read value of 'public int field_name'
int JavaInterfaceCommon::get_java_field_int(JavaJNIObjectClass obj, const char *field_name) {
        jfieldID fid = get_field_id(obj, field_name, "I");
  	return jni_entry.GetJniEnv()->GetIntField(obj.GetObject(), fid);
}

//  read value of 'public double field_name'
double JavaInterfaceCommon::get_java_field_double(JavaJNIObjectClass obj, const char *field_name) {
        jfieldID fid = get_field_id(obj, field_name, "D");
  	return jni_entry.GetJniEnv()->GetDoubleField(obj.GetObject(), fid);
}

//  read value of 'public AnyClass field_name'
jobject JavaInterfaceCommon::get_java_field_jobject(JavaJNIObjectClass obj, const char *field_name, const char *field_sig) {
        jfieldID fid = get_field_id(obj, field_name, field_sig);
  	return jni_entry.GetJniEnv()->GetObjectField(obj.GetObject(), fid);
}

//  read value of 'public string field_name'
std::string JavaInterfaceCommon::get_java_field_string(JavaJNIObjectClass obj, const char *field_name) {
        jfieldID fid = get_field_id(obj, field_name, "Ljava/lang/String;");
	jstring jstr = (jstring) jni_entry.GetJniEnv()->GetObjectField(obj.GetObject(), fid);
	const char *str = (jstr == 0) ? 0 : jni_entry.GetJniEnv()->GetStringUTFChars(jstr, 0);
	if (str == NULL ) 
		return "";
	else
		return std::string(str);
}


JavaAccessException::JavaAccessException(const char *class_id, const char * field_id, const char * reason1, const char *reason2) {
	descr = "\n class id : ";
	descr.append(class_id);
	descr = "\n field id : ";
	descr.append(class_id);
	descr = "info : ";
	descr.append(reason1);
	descr.append(" ");
	descr.append(reason2);
};


}

