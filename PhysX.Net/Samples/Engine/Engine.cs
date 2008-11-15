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
		private Game _game;
		private GraphicsDeviceManager _deviceManager;

		private Camera _camera;

		private BasicEffect _visualizationEffect;

		private Core _core;
		private Scene _scene;

		public Engine( Game game )
		{
			_game = game;
			_deviceManager = new GraphicsDeviceManager( game );
		}

		public void Initalize()
		{
			_camera = new Camera( this );

			_visualizationEffect = new BasicEffect( this.Device, null );
			_visualizationEffect.VertexColorEnabled = true;

			//

			CoreDescription coreDesc = new CoreDescription();
			UserOutput output = new UserOutput();
			
			_core = new Core( coreDesc, output );
				_core.SetParameter( PhysicsParameter.VisualizationScale, 2.0f );
				_core.SetParameter( PhysicsParameter.VisualizeCollisionShapes, true );
				_core.SetParameter( PhysicsParameter.VisualizeClothMesh, true );
				_core.SetParameter( PhysicsParameter.VisualizeJointLocalAxes, true );
				_core.SetParameter( PhysicsParameter.VisualizeJointLimits, true );
				_core.SetParameter( PhysicsParameter.VisualizeFluidPosition, true );
				_core.SetParameter( PhysicsParameter.VisualizeFluidEmitters, false ); // Slows down rendering a bit to much
				_core.SetParameter( PhysicsParameter.VisualizeForceFields, true );
				_core.SetParameter( PhysicsParameter.VisualizeSoftBodyMesh, true );

			SceneDescription sceneDesc = new SceneDescription();
				sceneDesc.SimulationType = SimulationType.Software;
				sceneDesc.Gravity = new Vector3( 0.0f, -9.81f, 0.0f );
				sceneDesc.GroundPlaneEnabled = true;

			_scene = _core.CreateScene( sceneDesc );

			HardwareVersion ver = Core.HardwareVersion;

			// Connect to the remote debugger if its there
			_core.Foundation.RemoteDebugger.Connect( "localhost" );
		}

		public void Update( GameTime gameTime )
		{
			// Update Physics
			_scene.Simulate( (float)gameTime.ElapsedGameTime.TotalMilliseconds / 1000.0f );
			//_scene.Simulate( 1.0f / 60.0f );
			_scene.FlushStream();
			_scene.FetchResults( SimulationStatus.RigidBodyFinished, true );

			_camera.Update( gameTime );
		}
		public void Draw()
		{
			this.Device.Clear( Color.LightBlue );

			this.Device.VertexDeclaration = new VertexDeclaration( this.Device, VertexPositionColor.VertexElements );

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

		private Color Int32ToColor( int color )
		{
			byte a = (byte)( ( color & 0xFF000000 ) >> 32 );
			byte r = (byte)( ( color & 0x00FF0000 ) >> 16 );
			byte g = (byte)( ( color & 0x0000FF00 ) >> 8 );
			byte b = (byte)( ( color & 0x000000FF ) >> 0 );

			return new Color( r, g, b, a );
		}

		#region Properties
		public Game Game
		{
			get
			{
				return _game;
			}
		}
		public Camera Camera
		{
			get
			{
				return _camera;
			}
		}

		public Core Core
		{
			get
			{
				return _core;
			}
		}
		public Scene Scene
		{
			get
			{
				return _scene;
			}
		}

		public GraphicsDeviceManager DeviceManager
		{
			get
			{
				return _deviceManager;
			}
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