#include "pch.h"
#include "networking.h"
#if __has_include("networking.g.cpp")
#include "networking.g.cpp"
#endif

using namespace winrt;
using namespace Windows::UI::Xaml;

namespace winrt::NettedToolbox::implementation
{
    int32_t networking::MyProperty()
    {
        throw hresult_not_implemented();
    }

    void networking::MyProperty(int32_t /* value */)
    {
        throw hresult_not_implemented();
    }

    void networking::ClickHandler(IInspectable const&, RoutedEventArgs const&)
    {
        Button().Content(box_value(L"Clicked"));
    }
}
