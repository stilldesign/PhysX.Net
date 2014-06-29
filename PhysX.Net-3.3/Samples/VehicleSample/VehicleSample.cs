using System;
using System.Collections.Generic;
using System.Linq;
using PhysX.Math;

namespace PhysX.Samples.VehicleSample
{
	public class VehicleSample : Sample
	{
		const int TIRE_TYPE_SLICKS = 0;
		const int MAX_NUM_SURFACE_TYPES = 1;

		private Material _vehicleDrivableSurfaceType, _chassisMaterialDrivable, _chassisMaterialNonDrivable;

		protected override void LoadContent()
		{

		}

		protected override void LoadPhysics(Scene scene)
		{
			CreateMaterials(scene.Physics);

			var wheelCenters = new[]
			{
				new Vector3(-10, -3, -15),
				new Vector3(10, -3, -15),
				new Vector3(-10, -3, 15),
				new Vector3(10, -3, 15)
			};

			var wheels = new VehicleWheelsSimData(4);
			var drive = new VehicleDriveSimData4W();
			var chassis = new VehicleChassisData();

			CreateVehicle4WSimulationData(1000, null, 3, null, wheelCenters, wheels, drive, chassis);
		}

		private void CreateMaterials(Physics physics)
		{
			_vehicleDrivableSurfaceType = physics.CreateMaterial(0.5f, 0.5f, 0.2f);
			_chassisMaterialDrivable = physics.CreateMaterial(0.0f, 0.0f, 0.0f);
			_chassisMaterialNonDrivable = physics.CreateMaterial(1.0f, 1.0f, 0.0f);
		}

		private void CreateVehicle4WSimulationData(
			float chassisMass,
			ConvexMesh chassisConvexMesh,
			float wheelMass,
			ConvexMesh[] wheelConvexMeshes,
			Vector3[] wheelCentreOffsets,
			VehicleWheelsSimData wheelsData,
			VehicleDriveSimData4W driveData,
			VehicleChassisData chassisData)
		{


			//Extract the chassis AABB dimensions from the chassis convex mesh.
			//Vector3 chassisDims = computeChassisAABBDimensions(chassisConvexMesh);
			Vector3 chassisDims = new Vector3(10, 10, 10);

			//The origin is at the center of the chassis mesh.
			//Set the center of mass to be below this point and a little towards the front.
			Vector3 chassisCMOffset = new Vector3(0.0f, -chassisDims.Y * 0.5f + 0.65f, 0.25f);

			//Now compute the chassis mass and moment of inertia.
			//Use the moment of inertia of a cuboid as an approximate value for the chassis moi.
			Vector3 chassisMOI = new Vector3
			(
				(chassisDims.Y * chassisDims.Y + chassisDims.Z * chassisDims.Z) * chassisMass / 12.0f,
				(chassisDims.X * chassisDims.X + chassisDims.Z * chassisDims.Z) * chassisMass / 12.0f,
				(chassisDims.X * chassisDims.X + chassisDims.Y * chassisDims.Y) * chassisMass / 12.0f
			);

			//A bit of tweaking here.  The car will have more responsive turning if we reduce the
			//y-component of the chassis moment of inertia.
			chassisMOI.Y *= 0.8f;

			//Let's set up the chassis data structure now.
			chassisData.Mass = chassisMass;
			chassisData.MomentOfInertia = chassisMOI;
			chassisData.CenterOfMassOffset = chassisCMOffset;

			//Work out the front/rear mass split from the cm offset.
			//This is a very approximate calculation with lots of assumptions.
			//massRear*zRear + massFront*zFront = mass*cm           (1)
			//massRear       + massFront        = mass                      (2)
			//Rearrange (2)
			//massFront = mass - massRear                                           (3)
			//Substitute (3) into (1)
			//massRear(zRear - zFront) + mass*zFront = mass*cm      (4)
			//Solve (4) for massRear
			//massRear = mass(cm - zFront)/(zRear-zFront)           (5)
			//Now we also have
			//zFront = (z-cm)/2                                                                     (6a)
			//zRear = (-z-cm)/2                                                                     (6b)
			//Substituting (6a-b) into (5) gives
			//massRear = 0.5*mass*(z-3cm)/z                                         (7)
			float massRear = 0.5f * chassisMass * (chassisDims.Z - 3 * chassisCMOffset.Z) / chassisDims.Z;
			float massFront = chassisMass - massRear;

			//Extract the wheel radius and width from the wheel convex meshes.
			float[] wheelWidths = new float[4];
			float[] wheelRadii = new float[4];
			//ComputeWheelWidthsAndRadii(wheelConvexMeshes, wheelWidths, wheelRadii);
			wheelWidths = new[] { 3f, 3, 3, 3 };
			wheelRadii = new[] { 1f, 1, 1, 1 };

			//Now compute the wheel masses and inertias components around the axle's axis.
			//http://en.wikipedia.org/wiki/List_of_moments_of_inertia
			float[] wheelMOIs = new float[4];
			for (int i = 0; i < 4; i++)
			{
				wheelMOIs[i] = 0.5f * wheelMass * wheelRadii[i] * wheelRadii[i];
			}
			//Let's set up the wheel data structures now with radius, mass, and moi.
			VehicleWheelData[] wheels = new VehicleWheelData[4]
			{
				new VehicleWheelData(),
				new VehicleWheelData(),
				new VehicleWheelData(),
				new VehicleWheelData()
			};
			for (int i = 0; i < 4; i++)
			{
				wheels[i].Radius = wheelRadii[i];
				wheels[i].Mass = wheelMass;
				wheels[i].MomentOfInertia = wheelMOIs[i];
				wheels[i].Width = wheelWidths[i];
			}
			//Disable the handbrake from the front wheels and enable for the rear wheels
			wheels[(int)VehicleWheelOrdering.FrontLeft].MaxHandBrakeTorque = 0.0f;
			wheels[(int)VehicleWheelOrdering.FrontRight].MaxHandBrakeTorque = 0.0f;
			wheels[(int)VehicleWheelOrdering.RearLeft].MaxHandBrakeTorque = 4000.0f;
			wheels[(int)VehicleWheelOrdering.RearRight].MaxHandBrakeTorque = 4000.0f;
			//Enable steering for the front wheels and disable for the front wheels.
			wheels[(int)VehicleWheelOrdering.FrontLeft].MaxSteer = (float)System.Math.PI * 0.3333f;
			wheels[(int)VehicleWheelOrdering.FrontRight].MaxSteer = (float)System.Math.PI * 0.3333f;
			wheels[(int)VehicleWheelOrdering.RearLeft].MaxSteer = 0.0f;
			wheels[(int)VehicleWheelOrdering.RearRight].MaxSteer = 0.0f;

			//Let's set up the tire data structures now.
			//Put slicks on the front tires and wets on the rear tires.
			var tires = new VehicleTireData[4]
			{
				new VehicleTireData(),
				new VehicleTireData(),
				new VehicleTireData(),
				new VehicleTireData()
			};
			tires[(int)VehicleWheelOrdering.FrontLeft].Type = TIRE_TYPE_SLICKS;
			tires[(int)VehicleWheelOrdering.FrontRight].Type = TIRE_TYPE_SLICKS;
			tires[(int)VehicleWheelOrdering.RearLeft].Type = TIRE_TYPE_SLICKS;
			tires[(int)VehicleWheelOrdering.RearRight].Type = TIRE_TYPE_SLICKS;

			//Let's set up the suspension data structures now.
			VehicleSuspensionData[] susps = new VehicleSuspensionData[4]
			{
				new VehicleSuspensionData(),
				new VehicleSuspensionData(),
				new VehicleSuspensionData(),
				new VehicleSuspensionData()
			};
			for (int i = 0; i < 4; i++)
			{
				susps[i].MaxCompression = 0.3f;
				susps[i].MaxDroop = 0.1f;
				susps[i].SpringStrength = 35000.0f;
				susps[i].SpringDamperRate = 4500.0f;
			}
			susps[(int)VehicleWheelOrdering.FrontLeft].SprungMass = massFront * 0.5f;
			susps[(int)VehicleWheelOrdering.FrontRight].SprungMass = massFront * 0.5f;
			susps[(int)VehicleWheelOrdering.RearLeft].SprungMass = massRear * 0.5f;
			susps[(int)VehicleWheelOrdering.RearRight].SprungMass = massRear * 0.5f;

			//We need to set up geometry data for the suspension, wheels, and tires.
			//We already know the wheel centers described as offsets from the rigid body centre of mass.
			//From here we can approximate application points for the tire and suspension forces.
			//Lets assume that the suspension travel directions are absolutely vertical.
			//Also assume that we apply the tire and suspension forces 30cm below the centre of mass.
			Vector3[] suspTravelDirections = new Vector3[] { new Vector3(0, -1, 0), new Vector3(0, -1, 0), new Vector3(0, -1, 0), new Vector3(0, -1, 0) };
			Vector3[] wheelCentreCMOffsets = new Vector3[4];
			Vector3[] suspForceAppCMOffsets = new Vector3[4];
			Vector3[] tireForceAppCMOffsets = new Vector3[4];
			for (int i = 0; i < 4; i++)
			{
				wheelCentreCMOffsets[i] = wheelCentreOffsets[i] - chassisCMOffset;
				suspForceAppCMOffsets[i] = new Vector3(wheelCentreCMOffsets[i].X, -0.3f, wheelCentreCMOffsets[i].Z);
				tireForceAppCMOffsets[i] = new Vector3(wheelCentreCMOffsets[i].X, -0.3f, wheelCentreCMOffsets[i].Z);
			}

			//Now add the wheel, tire and suspension data.
			for (int i = 0; i < 4; i++)
			{
				wheelsData.SetWheelData(i, wheels[i]);
				wheelsData.SetTireData(i, tires[i]);
				wheelsData.SetSuspensionData(i, susps[i]);
				wheelsData.SetSuspensionTravelDirection(i, suspTravelDirections[i]);
				wheelsData.SetWheelCentreOffset(i, wheelCentreCMOffsets[i]);
				wheelsData.SetSuspensionForceApplicationPointOffset(i, suspForceAppCMOffsets[i]);
				wheelsData.SetTireForceApplicationPointOffset(i, tireForceAppCMOffsets[i]);
			}

			//Now set up the differential, engine, gears, clutch, and ackermann steering.

			//Diff
			var diff = new VehicleDifferential4WData();
			diff.Type = VehicleDifferentialType.LimitedSlip4WheelDrive;
			driveData.SetDifferentialData(diff);

			//Engine
			var engine = new VehicleEngineData()
			{
				PeakTorque = 500.0f,
				MaxOmega = 600.0f//approx 6000 rpm
			};
			driveData.SetEngineData(engine);

			//Gears
			var gears = new VehicleGearsData()
			{
				SwitchTime = 0.5f
			};
			driveData.SetGearsData(gears);

			//Clutch
			var clutch = new VehicleClutchData()
			{
				Strength = 10.0f
			};
			driveData.SetClutchData(clutch);

			//Ackermann steer accuracy
			var ackermann = new VehicleAckermannGeometryData()
			{
				Accuracy = 1.0f,
				AxleSeparation = wheelCentreOffsets[(int)VehicleWheelOrdering.FrontLeft].Z - wheelCentreOffsets[(int)VehicleWheelOrdering.RearLeft].Z,
				FrontWidth = wheelCentreOffsets[(int)VehicleWheelOrdering.FrontRight].X - wheelCentreOffsets[(int)VehicleWheelOrdering.FrontLeft].X,
				RearWidth = wheelCentreOffsets[(int)VehicleWheelOrdering.RearRight].X - wheelCentreOffsets[(int)VehicleWheelOrdering.RearLeft].X
			};
			driveData.SetAckermannGeometryData(ackermann);

			// Create actor
			var vehActor = CreateVehicleActor4W(chassisData, wheelConvexMeshes, chassisConvexMesh, this.Scene, _chassisMaterialNonDrivable);
		}

		private RigidDynamic CreateVehicleActor4W(
				VehicleChassisData chassisData,
				ConvexMesh[] wheelConvexMeshes,
				ConvexMesh chassisConvexMesh,
				Scene scene,
				Material material)
		{
			//We need a rigid body actor for the vehicle.
			//Don't forget to add the actor the scene after setting up the associated vehicle.
			RigidDynamic vehActor = scene.Physics.CreateRigidDynamic();

			//We need to add wheel collision shapes, their local poses, a material for the wheels, and a simulation filter for the wheels.
			ConvexMeshGeometry frontLeftWheelGeom = new ConvexMeshGeometry(wheelConvexMeshes[0]);
			ConvexMeshGeometry frontRightWheelGeom = new ConvexMeshGeometry(wheelConvexMeshes[1]);
			ConvexMeshGeometry rearLeftWheelGeom = new ConvexMeshGeometry(wheelConvexMeshes[2]);
			ConvexMeshGeometry rearRightWheelGeom = new ConvexMeshGeometry(wheelConvexMeshes[3]);

			var wheelGeometries = new[]
			{
				frontLeftWheelGeom,
				frontRightWheelGeom,
				rearLeftWheelGeom,
				rearRightWheelGeom
			};

			var wheelLocalPoses = new[]
			{
				Matrix.Identity,
				Matrix.Identity,
				Matrix.Identity,
				Matrix.Identity
			};

			Material wheelMaterial = material;

			FilterData wheelCollFilterData = new FilterData();
			wheelCollFilterData.Word0 = (uint)CollisionFlags.COLLISION_FLAG_WHEEL;
			wheelCollFilterData.Word1 = (uint)CollisionFlags.COLLISION_FLAG_WHEEL_AGAINST;

			//We need to add chassis collision shapes, their local poses, a material for the chassis, and a simulation filter for the chassis.
			var chassisConvexGeom = new ConvexMeshGeometry(chassisConvexMesh);
			var chassisGeoms = new[]
			{
				chassisConvexGeom 
			};

			var chassisLocalPoses = new[]
			{
				Matrix.Identity
			};

			Material chassisMaterial = material;

			FilterData chassisCollFilterData = new FilterData();
			chassisCollFilterData.Word0 = (uint)CollisionFlags.COLLISION_FLAG_CHASSIS;
			chassisCollFilterData.Word1 = (uint)CollisionFlags.COLLISION_FLAG_CHASSIS_AGAINST;

			//Create a query filter data for the car to ensure that cars
			//do not attempt to drive on themselves.
			FilterData vehQryFilterData = new FilterData();
			//SampleVehicleSetupVehicleShapeQueryFilterData(&vehQryFilterData);
			vehQryFilterData.Word3 = (uint)DrivableSurfaces.SAMPLEVEHICLE_UNDRIVABLE_SURFACE;

			//Set up the physx rigid body actor with shapes, local poses, and filters.
			setupActor
				(vehActor,
				vehQryFilterData,
				wheelGeometries, wheelLocalPoses, wheelMaterial, wheelCollFilterData,
				chassisGeoms, chassisLocalPoses, chassisMaterial, chassisCollFilterData,
				chassisData,
				scene.Physics);

			return vehActor;
		}

		private void setupActor(
			RigidDynamic vehActor,
			FilterData vehQryFilterData,
			Geometry[] wheelGeometries, Matrix[] wheelLocalPoses, Material wheelMaterial, FilterData wheelCollFilterData,
			Geometry[] chassisGeometries, Matrix[] chassisLocalPoses, Material chassisMaterial, FilterData chassisCollFilterData,
			VehicleChassisData chassisData,
			Physics physics)
		{
			//Add all the wheel shapes to the actor.
			for (int i = 0; i < wheelLocalPoses.Length; i++)
			{
				var wheelShape = vehActor.CreateShape(wheelGeometries[i], wheelMaterial);
				wheelShape.QueryFilterData = vehQryFilterData;
				wheelShape.SimulationFilterData = wheelCollFilterData;
				wheelShape.LocalPose = wheelLocalPoses[i];
			}

			//Add the chassis shapes to the actor.
			for (int i = 0; i < chassisGeometries.Length; i++)
			{
				var chassisShape = vehActor.CreateShape(chassisGeometries[i], chassisMaterial);

				chassisShape.QueryFilterData = vehQryFilterData;
				chassisShape.SimulationFilterData = chassisCollFilterData;
				chassisShape.LocalPose = chassisLocalPoses[i];
			}

			vehActor.Mass = chassisData.Mass;
			vehActor.MassSpaceInertiaTensor = chassisData.MomentOfInertia;
			vehActor.CenterOfMassLocalPose = Matrix.Translation(chassisData.CenterOfMassOffset);
		}

		private void ComputeWheelWidthsAndRadii(ConvexMesh[] wheelConvexMeshes, ref float[] wheelWidths, ref float[] wheelRadii)
		{
			for (int i = 0; i < 4; i++)
			{
				int numWheelVerts = wheelConvexMeshes[i].NumberOfVertices;
				var wheelVerts = wheelConvexMeshes[i].GetVertices();

				Vector3 wheelMin = new Vector3(float.MaxValue, float.MaxValue, float.MaxValue);
				Vector3 wheelMax = new Vector3(-float.MaxValue, -float.MaxValue, -float.MaxValue);
				for (int j = 0; j < numWheelVerts; j++)
				{
					wheelMin.X = System.Math.Min(wheelMin.X, wheelVerts[j].X);
					wheelMin.Y = System.Math.Min(wheelMin.Y, wheelVerts[j].Y);
					wheelMin.Z = System.Math.Min(wheelMin.Z, wheelVerts[j].Z);
					wheelMax.X = System.Math.Max(wheelMax.X, wheelVerts[j].X);
					wheelMax.Y = System.Math.Max(wheelMax.Y, wheelVerts[j].Y);
					wheelMax.Z = System.Math.Max(wheelMax.Z, wheelVerts[j].Z);
				}
				wheelWidths[i] = wheelMax.X - wheelMin.X;
				wheelRadii[i] = System.Math.Max(wheelMax.Y, wheelMax.Z) * 0.975f;
			}
		}

		private Vector3 ComputeChassisAABBDimensions(ConvexMesh chassisConvexMesh)
		{
			int numChassisVerts = chassisConvexMesh.NumberOfVertices;
			var chassisVerts = chassisConvexMesh.GetVertices();

			Vector3 chassisMin = new Vector3(float.MaxValue, float.MaxValue, float.MaxValue);
			Vector3 chassisMax = new Vector3(-float.MaxValue, -float.MaxValue, -float.MaxValue);

			for (int i = 0; i < numChassisVerts; i++)
			{
				chassisMin.X = System.Math.Min(chassisMin.X, chassisVerts[i].X);
				chassisMin.Y = System.Math.Min(chassisMin.Y, chassisVerts[i].Y);
				chassisMin.Z = System.Math.Min(chassisMin.Z, chassisVerts[i].Z);
				chassisMax.X = System.Math.Max(chassisMax.X, chassisVerts[i].X);
				chassisMax.Y = System.Math.Max(chassisMax.Y, chassisVerts[i].Y);
				chassisMax.Z = System.Math.Max(chassisMax.Z, chassisVerts[i].Z);
			}
			Vector3 chassisDims = chassisMax - chassisMin;
			return chassisDims;
		}

		private void createVehicle4WSimulationData(
			float chassisMass, ConvexMesh chassisConvexMesh,
			float wheelMass, ConvexMesh[] wheelConvexMeshes, Vector3[] wheelCentreOffsets,
			VehicleWheelsSimData wheelsData, VehicleDriveSimData4W driveData, VehicleChassisData chassisData)
		{
			//Extract the chassis AABB dimensions from the chassis convex mesh.
			Vector3 chassisDims = ComputeChassisAABBDimensions(chassisConvexMesh);

			//The origin is at the center of the chassis mesh.
			//Set the center of mass to be below this point and a little towards the front.
			Vector3 chassisCMOffset = new Vector3(0.0f, -chassisDims.Y * 0.5f + 0.65f, 0.25f);

			//Now compute the chassis mass and moment of inertia.
			//Use the moment of inertia of a cuboid as an approximate value for the chassis moi.
			Vector3 chassisMOI = new Vector3
				((chassisDims.Y * chassisDims.Y + chassisDims.Z * chassisDims.Z) * chassisMass / 12.0f,
				 (chassisDims.X * chassisDims.X + chassisDims.Z * chassisDims.Z) * chassisMass / 12.0f,
				 (chassisDims.X * chassisDims.X + chassisDims.Y * chassisDims.Y) * chassisMass / 12.0f);
			//A bit of tweaking here.  The car will have more responsive turning if we reduce the 	
			//y-component of the chassis moment of inertia.
			chassisMOI.Y *= 0.8f;

			//Let's set up the chassis data structure now.
			chassisData.Mass = chassisMass;
			chassisData.MomentOfInertia = chassisMOI;
			chassisData.CenterOfMassOffset = chassisCMOffset;

			//Compute the sprung masses of each suspension spring using a helper function.
			var suspSprungMasses = VehicleUtilSetup.ComputeSprungMasses(wheelCentreOffsets, chassisCMOffset, chassisMass, 1);

			//Extract the wheel radius and width from the wheel convex meshes.
			var wheelWidths = new float[4];
			var wheelRadii = new float[4];
			ComputeWheelWidthsAndRadii(wheelConvexMeshes, ref wheelWidths, ref wheelRadii);

			//Now compute the wheel masses and inertias components around the axle's axis.
			//http://en.wikipedia.org/wiki/List_of_moments_of_inertia
			var wheelMOIs = new float[4];
			for (int i = 0; i < 4; i++)
			{
				wheelMOIs[i] = 0.5f * wheelMass * wheelRadii[i] * wheelRadii[i];
			}
			//Let's set up the wheel data structures now with radius, mass, and moi.
			var wheels = new VehicleWheelData[4];
			for (int i = 0; i < 4; i++)
			{
				wheels[i].Radius = wheelRadii[i];
				wheels[i].Mass = wheelMass;
				wheels[i].MomentOfInertia = wheelMOIs[i];
				wheels[i].Width = wheelWidths[i];
			}
			//Disable the handbrake from the front wheels and enable for the rear wheels
			wheels[(int)VehicleWheelOrdering.FrontLeft].MaxHandBrakeTorque = 0.0f;
			wheels[(int)VehicleWheelOrdering.FrontRight].MaxHandBrakeTorque = 0.0f;
			wheels[(int)VehicleWheelOrdering.RearLeft].MaxHandBrakeTorque = 4000.0f;
			wheels[(int)VehicleWheelOrdering.RearRight].MaxHandBrakeTorque = 4000.0f;
			//Enable steering for the front wheels and disable for the front wheels.
			wheels[(int)VehicleWheelOrdering.FrontLeft].MaxSteer = (float)(System.Math.PI * 0.3333);
			wheels[(int)VehicleWheelOrdering.FrontRight].MaxSteer = (float)(System.Math.PI * 0.3333);
			wheels[(int)VehicleWheelOrdering.RearLeft].MaxSteer = 0.0f;
			wheels[(int)VehicleWheelOrdering.RearRight].MaxSteer = 0.0f;

			//Let's set up the tire data structures now.
			//////////Put slicks on the front tires and wets on the rear tires.
			//Put slicks on the front tires and slicks on the rear tires.
			var tires = new VehicleTireData[4];
			tires[(int)VehicleWheelOrdering.FrontLeft].Type = TIRE_TYPE_SLICKS;
			tires[(int)VehicleWheelOrdering.FrontRight].Type = TIRE_TYPE_SLICKS;
			tires[(int)VehicleWheelOrdering.RearLeft].Type = TIRE_TYPE_SLICKS;
			tires[(int)VehicleWheelOrdering.RearRight].Type = TIRE_TYPE_SLICKS;

			//Let's set up the suspension data structures now.
			var susps = new VehicleSuspensionData[4];
			for (int i = 0; i < 4; i++)
			{
				susps[i].MaxCompression = 0.3f;
				susps[i].MaxDroop = 0.1f;
				susps[i].SpringStrength = 35000.0f;
				susps[i].SpringDamperRate = 4500.0f;
			}
			susps[(int)VehicleWheelOrdering.FrontLeft].SprungMass = suspSprungMasses[(int)VehicleWheelOrdering.FrontLeft];
			susps[(int)VehicleWheelOrdering.FrontRight].SprungMass = suspSprungMasses[(int)VehicleWheelOrdering.FrontRight];
			susps[(int)VehicleWheelOrdering.RearLeft].SprungMass = suspSprungMasses[(int)VehicleWheelOrdering.RearLeft];
			susps[(int)VehicleWheelOrdering.RearRight].SprungMass = suspSprungMasses[(int)VehicleWheelOrdering.RearRight];

			//Set up the camber.
			//Remember that the left and right wheels need opposite camber so that the car preserves symmetry about the forward direction.
			//Set the camber to 0.0f when the spring is neither compressed or elongated.
			const float camberAngleAtRest = 0;
			susps[(int)VehicleWheelOrdering.FrontLeft].CamberAtRest = camberAngleAtRest;
			susps[(int)VehicleWheelOrdering.FrontRight].CamberAtRest = -camberAngleAtRest;
			susps[(int)VehicleWheelOrdering.RearLeft].CamberAtRest = camberAngleAtRest;
			susps[(int)VehicleWheelOrdering.RearRight].CamberAtRest = -camberAngleAtRest;
			//Set the wheels to camber inwards at maximum droop (the left and right wheels almost form a V shape)
			const float camberAngleAtMaxDroop = 0.001f;
			susps[(int)VehicleWheelOrdering.FrontLeft].CamberAtMaxDroop = camberAngleAtMaxDroop;
			susps[(int)VehicleWheelOrdering.FrontRight].CamberAtMaxDroop = -camberAngleAtMaxDroop;
			susps[(int)VehicleWheelOrdering.RearLeft].CamberAtMaxDroop = camberAngleAtMaxDroop;
			susps[(int)VehicleWheelOrdering.RearRight].CamberAtMaxDroop = -camberAngleAtMaxDroop;
			//Set the wheels to camber outwards at maximum compression (the left and right wheels almost form a A shape).
			const float camberAngleAtMaxCompression = -0.001f;
			susps[(int)VehicleWheelOrdering.FrontLeft].CamberAtMaxCompression = camberAngleAtMaxCompression;
			susps[(int)VehicleWheelOrdering.FrontRight].CamberAtMaxCompression = -camberAngleAtMaxCompression;
			susps[(int)VehicleWheelOrdering.RearLeft].CamberAtMaxCompression = camberAngleAtMaxCompression;
			susps[(int)VehicleWheelOrdering.RearRight].CamberAtMaxCompression = -camberAngleAtMaxCompression;

			//We need to set up geometry data for the suspension, wheels, and tires.
			//We already know the wheel centers described as offsets from the actor center and the center of mass offset from actor center.
			//From here we can approximate application points for the tire and suspension forces.
			//Lets assume that the suspension travel directions are absolutely vertical.
			//Also assume that we apply the tire and suspension forces 30cm below the center of mass.
			var suspTravelDirections = new[] { new Vector3(0, -1, 0), new Vector3(0, -1, 0), new Vector3(0, -1, 0), new Vector3(0, -1, 0) };
			var wheelCentreCMOffsets = new Vector3[4];
			var suspForceAppCMOffsets = new Vector3[4];
			var tireForceAppCMOffsets = new Vector3[4];
			for (int i = 0; i < 4; i++)
			{
				wheelCentreCMOffsets[i] = wheelCentreOffsets[i] - chassisCMOffset;
				suspForceAppCMOffsets[i] = new Vector3(wheelCentreCMOffsets[i].X, -0.3f, wheelCentreCMOffsets[i].Z);
				tireForceAppCMOffsets[i] = new Vector3(wheelCentreCMOffsets[i].X, -0.3f, wheelCentreCMOffsets[i].Z);
			}

			//Now add the wheel, tire and suspension data.
			for (int i = 0; i < 4; i++)
			{
				wheelsData.SetWheelData(i, wheels[i]);
				wheelsData.SetTireData(i, tires[i]);
				wheelsData.SetSuspensionData(i, susps[i]);
				wheelsData.SetSuspensionTravelDirection(i, suspTravelDirections[i]);
				wheelsData.SetWheelCentreOffset(i, wheelCentreCMOffsets[i]);
				wheelsData.SetSuspensionForceApplicationPointOffset(i, suspForceAppCMOffsets[i]);
				wheelsData.SetTireForceApplicationPointOffset(i, tireForceAppCMOffsets[i]);
			}

			//Set the car to perform 3 sub-steps when it moves with a forwards speed of less than 5.0 
			//and with a single step when it moves at speed greater than or equal to 5.0.
			wheelsData.SetSubStepCount(5.0f, 3, 1);


			//Now set up the differential, engine, gears, clutch, and ackermann steering.

			//Diff
			var diff = new VehicleDifferential4WData();
			diff.Type = VehicleDifferentialType.LimitedSlip4WheelDrive;
			driveData.SetDifferentialData(diff);

			//Engine
			var engine = new VehicleEngineData();
			engine.PeakTorque = 500.0f;
			engine.MaxOmega = 600.0f;//approx 6000 rpm
			driveData.SetEngineData(engine);

			//Gears
			var gears = new VehicleGearsData();
			gears.SwitchTime = 0.5f;
			driveData.SetGearsData(gears);

			//Clutch
			var clutch = new VehicleClutchData();
			clutch.Strength = 10.0f;
			driveData.SetClutchData(clutch);

			//Ackermann steer accuracy
			var ackermann = new VehicleAckermannGeometryData();
			ackermann.Accuracy = 1.0f;
			ackermann.AxleSeparation = wheelCentreOffsets[(int)VehicleWheelOrdering.FrontLeft].Z - wheelCentreOffsets[(int)VehicleWheelOrdering.RearLeft].Z;
			ackermann.FrontWidth = wheelCentreOffsets[(int)VehicleWheelOrdering.FrontRight].X - wheelCentreOffsets[(int)VehicleWheelOrdering.FrontLeft].X;
			ackermann.RearWidth = wheelCentreOffsets[(int)VehicleWheelOrdering.RearRight].X - wheelCentreOffsets[(int)VehicleWheelOrdering.RearLeft].X;
			driveData.SetAckermannGeometryData(ackermann);

			// Create actor
			var vehActor = CreateVehicleActor4W(chassisData, wheelConvexMeshes, chassisConvexMesh, this.Scene, _chassisMaterialNonDrivable);
		}

		private RigidDynamic CreateVehicleActor4W(
				VehicleChassisData chassisData,
				ConvexMesh[] wheelConvexMeshes,
				ConvexMesh chassisConvexMesh,
				Scene scene,
				Material material)
		{
			//We need a rigid body actor for the vehicle.
			//Don't forget to add the actor the scene after setting up the associated vehicle.
			RigidDynamic vehActor = scene.Physics.CreateRigidDynamic();

			//We need to add wheel collision shapes, their local poses, a material for the wheels, and a simulation filter for the wheels.
			ConvexMeshGeometry frontLeftWheelGeom = new ConvexMeshGeometry(wheelConvexMeshes[0]);
			ConvexMeshGeometry frontRightWheelGeom = new ConvexMeshGeometry(wheelConvexMeshes[1]);
			ConvexMeshGeometry rearLeftWheelGeom = new ConvexMeshGeometry(wheelConvexMeshes[2]);
			ConvexMeshGeometry rearRightWheelGeom = new ConvexMeshGeometry(wheelConvexMeshes[3]);

			var wheelGeometries = new[]
			{
				frontLeftWheelGeom,
				frontRightWheelGeom,
				rearLeftWheelGeom,
				rearRightWheelGeom
			};

			var wheelLocalPoses = new[]
			{
				Matrix.Identity,
				Matrix.Identity,
				Matrix.Identity,
				Matrix.Identity
			};

			Material wheelMaterial = material;

			FilterData wheelCollFilterData = new FilterData();
			wheelCollFilterData.Word0 = (uint)CollisionFlags.COLLISION_FLAG_WHEEL;
			wheelCollFilterData.Word1 = (uint)CollisionFlags.COLLISION_FLAG_WHEEL_AGAINST;

			//We need to add chassis collision shapes, their local poses, a material for the chassis, and a simulation filter for the chassis.
			var chassisConvexGeom = new ConvexMeshGeometry(chassisConvexMesh);
			var chassisGeoms = new[]
			{
				chassisConvexGeom 
			};

			var chassisLocalPoses = new[]
			{
				Matrix.Identity
			};

			Material chassisMaterial = material;

			FilterData chassisCollFilterData = new FilterData();
			chassisCollFilterData.Word0 = (uint)CollisionFlags.COLLISION_FLAG_CHASSIS;
			chassisCollFilterData.Word1 = (uint)CollisionFlags.COLLISION_FLAG_CHASSIS_AGAINST;

			//Create a query filter data for the car to ensure that cars
			//do not attempt to drive on themselves.
			FilterData vehQryFilterData = new FilterData();
			//SampleVehicleSetupVehicleShapeQueryFilterData(&vehQryFilterData);
			vehQryFilterData.Word3 = (uint)DrivableSurfaces.SAMPLEVEHICLE_UNDRIVABLE_SURFACE;

			//Set up the physx rigid body actor with shapes, local poses, and filters.
			setupActor
				(vehActor,
				vehQryFilterData,
				wheelGeometries, wheelLocalPoses, wheelMaterial, wheelCollFilterData,
				chassisGeoms, chassisLocalPoses, chassisMaterial, chassisCollFilterData,
				chassisData,
				scene.Physics);

			return vehActor;
		}

		private void setupActor(
			RigidDynamic vehActor,
			FilterData vehQryFilterData,
			Geometry[] wheelGeometries, Matrix[] wheelLocalPoses, Material wheelMaterial, FilterData wheelCollFilterData,
			Geometry[] chassisGeometries, Matrix[] chassisLocalPoses, Material chassisMaterial, FilterData chassisCollFilterData,
			VehicleChassisData chassisData,
			Physics physics)
		{
			//Add all the wheel shapes to the actor.
			for (int i = 0; i < wheelLocalPoses.Length; i++)
			{
				var wheelShape = vehActor.CreateShape(wheelGeometries[i], wheelMaterial);
				wheelShape.QueryFilterData = vehQryFilterData;
				wheelShape.SimulationFilterData = wheelCollFilterData;
				wheelShape.LocalPose = wheelLocalPoses[i];
			}

			//Add the chassis shapes to the actor.
			for (int i = 0; i < chassisGeometries.Length; i++)
			{
				var chassisShape = vehActor.CreateShape(chassisGeometries[i], chassisMaterial);

				chassisShape.QueryFilterData = vehQryFilterData;
				chassisShape.SimulationFilterData = chassisCollFilterData;
				chassisShape.LocalPose = chassisLocalPoses[i];
			}

			vehActor.Mass = chassisData.Mass;
			vehActor.MassSpaceInertiaTensor = chassisData.MomentOfInertia;
			vehActor.CenterOfMassLocalPose = Matrix.Translation(chassisData.CenterOfMassOffset);
		}

		private void ComputeWheelWidthsAndRadii(ConvexMesh[] wheelConvexMeshes, ref float[] wheelWidths, ref float[] wheelRadii)
		{
			for (int i = 0; i < 4; i++)
			{
				int numWheelVerts = wheelConvexMeshes[i].NumberOfVertices;
				var wheelVerts = wheelConvexMeshes[i].GetVertices();

				Vector3 wheelMin = new Vector3(float.MaxValue, float.MaxValue, float.MaxValue);
				Vector3 wheelMax = new Vector3(-float.MaxValue, -float.MaxValue, -float.MaxValue);
				for (int j = 0; j < numWheelVerts; j++)
				{
					wheelMin.X = System.Math.Min(wheelMin.X, wheelVerts[j].X);
					wheelMin.Y = System.Math.Min(wheelMin.Y, wheelVerts[j].Y);
					wheelMin.Z = System.Math.Min(wheelMin.Z, wheelVerts[j].Z);
					wheelMax.X = System.Math.Max(wheelMax.X, wheelVerts[j].X);
					wheelMax.Y = System.Math.Max(wheelMax.Y, wheelVerts[j].Y);
					wheelMax.Z = System.Math.Max(wheelMax.Z, wheelVerts[j].Z);
				}
				wheelWidths[i] = wheelMax.X - wheelMin.X;
				wheelRadii[i] = System.Math.Max(wheelMax.Y, wheelMax.Z) * 0.975f;
			}
		}

		private Vector3 ComputeChassisAABBDimensions(ConvexMesh chassisConvexMesh)
		{
			int numChassisVerts = chassisConvexMesh.NumberOfVertices;
			var chassisVerts = chassisConvexMesh.GetVertices();

			Vector3 chassisMin = new Vector3(float.MaxValue, float.MaxValue, float.MaxValue);
			Vector3 chassisMax = new Vector3(-float.MaxValue, -float.MaxValue, -float.MaxValue);

			for (int i = 0; i < numChassisVerts; i++)
			{
				chassisMin.X = System.Math.Min(chassisMin.X, chassisVerts[i].X);
				chassisMin.Y = System.Math.Min(chassisMin.Y, chassisVerts[i].Y);
				chassisMin.Z = System.Math.Min(chassisMin.Z, chassisVerts[i].Z);
				chassisMax.X = System.Math.Max(chassisMax.X, chassisVerts[i].X);
				chassisMax.Y = System.Math.Max(chassisMax.Y, chassisVerts[i].Y);
				chassisMax.Z = System.Math.Max(chassisMax.Z, chassisVerts[i].Z);
			}
			Vector3 chassisDims = chassisMax - chassisMin;
			return chassisDims;
		}

		private void createVehicle4WSimulationData(
			float chassisMass, ConvexMesh chassisConvexMesh,
			float wheelMass, ConvexMesh[] wheelConvexMeshes, Vector3[] wheelCentreOffsets,
			VehicleWheelsSimData wheelsData, VehicleDriveSimData4W driveData, VehicleChassisData chassisData)
		{
			//Extract the chassis AABB dimensions from the chassis convex mesh.
			Vector3 chassisDims = ComputeChassisAABBDimensions(chassisConvexMesh);

			//The origin is at the center of the chassis mesh.
			//Set the center of mass to be below this point and a little towards the front.
			Vector3 chassisCMOffset = new Vector3(0.0f, -chassisDims.Y * 0.5f + 0.65f, 0.25f);

			//Now compute the chassis mass and moment of inertia.
			//Use the moment of inertia of a cuboid as an approximate value for the chassis moi.
			Vector3 chassisMOI = new Vector3
				((chassisDims.Y * chassisDims.Y + chassisDims.Z * chassisDims.Z) * chassisMass / 12.0f,
				 (chassisDims.X * chassisDims.X + chassisDims.Z * chassisDims.Z) * chassisMass / 12.0f,
				 (chassisDims.X * chassisDims.X + chassisDims.Y * chassisDims.Y) * chassisMass / 12.0f);
			//A bit of tweaking here.  The car will have more responsive turning if we reduce the 	
			//y-component of the chassis moment of inertia.
			chassisMOI.Y *= 0.8f;

			//Let's set up the chassis data structure now.
			chassisData.Mass = chassisMass;
			chassisData.MomentOfInertia = chassisMOI;
			chassisData.CenterOfMassOffset = chassisCMOffset;

			//Compute the sprung masses of each suspension spring using a helper function.
			var suspSprungMasses = VehicleUtilSetup.ComputeSprungMasses(wheelCentreOffsets, chassisCMOffset, chassisMass, 1);

			//Extract the wheel radius and width from the wheel convex meshes.
			var wheelWidths = new float[4];
			var wheelRadii = new float[4];
			ComputeWheelWidthsAndRadii(wheelConvexMeshes, ref wheelWidths, ref wheelRadii);

			//Now compute the wheel masses and inertias components around the axle's axis.
			//http://en.wikipedia.org/wiki/List_of_moments_of_inertia
			var wheelMOIs = new float[4];
			for (int i = 0; i < 4; i++)
			{
				wheelMOIs[i] = 0.5f * wheelMass * wheelRadii[i] * wheelRadii[i];
			}
			//Let's set up the wheel data structures now with radius, mass, and moi.
			var wheels = new VehicleWheelData[4];
			for (int i = 0; i < 4; i++)
			{
				wheels[i].Radius = wheelRadii[i];
				wheels[i].Mass = wheelMass;
				wheels[i].MomentOfInertia = wheelMOIs[i];
				wheels[i].Width = wheelWidths[i];
			}
			//Disable the handbrake from the front wheels and enable for the rear wheels
			wheels[(int)VehicleWheelOrdering.FrontLeft].MaxHandBrakeTorque = 0.0f;
			wheels[(int)VehicleWheelOrdering.FrontRight].MaxHandBrakeTorque = 0.0f;
			wheels[(int)VehicleWheelOrdering.RearLeft].MaxHandBrakeTorque = 4000.0f;
			wheels[(int)VehicleWheelOrdering.RearRight].MaxHandBrakeTorque = 4000.0f;
			//Enable steering for the front wheels and disable for the front wheels.
			wheels[(int)VehicleWheelOrdering.FrontLeft].MaxSteer = (float)(System.Math.PI * 0.3333);
			wheels[(int)VehicleWheelOrdering.FrontRight].MaxSteer = (float)(System.Math.PI * 0.3333);
			wheels[(int)VehicleWheelOrdering.RearLeft].MaxSteer = 0.0f;
			wheels[(int)VehicleWheelOrdering.RearRight].MaxSteer = 0.0f;

			//Let's set up the tire data structures now.
			//////////Put slicks on the front tires and wets on the rear tires.
			//Put slicks on the front tires and slicks on the rear tires.
			var tires = new VehicleTireData[4];
			tires[(int)VehicleWheelOrdering.FrontLeft].Type = TIRE_TYPE_SLICKS;
			tires[(int)VehicleWheelOrdering.FrontRight].Type = TIRE_TYPE_SLICKS;
			tires[(int)VehicleWheelOrdering.RearLeft].Type = TIRE_TYPE_SLICKS;
			tires[(int)VehicleWheelOrdering.RearRight].Type = TIRE_TYPE_SLICKS;

			//Let's set up the suspension data structures now.
			var susps = new VehicleSuspensionData[4];
			for (int i = 0; i < 4; i++)
			{
				susps[i].MaxCompression = 0.3f;
				susps[i].MaxDroop = 0.1f;
				susps[i].SpringStrength = 35000.0f;
				susps[i].SpringDamperRate = 4500.0f;
			}
			susps[(int)VehicleWheelOrdering.FrontLeft].SprungMass = suspSprungMasses[(int)VehicleWheelOrdering.FrontLeft];
			susps[(int)VehicleWheelOrdering.FrontRight].SprungMass = suspSprungMasses[(int)VehicleWheelOrdering.FrontRight];
			susps[(int)VehicleWheelOrdering.RearLeft].SprungMass = suspSprungMasses[(int)VehicleWheelOrdering.RearLeft];
			susps[(int)VehicleWheelOrdering.RearRight].SprungMass = suspSprungMasses[(int)VehicleWheelOrdering.RearRight];

			//Set up the camber.
			//Remember that the left and right wheels need opposite camber so that the car preserves symmetry about the forward direction.
			//Set the camber to 0.0f when the spring is neither compressed or elongated.
			const float camberAngleAtRest = 0;
			susps[(int)VehicleWheelOrdering.FrontLeft].CamberAtRest = camberAngleAtRest;
			susps[(int)VehicleWheelOrdering.FrontRight].CamberAtRest = -camberAngleAtRest;
			susps[(int)VehicleWheelOrdering.RearLeft].CamberAtRest = camberAngleAtRest;
			susps[(int)VehicleWheelOrdering.RearRight].CamberAtRest = -camberAngleAtRest;
			//Set the wheels to camber inwards at maximum droop (the left and right wheels almost form a V shape)
			const float camberAngleAtMaxDroop = 0.001f;
			susps[(int)VehicleWheelOrdering.FrontLeft].CamberAtMaxDroop = camberAngleAtMaxDroop;
			susps[(int)VehicleWheelOrdering.FrontRight].CamberAtMaxDroop = -camberAngleAtMaxDroop;
			susps[(int)VehicleWheelOrdering.RearLeft].CamberAtMaxDroop = camberAngleAtMaxDroop;
			susps[(int)VehicleWheelOrdering.RearRight].CamberAtMaxDroop = -camberAngleAtMaxDroop;
			//Set the wheels to camber outwards at maximum compression (the left and right wheels almost form a A shape).
			const float camberAngleAtMaxCompression = -0.001f;
			susps[(int)VehicleWheelOrdering.FrontLeft].CamberAtMaxCompression = camberAngleAtMaxCompression;
			susps[(int)VehicleWheelOrdering.FrontRight].CamberAtMaxCompression = -camberAngleAtMaxCompression;
			susps[(int)VehicleWheelOrdering.RearLeft].CamberAtMaxCompression = camberAngleAtMaxCompression;
			susps[(int)VehicleWheelOrdering.RearRight].CamberAtMaxCompression = -camberAngleAtMaxCompression;

			//We need to set up geometry data for the suspension, wheels, and tires.
			//We already know the wheel centers described as offsets from the actor center and the center of mass offset from actor center.
			//From here we can approximate application points for the tire and suspension forces.
			//Lets assume that the suspension travel directions are absolutely vertical.
			//Also assume that we apply the tire and suspension forces 30cm below the center of mass.
			var suspTravelDirections = new[] { new Vector3(0, -1, 0), new Vector3(0, -1, 0), new Vector3(0, -1, 0), new Vector3(0, -1, 0) };
			var wheelCentreCMOffsets = new Vector3[4];
			var suspForceAppCMOffsets = new Vector3[4];
			var tireForceAppCMOffsets = new Vector3[4];
			for (int i = 0; i < 4; i++)
			{
				wheelCentreCMOffsets[i] = wheelCentreOffsets[i] - chassisCMOffset;
				suspForceAppCMOffsets[i] = new Vector3(wheelCentreCMOffsets[i].X, -0.3f, wheelCentreCMOffsets[i].Z);
				tireForceAppCMOffsets[i] = new Vector3(wheelCentreCMOffsets[i].X, -0.3f, wheelCentreCMOffsets[i].Z);
			}

			//Now add the wheel, tire and suspension data.
			for (int i = 0; i < 4; i++)
			{
				wheelsData.SetWheelData(i, wheels[i]);
				wheelsData.SetTireData(i, tires[i]);
				wheelsData.SetSuspensionData(i, susps[i]);
				wheelsData.SetSuspensionTravelDirection(i, suspTravelDirections[i]);
				wheelsData.SetWheelCentreOffset(i, wheelCentreCMOffsets[i]);
				wheelsData.SetSuspensionForceApplicationPointOffset(i, suspForceAppCMOffsets[i]);
				wheelsData.SetTireForceApplicationPointOffset(i, tireForceAppCMOffsets[i]);
			}

			//Set the car to perform 3 sub-steps when it moves with a forwards speed of less than 5.0 
			//and with a single step when it moves at speed greater than or equal to 5.0.
			wheelsData.SetSubStepCount(5.0f, 3, 1);


			//Now set up the differential, engine, gears, clutch, and ackermann steering.

			//Diff
			var diff = new VehicleDifferential4WData();
			diff.Type = VehicleDifferentialType.LimitedSlip4WheelDrive;
			driveData.SetDifferentialData(diff);

			//Engine
			var engine = new VehicleEngineData();
			engine.PeakTorque = 500.0f;
			engine.MaxOmega = 600.0f;//approx 6000 rpm
			driveData.SetEngineData(engine);

			//Gears
			var gears = new VehicleGearsData();
			gears.SwitchTime = 0.5f;
			driveData.SetGearsData(gears);

			//Clutch
			var clutch = new VehicleClutchData();
			clutch.Strength = 10.0f;
			driveData.SetClutchData(clutch);

			//Ackermann steer accuracy
			var ackermann = new VehicleAckermannGeometryData();
			ackermann.Accuracy = 1.0f;
			ackermann.AxleSeparation = wheelCentreOffsets[(int)VehicleWheelOrdering.FrontLeft].Z - wheelCentreOffsets[(int)VehicleWheelOrdering.RearLeft].Z;
			ackermann.FrontWidth = wheelCentreOffsets[(int)VehicleWheelOrdering.FrontRight].X - wheelCentreOffsets[(int)VehicleWheelOrdering.FrontLeft].X;
			ackermann.RearWidth = wheelCentreOffsets[(int)VehicleWheelOrdering.RearRight].X - wheelCentreOffsets[(int)VehicleWheelOrdering.RearLeft].X;
			driveData.SetAckermannGeometryData(ackermann);

			// Create actor
			var vehActor = CreateVehicleActor4W(chassisData, wheelConvexMeshes, chassisConvexMesh, this.Scene, _chassisMaterialNonDrivable);
		}

		private RigidDynamic CreateVehicleActor4W(
				VehicleChassisData chassisData,
				ConvexMesh[] wheelConvexMeshes,
				ConvexMesh chassisConvexMesh,
				Scene scene,
				Material material)
		{
			//We need a rigid body actor for the vehicle.
			//Don't forget to add the actor the scene after setting up the associated vehicle.
			RigidDynamic vehActor = scene.Physics.CreateRigidDynamic();

			//We need to add wheel collision shapes, their local poses, a material for the wheels, and a simulation filter for the wheels.
			ConvexMeshGeometry frontLeftWheelGeom = new ConvexMeshGeometry(wheelConvexMeshes[0]);
			ConvexMeshGeometry frontRightWheelGeom = new ConvexMeshGeometry(wheelConvexMeshes[1]);
			ConvexMeshGeometry rearLeftWheelGeom = new ConvexMeshGeometry(wheelConvexMeshes[2]);
			ConvexMeshGeometry rearRightWheelGeom = new ConvexMeshGeometry(wheelConvexMeshes[3]);

			var wheelGeometries = new[]
			{
				frontLeftWheelGeom,
				frontRightWheelGeom,
				rearLeftWheelGeom,
				rearRightWheelGeom
			};

			var wheelLocalPoses = new[]
			{
				Matrix.Identity,
				Matrix.Identity,
				Matrix.Identity,
				Matrix.Identity
			};

			Material wheelMaterial = material;

			FilterData wheelCollFilterData = new FilterData();
			wheelCollFilterData.Word0 = (uint)CollisionFlags.COLLISION_FLAG_WHEEL;
			wheelCollFilterData.Word1 = (uint)CollisionFlags.COLLISION_FLAG_WHEEL_AGAINST;

			//We need to add chassis collision shapes, their local poses, a material for the chassis, and a simulation filter for the chassis.
			var chassisConvexGeom = new ConvexMeshGeometry(chassisConvexMesh);
			var chassisGeoms = new[]
			{
				chassisConvexGeom 
			};

			var chassisLocalPoses = new[]
			{
				Matrix.Identity
			};

			Material chassisMaterial = material;

			FilterData chassisCollFilterData = new FilterData();
			chassisCollFilterData.Word0 = (uint)CollisionFlags.COLLISION_FLAG_CHASSIS;
			chassisCollFilterData.Word1 = (uint)CollisionFlags.COLLISION_FLAG_CHASSIS_AGAINST;

			//Create a query filter data for the car to ensure that cars
			//do not attempt to drive on themselves.
			FilterData vehQryFilterData = new FilterData();
			//SampleVehicleSetupVehicleShapeQueryFilterData(&vehQryFilterData);
			vehQryFilterData.Word3 = (uint)DrivableSurfaces.SAMPLEVEHICLE_UNDRIVABLE_SURFACE;

			//Set up the physx rigid body actor with shapes, local poses, and filters.
			setupActor
				(vehActor,
				vehQryFilterData,
				wheelGeometries, wheelLocalPoses, wheelMaterial, wheelCollFilterData,
				chassisGeoms, chassisLocalPoses, chassisMaterial, chassisCollFilterData,
				chassisData,
				scene.Physics);

			return vehActor;
		}

		private void setupActor(
			RigidDynamic vehActor,
			FilterData vehQryFilterData,
			Geometry[] wheelGeometries, Matrix[] wheelLocalPoses, Material wheelMaterial, FilterData wheelCollFilterData,
			Geometry[] chassisGeometries, Matrix[] chassisLocalPoses, Material chassisMaterial, FilterData chassisCollFilterData,
			VehicleChassisData chassisData,
			Physics physics)
		{
			//Add all the wheel shapes to the actor.
			for (int i = 0; i < wheelLocalPoses.Length; i++)
			{
				var wheelShape = vehActor.CreateShape(wheelGeometries[i], wheelMaterial);
				wheelShape.QueryFilterData = vehQryFilterData;
				wheelShape.SimulationFilterData = wheelCollFilterData;
				wheelShape.LocalPose = wheelLocalPoses[i];
			}

			//Add the chassis shapes to the actor.
			for (int i = 0; i < chassisGeometries.Length; i++)
			{
				var chassisShape = vehActor.CreateShape(chassisGeometries[i], chassisMaterial);

				chassisShape.QueryFilterData = vehQryFilterData;
				chassisShape.SimulationFilterData = chassisCollFilterData;
				chassisShape.LocalPose = chassisLocalPoses[i];
			}

			vehActor.Mass = chassisData.Mass;
			vehActor.MassSpaceInertiaTensor = chassisData.MomentOfInertia;
			vehActor.CenterOfMassLocalPose = Matrix.Translation(chassisData.CenterOfMassOffset);
		}

		private void ComputeWheelWidthsAndRadii(ConvexMesh[] wheelConvexMeshes, ref float[] wheelWidths, ref float[] wheelRadii)
		{
			for (int i = 0; i < 4; i++)
			{
				int numWheelVerts = wheelConvexMeshes[i].NumberOfVertices;
				var wheelVerts = wheelConvexMeshes[i].GetVertices();

				Vector3 wheelMin = new Vector3(float.MaxValue, float.MaxValue, float.MaxValue);
				Vector3 wheelMax = new Vector3(-float.MaxValue, -float.MaxValue, -float.MaxValue);
				for (int j = 0; j < numWheelVerts; j++)
				{
					wheelMin.X = System.Math.Min(wheelMin.X, wheelVerts[j].X);
					wheelMin.Y = System.Math.Min(wheelMin.Y, wheelVerts[j].Y);
					wheelMin.Z = System.Math.Min(wheelMin.Z, wheelVerts[j].Z);
					wheelMax.X = System.Math.Max(wheelMax.X, wheelVerts[j].X);
					wheelMax.Y = System.Math.Max(wheelMax.Y, wheelVerts[j].Y);
					wheelMax.Z = System.Math.Max(wheelMax.Z, wheelVerts[j].Z);
				}
				wheelWidths[i] = wheelMax.X - wheelMin.X;
				wheelRadii[i] = System.Math.Max(wheelMax.Y, wheelMax.Z) * 0.975f;
			}
		}

		private Vector3 ComputeChassisAABBDimensions(ConvexMesh chassisConvexMesh)
		{
			int numChassisVerts = chassisConvexMesh.NumberOfVertices;
			var chassisVerts = chassisConvexMesh.GetVertices();

			Vector3 chassisMin = new Vector3(float.MaxValue, float.MaxValue, float.MaxValue);
			Vector3 chassisMax = new Vector3(-float.MaxValue, -float.MaxValue, -float.MaxValue);

			for (int i = 0; i < numChassisVerts; i++)
			{
				chassisMin.X = System.Math.Min(chassisMin.X, chassisVerts[i].X);
				chassisMin.Y = System.Math.Min(chassisMin.Y, chassisVerts[i].Y);
				chassisMin.Z = System.Math.Min(chassisMin.Z, chassisVerts[i].Z);
				chassisMax.X = System.Math.Max(chassisMax.X, chassisVerts[i].X);
				chassisMax.Y = System.Math.Max(chassisMax.Y, chassisVerts[i].Y);
				chassisMax.Z = System.Math.Max(chassisMax.Z, chassisVerts[i].Z);
			}
			Vector3 chassisDims = chassisMax - chassisMin;
			return chassisDims;
		}

		private void createVehicle4WSimulationData(
			float chassisMass, ConvexMesh chassisConvexMesh,
			float wheelMass, ConvexMesh[] wheelConvexMeshes, Vector3[] wheelCentreOffsets,
			VehicleWheelsSimData wheelsData, VehicleDriveSimData4W driveData, VehicleChassisData chassisData)
		{
			//Extract the chassis AABB dimensions from the chassis convex mesh.
			Vector3 chassisDims = ComputeChassisAABBDimensions(chassisConvexMesh);

			//The origin is at the center of the chassis mesh.
			//Set the center of mass to be below this point and a little towards the front.
			Vector3 chassisCMOffset = new Vector3(0.0f, -chassisDims.Y * 0.5f + 0.65f, 0.25f);

			//Now compute the chassis mass and moment of inertia.
			//Use the moment of inertia of a cuboid as an approximate value for the chassis moi.
			Vector3 chassisMOI = new Vector3
				((chassisDims.Y * chassisDims.Y + chassisDims.Z * chassisDims.Z) * chassisMass / 12.0f,
				 (chassisDims.X * chassisDims.X + chassisDims.Z * chassisDims.Z) * chassisMass / 12.0f,
				 (chassisDims.X * chassisDims.X + chassisDims.Y * chassisDims.Y) * chassisMass / 12.0f);
			//A bit of tweaking here.  The car will have more responsive turning if we reduce the 	
			//y-component of the chassis moment of inertia.
			chassisMOI.Y *= 0.8f;

			//Let's set up the chassis data structure now.
			chassisData.Mass = chassisMass;
			chassisData.MomentOfInertia = chassisMOI;
			chassisData.CenterOfMassOffset = chassisCMOffset;

			//Compute the sprung masses of each suspension spring using a helper function.
			var suspSprungMasses = VehicleUtilSetup.ComputeSprungMasses(wheelCentreOffsets, chassisCMOffset, chassisMass, 1);

			//Extract the wheel radius and width from the wheel convex meshes.
			var wheelWidths = new float[4];
			var wheelRadii = new float[4];
			ComputeWheelWidthsAndRadii(wheelConvexMeshes, ref wheelWidths, ref wheelRadii);

			//Now compute the wheel masses and inertias components around the axle's axis.
			//http://en.wikipedia.org/wiki/List_of_moments_of_inertia
			var wheelMOIs = new float[4];
			for (int i = 0; i < 4; i++)
			{
				wheelMOIs[i] = 0.5f * wheelMass * wheelRadii[i] * wheelRadii[i];
			}
			//Let's set up the wheel data structures now with radius, mass, and moi.
			var wheels = new VehicleWheelData[4];
			for (int i = 0; i < 4; i++)
			{
				wheels[i].Radius = wheelRadii[i];
				wheels[i].Mass = wheelMass;
				wheels[i].MomentOfInertia = wheelMOIs[i];
				wheels[i].Width = wheelWidths[i];
			}
			//Disable the handbrake from the front wheels and enable for the rear wheels
			wheels[(int)VehicleWheelOrdering.FrontLeft].MaxHandBrakeTorque = 0.0f;
			wheels[(int)VehicleWheelOrdering.FrontRight].MaxHandBrakeTorque = 0.0f;
			wheels[(int)VehicleWheelOrdering.RearLeft].MaxHandBrakeTorque = 4000.0f;
			wheels[(int)VehicleWheelOrdering.RearRight].MaxHandBrakeTorque = 4000.0f;
			//Enable steering for the front wheels and disable for the front wheels.
			wheels[(int)VehicleWheelOrdering.FrontLeft].MaxSteer = (float)(System.Math.PI * 0.3333);
			wheels[(int)VehicleWheelOrdering.FrontRight].MaxSteer = (float)(System.Math.PI * 0.3333);
			wheels[(int)VehicleWheelOrdering.RearLeft].MaxSteer = 0.0f;
			wheels[(int)VehicleWheelOrdering.RearRight].MaxSteer = 0.0f;

			//Let's set up the tire data structures now.
			//////////Put slicks on the front tires and wets on the rear tires.
			//Put slicks on the front tires and slicks on the rear tires.
			var tires = new VehicleTireData[4];
			tires[(int)VehicleWheelOrdering.FrontLeft].Type = TIRE_TYPE_SLICKS;
			tires[(int)VehicleWheelOrdering.FrontRight].Type = TIRE_TYPE_SLICKS;
			tires[(int)VehicleWheelOrdering.RearLeft].Type = TIRE_TYPE_SLICKS;
			tires[(int)VehicleWheelOrdering.RearRight].Type = TIRE_TYPE_SLICKS;

			//Let's set up the suspension data structures now.
			var susps = new VehicleSuspensionData[4];
			for (int i = 0; i < 4; i++)
			{
				susps[i].MaxCompression = 0.3f;
				susps[i].MaxDroop = 0.1f;
				susps[i].SpringStrength = 35000.0f;
				susps[i].SpringDamperRate = 4500.0f;
			}
			susps[(int)VehicleWheelOrdering.FrontLeft].SprungMass = suspSprungMasses[(int)VehicleWheelOrdering.FrontLeft];
			susps[(int)VehicleWheelOrdering.FrontRight].SprungMass = suspSprungMasses[(int)VehicleWheelOrdering.FrontRight];
			susps[(int)VehicleWheelOrdering.RearLeft].SprungMass = suspSprungMasses[(int)VehicleWheelOrdering.RearLeft];
			susps[(int)VehicleWheelOrdering.RearRight].SprungMass = suspSprungMasses[(int)VehicleWheelOrdering.RearRight];

			//Set up the camber.
			//Remember that the left and right wheels need opposite camber so that the car preserves symmetry about the forward direction.
			//Set the camber to 0.0f when the spring is neither compressed or elongated.
			const float camberAngleAtRest = 0;
			susps[(int)VehicleWheelOrdering.FrontLeft].CamberAtRest = camberAngleAtRest;
			susps[(int)VehicleWheelOrdering.FrontRight].CamberAtRest = -camberAngleAtRest;
			susps[(int)VehicleWheelOrdering.RearLeft].CamberAtRest = camberAngleAtRest;
			susps[(int)VehicleWheelOrdering.RearRight].CamberAtRest = -camberAngleAtRest;
			//Set the wheels to camber inwards at maximum droop (the left and right wheels almost form a V shape)
			const float camberAngleAtMaxDroop = 0.001f;
			susps[(int)VehicleWheelOrdering.FrontLeft].CamberAtMaxDroop = camberAngleAtMaxDroop;
			susps[(int)VehicleWheelOrdering.FrontRight].CamberAtMaxDroop = -camberAngleAtMaxDroop;
			susps[(int)VehicleWheelOrdering.RearLeft].CamberAtMaxDroop = camberAngleAtMaxDroop;
			susps[(int)VehicleWheelOrdering.RearRight].CamberAtMaxDroop = -camberAngleAtMaxDroop;
			//Set the wheels to camber outwards at maximum compression (the left and right wheels almost form a A shape).
			const float camberAngleAtMaxCompression = -0.001f;
			susps[(int)VehicleWheelOrdering.FrontLeft].CamberAtMaxCompression = camberAngleAtMaxCompression;
			susps[(int)VehicleWheelOrdering.FrontRight].CamberAtMaxCompression = -camberAngleAtMaxCompression;
			susps[(int)VehicleWheelOrdering.RearLeft].CamberAtMaxCompression = camberAngleAtMaxCompression;
			susps[(int)VehicleWheelOrdering.RearRight].CamberAtMaxCompression = -camberAngleAtMaxCompression;

			//We need to set up geometry data for the suspension, wheels, and tires.
			//We already know the wheel centers described as offsets from the actor center and the center of mass offset from actor center.
			//From here we can approximate application points for the tire and suspension forces.
			//Lets assume that the suspension travel directions are absolutely vertical.
			//Also assume that we apply the tire and suspension forces 30cm below the center of mass.
			var suspTravelDirections = new[] { new Vector3(0, -1, 0), new Vector3(0, -1, 0), new Vector3(0, -1, 0), new Vector3(0, -1, 0) };
			var wheelCentreCMOffsets = new Vector3[4];
			var suspForceAppCMOffsets = new Vector3[4];
			var tireForceAppCMOffsets = new Vector3[4];
			for (int i = 0; i < 4; i++)
			{
				wheelCentreCMOffsets[i] = wheelCentreOffsets[i] - chassisCMOffset;
				suspForceAppCMOffsets[i] = new Vector3(wheelCentreCMOffsets[i].X, -0.3f, wheelCentreCMOffsets[i].Z);
				tireForceAppCMOffsets[i] = new Vector3(wheelCentreCMOffsets[i].X, -0.3f, wheelCentreCMOffsets[i].Z);
			}

			//Now add the wheel, tire and suspension data.
			for (int i = 0; i < 4; i++)
			{
				wheelsData.SetWheelData(i, wheels[i]);
				wheelsData.SetTireData(i, tires[i]);
				wheelsData.SetSuspensionData(i, susps[i]);
				wheelsData.SetSuspensionTravelDirection(i, suspTravelDirections[i]);
				wheelsData.SetWheelCentreOffset(i, wheelCentreCMOffsets[i]);
				wheelsData.SetSuspensionForceApplicationPointOffset(i, suspForceAppCMOffsets[i]);
				wheelsData.SetTireForceApplicationPointOffset(i, tireForceAppCMOffsets[i]);
			}

			//Set the car to perform 3 sub-steps when it moves with a forwards speed of less than 5.0 
			//and with a single step when it moves at speed greater than or equal to 5.0.
			wheelsData.SetSubStepCount(5.0f, 3, 1);


			//Now set up the differential, engine, gears, clutch, and ackermann steering.

			//Diff
			var diff = new VehicleDifferential4WData();
			diff.Type = VehicleDifferentialType.LimitedSlip4WheelDrive;
			driveData.SetDifferentialData(diff);

			//Engine
			var engine = new VehicleEngineData();
			engine.PeakTorque = 500.0f;
			engine.MaxOmega = 600.0f;//approx 6000 rpm
			driveData.SetEngineData(engine);

			//Gears
			var gears = new VehicleGearsData();
			gears.SwitchTime = 0.5f;
			driveData.SetGearsData(gears);

			//Clutch
			var clutch = new VehicleClutchData();
			clutch.Strength = 10.0f;
			driveData.SetClutchData(clutch);

			//Ackermann steer accuracy
			var ackermann = new VehicleAckermannGeometryData();
			ackermann.Accuracy = 1.0f;
			ackermann.AxleSeparation = wheelCentreOffsets[(int)VehicleWheelOrdering.FrontLeft].Z - wheelCentreOffsets[(int)VehicleWheelOrdering.RearLeft].Z;
			ackermann.FrontWidth = wheelCentreOffsets[(int)VehicleWheelOrdering.FrontRight].X - wheelCentreOffsets[(int)VehicleWheelOrdering.FrontLeft].X;
			ackermann.RearWidth = wheelCentreOffsets[(int)VehicleWheelOrdering.RearRight].X - wheelCentreOffsets[(int)VehicleWheelOrdering.RearLeft].X;
			driveData.SetAckermannGeometryData(ackermann);

			// Create actor
			var vehActor = CreateVehicleActor4W(chassisData, wheelConvexMeshes, chassisConvexMesh, this.Scene, material);
		}

		private RigidDynamic CreateVehicleActor4W(
				VehicleChassisData chassisData,
				ConvexMesh[] wheelConvexMeshes,
				ConvexMesh chassisConvexMesh,
				Scene scene,
				Material material)
		{
			//We need a rigid body actor for the vehicle.
			//Don't forget to add the actor the scene after setting up the associated vehicle.
			RigidDynamic vehActor = scene.Physics.CreateRigidDynamic();

			//We need to add wheel collision shapes, their local poses, a material for the wheels, and a simulation filter for the wheels.
			ConvexMeshGeometry frontLeftWheelGeom = new ConvexMeshGeometry(wheelConvexMeshes[0]);
			ConvexMeshGeometry frontRightWheelGeom = new ConvexMeshGeometry(wheelConvexMeshes[1]);
			ConvexMeshGeometry rearLeftWheelGeom = new ConvexMeshGeometry(wheelConvexMeshes[2]);
			ConvexMeshGeometry rearRightWheelGeom = new ConvexMeshGeometry(wheelConvexMeshes[3]);

			var wheelGeometries = new[]
			{
				frontLeftWheelGeom,
				frontRightWheelGeom,
				rearLeftWheelGeom,
				rearRightWheelGeom
			};

					var wheelLocalPoses = new[]
			{
				Matrix.Identity,
				Matrix.Identity,
				Matrix.Identity,
				Matrix.Identity
			};

			Material wheelMaterial = material;

			FilterData wheelCollFilterData;
			wheelCollFilterData.Word0 = (uint)CollisionFlags.COLLISION_FLAG_WHEEL;
			wheelCollFilterData.Word1 = (uint)CollisionFlags.COLLISION_FLAG_WHEEL_AGAINST;

			//We need to add chassis collision shapes, their local poses, a material for the chassis, and a simulation filter for the chassis.
			var chassisConvexGeom = new ConvexMeshGeometry(chassisConvexMesh);
			var chassisGeoms = new[]
			{
				chassisConvexGeom 
			};

					var chassisLocalPoses = new[]
			{
				Matrix.Identity
			};

			Material chassisMaterial = material;

			FilterData chassisCollFilterData;
			chassisCollFilterData.Word0 = (uint)CollisionFlags.COLLISION_FLAG_CHASSIS;
			chassisCollFilterData.Word1 = (uint)CollisionFlags.COLLISION_FLAG_CHASSIS_AGAINST;

			//Create a query filter data for the car to ensure that cars
			//do not attempt to drive on themselves.
			FilterData vehQryFilterData;
			//SampleVehicleSetupVehicleShapeQueryFilterData(&vehQryFilterData);
			vehQryFilterData.Word3 = (uint)DrivableSurfaces.SAMPLEVEHICLE_UNDRIVABLE_SURFACE;

			//Set up the physx rigid body actor with shapes, local poses, and filters.
			setupActor
				(vehActor,
				vehQryFilterData,
				wheelGeometries, wheelLocalPoses, 4, wheelMaterial, wheelCollFilterData,
				chassisGeoms, chassisLocalPoses, 1, chassisMaterial, chassisCollFilterData,
				chassisData,
				scene.Physics);

			return vehActor;
		}

		private void setupActor(
			RigidDynamic vehActor,
			FilterData vehQryFilterData,
			Geometry[] wheelGeometries, Matrix[] wheelLocalPoses, Material wheelMaterial, FilterData wheelCollFilterData,
			Geometry[] chassisGeometries, Matrix[] chassisLocalPoses, Material chassisMaterial, FilterData chassisCollFilterData,
			VehicleChassisData chassisData,
			Physics physics)
		{
			//Add all the wheel shapes to the actor.
			for (int i = 0; i < wheelLocalPoses.Length; i++)
			{
				var wheelShape = vehActor.CreateShape(wheelGeometries[i], wheelMaterial);
				wheelShape.QueryFilterData = vehQryFilterData;
				wheelShape.SimulationFilterData = wheelCollFilterData;
				wheelShape.LocalPose = wheelLocalPoses[i];
			}

			//Add the chassis shapes to the actor.
			for (int i = 0; i < chassisGeometries.Length; i++)
			{
				var chassisShape = vehActor.CreateShape(chassisGeometries[i], chassisMaterial);

				chassisShape.QueryFilterData = vehQryFilterData;
				chassisShape.SimulationFilterData = chassisCollFilterData;
				chassisShape.LocalPose = chassisLocalPoses[i];
			}

			vehActor.Mass = chassisData.Mass;
			vehActor.MassSpaceInertiaTensor = chassisData.MomentOfInertia;
			vehActor.CenterOfMassLocalPose = Matrix.Translation(chassisData.CenterOfMassOffset);
		}

		protected override void Update(TimeSpan elapsed)
		{

		}

		protected override void Draw()
		{

		}
	}
}