#pragma once

using namespace System;
using namespace System::Reflection;

#define PhysXDllVersion "2.8.4.4"
#define PhysXDeviceDllVersion "10.7.1.0"
#define CudaDllVersion "6.14.11.3000"

namespace StillDesign
{
	namespace PhysX
	{
		private ref class RuntimeFileChecks
		{
			public:
				static void Check();
				
			private:
				static void CheckFile( String^ filename, String^ requiredVersion );
				static void CheckFile( String^ filename, Version^ requiredVersion );
				
				static String^ FindLibraryPath( System::String^ name );
				static Assembly^ GetBestAssembly();
				
				static String^ GetEnvironmentPathVariable( String^ name );
				
				static Version^ GetFileVersion( String^ filename );
		};
	};
};