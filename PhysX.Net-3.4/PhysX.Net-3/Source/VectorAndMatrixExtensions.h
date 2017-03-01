#pragma once

using namespace System::Runtime::CompilerServices;

namespace PhysX
{
	// Copy from System.Numerics.* to other matching types (probably less needed now that the world
	// has this nice underlying super minimal library providing these common types that we can all
	// just share)
	[ExtensionAttribute]
	public ref class VectorAndMatrixExtensions abstract sealed
	{
	public:
		generic<typename T> where T : value class
			[ExtensionAttribute]
		static T As(System::Numerics::Vector2 vector2)
		{
			return Util::CloneFloatStruct<T>(2, (void*)(&vector2));
		}

		generic<typename T> where T : value class
			[ExtensionAttribute]
		static T As(System::Numerics::Vector3 vector3)
		{
			return Util::CloneFloatStruct<T>(3, (void*)(&vector3));
		}

		generic<typename T> where T : value class
			[ExtensionAttribute]
		static T As(System::Numerics::Vector4 vector4)
		{
			return Util::CloneFloatStruct<T>(4, (void*)(&vector4));
		}

		generic<typename T> where T : value class
			[ExtensionAttribute]
		static T As(System::Numerics::Matrix4x4 matrix)
		{
			return Util::CloneFloatStruct<T>(16, (void*)(&matrix));
		}
	};
};