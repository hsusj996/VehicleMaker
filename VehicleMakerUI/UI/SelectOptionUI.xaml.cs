using System.Windows;
using System.Windows.Controls;
using System.Windows.Media;
using System.Text.Json;
using System.Net.Sockets;
using System.Text;
using VehicleMakerUI.Models;

namespace VehicleMakerUI.UI
{
    public partial class SelectOptionUI : Window
    {
        public VehicleConfiguration SelectedConfig { get; private set; }

        public SelectOptionUI()
        {
            InitializeComponent();
            SelectedConfig = new VehicleConfiguration(); 
            HighlightStep(stepType);
        }

        private void HighlightStep(TextBlock activeStep)
        {
            stepType.Foreground = Brushes.Gray;
            stepEngine.Foreground = Brushes.Gray;
            stepBrake.Foreground = Brushes.Gray;
            stepSteering.Foreground = Brushes.Gray;
            stepTest.Foreground = Brushes.Gray;

            stepType.FontWeight = FontWeights.Normal;
            stepEngine.FontWeight = FontWeights.Normal;
            stepBrake.FontWeight = FontWeights.Normal;
            stepSteering.FontWeight = FontWeights.Normal;
            stepTest.FontWeight = FontWeights.Normal;

            activeStep.Foreground = Brushes.White;
            activeStep.FontWeight = FontWeights.Bold;
        }

        public void SetCarType(string type)
        {
            SelectedConfig.CarType = type;
            ShowEngineUI();
        }

        public void SetEngineType(string engine)
        {
            SelectedConfig.EngineType = engine;
            ShowBrakeUI();
        }

        public void SetBrakeSystem(string brake)
        {
            SelectedConfig.BrakeSystem = brake;
            ShowSteeringUI();
        }

        public void SetSteeringSystem(string steering)
        {
            SelectedConfig.SteeringSystem = steering;
            ShowTestUI();
        }

        public void ShowEngineUI()
        {
            carTypeUI.Visibility = Visibility.Collapsed;
            engineUI.Visibility = Visibility.Visible;
            HighlightStep(stepEngine);
        }

        public void ShowBrakeUI()
        {
            engineUI.Visibility = Visibility.Collapsed;
            brakeUI.Visibility = Visibility.Visible;
            HighlightStep(stepBrake);
        }

        public void ShowSteeringUI()
        {
            brakeUI.Visibility = Visibility.Collapsed;
            steeringUI.Visibility = Visibility.Visible;
            HighlightStep(stepSteering);
        }

        public void ShowTestUI()
        {
            steeringUI.Visibility = Visibility.Collapsed;
            testUI.Visibility = Visibility.Visible;
            HighlightStep(stepTest);
        }

        public void resetUI()
        {
            SelectedConfig = new VehicleConfiguration();

            carTypeUI.Visibility = Visibility.Visible;
            engineUI.Visibility = Visibility.Collapsed;
            brakeUI.Visibility = Visibility.Collapsed;
            steeringUI.Visibility = Visibility.Collapsed;
            testUI.Visibility = Visibility.Collapsed;

            HighlightStep(stepType);
        }
        public void SendToCppServer(string testMode)
        {
            try
            {
                string response = SocketService.SendConfiguration(SelectedConfig, testMode);
                MessageBox.Show(response);
            }
            catch (Exception ex)
            {
                MessageBox.Show($"전송 실패: {ex.Message}");
            }
        }

        public void SendResetToCpp()
        {
            try
            {
                SocketService.SendReset();
            }
            catch (Exception ex)
            {
                MessageBox.Show($"리셋 전송 실패: {ex.Message}");
            }
        }

    }



}
