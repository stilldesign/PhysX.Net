using System;
using System.Diagnostics;
using System.IO;
using System.Numerics;
using System.Reflection;
using System.Windows;
using System.Windows.Input;
using SlimDX;
using SlimDX.D3DCompiler;
using SlimDX.Direct3D11;
using SlimDX.DXGI;
using Buffer = SlimDX.Direct3D11.Buffer;
using Device = SlimDX.Direct3D11.Device;
using Vector2 = System.Numerics.Vector2;
using Vector3 = System.Numerics.Vector3;
using Vector4 = System.Numerics.Vector4;
using Matrix = System.Numerics.Matrix4x4;

namespace PhysX.Samples.Engine
{
	public delegate void UpdateEventHandler(TimeSpan elapsed);

	public class Engine
	{
		public event UpdateEventHandler OnUpdate;
		public event EventHandler OnDraw;

		private Keyboard _keyboard;
		private VisualizationEffect _visualizationEffect;

		private RenderTargetView _backBuffer;
		private DepthStencilView _depthBuffer;
		private SwapChain _swapChain;

		private Buffer _userPrimitivesBuffer;
		private InputLayout _inputLayout;

		public Engine()
		{
			Window = new SampleWindow();
			Window.Show();

			_keyboard = new Keyboard(this);
			_keyboard.OnKeyDown += new KeyEventHandler(_keyboard_OnKeyDown);

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

			rigidActor.GlobalPose = Matrix.CreateTranslation(cameraPos);
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

			Device device;
			try
			{
				Device.CreateWithSwapChain(DriverType.Hardware, DeviceCreationFlags.None, swapChainDesc, out device, out _swapChain);
				GraphicsDevice = device;
			}
			catch
			{
				throw new Exception("Failed to create graphics device. Do you have DirectX 11?");
			}

			// Create a view of our render target, which is the 'back buffer' of the swap chain we just created
			{
				using (var resource = SlimDX.Direct3D11.Resource.FromSwapChain<Texture2D>(_swapChain, 0))
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
			_userPrimitivesBuffer = new SlimDX.Direct3D11.Buffer(GraphicsDevice, VertexPositionColor.SizeInBytes * 50000, ResourceUsage.Dynamic, BindFlags.VertexBuffer, CpuAccessFlags.Write, ResourceOptionFlags.None, VertexPositionColor.SizeInBytes);
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

			var shaderByteCode = ShaderBytecode.CompileFromFile(visEffectFile, "fx_5_0");

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

			var sceneDesc = new SceneDesc()
			{
				Gravity = new System.Numerics.Vector3(0, -9.81f, 0),
#if GPU
				GpuDispatcher = cudaContext.GpuDispatcher
#endif
				FilterShader = new SampleFilterShader()
			};

			this.Scene = this.Physics.CreateScene(sceneDesc);

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
		private void CreateGroundPlane()
		{
			var groundPlaneMaterial = this.Scene.Physics.CreateMaterial(0.1f, 0.1f, 0.1f);

			var groundPlane = this.Scene.Physics.CreateRigidStatic();
			groundPlane.Name = "Ground Plane";
			groundPlane.GlobalPose = Matrix.CreateFromAxisAngle(new Vector3(0, 0, 1), (float)System.Math.PI / 2);

			var planeGeom = new PlaneGeometry();

			groundPlane.CreateShape(planeGeom, groundPlaneMaterial);

			this.Scene.AddActor(groundPlane);
		}

		public void Run()
		{
			Window.Show();
			Window.Focus();
			//Application.DoEvents();

			var frameTimer = Stopwatch.StartNew();

			// Not an ideal render loop, but it will do for this sample
			while (true)
			{
				// 60fps = 1/60 = 16.67 ms/frame
				if (frameTimer.Elapsed < TimeSpan.FromMilliseconds(16.67))
					continue;

				if (!Window.IsActive)
				{
					System.Windows.Forms.Application.DoEvents();
					System.Threading.Thread.Sleep(50);
					continue;
				}

				Update(frameTimer.Elapsed);
				Draw();

				frameTimer.Restart();
				System.Windows.Forms.Application.DoEvents();
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
			this.GraphicsDevice.ImmediateContext.ClearRenderTargetView(_backBuffer, new Color4(0.27f, 0.51f, 0.71f));
			this.GraphicsDevice.ImmediateContext.ClearDepthStencilView(_depthBuffer, DepthStencilClearFlags.Depth | DepthStencilClearFlags.Stencil, 1, 0);
			this.GraphicsDevice.ImmediateContext.Rasterizer.SetViewports(this.Camera.Viewport);

			DrawDebug(this.Scene.GetRenderBuffer());

			if (OnDraw != null)
				OnDraw(this, null);

			_swapChain.Present(0, PresentFlags.None);
		}
		private void DrawDebug(RenderBuffer data)
		{
			var pass = _visualizationEffect.RenderScenePass0;

			_visualizationEffect.World.SetMatrix(SlimDX.Matrix.Identity);
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

					vertices[i * 2 + 0] = new VertexPositionColor(point.Point.As<SlimDX.Vector3>(), Color.FromArgb(point.Color));
				}

				DrawVertices(vertices, PrimitiveTopology.PointList);
			}

			if (data.NumberOfLines > 0)
			{
				var vertices = new VertexPositionColor[data.Lines.Length * 2];
				for (int x = 0; x < data.Lines.Length; x++)
				{
					DebugLine line = data.Lines[x];

					vertices[x * 2 + 0] = new VertexPositionColor(line.Point0.As<SlimDX.Vector3>(), Color.FromArgb(line.Color0));
					vertices[x * 2 + 1] = new VertexPositionColor(line.Point1.As<SlimDX.Vector3>(), Color.FromArgb(line.Color1));
				}

				DrawVertices(vertices, PrimitiveTopology.LineList);
			}

			if (data.NumberOfTriangles > 0)
			{
				var vertices = new VertexPositionColor[data.Triangles.Length * 3];
				for (int x = 0; x < data.Triangles.Length; x++)
				{
					DebugTriangle triangle = data.Triangles[x];

					vertices[x * 3 + 0] = new VertexPositionColor(triangle.Point0.As<SlimDX.Vector3>(), Color.FromArgb(triangle.Color0));
					vertices[x * 3 + 1] = new VertexPositionColor(triangle.Point1.As<SlimDX.Vector3>(), Color.FromArgb(triangle.Color1));
					vertices[x * 3 + 2] = new VertexPositionColor(triangle.Point2.As<SlimDX.Vector3>(), Color.FromArgb(triangle.Color2));
				}

				DrawVertices(vertices, PrimitiveTopology.TriangleList);
			}
		}

		private void PopulatePrimitivesBuffer(VertexPositionColor[] vertices)
		{
			var data = this.GraphicsDevice.ImmediateContext.MapSubresource(_userPrimitivesBuffer, MapMode.WriteDiscard, SlimDX.Direct3D11.MapFlags.None);

			data.Data.WriteRange(vertices);

			this.GraphicsDevice.ImmediateContext.UnmapSubresource(_userPrimitivesBuffer, 0);

			data.Data.Dispose();
		}
		private void DrawVertices(VertexPositionColor[] vertices, PrimitiveTopology top)
		{
			PopulatePrimitivesBuffer(vertices);

			this.GraphicsDevice.ImmediateContext.InputAssembler.PrimitiveTopology = top;
			this.GraphicsDevice.ImmediateContext.InputAssembler.SetVertexBuffers(0, new VertexBufferBinding(_userPrimitivesBuffer, VertexPositionColor.SizeInBytes, 0));
			this.GraphicsDevice.ImmediateContext.Draw(vertices.Length, 0);
		}
		public void DrawSimple(Buffer vertexBuffer, Buffer indexBuffer, int indexCount)
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

		public Device GraphicsDevice { get; private set; }

		public SampleWindow Window { get; private set; }

		public Keyboard Keyboard
		{
			get
			{
				return _keyboard;
			}
		}

		public TimeSpan FrameTime { get; private set; }
	}
}