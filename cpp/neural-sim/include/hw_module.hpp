#ifndef HW_MODULE_HPP
#define HW_MODULE_HPP

namespace neural_sim {

class HWBlock {
public:
  ~HWBlock() = default;

private:
  HWBlock() = delete;
  HWBlock(HWBlock &&) = delete;
  HWBlock(const HWBlock &) = delete;
  HWBlock &operator=(HWBlock &&) = delete;
  HWBlock &operator=(const HWBlock &) = delete;
};

class ActiveHWBlock : public HWBlock {
public:
  ~ActiveHWBlock() = default;
  
private:
  ActiveHWBlock() = delete;
  ActiveHWBlock(ActiveHWBlock &&) = delete;
  ActiveHWBlock(const ActiveHWBlock &) = delete;
  ActiveHWBlock &operator=(ActiveHWBlock &&) = delete;
  ActiveHWBlock &operator=(const ActiveHWBlock &) = delete;
};

class PassiveHWBlock {
public:
  ~PassiveHWBlock() = default;

private:
  PassiveHWBlock() = delete;
  PassiveHWBlock(PassiveHWBlock &&) = delete;
  PassiveHWBlock(const PassiveHWBlock &) = delete;
  PassiveHWBlock &operator=(PassiveHWBlock &&) = delete;
  PassiveHWBlock &operator=(const PassiveHWBlock &) = delete;
};

class ScratchPadMem : public PassiveHWBlock {
public:
  ~ScratchPadMem() = default;

private:
  ScratchPadMem() = delete;
  ScratchPadMem(ScratchPadMem &&) = delete;
  ScratchPadMem(const ScratchPadMem &) = delete;
  ScratchPadMem &operator=(ScratchPadMem &&) = delete;
  ScratchPadMem &operator=(const ScratchPadMem &) = delete;
};

class ComputationCore : public ActiveHWBlock {
public:
  ~ComputationCore() = default;

private:
  ComputationCore() = delete;
  ComputationCore(ComputationCore &&) = delete;
  ComputationCore(const ComputationCore &) = delete;
  ComputationCore &operator=(ComputationCore &&) = delete;
  ComputationCore &operator=(const ComputationCore &) = delete;
};

class DMA : public ActiveHWBlock {
public:
  ~DMA() = default;

private:
  DMA() = delete;
  DMA(DMA &&) = delete;
  DMA(const DMA &) = delete;
  DMA &operator=(DMA &&) = delete;
  DMA &operator=(const DMA &) = delete;
};

} // namespace neural_sim

#endif // HW_MODULE_HPP
