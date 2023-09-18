
#include "comp_core.h"


using namespace SST;
using namespace SST::NeuralProcessor;

CompCore::CompCore (SST::ComponentId_t id, SST::Params& params): 
SST::Component(id){


 link = configureLink("port", new Event::Handler<CompCore>(this, &CompCore::handleEvent));

}

CompCore::~CompCore() {

}


void CompCore::handleEvent(SST::Event *ev)
{
    auto *event = dynamic_cast<SST::NeuralProcessor::CP2CompCoreEvent*>(ev);
    
    volatile int sum = 0;
    if (event) {
        for (auto val: event->payload){
            std::cout << "Recieved Event" << val;
            sum+=val;
        }
        
        std::cout << sum;
        // Receiver has the responsiblity for deleting events
        delete event;

    } else {
        std::cout << "Error! Bad Event Type received by %s!\n", getName().c_str();
    }
}