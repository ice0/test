<!---
  category: ControlsLayoutAndText
  samplefwlink: http://go.microsoft.com/fwlink/p/?LinkId=620525
--->

# Context menu sample

Shows how to create a context menu and how to replace the default context menu for text. 

> **Note:** This sample is part of a large collection of UWP feature samples. 
> If you are unfamiliar with Git and GitHub, you can download the entire collection as a 
> [ZIP file](https://github.com/Microsoft/Windows-universal-samples/archive/master.zip), but be 
> sure to unzip everything to access shared dependencies. For more info on working with the ZIP file, 
> the samples collection, and GitHub, see [Get the UWP samples from GitHub](https://aka.ms/ovu2uq). 
> For more samples, see the [Samples portal](https://aka.ms/winsamples) on the Windows Dev Center. 

This sample uses [Windows.UI.Popups](http://msdn.microsoft.com/library/windows/apps/br242180) API, 
including the [PopupMenu](http://msdn.microsoft.com/library/windows/apps/br208693) and the 
[contextmenu | oncontextmenu](http://msdn.microsoft.com/library/windows/apps/hh441317) event.

The sample demonstrates these two tasks:

-   **Creating a context menu to show for a file**

-   **Replacing the default commands in the context menu that is shown for text**

To learn about choosing commands and designing a context menu, see [Guidelines and checklist for context menus](http://msdn.microsoft.com/library/windows/apps/hh465308).

Additional APIs for this sample include:

-   [UICommand](http://msdn.microsoft.com/library/windows/apps/br242166) class
-   [UICommandSeparator](http://msdn.microsoft.com/library/windows/apps/br242168) class

**Note** The Windows universal samples require Visual Studio 2017 to build and Windows 10 to execute.
 
To obtain information about Windows 10 development, go to the [Windows Dev Center](http://go.microsoft.com/fwlink/?LinkID=532421)

To obtain information about Microsoft Visual Studio and the tools for developing Windows apps, go to [Visual Studio](http://go.microsoft.com/fwlink/?LinkID=532422)

## Related topics

### Reference

[Windows.UI.Popups](http://msdn.microsoft.com/library/windows/apps/br242180)  

## System requirements

**Client:** Windows 10

**Server:** Windows Server 2016 Technical Preview

**Phone:** Windows 10

## Build the sample

1. If you download the samples ZIP, be sure to unzip the entire archive, not just the folder with the sample you want to build. 
2. Start Microsoft Visual Studio 2017 and select **File** \> **Open** \> **Project/Solution**.
3. Starting in the folder where you unzipped the samples, go to the Samples subfolder, then the subfolder for this specific sample, then the subfolder for your preferred language (C++, C#, or JavaScript). Double-click the Visual Studio Solution (.sln) file.
4. Press Ctrl+Shift+B, or select **Build** \> **Build Solution**.

## Run the sample

The next steps depend on whether you just want to deploy the sample or you want to both deploy and run it.

### Deploying the sample

- Select Build > Deploy Solution. 

### Deploying and running the sample

- To debug the sample and then run it, press F5 or select Debug >  Start Debugging. To run the sample without debugging, press Ctrl+F5 or select Debug > Start Without Debugging. 
