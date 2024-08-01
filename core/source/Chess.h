#pragma once
#include <Handler.h>

namespace Chess {
static void Run() {
  Handler handler = Handler();
  handler.GameLoop();
}
} // namespace Chess
