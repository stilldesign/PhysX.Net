#pragma once

#include "Enums.h"

namespace StillDesign
{
	namespace PhysX
	{
		public value class SceneTimingInformation
		{
			private:
				float _maxTimestep;
				int _maxIterations;
				TimestepMethod _timestepMethod;
				int _subSteps;
			
			public:
				property float MaximumTimestep
				{
					float get();
					void set( float value );
				}
				property int MaximumIterations
				{
					int get();
					void set( int value );
				}
				property PhysX::TimestepMethod TimestepMethod
				{
					PhysX::TimestepMethod get();
					void set( PhysX::TimestepMethod value );
				}
				property int NumberOfSubSteps
				{
					int get();
					void set( int value );
				}
		};
	};
};