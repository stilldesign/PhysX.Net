#pragma once

using namespace System;
UsingFrameworkNamespace

namespace StillDesign
{
	namespace PhysX
	{
		public ref class Description abstract
		{
			public:
				/// <summary>Returns 0 if the current settings are valid.</summary>
				virtual int CheckValid() = 0;
		};
	};
};