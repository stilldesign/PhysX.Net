using System;
using System.Windows;
using System.Windows.Interop;

namespace PhysX.Samples
{
	/// <summary>
	/// Interaction logic for SampleWindow.xaml
	/// </summary>
	public partial class SampleWindow : Window
	{
		public SampleWindow()
		{
			InitializeComponent();

			Loaded += Window_Loaded;
			Closed += SampleWindow_Closed;
		}

		private void SampleWindow_Closed(object sender, EventArgs e)
		{
			Environment.Exit(0);
		}

		private void Window_Loaded(object sender, RoutedEventArgs e)
		{
			this.Width = (int)(SystemParameters.PrimaryScreenWidth * 0.85);
			this.Height = (int)(SystemParameters.PrimaryScreenHeight * 0.85);
		}

		public IntPtr RenderCanvasHandle
		{
			get
			{
				return new WindowInteropHelper(this).Handle;
			}
		}
	}
}