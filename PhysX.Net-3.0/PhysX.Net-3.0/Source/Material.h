#pragma once

#include <PxMaterial.h>
#include "MaterialEnum.h"

using namespace PhysX::MathPrimitives;

namespace PhysX
{
	public ref class Material
	{
		private:
			PxMaterial* _material;
			Object^ _userData;

		internal:
			Material(PxMaterial* material);
		public:
			~Material();
		protected:
			!Material();
			
		public:
			property bool Disposed
			{
				bool get();
			}

			/// <summary>Gets or sets the coefficient of dynamic friction.</summary>
			property float DynamicFriction
			{
				float get();
				void set(float value);
			}
			/// <summary>Gets or sets the dynamic friction coefficient for the V direction.</summary>
			property float DynamicFrictionV
			{
				float get();
				void set(float value);
			}
			/// <summary>Gets or sets the coefficient of static friction.</summary>
			property float StaticFriction
			{
				float get();
				void set(float value);
			}
			/// <summary>Gets or sets the static friction coefficient along the secondary (V) axis.</summary>
			property float StaticFrictionV
			{
				float get();
				void set(float value);
			}
				
			/// <summary>Gets or sets the coefficient of restitution.</summary>
			property float Restitution
			{
				float get();
				void set(float value);
			}
			
			/// <summary>Gets or sets the shape space direction (unit vector) of anisotropy.</summary>
			property Vector3 DirectionOfAnisotropy
			{
				Vector3 get();
				void set(Vector3 value);
			}
				
			/// <summary>Get or sets the material flags (a combination of <see cref="MaterialFlag" />).</summary>
			property MaterialFlag Flags
			{
				MaterialFlag get();
				void set(MaterialFlag value);
			}
			/// <summary>Gets or sets the the friction combine mode.</summary>
			property CombineMode FrictionCombineMode
			{
				CombineMode get();
				void set(CombineMode value);
			}
			/// <summary>Gets or sets the restitution combine mode.</summary>
			property CombineMode RestitutionCombineMode
			{
				CombineMode get();
				void set(CombineMode value);
			}

			/// <summary>Gets or sets an object, usually to create a 1:1 relationship with a user object.</summary>
			property Object^ UserData
			{
				Object^ get();
				void set( Object^ value );
			}

		internal:
			property PxMaterial* UnmanagedPointer
			{
				PxMaterial* get();
			}
	};
};