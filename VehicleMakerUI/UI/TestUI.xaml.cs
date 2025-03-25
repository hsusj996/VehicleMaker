using System.Windows;
using System.Windows.Controls;

namespace VehicleMakerUI.UI
{
    public partial class TestUI : UserControl
    {
        public TestUI()
        {
            InitializeComponent();
        }

        private void btnRun_Click(object sender, System.Windows.RoutedEventArgs e)
        {
            var parentWindow = Window.GetWindow(this) as SelectOptionUI;
            parentWindow?.SendToCppServer("Run");
        }

        private void btnTest_Click(object sender, System.Windows.RoutedEventArgs e)
        {
            var parentWindow = Window.GetWindow(this) as SelectOptionUI;
            parentWindow?.SendToCppServer("Test");
        }
    }
}
