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
			using( FluidBlob game = new FluidBlob() )
			{
				game.Run();
			}
		}
	}
}

