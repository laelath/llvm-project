//===-- GoodbyeWorld.cpp - Example Transformations ------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "llvm/Transforms/Utils/GoodbyeWorld.h"

#include "llvm/IR/Constants.h"

using namespace llvm;

PreservedAnalyses GoodbyeWorldPass::run(Module &M, ModuleAnalysisManager &AM) {

  SymbolTableList<GlobalVariable> &Thing = M.getGlobalList();
  for (auto &GV : Thing) {
      if (GV.hasInitializer()) {
          Constant *Initer = GV.getInitializer();

          if (auto *V = dyn_cast<ConstantDataSequential>(Initer)) {
              if (V->isCString()) {
                  auto CStr = V->getAsCString();
                  if (CStr.equals("hello world")) {
                      errs() << "found \"hello world\"!\n";

                      auto *Goodbye = ConstantDataArray::get(M.getContext(), "gdbye world");
                      GV.setInitializer(Goodbye);
                  }
              }
          }
      }
  }

  return PreservedAnalyses::none();
}
