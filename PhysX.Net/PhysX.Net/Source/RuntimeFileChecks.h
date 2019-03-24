#pragma once

using namespace System;
using namespace System::Reflection;

// Unfortunately they forgot to update the version to 4.1
#define PhysXDllVersion "4.0.0.0"

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