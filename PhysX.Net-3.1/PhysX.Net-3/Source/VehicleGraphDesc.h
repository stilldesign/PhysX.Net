#pragma once

#include <PxVehicleUtils.h>

namespace PhysX
{
	/// <summary>
	/// 
	/// </summary>
	public ref class VehicleGraphDesc
	{
		internal:
			static PxVehicleGraphDesc ToUnmanaged(VehicleGraphDesc desc);

		public:
			/// <summary>
			/// X-coord of graph centre. Range: (0,1).
			/// </summary>
			property float PositionX;
			/// <summary>
			/// Y-coord of graph centre. Range: (0,1).
			/// </summary>
			property float PositionY;
			/// <summary>
			/// X-extents of graph (from mPosX-0.5f*mSizeX to mPosX+0.5f*mSizeX). Range: (0,1).
			/// </summary>
			property float SizeX;
			/// <summary>
			/// Y-extents of graph (from mPosY-0.5f*mSizeY to mPosY+0.5f*mSizeY). Range: (0,1).
			/// </summary>
			property float SizeY;
			/// <summary>
			/// Background colour of graph.
			/// </summary>
			property Vector3 BackgroundColour;
			/// <summary>
			/// Alpha value of background colour.
			/// </summary>
			property float Alpha;
	};
};