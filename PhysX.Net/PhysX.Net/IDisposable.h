#pragma once

using namespace System;

namespace StillDesign
{
	namespace PhysX
	{
		public interface class IDisposable : System::IDisposable
		{
			public:
				event EventHandler^ onDisposing;
				event EventHandler^ onDisposed;
				
				property bool IsDisposed
				{
					bool get();
				}
		};
	};
};