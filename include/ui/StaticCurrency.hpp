#ifndef STATICCURRENCY_HPP
#define STATICCURRENCY_HPP

#include <wx/stattext.h>

class StaticCurrency : public wxStaticText
{
public:
	StaticCurrency(wxWindow* parent, wxWindowID id = wxID_ANY, double amount = 0.0f);

	void SetAmount(double amount);
};

#endif
