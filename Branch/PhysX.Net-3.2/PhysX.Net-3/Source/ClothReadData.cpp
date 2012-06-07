#include "StdAfx.h"
#include "ClothReadData.h"

ClothReadData::ClothReadData(PxClothReadData* data, int particleCount)
	: LockedData(data)
{
	int n = particleCount;

	if (n == 0)
	{
		this->Particles = gcnew array<ClothParticle>(0);
		this->PreviousParticles = gcnew array<ClothParticle>(0);
	}
	else
	{
		auto p = gcnew array<ClothParticle>(n);
		auto pp = gcnew array<ClothParticle>(n);

		pin_ptr<ClothParticle> p_pin = &p[0];
		pin_ptr<ClothParticle> pp_pin = &pp[0];

		memcpy_s(p_pin, n*sizeof(PxClothParticle), data->particles, n*sizeof(PxClothParticle));
		memcpy_s(pp_pin, n*sizeof(PxClothParticle), data->previousParticles, n*sizeof(PxClothParticle));

		this->Particles = p;
		this->PreviousParticles = pp;
	}
}