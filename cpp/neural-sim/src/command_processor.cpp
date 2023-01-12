
#include "command_processor.h"
#include "events.h"

using namespace SST;
using namespace SST::NeuralProcessor;

CommandProcessor::CommandProcessor (SST::ComponentId_t id, SST::Params& params): 
SST::Component(id){

    link = configureLink("port");
    registerClock("1GHz", new Clock::Handler<CommandProcessor>(this, &CommandProcessor::clockTick));
}

void CommandProcessor::setup() {

}

CommandProcessor::~CommandProcessor() {

}

bool CommandProcessor::clockTick( Cycle_t cycleCount)
{
     if (cycleCount % 100 == 0){
    std::cout << "Sending event";
    auto* ev = new CP2CompCoreEvent(); 
    ev->payload.push_back(2);
    ev->payload.push_back(3);
    link->send(ev);
    return true;
    }
    return false;
}