#include "eventi/Scoped_disable.h"

namespace eventi {

Scoped_disable::Scoped_disable(IEvent& event)
    : m_event(event),
      m_active(m_event.enabled()){
    if(m_active) {
        m_event.enable_event(false);
    }
}

Scoped_disable::~Scoped_disable() {
    if(m_active) {
        m_event.enable_event(true);
    }
}

}  // namespace eventi
