#pragma once

using namespace System;

namespace PhysX
{
	public interface class IDisposable : System::IDisposable
	{
		public:
			event EventHandler^ OnDisposing;
			event EventHandler^ OnDisposed;
				
			property bool Disposed
			{
				bool get();
			}
	};
};