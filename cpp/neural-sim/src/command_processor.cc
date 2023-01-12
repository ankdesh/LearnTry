
#include "command_processor.h"


using namespace SST;
using namespace SST::NeuralProcessor;

CommandProcessor::CommandProcessor (SST::ComponentId_t id, SST::Params& params): 
SST::Component(id){


}

CommandProcessor::~CommandProcessor() {

}

void CommandProcessor::handleEvent(SST::Event *ev)
{
    auto *event = dynamic_cast<SST::EmptyEvent*>(ev);
    
    if (event) {
        
        // Receiver has the responsiblity for deleting events
        delete event;

    } else {
        std::cout << "Error! Bad Event Type received by %s!\n", getName().c_str();
    }
}