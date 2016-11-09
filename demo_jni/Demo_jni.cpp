#include <iostream>
#include <time.h>

#include <core/PositionProcessor.h>
#include <core/simulation.h>

#include "com_gridgainec2_DemoManagerJni.h"
#include "JavaInterface.h"


void runMonteCarlo(JNIEnv *jni_env, jobject java_this, jobjectArray position_array, jint horizon, jint iters);


extern "C" {
//public native void runMonteCarlo(Position[] array, int horizon, int iters);

JNIEXPORT void JNICALL Java_com_gridgainec2_DemoManagerJni_runMonteCarlo
  (JNIEnv *jni_env, jobject java_this, jobjectArray position_array, jint horizon, jint iters) {
// return something from 1 onto 100
	runMonteCarlo(jni_env, java_this, position_array, horizon, iters);
};
}  // extern "C"




////public native int runMonteCarlo(Position[] array, int horizon, int iters);
void runMonteCarlo(JNIEnv *jni_env, jobject java_this, jobjectArray position_array, jint horizon, jint iters) {
try { 
	PositionJobData jobData;
	
	int size  = jni_env->GetArrayLength(position_array);


	JavaJNI::JavaJNIEntryData entry_data(jni_env, java_this, position_array, position_array);
	JavaJNI::JavaInterface::Convert(entry_data, jobData.GetPortfolioPtr());
	jobData.SetHorizon(horizon);
	jobData.SetIters(iters);

	runMonteCarlo(jobData);
	
	// save simulatedValues on to java
	JavaJNI::JavaInterface::UpdateJava(jobData.GetPortfolioPtr(), entry_data);




} catch (std::bad_alloc &mem )  {
	printf("Run time error ( bad_alloc ) : runMonteCarlo exception : %s\n", mem.what());
} catch (std::exception& exc) {
	printf("Run time error : runMonteCarlo exception : %s\n", exc.what());
} catch (...) {
	printf("Run time error : runMonteCarlo unknown exception\n");
};
}






