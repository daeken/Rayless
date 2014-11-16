#include "InstructionDispatcher.hpp"
void InstructionDispatcher::add_Eb_Gb() {
Builder.CreateStore(Builder.CreateAdd(0, 0), 0);
}
void InstructionDispatcher::add_Ev_Gv() {
Builder.CreateStore(Builder.CreateAdd(0, 0), 0);
}
void InstructionDispatcher::add_Gb_Eb() {
Builder.CreateStore(Builder.CreateAdd(0, 0), 0);
}
void InstructionDispatcher::add_Gv_Ev() {
Builder.CreateStore(Builder.CreateAdd(0, 0), 0);
}
void InstructionDispatcher::add_AL_Ib() {
Builder.CreateStore(Builder.CreateAdd(0, 0), 0);
}
void InstructionDispatcher::add_rAX_Iz() {
Builder.CreateStore(Builder.CreateAdd(0, 0), 0);
}
void InstructionDispatcher::sub_Eb_Gb() {
Builder.CreateStore(Builder.CreateSub(0, 0), 0);
}
void InstructionDispatcher::sub_Ev_Gv() {
Builder.CreateStore(Builder.CreateSub(0, 0), 0);
}
void InstructionDispatcher::sub_Gb_Eb() {
Builder.CreateStore(Builder.CreateSub(0, 0), 0);
}
void InstructionDispatcher::sub_Gv_Ev() {
Builder.CreateStore(Builder.CreateSub(0, 0), 0);
}
void InstructionDispatcher::sub_AL_Ib() {
Builder.CreateStore(Builder.CreateSub(0, 0), 0);
}
void InstructionDispatcher::sub_rAX_Iz() {
Builder.CreateStore(Builder.CreateSub(0, 0), 0);
}
void InstructionDispatcher::mov_Eb_Gb() {
Builder.CreateStore(0, 0);
}
void InstructionDispatcher::mov_Ev_Gv() {
Builder.CreateStore(0, 0);
}
void InstructionDispatcher::mov_Gb_Eb() {
Builder.CreateStore(0, 0);
}
void InstructionDispatcher::mov_Gv_Ev() {
Builder.CreateStore(0, 0);
}
void InstructionDispatcher::mov_AL_Ov() {
Builder.CreateStore(0, 0);
}
void InstructionDispatcher::mov_rAX_Ov() {
Builder.CreateStore(0, 0);
}
void InstructionDispatcher::mov_Ov_AL() {
Builder.CreateStore(0, 0);
}
void InstructionDispatcher::mov_Ov_rAX() {
Builder.CreateStore(0, 0);
}
void InstructionDispatcher::mov_AL_Ib() {
Builder.CreateStore(0, 0);
}
void InstructionDispatcher::mov_CL_Ib() {
Builder.CreateStore(0, 0);
}
void InstructionDispatcher::mov_DL_Ib() {
Builder.CreateStore(0, 0);
}
void InstructionDispatcher::mov_BL_Ib() {
Builder.CreateStore(0, 0);
}
void InstructionDispatcher::mov_AH_Ib() {
Builder.CreateStore(0, 0);
}
void InstructionDispatcher::mov_CH_Ib() {
Builder.CreateStore(0, 0);
}
void InstructionDispatcher::mov_DH_Ib() {
Builder.CreateStore(0, 0);
}
void InstructionDispatcher::mov_BH_Ib() {
Builder.CreateStore(0, 0);
}
void InstructionDispatcher::mov_rAX_Iv() {
Builder.CreateStore(0, 0);
}
void InstructionDispatcher::mov_rCX_Iv() {
Builder.CreateStore(0, 0);
}
void InstructionDispatcher::mov_rDX_Iv() {
Builder.CreateStore(0, 0);
}
void InstructionDispatcher::mov_rBX_Iv() {
Builder.CreateStore(0, 0);
}
void InstructionDispatcher::mov_rSP_Iv() {
Builder.CreateStore(0, 0);
}
void InstructionDispatcher::mov_rBP_Iv() {
Builder.CreateStore(0, 0);
}
void InstructionDispatcher::mov_rSI_Iv() {
Builder.CreateStore(0, 0);
}
void InstructionDispatcher::mov_rDI_Iv() {
Builder.CreateStore(0, 0);
}
