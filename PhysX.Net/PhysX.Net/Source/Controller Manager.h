#pragma once

#include "Controller.h"
#include "Element Collection.h"

using namespace System;
namespace StillDesign
{
	namespace PhysX
	{
		ref class Scene;
		ref class ControllerDescription;
		
		public ref class ControllerManager : StillDesign::PhysX::IDisposable
		{
			public:
				virtual event EventHandler^ OnDisposing;
				virtual event EventHandler^ OnDisposed;
				
			private:
				NxControllerManager* _manager;
				StillDesign::PhysX::Scene^ _scene;
				
				ElementCollection<StillDesign::PhysX::Controller^>^ _controllers;
				
				Object^ _userData;
				
				String^ _name;
			
			internal:
				ControllerManager( NxControllerManager* manager, StillDesign::PhysX::Scene^ scene );
			public:
				~ControllerManager();
			protected:
				!ControllerManager();
			public:
				property bool IsDisposed
				{
					virtual bool get();
				}
			
			public:
				generic<class T>
				where T : StillDesign::PhysX::Controller
				T CreateController( ControllerDescription^ controllerDescription );
				/// <summary></summary>
				StillDesign::PhysX::Controller^ CreateController( ControllerDescription^ controllerDescription );
				
				/// <summary></summary>
				void UpdateControllers();
				
				//
				
				/// <summary></summary>
				property StillDesign::PhysX::Scene^ Scene
				{
					StillDesign::PhysX::Scene^ get();
				}
				
				/// <summary>Gets the Collection of Controller</summary>
				property ReadOnlyList< Controller^ >^ Controllers
				{
					ReadOnlyList< Controller^ >^ get();
				}
				
				/// <summary></summary>
				property String^ Name
				{
					String^ get();
					void set( String^ value );
				}
				
				/// <summary></summary>
				property Object^ UserData
				{
					virtual Object^ get();
					virtual void set( Object^ value );
				}
			
			internal:
				property NxControllerManager* UnmanagedPointer
				{
					NxControllerManager* get();
				}
		};
	};
};