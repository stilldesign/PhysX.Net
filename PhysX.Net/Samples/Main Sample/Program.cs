using System;

namespace StillDesign.PhysX.Samples
{
	static class Program
	{
		/// <summary>
		/// The main entry point for the application.
		/// </summary>
		static void Main( string[] args )
		{
			using( MainSample game = new MainSample() )
			{
				game.Run();
			}
		}
	}
}