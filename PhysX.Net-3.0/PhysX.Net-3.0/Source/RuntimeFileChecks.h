#pragma once

using namespace System;
using namespace System::Reflection;

#define PhysXDllVersion "3.0.2.1"
//#define CudaDllVersion "6.14.11.3000"

namespace PhysX
{
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