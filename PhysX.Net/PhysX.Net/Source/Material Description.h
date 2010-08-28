#pragma once

#include "Material Enums.h"
#include "Spring Description.h"
#include "Description.h"

UsingFrameworkNamespace

namespace StillDesign
{
	namespace PhysX
	{
		ref class Material;
		
		public ref class MaterialDescription : Description
		{
			private:
				NxMaterialDesc* _desc;
				
				String^ _name;
			
			public:
				MaterialDescription();
			internal:
				MaterialDescription( NxMaterialDesc* desc );
			public:
				~MaterialDescription();
			protected:
				!MaterialDescription();
			
			public:
				/// <summary>(Re)sets the structure to the default</summary>
				void SetToDefault();
				/// <summary>Returns 0 if the current settings are valid.</summary>
				virtual int CheckValid() override;
				/// <summary>Returns true if the descriptor is valid</summary>
				bool IsValid();
				
				/// <summary>Gets or Sets the name of the material</summary>
				property String^ Name
				{
					String^ get();
					void set( String^ value );
				}
				/// <summary>Gets or Sets the coefficient of dynamic friction</summary>
				property float DynamicFriction
				{
					float get();
					void set( float value );
				}
				/// <summary>Gets or Sets the coefficient of static friction</summary>
				property float StaticFriction
				{
					float get();
					void set( float value );
				}
				/// <summary>Gets or Sets the anisotropic dynamic friction coefficient for along the secondary (V) axis of anisotropy</summary>
				property float DynamicFrictionV
				{
					float get();
					void set( float value );
				}
				/// <summary>Gets or Sets anisotropic static friction coefficient for along the secondary (V) axis of anisotropy</summary>
				property float StaticFrictionV
				{
					float get();
					void set( float value );
				}
				
				/// <summary>Gets or Sets coefficient of restitution</summary>
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
				
				/// <summary>Gets or Sets the material flags (a combination of the bits defined by the enum MaterialFlag)</summary>
				property MaterialFlag Flags
				{
					MaterialFlag get();
					void set( MaterialFlag value );
				}
				/// <summary>Gets or Sets the friction combine mode</summary>
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
			
			internal:
				property NxMaterialDesc* UnmanagedPointer
				{
					NxMaterialDesc* get();
				}
		};
	};
};