#include <string>

class IService
{
public:
    // general return type, should be a template (or type-erasure)?
    virtual string functionHandle(std::string func) = 0;
};
