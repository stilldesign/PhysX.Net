using System;
using System.Collections.Generic;

using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Audio;
using Microsoft.Xna.Framework.Content;
using Microsoft.Xna.Framework.GamerServices;
using Microsoft.Xna.Framework.Graphics;
using Microsoft.Xna.Framework.Input;
using Microsoft.Xna.Framework.Net;
using Microsoft.Xna.Framework.Storage;

using StillDesign.PhysX;
using StillDesign.PhysX.Utilities;

namespace StillDesign
{
	public class SerializationExample : Microsoft.Xna.Framework.Game
	{
		private Engine _engine;

		private Core _core;
		private Scene _scene;

		public SerializationExample()
		{
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

			LoadPhysics();
		}

		protected override void LoadContent()
		{
			
		}
		private void LoadPhysics()
		{
			// Load a physics scene from a file
			PhysicsCollection collection = Utilities.LoadCollection( @"Scene 3.xml", UtilitiesFileType.Xml );

			LoadUserNotify notify = new LoadUserNotify();

			bool i = collection.InstantiateCollection( _core, _scene, null, notify );
		}

		protected override void UnloadContent()
		{
			
		}

		protected override void Update( GameTime gameTime )
		{
			KeyboardState keyboardState = Keyboard.GetState();

			if( keyboardState.IsKeyDown( Keys.Escape ) )
				this.Exit();

			//

			base.Update( gameTime );

			_engine.Update( gameTime );

			// Update Physics
			_scene.Simulate( (float)gameTime.ElapsedGameTime.TotalMilliseconds / 1000.0f );
			//_scene.Simulate( 1.0f / 60.0f );
			_scene.FlushStream();
			_scene.FetchResults( SimulationStatus.RigidBodyFinished, true );
		}

		protected override void Draw( GameTime gameTime )
		{
			base.Draw( gameTime );

			_engine.Draw();
		}
	}

	public class LoadUserNotify : StillDesign.PhysX.Utilities.UserNotify
	{
		public LoadUserNotify()
		{

		}

		public override void NotifyActor( Actor actor, string userProperties )
		{
			
		}
		public override bool PreNotifyJoint( JointDescription joint, string userProperties )
		{
			joint.IsValid();
			return true;
		}
		public override void NotifyJoint( Joint joint, string userProperties )
		{
			base.NotifyJoint( joint, userProperties );
		}
		public override void PreNotifyJointFailed( JointDescription joint, string userProperties )
		{
			base.PreNotifyJointFailed( joint, userProperties );
		}
	}
}