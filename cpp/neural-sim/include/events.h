#ifndef EVENTS_H
#define EVENTS_H

#include <iostream>
#include <sst/core/event.h>

namespace SST {
namespace NeuralProcessor{

class CP2CompCoreEvent : public SST::Event {
public:
  ~CP2CompCoreEvent() = default;
  CP2CompCoreEvent() : SST::Event() { }

    // Example data members
    std::vector<char> payload;
    
    // Events must provide a serialization function that serializes
    // all data members of the event
    void serialize_order(SST::Core::Serialization::serializer &ser)  override {
        Event::serialize_order(ser);
        ser & payload;
    }

    // Register this event as serializable
    ImplementSerializable(SST::NeuralProcessor::CP2CompCoreEvent);

private:

  CP2CompCoreEvent(CP2CompCoreEvent &&) = delete;
  CP2CompCoreEvent(const CP2CompCoreEvent &) = delete;
  CP2CompCoreEvent &operator=(CP2CompCoreEvent &&) = delete;
  CP2CompCoreEvent &operator=(const CP2CompCoreEvent &) = delete;
};

} // namespace NeuralProcessor
} // namespace SST

#endif // EVENTS_H