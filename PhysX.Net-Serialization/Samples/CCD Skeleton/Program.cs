using System;

namespace StillDesign
{
	static class Program
	{
		/// <summary>
		/// The main entry point for the application.
		/// </summary>
		static void Main( string[] args )
		{
			using( CCDSkeletonSample game = new CCDSkeletonSample() )
			{
				game.Run();
			}
		}
	}
}

