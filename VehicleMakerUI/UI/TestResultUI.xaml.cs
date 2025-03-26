using System;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Threading;
using VehicleMakerUI.Models;
using System.Windows.Controls;
namespace VehicleMakerUI.UI
{
    public partial class TestResultUI : UserControl
    {
        #region ---Initialize---
        private readonly CppResponseCode _result;
        public TestResultUI(CppResponseCode result)
        {
            InitializeComponent();
            _result = result;

            Loaded += TestResultDialog_Loaded;
        }
        #endregion


        private async void TestResultDialog_Loaded(object sender, RoutedEventArgs e)
        {
            await Task.Delay(1000);

            LoadingBar.Visibility = Visibility.Collapsed;
            ResultText.Text = GetMessage(_result);
            ResultText.Visibility = Visibility.Visible;
        }

        private string GetMessage(CppResponseCode result)
        {
            return result switch
            {
                CppResponseCode.Success_Run => "✅ Run 테스트 결과 : PASS\n엔진이 정상입니다.",
                CppResponseCode.Fail_EngineBroken => "❌ 엔진이 고장났습니다.\n자동차가 움직이지 않습니다.",
                CppResponseCode.Fail_Sedan_Continental => "❌ Sedan은 Continental 제동장치를 쓸 수 없습니다.",
                CppResponseCode.Fail_SUV_Toyota => "❌ SUV는 도요타 엔진을 쓸 수 없습니다.",
                CppResponseCode.Fail_Truck_WIA => "❌ Truck은 WIA 엔진을 쓸 수 없습니다.",
                CppResponseCode.Fail_Truck_Mando => "❌ Truck은 MANDO 제동장치를 쓸 수 없습니다.",
                CppResponseCode.Fail_BoschBrake_NoBoschSteering => "❌ Bosch 제동장치를 썼다면, 조향장치도 Bosch여야 합니다.",
                CppResponseCode.Fail_BoschSteering_NoBoschBrake => "❌ Bosch 조향장치를 썼다면, 제동장치도 Bosch여야 합니다.",
                CppResponseCode.Success_Test => "✅ 자동차 테스트 결과 : PASS\n모든 조건을 만족합니다.",
                _ => "⚠ 알 수 없는 결과입니다."
            };
        }

        private void Button_Click(object sender, RoutedEventArgs e)
        {
            var initial = new InitialUI();
            initial.Show();
            Window.GetWindow(this)?.Close();
        }
    }
}




