#include "StdAfx.h"

#include "Tire Function Description.h"

using namespace StillDesign::PhysX;

TireFunctionDescription::operator TireFunctionDescription( NxTireFunctionDesc desc )
{
	TireFunctionDescription d;
		d.ExtremumSlip = desc.extremumSlip;
		d.ExtremumValue = desc.extremumValue;
		d.AsymptoteSlip = desc.asymptoteSlip;
		d.AsymptoteValue = desc.asymptoteValue;
		d.StiffnessFactor = desc.stiffnessFactor;
	
	return d;
}
TireFunctionDescription::operator NxTireFunctionDesc( TireFunctionDescription desc )
{
	NxTireFunctionDesc d;
		d.extremumSlip = desc.ExtremumSlip;
		d.extremumValue = desc.ExtremumValue;
		d.asymptoteSlip = desc.AsymptoteSlip;
		d.asymptoteValue = desc.AsymptoteValue;
		d.stiffnessFactor = desc.StiffnessFactor;
	
	return d;
}

TireFunctionDescription TireFunctionDescription::Default::get()
{
	TireFunctionDescription desc;
		desc.SetToDefault();
	
	return desc;
}

void TireFunctionDescription::SetToDefault()
{
	_extremumSlip = 1.0f;
	_extremumValue = 0.02f;
	_asymptoteSlip = 2.0f;
	_asymptoteValue = 0.01f;	
	_stiffnessFactor = 1000000.0f;	//quite stiff by default.
}
bool TireFunctionDescription::IsValid()
{
	if(!(0.0f < _extremumSlip))
		return DescriptorValidity::Invalid( "!(0.0f < _extremumSlip)" );
		
	if(!(_extremumSlip < _asymptoteSlip))	
		return DescriptorValidity::Invalid( "!(_extremumSlip < _asymptoteSlip)" );
		
	if(!(0.0f < _extremumValue))
		return DescriptorValidity::Invalid( "!(0.0f < _extremumValue)" );
		
	if(!(0.0f < _asymptoteValue))
		return DescriptorValidity::Invalid( "!(0.0f < _asymptoteValue)" );
		
	if(!(0.0f <= _stiffnessFactor))
		return DescriptorValidity::Invalid( "!(0.0f <= _stiffnessFactor)" );
	
	return true;
}
float TireFunctionDescription::HermiteEvaluation( float t )
{

	// This fix for TTP 3429 & 3675 is from Sega.
	// Assume blending functions (look these up in a graph):
	// H0(t) =  2ttt - 3tt + 1
	// H1(t) = -2ttt + 3tt
	// H2(t) =   ttt - 2tt + t
	// H3(t) =   ttt -  tt 

	NxReal v = NxMath::abs(t);
	NxReal s = (t>=0) ? 1.0f : -1.0f;

	NxReal F;

	if(v<_extremumSlip)
		{
		// For t in the interval 0 < t < extremumSlip
		// We normalize t:
		// a = t/extremumSlip;
		// and use H1 + H2 to compute F:
		// F = extremumValue * ( H1(a) + H2(a) )

		NxReal a = v/_extremumSlip;
		NxReal a2 = a*a;
		NxReal a3 = a*a2;

		F = _extremumValue * (-a3 + a2 + a);
		}
	else
		{
		if(v<_asymptoteSlip)
			{
			// For the interval extremumSlip <= t < asymtoteSlip
			// We normalize and remap t:
			// a = (t-extremumSlip)/(asymptoteSlip - extremumSlip)
			// and use H0 to compute F:
			// F = extremumValue + (extremumValue - asymtoteValue) * H0(a)
			// note that the above differs from the actual expression but this is how it looks with H0 factorized.
				
			NxReal a = (v-_extremumSlip)/(_asymptoteSlip - _extremumSlip);
			NxReal a2 = a*a;
			NxReal a3 = a*a2;

			NxReal diff = _asymptoteValue - _extremumValue;
			F = -2.0f*diff*a3 + 3.0f*diff*a2 + _extremumValue;
			}
		else
			{
			F = _asymptoteValue;
			}
		}
	return s*F;
}

float TireFunctionDescription::ExtremumSlip::get()
{
	return _extremumSlip;
}
void TireFunctionDescription::ExtremumSlip::set( float value )
{
	_extremumSlip = value;
}

float TireFunctionDescription::ExtremumValue::get()
{
	return _extremumValue;
}
void TireFunctionDescription::ExtremumValue::set( float value )
{
	_extremumValue = value;
}

float TireFunctionDescription::AsymptoteSlip::get()
{
	return _asymptoteSlip;
}
void TireFunctionDescription::AsymptoteSlip::set( float value )
{
	_asymptoteSlip = value;
}

float TireFunctionDescription::AsymptoteValue::get()
{
	return _asymptoteValue;
}
void TireFunctionDescription::AsymptoteValue::set( float value )
{
	_asymptoteValue = value;
}

float TireFunctionDescription::StiffnessFactor::get()
{
	return _stiffnessFactor;
}
void TireFunctionDescription::StiffnessFactor::set( float value )
{
	_stiffnessFactor = value;
}