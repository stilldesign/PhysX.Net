#pragma once

#include "Enums.h"
#include "Physics Collection.h"

using namespace System;

namespace StillDesign
{
	namespace PhysX
	{
		ref class Scene;
		ref class Core;
		
		namespace Utilities
		{
			ref class ErrorReport;
			
			public ref class Utilities
			{
				private:
					static StillDesign::PhysX::Utilities::ErrorReport^ _errorReport;
					
				public:
					static bool SaveCollection( PhysicsCollection^ physicsCollection, String^ path, UtilitiesFileType fileType );
					static bool SaveCollection( PhysicsCollection^ physicsCollection, String^ path, UtilitiesFileType fileType, bool saveDefaults, bool saveCookedData );
					//static bool SaveCollectionToMemory( PhysicsCollection^ physicsCollection, String^ file, Utit
					
					/// <summary>Loads an NxuPhysicsCollection either from a file on disk or a buffer in memory</summary>
					static PhysicsCollection^ LoadCollection( String^ file, UtilitiesFileType fileType );
					
					static PhysicsCollection^ ExtractCollectionFromScene( Scene^ scene );
					
					static bool CoreDump( Core^ core, String^ file, UtilitiesFileType fileType );
					
					//
					
					property StillDesign::PhysX::Utilities::ErrorReport^ ErrorReport
					{
						static StillDesign::PhysX::Utilities::ErrorReport^ get();
						static void set( StillDesign::PhysX::Utilities::ErrorReport^ value );
					}
			};
		};
	};
};