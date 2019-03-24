using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Reflection;
using System.Text;
using System.Threading.Tasks;
using Microsoft.VisualStudio.TestTools.UnitTesting;

namespace PhysX.Test
{
	public static class TestDependantFiles
	{
		// Copy out the dependant DLL files needed for each test run
		internal static void CopyDependantFiles(TestContext ctx)
		{
			const string platform = "x64";

#if DEBUG
			const string config = "Debug";
#elif RELEASE
			const string config = "Release";
#endif

			string dir = $@"..\..\Assemblies\{platform}\{config}";
			dir = Path.Combine(ctx.TestRunDirectory, dir);
			dir = Path.GetFullPath(dir);

			var files = Directory.GetFiles(dir);

			foreach (var file in files)
			{
				string dst = Path.Combine(ctx.TestDeploymentDir, Path.GetFileName(file));

				File.Copy(file, dst);
			}
		}
	}
}
