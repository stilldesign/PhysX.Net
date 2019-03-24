#pragma once

#include "MaterialEnum.h"
#include "PhysicsEnum.h"

namespace PhysX
{
	ref class Physics;
	ref class Serializable;

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

			/// <summary>
			/// Gets an object which is responsible for serialization of this type.
			/// </summary>
			Serializable^ AsSerializable();

			virtual String^ ToString() override;

			/// <summary>Gets or sets the coefficient of dynamic friction.</summary>
			property float DynamicFriction
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
			
			/// <summary>Gets or sets the coefficient of restitution.</summary>
			property float Restitution
			{
				float get();
				void set(float value);
			}
				
			/// <summary>Get or sets the material flags (a combination of <see cref="MaterialFlag" />).</summary>
			property MaterialFlags Flags
			{
				MaterialFlags get();
				void set(MaterialFlags value);
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

			property String^ ConcreteTypeName
			{
				String^ get();
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