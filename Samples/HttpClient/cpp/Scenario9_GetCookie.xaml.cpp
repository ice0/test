//*********************************************************
//
// Copyright (c) Microsoft. All rights reserved.
// This code is licensed under the MIT License (MIT).
// THIS CODE IS PROVIDED *AS IS* WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESS OR IMPLIED, INCLUDING ANY
// IMPLIED WARRANTIES OF FITNESS FOR A PARTICULAR
// PURPOSE, MERCHANTABILITY, OR NON-INFRINGEMENT.
//
//*********************************************************



#include "pch.h"
#include "Scenario9_GetCookie.xaml.h"

using namespace SDKTemplate;

using namespace concurrency;
using namespace Platform;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::Globalization::DateTimeFormatting;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Navigation;
using namespace Windows::Web::Http;
using namespace Windows::Web::Http::Filters;

Scenario9::Scenario9()
{
    InitializeComponent();
}

/// <summary>
/// Invoked when this page is about to be displayed in a Frame.
/// </summary>
/// <param name="e">Event data that describes how this page was reached.  The Parameter
/// property is typically used to configure the page.</param>
void Scenario9::OnNavigatedTo(NavigationEventArgs^ e)
{
    // A pointer back to the main page.  This is needed if you want to call methods in MainPage such
    // as NotifyUser()
    rootPage = MainPage::Current;

    httpClient = Helpers::CreateHttpClient();
    cancellationTokenSource = cancellation_token_source();
}

void Scenario9::OnNavigatedFrom(NavigationEventArgs^ e)
{
    // If the navigation is external to the app do not clean up.
    // This can occur on Phone when suspending the app.
    if (e->NavigationMode == NavigationMode::Forward && e->Uri == nullptr)
    {
        return;
    }

    Page::OnNavigatedFrom(e);
}

void Scenario9::GetCookies_Click(Object^ sender, RoutedEventArgs^ e)
{
    try
    {
        Uri^ resourceAddress;

        // The value of 'AddressField' is set by the user and is therefore untrusted input. If we can't create a
        // valid, absolute URI, we'll notify the user about the incorrect input.
        if (!rootPage->TryGetUri(AddressField->Text, &resourceAddress))
        {
            rootPage->NotifyUser("Invalid URI.", NotifyType::ErrorMessage);
            return;
        }

        HttpBaseProtocolFilter^ filter = ref new HttpBaseProtocolFilter();
        HttpCookieCollection^ cookieCollection = filter->CookieManager->GetCookies(resourceAddress);
        OutputField->Text = cookieCollection->Size + " cookies found.\r\n";
        for (HttpCookie^ cookie : cookieCollection)
        {
            OutputField->Text += "--------------------\r\n";
            OutputField->Text += "Name: " + cookie->Name + "\r\n";
            OutputField->Text += "Domain: " + cookie->Domain + "\r\n";
            OutputField->Text += "Path: " + cookie->Path + "\r\n";
            OutputField->Text += "Value: " + cookie->Value + "\r\n";

            String^ expirationTimeString = "";
            if (cookie->Expires)
            {
                DateTimeFormatter^ dateFormatter = ref new DateTimeFormatter("shortdate longtime");
                expirationTimeString = dateFormatter->Format(cookie->Expires->Value);
            }

            OutputField->Text += "Expires: " + expirationTimeString + "\r\n";
            OutputField->Text += "Secure: " + cookie->Secure + "\r\n";
            OutputField->Text += "HttpOnly: " + cookie->HttpOnly + "\r\n";
        }
    }
    catch (Exception^ ex)
    {
        rootPage->NotifyUser("Error: " + ex->Message, NotifyType::ErrorMessage);
    }
}

void Scenario9::SendHttpGetButton_Click(Object^ sender, RoutedEventArgs^ e)
{
    Helpers::ScenarioStarted(SendHttpGetButton, CancelButton, OutputField);
    rootPage->NotifyUser("In progress", NotifyType::StatusMessage);

    Uri^ resourceAddress;

    // The value of 'AddressField' is set by the user and is therefore untrusted input. If we can't create a
    // valid, absolute URI, we'll notify the user about the incorrect input.
    if (!rootPage->TryGetUri(AddressField->Text, &resourceAddress))
    {
        rootPage->NotifyUser("Invalid URI.", NotifyType::ErrorMessage);
        return;
    }

    // Do an asynchronous GET.  We need to use use_current() with the continuations since the tasks are completed on
    // background threads and we need to run on the UI thread to update the UI.
    create_task(
        httpClient->GetAsync(resourceAddress),
        cancellationTokenSource.get_token()).then([this](HttpResponseMessage^ response)
    {
        return Helpers::DisplayTextResultAsync(response, OutputField, cancellationTokenSource.get_token());
    }, task_continuation_context::use_current()).then([=](task<HttpResponseMessage^> previousTask)
    {
        try
        {
            // Check if any previous task threw an exception.
            previousTask.get();

            rootPage->NotifyUser("Completed", NotifyType::StatusMessage);
        }
        catch (const task_canceled&)
        {
            rootPage->NotifyUser("Request canceled.", NotifyType::ErrorMessage);
        }
        catch (Exception^ ex)
        {
            rootPage->NotifyUser("Error: " + ex->Message, NotifyType::ErrorMessage);
        }

        Helpers::ScenarioCompleted(SendHttpGetButton, CancelButton);

    }, task_continuation_context::use_current());
}

void Scenario9::Cancel_Click(Object^ sender, RoutedEventArgs^ e)
{
    cancellationTokenSource.cancel();

    // Re-create the CancellationTokenSource.
    cancellationTokenSource = cancellation_token_source();
}
