﻿using System.Windows;
using System.Windows.Controls;

namespace VehicleMakerUI.UI
{
    public partial class SteeringSelectUI : UserControl
    {
        #region ---Initialize---
        public SteeringSelectUI()
        {
            InitializeComponent();
        }
        #endregion

        #region ---Button Event---
        private void btnSelectBosch_Click(object sender, System.Windows.RoutedEventArgs e)
        {
            var parentWindow = Window.GetWindow(this) as SelectOptionUI;
            parentWindow?.SetSteeringSystem("Bosch");
            parentWindow?.ShowTestUI();

        }

        private void btnSelectMobis_Click(object sender, System.Windows.RoutedEventArgs e)
        {
            var parentWindow = Window.GetWindow(this) as SelectOptionUI;
            parentWindow?.SetSteeringSystem("Mobis");
            parentWindow?.ShowTestUI();
        }
        #endregion
    }
}
