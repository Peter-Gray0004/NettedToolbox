#include "pch.h"
#include "elements.h"
#if __has_include("elements.g.cpp")
#include "elements.g.cpp"
#endif

using namespace winrt;
using namespace Windows::UI::Xaml;

namespace winrt::NettedToolbox::implementation
{
    int32_t elements::MyProperty()
    {
        throw hresult_not_implemented();
    }

    void elements::MyProperty(int32_t /* value */)
    {
        throw hresult_not_implemented();
    }

    void elements::ClickHandler(IInspectable const&, RoutedEventArgs const&)
    {
        Button().Content(box_value(L"Clicked"));
    }
}
