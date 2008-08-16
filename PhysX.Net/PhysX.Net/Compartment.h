#pragma once

#include "Enums.h"
#include "IDisposable.h"

UsingFrameworkNamespace

namespace StillDesign
{
	namespace PhysX
	{
		ref class Scene;
		ref class CompartmentDescription;
		value class SceneTimingInformation;
		
		public ref class Compartment : IDisposable
		{
			public:
				virtual event EventHandler^ onDisposing;
				virtual event EventHandler^ onDisposed;
			
			private:
				NxCompartment* _compartment;
				
				StillDesign::PhysX::Scene^ _scene;
			
			internal:
				Compartment( NxCompartment* compartment, StillDesign::PhysX::Scene^ scene );
			public:
				~Compartment();
			protected:
				!Compartment();
			public:
				property bool IsDisposed
				{
					virtual bool get();
				}
			
			public:
				/// <summary>Saves the compartment to a descriptor</summary>
				/// <remarks>Please note that the device code will be the same as the value returned by getDeviceCode(), i.e. not necessarily the same as the value you assigned when first creating the compartment (when using auto-assign).</remarks>
				CompartmentDescription^ SaveToDescription();
				
				/// <summary>This checks to see if the simulation of the objects in this compartment has completed</summary>
				bool CheckResults();
				/// <summary>This checks to see if the simulation of the objects in this compartment has completed</summary>
				/// <param name="block">When set to true will block until the condition is met</param>
				bool CheckResults( bool block );
				
				/// <summary>This is the big brother to checkResults() it basically makes the results of the compartment's simulation readable</summary>
				bool FetchResults();
				/// <summary>This is the big brother to checkResults() it basically makes the results of the compartment's simulation readable</summary>
				/// <param name="block">When set to true will block until the condition is met</param>
				bool FetchResults( bool block );
				
				/// <summary>Gets the scene the compartment belongs to</summary>
				property StillDesign::PhysX::Scene^ Scene
				{
					StillDesign::PhysX::Scene^ get();
				}
				/// <summary>Gets the compartment simulation type</summary>
				property CompartmentType Type
				{
					CompartmentType get();
				}
				/// <summary>The device code that is specified when creating a compartment or the automatically assigned device code, if NX_DC_PPU_AUTO_ASSIGN was used</summary>
				property StillDesign::PhysX::DeviceCode DeviceCode
				{
					StillDesign::PhysX::DeviceCode get();
				}
				/// <summary>Gets the paging grid cell size</summary>
				property float GridHashCellSize
				{
					float get();
				}
				/// <summary>Gets or Sets the compartment flags</summary>
				property CompartmentFlag Flags
				{
					CompartmentFlag get();
					void set( CompartmentFlag value );
				}
				/// <summary>Gets or Sets the time scale for the compartment</summary>
				property float Timescale
				{
					float get();
					void set( float value );
				}
				/// <summary>Get or Sets simulation timing parameters used to simulate the compartment</summary>
				property SceneTimingInformation Timing
				{
					SceneTimingInformation get();
					void set( SceneTimingInformation value );
				}
			
			internal:
				property NxCompartment* UnmanagedPointer
				{
					NxCompartment* get();
				}
		};
	};
};