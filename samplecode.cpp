jint lResult;

jint lFlags = 0;

JavaVM* lJavaVM = MyNativeHelper::getJavaVM();    //<---- replace this with your NativeActivity pointer

JNIEnv *lJNIEnv = 0;

lResult=lJavaVM->AttachCurrentThread(&lJNIEnv,NULL);

if (lResult == JNI_ERR) {

    return;

}

jobject lNativeActivity = MyNativeHelper::getClassName();

jclass ClassNativeActivity = lJNIEnv->FindClass("android/app/NativeActivity");

jclass contextClass = lJNIEnv->FindClass("android/content/Context");

if(contextClass == 0)

    return;

jmethodID startActivityMethodId = lJNIEnv->GetMethodID(contextClass, "startActivity", "(Landroid/content/Intent;)V");

if(startActivityMethodId == 0)

    return;

jclass intentClass = lJNIEnv->FindClass("android/content/Intent");

if(intentClass == 0)

    return;

jmethodID intentConstructorMethodId = lJNIEnv->GetMethodID(intentClass, "<init>", "()V");

if(intentConstructorMethodId == 0)

    return;

jmethodID intentSetActionMethodId = lJNIEnv->GetMethodID(intentClass, "setAction", "(Ljava/lang/String;)Landroid/content/Intent;");

if(intentSetActionMethodId == 0)

    return;

jmethodID getClassLoader = lJNIEnv->GetMethodID(ClassNativeActivity,"getClassLoader", "()Ljava/lang/ClassLoader;");

if(getClassLoader == 0)

    return;

jobject cls = lJNIEnv->CallObjectMethod(lNativeActivity, getClassLoader);

if(cls == 0)

    return;

jclass classLoader = lJNIEnv->FindClass("java/lang/ClassLoader");

if(classLoader == 0)

    return;

jmethodID findClass = lJNIEnv->GetMethodID(classLoader, "loadClass", "(Ljava/lang/String;)Ljava/lang/Class;");

if(findClass == 0)

    return;

jstring intentString = lJNIEnv->NewStringUTF("mypackage.myactivity");

if(intentString == 0)

    return;

jclass marketActivityClass = (jclass)lJNIEnv->CallObjectMethod(cls, findClass, intentString);

if(marketActivityClass == 0)

    return;

//jobject intentObject = lJNIEnv->NewObject(intentClass,intentConstructorMethodId);
	
Jobject intentObject = lJNIEnv->AllocObject(intentClass);
	
lJNIEnv->CallVoidMethod(intentObject, intentConstructorMethodId);

if(intentObject == 0)

    return;

lJNIEnv->CallVoidMethod(intentObject, intentSetActionMethodId, intentString);

lJNIEnv->CallVoidMethod(lNativeActivity, startActivityMethodId, intentObject);
	
lJavaVM->DetachCurrentThread();
