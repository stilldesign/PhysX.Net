#pragma once

using namespace System;
using namespace System::Reflection;

#define RequiredDllVersion "2.8.3.21"

namespace StillDesign
{
	namespace PhysX
	{
		private ref class RuntimeFileChecks
		{
			public:
				static void Check();
				
			private:
				static void CheckFile( String^ filename );
				
				static String^ FindLibraryPath( System::String^ name );
				static Assembly^ GetBestAssembly();
				
				static String^ GetEnvironmentPathVariable( String^ name );
				
				static Version^ GetFileVersion( String^ filename );
		};
	};
};