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

//
// ActivitySensorBackgroundTask.h
// Declaration of the ActivitySensorBackgroundTask class
//

#pragma once

#include "pch.h"

using namespace Windows::ApplicationModel::Background;

namespace Tasks
{
    [Windows::Foundation::Metadata::WebHostHidden]
    public ref class ActivitySensorBackgroundTask sealed : public IBackgroundTask
    {

    public:
        ActivitySensorBackgroundTask() {}

        virtual void Run(IBackgroundTaskInstance^ taskInstance);
        void OnCanceled(IBackgroundTaskInstance^ taskInstance, BackgroundTaskCancellationReason reason);

    private:
        ~ActivitySensorBackgroundTask() {}

        IBackgroundTaskInstance^ TaskInstance;
    };
}