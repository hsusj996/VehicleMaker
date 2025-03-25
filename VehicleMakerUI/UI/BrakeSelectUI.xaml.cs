﻿using System.Windows;
using System.Windows.Controls;

namespace VehicleMakerUI.UI
{
    public partial class BrakeSelectUI : UserControl
    {
        public BrakeSelectUI()
        {
            InitializeComponent();
        }

        private void btnSelectBosch_Click(object sender, System.Windows.RoutedEventArgs e)
        {
            var parentWindow = Window.GetWindow(this) as SelectOptionUI;
            parentWindow?.ShowSteeringUI();
            parentWindow?.SetBrakeSystem("Bosch");
        }

        private void btnSelectContinental_Click(object sender, System.Windows.RoutedEventArgs e)
        {
            var parentWindow = Window.GetWindow(this) as SelectOptionUI;
            parentWindow?.ShowSteeringUI();
            parentWindow?.SetBrakeSystem("Continental");
        }

        private void btnSelectMando_Click(object sender, System.Windows.RoutedEventArgs e)
        {
            var parentWindow = Window.GetWindow(this) as SelectOptionUI;
            parentWindow?.ShowSteeringUI();
            parentWindow?.SetBrakeSystem("Mando");
        }
    }
}
