#include <jni.h>
#include <string>
                                    //java_applicationPackage_className_declaredMethodintotheActivity
extern "C" JNIEXPORT jstring JNICALL Java_com_example_jnifirstapplication_MainActivity_stringFromJNI(
        JNIEnv* env, jobject /* this */) {
    std::string hello = "Hello Your Addition :";
    return env->NewStringUTF(hello.c_str());
}

// Creating Our Own method (here mainActivityInstance is a parameter of the jobject type)
extern "C" JNIEXPORT jstring JNICALL Java_com_example_jnifirstapplication_MainActivity_process(
        JNIEnv* env, jobject mainActivityInstance/* this */) {

    const jclass mainActivitycls = env->GetObjectClass(mainActivityInstance);
                               // methodId(class name, Method Name, return type of the method)
    const jmethodID jmethodId = env->GetMethodID(mainActivitycls, "processInJava", "()Ljava/lang/String;");

    // returning the value
    if (jmethodId == nullptr)
    {
        return env->NewStringUTF("");
    }

    // calling the method
    const jobject result = env->CallObjectMethod(mainActivityInstance, jmethodId);

    // converting jobject into the string type
    const std::string java_msg = env->GetStringUTFChars((jstring) result, JNI_FALSE);
    // now showing the message into the c
    const std::string c_msg = "Result from java=>";
    //concatinating to the both
    const std::string msg = c_msg + java_msg;
    // returning concatinated value(string)
    return env->NewStringUTF(msg.c_str());
}

// Addition
extern "C" JNIEXPORT jint JNICALL Java_com_example_jnifirstapplication_MainActivity_additionNum(JNIEnv* env, jobject maintActivityInstance, jint num1, jint num2){

    // accessing her the mainActivity class
    //const jclass mactivityclass = env->GetObjectClass(maintActivityInstance);

    jint result = num1 + num2;

   return result;

}

extern "C" JNIEXPORT jint JNICALL Java_com_example_jnifirstapplication_MainActivity_subtraction(JNIEnv* env, jobject maintActivityInstance, jint num1, jint num2){

    jint result = num1 - num2;

    return result;
}


extern "C" JNIEXPORT jint JNICALL Java_com_example_jnifirstapplication_MainActivity_arraySum(JNIEnv *env, jobject mainActivityInstance, jintArray array) {
    jint *arr = env->GetIntArrayElements(array, nullptr);
    jint len = env->GetArrayLength(array);

    int sum = 0;
    for (int i = 0; i < len; ++i) {
        sum += arr[i];
    }

    env->ReleaseIntArrayElements(array, arr, NULL);

    return sum;
}

extern "C" JNIEXPORT jstring JNICALL Java_com_example_jnifirstapplication_MainActivity_concatenateString(JNIEnv *env, jobject mainActivityInstance, jstring str1, jstring str2) {
    const char *nativeStr1 = env->GetStringUTFChars(str1, nullptr);
    const char *nativeStr2 = env->GetStringUTFChars(str2, nullptr);

    // Concatenate the strings
    std::string resultStr = std::string(nativeStr1) + std::string(nativeStr2);

    // Release the allocated memory
    env->ReleaseStringUTFChars(str1, nativeStr1);
    env->ReleaseStringUTFChars(str2, nativeStr2);

    // Return the concatenated string as a new Java string
    return env->NewStringUTF(resultStr.c_str());
}

extern "C" JNIEXPORT jint JNICALL Java_com_example_jnifirstapplication_MainActivity_getRandomNumber(JNIEnv *env, jobject mainActivityInstance){

    jint num = rand();
    return num;
}

extern "C" JNIEXPORT jobject JNICALL Java_com_example_jnifirstapplication_MainActivity_createStudent(JNIEnv *env, jobject obj) {
    // Obtain the class references
    jclass studentClass = env->FindClass("com/example/jnifirstapplication/Student");
    jclass marksClass = env->FindClass("com/example/jnifirstapplication/Marks");

    // Get the method IDs
    jmethodID studentConstructor = env->GetMethodID(studentClass, "<init>",
                                                    "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;ILjava/util/List;)V");
    jmethodID marksConstructor = env->GetMethodID(marksClass, "<init>", "(Ljava/lang/String;I)V");

    // Create instances of the classes
    jstring fname = env->NewStringUTF("Ravikumar");
    jstring lname = env->NewStringUTF("Pathak");
    jstring phoneNo = env->NewStringUTF("1234567890");
    jstring address = env->NewStringUTF("Ahmedabad");
    jint rollNo = 12345;

    // Create a List to hold Marks objects
    jclass arrayListClass = env->FindClass("java/util/ArrayList");
    jmethodID arrayListConstructor = env->GetMethodID(arrayListClass, "<init>", "()V");
    jmethodID arrayListAdd = env->GetMethodID(arrayListClass, "add", "(Ljava/lang/Object;)Z");
    jobject marksList = env->NewObject(arrayListClass, arrayListConstructor);

    // Create a Marks object and add it to the list
    jstring subjectFirst = env->NewStringUTF("Math");
    jint marksValue = 95;
    jobject marksObject = env->NewObject(marksClass, marksConstructor, subjectFirst, marksValue);
    env->CallBooleanMethod(marksList, arrayListAdd, marksObject);

    // Create a Marks object and add it to the list
    jstring subjectSecond = env->NewStringUTF("Science");
    jint marksValueSecond = 98;
    jobject marksObjectSecond = env->NewObject(marksClass, marksConstructor, subjectSecond, marksValueSecond);
    env->CallBooleanMethod(marksList, arrayListAdd, marksObjectSecond);

    // Release local references
    env->DeleteLocalRef(subjectFirst);
    env->DeleteLocalRef(marksObject);
    env->DeleteLocalRef(subjectSecond);
    env->DeleteLocalRef(marksObjectSecond);

    // Create the Student object with the List of Marks
    jobject studentObject = env->NewObject(studentClass, studentConstructor, fname, lname, phoneNo, address, rollNo, marksList);

    // Clean up local references
    env->DeleteLocalRef(fname);
    env->DeleteLocalRef(lname);
    env->DeleteLocalRef(phoneNo);
    env->DeleteLocalRef(address);
    env->DeleteLocalRef(marksList);

    // Return the studentObject
    return studentObject;
}


#include <jni.h>

extern "C" JNIEXPORT jobject JNICALL Java_com_example_jnifirstapplication_MainActivity_getStudentDetails(JNIEnv *env, jobject obj, jobject student) {
    // Assuming Student class has getters for fname, lname, phoneNo, address, and rollNo
    // Assuming Marks class has getters for subject and score

    // Get the class references
    jclass studentClass = env->GetObjectClass(student);
    jclass marksClass = env->FindClass("com/example/jnifirstapplication/Marks");

    // Get the method IDs for getters in Student class
    jmethodID getFname = env->GetMethodID(studentClass, "getFname", "()Ljava/lang/String;");
    jmethodID getLname = env->GetMethodID(studentClass, "getLname", "()Ljava/lang/String;");
    jmethodID getPhoneNo = env->GetMethodID(studentClass, "getPhoneNo", "()Ljava/lang/String;");
    jmethodID getAddress = env->GetMethodID(studentClass, "getAddress", "()Ljava/lang/String;");
    jmethodID getRollNo = env->GetMethodID(studentClass, "getRollNo", "()I");

    // Get the method IDs for getters in Marks class
    jmethodID getSubject = env->GetMethodID(marksClass, "getSubjectName", "()Ljava/lang/String;");
    jmethodID getScore = env->GetMethodID(marksClass, "getSubjectMark", "()I");

    // Call the getters to retrieve the details
    jstring fname = (jstring) env->CallObjectMethod(student, getFname);
    jstring lname = (jstring) env->CallObjectMethod(student, getLname);
    jstring phoneNo = (jstring) env->CallObjectMethod(student, getPhoneNo);
    jstring address = (jstring) env->CallObjectMethod(student, getAddress);
    jint rollNo = env->CallIntMethod(student, getRollNo);

    // Create a new List to hold Marks objects
    jclass listClass = env->FindClass("java/util/ArrayList");
    jmethodID listConstructor = env->GetMethodID(listClass, "<init>", "()V");
    jmethodID listAdd = env->GetMethodID(listClass, "add", "(Ljava/lang/Object;)Z");
    jobject marksListNew = env->NewObject(listClass, listConstructor);

    // Get the size of the list
    jmethodID sizeMethod = env->GetMethodID(listClass, "size", "()I");
    jint size = env->CallIntMethod(marksListNew, sizeMethod);

    // Iterate through the existing list of marks and create new Marks objects
    for (jint i = 0; i < size; i++) {
        // Get the Marks object from the list
        jobject marksObject = env->CallObjectMethod(marksListNew, env->GetMethodID(listClass, "get", "(I)Ljava/lang/Object;"), i);

        // Call the getters to retrieve the details of the Marks object
        jstring subject = (jstring) env->CallObjectMethod(marksObject, getSubject);
        jint score = env->CallIntMethod(marksObject, getScore);

        // Create a new Marks object with the retrieved details
        jobject marksNew = env->NewObject(marksClass, env->GetMethodID(marksClass, "<init>", "(Ljava/lang/String;I)V"), subject, score);

        // Add the new Marks object to the list
        env->CallBooleanMethod(marksListNew, listAdd, marksNew);

        // Clean up local references
        env->DeleteLocalRef(subject);
        env->DeleteLocalRef(marksObject);
        env->DeleteLocalRef(marksNew);
    }

    // Create a new Student object with the retrieved details and list of Marks
    jclass studentClassNew = env->FindClass("com/example/jnifirstapplication/Student");
    jmethodID constructor = env->GetMethodID(studentClassNew, "<init>", "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;ILjava/util/List;)V");

    jobject studentNew = env->NewObject(studentClassNew, constructor, fname, lname, phoneNo, address, rollNo, marksListNew);

    // Clean up local references
    env->DeleteLocalRef(fname);
    env->DeleteLocalRef(lname);
    env->DeleteLocalRef(phoneNo);
    env->DeleteLocalRef(address);
    env->DeleteLocalRef(marksListNew);

    // Return the new Student object
    return studentNew;
}

extern "C" JNIEXPORT jobject JNICALL Java_com_example_jnifirstapplication_MainActivity_calculateResult(JNIEnv *env, jobject obj, jstring firstName, jint rollNo, jstring phoneNo, jobject marksList) {
    jclass resultClass = env->FindClass("com/example/jnifirstapplication/Result");
    jmethodID resultConstructor = env->GetMethodID(resultClass, "<init>", "(Ljava/lang/String;ILjava/lang/String;ZD)V");

    // Convert Java strings to C strings
    const char *firstNameStr = env->GetStringUTFChars(firstName, NULL);
    const char *phoneNoStr = env->GetStringUTFChars(phoneNo, NULL);

    // Iterate through the list of marks and calculate the percentage
    jclass listClass = env->FindClass("java/util/List");
    jmethodID listSize = env->GetMethodID(listClass, "size", "()I");
    jmethodID listGet = env->GetMethodID(listClass, "get", "(I)Ljava/lang/Object;");

    jint size = env->CallIntMethod(marksList, listSize);
    jint passCount = 0;

    for (jint i = 0; i < size; i++) {
        jobject marksObject = env->CallObjectMethod(marksList, listGet, i);
        jclass marksClass = env->GetObjectClass(marksObject);

        jmethodID getScore = env->GetMethodID(marksClass, "getSubjectMark", "()I");
        jint score = env->CallIntMethod(marksObject, getScore);

        if (score >= 40) {
            passCount++;
        }

        env->DeleteLocalRef(marksObject);
    }

    // Calculate the pass/fail percentage
    double percentage = (passCount / static_cast<double>(size)) * 100;
    bool pass = percentage >= 40;

    // Create the Result object
    jobject result = env->NewObject(resultClass, resultConstructor, env->NewStringUTF(firstNameStr), rollNo, env->NewStringUTF(phoneNoStr), pass, percentage);

    // Release the allocated resources
    env->ReleaseStringUTFChars(firstName, firstNameStr);
    env->ReleaseStringUTFChars(phoneNo, phoneNoStr);

    return result;
}

#include <jni.h>

extern "C" JNIEXPORT jint JNICALL Java_com_example_jnifirstapplication_MainActivity_getEnumStudentValue(JNIEnv *env, jobject obj, jobject enumObject) {
    jclass enumClass = env->GetObjectClass(enumObject);
    jmethodID getValueMethod = env->GetMethodID(enumClass, "getValue", "()I");
    jint value = env->CallIntMethod(enumObject, getValueMethod);
    return value;
}


#include <jni.h>
#include <string>
#include <vector>

extern "C" JNIEXPORT jstring JNICALL Java_com_example_jnifirstapplication_MainActivity_sendStudents(JNIEnv *env, jobject obj, jobject studentsList) {
    // Obtain the class references
    jclass arrayListClass = env->GetObjectClass(studentsList);
    jmethodID sizeMethod = env->GetMethodID(arrayListClass, "size", "()I");
    jmethodID getMethod = env->GetMethodID(arrayListClass, "get", "(I)Ljava/lang/Object;");

    // Get the size of the ArrayList
    jint size = env->CallIntMethod(studentsList, sizeMethod);

    // Iterate through the ArrayList and retrieve student names
    std::vector<std::string> studentNameList;

    for (int i = 0; i < size; i++) {
        // Get the Student object from the ArrayList
        jobject studentObject = env->CallObjectMethod(studentsList, getMethod, i);
        jclass studentClass = env->GetObjectClass(studentObject);

        // Assuming Student class has getName() method
        jmethodID getNameMethod = env->GetMethodID(studentClass, "getFname", "()Ljava/lang/String;");

        // Get student name
        jstring name = (jstring) env->CallObjectMethod(studentObject, getNameMethod);

        // Convert Java strings to C++ strings
        const char* nameStr = env->GetStringUTFChars(name, NULL);

        // Process student information (for demonstration, just add to a vector)
        std::string studentName = std::string(nameStr);
        studentNameList.push_back(studentName);

        // Release local references
        env->ReleaseStringUTFChars(name, nameStr);
        env->DeleteLocalRef(name);
        env->DeleteLocalRef(studentObject);
    }

    // Process the student name vector (for demonstration, just concatenate)
    std::string result;
    for (const auto& studentName : studentNameList) {
        result += studentName + "\n";
    }

    // Return the result as a Java string
    return env->NewStringUTF(result.c_str());
}

#include <jni.h>
#include <string>

extern "C" JNIEXPORT jboolean JNICALL Java_com_example_jnifirstapplication_MainActivity_basicTypes(JNIEnv *env, jobject instance,
                                                                                        jint anInt, jlong aLong, jboolean aBoolean,
                                                                                        jfloat aFloat, jdouble aDouble,
                                                                                        jstring aString) {

    // Validate the data types
    jclass integerClass = env->FindClass("java/lang/Integer");
    jclass longClass = env->FindClass("java/lang/Long");
    jclass booleanClass = env->FindClass("java/lang/Boolean");
    jclass floatClass = env->FindClass("java/lang/Float");
    jclass doubleClass = env->FindClass("java/lang/Double");
    jclass stringClass = env->FindClass("java/lang/String");

    jboolean isInt = (env->IsInstanceOf(instance, integerClass) == JNI_TRUE);
    jboolean isLong = (env->IsInstanceOf(instance, longClass) == JNI_TRUE);
    jboolean isBoolean = (env->IsInstanceOf(instance, booleanClass) == JNI_TRUE);
    jboolean isFloat = (env->IsInstanceOf(instance, floatClass) == JNI_TRUE);
    jboolean isDouble = (env->IsInstanceOf(instance, doubleClass) == JNI_TRUE);
    jboolean isString = (env->IsInstanceOf(instance, stringClass) == JNI_TRUE);

    // Validate the data here as per your requirements
    if (isInt && isLong && isBoolean && isFloat && isDouble && isString) {
        // Your additional validation logic can go here
        return JNI_TRUE;
    } else {
        return JNI_FALSE;
    }

    // Release the allocated resources (not reached in this code, just added for completeness)
    env->ReleaseStringUTFChars(aString, env->GetStringUTFChars(aString, 0));

    return JNI_FALSE;
}


#include <jni.h>

//extern "C" JNIEXPORT jobject JNICALL Java_com_example_jnifirstapplication_Student_createStudentFromBundle(JNIEnv *env, jclass clazz, jobject bundleObj) {
//    // Get method and field IDs
//    jmethodID getStringMethod = env->GetMethodID(env->FindClass("android/os/Bundle"), "getString", "(Ljava/lang/String;)Ljava/lang/String;");
//    jmethodID getIntMethod = env->GetMethodID(env->FindClass("android/os/Bundle"), "getInt", "(Ljava/lang/String;)I");
//    jmethodID getSerializableMethod = env->GetMethodID(env->FindClass("android/os/Bundle"), "getSerializable", "(Ljava/lang/String;)Ljava/io/Serializable;");
//
//    jfieldID fid_fname = env->GetFieldID(clazz, "fname", "Ljava/lang/String;");
//    jfieldID fid_lname = env->GetFieldID(clazz, "lname", "Ljava/lang/String;");
//    jfieldID fid_rollno = env->GetFieldID(clazz, "rollNo", "I");
//    jfieldID fid_phoneNumber = env->GetFieldID(clazz, "phoneNo", "Ljava/lang/String;");
//    jfieldID fid_address = env->GetFieldID(clazz, "address", "Ljava/lang/String;");
//    jfieldID fid_marks = env->GetFieldID(clazz, "marks", "Ljava/util/List;");
//
//    // Extract values from Bundle
//    jstring fname = (jstring)env->CallObjectMethod(bundleObj, getStringMethod, env->NewStringUTF("fname"));
//    jstring lname = (jstring)env->CallObjectMethod(bundleObj, getStringMethod, env->NewStringUTF("lname"));
//    jint rollno = env->CallIntMethod(bundleObj, getIntMethod, env->NewStringUTF("rollno"));
//    jstring phoneNumber = (jstring)env->CallObjectMethod(bundleObj, getStringMethod, env->NewStringUTF("phoneNumber"));
//    jstring address = (jstring)env->CallObjectMethod(bundleObj, getStringMethod, env->NewStringUTF("address"));
//    jobject marksSerializable = env->CallObjectMethod(bundleObj, getSerializableMethod, env->NewStringUTF("marks"));
//
//    // Cast Serializable to List
//    jclass arrayListClass = env->FindClass("java/util/ArrayList");
//    jmethodID listCtor = env->GetMethodID(arrayListClass, "<init>", "()V");
//    jobject marksList = env->NewObject(arrayListClass, listCtor);
//    jmethodID addMethod = env->GetMethodID(arrayListClass, "add", "(Ljava/lang/Object;)Z");
//    env->CallBooleanMethod(marksList, addMethod, marksSerializable);
//
//    // Create Student object
//    jclass studentClass = env->FindClass("com/example/jnifirstapplication/Student");
//    jobject studentObj = env->AllocObject(studentClass);
//
//    // Set fields in Student object
//    env->SetObjectField(studentObj, fid_fname, fname);
//    env->SetObjectField(studentObj, fid_lname, lname);
//    env->SetIntField(studentObj, fid_rollno, rollno);
//    env->SetObjectField(studentObj, fid_phoneNumber, phoneNumber);
//    env->SetObjectField(studentObj, fid_address, address);
//    env->SetObjectField(studentObj, fid_marks, marksList);
//
//    // Release resources
//    env->DeleteLocalRef(fname);
//    env->DeleteLocalRef(lname);
//    env->DeleteLocalRef(phoneNumber);
//    env->DeleteLocalRef(address);
//    env->DeleteLocalRef(marksSerializable);
//    env->DeleteLocalRef(marksList);
//
//    return studentObj;
//}

#include <jni.h>
#include <string>
#include <vector>

extern "C" JNIEXPORT jobject JNICALL
Java_com_example_jnifirstapplication_Student_createStudentFromBundle(JNIEnv *env, jclass clazz, jobject bundleObj) {
    // Get method IDs for accessing Bundle class methods
    jclass bundleClass = env->GetObjectClass(bundleObj);
    jmethodID getStringMethod = env->GetMethodID(bundleClass, "getString", "(Ljava/lang/String;)Ljava/lang/String;");
    jmethodID getIntMethod = env->GetMethodID(bundleClass, "getInt", "(Ljava/lang/String;)I");

    // Extract data from Bundle
    jstring fnameString = static_cast<jstring>(env->CallObjectMethod(bundleObj, getStringMethod, env->NewStringUTF("fname")));
    jstring lnameString = static_cast<jstring>(env->CallObjectMethod(bundleObj, getStringMethod, env->NewStringUTF("lname")));
    jstring phoneNoString = static_cast<jstring>(env->CallObjectMethod(bundleObj, getStringMethod, env->NewStringUTF("phoneNo")));
    jstring addressString = static_cast<jstring>(env->CallObjectMethod(bundleObj, getStringMethod, env->NewStringUTF("address")));
    jint rollNo = env->CallIntMethod(bundleObj, getIntMethod, env->NewStringUTF("rollNo"));

    // Create Student object
    jclass studentClass = env->FindClass("com/example/jnifirstapplication/Student");
    jmethodID studentConstructor = env->GetMethodID(studentClass, "<init>", "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;ILjava/util/List;)V");

    // Create marks list (assuming you have a method to create it)
    jclass arrayListClass = env->FindClass("java/util/ArrayList");
    jmethodID arrayListConstructor = env->GetMethodID(arrayListClass, "<init>", "()V");
    jmethodID arrayListAddMethod = env->GetMethodID(arrayListClass, "add", "(Ljava/lang/Object;)Z");

    jobject marksList = env->NewObject(arrayListClass, arrayListConstructor);

    // Create Student object
    jobject studentObj = env->NewObject(studentClass, studentConstructor, fnameString, lnameString, phoneNoString, addressString, rollNo, marksList);

    // Release local references
    env->DeleteLocalRef(fnameString);
    env->DeleteLocalRef(lnameString);
    env->DeleteLocalRef(phoneNoString);
    env->DeleteLocalRef(addressString);

    return studentObj;
}




