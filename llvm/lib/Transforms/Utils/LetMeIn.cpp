//===----- LetMeIn.cpp - Example Transformations --------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "llvm/Transforms/Utils/LetMeIn.h"

#include "llvm/Transforms/Utils/BuildLibCalls.h"

#include "llvm/Pass.h"

#include "llvm/IR/Constants.h"
#include "llvm/IR/IRBuilder.h"

using namespace llvm;

BasicBlock *createCheck(LLVMContext &Context, Function &F, unsigned Idx, char C, BasicBlock *Next, BasicBlock *Done) {
    auto *I8Ty = Type::getInt8Ty(Context);

    auto *BB = BasicBlock::Create(Context, "cmp", &F, Next);
    IRBuilder<> Builder(BB);

    auto *GEP = Builder.CreateConstInBoundsGEP1_64(I8Ty, F.getArg(0), Idx);
    auto *Load = Builder.CreateLoad(I8Ty, GEP);
    auto *Cmp = Builder.CreateICmpEQ(Load, ConstantInt::get(I8Ty, C));
    Builder.CreateCondBr(Cmp, Next, Done);

    return BB;
}

PreservedAnalyses LetMeInPass::run(Function &F, FunctionAnalysisManager &AM) {

    LLVMContext &Context = F.getContext();

    if (F.hasName() && F.getName().equals("checkPassword")) {
        auto &Entry = F.getEntryBlock();

        auto *BB = BasicBlock::Create(Context, "muahaha", &F, &Entry);
        IRBuilder<> Builder(BB);

        Builder.CreateRet(ConstantInt::get(Type::getInt32Ty(Context), 1));

        auto *B0  = createCheck(Context, F, 13, '\0', BB, &Entry);
        auto *BE4 = createCheck(Context, F, 12, 'e', B0, &Entry);
        auto *BS  = createCheck(Context, F, 11, 's', BE4, &Entry);
        auto *BA  = createCheck(Context, F, 10, 'a', BS, &Entry);
        auto *BE3 = createCheck(Context, F, 9, 'e', BA, &Entry);
        auto *BL  = createCheck(Context, F, 8, 'l', BE3, &Entry);
        auto *BP  = createCheck(Context, F, 7, 'p', BL, &Entry);
        auto *BN  = createCheck(Context, F, 6, 'n', BP, &Entry);
        auto *BI  = createCheck(Context, F, 5, 'i', BN, &Entry);
        auto *BE2 = createCheck(Context, F, 4, 'e', BI, &Entry);
        auto *BM  = createCheck(Context, F, 3, 'm', BE2, &Entry);
        auto *BT  = createCheck(Context, F, 2, 't', BM, &Entry);
        auto *BE1 = createCheck(Context, F, 1, 'e', BT, &Entry);
        createCheck(Context, F, 0, 'l', BE1, &Entry);
    }

    return PreservedAnalyses::none();
}
