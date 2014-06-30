#include "StdAfx.h"
#include "VehicleUtilSetup.h"

array<float>^ VehicleUtilSetup::ComputeSprungMasses(array<Vector3>^ sprungMassCoordinates, Vector3 centreOfMass, float totalMass, int gravityDirection)
{
	ThrowIfNull(sprungMassCoordinates, "sprungMassCoordinates");
	if (sprungMassCoordinates->Length == 0)
		return gcnew array<float>(0);

	auto masses = gcnew array<float>(sprungMassCoordinates->Length);

	PxVec3* smc = new PxVec3[sprungMassCoordinates->Length];
	Util::AsUnmanagedArray(sprungMassCoordinates, smc);

	auto sprungMasses = gcnew array<float>(sprungMassCoordinates->Length);
	pin_ptr<float> sprungMassesPin = &sprungMasses[0];

	PxVehicleComputeSprungMasses(sprungMassCoordinates->Length, smc, UV(centreOfMass), totalMass, gravityDirection, sprungMassesPin);

	delete[] smc;

	return sprungMasses;
}