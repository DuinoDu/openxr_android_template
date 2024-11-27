.PHONY: log build install uninstall run stop

ADB="adb"
# ADB="adb -s 10.4.167.23:5555"

apk=app/build/outputs/apk/debug/app-debug.apk

# Find package name by "adb shell pm list packages | grep -i hello"
package="app.example.{{crate_name}}"

# Find activity name by "adb shell dumpsys package {package-name} | grep -i activity"
activity="android.app.NativeActivity"

log:
	$(ADB) logcat -c | $(ADB) logcat | grep '{{crate_name}}:'

build:
	./gradlew assembleDebug

build-install:
	./gradlew installDebug

install:
	$(ADB) install -r -d $(apk)

uninstall:
	$(ADB) uninstall $(package)

run:
	$(ADB) shell am start -n $(package)/$(activity)

stop:
	$(ADB) shell am force-stop $(package)
