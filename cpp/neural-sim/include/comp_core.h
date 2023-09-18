#ifndef COMP_CORE_H
#define COMP_CORE_H

#include <iostream>

#include <sst/core/component.h>
#include <sst/core/link.h>
#include <sst/core/event.h>
#include <sst/core/sst_config.h>

#include "events.h"

namespace SST {
namespace NeuralProcessor{

class CompCore: public SST::Component {
public:
    ~CompCore();

      // REGISTER THIS COMPONENT INTO THE ELEMENT LIBRARY
    SST_ELI_REGISTER_COMPONENT(
        CompCore,                               // Component class
        "NeuralProcessor",                      // Component library (for Python/library lookup)
        "CompCore",                             // Component name (for Python/library lookup)
        SST_ELI_ELEMENT_VERSION(1,0,0),         // Version of the component 
        "Hardware driver for NeuralProcesor",   // Description
        COMPONENT_CATEGORY_PROCESSOR            // Category
    )

    // Document the parameters that this component accepts
    // { "parameter_name", "description", "default value or NULL if required" }
    SST_ELI_DOCUMENT_PARAMS(

     )

        // Document the ports that this component has
    // {"Port name", "Description", { "list of event types that the port can handle"} }
    SST_ELI_DOCUMENT_PORTS(
        {"port",  "Link to another component", { "NeuralProcessor.CP2CompCoreEvent", ""} }
    )

    // Optional since there is nothing to document - see statistics example for more info
    SST_ELI_DOCUMENT_STATISTICS( )
    

    // Optional since there is nothing to document - see SubComponent examples for more info
    SST_ELI_DOCUMENT_SUBCOMPONENT_SLOTS( )

    CompCore(SST::ComponentId_t id, SST::Params& params);
private:
    CompCore() = delete;
    CompCore(CompCore &&) = delete;
    CompCore(const CompCore &) = delete;
    CompCore &operator=(CompCore &&) = delete;
    CompCore &operator=(const CompCore &) = delete; 

    // Event handler, called when an event is received on our link
    void handleEvent(SST::Event *ev);

    // Links
    SST::Link* link;
};

} // namespace NeuralProcessor
} // namespace SST


#endif // COMP_CORE_H