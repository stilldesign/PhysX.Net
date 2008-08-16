#pragma once

namespace StillDesign
{
	namespace PhysX
	{
		namespace Utilities
		{
			public ref class ParameterDescription
			{
				private:
					NXU::ParameterDesc* _desc;
					
				public:
					ParameterDescription();
					~ParameterDescription();
				protected:
					!ParameterDescription();
					
				public:
					
			};
		};
	};
};