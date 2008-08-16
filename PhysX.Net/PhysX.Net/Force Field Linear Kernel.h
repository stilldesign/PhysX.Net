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
				/// <summary></summary>
				ForceFieldLinearKernelDescription^ SaveToDescription();
				
				/// <summary></summary>
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
				
				/// <summary></summary>
				property Vector3 Constant
				{
					Vector3 get();
					void set( Vector3 value );
				}
				/// <summary></summary>
				property Matrix PositionMultiplier
				{
					Matrix get();
					void set( Matrix value );
				}
				/// <summary></summary>
				property Vector3 PositionTarget
				{
					Vector3 get();
					void set( Vector3 value );
				}
				/// <summary></summary>
				property Matrix VelocityMultiplier
				{
					Matrix get();
					void set( Matrix value );
				}
				/// <summary></summary>
				property Vector3 VelocityTarget
				{
					Vector3 get();
					void set( Vector3 value );
				}
				/// <summary></summary>
				property Vector3 FalloffLinear
				{
					Vector3 get();
					void set( Vector3 value );
				}
				/// <summary></summary>
				property Vector3 FalloffQuadratic
				{
					Vector3 get();
					void set( Vector3 value );
				}
				/// <summary></summary>
				property float TorusRadius
				{
					float get();
					void set( float value );
				}
				/// <summary></summary>
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