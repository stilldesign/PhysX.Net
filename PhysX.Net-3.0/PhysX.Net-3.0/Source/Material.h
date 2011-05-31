#pragma once

#include <PxMaterial.h>
#include "MaterialEnum.h"
#include "PhysicsEnum.h"

using namespace PhysX::Math;

namespace PhysX
{
	ref class Physics;

	public ref class Material : IDisposable
	{
		public:
			virtual event EventHandler^ OnDisposing;
			virtual event EventHandler^ OnDisposed;

		private:
			PxMaterial* _material;

		internal:
			Material(PxMaterial* material, PhysX::Physics^ owner);
		public:
			~Material();
		protected:
			!Material();
			
		public:
			property bool Disposed
			{
				virtual bool get();
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
			property Object^ UserData;

		internal:
			property PxMaterial* UnmanagedPointer
			{
				PxMaterial* get();
			}
	};
};