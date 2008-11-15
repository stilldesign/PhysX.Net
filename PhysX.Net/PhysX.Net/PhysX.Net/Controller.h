#pragma once

#include "Controller Enums.h"
#include "Enums.h"
#include "IDisposable.h"

using namespace System;

UsingFrameworkNamespace

namespace StillDesign
{
	namespace PhysX
	{
		ref class Actor;
		ref class ControllerManager;
		ref class ControllerDescription;
		ref class ControllerMoveResult;
		
		public ref class Controller abstract : StillDesign::PhysX::IDisposable
		{
			public:
				virtual event EventHandler^ onDisposing;
				virtual event EventHandler^ onDisposed;
				
			private:
				NxController* _controller;
				ControllerManager^ _manager;
				
				StillDesign::PhysX::Actor^ _actor;
				
				Object^ _userData;
				String^ _name;
			
			protected:
				Controller( NxController* controller, ControllerManager^ manager );
			public:
				~Controller();
			protected:
				!Controller();
			public:
				property bool IsDisposed
				{
					virtual bool get();
				}
				
				/// <summary>Moves the controller</summary>
				/// <param name="displacementX">The distance to move the controller in the world space X direction</param>
				/// <param name="displacementY">The distance to move the controller in the world space Y direction</param>
				/// <param name="displacementZ">The distance to move the controller in the world space Z direction</param>
				/// <remarks>Minimum Distance = 0.00001f</remarks>
				ControllerMoveResult^ Move( float displacementX, float displacementY, float displacementZ );
				/// <summary>Moves the Controller</summary>
				/// <param name="displacement">The Distance to Move the Controller in the World Space Direction</param>
				/// <remarks>Minimum Distance = 0.00001f</remarks>
				ControllerMoveResult^ Move( Vector3 displacement );
				/// <summary>Moves the Controller</summary>
				/// <param name="displacement">The Distance to Move the Controller in the World Space Direction</param>
				/// <param name="minimumDistance">The Minimum Travelled Distance to Consider. If Travelled Distance is Smaller, the Character Doesn't Move</param>
				/// <param name="sharpness">This Coefficient Defines the Amount of Smoothing. Ranges from 0.0 (Full Smooting) to 1.0 (No Smoothing)</param>
				ControllerMoveResult^ Move( Vector3 displacement, unsigned int activeGroups, float minimumDistance, float sharpness );
				
				/// <summary>Call this Function When the Scene Has Had Static Actors Added or Modified. The Character Controller Uses Caching in Order to Speed Up Collision Testing, this Caching Can Not Detect when Static Objects have Changed in the Scene.</summary>
				void ReportSceneChanged();
				
				/// <summary>Sets the step height (The maximum height the controller can move up onto)</summary>
				/// <param name="offset">The new step offset for the controller</param>
				void SetStepOffset( float offset );
				/// <summary>Enable or disable collisions for this controller</summary>
				/// <param name="enabled">True to enable collision with the controller</param>
				void SetCollisionEnabled( bool enabled );
				
				//
				
				/// <summary>Gets the controller manager this controller is owned by</summary>
				property StillDesign::PhysX::ControllerManager^ Manager
				{
					StillDesign::PhysX::ControllerManager^ get();
				}
				
				/// <summary>Get the Actor Associated with this Controller</summary>
				property StillDesign::PhysX::Actor^ Actor
				{
					StillDesign::PhysX::Actor^ get();
				}
				
				/// <summary>Gets or Sets the name of the controller</summary>
				property String^ Name
				{
					String^ get();
					void set( String^ value );
				}
				
				/// <summary>The Interaction Flag Controls if a Character Controller Collides with Other Controllers</summary>
				property CCTInteractionFlag InteractionFlag
				{
					CCTInteractionFlag get();
					void set( CCTInteractionFlag value );
				}
				
				/// <summary>Gets or Sets the position of the controller</summary>
				property Vector3 Position
				{
					Vector3 get();
					void set( Vector3 value );
				}
				/// <summary>Gets or Sets the 'up' direction</summary>
				property Vector3 FilteredPosition
				{
					Vector3 get();
				}
				
				/// <summary>Gets or Sets the position of the controller</summary>
				property Vector3 DebugPosition
				{
					Vector3 get();
				}
				/// <summary>Gets or Sets the the type of controller</summary>
				property ControllerType Type
				{
					ControllerType get();
				}
				/// <summary>Gets or Sets an arbitrary 1:1 object</summary>
				property Object^ UserData
				{
					Object^ get();
					void set( Object^ value );
				}
			
			internal:
				property NxController* UnmanagedPointer
				{
					NxController* get();
				}
		};
	};
};