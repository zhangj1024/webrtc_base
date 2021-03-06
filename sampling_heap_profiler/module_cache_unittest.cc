// Copyright 2018 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "base/sampling_heap_profiler/module_cache.h"
#include "build/build_config.h"
#include "testing/gtest/include/gtest/gtest.h"

namespace base {
namespace {

class ModuleCacheTest : public ::testing::Test {};

int AFunctionForTest() {
  return 42;
}

// Checks that ModuleCache returns the same module instance for
// addresses within the module.
#if defined(OS_MACOSX) && !defined(OS_IOS)
#define MAYBE_ModuleCache ModuleCache
#else
#define MAYBE_ModuleCache DISABLED_ModuleCache
#endif
TEST_F(ModuleCacheTest, MAYBE_ModuleCache) {
  uintptr_t ptr1 = reinterpret_cast<uintptr_t>(&AFunctionForTest);
  uintptr_t ptr2 = ptr1 + 1;
  ModuleCache cache;
  const ModuleCache::Module& module1 = cache.GetModuleForAddress(ptr1);
  const ModuleCache::Module& module2 = cache.GetModuleForAddress(ptr2);
  EXPECT_EQ(&module1, &module2);
  EXPECT_TRUE(module1.is_valid);
  EXPECT_LT(module1.base_address, ptr1);
  EXPECT_GT(module1.base_address + module1.size, ptr2);
}

TEST_F(ModuleCacheTest, InvalidModule) {
  ModuleCache cache;
  const ModuleCache::Module& invalid_module = cache.GetModuleForAddress(1);
  EXPECT_FALSE(invalid_module.is_valid);
}

}  // namespace
}  // namespace base
