using System;
using System.Collections.Generic;
using System.Linq;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Content;
using Microsoft.Xna.Framework.Graphics;
using Microsoft.Xna.Framework.Input;
using StillDesign.PhysX;

using Vector3 = StillDesign.PhysX.MathPrimitives.Vector3;
using Matrix = StillDesign.PhysX.MathPrimitives.Matrix;

namespace StillDesign.PhysX.Samples
{
	public delegate void ContactCallback( Actor a, Actor b, ContactPairFlag events );

	public partial class MainSample : Game
	{
		private readonly Engine _engine;

		private Core _core;
		private Scene _scene;

		private Cloth _flag;

		private Actor _contactReportActor;
		private Actor _groundActor;

		private Model _torusModel;
		private Actor _torusActor;

		private Vehicle _basicVehicle;

		//

		public MainSample()
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
				var transforms = new Microsoft.Xna.Framework.Matrix[ _torusModel.Bones.Count ];
				_torusModel.CopyAbsoluteBoneTransformsTo( transforms );

				foreach( ModelMesh mesh in _torusModel.Meshes )
				{
					foreach( BasicEffect effect in mesh.Effects )
					{
						effect.EnableDefaultLighting();

						//Matrix world = 
						//    Matrix.Scaling( 0.1f, 0.1f, 0.1f ) *
						//    transforms[ mesh.ParentBone.Index ].AsPhysX() *
						//    _torusActor.GlobalPose;

						//effect.World = world.As<Microsoft.Xna.Framework.Matrix>();
						//effect.View = _engine.Camera.View;
						//effect.Projection = _engine.Camera.Projection;
					}

					mesh.Draw();
				}
			}

			// Display basic info about the vehicle
			//WheelContactData contactData = _basicVehicle.LeftFront.GetContactData();

			//Vector3 readOut = contactData.LongitudalDirection;
			//this.Window.Title = String.Format( "LongitudalDirection: {0:0.00},{1:0.00},{2:0.00}", readOut.X, readOut.Y, readOut.Z );
		}

		private void Shutdown()
		{
			_core.Dispose();

			this.Exit();
		}

		//

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
	}
}