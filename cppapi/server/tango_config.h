
//===================================================================================================================
//
// file :               Tango_config.h
//
// description :        Include file where all the system dependant types are defined.
//
// project :            TANGO
//
// author(s) :          A.Gotz + E.Taurel
//
// Copyright (C) :      2004,2005,2006,2007,2008,2009,2010,2011,2012,2013,2014,2015
//						European Synchrotron Radiation Facility
//                      BP 220, Grenoble 38043
//                      FRANCE
//
// This file is part of Tango.
//
// Tango is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// Tango is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty
// of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License along with Tango.
// If not, see <http://www.gnu.org/licenses/>.
//
//
//===================================================================================================================

#ifndef _TANGO_CONFIG_H
#define _TANGO_CONFIG_H

//
// Add some define for Win32 and omniORB
// !!!!!!!!!! In some cases, VC++ wizard generates Stdafx.h file which include
// windows.h file as their first include. Stdafx.h file is the first
// file which should be in included by the include files list. Therefore, in
// this case, it is not possible to define anything before windows.h file is
// included (except by modying stdafx.h file by hand...). In order to include
// Windows socket release 2 software, _WIN32_WINNT must be defined and set
// to something >= 0x0400. Therefore, in this case, define it in the project
// setting in the preprocessor definitions....
//
// Windows:
// The Windows VC compilers family defined _WIN32 (always) and _WIN64
// (when compiled as 64 bits)
// The Windows windef.h include file defines the preprocessor WIN32 on top of the
// _WIN32 one defined by the compiler itself.
//
// This means that on Windows 64 bits, we will have BOTH
//		_WIN32
//		WIN32
//		_WIN64
//
// Within Tango, Windows include files are included by the "idl/tango.h" include file
// included by tango.h after this file
//

#ifdef _WIN32
  #ifndef __WIN32__
    #define __WIN32__
  #endif
  #ifndef __x86__
    #define __x86__
  #endif
  #ifndef _WIN32_WINNT
    #define _WIN32_WINNT 0x0500
  #endif
  #ifndef __NT__
    #define __NT__
  #endif
  #ifndef __OSVERSION
    #define __OSVERSION 4
  #endif
#endif

//
// Check Win32 VC release
//

#ifdef _WIN32
    #ifdef _MSC_VER
        #if ((_MSC_VER >= 1400)  && (_MSC_VER < 1500))
            #define WIN32_VC8
        #elif ((_MSC_VER >= 1500) && (_MSC_VER < 1600))
            #define WIN32_VC9
        #elif ((_MSC_VER >= 1600) && (_MSC_VER < 1700))
            #define WIN32_VC10
		#elif ((_MSC_VER >= 1700) && (_MSC_VER < 1800))
			#define WIN32_VC11
		#elif ((_MSC_VER >= 1800) && (_MSC_VER < 1900))
			#define WIN32_VC12
        #elif (_MSC_VER >= 1900)
			#define WIN32_VC14
        #endif   // VC8+/VC9/VC10/VC11/VC12/VC14
    #endif
#endif


//
// Define a common preprocessor macros for all Windows (32 or 64 bits)
//

#ifdef _WIN32
	#define _TG_WINDOWS_
#endif

//
// For Windows DLL (import and export nightmare)
//

#ifdef  _TG_WINDOWS_
	#if ((defined _USRDLL) || (defined TANGO_HAS_DLL))
		#if (defined _TANGO_LIB)
			#define TANGO_IMP_EXP	__declspec(dllexport)
			#define TANGO_IMP
		#else
			#define TANGO_IMP_EXP	__declspec(dllimport)
			#define TANGO_IMP	__declspec(dllimport)
		#endif
	#else
		#define TANGO_IMP_EXP
		#define TANGO_IMP
	#endif
#else
	#define TANGO_IMP_EXP
	#define TANGO_IMP
#endif /* _WINDOWS_ */

//
// Some C++11 feature
// map::at() -> gcc 4.1.0 (See C++ Standard Library Defect Report 464)
// Unique_ptr -> gcc 4.3
// rvalues -> gcc 4.3
// Lambda function -> gcc 4.5
// nullptr -> gcc 4.6
// attributes -> gcc 4.8
// constexpr -> gcc 5.0 (C++14 style constexpr)

#ifndef _TG_WINDOWS_
    #if defined(__GNUC__)
        #if __GNUC__ == 4
            #if __GNUC_MINOR__ > 0
                #define HAS_MAP_AT
            #endif
            #if __GNUC_MINOR__ > 3
                #define HAS_UNIQUE_PTR
                #define HAS_RVALUE
                #define HAS_THREAD
                #define HAS_TYPE_TRAITS
                #define HAS_VARIADIC_TEMPLATE
            #endif
            #if __GNUC_MINOR__ > 4
                #define HAS_LAMBDA_FUNC
                #define HAS_ISNAN_IN_STD
            #endif
            #if __GNUC_MINOR__ > 5
                #define HAS_NULLPTR
                #define HAS_RANGE_BASE_FOR
                #define INIT_LIST
            #endif
            #if __GNUC_MINOR__ > 6
                #define HAS_OVERRIDE
            #endif
            #if __GNUC_MINOR__ > 7
                #define HAS_UNDERLYING
                #define HAS_ATTRIBUTE_SPECIFIERS
            #endif
        #elif __GNUC__ > 4
            #define HAS_UNIQUE_PTR
            #define HAS_RVALUE
            #define HAS_LAMBDA_FUNC
            #define HAS_ISNAN_IN_STD
            #define HAS_NULLPTR
            #define HAS_RANGE_BASE_FOR
            #define INIT_LIST
            #define HAS_THREAD
            #define HAS_TYPE_TRAITS
            #define HAS_UNDERLYING
            #define HAS_VARIADIC_TEMPLATE
            #define HAS_MAP_AT
            #define HAS_ATTRIBUTE_SPECIFIERS
            #define HAS_CONSTEXPR
        #endif
        #if defined(__clang__)
            #if __clang_major__ > 3
                #define HAS_UNIQUE_PTR
                #define HAS_RVALUE
                #define HAS_LAMBDA_FUNC
                #define HAS_ISNAN_IN_STD
                #define HAS_NULLPTR
                #define HAS_RANGE_BASE_FOR
                #define INIT_LIST
                #define HAS_THREAD
                #define HAS_TYPE_TRAITS
                #define HAS_UNDERLYING
                #define HAS_VARIADIC_TEMPLATE
                #define HAS_MAP_AT
                #define HAS_ATTRIBUTE_SPECIFIERS
                #define HAS_CONSTEXPR
            #endif
        #endif
    #endif
#else
    #ifdef WIN32_VC10
        #define HAS_UNIQUE_PTR
        #define HAS_LAMBDA_FUNC
        #define HAS_NULLPTR
        #define HAS_RVALUE
        #define HAS_TYPE_TRAITS
        #define HAS_MAP_AT
    #endif
    #ifdef WIN32_VC11
        #define HAS_UNIQUE_PTR
        #define HAS_LAMBDA_FUNC
        #define HAS_NULLPTR
        #define HAS_RVALUE
		#define HAS_RANGE_BASE_FOR
        #define HAS_TYPE_TRAITS
        #define HAS_UNDERLYING
        #define HAS_MAP_AT
    #endif
    #ifdef WIN32_VC12
        #define HAS_UNIQUE_PTR
        #define HAS_LAMBDA_FUNC
        #define HAS_NULLPTR
        #define HAS_RVALUE
		#define HAS_RANGE_BASE_FOR
        #define HAS_TYPE_TRAITS
        #define HAS_UNDERLYING
        #define HAS_VARIADIC_TEMPLATE
        #define HAS_MAP_AT
        #define HAS_OVERRIDE
    #endif
    #ifdef WIN32_VC14
        #define HAS_UNIQUE_PTR
        #define HAS_LAMBDA_FUNC
        #define HAS_NULLPTR
        #define HAS_RVALUE
        #define HAS_RANGE_BASE_FOR
        #define HAS_TYPE_TRAITS
        #define HAS_UNDERLYING
        #define HAS_VARIADIC_TEMPLATE
        #define HAS_MAP_AT
        #define HAS_ATTRIBUTE_SPECIFIERS
        #define HAS_OVERRIDE
        #define HAS_CONSTEXPR
    #endif
#endif

//
// For gcc 5 new ABI
//

#ifdef _GLIBCXX_USE_CXX11_ABI
    #define TANGO_CXX11_ABI __attribute((abi_tag("cxx11")))
#else
    #define TANGO_CXX11_ABI
#endif

//
// Some helper define
//

#define 	TangoSys_OMemStream	std::ostringstream
#define		TangoSys_MemStream	std::stringstream
#define		TangoSys_Pid		int
#define		TangoSys_Cout		std::ostream

//
// For Microsoft compilers
//

#ifdef _TG_WINDOWS_
	#pragma warning(disable : 4355)
	#pragma warning(disable : 4715)
    	#pragma warning(disable : 4786)
    	#pragma warning(disable : 4267) // var : conversion from size_t to type, possible loss of data
    	#pragma warning(disable : 4244) // conversion conversion from type1 to type2, possible loss of data
	#if (_MSC_VER >= 1400)       // VC8+
		#pragma warning(disable : 4996)    // disable all deprecation warnings
	#endif   // VC8+
#endif

//
// Define a common isnan call
//

#ifndef _TG_WINDOWS_
    #ifdef HAS_ISNAN_IN_STD
        #define Tango_isnan(A)  std::isnan(A)
    #else
        #define Tango_isnan(A) isnan(A)
    #endif
#else
    #define Tango_isnan(A) _isnan(A)
#endif

//
// Define a common NULL constant
//

#ifdef HAS_NULLPTR
    #define Tango_nullptr   nullptr
#else
    #define Tango_nullptr   NULL
#endif

//
// Define a common sleep call
//

#ifndef _TG_WINDOWS_
    #define Tango_sleep(A) sleep(A)
#else
    #define Tango_sleep(A) Sleep(A * 1000)
#endif

//
// Define a time_t to long casting
//

#ifndef _TG_WINDOWS_
    #define time_t_2_long(A) A
#else
    #define time_t_2_long(A) (long)A
#endif

//
// Define a common strcasecmp function
//

#ifndef _TG_WINDOWS_
    #define TG_strcasecmp strcasecmp
    #define TG_strncasecmp strncasecmp
#else
    #define	TG_strcasecmp stricmp
    #define TG_strncasecmp strnicmp
#endif

//
// ACTIVATE (or DEACTIVATE) THE TANGO LOGGING MECHANISM
//

#define TANGO_HAS_LOG4TANGO

//
// USE DSERVER'S LOGGER TO LOG TANGO CORE MESSAGES (cout1..4)
//

#define TANGO_HAS_CORE_LOGGER

//
// Define a macro for unused parameter warning
//

#ifdef _TG_WINDOWS_
#define TANGO_UNUSED(var) var
#else
	#if __GNUC__ == 3 && __GNUC_MINOR__ >= 4
        #define TANGO_UNUSED(var) var __attribute__ ((unused))
    #elif __GNUC__ > 3
        #define TANGO_UNUSED(var) var __attribute__ ((unused))
    #else
        #define TANGO_UNUSED(var) var
	#endif
#endif

//
// Is it a 32 or 64 bits computer
//

#ifndef _TG_WINDOWS_
	#include <omniORB4/acconfig.h>

	#ifdef PACKAGE_BUGREPORT
		#undef PACKAGE_BUGREPORT
	#endif

	#ifdef PACKAGE_NAME
		#undef PACKAGE_NAME
	#endif

	#ifdef PACKAGE_STRING
		#undef PACKAGE_STRING
	#endif

	#ifdef PACKAGE_TARNAME
		#undef PACKAGE_TARNAME
	#endif

	#ifdef PACKAGE_VERSION
		#undef PACKAGE_VERSION
	#endif

	#if SIZEOF_LONG == 8
		#define TANGO_LONG64
	#else
		#define TANGO_LONG32
	#endif
#else
	#define TANGO_LONG32
#endif

#ifdef HAS_ATTRIBUTE_SPECIFIERS
  #define TANGO_NORETURN [[noreturn]]
#else
  #define TANGO_NORETURN
#endif

// C++14 style constexpr
#ifdef HAS_CONSTEXPR
  #define TANGO_CONSTEXPR constexpr
#else
  #define TANGO_CONSTEXPR
#endif

#endif /* _TANGO_CONFIG_H */
