using System;
using System.Windows;
using System.Windows.Interop;
using System.Windows.Input;

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

			this.Left = (SystemParameters.PrimaryScreenWidth / 2) - (this.Width / 2);
			this.Top = (SystemParameters.PrimaryScreenHeight / 2) - (this.Height / 2);
		}

		private void Window_KeyUp(object sender, KeyEventArgs e)
		{
			if (e.Key == Key.Escape)
				Close();
		}

		//

		public IntPtr RenderCanvasHandle
		{
			get
			{
				return new WindowInteropHelper(this).Handle;
			}
		}

		public Size RenderCanvasSize
		{
			get
			{
				return new Size(uxRenderCanvas.ActualWidth, uxRenderCanvas.ActualHeight);
			}
		}
	}
}