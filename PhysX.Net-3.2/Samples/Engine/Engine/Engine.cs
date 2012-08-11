using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Linq;
using System.Reflection;
using System.Windows;
using System.Windows.Input;
using SlimDX;
using SlimDX.D3DCompiler;
using SlimDX.Direct3D10;
using SlimDX.DXGI;

using Buffer = SlimDX.Direct3D10.Buffer;
using Device = SlimDX.Direct3D10.Device;

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
		private RasterizerState _rasterizerState;
		private BlendState _blendState;

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

			rigidActor.GlobalPose = PhysX.Math.Matrix.Translation(cameraPos);
			rigidActor.SetMassAndUpdateInertia(100);

			this.Scene.AddActor(rigidActor);

			rigidActor.AddForceAtLocalPosition(cameraDir * force, new Math.Vector3(0, 0, 0), ForceMode.Impulse, true);
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
					Width = (int)Window.RenderCanvasSize.Width,
					Height = (int)Window.RenderCanvasSize.Height,
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
			var viewport = new Viewport(0, 0, (int)Window.RenderCanvasSize.Width, (int)Window.RenderCanvasSize.Height);
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

			// States
			var blendDesc = new BlendStateDescription()
			{
				SourceBlend = BlendOption.One,
				DestinationBlend = BlendOption.Zero,
				BlendOperation = BlendOperation.Add,
				SourceAlphaBlend = BlendOption.One,
				DestinationAlphaBlend = BlendOption.Zero,
				AlphaBlendOperation = BlendOperation.Add
			};
			blendDesc.SetBlendEnable(0, true);
			_blendState = BlendState.FromDescription(device, blendDesc);

			var rasterDesc = new RasterizerStateDescription()
			{
				IsAntialiasedLineEnabled = false,
				IsMultisampleEnabled = false,
				FillMode = FillMode.Solid,
				CullMode = CullMode.None
			};
			_rasterizerState = RasterizerState.FromDescription(device, rasterDesc);
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

			var effect = Effect.FromFile(this.GraphicsDevice, visEffectFile, "fx_4_0", ShaderFlags.None, EffectFlags.None, null, null);

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

			// Construct physics objects
			ErrorOutput errorOutput = new ErrorOutput();

			Foundation foundation = new Foundation(errorOutput);
			
			this.Physics = new Physics(foundation, checkRuntimeFiles: true);

			var sceneDesc = new SceneDesc()
			{
				Gravity = new Math.Vector3(0, -9.81f, 0)
			};

			this.Scene = this.Physics.CreateScene(sceneDesc);

			this.Scene.SetVisualizationParameter(VisualizationParameter.Scale, 2.0f);
			this.Scene.SetVisualizationParameter(VisualizationParameter.CollisionShapes, true);
			this.Scene.SetVisualizationParameter(VisualizationParameter.JointLocalFrames, true);
			this.Scene.SetVisualizationParameter(VisualizationParameter.JointLimits, true);
			this.Scene.SetVisualizationParameter(VisualizationParameter.ParticleSystemPosition, true);
			this.Scene.SetVisualizationParameter(VisualizationParameter.ActorAxes, true);

			// Connect to the remote debugger if it's there
			Physics.RemoteDebugger.Connect("localhost");

			CreateGroundPlane();
		}
		private void CreateGroundPlane()
		{
			var groundPlaneMaterial = this.Scene.Physics.CreateMaterial(0.1f, 0.1f, 0.1f);

			var groundPlane = this.Scene.Physics.CreateRigidStatic();
			groundPlane.GlobalPose = Matrix.RotationAxis(new Vector3(0, 0, 1), (float)System.Math.PI * 0.5f).AsPhysX();

			var planeGeom = new PlaneGeometry();

			groundPlane.CreateShape(planeGeom, groundPlaneMaterial);

			this.Scene.AddActor(groundPlane);
		}

		public void Run()
		{
			Window.Show();
			Window.Focus();
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
			this.GraphicsDevice.OutputMerger.SetTargets(_depthBuffer, _backBuffer);

			this.GraphicsDevice.ClearRenderTargetView(_backBuffer, new Color4(0.27f, 0.51f, 0.71f)); // A nice blue colour :)
			this.GraphicsDevice.ClearDepthStencilView(_depthBuffer, DepthStencilClearFlags.Depth | DepthStencilClearFlags.Stencil, 1, 0);
			this.GraphicsDevice.Rasterizer.SetViewports(Camera.Viewport);

			var pass = _visualizationEffect.RenderScenePass0;

			_visualizationEffect.World.SetMatrix(Matrix.Identity);
			_visualizationEffect.View.SetMatrix(this.Camera.View);
			_visualizationEffect.Projection.SetMatrix(this.Camera.Projection);

			this.GraphicsDevice.InputAssembler.SetInputLayout(_inputLayout);

			this.GraphicsDevice.Rasterizer.State = _rasterizerState;

			pass.Apply();

			DrawDebug(this.Scene.GetRenderBuffer());

			if (OnDraw != null)
				OnDraw(this, null);

			_swapChain.Present(0, PresentFlags.None);
		}
		private void DrawDebug(RenderBuffer data)
		{
			var pass = _visualizationEffect.RenderScenePass0;

			_visualizationEffect.World.SetMatrix(Matrix.Identity);
			_visualizationEffect.View.SetMatrix(this.Camera.View);
			_visualizationEffect.Projection.SetMatrix(this.Camera.Projection);

			this.GraphicsDevice.InputAssembler.SetInputLayout(_inputLayout);

			pass.Apply();

			if (data.NumberOfPoints > 0)
			{
				var vertices = new VertexPositionColor[data.Points.Length];
				for (int i = 0; i < data.Points.Length; i++)
				{
					var point = data.Points[i];

					vertices[i * 2 + 0] = new VertexPositionColor(point.Point.As<Vector3>(), Color.FromArgb(point.Color));
				}

				DrawVertices(vertices, PrimitiveTopology.PointList);
			}

			if (data.NumberOfLines > 0)
			{
				var vertices = new VertexPositionColor[data.Lines.Length * 2];
				for (int x = 0; x < data.Lines.Length; x++)
				{
					DebugLine line = data.Lines[x];

					vertices[x * 2 + 0] = new VertexPositionColor(line.Point0.As<Vector3>(), Color.FromArgb(line.Color0));
					vertices[x * 2 + 1] = new VertexPositionColor(line.Point1.As<Vector3>(), Color.FromArgb(line.Color1));
				}

				DrawVertices(vertices, PrimitiveTopology.LineList);
			}

			if (data.NumberOfTriangles > 0)
			{
				var vertices = new VertexPositionColor[data.Triangles.Length * 3];
				for (int x = 0; x < data.Triangles.Length; x++)
				{
					DebugTriangle triangle = data.Triangles[x];

					vertices[x * 3 + 0] = new VertexPositionColor(triangle.Point0.As<Vector3>(), Color.FromArgb(triangle.Color0));
					vertices[x * 3 + 1] = new VertexPositionColor(triangle.Point1.As<Vector3>(), Color.FromArgb(triangle.Color1));
					vertices[x * 3 + 2] = new VertexPositionColor(triangle.Point2.As<Vector3>(), Color.FromArgb(triangle.Color2));
				}

				DrawVertices(vertices, PrimitiveTopology.TriangleList);
			}
		}

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