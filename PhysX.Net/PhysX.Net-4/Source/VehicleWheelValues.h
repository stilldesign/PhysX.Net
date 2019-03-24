#pragma once

namespace PhysX
{
	generic<typename T>
	public ref class VehicleWheelValues
	{
		public:
			property T FrontLeftWheel;
			property T FrontRightWheel;
			property T RearLeftWheel;
			property T RearRightWheel;

			property T default[int]
			{
				T get(int index)
				{
					switch (index)
					{
						case 0:
							return FrontLeftWheel;

						case 1:
							return FrontRightWheel;

						case 2:
							return RearLeftWheel;

						case 3:
							return RearRightWheel;

						default:
							throw gcnew ArgumentOutOfRangeException("Invalid wheel index. Values are 0 to 3 inc.");
					}
				}
				void set(int index, T value)
				{
					switch (index)
					{
						case 0:
							FrontLeftWheel = value;
							break;

						case 1:
							FrontRightWheel = value;
							break;

						case 2:
							RearLeftWheel = value;
							break;

						case 3:
							RearRightWheel = value;
							break;

						default:
							throw gcnew ArgumentOutOfRangeException("Invalid wheel index. Values are 0 to 3 inc.");
					}
				}
			}
	};
};