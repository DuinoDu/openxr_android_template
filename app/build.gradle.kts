plugins {
    id("com.android.application")
}
android {
    compileSdk = 32
    ndkVersion = "26.3.11579264"
    namespace = "app.example.{{crate_name}}"
    defaultConfig {
        minSdk = 32
        targetSdk = 32
        versionCode = 1
        versionName = "1.0"
        applicationId = "app.example.{{crate_name}}"
        externalNativeBuild {
            cmake {
                arguments.add("-DANDROID_STL=c++_shared")
                arguments.add("-DANDROID_USE_LEGACY_TOOLCHAIN_FILE=OFF")
            }
            ndk {
                abiFilters.add("arm64-v8a")
            }
        }
    }
    signingConfigs {
        create("release") {
            // generate keystore by "bash scripts/gen_keystore.sh"
            storeFile = file("../example.keystore")
            storePassword = "android"
            keyAlias = "android"
            keyPassword = "android"
        }
    }
    lint {
        disable.add("ExpiredTargetSdkVersion")
    }
    buildFeatures {
        prefab = true
    }
    buildTypes {
        getByName("debug") {
            isDebuggable = true
            isJniDebuggable = true
        }
        getByName("release") {
            isDebuggable = false
            isJniDebuggable = false
            signingConfig = signingConfigs.getByName("release")

        }
    }
    externalNativeBuild {
        cmake {
            version = "3.22.1"
            path("CMakeLists.txt")
        }
    }
    sourceSets {
        getByName("main") {
            manifest.srcFile("AndroidManifest.xml")
        }
    }
    packaging {
        jniLibs {
            keepDebugSymbols.add("**.so")
        }
    }
}

dependencies {
    implementation("org.khronos.openxr:openxr_loader_for_android:1.0.31")
}
