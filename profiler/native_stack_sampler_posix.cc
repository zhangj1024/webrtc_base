// Copyright 2015 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "base/profiler/native_stack_sampler.h"

namespace base {

std::unique_ptr<NativeStackSampler> NativeStackSampler::Create(
    PlatformThreadId thread_id,
    NativeStackSamplerTestDelegate* test_delegate) {
  return std::unique_ptr<NativeStackSampler>();
}

// static
StackSamplingProfiler::InternalModule NativeStackSampler::GetModuleForAddress(
    uintptr_t address) {
  // TODO(alph): Implement it.
  return StackSamplingProfiler::InternalModule();
}

size_t NativeStackSampler::GetStackBufferSize() {
  return 0;
}

}  // namespace base
