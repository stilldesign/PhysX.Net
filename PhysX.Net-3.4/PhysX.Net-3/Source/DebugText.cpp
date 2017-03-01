#include "StdAfx.h"
#include "DebugText.h"

DebugText::DebugText(Vector3 position, float size, int color, System::String^ string)
{
	Position = position;
	Size = size;
	Color = color;
	String = string;
}