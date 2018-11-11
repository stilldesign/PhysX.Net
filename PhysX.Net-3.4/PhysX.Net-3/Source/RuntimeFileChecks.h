#pragma once

using namespace System;
using namespace System::Reflection;

// It's technically 3.4.2, but the version number hasn't been updated correctly - hopefully it will be in the future.
#define PhysXDllVersion "3.4.1.0"
#define FoundationDllVersion "1.0.0.0"
#define PvdDllVersion "1.0.0.0"

namespace PhysX
{
	/// <summary>
	/// Methods to make sure the correct versions of the native PhysX DLLs are being loaded.
	/// </summary>
	private ref class RuntimeFileChecks
	{
		public:
			static void Check();

		private:
			static void CheckFile(String^ filename, String^ requiredVersion);
			static void CheckFile(String^ filename, Version^ requiredVersion);

			static String^ FindLibraryPath(String^ name);
			static Assembly^ GetBestAssembly();

			static String^ GetEnvironmentPathVariable(String^ name);

			static Version^ GetFileVersion(String^ filename);
	};
};