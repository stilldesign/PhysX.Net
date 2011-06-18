#pragma once

#include "ObservableEnum.h"
#include "Observer.h"
#include "IObservable.h"

using namespace System::Runtime::CompilerServices;

namespace PhysX
{
	/// <summary>
	/// Observable interface for classes which can send out state change notifications.
	/// </summary>
	[Extension]
	public ref class ObservableExtensions abstract sealed
	{
		public:
			/// <summary>
			/// Return the type of the observable object.
			/// </summary>
			[Extension]
			static ObservableType GetObservableType(PhysX::IObservable^ observable);

			/// <summary>
			/// Register an observer.
			/// </summary>
			[Extension]
			static void RegisterObserver(PhysX::IObservable^ observable, PhysX::Observer^ observer);

			/// <summary>
			/// Unregister an observer.
			/// </summary>
			[Extension]
			static void UnregisterObserver(PhysX::IObservable^ observable, PhysX::Observer^ observer);

			/// <summary>
			/// Return the number of registered observers.
			/// </summary>
			[Extension]
			static int GetNumberOfObservers(PhysX::IObservable^ observable);

			/// <summary>
			/// Retrieve an array of all the registered observers.
			/// </summary>
			[Extension]
			static array<PhysX::Observer^>^ GetObservers(PhysX::IObservable^ observable);
	};
};