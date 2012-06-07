using System;
using System.Collections.Generic;
using System.Linq;

namespace PhysX.Test
{
	public class PhysicsAndSceneTestUnit : System.IDisposable
	{
		public Physics Physics { get; set; }
		public Scene Scene { get; set; }
		public ErrorLog ErrorOutput { get; set; }

		#region IDisposable Members

		public void Dispose()
		{
			if (Physics != null && !Physics.Disposed)
				Physics.Dispose();

			Physics = null;
			Scene = null;
			ErrorOutput = null;
		}

		#endregion
	}
}