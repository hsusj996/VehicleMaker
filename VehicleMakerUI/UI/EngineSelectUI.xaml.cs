using System.Windows;
using System.Windows.Controls;

namespace VehicleMakerUI.UI
{
    public partial class EngineSelectUI : UserControl
    {
        public EngineSelectUI()
        {
            InitializeComponent();
        }


        private void btnSelectGm_Click(object sender, RoutedEventArgs e)
        {
            var parentWindow = Window.GetWindow(this) as SelectOptionUI;
            parentWindow?.ShowBrakeUI();
            parentWindow?.SetEngineType("Gm");
        }

        private void btnSelectToyota_Click(object sender, RoutedEventArgs e)
        {
            var parentWindow = Window.GetWindow(this) as SelectOptionUI;
            parentWindow?.ShowBrakeUI();
            parentWindow?.SetEngineType("Toyota");
        }

        private void btnSelectWia_Click(object sender, RoutedEventArgs e)
        {
            var parentWindow = Window.GetWindow(this) as SelectOptionUI;
            parentWindow?.ShowBrakeUI();
            parentWindow?.SetEngineType("Wia");
        }

        private void btnBroken_Click(object sender, RoutedEventArgs e)
        {
            var parentWindow = Window.GetWindow(this) as SelectOptionUI;
            parentWindow?.ShowBrakeUI();
            parentWindow?.SetEngineType("Broken");
        }
    }
}
