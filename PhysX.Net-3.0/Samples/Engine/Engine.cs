using System;
using System.Diagnostics;
using System.Windows;
using SlimDX;
using SlimDX.D3DCompiler;
using SlimDX.Direct3D10;
using SlimDX.DXGI;

using Buffer = SlimDX.Direct3D10.Buffer;
using Device = SlimDX.Direct3D10.Device;
using System.Windows.Input;

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

		private SlimDX.Direct3D10.Buffer _userPrimitivesBuffer;
		private InputLayout _inputLayout;

		public Engine()
		{
			Window = new SampleWindow();
			Window.Show();
			_keyboard = new Keyboard(this);

			InitalizeGraphics();

			InitalizePhysics();

			Mouse.SetCursor(Cursors.None);
		}

		private void InitalizeGraphics()
		{
			if (Window.RenderCanvasHandle == IntPtr.Zero)
				throw new InvalidOperationException();

			SwapChainDescription swapChainDesc = new SwapChainDescription()
			{
				BufferCount = 1,
				Flags = SwapChainFlags.None,
				IsWindowed = true,
				OutputHandle = Window.RenderCanvasHandle,
				SwapEffect = SwapEffect.Discard,
				Usage = Usage.RenderTargetOutput,
				ModeDescription = new ModeDescription()
				{
					Format = SlimDX.DXGI.Format.R8G8B8A8_UNorm,
					//Format = SlimDX.DXGI.Format.B8G8R8A8_UNorm,
					Width = (int)Window.Width,
					Height = (int)Window.Height,
					RefreshRate = new Rational(60, 1),
					Scaling = DisplayModeScaling.Unspecified,
					ScanlineOrdering = DisplayModeScanlineOrdering.Unspecified
				},
				SampleDescription = new SampleDescription(1, 0)
			};

			var giFactory = new SlimDX.DXGI.Factory();
			var adapter = giFactory.GetAdapter(0);

			Device device;
			SwapChain swapChain;
			Device.CreateWithSwapChain(adapter, DriverType.Hardware, DeviceCreationFlags.Debug, swapChainDesc, out device, out swapChain);
			_swapChain = swapChain;
			GraphicsDevice = device;

			// create a view of our render target, which is the backbuffer of the swap chain we just created
			using (var resource = SlimDX.Direct3D10.Resource.FromSwapChain<Texture2D>(swapChain, 0))
			{
				_backBuffer = new RenderTargetView(device, resource);
			}

			// setting a viewport is required if you want to actually see anything
			var viewport = new Viewport(0, 0, (int)Window.Width, (int)Window.Height);
			device.OutputMerger.SetTargets(_backBuffer);
			device.Rasterizer.SetViewports(viewport);

			CreateDepthStencil();
			LoadVisualizationEffect();

			// Allocate a large buffer to write the PhysX visualization vertices into
			// There's more optimized ways of doing this, but for this sample a large buffer will do
			_userPrimitivesBuffer = new SlimDX.Direct3D10.Buffer(GraphicsDevice, VertexPositionColor.SizeInBytes * 50000, ResourceUsage.Dynamic, BindFlags.VertexBuffer, CpuAccessFlags.Write, ResourceOptionFlags.None);

			var elements = new[]
			{
				new InputElement("Position", 0, Format.R32G32B32A32_Float, 0, 0),
				new InputElement("Color", 0, Format.R32G32B32A32_Float, 16, 0)
			};
			_inputLayout = new InputLayout(GraphicsDevice, _visualizationEffect.RenderScenePass0.Description.Signature, elements);
		}
		private void CreateDepthStencil()
		{
			var stencilDesc = new Texture2DDescription()
			{
				Width = (int)Window.Width,
				Height = (int)Window.Height,
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
			var effect = Effect.FromFile(this.GraphicsDevice, @"Shaders\VisualizationEffect.fx", "fx_4_0", ShaderFlags.None, EffectFlags.None, null, null);

			_visualizationEffect = new VisualizationEffect()
			{
				Effect = effect,
				World = effect.GetVariableByName("World").AsMatrix(),
				View = effect.GetVariableByName("View").AsMatrix(),
				Projection = effect.GetVariableByName("Projection").AsMatrix(),
				RenderScenePass0 = effect.GetTechniqueByName("RenderScene").GetPassByIndex(0)
			};
		}

		public void InitalizePhysics()
		{
			// Construct engine objects
			this.Camera = new Camera(this);

			//_visualizationEffect = new BasicEffect(this.Device)
			//{
			//    VertexColorEnabled = true
			//};
			//_vertexDeclaration = VertexPositionColor.VertexDeclaration;

			// Construct physics objects
			ErrorOutput errorOutput = new ErrorOutput();

			this.Core = new Physics(errorOutput);

			Physics physics = this.Core;
			//physics.SetParameter(PhysicsParameter.VisualizationScale, 2.0f);
			//physics.SetParameter(PhysicsParameter.VisualizeCollisionShapes, true);
			//physics.SetParameter(PhysicsParameter.VisualizeClothMesh, true);
			//physics.SetParameter(PhysicsParameter.VisualizeJointLocalAxes, true);
			//physics.SetParameter(PhysicsParameter.VisualizeJointLimits, true);
			//physics.SetParameter(PhysicsParameter.VisualizeFluidPosition, true);
			//physics.SetParameter(PhysicsParameter.VisualizeFluidEmitters, false); // Slows down rendering a bit too much
			//physics.SetParameter(PhysicsParameter.VisualizeForceFields, true);
			//physics.SetParameter(PhysicsParameter.VisualizeSoftBodyMesh, true);

			var sceneDesc = new SceneDesc()
			{
				//SimulationType = SimulationType.Hardware,
				Gravity = new MathPrimitives.Vector3(0, -9.81f, 0),
				//GroundPlaneEnabled = true
			};

			this.Scene = physics.CreateScene(sceneDesc);

			// Connect to the remote debugger if it's there
			//physics.Foundation.RemoteDebugger.Connect("localhost");
		}

		public void Run()
		{
			Window.Show();
			//Application.DoEvents();

			Stopwatch timer = new Stopwatch();
			timer.Start();

			// Not an ideal render loop, but it will do for this sample
			while (true)
			{
				// 60fps = 1/60 = 16.67 ms/frame
				if (timer.Elapsed < TimeSpan.FromMilliseconds(16.67))
					continue;

				Update(timer.Elapsed);
				Draw();

				timer.Restart();
				System.Windows.Forms.Application.DoEvents();
			}
		}

		private void Update(TimeSpan elapsed)
		{
			// Update Physics
			this.Scene.Simulate((float)elapsed.TotalSeconds);
			//_scene.Simulate( 1.0f / 60.0f );
			//this.Scene.FlushStream();
			this.Scene.FetchResults(block: false);

			this.Camera.Update(elapsed);

			if (OnUpdate != null)
				OnUpdate(elapsed);
		}
		private void Draw()
		{
			this.GraphicsDevice.OutputMerger.SetTargets(_depthBuffer, _backBuffer);

			this.GraphicsDevice.ClearRenderTargetView(_backBuffer, new Color4(0.27f, 0.51f, 0.71f));
			this.GraphicsDevice.ClearDepthStencilView(_depthBuffer, DepthStencilClearFlags.Depth | DepthStencilClearFlags.Stencil, 1, 0);
			this.GraphicsDevice.Rasterizer.SetViewports(Camera.Viewport);

			//using (DebugRenderable data = this.Scene.GetDebugRenderable())
			//{
			//    DrawDebug(data);
			//}

			if (OnDraw != null)
				OnDraw(this, null);

			_swapChain.Present(0, PresentFlags.None);
		}

		//private void DrawDebug(DebugRenderable data)
		//{
		//    var pass = _visualizationEffect.RenderScenePass0;

		//    _visualizationEffect.World.SetMatrix(Matrix.Identity);
		//    _visualizationEffect.View.SetMatrix(this.Camera.View);
		//    _visualizationEffect.Projection.SetMatrix(this.Camera.Projection);

		//    this.GraphicsDevice.InputAssembler.SetInputLayout(_inputLayout);

		//    pass.Apply();

		//    if (data.PointCount > 0)
		//    {
		//        var points = data.GetDebugPoints();

		//        var vertices = new VertexPositionColor[points.Length];
		//        for (int i = 0; i < data.LineCount; i++)
		//        {
		//            var point = points[i];

		//            vertices[i * 2 + 0] = new VertexPositionColor(point.Point.As<Vector3>(), Color.FromArgb(point.Color));
		//        }

		//        DrawVertices(vertices, PrimitiveTopology.PointList);
		//    }

		//    if (data.LineCount > 0)
		//    {
		//        var lines = data.GetDebugLines();

		//        var vertices = new VertexPositionColor[data.LineCount * 2];
		//        for (int x = 0; x < data.LineCount; x++)
		//        {
		//            DebugLine line = lines[x];

		//            vertices[x * 2 + 0] = new VertexPositionColor(line.Point0.As<Vector3>(), Color.FromArgb(line.Color));
		//            vertices[x * 2 + 1] = new VertexPositionColor(line.Point1.As<Vector3>(), Color.FromArgb(line.Color));
		//        }

		//        DrawVertices(vertices, PrimitiveTopology.LineList);
		//    }

		//    if (data.TriangleCount > 0)
		//    {
		//        var triangles = data.GetDebugTriangles();

		//        var vertices = new VertexPositionColor[data.TriangleCount * 3];
		//        for (int x = 0; x < data.TriangleCount; x++)
		//        {
		//            DebugTriangle triangle = triangles[x];

		//            vertices[x * 3 + 0] = new VertexPositionColor(triangle.Point0.As<Vector3>(), Color.FromArgb(triangle.Color));
		//            vertices[x * 3 + 1] = new VertexPositionColor(triangle.Point1.As<Vector3>(), Color.FromArgb(triangle.Color));
		//            vertices[x * 3 + 2] = new VertexPositionColor(triangle.Point2.As<Vector3>(), Color.FromArgb(triangle.Color));
		//        }

		//        DrawVertices(vertices, PrimitiveTopology.TriangleList);
		//    }

		//    // World axis
		//    {
		//        var vertices = new[] 
		//        {
		//            // X
		//            new VertexPositionColor(new Vector3(0,0,0), new Color(1, 0, 0)),
		//            new VertexPositionColor(new Vector3(5,0,0), new Color(1, 0, 0)),

		//            // Y
		//            new VertexPositionColor(new Vector3(0,0,0), new Color(0, 1, 0)),
		//            new VertexPositionColor(new Vector3(0,5,0), new Color(0, 1, 0)),

		//            // Z
		//            new VertexPositionColor(new Vector3(0,0,0), new Color(0, 0, 1)),
		//            new VertexPositionColor(new Vector3(0,0,5), new Color(0, 0, 1)),
		//        };

		//        DrawVertices(vertices, PrimitiveTopology.LineList);
		//    }
		//}

		private void PopulatePrimitivesBuffer(VertexPositionColor[] vertices)
		{
			using (var stream = _userPrimitivesBuffer.Map(MapMode.WriteDiscard, SlimDX.Direct3D10.MapFlags.None))
			{
				for (int i = 0; i < vertices.Length; i++)
				{
					stream.Write(vertices[i]);
				}
			}
			_userPrimitivesBuffer.Unmap();
		}
		private void DrawVertices(VertexPositionColor[] vertices, PrimitiveTopology top)
		{
			PopulatePrimitivesBuffer(vertices);

			this.GraphicsDevice.InputAssembler.SetPrimitiveTopology(top);
			this.GraphicsDevice.InputAssembler.SetVertexBuffers(0, new VertexBufferBinding(_userPrimitivesBuffer, VertexPositionColor.SizeInBytes, 0));
			this.GraphicsDevice.Draw(vertices.Length, 0);
		}

		public void DrawSimple(Buffer vertexBuffer, Buffer indexBuffer, int indexCount)
		{
			GraphicsDevice.InputAssembler.SetVertexBuffers(0, new VertexBufferBinding(vertexBuffer, 0, 0));
			GraphicsDevice.InputAssembler.SetIndexBuffer(indexBuffer, Format.R32_UInt, 0);
			GraphicsDevice.InputAssembler.SetPrimitiveTopology(PrimitiveTopology.LineList);

			GraphicsDevice.DrawIndexed(indexCount, 0, 0);
		}

		//

		public Camera Camera { get; private set; }

		public Physics Core { get; private set; }
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
	}
}