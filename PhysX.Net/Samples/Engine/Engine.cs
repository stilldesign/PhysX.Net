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

namespace StillDesign
{
	public class Engine
	{
		private BasicEffect _visualizationEffect;

		public Engine( Game game )
		{
			this.Game = game;
			this.DeviceManager = new GraphicsDeviceManager( game );

			this.DeviceManager.PreferredBackBufferWidth = (int)( GraphicsAdapter.DefaultAdapter.CurrentDisplayMode.Width * 0.8 );
			this.DeviceManager.PreferredBackBufferHeight = (int)( GraphicsAdapter.DefaultAdapter.CurrentDisplayMode.Height * 0.8 );
		}

		public void Initalize()
		{
			this.Camera = new Camera( this );

			_visualizationEffect = new BasicEffect( this.Device, null )
			{
				VertexColorEnabled = true
			};

			//

			CoreDescription coreDesc = new CoreDescription();
			UserOutput output = new UserOutput();

			this.Core = new Core( coreDesc, output );

			var core = this.Core;
			core.SetParameter( PhysicsParameter.VisualizationScale, 2.0f );
			core.SetParameter( PhysicsParameter.VisualizeCollisionShapes, true );
			core.SetParameter( PhysicsParameter.VisualizeClothMesh, true );
			core.SetParameter( PhysicsParameter.VisualizeJointLocalAxes, true );
			core.SetParameter( PhysicsParameter.VisualizeJointLimits, true );
			core.SetParameter( PhysicsParameter.VisualizeFluidPosition, true );
			core.SetParameter( PhysicsParameter.VisualizeFluidEmitters, false ); // Slows down rendering a bit to much
			core.SetParameter( PhysicsParameter.VisualizeForceFields, true );
			core.SetParameter( PhysicsParameter.VisualizeSoftBodyMesh, true );

			SceneDescription sceneDesc = new SceneDescription()
			{
				//SimulationType = SimulationType.Hardware,
				Gravity = new Vector3( 0.0f, -9.81f, 0.0f ),
				GroundPlaneEnabled = true
			};

			this.Scene = core.CreateScene( sceneDesc );

			HardwareVersion ver = Core.HardwareVersion;
			SimulationType simType = this.Scene.SimulationType;

			// Connect to the remote debugger if its there
			core.Foundation.RemoteDebugger.Connect( "localhost" );
		}

		public void Update( GameTime gameTime )
		{
			// Update Physics
			this.Scene.Simulate( (float)gameTime.ElapsedGameTime.TotalMilliseconds / 1000.0f );
			//_scene.Simulate( 1.0f / 60.0f );
			this.Scene.FlushStream();
			this.Scene.FetchResults( SimulationStatus.RigidBodyFinished, true );

			this.Camera.Update( gameTime );
		}
		public void Draw()
		{
			this.Device.Clear( Color.LightBlue );

			this.Device.VertexDeclaration = new VertexDeclaration( this.Device, VertexPositionColor.VertexElements );

			_visualizationEffect.World = Matrix.Identity;
			_visualizationEffect.View = this.Camera.View;
			_visualizationEffect.Projection = this.Camera.Projection;

			DebugRenderable data = this.Scene.GetDebugRenderable();

			_visualizationEffect.Begin();

				foreach( EffectPass pass in _visualizationEffect.CurrentTechnique.Passes )
				{
					pass.Begin();

						if( data.PointCount > 0 )
						{
							DebugPoint[] points = data.GetDebugPoints();

							this.Device.DrawUserPrimitives<DebugPoint>( PrimitiveType.PointList, points, 0, points.Length );
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

							this.Device.DrawUserPrimitives<VertexPositionColor>( PrimitiveType.LineList, vertices, 0, lines.Length );
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

							this.Device.DrawUserPrimitives<VertexPositionColor>( PrimitiveType.TriangleList, vertices, 0, triangles.Length );
						}

					pass.End();
				}

			_visualizationEffect.End();
		}

		public static Color Int32ToColor( int color )
		{
			byte a = (byte)( ( color & 0xFF000000 ) >> 32 );
			byte r = (byte)( ( color & 0x00FF0000 ) >> 16 );
			byte g = (byte)( ( color & 0x0000FF00 ) >> 8 );
			byte b = (byte)( ( color & 0x000000FF ) >> 0 );

			return new Color( r, g, b, a );
		}
		public static int ColorToArgb( Color color )
		{
			int a = (int)( color.A );
			int r = (int)( color.R );
			int g = (int)( color.G );
			int b = (int)( color.B );

			return ( a << 24 ) | ( r << 16 ) | ( g << 8 ) | ( b << 0 );
		}

		#region Properties
		public Game Game
		{
			get;
			private set;
		}
		public Camera Camera
		{
			get;
			private set;
		}

		public Core Core
		{
			get;
			private set;
		}
		public Scene Scene
		{
			get;
			private set;
		}

		public GraphicsDeviceManager DeviceManager
		{
			get;
			private set;
		}
		public GraphicsDevice Device
		{
			get
			{
				return this.DeviceManager.GraphicsDevice;
			}
		}
		#endregion
	}
}