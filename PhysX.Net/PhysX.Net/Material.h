#pragma once

#include "Material Enums.h"
#include "IDisposable.h"

using namespace System;
UsingFrameworkNamespace

class NxMaterial;
class NxMaterialDesc;

namespace StillDesign
{
	namespace PhysX
	{
		ref class Scene;
		ref class MaterialDescription;
		
		public ref class Material : StillDesign::PhysX::IDisposable
		{
			public:
				virtual event EventHandler^ onDisposing;
				virtual event EventHandler^ onDisposed;

			private:
				NxMaterial* _material;
				
				StillDesign::PhysX::Scene^ _scene;
				
				String^ _name;
				Object^ _userData;
				
			internal:
				Material( NxMaterial* material );
			public:
				~Material();
			protected:
				!Material();
			public:
				/// <summary>Is the Material Disposed</summary>
				property bool IsDisposed
				{
					virtual bool get();
				}
			
			public:
				/// <summary>Saves the state of the material into a descriptor</summary>
				MaterialDescription^ SaveToDescription();
				/// <summary>Loads the entire state of the material from a descriptor with a single call</summary>
				void LoadFromDescription( MaterialDescription^ description );
				
				/// <summary>Gets the scene the material is owned by</summary>
				property StillDesign::PhysX::Scene^ Scene
				{
					StillDesign::PhysX::Scene^ get();
				}
				/// <summary>Gets the Index/ID of the Material</summary>
				property int Index
				{
					int get();
				}
				
				/// <summary>Gets or Set the name of the material</summary>
				property String^ Name
				{
					String^ get();
					virtual void set( String^ name );
				}
				
				/// <summary>Gets or Set the dynamic friction</summary>
				property float DynamicFriction
				{
					float get();
					void set( float value );
				}
				/// <summary>Gets or Sets the dynamic friction coefficient along the secondary (V) axis</summary>
				property float DynamicFrictionV
				{
					float get();
					void set( float value );
				}
				/// <summary>Retrieves the coefficient of static friction</summary>
				property float StaticFriction
				{
					float get();
					void set( float value );
				}
				/// <summary>Gets or Sets the static friction along the secondary (V) axis</summary>
				property float StaticFrictionV
				{
					float get();
					void set( float value );
				}
				
				/// <summary>Gets or Sets the coefficient of restitution. Restition is amount of bounce the material has</summary>
				property float Restitution
				{
					float get();
					void set( float value );
				}
				
				/// <summary>Gets or Sets the shape space direction (unit vector) of anisotropy</summary>
				property Vector3 DirectionOfAnisotropy
				{
					Vector3 get();
					void set( Vector3 value );
				}
				
				/// <summary>Get or Sets the material flags (a combination of MaterialFlag)</summary>
				property MaterialFlag Flags
				{
					MaterialFlag get();
					void set( MaterialFlag value );
				}
				/// <summary>Gets or Sets the the friction combine mode</summary>
				property CombineMode FrictionCombineMode
				{
					CombineMode get();
					void set( CombineMode value );
				}
				/// <summary>Gets or Sets the restitution combine mode</summary>
				property CombineMode RestitutionCombineMode
				{
					CombineMode get();
					void set( CombineMode value );
				}
				
				property Object^ UserData
				{
					Object^ get();
					void set( Object^ value );
				}
				
			internal:
				/// <summary>Gets the Unmanaged Pointer to the Underlying NxMaterial</summary>
				property NxMaterial* UnmanagedPointer
				{
					NxMaterial* get();
				}
		};
	};
};