using System;
using System.Diagnostics;
using System.IO;
using System.Numerics;
using System.Reflection;
using System.Windows;
using System.Windows.Input;
using SharpDX.D3DCompiler;
using SharpDX.Direct3D;
using SharpDX.Direct3D11;
using SharpDX.DXGI;

namespace PhysX.Samples.Engine
{
	public delegate void UpdateEventHandler(TimeSpan elapsed);

	public class Engine
	{
		public event UpdateEventHandler OnUpdate;
		public event EventHandler OnDraw;

		private Action<SceneDesc> _sceneDescCallback;

		private Keyboard _keyboard;
		private VisualizationEffect _visualizationEffect;

		private RenderTargetView _backBuffer;
		private DepthStencilView _depthBuffer;
		private SwapChain _swapChain;

		private SharpDX.Direct3D11.Buffer _userPrimitivesBuffer;
		private InputLayout _inputLayout;

		// TODO: Clean up this class
		public Engine(Action<SceneDesc> sceneDescCallback = null)
		{
			_sceneDescCallback = sceneDescCallback;

			Window = new SampleWindow();
			Window.Show();

			_keyboard = new Keyboard(this);
			_keyboard.OnKeyDown += _keyboard_OnKeyDown;

			InitalizeGraphics();

			InitalizePhysics();

			Mouse.SetCursor(Cursors.None);
		}

		private void _keyboard_OnKeyDown(object sender, KeyEventArgs e)
		{
			if (e.Key == Key.Space)
			{
				ShootSphere();
			}
		}

		private void ShootSphere()
		{
			const float force = 5000;

			var cameraPos = Camera.Position.AsPhysX();
			var cameraDir = Camera.Direction.AsPhysX();

			var material = this.Scene.Physics.CreateMaterial(0.1f, 0.5f, 0.5f);

			var rigidActor = this.Scene.Physics.CreateRigidDynamic();

			var sphereGeom = new SphereGeometry(2);
			var boxShape = rigidActor.CreateShape(sphereGeom, material);

			rigidActor.GlobalPose = Matrix4x4.CreateTranslation(cameraPos);
			rigidActor.SetMassAndUpdateInertia(100);

			this.Scene.AddActor(rigidActor);

			rigidActor.AddForceAtLocalPosition(cameraDir * force, new System.Numerics.Vector3(0, 0, 0), ForceMode.Impulse, true);
		}

		private void InitalizeGraphics()
		{
			if (Window.RenderCanvasHandle == IntPtr.Zero)
				throw new InvalidOperationException();

			var swapChainDesc = new SwapChainDescription()
			{
				BufferCount = 1,
				IsWindowed = true,
				OutputHandle = Window.RenderCanvasHandle,
				SwapEffect = SwapEffect.Discard,
				Usage = Usage.RenderTargetOutput,
				ModeDescription = new ModeDescription()
				{
					Format = Format.R8G8B8A8_UNorm,
					Width = (int)Window.RenderCanvasSize.Width,
					Height = (int)Window.RenderCanvasSize.Height,
					RefreshRate = new Rational(60, 1)
				},
				SampleDescription = new SampleDescription(1, 0)
			};

			SharpDX.Direct3D11.Device device;
			try
			{
				SharpDX.Direct3D11.Device.CreateWithSwapChain(DriverType.Warp, DeviceCreationFlags.None, swapChainDesc, out device, out _swapChain);
				GraphicsDevice = device;
			}
			catch
			{
				throw new Exception("Failed to create graphics device. Do you have DirectX 11?");
			}

			// Create a view of our render target, which is the 'back buffer' of the swap chain we just created
			{
				using (var resource = SharpDX.Direct3D11.Resource.FromSwapChain<Texture2D>(_swapChain, 0))
				{
					_backBuffer = new RenderTargetView(device, resource);
				}

				// Use it
				device.ImmediateContext.OutputMerger.SetTargets(_backBuffer);
			}

			CreateDepthStencil();
			LoadVisualizationEffect();

			// Allocate a large buffer to write the PhysX visualization vertices into
			// There's more optimized ways of doing this, but for this sample a large buffer will do
			_userPrimitivesBuffer = new SharpDX.Direct3D11.Buffer(GraphicsDevice, VertexPositionColor.SizeInBytes * 50000, ResourceUsage.Dynamic, BindFlags.VertexBuffer, CpuAccessFlags.Write, ResourceOptionFlags.None, VertexPositionColor.SizeInBytes);
		}
		private void CreateDepthStencil()
		{
			var stencilDesc = new Texture2DDescription()
			{
				Width = (int)Window.RenderCanvasSize.Width,
				Height = (int)Window.RenderCanvasSize.Height,
				MipLevels = 1,
				ArraySize = 1,
				Format = Format.D32_Float,
				SampleDescription = new SampleDescription() { Count = 1, Quality = 0 },
				Usage = ResourceUsage.Default,
				BindFlags = BindFlags.DepthStencil,
				CpuAccessFlags = CpuAccessFlags.None,
				OptionFlags = ResourceOptionFlags.None
			};

			var depthBufferTexture = new Texture2D(GraphicsDevice, stencilDesc);

			_depthBuffer = new DepthStencilView(this.GraphicsDevice, depthBufferTexture);
		}
		private void LoadVisualizationEffect()
		{
			string engineDir = Path.GetDirectoryName(Assembly.GetExecutingAssembly().Location);

			string visEffectFile = Path.Combine(engineDir, @"Shaders\VisualizationEffect.fx");

			var shaderByteCode = ShaderBytecode.CompileFromFile(visEffectFile, "fx_5_0", ShaderFlags.Debug);

			var effect = new Effect(this.GraphicsDevice, shaderByteCode);

			_visualizationEffect = new VisualizationEffect()
			{
				Effect = effect,
				World = effect.GetVariableByName("World").AsMatrix(),
				View = effect.GetVariableByName("View").AsMatrix(),
				Projection = effect.GetVariableByName("Projection").AsMatrix(),
				RenderScenePass0 = effect.GetTechniqueByName("RenderScene").GetPassByIndex(0)
			};

			// Vertex structure the shader is expecting - very basic sample, just Position and Color.
			var elements = new[]
			{
				new InputElement("Position", 0, Format.R32G32B32A32_Float, 0, 0),
				new InputElement("Color", 0, Format.R32G32B32A32_Float, 16, 0)
			};
			_inputLayout = new InputLayout(this.GraphicsDevice, _visualizationEffect.RenderScenePass0.Description.Signature, elements);
		}

		public void InitalizePhysics()
		{
			// Construct engine objects
			this.Camera = new Camera(this);

			// Construct physics objects
			ErrorOutput errorOutput = new ErrorOutput();

			Foundation foundation = new Foundation(errorOutput);

			this.Physics = new Physics(foundation, checkRuntimeFiles: true);

#if GPU
			var cudaContext = new CudaContextManager(foundation);
#endif

			this.Scene = this.Physics.CreateScene(CreateSceneDesc());

			this.Scene.SetVisualizationParameter(VisualizationParameter.Scale, 2.0f);
			this.Scene.SetVisualizationParameter(VisualizationParameter.CollisionShapes, true);
			this.Scene.SetVisualizationParameter(VisualizationParameter.JointLocalFrames, true);
			this.Scene.SetVisualizationParameter(VisualizationParameter.JointLimits, true);
			this.Scene.SetVisualizationParameter(VisualizationParameter.ParticleSystemPosition, true);
			this.Scene.SetVisualizationParameter(VisualizationParameter.ActorAxes, true);

			// Connect to the remote debugger (if it's there)
			if (this.Physics.RemoteDebugger != null)
			{
				this.Physics.RemoteDebugger.Connect("localhost");
			}

			CreateGroundPlane();
		}
		protected virtual SceneDesc CreateSceneDesc()
		{
			var sceneDesc = new SceneDesc
			{
				Gravity = new System.Numerics.Vector3(0, -9.81f, 0),
#if GPU
				GpuDispatcher = cudaContext.GpuDispatcher
#endif
				FilterShader = new SampleFilterShader()
			};

			if (_sceneDescCallback != null)
				_sceneDescCallback(sceneDesc);

			return sceneDesc;
		}
		private void CreateGroundPlane()
		{
			var groundPlaneMaterial = this.Scene.Physics.CreateMaterial(0.1f, 0.1f, 0.1f);

			var groundPlane = this.Scene.Physics.CreateRigidStatic();
			groundPlane.Name = "Ground Plane";
			groundPlane.GlobalPose = Matrix4x4.CreateFromAxisAngle(new System.Numerics.Vector3(0, 0, 1), (float)System.Math.PI / 2);

			var planeGeom = new PlaneGeometry();

			groundPlane.CreateShape(planeGeom, groundPlaneMaterial);

			this.Scene.AddActor(groundPlane);
		}

		public void Run()
		{
			Window.Show();
			Window.Focus();

			var frameTimer = Stopwatch.StartNew();

			// Not an ideal render loop, but it will do for this sample
			while (true)
			{
				if (!Window.IsActive)
				{
					System.Windows.Forms.Application.DoEvents();
					System.Threading.Thread.Sleep(50);
					continue;
				}

				Draw();

				// 60fps = 1/60 = 16.67 ms/frame
				if (frameTimer.Elapsed >= TimeSpan.FromMilliseconds(16.67))
				{
					Update(frameTimer.Elapsed);

					frameTimer.Restart();
					System.Windows.Forms.Application.DoEvents();
				}
			}
		}

		private void Update(TimeSpan elapsed)
		{
			this.FrameTime = elapsed;

			// Update Physics
			this.Scene.Simulate((float)elapsed.TotalSeconds);
			this.Scene.FetchResults(block: true);

			this.Camera.Update(elapsed);

			if (OnUpdate != null)
				OnUpdate(elapsed);
		}

		private void Draw()
		{
			this.GraphicsDevice.ImmediateContext.OutputMerger.SetTargets(_depthBuffer, _backBuffer);

			// Clear to a nice blue colour :)
			this.GraphicsDevice.ImmediateContext.ClearRenderTargetView(_backBuffer, new SharpDX.Color4(0.27f, 0.51f, 0.71f, 1));
			this.GraphicsDevice.ImmediateContext.ClearDepthStencilView(_depthBuffer, DepthStencilClearFlags.Depth | DepthStencilClearFlags.Stencil, 1, 0);
			this.GraphicsDevice.ImmediateContext.Rasterizer.SetViewports(new[] { (SharpDX.Mathematics.Interop.RawViewportF)this.Camera.Viewport }, 1);

			DrawDebug(this.Scene.GetRenderBuffer());

			if (OnDraw != null)
				OnDraw(this, null);

			_swapChain.Present(0, PresentFlags.None);
		}
		private void DrawDebug(RenderBuffer data)
		{
			var pass = _visualizationEffect.RenderScenePass0;

			_visualizationEffect.World.SetMatrix(SharpDX.Matrix.Identity);
			_visualizationEffect.View.SetMatrix(this.Camera.View);
			_visualizationEffect.Projection.SetMatrix(this.Camera.Projection);

			this.GraphicsDevice.ImmediateContext.InputAssembler.InputLayout = _inputLayout;

			pass.Apply(this.GraphicsDevice.ImmediateContext);

			if (data.NumberOfPoints > 0)
			{
				var vertices = new VertexPositionColor[data.Points.Length];
				for (int i = 0; i < data.Points.Length; i++)
				{
					var point = data.Points[i];

					vertices[i * 2 + 0] = new VertexPositionColor(point.Point.As<SharpDX.Vector3>(), Color.FromArgb(point.Color));
				}

				DrawVertices(vertices, PrimitiveTopology.PointList);
			}

			if (data.NumberOfLines > 0)
			{
				var vertices = new VertexPositionColor[data.Lines.Length * 2];
				for (int x = 0; x < data.Lines.Length; x++)
				{
					DebugLine line = data.Lines[x];

					vertices[x * 2 + 0] = new VertexPositionColor(line.Point0.As<SharpDX.Vector3>(), Color.FromArgb(line.Color0));
					vertices[x * 2 + 1] = new VertexPositionColor(line.Point1.As<SharpDX.Vector3>(), Color.FromArgb(line.Color1));
				}

				DrawVertices(vertices, PrimitiveTopology.LineList);
			}

			if (data.NumberOfTriangles > 0)
			{
				var vertices = new VertexPositionColor[data.Triangles.Length * 3];
				for (int x = 0; x < data.Triangles.Length; x++)
				{
					DebugTriangle triangle = data.Triangles[x];

					vertices[x * 3 + 0] = new VertexPositionColor(triangle.Point0.As<SharpDX.Vector3>(), Color.FromArgb(triangle.Color0));
					vertices[x * 3 + 1] = new VertexPositionColor(triangle.Point1.As<SharpDX.Vector3>(), Color.FromArgb(triangle.Color1));
					vertices[x * 3 + 2] = new VertexPositionColor(triangle.Point2.As<SharpDX.Vector3>(), Color.FromArgb(triangle.Color2));
				}

				DrawVertices(vertices, PrimitiveTopology.TriangleList);
			}
		}

		private void PopulatePrimitivesBuffer(VertexPositionColor[] vertices)
		{
			var dataBox = this.GraphicsDevice.ImmediateContext.MapSubresource(_userPrimitivesBuffer, 0, MapMode.WriteDiscard, SharpDX.Direct3D11.MapFlags.None);
			SharpDX.Utilities.Write(IntPtr.Add(dataBox.DataPointer, 0), vertices, 0, vertices.Length);
			this.GraphicsDevice.ImmediateContext.UnmapSubresource(_userPrimitivesBuffer, 0);
		}
		private void DrawVertices(VertexPositionColor[] vertices, PrimitiveTopology top)
		{
			PopulatePrimitivesBuffer(vertices);

			this.GraphicsDevice.ImmediateContext.InputAssembler.PrimitiveTopology = top;
			this.GraphicsDevice.ImmediateContext.InputAssembler.SetVertexBuffers(0, new VertexBufferBinding(_userPrimitivesBuffer, VertexPositionColor.SizeInBytes, 0));
			this.GraphicsDevice.ImmediateContext.Draw(vertices.Length, 0);
		}
		public void DrawSimple(SharpDX.Direct3D11.Buffer vertexBuffer, SharpDX.Direct3D11.Buffer indexBuffer, int indexCount)
		{
			this.GraphicsDevice.ImmediateContext.InputAssembler.SetVertexBuffers(0, new VertexBufferBinding(vertexBuffer, 0, 0));
			this.GraphicsDevice.ImmediateContext.InputAssembler.SetIndexBuffer(indexBuffer, Format.R32_UInt, 0);
			this.GraphicsDevice.ImmediateContext.InputAssembler.PrimitiveTopology = PrimitiveTopology.LineList;

			this.GraphicsDevice.ImmediateContext.DrawIndexed(indexCount, 0, 0);
		}

		//

		public Camera Camera { get; private set; }

		public Physics Physics { get; private set; }
		public Scene Scene { get; private set; }

		public SharpDX.Direct3D11.Device GraphicsDevice { get; private set; }

		public SampleWindow Window { get; private set; }

		public Keyboard Keyboard => _keyboard;

		public TimeSpan FrameTime { get; private set; }
	}
}