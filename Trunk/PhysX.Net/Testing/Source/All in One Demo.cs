using System;
using System.Collections.Generic;

using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;
using Microsoft.Xna.Framework.Content;
using Microsoft.Xna.Framework.Input;

using StillDesign.PhysX;

namespace StillDesign
{
	public delegate void ContactCallback( Actor a, Actor b, ContactPairFlag events );

	public partial class Demo : Game
	{
		#region Variables
			private GraphicsDeviceManager _device;

			private BasicEffect _visualizationEffect;

			private Core _core;
			private Scene _scene;

			private Cloth _flag;

			private Camera _camera;

			private Actor _contactReportActor;
			private Actor _groundActor;

			private Model _torusModel;
			private Actor _torusActor;

			private Vehicle _basicVehicle;
		#endregion

		public Demo()
		{
			_device = new GraphicsDeviceManager( this );
		}

		protected override void Initialize()
		{
			base.Initialize();
		}
		protected override void LoadContent()
		{
			_torusModel = this.Content.Load<Model>( "Torus Knot" );

			LoadGraphics();
			LoadPhysics();

			_camera = new Camera( this );
		}
		private void LoadGraphics()
		{
			_device.PreferMultiSampling = true;
			_device.ApplyChanges();

			_visualizationEffect = new BasicEffect( _device.GraphicsDevice, null );
				_visualizationEffect.VertexColorEnabled = true;
		}

		protected override void Update( GameTime gameTime )
		{
			base.Update( gameTime );

			KeyboardState keyboardState = Keyboard.GetState();

			if( keyboardState.IsKeyDown( Keys.Escape ) )
				this.Exit();

			//if( keyboardState.IsKeyDown( Keys.L ) )
			//{
			//    Box box = new Box( new Vector3( 0, 0, 0 ), new Vector3( 100, 100, 100 ) );

			//    var s = _scene.LinearSweep( box, new Vector3( 0, 0, 100 ), SweepFlags.AllHits, null );
			//}

			//

			// Drive the vehicle
			if( keyboardState.IsKeyDown( Keys.Up ) )
				_basicVehicle.Accelerate( 3 );

			// Steering (Positive is a counter-clockwise turn)
			if( keyboardState.IsKeyDown( Keys.Left ) )
				_basicVehicle.Turn( 0.05f );
			if( keyboardState.IsKeyDown( Keys.Right ) )
				_basicVehicle.Turn( -0.05f );

			//

			_camera.Update( gameTime );

			// Update Physics
			_scene.Simulate( (float)gameTime.ElapsedGameTime.TotalMilliseconds / 1000.0f );
			//_scene.Simulate( 1.0f / 60.0f );
			_scene.FlushStream();
			_scene.FetchResults( SimulationStatus.RigidBodyFinished, true );
		}

		protected override void Draw( GameTime gameTime )
		{
			_device.GraphicsDevice.Clear( Color.LightBlue );

			base.Draw( gameTime );

			{
				_device.GraphicsDevice.VertexDeclaration = new VertexDeclaration( _device.GraphicsDevice, VertexPositionColor.VertexElements );

				_visualizationEffect.World = Matrix.Identity;
				_visualizationEffect.View = _camera.View;
				_visualizationEffect.Projection = _camera.Projection;

				DebugRenderable data = _scene.GetDebugRenderable();

				_visualizationEffect.Begin();

					foreach( EffectPass pass in _visualizationEffect.CurrentTechnique.Passes )
					{
						pass.Begin();

							if( data.PointCount > 0 )
							{
								DebugPoint[] points = data.GetDebugPoints();

								_device.GraphicsDevice.DrawUserPrimitives<DebugPoint>( PrimitiveType.PointList, points, 0, points.Length );
							}

							if( data.LineCount > 0 )
							{
								DebugLine[] lines = data.GetDebugLines();

								VertexPositionColor[] vertices = new VertexPositionColor[ data.LineCount * 2 ];
								for( int x = 0; x < data.LineCount; x++ )
								{
									DebugLine line = lines[ x ];

									vertices[ x * 2 + 0 ] = new VertexPositionColor( line.Point0, Int32ToColor( line.Color ) );
									vertices[ x * 2 + 1 ] = new VertexPositionColor( line.Point1, Int32ToColor( line.Color ) );
								}

								_device.GraphicsDevice.DrawUserPrimitives<VertexPositionColor>( PrimitiveType.LineList, vertices, 0, lines.Length );
							}

							if( data.TriangleCount > 0 )
							{
								DebugTriangle[] triangles = data.GetDebugTriangles();

								VertexPositionColor[] vertices = new VertexPositionColor[ data.TriangleCount * 3 ];
								for( int x = 0; x < data.TriangleCount; x++ )
								{
									DebugTriangle triangle = triangles[ x ];

									vertices[ x * 3 + 0 ] = new VertexPositionColor( triangle.Point0, Int32ToColor( triangle.Color ) );
									vertices[ x * 3 + 1 ] = new VertexPositionColor( triangle.Point1, Int32ToColor( triangle.Color ) );
									vertices[ x * 3 + 2 ] = new VertexPositionColor( triangle.Point2, Int32ToColor( triangle.Color ) );
								}

								_device.GraphicsDevice.DrawUserPrimitives<VertexPositionColor>( PrimitiveType.TriangleList, vertices, 0, triangles.Length );
							}

						pass.End();
					}

				_visualizationEffect.End();
			}
			/*
			// Draw the torus knot
			{
				Matrix[] transforms = new Matrix[ _torusModel.Bones.Count ];
				_torusModel.CopyAbsoluteBoneTransformsTo( transforms );

				foreach( ModelMesh mesh in _torusModel.Meshes )
				{
					foreach( BasicEffect effect in mesh.Effects )
					{
						effect.EnableDefaultLighting();

						effect.World = Matrix.CreateScale( 0.1f, 0.1f, 0.1f ) * transforms[ mesh.ParentBone.Index ] * _torusActor.GlobalPose;
						effect.View = _camera.View;
						effect.Projection = _camera.Projection;
					}

					mesh.Draw();
				}
			}

			// Basic info about the vehicle
			WheelContactData contactData = _basicVehicle.LeftFront.GetContactData();

			Vector3 readOut = contactData.LongitudalDirection;
			this.Window.Title = String.Format( "LongitudalDirection: {0:0.00},{1:0.00},{2:0.00}", readOut.X, readOut.Y, readOut.Z );*/
		}
		
		#region Properties
		public Scene Scene
		{
			get
			{
				return _scene;
			}
		}

		public Actor GroundActor
		{
			get
			{
				return _groundActor;
			}
		}
		public Actor ContactReportActor
		{
			get
			{
				return _contactReportActor;
			}
		}
		#endregion
	}

	public class UserOutput : UserOutputStream
	{
		public override void Print( string message )
		{
			Console.WriteLine( "PhysX: " + message );
		}
		public override AssertResponse ReportAssertionViolation( string message, string file, int lineNumber )
		{
			Console.WriteLine( "PhysX: " + message );

			return AssertResponse.Continue;
		}
		public override void ReportError( ErrorCode errorCode, string message, string file, int lineNumber )
		{
			Console.WriteLine( "PhysX: " + message );
		}
	}

	public class ContactReport : UserContactReport
	{
		private Demo _demo;

		private List<ContactReportPair> _contactPairs;

		public ContactReport( Demo demo )
		{
			_demo = demo;

			// Associate the pairs with a function
			_contactPairs = new List<ContactReportPair>();
				_contactPairs.Add( new ContactReportPair( _demo.ContactReportActor, _demo.GroundActor, new ContactCallback( CapsuleAndGroundPlaneContact ) ) );
		}

		// PhysX calls OnContactNotify is the base class which you then provide the implementation for
		public override void OnContactNotify( ContactPair contactInformation, ContactPairFlag events )
		{
			Actor a = contactInformation.ActorA;
			Actor b = contactInformation.ActorB;

			// This shouldn't be O(n)
			foreach( ContactReportPair pair in _contactPairs )
			{
				if( ( pair.A == a || pair.A == b ) && ( pair.B == a || pair.B == b ) )
				{
					pair.Callback( a, b, events );
				}
			}
		}

		private void CapsuleAndGroundPlaneContact( Actor a, Actor b, ContactPairFlag events )
		{
			// The capsule hit the ground, add some bounce
			// Can be done with materials, but this just an example to demonstrate contact report
			_demo.ContactReportActor.AddForce( new Vector3( 0, 5000, 0 ), ForceMode.Force );
		}
	}
	public class ContactReportPair
	{
		private Actor _a, _b;
		private ContactCallback _callback;

		public ContactReportPair( Actor a, Actor b, ContactCallback callback )
		{
			_a = a;
			_b = b;
			_callback = callback;
		}

		public Actor A
		{
			get
			{
				return _a;
			}
		}
		public Actor B
		{
			get
			{
				return _b;
			}
		}
		public ContactCallback Callback
		{
			get
			{
				return _callback;
			}
		}
	}

	public class Notify : UserNotify
	{
		public Notify( Demo demo )
		{

		}

		public override bool OnSleep( Actor[] actors )
		{
			foreach( Actor actor in actors )
			{
				Console.WriteLine( "Actor '{0}' Went to Sleep at {1}", actor.Name == null ? String.Empty : actor.Name, DateTime.Now.ToShortTimeString() );
			}

			return true;
		}

		public override bool OnJointBreak( float breakingForce, Joint brokenJoint )
		{
			return true;
		}

		public override bool OnWake( Actor[] actors )
		{
			return true;
		}
	}

	public class TriggerReport : UserTriggerReport
	{
		public TriggerReport( Demo demo )
		{

		}

		public override void OnTrigger( Shape triggerShape, Shape otherShape, TriggerFlag status )
		{
			// A trigger occured, just report the names the actors of the shapes that contacted
			Console.WriteLine( String.Format( "'{0}' and '{1}' Triggered with Type '{2}'", triggerShape.Actor.Name, otherShape.Actor.Name, status ) );
		}
	}
}