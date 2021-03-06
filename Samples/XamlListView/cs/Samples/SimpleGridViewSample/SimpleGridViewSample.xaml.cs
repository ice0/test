using ListViewSample.Model;
using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;

namespace ListViewSample
{
    public sealed partial class SimpleGridViewSample : Page
    {
        public SimpleGridViewSample()
        {
            this.InitializeComponent();
            ContactsCVS.Source = Contact.GetContactsGrouped(250);
        }
        private void ShowSliptView(object sender, RoutedEventArgs e)
        {
            MySamplesPane.SamplesSplitView.IsPaneOpen = !MySamplesPane.SamplesSplitView.IsPaneOpen;
        }
    }
}
