#include "StdAfx.h"
#include "ClothFabric.h"
#include "Serializable.h"

ClothFabric::ClothFabric(PxClothFabric* clothFabric, PhysX::Physics^ owner)
{
	if (clothFabric == NULL)
		throw gcnew ArgumentNullException("clothFabric");
	ThrowIfNullOrDisposed(owner, "owner");

	_clothFabric = clothFabric;

	ObjectTable::Add((intptr_t)_clothFabric, this, owner);
}
ClothFabric::~ClothFabric()
{
	this->!ClothFabric();
}
ClothFabric::!ClothFabric()
{
	OnDisposing(this, nullptr);

	if (this->Disposed)
		return;

	_clothFabric->release();
	_clothFabric = NULL;

	OnDisposed(this, nullptr);
}

bool ClothFabric::Disposed::get()
{
	return (_clothFabric == NULL);
}

Serializable^ ClothFabric::AsSerializable()
{
	return gcnew Serializable(_clothFabric);
}

array<int>^ ClothFabric::GetPhases()
{
	int n = _clothFabric->getNbPhases();
	PxU32* buffer;
	
	try
	{
		buffer = new PxU32[n];

		PxU32 c = _clothFabric->getPhases(buffer, n);

		if (c == 0)
			return nullptr;

		return Util::AsManagedArray<int>(buffer, c);
	}
	finally
	{
		delete[] buffer;
	}
}

array<int>^ ClothFabric::GetSets()
{
	int n = _clothFabric->getNbSets();
	PxU32* buffer;
	
	try
	{
		buffer = new PxU32[n];

		PxU32 c = _clothFabric->getSets(buffer, n);

		if (c == 0)
			return nullptr;

		return Util::AsManagedArray<int>(buffer, c);
	}
	finally
	{
		delete[] buffer;
	}
}

array<int>^ ClothFabric::GetFibers()
{
	int n = _clothFabric->getNbFibers();
	PxU32* buffer;
	
	try
	{
		buffer = new PxU32[n];

		PxU32 c = _clothFabric->getFibers(buffer, n);

		if (c == 0)
			return nullptr;

		return Util::AsManagedArray<int>(buffer, c);
	}
	finally
	{
		delete[] buffer;
	}
}

array<int>^ ClothFabric::GetParticleIndices()
{
	int n = _clothFabric->getNbParticleIndices();
	PxU32* buffer;
	
	try
	{
		buffer = new PxU32[n];

		PxU32 c = _clothFabric->getParticleIndices(buffer, n);

		if (c == 0)
			return nullptr;

		return Util::AsManagedArray<int>(buffer, c);
	}
	finally
	{
		delete[] buffer;
	}
}

array<float>^ ClothFabric::GetRestValues()
{
	int n = _clothFabric->getNbRestvalues();
	float* buffer;
	
	try
	{
		buffer = new float[n];

		int c = _clothFabric->getRestvalues(buffer, n);

		if (c == 0)
			return nullptr;

		return Util::AsManagedArray<float>(buffer, c);
	}
	finally
	{
		delete[] buffer;
	}
}

ClothFabricPhaseType ClothFabric::GetPhaseType(int phaseIndex)
{
	return ToManagedEnum(ClothFabricPhaseType, _clothFabric->getPhaseType(phaseIndex));
}

void ClothFabric::ScaleRestValues(ClothFabricPhaseType phaseType, float scale)
{
	_clothFabric->scaleRestvalues(ToUnmanagedEnum(PxClothFabricPhaseType, phaseType), scale);
}

int ClothFabric::NumberOfParticles::get()
{
	return _clothFabric->getNbParticles();
}

int ClothFabric::NumberOfPhases::get()
{
	return _clothFabric->getNbPhases();
}

int ClothFabric::NumberOfRestValues::get()
{
	return _clothFabric->getNbRestvalues();
}

int ClothFabric::NumberOfSets::get()
{
	return _clothFabric->getNbSets();
}

int ClothFabric::NumberOfFibers::get()
{
	return _clothFabric->getNbFibers();
}

int ClothFabric::NumberOfParticleIndices::get()
{
	return _clothFabric->getNbParticleIndices();
}

int ClothFabric::ReferenceCount::get()
{
	return _clothFabric->getReferenceCount();
}

PxClothFabric* ClothFabric::UnmanagedPointer::get()
{
	return _clothFabric;
}