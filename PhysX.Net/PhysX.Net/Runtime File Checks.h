#pragma once

namespace StillDesign
{
	namespace PhysX
	{
		private ref class RuntimeFileChecks
		{
			public:
				static void Check();
				
			private:
				static void CheckFile( String^ filename, ... array<int>^ hash );
				static System::String^ FindLibraryPath( System::String^ name );
		};
	};
};