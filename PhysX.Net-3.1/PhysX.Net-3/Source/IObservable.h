#pragma once

namespace PhysX
{
	ref class ObservableInstance;

	public interface class IObservable
	{
		ObservableInstance^ GetObservableInstance();
	};
};