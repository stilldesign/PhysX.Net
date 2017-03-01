#pragma once

#include "VisualDebuggerEnum.h"
//#include <PvdConnection.h>

namespace PhysX
{
	ref class Physics;

	namespace VisualDebugger
	{
		ref class Connection;
		ref class ConnectionManager;

		public ref class VisualDebuggerExt
		{
		private:
			PxVisualDebuggerExt* _ext;

		public:
			VisualDebuggerExt();
		};
	};
};