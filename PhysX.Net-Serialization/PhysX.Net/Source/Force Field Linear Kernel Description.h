#pragma once

namespace StillDesign
{
	namespace PhysX
	{
		public ref class ForceFieldLinearKernelDescription
		{
			private:
				NxForceFieldLinearKernelDesc* _desc;
				
				Object^ _userData;
				
			public:
				ForceFieldLinearKernelDescription();
				~ForceFieldLinearKernelDescription();
			protected:
				!ForceFieldLinearKernelDescription();
				
			public:
				void SetToDefault();
				bool IsValid();
				
				/// <summary>Gets the Name of the descriptor</summary>
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
				/// <summary>Gets or Sets the linear term in magnitude falloff factor</summary>
				property Vector3 FalloffLinear
				{
					Vector3 get();
					void set( Vector3 value );
				}
				/// <summary>Gets or Sets the quadratic term in magnitude falloff factor</summary>
				property Vector3 FalloffQuadratic
				{
					Vector3 get();
					void set( Vector3 value );
				}
				/// <summary>Gets or Sets the radius for ForceFieldCoordinates.Toroidal type coordinates</summary>
				property float TorusRadius
				{
					float get();
					void set( float value );
				}
				/// <summary>Gets or Sets the </summary>
				property Vector3 Noise
				{
					Vector3 get();
					void set( Vector3 value );
				}
				
				property Object^ UserData
				{
					Object^ get();
					void set( Object^ value );
				}
				
			internal:
				property NxForceFieldLinearKernelDesc* UnmanagedPointer
				{
					NxForceFieldLinearKernelDesc* get();
				}
		};
	};
};