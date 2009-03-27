#pragma once

#include "Enums.h"
#include "Controller Enums.h"

using namespace System;

UsingFrameworkNamespace

namespace StillDesign
{
	namespace PhysX
	{
		ref class Actor;
		ref class UserControllerHitReport;
		
		public delegate ControllerAction ControllerActionHandler();
		
		public ref class ControllerDescription abstract
		{
			private:
				NxControllerDesc* _desc;
				
				UserControllerHitReport^ _hitReport;
			
			protected:
				ControllerDescription( NxControllerDesc* controllerDesc );
			public:
				~ControllerDescription();
			protected:
				!ControllerDescription();
				
			public:
				/// <summary>Is the Description Settings Valid</summary>
				bool IsValid();
				void SetToDefault();
				
				/// <summary>Gets the Character Controller Type</summary>
				property ControllerType Type
				{
					ControllerType get();
				}
				
				/// <summary>Gets or Sets the Position of the Character</summary>
				property Vector3 Position
				{
					Vector3 get();
					void set( Vector3 value );
				}
				/// <summary>Gets or Sets the Maximum Slope Which the Character Can Walk Up</summary>
				property float SlopeLimit
				{
					float get();
					void set( float value );
				}
				/// <summary>Gets or Sets the Skin Width Used by the Controller</summary>
				property float SkinWidth
				{
					float get();
					void set( float value );
				}
				/// <summary>Defines the Maximum Height of an Obstacle Which the Character Can Climb</summary>
				property float StepOffset
				{
					float get();
					void set( float value );
				}
				/// <summary>Gets or Sets the Interaction Flag. This Controls how a Character Controller Collides with Other Controllers</summary>
				property CCTInteractionFlag InteractionFlag
				{
					CCTInteractionFlag get();
					void set( CCTInteractionFlag value );
				}
				
				/// <summary>Gets or Sets the 'Up' Direction</summary>
				property Axis UpDirection
				{
					Axis get();
					void set( Axis value );
				}
				
				/// <summary></summary>
				property UserControllerHitReport^ Callback
				{
					UserControllerHitReport^ get();
					void set( UserControllerHitReport^ value );
				}
				
			internal:
				/// <summary>Gets the Unmanaged Pointer to the NxControllerDesc</summary>
				property NxControllerDesc* UnmanagedPointer
				{
					NxControllerDesc* get();
				}
		};
	};
};