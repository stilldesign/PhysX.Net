using System;
using System.Collections.Generic;
using System.Xml;
using System.IO;

using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;
using Microsoft.Xna.Framework.Content;

using StillDesign.PhysX;

namespace StillDesign
{
	public partial class Demo1
	{
		/// <summary>Simple examples of all the PhysX bits running together</summary>
		private void LoadPhysics()
		{
			// The ground plane (if created) sould be the first actor
			_groundActor = _scene.Actors[ 0 ];
				_groundActor.Name = "Default Ground Plane";

			//
			
			#region Some Boxes
			for( int x = 0; x < 5; x++ )
			{
				BoxShapeDescription boxShapeDesc = new BoxShapeDescription( 2, 3, 8 );
				
				ActorDescription actorDesc = new ActorDescription();
					actorDesc.Name = String.Format( "Box {0}", x );
					actorDesc.BodyDescription = new BodyDescription( 10.0f );
					actorDesc.GlobalPose = Matrix.CreateTranslation( 100, 15 + 3 * x, 20 );
					actorDesc.Shapes.Add( boxShapeDesc );

				Actor actor = _scene.CreateActor( actorDesc );
			}
			#endregion

			#region Cloth (Flag)
			{
				// Create a Grid of Points
				VertexGrid grid = CreateGrid( 10, 10 );

				ClothMeshDescription clothMeshDesc = new ClothMeshDescription();
					clothMeshDesc.AllocateVertices<Vector3>( grid.Points.Length );
					clothMeshDesc.AllocateTriangles<int>( grid.Indices.Length / 3 );

					clothMeshDesc.VertexCount = grid.Points.Length;
					clothMeshDesc.TriangleCount = grid.Indices.Length / 3;

					clothMeshDesc.VerticesStream.SetData<Vector3>( grid.Points );
					clothMeshDesc.TriangleStream.SetData<int>( grid.Indices );

					// We are using 32 bit integers, so make sure the 16 bit flag is removed.
					// 32 bits are the default, so this isn't technically needed
					clothMeshDesc.Flags &= ~MeshFlag.Indices16Bit;

				// Write the cooked data to memory
				MemoryStream memoryStream = new MemoryStream();

				Cooking.InitializeCooking();
				Cooking.CookClothMesh( clothMeshDesc, memoryStream );
				Cooking.CloseCooking();

				// Need to reset the position of the stream to the beginning
				memoryStream.Position = 0;

				ClothMesh clothMesh = _core.CreateClothMesh( memoryStream );

				//

				ClothDescription clothDesc = new ClothDescription();
					clothDesc.ClothMesh = clothMesh;
					clothDesc.Flags = ClothFlag.Gravity | ClothFlag.Bending | ClothFlag.CollisionTwoway | ClothFlag.Visualization;
					clothDesc.GlobalPose = 
						Matrix.CreateFromYawPitchRoll( 0, Mathematics.PiOver2, Mathematics.PiOver2 ) *
						Matrix.CreateTranslation( 0, 20, 0 );

					clothDesc.MeshData.AllocatePositions<Vector3>( grid.Points.Length );
					clothDesc.MeshData.AllocateIndices<int>( grid.Indices.Length );
					clothDesc.MeshData.MaximumVertices = grid.Points.Length;
					clothDesc.MeshData.MaximumIndices = grid.Indices.Length;

				_flag = _scene.CreateCloth( clothDesc );

				// Flag Pole
				ActorDescription flagPoleActorDesc = new ActorDescription();
					flagPoleActorDesc.Shapes.Add( new BoxShapeDescription( 1.0f, 20.0f, 1.0f ) );
					flagPoleActorDesc.GlobalPose = Matrix.CreateTranslation( 0, 10, 0 );

				Actor flagPoleActor = _scene.CreateActor( flagPoleActorDesc );

				_flag.AttachToShape( flagPoleActor.Shapes[ 0 ], 0 );
				_flag.WindAcceleration = new Vector3( 10, 10, 10 );
				_flag.BendingStiffness = 0.1f;
			}
			#endregion

			#region Revolute Joint
			{
				BoxShapeDescription boxShapeDescA = new BoxShapeDescription( 3, 3, 3 );
				BoxShapeDescription boxShapeDescB = new BoxShapeDescription( 3, 3, 3 );

				ActorDescription actorDescA = new ActorDescription();
					actorDescA.BodyDescription = new BodyDescription( 10.0f );
					actorDescA.GlobalPose = Matrix.CreateTranslation( 75, 1.5f, 55 );
					actorDescA.Shapes.Add( boxShapeDescA );
				Actor actorA = _scene.CreateActor( actorDescA );

				ActorDescription actorDescB = new ActorDescription();
					actorDescB.BodyDescription = new BodyDescription( 10.0f );
					actorDescB.GlobalPose = Matrix.CreateTranslation( 70, 1.5f, 55 );
					actorDescB.Shapes.Add( boxShapeDescB );
				Actor actorB = _scene.CreateActor( actorDescB );

				//

				RevoluteJointDescription revoluteJointDesc = new RevoluteJointDescription();
					revoluteJointDesc.Actor1 = actorA;
					revoluteJointDesc.Actor2 = actorB;
					revoluteJointDesc.Motor = new MotorDescription( 20, 20.1f, true );
					revoluteJointDesc.Flags |= RevoluteJointFlag.MotorEnabled;
					revoluteJointDesc.SetGlobalAnchor( new Vector3( 73.5f, 1.5f, 55 ) );
					revoluteJointDesc.SetGlobalAxis( new Vector3( 1, 0, 0 ) );

				RevoluteJoint revoluteJoint = _scene.CreateJoint( revoluteJointDesc ) as RevoluteJoint;
			}
			#endregion

			#region Prismatic Joint with Limit
			{
				Actor actorA, actorB;
				{
					BoxShapeDescription boxShapeDesc = new BoxShapeDescription( 3, 3, 3 );

					BodyDescription bodyDesc = new BodyDescription( 10.0f );
						bodyDesc.BodyFlags |= BodyFlag.Kinematic;

					ActorDescription actorDesc = new ActorDescription();
						actorDesc.BodyDescription = bodyDesc;
						actorDesc.GlobalPose = Matrix.CreateTranslation( 70, 25, 65 );
						actorDesc.Shapes.Add( boxShapeDesc );
					actorA = _scene.CreateActor( actorDesc );
				}
				{
					BoxShapeDescription boxShapeDesc = new BoxShapeDescription( 3, 3, 3 );

					ActorDescription actorDesc = new ActorDescription();
						actorDesc.BodyDescription = new BodyDescription( 10.0f );
						actorDesc.GlobalPose = Matrix.CreateTranslation( 70, 15, 65 );
						actorDesc.Shapes.Add( boxShapeDesc );
					actorB = _scene.CreateActor( actorDesc );
				}

				PrismaticJointDescription prismaticJointDesc = new PrismaticJointDescription();
					prismaticJointDesc.Actor1 = actorA;
					prismaticJointDesc.Actor2 = actorB;
					prismaticJointDesc.SetGlobalAnchor( new Vector3( 70, 20, 65 ) );
					prismaticJointDesc.SetGlobalAxis( new Vector3( 0, 1, 0 ) );

				PrismaticJoint prismaticJoint = _scene.CreateJoint( prismaticJointDesc ) as PrismaticJoint;

				LimitPlane limitPlane = new LimitPlane( new Vector3( 0, 1, 0 ), new Vector3( -30, 8, -30 ), 0 );
					prismaticJoint.AddLimitPlane( limitPlane );
			}
			#endregion

			#region Fluid
			{
				const int maximumParticles = 1000;

				FluidEmitterDescription fluidEmitterDesc = new FluidEmitterDescription();
					fluidEmitterDesc.DimensionX = 0.5f;
					fluidEmitterDesc.DimensionY = 0.5f;
					fluidEmitterDesc.Flags |= ( FluidEmitterFlag.Enabled | FluidEmitterFlag.Visualization );
					fluidEmitterDesc.Rate = 15;
					fluidEmitterDesc.RelativePose = Matrix.CreateTranslation( -40, 10, 50 );
					fluidEmitterDesc.Shape = EmitterShape.Rectangular;
					fluidEmitterDesc.Type = EmitterType.ConstantFlowRate;
					fluidEmitterDesc.RandomAngle = 0.5f;

				FluidDescription fluidDesc = new FluidDescription();
					fluidDesc.Emitters.Add( fluidEmitterDesc );
					fluidDesc.Flags = FluidFlag.Enabled | FluidFlag.Visualization;
					fluidDesc.MaximumParticles = maximumParticles;
					fluidDesc.ParticleWriteData.AllocatePositionBuffer<Vector3>( maximumParticles );
				
				Fluid fluid = _scene.CreateFluid( fluidDesc );

				// Ledge
				{
					BoxShapeDescription boxShapeDesc = new BoxShapeDescription( 5, 0.1f, 5 );
					
					ActorDescription drainActorDesc = new ActorDescription();
						drainActorDesc.Shapes.Add( boxShapeDesc );
						drainActorDesc.GlobalPose = Matrix.CreateRotationX( 0.5f ) * Matrix.CreateTranslation( -40, 5, 52 );

					Actor drianActor = _scene.CreateActor( drainActorDesc );
				}

				// Drain
				{
					BoxShapeDescription boxShapeDesc = new BoxShapeDescription( 5, 0.1f, 5 );
						boxShapeDesc.Flags |= ShapeFlag.FluidDrain;

					ActorDescription drainActorDesc = new ActorDescription();
						drainActorDesc.Shapes.Add( boxShapeDesc );
						drainActorDesc.GlobalPose = Matrix.CreateTranslation( -40, 0, 55 );

					Actor drianActor = _scene.CreateActor( drainActorDesc );
				}
			}
			#endregion

			#region Force Field
			{
				BoxForceFieldShapeDescription boxForceFieldShapeDesc = new BoxForceFieldShapeDescription();
					boxForceFieldShapeDesc.Size = new Vector3( 10, 10, 10 );
				
				ForceFieldLinearKernelDescription kernelDesc = new ForceFieldLinearKernelDescription();
					kernelDesc.Constant = new Vector3( 0, 100.0f, 0 );

				ForceFieldLinearKernel kernel = _scene.CreateForceFieldLinearKernel( kernelDesc );

				ForceFieldShapeGroupDescription shapeGroupDesc = new ForceFieldShapeGroupDescription();
					shapeGroupDesc.Shapes.Add( boxForceFieldShapeDesc );

				ForceFieldShapeGroup shapeGroup = _scene.CreateForceFieldShapeGroup( shapeGroupDesc );

				BoxForceFieldShape boxForceFieldShape = shapeGroup.CreateShape( boxForceFieldShapeDesc ) as BoxForceFieldShape;
					boxForceFieldShape.Pose = Matrix.CreateTranslation( 30, 5, 0 );

				ForceFieldDescription forceFieldDesc = new ForceFieldDescription();
					forceFieldDesc.Kernel = kernel;
					forceFieldDesc.ShapeGroups.Add( shapeGroup );

				ForceField forceField = _scene.CreateForceField( forceFieldDesc );
			}
			#endregion
			
			#region Heightfield
			{
				int rows = 25;
				int columns = 25;

				HeightFieldSample[] samples = new HeightFieldSample[ rows * columns ];
				for( int r = 0; r < rows; r++ )
				{
					for( int c = 0; c < columns; c++ )
					{
						// Put a z and x curve together
						double h = Math.Sin( c ) * Math.Cos( r ) * short.MaxValue;

						HeightFieldSample sample = new HeightFieldSample();
							sample.Height = (short)h;
							sample.MaterialIndex0 = 0;
							sample.MaterialIndex1 = 1;
							sample.TessellationFlag = 0;

						samples[ r * columns + c ] = sample;
					}
				}

				HeightFieldDescription heightFieldDesc = new HeightFieldDescription();
					heightFieldDesc.NumberOfRows = rows;
					heightFieldDesc.NumberOfColumns = columns;
					heightFieldDesc.Samples = samples;

				HeightField heightField = _core.CreateHeightField( heightFieldDesc );
				
				//

				HeightFieldShapeDescription heightFieldShapeDesc = new HeightFieldShapeDescription();
					heightFieldShapeDesc.HeightField = heightField;
					heightFieldShapeDesc.HoleMaterial = 2;
					// The max height of our samples is short.MaxValue and we want it to be 1
					heightFieldShapeDesc.HeightScale = 1.0f / (float)short.MaxValue;
					heightFieldShapeDesc.RowScale = 3;
					heightFieldShapeDesc.ColumnScale = 3;
					heightFieldShapeDesc.LocalPosition = new Vector3( -0.5f * rows * 1 * heightFieldShapeDesc.RowScale, 0, -0.5f * columns * 1 * heightFieldShapeDesc.ColumnScale );

				ActorDescription actorDesc = new ActorDescription();
					actorDesc.Shapes.Add( heightFieldShapeDesc );
					actorDesc.GlobalPose = Matrix.CreateTranslation( 100, 0, 0 );

				Actor actor = _scene.CreateActor( actorDesc );
			}
			#endregion

			#region Convex Mesh
			{
				ModelMesh mesh = _torusModel.Meshes[ 0 ];

				Matrix[] transforms = new Matrix[ _torusModel.Bones.Count ];
				_torusModel.CopyAbsoluteBoneTransformsTo( transforms );

				// Gets the vertices from the mesh
				VertexPositionNormalTexture[] vertices = new VertexPositionNormalTexture[ mesh.MeshParts[ 0 ].NumVertices ];
				mesh.VertexBuffer.GetData<VertexPositionNormalTexture>( vertices );

				// Get the indices from the mesh
				//short[] indices = new short[ mesh.MeshParts[ 0 ].PrimitiveCount * 3 ];
				//mesh.IndexBuffer.GetData<short>( indices );

				//int numberOfTriangles = indices.Length / 3;

				//

				// Allocate memory for the points and triangles
				ConvexMeshDescription convexMeshDesc = new ConvexMeshDescription();
				    convexMeshDesc.PointCount = vertices.Length;
				    convexMeshDesc.Flags |= ConvexFlag.ComputeConvex;

				    convexMeshDesc.AllocatePoints<Vector3>( vertices.Length );

				// Write in the points and triangles
				// We only want the Position component of the vertex. Also scale down the mesh
				foreach( VertexPositionNormalTexture vertex in vertices )
				{
					Vector3 position = Vector3.Transform( vertex.Position, Matrix.CreateScale( 0.1f, 0.1f, 0.1f ) * transforms[ 0 ] );

				    convexMeshDesc.PointsStream.Write( position );
				}

				//

				// Cook to memory or to a file
				MemoryStream stream = new MemoryStream();
				//FileStream stream = new FileStream( @"Convex Mesh.cooked", FileMode.CreateNew );

				Cooking.InitializeCooking( new ConsoleOutputStream() );
				Cooking.CookConvexMesh( convexMeshDesc, stream );
				Cooking.CloseCooking();

				stream.Position = 0;

				ConvexMesh convexMesh = _core.CreateConvexMesh( stream );

				ConvexShapeDescription convexShapeDesc = new ConvexShapeDescription( convexMesh );

				ActorDescription actorDesc = new ActorDescription();
				    actorDesc.BodyDescription = new BodyDescription( 10.0f );
					actorDesc.GlobalPose = Matrix.CreateTranslation( 30, 30, 0 );
				    actorDesc.Shapes.Add( convexShapeDesc );

				_torusActor = _scene.CreateActor( actorDesc );
			}
			#endregion

			#region SoftBody
			if( false ) // Enable to view soft bodies, they run slowly
			{
				XmlDocument doc = new XmlDocument();
					doc.Load( "Teapot.xml" );
				
				// Not how NxuStream are meant to used but what ever :S
				Vector3[] vertices = ReadVertices( doc.SelectSingleNode( "/NXUSTREAM2/NxuPhysicsCollection/NxSoftBodyMeshDesc/vertices" ) );
				int[] tetrahedraSingles = ReadTetrahedra( doc.SelectSingleNode( "/NXUSTREAM2/NxuPhysicsCollection/NxSoftBodyMeshDesc/tetrahedra" ) );

				SoftBodyMeshDescription softBodyMeshDesc = new SoftBodyMeshDescription();
					softBodyMeshDesc.VertexCount = vertices.Length;
					softBodyMeshDesc.TetrahedraCount = tetrahedraSingles.Length / 4; // Tetrahedras come in quadruples of ints

					softBodyMeshDesc.AllocateVertices<Vector3>( softBodyMeshDesc.VertexCount );
					softBodyMeshDesc.AllocateTetrahedra<int>( softBodyMeshDesc.TetrahedraCount ); // Note: T is an int. T is the type of each point

					foreach( Vector3 vertex in vertices )
					{
						softBodyMeshDesc.VertexStream.Write( vertex );
					}
					foreach( int tet in tetrahedraSingles )
					{
						softBodyMeshDesc.TetrahedraStream.Write( tet );
					}

				MemoryStream memoryStream = new MemoryStream();

				Cooking.InitializeCooking();
				Cooking.CookSoftBodyMesh( softBodyMeshDesc, memoryStream );
				Cooking.CloseCooking();

				memoryStream.Position = 0;

				SoftBodyMesh softBodyMesh = _core.CreateSoftBodyMesh( memoryStream );

				SoftBodyDescription desc = new SoftBodyDescription();
					desc.GlobalPose = Matrix.CreateTranslation( -30, 20, -30 );
					desc.SoftBodyMesh = softBodyMesh;
					desc.Flags |= SoftBodyFlag.Visualization;

					desc.MeshData.AllocatePositions<Vector3>( vertices.Length );
					desc.MeshData.AllocateIndices<int>( tetrahedraSingles.Length );
				SoftBody softBody = _scene.CreateSoftBody( desc );
			}
			#endregion

			#region Reports
			// Contact report
			// When the capsule actor hits the ground make it bounce by using the conact report
			{
				CapsuleShapeDescription capsuleShapeDesc = new CapsuleShapeDescription( 1, 5 );
				
				ActorDescription actorDesc = new ActorDescription();
					actorDesc.GlobalPose = Matrix.CreateTranslation( -30, 20, 0 );
					actorDesc.BodyDescription = new BodyDescription( 10.0f );
					actorDesc.Shapes.Add( capsuleShapeDesc );
					actorDesc.Name = "Report Capsule";

				_contactReportActor = _scene.CreateActor( actorDesc );

				_scene.SetActorPairFlags( _contactReportActor, _groundActor, ContactPairFlag.All );

				_scene.UserContactReport = new ContactReport( this );
			}

			// Trigger Reports
			{
				BoxShapeDescription boxShapeDesc = new BoxShapeDescription( 15, 8, 15 );
					boxShapeDesc.Flags |= ( ShapeFlag.TriggerOnEnter | ShapeFlag.TriggerOnLeave );

				ActorDescription actorDesc = new ActorDescription();
					actorDesc.GlobalPose = Matrix.CreateTranslation( -30, 4, 0 );
					actorDesc.Shapes.Add( boxShapeDesc );

				_scene.CreateActor( actorDesc );

				_scene.UserTriggerReport = new TriggerReport( this );
			}

			_scene.UserNotify = new Notify( this );
			#endregion

			#region Wheel
			{
				_basicVehicle = new Vehicle( this );
			}
			#endregion

			ControllerManager manager = _scene.CreateControllerManager();

			CapsuleControllerDescription boxControllerDesc = new CapsuleControllerDescription( 4, 3 );

			CapsuleController boxController = manager.CreateController( boxControllerDesc ) as CapsuleController;

			boxController.Actor.Name = "BoxController";
		}

		private Vector3[] ReadVertices( XmlNode node )
		{
			string innerText = node.InnerText;

			string[] floatStrings = innerText.Split( ' ' );
			List<float> floats = new List<float>();

			for( int x = 0; x < floatStrings.Length; x++ )
			{
				float f;
				if( Single.TryParse( floatStrings[ x ], out f ) == false )
					continue;

				floats.Add( f );
			}

			Vector3[] vertices = new Vector3[ floats.Count / 3 ];
			for( int i = 0; i < floats.Count; i += 3 )
			{
				float x = floats[ i + 0 ];
				float y = floats[ i + 1 ];
				float z = floats[ i + 2 ];

				vertices[ i / 3 ] = new Vector3( x, y, z );
			}

			return vertices;
		}
		private int[] ReadTetrahedra( XmlNode node )
		{
			string innerText = node.InnerText;
			string[] tetrahedraStrings = innerText.Split( new string[] { " " }, StringSplitOptions.RemoveEmptyEntries );

			List<int> tetrahedra = new List<int>();

			for( int x = 0; x < tetrahedraStrings.Length; x++ )
			{
				int tet;
				if( Int32.TryParse( tetrahedraStrings[ x ], out tet ) == false )
					continue;

				tetrahedra.Add( tet );
			}

			return tetrahedra.ToArray();
		}

		private VertexGrid CreateGrid( int rows, int columns )
		{
			int numVertsX = rows + 1;
			int numVertsZ = columns + 1;

			VertexGrid grid = new VertexGrid( new Vector3[ numVertsX * numVertsZ ], new int[ rows * columns * 2 * 3 ] );

			{
				for( int r = 0; r < numVertsX; r++ )
				{
					for( int c = 0; c < numVertsZ; c++ )
					{
						grid.Points[ r * numVertsZ + c ] = new Vector3( r, 0, c );
					}
				}
			}

			{
				int count = 0;
				int vIndex = 0;
				for( int z = 0; z < columns; z++ )
				{
					for( int x = 0; x < rows; x++ )
					{
						// first triangle
						grid.Indices[ count++ ] = vIndex;
						grid.Indices[ count++ ] = vIndex + 1;
						grid.Indices[ count++ ] = vIndex + numVertsX;

						// second triangle
						grid.Indices[ count++ ] = vIndex + numVertsX;
						grid.Indices[ count++ ] = vIndex + 1;
						grid.Indices[ count++ ] = vIndex + numVertsX + 1;

						vIndex++;
					}
					vIndex++;
				}
			}

			return grid;
		}
	}

	public class VertexGrid
	{
		private Vector3[] _points;
		private int[] _indices;

		public VertexGrid( Vector3[] points, int[] indices )
		{
			_points = points;
			_indices = indices;
		}

		public Vector3[] Points
		{
			get
			{
				return _points;
			}
		}
		public int[] Indices
		{
			get
			{
				return _indices;
			}
		}
	}
}