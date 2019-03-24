#pragma once

#include <extensions\PxDefaultSimulationFilterShader.h>

namespace PhysX
{
	public enum class FilterOp
	{
		And = PxFilterOp::PX_FILTEROP_AND,
		Or = PxFilterOp::PX_FILTEROP_OR,
		XOr = PxFilterOp::PX_FILTEROP_XOR,
		NAnd = PxFilterOp::PX_FILTEROP_NAND,
		NOr = PxFilterOp::PX_FILTEROP_NOR,
		NXOr = PxFilterOp::PX_FILTEROP_NXOR,
		//UBISOFT : FILTERING
		SwapAnd = PxFilterOp::PX_FILTEROP_SWAP_AND
	};
}