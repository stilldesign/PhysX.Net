#pragma once


namespace PhysX
{
	public enum class VehicleDifferentialType
	{
		LimitedSlip4WheelDrive = PxVehicleDifferential4WData::eDIFF_TYPE_LS_4WD,			//limited slip differential for car with 4 driven wheels
		LimitedSlipFrontWheelDrive = PxVehicleDifferential4WData::eDIFF_TYPE_LS_FRONTWD,		//limited slip differential for car with front-wheel drive
		LimitedSlipRearWheelDrive = PxVehicleDifferential4WData::eDIFF_TYPE_LS_REARWD,		//limited slip differential for car with rear-wheel drive
		OpenDifferential4WheelDrive = PxVehicleDifferential4WData::eDIFF_TYPE_OPEN_4WD,		//open differential for car with 4 driven wheels 
		OpenDifferentialFrontWheelDrive = PxVehicleDifferential4WData::eDIFF_TYPE_OPEN_FRONTWD,	//open differential for car with front-wheel drive
		OpenDifferentialRearWheelDrive = PxVehicleDifferential4WData::eDIFF_TYPE_OPEN_REARWD		//open differentila for car with rear-wheel drive
	};					 

	public enum class VehicleDrivableSurfaceType
	{
		Unknown = PxVehicleDrivableSurfaceType::eSURFACE_TYPE_UNKNOWN
	};

	public enum class VehicleGears
	{
		Reverse = PxVehicleGearsData::eREVERSE,
		Neutral = PxVehicleGearsData::eNEUTRAL,
		First = PxVehicleGearsData::eFIRST,
		Second = PxVehicleGearsData::eSECOND,
		Third = PxVehicleGearsData::eTHIRD,
		Fourth = PxVehicleGearsData::eFOURTH,
		Fifth = PxVehicleGearsData::eFIFTH,
		Sixth = PxVehicleGearsData::eSIXTH,
		Seventh = PxVehicleGearsData::eSEVENTH, 
		Eighth = PxVehicleGearsData::eEIGHTH, 
		Ninth = PxVehicleGearsData::eNINTH, 
		Tenth = PxVehicleGearsData::eTENTH, 
		Eleventh = PxVehicleGearsData::eELEVENTH, 
		Twelfth = PxVehicleGearsData::eTWELFTH, 
		Thirteenth = PxVehicleGearsData::eTHIRTEENTH, 
		Fourteenth = PxVehicleGearsData::eFOURTEENTH, 
		Fifteenth = PxVehicleGearsData::eFIFTEENTH, 
		Sixteenth = PxVehicleGearsData::eSIXTEENTH, 
		Seventeenth = PxVehicleGearsData::eSEVENTEENTH, 
		Eighteenth = PxVehicleGearsData::eEIGHTEENTH, 
		Nineteenth = PxVehicleGearsData::eNINETEENTH, 
		Twentieth = PxVehicleGearsData::eTWENTIETH, 
		TwentyFirst = PxVehicleGearsData::eTWENTYFIRST, 
		TwentySecond = PxVehicleGearsData::eTWENTYSECOND, 
		TwentyThird = PxVehicleGearsData::eTWENTYTHIRD, 
		TwentyFourth = PxVehicleGearsData::eTWENTYFOURTH, 
		TwentyFifth = PxVehicleGearsData::eTWENTYFIFTH, 
		TwentySixth = PxVehicleGearsData::eTWENTYSIXTH, 
		TwentySeventh = PxVehicleGearsData::eTWENTYSEVENTH, 
		TwentyEighth = PxVehicleGearsData::eTWENTYEIGHTH, 
		TwentyNinth = PxVehicleGearsData::eTWENTYNINTH, 
		Thirtieth = PxVehicleGearsData::eTHIRTIETH
	};

	public enum class VehicleWheelOrdering
	{
		FrontLeft = PxVehicleDrive4WWheelOrder::eFRONT_LEFT,
		FrontRight = PxVehicleDrive4WWheelOrder::eFRONT_RIGHT,
		RearLeft = PxVehicleDrive4WWheelOrder::eREAR_LEFT,
		RearRight = PxVehicleDrive4WWheelOrder::eREAR_RIGHT
	};

	public enum class VehicleGravityDirection
	{
		NegativeX = 0,
		NegativeY = 1,
		NegativeZ = 2
	};
};