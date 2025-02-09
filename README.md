# {{crate_name}}

Project for {{crate_name}}

### Building the project

```bash
./gradlew build             # for debug and release build

./gradlew assembleDebug     # for debug build
./gradlew assembleRelease   # for release build

./gradlew installDebug      # install debug apk on device
```

Use this template project by:
```
cargo generate https://github.com/DuinoDu/openxr_android_template
```

### Fix bug

Bug:
```
> SDK location not found. Define a valid SDK location with an ANDROID_HOME environment variable or by setting the sdk.dir path in your project's local properties file at '.../local.properties'.
```
Solution:
Open project using AndroidStudio, or define ANDROID_HOME, or create local.properties containing sdk.dir path.
