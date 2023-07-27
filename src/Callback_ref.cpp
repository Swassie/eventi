#include "eventi/Callback_ref.h"

namespace eventi {

Callback_ref::Callback_ref() {}

Callback_ref::Callback_ref(const std::function<void()>& callback_remover)
    : m_callback_remover(callback_remover) {}

void Callback_ref::remove_callback() {
    m_callback_remover();
    m_callback_remover = [] {};
}

}  // namespace eventi
