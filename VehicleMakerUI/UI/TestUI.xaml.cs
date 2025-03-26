using System.Windows;
using System.Windows.Controls;

namespace VehicleMakerUI.UI
{
    public partial class TestUI : UserControl
    {
        #region ---Initialize---
        public TestUI()
        {
            InitializeComponent();
        }
        #endregion

        #region ---Button Event---
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

        private void btnReset_Click(object sender, RoutedEventArgs e)
        {
            var parentWindow = Window.GetWindow(this) as SelectOptionUI;
            parentWindow?.resetUI();
            parentWindow?.SendResetToCpp();
        }
        #endregion
    }
}
