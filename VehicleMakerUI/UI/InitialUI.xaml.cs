using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using VehicleMakerUI.UI;

namespace VehicleMakerUI.UI;

public partial class InitialUI : Window
{
    public InitialUI()
    {
        InitializeComponent();
    }

    private void btnStart_Click(object sender, RoutedEventArgs e)
    {
        SelectOptionUI OptionWindow = new SelectOptionUI();

        OptionWindow.Show();

        this.Close();
    }
}