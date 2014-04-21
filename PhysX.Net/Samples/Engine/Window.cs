using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace StillDesign.PhysX.Samples
{
	public partial class Window : Form
	{
		public Window()
		{
			InitializeComponent();

			Size = new Size((int)(SystemInformation.PrimaryMonitorSize.Width * 0.85), (int)(SystemInformation.PrimaryMonitorSize.Height * 0.85));
		}

		public IntPtr RenderCanvasHandle
		{
			get
			{
				return panel1.Handle;
			}
		}
	}
}