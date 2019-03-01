#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <jni.h>

#include <hunspell/hunspell.h>
#include "io_github_hunspell_Hunspell.h"

/*
 * Convenience function to retrieve the java handle from an object.
 *
 * Input:
 *   env               Java VM environment
 *   obj               Java object for which handle is to be retrieved
 *   nativeFieldId     if non-null, contains the nativeHandle field ID. 0 to request retrieval.
 *
 * Output:
 *   nativeFieldId     if non-null, will contain field ID of the nativeHandle on output.
 */
void *getHandle(JNIEnv *env,
		jobject obj,
		jfieldID *nativeFieldId)
{
	jobject nativeHandleObj;
	jclass nativeHandleObjClass;
	jclass objClass;
	jfieldID nativeHandleFid;
	jfieldID handleFid;
	
	/* Retrieve the field ID of the nativeHandle */
	if (nativeFieldId == NULL) {
		objClass = (*env)->GetObjectClass(env, obj);
		if (objClass == 0) {
			return NULL;
		}
		nativeHandleFid = (*env)->GetFieldID(env, objClass, "nativeHandle", "Lio/github/hunspell/Hunspell$NativeHandle;");
	} else if (*nativeFieldId == 0) {
		objClass = (*env)->GetObjectClass(env, obj);
		if (objClass == 0) {
			return NULL;
		}
		nativeHandleFid = *nativeFieldId = (*env)->GetFieldID(env, objClass, "nativeHandle", "Lio/github/hunspell/Hunspell$NativeHandle;");
	} else {
		nativeHandleFid = *nativeFieldId;
	}

	nativeHandleObj = (*env)->GetObjectField(env, obj, nativeHandleFid);

	/* Retrieve the field ID of the handle */
	nativeHandleObjClass = (*env)->GetObjectClass(env, nativeHandleObj);
	if (nativeHandleObjClass == 0) {
		return NULL;
	}
	handleFid = (*env)->GetFieldID(env, nativeHandleObjClass, "handle", "J");

	return (void*) (*env)->GetLongField(env, nativeHandleObj, handleFid);
}

/*
 * Convenience function to set the java handle in an object.
 *
 * Input:
 *   env               Java VM environment
 *   obj               Java object for which handle is to be retrieved
 *   handle            the handle value to set
 *   nativeFieldId     if non-null, contains the nativeHandle field ID. 0 to request retrieval.
 *
 * Output:
 *   nativeFieldId     if non-null, will contain field ID of the nativeHandle on output.
 *
 * Return:
 *   non-zero          if successful
 *   zero              if failure
 */
int setHandle(JNIEnv *env,
		jobject obj,
		void *handle,
		jfieldID *nativeHandleFieldId)
{
	jobject nativeHandleObj;
	jclass nativeHandleObjClass;
	jclass objClass;
	jfieldID nativeHandleFid;
	jmethodID setHandleMethodID;

	/* Retrieve the field ID of the handle */
	if (nativeHandleFieldId == NULL) {
		objClass = (*env)->GetObjectClass(env, obj);
		if (objClass == 0) {
			return 0;
		}
		nativeHandleFid = (*env)->GetFieldID(env, objClass, "nativeHandle", "Lio/github/hunspell/Hunspell$NativeHandle;");
	} else if (*nativeHandleFieldId == 0) {
		objClass = (*env)->GetObjectClass(env, obj);
		if (objClass == 0) {
			return 0;
		}
		nativeHandleFid = *nativeHandleFieldId = (*env)->GetFieldID(env, objClass, "nativeHandle", "Lio/github/hunspell/Hunspell$NativeHandle;");
	} else {
		nativeHandleFid = *nativeHandleFieldId;
	}

	if (nativeHandleFid == 0) {
		return 0;
	}
	
	nativeHandleObj = (*env)->GetObjectField(env, obj, nativeHandleFid);

	/* Retrieve the method ID of the setHandle(long handle) method */
	nativeHandleObjClass = (*env)->GetObjectClass(env, nativeHandleObj);
	if (nativeHandleObjClass == 0) {
		return 0;
	}
	setHandleMethodID = (*env)->GetMethodID(env, nativeHandleObjClass, "setHandle", "(J)V");

	if (setHandleMethodID == 0) {
		return 0;
	}

	(*env)->CallVoidMethod(env, nativeHandleObj, setHandleMethodID, (jlong) handle);

	return 1;
}

/*
 * Convenience function to help throw a RuntimeException.
 *
 * Input:
 *   message       error message
 */
void throwRuntimeException(JNIEnv* env, const char* message) {
	jclass runtimeExceptionClass;
	jmethodID consMethodID = 0;
	jobject newObj;
	jstring jmessage;
	int result;

	/* Find the class ID */
	runtimeExceptionClass = (*env)->FindClass( env, "java/lang/RuntimeException" );
	if ( runtimeExceptionClass == 0 ) {
		return;
	}

	/* Find the constructor ID */
	consMethodID = (*env)->GetMethodID( env, runtimeExceptionClass, "<init>", "(Ljava/lang/String;)V" );
	if ( consMethodID == 0 ) {
		return;
	}

	/* Obtain the string objects */
	jmessage = (*env)->NewStringUTF( env, message );
	if ( jmessage == NULL ) {
		return;
	}

	/* Create the RuntimeException object */
	newObj = (*env)->NewObject( env, runtimeExceptionClass, consMethodID, jmessage );
	if ( newObj == NULL ) {
		return;
	}

	/* Throw the exception. */
	result = (*env)->Throw( env, newObj );
}

/*
 * Convenience function to help throw a IllegalArgumentException.
 *
 * Input:
 *   message       error message
 */
void throwIllegalArgumentException(JNIEnv* env, const char* message) {
	jclass illegalArgumentExceptionClass;
	jmethodID consMethodID = 0;
	jobject newObj;
	jstring jmessage;
	int result;

	/* Find the class ID */
	illegalArgumentExceptionClass = (*env)->FindClass( env, "java/lang/IllegalArgumentException" );
	if ( illegalArgumentExceptionClass == 0 ) {
		return;
	}

	/* Find the constructor ID */
	consMethodID = (*env)->GetMethodID( env, illegalArgumentExceptionClass, "<init>", "(Ljava/lang/String;)V" );
	if ( consMethodID == 0 ) {
		return;
	}

	/* Obtain the string objects */
	jmessage = (*env)->NewStringUTF( env, message );
	if ( jmessage == NULL ) {
		return;
	}

	/* Create the IllegalArgumentException object */
	newObj = (*env)->NewObject( env, illegalArgumentExceptionClass, consMethodID, jmessage );
	if ( newObj == NULL ) {
		return;
	}

	/* Throw the exception. */
	result = (*env)->Throw( env, newObj );
}


JNIEXPORT jobject JNICALL Java_io_github_hunspell_Hunspell_openDictionary(JNIEnv *env, jclass cls, jstring jbasepath) {
	jmethodID jmid;
	jobject jobj = NULL;
	Hunhandle* pMS = NULL;
	char* aff;
	char* dic;

	const char* basepath =  (*env)->GetStringUTFChars( env, jbasepath, 0 );
	aff = (char*) malloc( strlen( basepath ) + 5 );
	strcpy( aff, basepath );
	strcat( aff, ".aff" );

	dic = (char*) malloc( strlen( basepath ) + 5 );
	strcpy( dic, basepath );
	strcat( dic, ".dic" );
	if ( aff && dic ) {
		pMS = Hunspell_create( aff, dic );
		if ( pMS == NULL ) {
			free( aff );
			free( dic );
			(*env)->ReleaseStringUTFChars( env, jbasepath, basepath );
			throwIllegalArgumentException( env, "Could not initialize the dictionary requested" );
			return NULL;
		}

		jmid = (*env)->GetMethodID( env, cls, "<init>", "()V" );
		if ( jmid == NULL ) {
			Hunspell_destroy( pMS );
			free( aff );
			free( dic );
			(*env)->ReleaseStringUTFChars( env, jbasepath, basepath );
			throwRuntimeException( env, "Could not find the Hunspell class constructor" );
			return NULL;
		}

		jobj = (*env)->NewObject( env, cls, jmid );
		if ( jobj == NULL ) {
			Hunspell_destroy( pMS );
			free( aff );
			free( dic );
			(*env)->ReleaseStringUTFChars( env, jbasepath, basepath );
			throwRuntimeException( env, "Could not create a new Hunspell instance" );
			return NULL;
		}

		if ( !setHandle( env, jobj, (void*) pMS, NULL ) ) {
			Hunspell_destroy( pMS );
			free( aff );
			free( dic );
			(*env)->ReleaseStringUTFChars( env, jbasepath, basepath );
			throwRuntimeException( env, "Could not set handle for new Hunspell instance" );
			return NULL;
		}
	}

	if ( aff ) {
		free( aff );
	}

	if ( dic ) {
		free( dic );
	}

	(*env)->ReleaseStringUTFChars( env, jbasepath, basepath );

	return jobj;
}

JNIEXPORT jboolean JNICALL Java_io_github_hunspell_Hunspell_checkWord(JNIEnv *env, jobject self, jstring jword) {
	Hunhandle* pMS;
	int dp = 0;

	pMS = getHandle( env, self, NULL );
	if ( pMS != NULL ) {
		const char* word = (*env)->GetStringUTFChars( env, jword, 0 );
		dp = Hunspell_spell( pMS, word );
		(*env)->ReleaseStringUTFChars( env, jword, word );
	} else {
		throwRuntimeException( env, "Could not find Hunhandle pointer" );
		return 0;
	}

	return dp != 0 ? JNI_TRUE : JNI_FALSE;
}

JNIEXPORT jobject JNICALL Java_io_github_hunspell_Hunspell_getSuggestions(JNIEnv *env, jobject self, jstring jword) {
	jclass jcls;
	jmethodID jmid;
	jobject jobj = NULL;
	Hunhandle* pMS = NULL;
	int dp;

	pMS = getHandle( env, self, NULL );
	if ( pMS != NULL ) {
		jcls = (*env)->FindClass( env, "java/util/HashSet" );
		if ( jcls == NULL ) {
			throwRuntimeException( env, "Could not find the HashSet class" );
			return NULL;
		}

		jmid = (*env)->GetMethodID( env, jcls, "<init>", "()V" );
		if ( jmid == NULL ) {
			throwRuntimeException( env, "Could not find the HashSet class constructor" );
			return NULL;
		}

		jobj = (*env)->NewObject( env, jcls, jmid );
		if ( jobj == NULL )
		{
			throwRuntimeException( env, "Could not create a new HashSet instance" );
			return NULL;
		}

		jmid = (*env)->GetMethodID( env, jcls, "add", "(Ljava/lang/Object;)Z" );
		if ( jmid == NULL ) {
			throwRuntimeException( env, "Could not find the HashSet.add(Object) method" );
			return NULL;
		}
		const char* word = (*env)->GetStringUTFChars( env, jword, 0 );

		dp = Hunspell_spell( pMS, word );
		if ( !dp ) {
			char** suggestionList;
			int numberOfSuggestions = Hunspell_suggest( pMS, &suggestionList, word );
			for ( int i = 0; i < numberOfSuggestions; i++ ) {
				(*env)->CallBooleanMethod( env, jobj, jmid, (*env)->NewStringUTF( env, suggestionList[i] ) );
			}
			Hunspell_free_list( pMS, &suggestionList, numberOfSuggestions );
		}

		(*env)->ReleaseStringUTFChars( env, jword, word );
	} else {
		throwRuntimeException( env, "Could not find Hunhandle pointer" );
		return NULL;
	}

	return jobj;
}

JNIEXPORT void JNICALL Java_io_github_hunspell_Hunspell_closeDictionary(JNIEnv *env, jclass class, jlong handle) {
	Hunhandle* pMS = (Hunhandle*) handle;
	if ( pMS != NULL ) {
		Hunspell_destroy( pMS );
	}

	return;
}
