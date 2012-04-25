using System;
using System.Collections.Generic;
using System.Linq;

namespace PhysX.Test
{
	public class ErrorLog : PhysX.ErrorCallback
	{
		private List<string> _errors;

		public ErrorLog()
		{
			_errors = new List<string>();
		}

		public override void ReportError(ErrorCode errorCode, string message, string file, int lineNumber)
		{
			_errors.Add(string.Format("Code: {0}, Message: {1}", errorCode, message));
		}

		public override string ToString()
		{
			if (_errors.Count == 0)
				return "No errors";
			else
				return string.Format("{0} errors. Last error: {1}", _errors.Count, _errors[_errors.Count - 1]);
		}
	}
}