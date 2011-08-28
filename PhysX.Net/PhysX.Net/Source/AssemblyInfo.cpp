#include "stdafx.h"

using namespace System;
using namespace System::Reflection;
using namespace System::Runtime::CompilerServices;
using namespace System::Runtime::InteropServices;
using namespace System::Security::Permissions;

//
// General Information about an assembly is controlled through the following
// set of attributes. Change these attribute values to modify the information
// associated with an assembly.
//
[assembly:AssemblyTitleAttribute( "PhysX.Net" )];
[assembly:AssemblyDescriptionAttribute( ".Net Wrapper for NVIDIA PhysX 2.8.4.6" )];
[assembly:AssemblyConfigurationAttribute( "" )];
[assembly:AssemblyCompanyAttribute( "StillDesign" )];
[assembly:AssemblyProductAttribute( "PhysX.Net" )];
[assembly:AssemblyCopyrightAttribute( "Copyright (c) StillDesign 2011" )];
[assembly:AssemblyTrademarkAttribute( "" )];
[assembly:AssemblyCultureAttribute( "" )];

//
// Version information for an assembly consists of the following four values:
//
//      Major Version
//      Minor Version
//      Build Number
//      Revision
//
// You can specify all the value or you can default the Revision and Build Numbers
// by using the '*' as shown below:

[assembly:AssemblyVersionAttribute("0.12.1.0")];

[assembly:ComVisible(false)];

[assembly:CLSCompliantAttribute(true)];

[assembly:SecurityPermission(SecurityAction::RequestMinimum, UnmanagedCode = true)];