#ifndef COMMAND_PROCESSOR_H
#define COMMAND_PROCESSOR_H

#include <iostream>

#include <sst/core/component.h>
#include <sst/core/link.h>
#include <sst/core/event.h>
#include <sst/core/sst_config.h>

#include "events.h"

namespace SST {
namespace NeuralProcessor{

class CommandProcessor: public SST::Component {
public:
    ~CommandProcessor();

      // REGISTER THIS COMPONENT INTO THE ELEMENT LIBRARY
    SST_ELI_REGISTER_COMPONENT(
        CommandProcessor,                       // Component class
        "NeuralProcessor",                      // Component library (for Python/library lookup)
        "CommandProcessor",                     // Component name (for Python/library lookup)
        SST_ELI_ELEMENT_VERSION(1,0,0),         // Version of the component 
        "Hardware driver for NeuralProcesor",   // Description
        COMPONENT_CATEGORY_PROCESSOR            // Category
    )

    // Document the parameters that this component accepts
    // { "parameter_name", "description", "default value or NULL if required" }
    SST_ELI_DOCUMENT_PARAMS(
        { "command_file", "File with lists of Command to execute", NULL},
     )

        // Document the ports that this component has
    // {"Port name", "Description", { "list of event types that the port can handle"} }
    SST_ELI_DOCUMENT_PORTS(
        {"port",  "Link to another component", { "CommandProcessor.EmptyEvent", ""} }
    )

    // Optional since there is nothing to document - see statistics example for more info
    SST_ELI_DOCUMENT_STATISTICS( )
    

    // Optional since there is nothing to document - see SubComponent examples for more info
    SST_ELI_DOCUMENT_SUBCOMPONENT_SLOTS( )

    CommandProcessor(SST::ComponentId_t id, SST::Params& params);
private:
    CommandProcessor() = delete;
    CommandProcessor(CommandProcessor &&) = delete;
    CommandProcessor(const CommandProcessor &) = delete;
    CommandProcessor &operator=(CommandProcessor &&) = delete;
    CommandProcessor &operator=(const CommandProcessor &) = delete; 

    // Event handler, called when an event is received on our link
    void handleEvent(SST::NeuralProcessor::CP2CoreEvent *ev);

    // Links
    SST::Link* link;
};

} // namespace NeuralProcessor
} // namespace SST


#endif // COMMAND_PROCESSOR_H