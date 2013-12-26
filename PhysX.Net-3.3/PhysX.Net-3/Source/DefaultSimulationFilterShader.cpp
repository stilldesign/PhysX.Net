#include "StdAfx.h"
#include "PhysicsEnum.h"
#include "FilterData.h"
#include "RigidActor.h"
#include "SimulationFilterShaderOps.h"
#include "DefaultSimulationFilterShader.h"

DefaultSimulationFilterShader::DefaultSimulationFilterShader()
{

}

FilterFlag DefaultSimulationFilterShader::Setup(int attributes0, FilterData filterData0, int attributes1, FilterData filterData1, PairFlag pairFlags, array<Byte>^ constantBlock)
{
	PxPairFlags pf = ToUnmanagedEnum(PxPairFlag, pairFlags);

	auto f = PxDefaultSimulationFilterShader(
		attributes0,
		FilterData::ToUnmanaged(filterData0),
		attributes1,
		FilterData::ToUnmanaged(filterData1),
		pf,
		NULL,
		0);

	return ToManagedEnum(FilterFlag, f);
}

bool DefaultSimulationFilterShader::GetGroupCollisionFlag(int group1, int group2)
{
	return PxGetGroupCollisionFlag(group1, group2);
}
void DefaultSimulationFilterShader::SetGroupCollisionFlag(int group1, int group2, bool enable)
{
	PxSetGroupCollisionFlag(group1, group2, enable);
}

int DefaultSimulationFilterShader::GetGroup(RigidActor^ actor)
{
	ThrowIfNullOrDisposed(actor, "actor");

	return (int)PxGetGroup(*actor->UnmanagedPointer);
}
void DefaultSimulationFilterShader::SetGroup(RigidActor^ actor, int collisionGroup)
{
	ThrowIfNullOrDisposed(actor, "actor");

	PxSetGroup(*actor->UnmanagedPointer, (PxU16)collisionGroup);
}

SimulationFilterShaderOps DefaultSimulationFilterShader::FilterOps::get()
{
	PxFilterOp::Enum op0, op1, op2;

	PxGetFilterOps(op0, op1, op2);

	auto managed = SimulationFilterShaderOps();
		managed.Op0 = ToManagedEnum(FilterOp, op0);
		managed.Op1 = ToManagedEnum(FilterOp, op1);
		managed.Op2 = ToManagedEnum(FilterOp, op2);

	return managed;
}
void DefaultSimulationFilterShader::FilterOps::set(SimulationFilterShaderOps value)
{
	PxSetFilterOps(
		ToUnmanagedEnum(PxFilterOp, value.Op0),
		ToUnmanagedEnum(PxFilterOp, value.Op1),
		ToUnmanagedEnum(PxFilterOp, value.Op2));
}