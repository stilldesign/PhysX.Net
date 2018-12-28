#pragma once

#include "PhysicsEnum.h"

namespace PhysX
{
	class InternalErrorCallback;

	public ref class ErrorCallback abstract
	{
		private:
			InternalErrorCallback* _errorCallback;

		protected:
			ErrorCallback();
		public:
			~ErrorCallback();
		protected:
			!ErrorCallback();

		public:
			virtual void ReportError(ErrorCode errorCode, String^ message, String^ file, int lineNumber) abstract;

		internal:
			property InternalErrorCallback* UnmanagedPointer
			{
				InternalErrorCallback* get();
			}
	};

	class InternalErrorCallback : public PxErrorCallback
	{
		private:
			gcroot<ErrorCallback^> _errorCallback;

		public:
			InternalErrorCallback(ErrorCallback^ errorCallback);

			virtual void reportError(PxErrorCode::Enum code, const char *message, const char *file, int line);
	};

	public ref class ConsoleErrorCallback sealed : ErrorCallback
	{
		public:
			ConsoleErrorCallback();

			virtual void ReportError(ErrorCode errorCode, String^ message, String^ file, int lineNumber) override;
	};

	public ref class DefaultErrorCallback sealed : ErrorCallback
	{
		public:
			DefaultErrorCallback();

			virtual void ReportError(ErrorCode errorCode, String^ message, String^ file, int lineNumber) override;
	};
};