#ifndef EVENTS_H
#define EVENTS_H

#include <iostream>
#include <sst/core/event.h>

namespace SST {
namespace NeuralProcessor{

class CP2CoreEvent : public SST::Event {
public:
  ~CP2CoreEvent() = default;
  CP2CoreEvent() : SST::Event() { }

    // Example data members
    std::vector<char> payload;
    
    // Events must provide a serialization function that serializes
    // all data members of the event
    void serialize_order(SST::Core::Serialization::serializer &ser)  override {
        Event::serialize_order(ser);
        ser & payload;
    }

    // Register this event as serializable
    ImplementSerializable(SST::NeuralProcessor::CP2CoreEvent);

private:

  CP2CoreEvent(CP2CoreEvent &&) = delete;
  CP2CoreEvent(const CP2CoreEvent &) = delete;
  CP2CoreEvent &operator=(CP2CoreEvent &&) = delete;
  CP2CoreEvent &operator=(const CP2CoreEvent &) = delete;
};

} // namespace NeuralProcessor
} // namespace SST

#endif // EVENTS_H