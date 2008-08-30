#pragma once

namespace StillDesign
{
	namespace PhysX
	{
		private ref class RuntimeFileChecks
		{
			public:
				static bool Check();
				
			private:
				static bool CheckFile( String^ filename, ... array<int>^ hash );
		};
	};
};