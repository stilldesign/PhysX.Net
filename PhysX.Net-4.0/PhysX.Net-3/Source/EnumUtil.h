#pragma once

namespace PhysX
{
	private ref class EnumValueState
	{
	public:
		EnumValueState(Enum^ enumValue, bool set)
		{
			this->EnumValue = enumValue;
			this->EnumInt = Convert::ToInt32(enumValue);
			this->Set = set;
		};

		property Enum^ EnumValue;
		property int EnumInt;
		property bool Set;
	};

	private ref class EnumUtil
	{
	public:
		static array<EnumValueState^>^ Difference(Enum^ originalEnum, Enum^ newEnum)
		{
			auto values = Enum::GetValues(originalEnum->GetType());

			auto result = gcnew List<EnumValueState^>();

			for each(Enum^ value in values)
			{
				EnumValueState^ state = nullptr;

				// In original, but not in new (i.e. removed)
				if (originalEnum->HasFlag(value) && !newEnum->HasFlag(value))
				{
					state = gcnew EnumValueState(value, false);
				}
				// Not in original, but in new (i.e. added)
				else if(!originalEnum->HasFlag(value) && newEnum->HasFlag(value))
				{
					state = gcnew EnumValueState(value, true);
				}

				if(state == nullptr)
					continue;

				result->Add(state);
			}

			return result->ToArray();
		}
	};
};