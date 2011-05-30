using System;
using System.Collections.Generic;
using System.Linq;

namespace PhysX.Test
{
	public class ErrorOutput : PhysX.ErrorCallback
	{
		public override void ReportError(ErrorCode errorCode, string message, string file, int lineNumber)
		{
			
		}
	}
}