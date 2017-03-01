#pragma once

#include "XmlParserOptions.h"

namespace PhysX
{
	ref class Physics;
	ref class Scene;
	ref class SerializationRegistry;
	ref class Cooking;
	ref class Collection;

	using namespace System::IO;

	public ref class Serialization
	{
	private:
		Serialization() { }

	public:
		//static bool IsSerializable(Collection^ collection, SerializationRegistry^ sr, [Optional] Collection^ externalReferences);
		//static void Complete(Collection^ collection, SerializationRegistry^ sr, [Optional] Collection^ exceptFor, [Optional] Nullable<bool> followJoints);
		//static void CreateNames(Collection^ collection, long base);
		//static void Remove(Collection^ collection, int serialType, SerializationRegistry^ sr, [Optional] Collection^ to);

		//static PxCollection *  createCollectionFromXml (PxInputData &inputData, PxCooking &cooking, PxSerializationRegistry &sr, const PxCollection *externalRefs=NULL, PxStringTable *stringTable=NULL, PxXmlParserOptions *outArgs=NULL);
		//
		//static PxCollection *  createCollectionFromBinary (void *memBlock, PxSerializationRegistry &sr, const PxCollection *externalRefs=NULL);
 
		static bool SerializeCollectionToXml(Stream^ outputStream, Collection^ collection, SerializationRegistry^ sr, [Optional] Cooking^ cooking, [Optional] Collection^ externalRefs, [Optional] Nullable<XmlParserOptions> parserOptions);
 
		static bool SerializeCollectionToBinary (Stream^ outputStream, Collection^ collection, SerializationRegistry^ sr, [Optional] Collection^ externalRefs, [Optional] Nullable<bool> exportNames);
 
		//static void  dumpBinaryMetaData (PxOutputStream &outputStream, const PxPhysics &physics, PxSerializationRegistry &sr);
 
		//static PxBinaryConverter *  createBinaryConverter (PxSerializationRegistry &sr, PxErrorCallback *error);
 
		static SerializationRegistry^ CreateSerializationRegistry(Physics^ physics);
	};
}