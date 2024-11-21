cmake_minimum_required(VERSION 3.22.1)
include(FetchContent)

project({{crate_name}})

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_POLICY_DEFAULT_CMP0077 NEW)

FetchContent_Declare(magic_enum
        GIT_REPOSITORY https://github.com/Neargye/magic_enum.git
        GIT_TAG v0.9.5
        GIT_SHALLOW TRUE
        GIT_PROGRESS TRUE
)
FetchContent_MakeAvailable(magic_enum)

FetchContent_Declare(spdlog
        GIT_REPOSITORY https://github.com/gabime/spdlog.git
        GIT_TAG v1.13.0
        GIT_SHALLOW TRUE
        GIT_PROGRESS TRUE
        )
FetchContent_MakeAvailable(spdlog)

FetchContent_Declare(glm
        GIT_REPOSITORY https://github.com/g-truc/glm.git
        GIT_TAG 1.0.1
        GIT_SHALLOW TRUE
        GIT_PROGRESS TRUE
        )
FetchContent_MakeAvailable(glm)

FetchContent_Declare(SPIRV-Reflect
        GIT_REPOSITORY https://github.com/KhronosGroup/SPIRV-Reflect.git
        GIT_TAG vulkan-sdk-1.3.280.0
        GIT_SHALLOW TRUE
        GIT_PROGRESS TRUE
        )
set(SPIRV_REFLECT_EXAMPLES OFF)
set(SPIRV_REFLECT_EXECUTABLE OFF)
set(SPIRV_REFLECT_STATIC_LIB ON)
FetchContent_MakeAvailable(SPIRV-Reflect)

find_package(OpenXR REQUIRED CONFIG)

add_subdirectory(cpp/vulkan)
add_subdirectory(cpp/shaders)

add_library(native_app_glue STATIC ${ANDROID_NDK}/sources/android/native_app_glue/android_native_app_glue.c)
target_include_directories(native_app_glue PUBLIC ${ANDROID_NDK}/sources/android/native_app_glue)
set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -u ANativeActivity_onCreate")

add_library(${CMAKE_PROJECT_NAME} SHARED
        cpp/graphics_plugin_vulkan.cpp
        cpp/main.cpp
        cpp/openxr_program.cpp
        cpp/openxr_utils.cpp
        cpp/platform_android.cpp
        cpp/vulkan_swapchain_context.cpp
        )

target_compile_definitions(${CMAKE_PROJECT_NAME} PRIVATE XR_USE_PLATFORM_ANDROID
        XR_USE_GRAPHICS_API_VULKAN
        VK_USE_PLATFORM_ANDROID_KHR)

target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE "openxr")

target_link_libraries(${CMAKE_PROJECT_NAME}
        android
        glm
        native_app_glue
        OpenXR::openxr_loader
        shaders
        spdlog
        vulkan-wrapper
)
