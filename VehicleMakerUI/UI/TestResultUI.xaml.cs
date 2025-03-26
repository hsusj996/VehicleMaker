using System;
using System.Collections.Generic;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Media;
using VehicleMakerUI.Models;

namespace VehicleMakerUI.UI
{
    public partial class TestResultUI : UserControl
    {
        #region ---Property---
        private readonly CppResponseCode _result;
        private readonly VehicleConfiguration _config;
        #endregion

        #region ---Initialize---
        public TestResultUI(CppResponseCode result, VehicleConfiguration config)
        {
            InitializeComponent();
            _result = result;
            _config = config;

            Loaded += TestResultUI_Loaded;
        }
        #endregion

        #region ---Events---
        private async void TestResultUI_Loaded(object sender, RoutedEventArgs e)
        {
            var messages = GetMessage(_result, _config);
            MessagePanel.Children.Clear();

            foreach (var msg in messages)
            {
                var textBlock = new TextBlock
                {
                    Text = "",
                    Foreground = Brushes.White,
                    FontSize = 35,
                    Margin = new Thickness(5),
                    TextWrapping = TextWrapping.Wrap
                };

                MessagePanel.Children.Add(textBlock);
                await AnimateTextAsync(msg, textBlock);
                await Task.Delay(100);
            }
            btnReturn.Visibility = Visibility.Visible;
        }

        private async Task AnimateTextAsync(string message, TextBlock target)
        {
            target.Text = "";
            foreach (char ch in message)
            {
                target.Text += ch;
                await Task.Delay(30);
            }
        }

        private List<string> GetMessage(CppResponseCode result, VehicleConfiguration config)
        {
            var lines = new List<string>();
            bool isSuccess = true;
            string car = $"\uD83D\uDE97 자동차 타입 체크 ... ✅ {config.CarType}";
            string engine = $"\uD83D\uDEE0 엔진 타입 체크 ... ✅ {config.EngineType}";
            string brake = $"\u1F6D1 브레이크 타입 체크 ... ✅ {config.BrakeSystem}";
            string steering = $"\uD83E\uDDFD 조향 타입 체크 ... ✅ {config.SteeringSystem}";
            string finalresult = $"Success";
            switch (result)
            {
                case CppResponseCode.Fail_Sedan_Continental:
                    car = "\uD83D\uDE97 자동차 타입 체크 ... ✅ Sedan";
                    brake = "\u1F6D1 브레이크 타입 체크 ... ❌ \nSedan은 Continental 제동장치를 사용할 수 없습니다.";
                    isSuccess = false;
                    break;

                case CppResponseCode.Fail_SUV_Toyota:
                    car = "\uD83D\uDE97 자동차 타입 체크 ... ✅ SUV";
                    engine = "\uD83D\uDEE0 엔진 타입 체크 ... ❌ \nSUV는 TOYOTA 엔진을 사용할 수 없습니다.";
                    isSuccess = false;
                    break;

                case CppResponseCode.Fail_Truck_WIA:
                    car = "\uD83D\uDE97 자동차 타입 체크 ... ✅ Truck";
                    engine = "\uD83D\uDEE0 엔진 타입 체크 ... ❌ \nTruck은 WIA 엔진을 사용할 수 없습니다.";
                    isSuccess = false;
                    break;

                case CppResponseCode.Fail_Truck_Mando:
                    car = "\uD83D\uDE97 자동차 타입 체크 ... ✅ Truck";
                    brake = "\u1F6D1 브레이크 타입 체크 ... ❌ \nTruck은 MANDO 제동장치를 사용할 수 없습니다.";
                    isSuccess = false;
                    break;

                case CppResponseCode.Fail_BoschBrake_NoBoschSteering:
                    brake = "\u1F6D1 브레이크 타입 체크 ... ✅ Bosch";
                    steering = "\uD83E\uDDFD 조향 타입 체크 ... ❌ \nBosch 제동장치를 썼다면 조향장치도 Bosch여야 합니다.";
                    isSuccess = false;
                    break;

                case CppResponseCode.Fail_BoschSteering_NoBoschBrake:
                    steering = "\uD83E\uDDFD 조향 타입 체크 ... ✅ Bosch";
                    brake = "\u1F6D1 브레이크 타입 체크 ... ❌ \nBosch 조향장치를 썼다면 제동장치도 Bosch여야 합니다.";
                    isSuccess = false;
                    break;

                case CppResponseCode.Fail_EngineBroken:
                    engine = "\uD83D\uDEE0 엔진 타입 체크 ... ❌ \n엔진이 고장났습니다. 자동차가 움직이지 않습니다.";
                    isSuccess = false;
                    break;
            }

            lines.Add(car);
            lines.Add(engine);
            lines.Add(brake);
            lines.Add(steering);
            string finalResult = isSuccess? "✅ 최종 결과: Success" : "❌ 최종 결과: Failed";
            lines.Add("");
            lines.Add(finalResult);
            return lines;
        }

        private void Button_Click(object sender, RoutedEventArgs e)
        {
            var initial = new InitialUI();
            initial.Show();
            Window.GetWindow(this)?.Close();
        }
    }
    #endregion
}