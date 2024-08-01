#pragma once
#include "Handler.h"
#include "memory"

namespace Chess {
void Start() {
  std::unique_ptr<Handler> handler = std::make_unique<Handler>();
};
} // namespace Chess
