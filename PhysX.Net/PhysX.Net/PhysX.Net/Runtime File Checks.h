#pragma once

using namespace System;
using namespace System::Reflection;

namespace StillDesign
{
	namespace PhysX
	{
		private ref class RuntimeFileChecks
		{
			public:
				static void Check();
				
			private:
				static void CheckFile( String^ filename, array<Byte>^ knownHash );
				
				static String^ FindLibraryPath( System::String^ name );
				static Assembly^ GetBestAssembly();
				
				static String^ GetEnvironmentPathVariable( String^ name );
				
				static bool CompareHash( array<Byte>^ a, array<Byte>^ b );
		};
	};
};