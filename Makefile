.PHONY: log build install uninstall run

ADB="adb"
# ADB="adb -s 10.4.167.23:5555"

log:
	$(ADB) logcat -c | $(ADB) logcat | grep '{{crate_name}}:'

build:
	./gradlew assembleDebug

install:
	$(ADB) install -r -d app/build/outputs/apk/debug/app-debug.apk

uninstall:
	$(ADB) uninstall app.example.{{crate_name}}

run:
	$(ADB) shell am start -n app.example.{{crate_name}}/android.app.NativeActivity
