//// Copyright (c) Microsoft Corporation. All rights reserved

(function () {
    "use strict";
    
    var DevEnum = Windows.Devices.Enumeration;
    var deviceWatcher = null;
    var resultCollection = new WinJS.Binding.List([]);
    var resultsListView;

    var page = WinJS.UI.Pages.define("/html/scenario2_devicewatcher.html", {
        ready: function (element, options) {

            // Setup beforeNavigate event
            WinJS.Navigation.addEventListener("beforenavigate", onLeavingPage);

            // Hook up button event handlers
            document.getElementById("startWatcherButton").addEventListener("click", startWatcher, false);
            document.getElementById("stopWatcherButton").addEventListener("click", stopWatcher, false);

            // Hook up result list data binding
            resultsListView = element.querySelector("#resultsListView").winControl;
            resultsListView.itemDataSource = resultCollection.dataSource;

            // Manually bind selector options
            DisplayHelpers.deviceWatcherSelectors.forEach(function each(item) {
                var option = document.createElement("option");
                option.textContent = item.displayName;
                selectorComboBox.appendChild(option);
            });

            // Process any data bindings
            WinJS.UI.processAll();
        }
    });

    function onLeavingPage() {
        stopWatcher();
        WinJS.Navigation.removeEventListener("beforenavigate", onLeavingPage);
        resultCollection.splice(0, resultCollection.length);
    }

    function startWatcher() {
        startWatcherButton.disabled = true;
        resultCollection.splice(0, resultCollection.length);

        // First get the device selector chosen by the UI.
        var selectedItem = DisplayHelpers.deviceWatcherSelectors.getAt(selectorComboBox.selectedIndex);

        if (null != selectedItem.deviceClassSelector) {
            // If the a pre-canned device class selector was chosen, call the DeviceClass overloa
            deviceWatcher = DevEnum.DeviceInformation.createWatcher(selectedItem.deviceClassSelector);
        }
        else if (selectedItem.kind == DevEnum.DeviceInformationKind.unknown){
            // Use AQS string selector from dynamic call to a device api's GetDeviceSelector call
            // Kind will be determined by the selector
            deviceWatcher = DevEnum.DeviceInformation.createWatcher(
                selectedItem.selector,
                null // don't request additional properties for this sample
                );
        }
        else {
            // Kind is specified in the selector info
            deviceWatcher = DevEnum.DeviceInformation.createWatcher(
                selectedItem.selector,
                null, // don't request additional properties for this sample
                selectedItem.kind);
        }

        // Add event handlers
        deviceWatcher.addEventListener("added", onAdded);
        deviceWatcher.addEventListener("updated", onUpdated);
        deviceWatcher.addEventListener("removed", onRemoved);
        deviceWatcher.addEventListener("enumerationcompleted", onEnumerationCompleted);
        deviceWatcher.addEventListener("stopped", onStopped);

        WinJS.log && WinJS.log("Starting watcher...", "sample", "status");
        deviceWatcher.start();
        stopWatcherButton.disabled = false;
    }

    function stopWatcher() {

        stopWatcherButton.disabled = true;

        if (null != deviceWatcher) {

            // First unhook all event handlers except the stopped handler. This ensures our
            // event handlers don't get called after stop, as stop won't block for any "in flight" 
            // event handler calls.  We leave the stopped handler as it's guaranteed to only be called
            // once and we'll use it to know when the query is completely stopped. 
            deviceWatcher.removeEventListener("added", onAdded);
            deviceWatcher.removeEventListener("updated", onUpdated);
            deviceWatcher.removeEventListener("removed", onRemoved);
            deviceWatcher.removeEventListener("enumerationcompleted", onEnumerationCompleted);        

            if (DevEnum.DeviceWatcherStatus.started == deviceWatcher.status ||
                DevEnum.DeviceWatcherStatus.enumerationCompleted == deviceWatcher.status) {
                deviceWatcher.stop();
            }
        }

        startWatcherButton.disabled = false;
    }

    function onAdded(deviceInfo) {
        // For simplicity, just creating a new "display object" on the fly since databinding directly with deviceInfo from
        // the callback doesn't work. 
        resultCollection.push(new DisplayHelpers.DeviceInformationDisplay(deviceInfo));

        if (deviceWatcher.status == DevEnum.DeviceWatcherStatus.enumerationCompleted) {
            WinJS.log && WinJS.log(resultCollection.length + " devices found. Watching for updates...", "sample", "status");
        }
    }

    function onUpdated(deviceInfoUpdate) {
        // Find the corresponding updated DeviceInformation in the collection and pass the update object
        // to the Update method of the existing DeviceInformation. This automatically updates the object
        // for us.
        resultCollection.forEach(function (value, index, array) {
            if (value.id == deviceInfoUpdate.id) {
                value.update(deviceInfoUpdate);
            }
        });
    }

    function onRemoved(deviceInfoUpdate) {
        for (var i = 0; resultCollection.length; i++) {
            if (resultCollection.getAt(i).id == deviceInfoUpdate.id) {
                resultCollection.splice(i, 1);
                break;
            }
        }

        WinJS.log && WinJS.log(resultCollection.length + " devices found. Watching for updates...", "sample", "status");
    }

    function onEnumerationCompleted(obj) {
        WinJS.log && WinJS.log(resultCollection.length + " devices found. Enumeration completed. Watching for updates...", "sample", "status");
    }

    function onStopped(obj) {
        WinJS.log && WinJS.log(resultCollection.length + " devices found. Watcher stopped", "sample", "status");
    }

})();
