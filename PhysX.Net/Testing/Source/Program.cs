using System;
using System.Collections.Generic;
using Microsoft.Xna.Framework;

namespace StillDesign
{
	static class Program
	{
		/// <summary>
		/// The main entry point for the application.
		/// </summary>
		[STAThread]
		static void Main()
		{
			using( Demo game = new Demo() )
			{
				game.Run();
			}
		}
	}
}