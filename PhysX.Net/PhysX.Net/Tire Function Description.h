#pragma once

namespace StillDesign
{
	namespace PhysX
	{
		public value class TireFunctionDescription
		{
			private:
				float _extremumSlip;
				float _extremumValue;
				float _asymptoteSlip;
				float _asymptoteValue;
				float _stiffnessFactor;
				
			internal:
				static explicit operator TireFunctionDescription( NxTireFunctionDesc desc );
				static explicit operator NxTireFunctionDesc( TireFunctionDescription desc );
				
			public:
				/// <summary>Resets the structure to the default.</summary>
				void SetToDefault();
				/// <summary>Returns true if the current settings are valid.</summary>
				bool IsValid();
				/// <summary>Evaluates the Force(Slip) function.</summary>
				float HermiteEvaluation( float t );
				
				//
				
				property TireFunctionDescription Default
				{
					static TireFunctionDescription get();
				}
				
				/// <summary>Extremal point of curve. Both values must be positive.</summary>
				property float ExtremumSlip
				{
					float get();
					void set( float value );
				}
				/// <summary>Extremal point of curve. Both values must be positive.</summary>
				property float ExtremumValue
				{
					float get();
					void set( float value );
				}
				/// <summary>Point on curve at which for all x > minumumX, function equals minimumY. Both values must be positive</summary>
				property float AsymptoteSlip
				{
					float get();
					void set( float value );
				}
				/// <summary>Point on curve at which for all x > minumumX, function equals minimumY. Both values must be positive.</summary>
				property float AsymptoteValue
				{
					float get();
					void set( float value );
				}
				/// <summary>Scaling factor for tire force.</summary>
				property float StiffnessFactor
				{
					float get();
					void set( float value );
				}
		};
	};
};