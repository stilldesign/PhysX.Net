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
#if x86
			const string platform = "x86";
#elif x64
			const string platform = "x64";
#endif

#if CHECKED
			const string config = "Checked";
#elif RELEASE
			const string config = "Release";
#endif

			string dir = String.Format(@"..\..\Assemblies\{0}\{1}", platform, config);
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
