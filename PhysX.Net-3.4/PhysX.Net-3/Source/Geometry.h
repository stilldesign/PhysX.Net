#pragma once

#include "GeometryEnum.h"

namespace PhysX
{
	/// <summary>
	/// A geometry object defines the characteristics of a spatial object, but without any information about
	/// its placement in the world.
	/// </summary>
	public ref class Geometry abstract
	{
	private:
		GeometryType _type;

	protected:
		Geometry(GeometryType type);
		
	internal:
		// TODO: Change to ref return object instead
		virtual PxGeometry* ToUnmanaged() abstract;

	public:
		property GeometryType Type
		{
			public: GeometryType get();
			private: void set(GeometryType value);
		}
	};
};