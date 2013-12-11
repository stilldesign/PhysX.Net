#pragma once

#include "DebugPoint.h"
#include "DebugLine.h"
#include "DebugTriangle.h"
#include "DebugText.h"
//#include <PxRenderBuffer.h> 

namespace PhysX
{
	public ref class RenderBuffer
	{
		private:
			array<DebugPoint>^ _points;
			array<DebugLine>^ _lines;
			array<DebugTriangle>^ _triangles;
			array<DebugText>^ _texts;

		internal:
			static RenderBuffer^ ToManaged(const PxRenderBuffer& buffer);

		public:
			property array<DebugPoint>^ Points
			{
				array<DebugPoint>^ get();
			}
			property array<DebugLine>^ Lines
			{
				array<DebugLine>^ get();
			}
			property array<DebugTriangle>^ Triangles
			{
				array<DebugTriangle>^ get();
			}
			property array<DebugText>^ Texts
			{
				array<DebugText>^ get();
			}

			property int NumberOfPoints;
			property int NumberOfLines;
			property int NumberOfTriangles;
			property int NumberOfTexts;
	};
};