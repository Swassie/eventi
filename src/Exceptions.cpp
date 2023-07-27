#include "eventi/Exceptions.h"

namespace eventi {

Event_error::Event_error(const std::string& message)
    : std::runtime_error(message) {}

}  // namespace eventi
