#pragma once
#include "eventi/IEvent.h"

namespace eventi {

/* Disables the event during the lifetime of this object. */
class Scoped_disable
{
public:
    Scoped_disable(IEvent&);
    ~Scoped_disable();

private:
    IEvent& m_event;
    bool m_active;
};

}  // namespace eventi
