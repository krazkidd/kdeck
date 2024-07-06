#include "ui/StaticCurrency.hpp"

namespace kdeck
{
    StaticCurrency::StaticCurrency(wxWindow* parent, wxWindowID id, double amount)
        : wxStaticText(parent, id, "")
    {
        SetAmount(amount);
    }

    void StaticCurrency::SetAmount(double amount)
    {
        SetLabel(wxString::Format("$%.2f", amount / 100.0));
    }
}
