#include "Directory.hpp"

std::shared_ptr<EmpDirectory> EmpDirectory::make(std::string repo_type){
    auto empDir = std::shared_ptr<EmpDirectory>(new EmpDirectory); // create empdir
    
    // Create appropriate repo
    if (repo_type == "InMemory"){ 
            empDir->repo_ = std::static_pointer_cast<RepositoryIf> (std::shared_ptr<InMemoryRepository>(new InMemoryRepository));
    }
    return empDir;
}