#include <jni.h>
#include <android/native_activity.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <stdint.h>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <sstream>
#include <vector>
#include <pthread.h>
#include <codecvt>
#include <chrono>
#include <unordered_map>
#include <vector>
#include <queue>
#include "ImGui/imgui_internal.h"
#include "ImGui/imgui.h"
#include "ImGui/backends/imgui_impl_android.h"
#include "ImGui/backends/imgui_impl_opengl3.h"
#include <EGL/egl.h>
#include <GLES3/gl3.h>
#include <android/asset_manager.h>
#include <android/asset_manager_jni.h>
#include <sys/system_properties.h>
#include <string>
#include "ImGui/FONTS/DEFAULT.h"
#include <Includes/Utils.h>
#include <Includes/Dobby/dobby.h>
#include "KittyMemory/MemoryPatch.h"

#include "ImGui/Verdana.h"

#include "Includes/Dobby/dobby.h"
#include "Includes/obfuscate.h"
#include "Includes/Utils.h"
#include "Includes/ByNameModding.h"
uintptr_t G_IL2CPP;
int screenWidth;
int screenHeight;
bool g_Initialized = false;
ImGuiWindow* g_window = NULL;
#include <Substrate/SubstrateHook.h>
#include <Substrate/CydiaSubstrate.h>
#include "Unity/Vector3.h"
#include "And64InlineHook/And64InlineHook.hpp"

#include "monostring.h"

#include <dlfcn.h>
#include <android/log.h>
#include <cmath>
#include <iostream>
#include "Includes/msg.h"
#include <dlfcn.h>
#include <string>

const char* MineLib = OBFUSCATE("libGLESv2.so");



bool show_window;
extern "C" {
    
    JNIEXPORT void JNICALL Java_com_mycompany_application_GLES3JNIView_init(JNIEnv* env, jclass cls);
    JNIEXPORT void JNICALL Java_com_mycompany_application_GLES3JNIView_resize(JNIEnv* env, jobject obj, jint width, jint height);
    JNIEXPORT void JNICALL Java_com_mycompany_application_GLES3JNIView_step(JNIEnv* env, jobject obj);
    JNIEXPORT void JNICALL Java_com_mycompany_application_GLES3JNIView_imgui_Shutdown(JNIEnv* env, jobject obj);
    JNIEXPORT void JNICALL Java_com_mycompany_application_GLES3JNIView_MotionEventClick(JNIEnv* env, jobject obj,jboolean down,jfloat PosX,jfloat PosY);
    JNIEXPORT jstring JNICALL Java_com_mycompany_application_GLES3JNIView_getWindowRect(JNIEnv *env, jobject thiz);
    JNIEXPORT void JNICALL Java_com_mycompany_application_GLES3JNIView_real(JNIEnv* env, jobject obj, jint width, jint height);
    
};




JNIEXPORT void JNICALL
Java_com_mycompany_application_GLES3JNIView_init(JNIEnv* env, jclass cls) {

    //SetUpImGuiContext
    if(!g_Initialized) {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    
    int screenWidth = io.DisplaySize.x;
    int screenHeight = io.DisplaySize.y;
  
    ImGui_ImplOpenGL3_Init("#version 100");
    ImGui::StyleColorsDark();
    ImGui::GetStyle().ScaleAllSizes(3.0f);
    
	

    g_Initialized = true;
    }
    return;
}

JNIEXPORT void JNICALL
Java_com_mycompany_application_GLES3JNIView_resize(JNIEnv* env, jobject obj, jint width, jint height) {
    if (g_Initialized) {
    screenWidth = (int) width;
    screenHeight = (int) height;
    ImGuiIO &io = ImGui::GetIO();
    io.IniFilename = NULL;
    ImGui::GetIO().DisplaySize = ImVec2((float)width, (float)height);
    }
    return;
}

    




void *hack_thread(void *) {
    
    do {
        sleep(1);
    } while (!isLibraryLoaded(libName));
	
    G_IL2CPP = findLibrary("libil2cpp.so");
    sleep(5);
    
    // Load Camera class
    // Don't Touch This Code );       
    
    return NULL;
}



JNIEXPORT void JNICALL
Java_com_mycompany_application_GLES3JNIView_step(JNIEnv* env, jobject obj) {
    if (g_Initialized) {
    ImGuiIO &io = ImGui::GetIO();
    
    ImGui_ImplOpenGL3_NewFrame();
    ImGui::NewFrame();
       
    
    ImVec2 windowSize = ImVec2(screenWidth * 0.30, screenHeight * 0.55);
    ImGui::SetNextWindowSize(windowSize, ImGuiCond_Once);
    

    ImGui::Begin("JAVA IMGUI [x32/64]");
        ImGui::Text("Counter Flame");
    
    


    ImGui::EndFrame();
    
    ImGui::Render();
    glClear(GL_COLOR_BUFFER_BIT);
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }
}

JNIEXPORT void JNICALL Java_com_mycompany_application_GLES3JNIView_imgui_Shutdown(JNIEnv* env, jobject obj){
    if (!g_Initialized)
        return;
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplAndroid_Shutdown();
    ImGui::DestroyContext();
    g_Initialized=false;
}

JNIEXPORT void JNICALL Java_com_mycompany_application_GLES3JNIView_MotionEventClick(JNIEnv* env, jobject obj,jboolean down,jfloat PosX,jfloat PosY){
    if (g_Initialized) {
    ImGuiIO & io = ImGui::GetIO();
    io.MouseDown[0] = down;
    io.MousePos = ImVec2(PosX,PosY);
    }
}

JNIEXPORT jstring JNICALL Java_com_mycompany_application_GLES3JNIView_getWindowRect(JNIEnv *env, jobject thiz) {
    if (g_Initialized) {
    char result[512]="0|0|0|0";
    if(g_window){
        sprintf(result,"%d|%d|%d|%d",(int)g_window->Pos.x,(int)g_window->Pos.y,(int)g_window->Size.x,(int)g_window->Size.y);
    }
    return env->NewStringUTF(result);
    }
}

JNIEXPORT jint JNICALL
JNI_OnLoad(JavaVM *vm, void *reserved) {
    JNIEnv *globalEnv;
    vm->GetEnv((void **) &globalEnv, JNI_VERSION_1_6);

   pthread_t gameThread = NULL;
    if (gameThread = pthread_self()) {
        pthread_create(&gameThread, NULL, hack_thread, NULL);
    }
    
    return JNI_VERSION_1_6;
}

JNIEXPORT void JNICALL
JNI_OnUnload(JavaVM *vm, void *reserved) {}

