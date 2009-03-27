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

	public partial class Demo1 : Game
	{
		#region Variables
			private readonly Engine _engine;

			private Core _core;
			private Scene _scene;

			private Cloth _flag;

			private Actor _contactReportActor;
			private Actor _groundActor;

			private Model _torusModel;
			private Actor _torusActor;

			private Vehicle _basicVehicle;
		#endregion

		public Demo1()
		{
			Content.RootDirectory = "Content";

			//

			_engine = new Engine( this );
		}

		protected override void Initialize()
		{
			_engine.Initalize();

			// For convenience
			_core = _engine.Core;
			_scene = _engine.Scene;

			// Initalize the content
			base.Initialize();

			LoadGraphics();
			LoadPhysics();
		}
		protected override void LoadContent()
		{
			_torusModel = this.Content.Load<Model>( @"Torus Knot" );
		}
		private void LoadGraphics()
		{
			_engine.DeviceManager.PreferMultiSampling = true;
			_engine.DeviceManager.ApplyChanges();
		}

		protected override void Update( GameTime gameTime )
		{
			base.Update( gameTime );

			KeyboardState keyboardState = Keyboard.GetState();

			if( keyboardState.IsKeyDown( Keys.Escape ) )
			{
				Shutdown();
				return;
			}

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

			_engine.Update( gameTime );
		}

		protected override void Draw( GameTime gameTime )
		{
			base.Draw( gameTime );

			_engine.Draw();
			
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
						effect.View = _engine.Camera.View;
						effect.Projection = _engine.Camera.Projection;
					}

					mesh.Draw();
				}
			}

			// Display basic info about the vehicle
			WheelContactData contactData = _basicVehicle.LeftFront.GetContactData();

			Vector3 readOut = contactData.LongitudalDirection;
			this.Window.Title = String.Format( "LongitudalDirection: {0:0.00},{1:0.00},{2:0.00}", readOut.X, readOut.Y, readOut.Z );
		}

		private void Shutdown()
		{
			_core.Dispose();

			this.Exit();
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

	public class ContactReport : UserContactReport
	{
		private Demo1 _demo;

		private List<ContactReportPair> _contactPairs;

		public ContactReport( Demo1 demo )
		{
			_demo = demo;

			// Associate the pairs with a function
			_contactPairs = new List<ContactReportPair>()
			{
				{ new ContactReportPair( _demo.ContactReportActor, _demo.GroundActor, CapsuleAndGroundPlaneContact ) }
			};
		}

		// PhysX calls OnContactNotify is the base class which you then provide the implementation for
		public override void OnContactNotify( ContactPair contactInformation, ContactPairFlag events )
		{
			Actor a = contactInformation.ActorA;
			Actor b = contactInformation.ActorB;

			// This shouldn't be O(n)
			foreach( ContactReportPair pair in _contactPairs )
			{
				if( ( pair.ActorA == a || pair.ActorA == b ) && ( pair.ActorB == a || pair.ActorB == b ) )
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
		public ContactReportPair( Actor a, Actor b, ContactCallback callback )
		{
			this.ActorA = a;
			this.ActorB = b;
			this.Callback = callback;
		}

		public Actor ActorA
		{
			get;
			private set;
		}
		public Actor ActorB
		{
			get;
			private set;
		}
		public ContactCallback Callback
		{
			get;
			private set;
		}
	}

	public class Notify : UserNotify
	{
		public Notify( Demo1 demo )
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
		public TriggerReport( Demo1 demo )
		{

		}

		public override void OnTrigger( Shape triggerShape, Shape otherShape, TriggerFlag status )
		{
			// A trigger occured, just report the names the actors of the shapes that contacted
			Console.WriteLine( String.Format( "'{0}' and '{1}' Triggered with Type '{2}'", triggerShape.Actor.Name, otherShape.Actor.Name, status ) );
		}
	}
}