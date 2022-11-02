//===-- GoodbyeWorld.h - Example Transformations ----------------*- C++ -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_TRANSFORMS_UTILS_GOODBYEWORLD_H
#define LLVM_TRANSFORMS_UTILS_GOODBYEWORLD_H

#include "llvm/IR/PassManager.h"

namespace llvm {

class GoodbyeWorldPass : public PassInfoMixin<GoodbyeWorldPass> {
public:
  PreservedAnalyses run(Module &M, ModuleAnalysisManager &AM);

  static bool isRequired() { return true; }
};

} // namespace llvm

#endif // LLVM_TRANSFORMS_UTILS_GOODBYEWORLD_H
