#include "StdAfx.h"
#include "RenderBuffer.h"

// TODO: Enforce creating the array buffers prior to using this class. Allocating arrays every frame is bad.
RenderBuffer^ RenderBuffer::ToManaged(const PxRenderBuffer& buffer, RenderBufferDataFlags flags)
{
	auto r = gcnew RenderBuffer();

	if (flags.HasFlag(RenderBufferDataFlags::Points))
	{
		r->NumberOfPoints = buffer.getNbPoints();

		if (buffer.getPoints() != NULL)
		{
			r->_points = Util::AsManagedArray<DebugPoint>((void*)buffer.getPoints(), buffer.getNbPoints());
		}
	}

	if (flags.HasFlag(RenderBufferDataFlags::Lines))
	{
		r->NumberOfLines = buffer.getNbLines();

		if (buffer.getLines() != NULL)
		{
			r->_lines = Util::AsManagedArray<DebugLine>((void*)buffer.getLines(), buffer.getNbLines());
		}
	}

	if (flags.HasFlag(RenderBufferDataFlags::Triangles))
	{
		r->NumberOfTriangles = buffer.getNbTriangles();

		if (buffer.getTriangles() != NULL)
		{
			r->_triangles = Util::AsManagedArray<DebugTriangle>((void*)buffer.getTriangles(), buffer.getNbTriangles());
		}
	}

	if (flags.HasFlag(RenderBufferDataFlags::Text))
	{
		r->NumberOfTexts = buffer.getNbTexts();

		if (buffer.getTexts() != NULL)
		{
			r->_texts = gcnew array<DebugText>(buffer.getNbTexts());
			for (PxU32 i = 0; i < buffer.getNbTexts(); i++)
			{
				const PxDebugText* t = buffer.getTexts() + i;

				r->_texts[i].Position = MathUtil::PxVec3ToVector3(t->position);
				r->_texts[i].Size = t->size;
				r->_texts[i].Color = t->color;
				r->_texts[i].String = (t->string == NULL ? nullptr : Util::ToManagedString(t->string));
			}
		}
	}

	return r;
}

array<DebugPoint>^ RenderBuffer::Points::get()
{
	return _points;
}
array<DebugLine>^ RenderBuffer::Lines::get()
{
	return _lines;
}
array<DebugTriangle>^ RenderBuffer::Triangles::get()
{
	return _triangles;
}
array<DebugText>^ RenderBuffer::Texts::get()
{
	return _texts;
}