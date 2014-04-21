#pragma once

#include "Force Field Kernel.h"

class NxForceFieldLinearKernel;

namespace StillDesign
{
	namespace PhysX
	{
		ref class Scene;
		ref class ForceFieldLinearKernelDescription;
		
		public ref class ForceFieldLinearKernel : ForceFieldKernel
		{
			private:
				StillDesign::PhysX::Scene^ _scene;
			
			internal:
				ForceFieldLinearKernel( NxForceFieldLinearKernel* kernel );
			
			public:
				/// <summary>Writes all of the kernel's attributes to the description, as well as setting the actor connection point</summary>
				ForceFieldLinearKernelDescription^ SaveToDescription();
				
				/// <summary>Retrieves the scene which this kernel belongs to</summary>
				property StillDesign::PhysX::Scene^ Scene
				{
					StillDesign::PhysX::Scene^ get();
				}
				
				/// <summary></summary>
				property String^ Name
				{
					String^ get();
					void set( String^ value );
				}
				
				/// <summary>Gets or Sets the constant part of force field function</summary>
				property Vector3 Constant
				{
					Vector3 get();
					void set( Vector3 value );
				}
				/// <summary>Gets or Sets the coefficient of force field function position term</summary>
				property Matrix PositionMultiplier
				{
					Matrix get();
					void set( Matrix value );
				}
				/// <summary>Gets or Sets the force field position target</summary>
				property Vector3 PositionTarget
				{
					Vector3 get();
					void set( Vector3 value );
				}
				/// <summary>Gets or Sets the coefficient of force field function velocity term</summary>
				property Matrix VelocityMultiplier
				{
					Matrix get();
					void set( Matrix value );
				}
				/// <summary>Gets or Sets the force field velocity target</summary>
				property Vector3 VelocityTarget
				{
					Vector3 get();
					void set( Vector3 value );
				}
				/// <summary>Gets or Sets the linear falloff term</summary>
				property Vector3 FalloffLinear
				{
					Vector3 get();
					void set( Vector3 value );
				}
				/// <summary>Gets or Sets the quadratic falloff term</summary>
				property Vector3 FalloffQuadratic
				{
					Vector3 get();
					void set( Vector3 value );
				}
				/// <summary>Gets or Sets the toroidal radius</summary>
				property float TorusRadius
				{
					float get();
					void set( float value );
				}
				/// <summary>Gets or Sets the force field noise</summary>
				property Vector3 Noise
				{
					Vector3 get();
					void set( Vector3 value );
				}
				
			internal:
				property NxForceFieldLinearKernel* UnmanagedPointer
				{
					virtual NxForceFieldLinearKernel* get() new;
				}
		};
	};
};