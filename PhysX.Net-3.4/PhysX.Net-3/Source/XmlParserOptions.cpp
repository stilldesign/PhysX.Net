#include "StdAfx.h"
#include "XmlParserOptions.h"

PxSerialization::PxXmlMiscParameter XmlParserOptions::ToUnmanaged(XmlParserOptions managed)
{
	PxSerialization::PxXmlMiscParameter unmanaged;
		unmanaged.scale = TolerancesScale::ToUnmanaged(managed.Scale);
		unmanaged.upVector = UV(managed.UpVector);

	return unmanaged;
}