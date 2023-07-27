#pragma once
#include <stdexcept>
#include <string>

namespace eventi {

class Event_error : public std::runtime_error
{
public:
    Event_error(const std::string&);
};

}  // namespace eventi
