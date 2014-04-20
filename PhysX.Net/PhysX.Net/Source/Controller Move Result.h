#pragma once

#include "Controller Enums.h"
#include "Enums.h"

using namespace System;

namespace StillDesign
{
	namespace PhysX
	{
		ref class Actor;
	
		ref class ControllerDescription;
		
		public ref class ControllerMoveResult
		{
			private:
				ControllerCollisionFlag _collision;
			
			public:
				ControllerMoveResult( ControllerCollisionFlag collision );
				
				property ControllerCollisionFlag CollisionFlag
				{
					ControllerCollisionFlag get();
				}
		};
	};
};