using System.Windows;
using System.Windows.Controls;
using System.Windows.Media.Imaging;

namespace VehicleMakerUI.UI
{
    public partial class CarTypeSelectUI : UserControl
    {
        public CarTypeSelectUI()
        {
            InitializeComponent();

        }


        private void btnSelectSedan_Click(object sender, RoutedEventArgs e)
        {
            var parentWindow = Window.GetWindow(this) as SelectOptionUI;
            parentWindow?.ShowEngineUI();
            parentWindow?.SetCarType("Sedan");
        }

        private void btnSelectSUV_Click(object sender, RoutedEventArgs e)
        {
            var parentWindow = Window.GetWindow(this) as SelectOptionUI;
            parentWindow?.ShowEngineUI();
            parentWindow?.SetCarType("Suv");
        }

        private void btnSelectTruck_Click(object sender, RoutedEventArgs e)
        {
            var parentWindow = Window.GetWindow(this) as SelectOptionUI;
            parentWindow?.ShowEngineUI();
            parentWindow?.SetCarType("Truck");
        }
    }
}