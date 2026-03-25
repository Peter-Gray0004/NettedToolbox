#pragma once

#include "networking.g.h"

namespace winrt::NettedToolbox::implementation
{
    struct networking : networkingT<networking>
    {
        networking() 
        {
            // Xaml objects should not call InitializeComponent during construction.
            // See https://github.com/microsoft/cppwinrt/tree/master/nuget#initializecomponent
        }

        int32_t MyProperty();
        void MyProperty(int32_t value);

        void ClickHandler(Windows::Foundation::IInspectable const& sender, Windows::UI::Xaml::RoutedEventArgs const& args);
    };
}

namespace winrt::NettedToolbox::factory_implementation
{
    struct networking : networkingT<networking, implementation::networking>
    {
    };
}
