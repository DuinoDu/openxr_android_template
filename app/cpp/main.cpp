#include <android_native_app_glue.h>

#include "platform_data.hpp"
#include "platform.hpp"

#include "openxr_program.hpp"
#include "log.hpp"

struct AndroidAppState {
  bool resumed = false;
};

static void AppHandleCmd(struct android_app *app, int32_t cmd) {
  auto *app_state = reinterpret_cast<AndroidAppState *>(app->userData);
  switch (cmd) {
    case APP_CMD_START: {
      Log->info("APP_CMD_START onStart()");
      break;
    }
    case APP_CMD_RESUME: {
      Log->info("APP_CMD_RESUME onResume()");
      app_state->resumed = true;
      break;
    }
    case APP_CMD_PAUSE: {
      Log->info("APP_CMD_PAUSE onPause()");
      app_state->resumed = false;
      break;
    }
    case APP_CMD_STOP: {
      Log->info("APP_CMD_STOP onStop()");
      break;
    }
    case APP_CMD_DESTROY: {
      Log->info("APP_CMD_DESTROY onDestroy()");
      break;
    }
    case APP_CMD_INIT_WINDOW: {
      Log->info("APP_CMD_INIT_WINDOW surfaceCreated()");
      break;
    }
    case APP_CMD_TERM_WINDOW: {
      Log->info("APP_CMD_TERM_WINDOW surfaceDestroyed()");
      break;
    }
  }
}

void android_main(struct android_app *app) {
  try {
    JNIEnv *env;
    app->activity->vm->AttachCurrentThread(&env, nullptr);

    AndroidAppState app_state = {};

    app->userData = &app_state;
    app->onAppCmd = AppHandleCmd;

    std::shared_ptr<PlatformData> data = std::make_shared<PlatformData>();
    data->application_vm = app->activity->vm;
    data->application_activity = app->activity->clazz;

    std::shared_ptr<OpenXrProgram> program = CreateOpenXrProgram(CreatePlatform(data));

    program->CreateInstance();
    program->InitializeSystem();
    program->InitializeSession();
    program->CreateSwapchains();
    while (app->destroyRequested == 0) {
      Log->info("in main loop");
      for (;;) {
        int events;
        struct android_poll_source *source;
        const int kTimeoutMilliseconds =
            (!app_state.resumed && !program->IsSessionRunning() && app->destroyRequested == 0) ? -1 : 0;
        if (ALooper_pollAll(kTimeoutMilliseconds, nullptr, &events, (void **)&source) < 0) {
          break;
        }
        if (source != nullptr) {
          source->process(app, source);
        }
      }

      program->PollEvents();
      if (!program->IsSessionRunning()) {
        continue;
      }

      program->PollActions();
      program->RenderFrame();
    }

    app->activity->vm->DetachCurrentThread();
  } catch (const std::exception &ex) {
    Log->error(ex.what());
  } catch (...) {
    Log->error("Unknown Error");
  }
}
