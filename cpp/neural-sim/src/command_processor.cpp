
#include "command_processor.h"


using namespace SST;
using namespace SST::NeuralProcessor;

CommandProcessor::CommandProcessor (SST::ComponentId_t id, SST::Params& params): 
SST::Component(id){


}

CommandProcessor::~CommandProcessor() {

}

void CommandProcessor::handleEvent(SST::NeuralProcessor::CP2CoreEvent *ev)
{
    auto *event = dynamic_cast<SST::NeuralProcessor::CP2CoreEvent*>(ev);
    
    if (event) {
        for (auto val: event->payload)
        std::cout << "Recieved Event" << val;
        // Receiver has the responsiblity for deleting events
        delete event;

    } else {
        std::cout << "Error! Bad Event Type received by %s!\n", getName().c_str();
    }
}