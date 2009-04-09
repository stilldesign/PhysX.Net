#pragma once

#include "Enums.h"
#include "IDisposable.h"

using namespace System;
using namespace System::Collections::Generic;

UsingFrameworkNamespace

namespace StillDesign
{
	namespace PhysX
	{
		ref class BodyDescription;
		ref class Actor;
		ref class ShapeDescription;
		ref class Compartment;
		
		public ref class ActorDescriptionBase abstract : StillDesign::PhysX::IDisposable
		{
			public:
				virtual event EventHandler^ OnDisposing;
				virtual event EventHandler^ OnDisposed;
				
			private:
				NxActorDescBase* _desc;
				
				StillDesign::PhysX::BodyDescription^ _body;
				StillDesign::PhysX::Compartment^ _compartment;
				
				Object^ _userData;
				
			protected:
				ActorDescriptionBase();
			public:
				~ActorDescriptionBase();
			protected:
				!ActorDescriptionBase();
			public:
				property bool IsDisposed
				{
					virtual bool get();
				}
				
				/// <summary>Is the description valid</summary>
				virtual bool IsValid();
				/// <summary>Sets the structure to a default state</summary>
				virtual void SetToDefault();
				
			public:
				property String^ Name
				{
					String^ get();
					void set( String^ value );
				}
				property ActorDescriptionType Type
				{
					virtual ActorDescriptionType get();
				}
				
				property StillDesign::PhysX::BodyDescription^ BodyDescription
				{
					StillDesign::PhysX::BodyDescription^ get();
					void set( StillDesign::PhysX::BodyDescription^ value );
				}
				
				/// <summary>Gets or Sets the compartment to place the actor in. Must be of type RigidBody. A null compartment means creating the actor in the scene proper.</summary>
				property StillDesign::PhysX::Compartment^ Compartment
				{
					StillDesign::PhysX::Compartment^ get();
					void set( StillDesign::PhysX::Compartment^ value );
				}
				
				/// <summary>Gets or Sets the Density of the Actor Description</summary>
				property float Density
				{
					float get();
					void set( float value );
				}
				property ActorFlag Flags
				{
					ActorFlag get();
					void set( ActorFlag value );
				}
				property short Group
				{
					short get();
					void set( short value );
				}
				property short DominanceGroup
				{
					short get();
					void set( short value );
				}
				property ContactPairFlag ContactReportFlags
				{
					ContactPairFlag get();
					void set( ContactPairFlag value );
				}
				property ContactPairFlag ContactPairFlags
				{
					ContactPairFlag get();
					void set( ContactPairFlag value );
				}
				property short ForceFieldMaterial
				{
					short get();
					void set( short value );
				}
				
				property Matrix GlobalPose
				{
					Matrix get();
					void set( Matrix value );
				}
				
				property Object^ UserData
				{
					Object^ get();
					void set( Object^ value );
				}
				
			internal:
				property NxActorDescBase* UnmanagedPointer
				{
					NxActorDescBase* get();
				}
		};
	};
};