# Use meta openxr loader

Current project uses official openxr loader from openxr org. It is automatically downloaded by gradle:

```kotlin
dependencies {
    implementation("org.khronos.openxr:openxr_loader_for_android:1.0.31")
}
```
You don't need to download openxr library manually.

Official openxr loader can be executed on PICO device, but not for Quest.

If you want to use meta openxr loader, you need to update files as following:

```
file: app/CMakeLists.txt
 
-find_package(OpenXR REQUIRED CONFIG)

+add_subdirectory(meta_quest_openxr_loader)
+
+FetchContent_Declare(OpenXR-SDK
+        GIT_REPOSITORY https://github.com/KhronosGroup/OpenXR-SDK.git
+        GIT_TAG release-1.0.33 #must match the meta quest loader OpenXR version
+        #https://developer.oculus.com/downloads/package/oculus-openxr-mobile-sdk#current-openxr-version
+        GIT_SHALLOW TRUE
+        GIT_PROGRESS TRUE
+)
+FetchContent_MakeAvailable(OpenXR-SDK)
 
file: app/build.gradle.kts

     lint {
         disable.add("ExpiredTargetSdkVersion")
     }
-    buildFeatures {
-        prefab = true
-    }
     buildTypes {
         getByName("release") {
             isDebuggable = false
@@ -44,14 +47,6 @@ android {
         getByName("main") {
             manifest.srcFile("AndroidManifest.xml")
         }
+        getByName("debug") {
+            jniLibs {
+                srcDir("libs/debug")
+            }
+        }
+        getByName("release") {
+            jniLibs.srcDir("libs/release")
+        }

-dependencies {
-    implementation("org.khronos.openxr:openxr_loader_for_android:1.0.31")
-}

file: app/cpp/CMakeLists.txt
 
-target_include_directories(hello-xr PRIVATE "openxr")

target_link_libraries(
         android
         glm
         native_app_glue
-        OpenXR::openxr_loader
+        meta_quest_openxr_loader
+        OpenXR::headers
         shaders
         magic_enum
         spdlog
```
