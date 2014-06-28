using System;
using System.Collections.Generic;
using System.Linq;
using SlimDX.Direct3D11;

namespace PhysX.Samples
{
	public class VisualizationEffect
	{
		public Effect Effect { get; set; }

		public EffectMatrixVariable World { get; set; }
		public EffectMatrixVariable View { get; set; }
		public EffectMatrixVariable Projection { get; set; }

		public EffectPass RenderScenePass0 { get; set; }
	}
}