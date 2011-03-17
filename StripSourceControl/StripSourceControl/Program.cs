using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;

namespace StripSourceControl
{
	/// <summary>
	/// Simple util app to strip out the TFS bindings from solution files.
	/// </summary>
	class Program
	{
		static void Main(string[] args)
		{
			foreach (string arg in args)
			{
				if (arg.EndsWith(".sln"))
				    StripFromSolution(arg);
			}
		}

		private static void StripFromSolution(string slnPath)
		{
			if (!File.Exists(slnPath))
				return;

			StringBuilder sln = new StringBuilder();
			StringReader reader = new StringReader(File.ReadAllText(slnPath));

			bool inTfsBlock = false;

			string line;
			while ((line = reader.ReadLine()) != null)
			{
				if (line.Contains("GlobalSection(TeamFoundationVersionControl)"))
				{
					inTfsBlock = true;
					continue;
				}

				if (inTfsBlock && line.Contains("EndGlobalSection"))
				{
					inTfsBlock = false;
					continue;
				}

				if (inTfsBlock)
					continue;

				sln.AppendLine(line);
			}

			File.WriteAllText(slnPath, sln.ToString(), Encoding.UTF8);
		}
	}
}