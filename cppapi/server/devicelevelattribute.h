//=============================================================================
//
// file :		DeviceLevelAttribute.h
//
// description :	Include file for the Tango attribute.
//			Three classes are declared in this file :
//
//			AttrProperty : A helper class. This class stored a couple
//				       property name, property value as strings
//		 	DeviceLevelAttribute : A class for each attribute with all
//					 its properties defined at the class
//					 level. The properties are still stored
//					 as string
//			MultiDeviceLevelAttribute : A class to manage all the class
//					      level definition of attributes.
//					      There is one instance of this class
//					      for each tango device pattern
//
// project :		TANGO
//
// author(s) :		E.Taurel
//
// Copyright (C) :      2004,2005,2006,2007,2008,2009,2010,2011,2012,2013,2014,2015
//						European Synchrotron Radiation Facility
//                      BP 220, Grenoble 38043
//                      FRANCE
//
// This file is part of Tango.
//
// Tango is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// Tango is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with Tango.  If not, see <http://www.gnu.org/licenses/>.
//
//
//=============================================================================

#ifndef _LOCAL_ATTRIBUTE_H
#define _LOCAL_ATTRIBUTE_H

#include <tango.h>
//#include <attrdesc.h>
#include <functional>

namespace Tango
{

//=============================================================================
//
//			The MultiDeviceLevelAttribute class
//
//
// description :	This class is a holder for all the DeviceLevelAttribute
//			instance. There is one instance of this class for each
//			Tango device pattern implementation. This instance is
//			stored in the DeviceLocal object of the pattern
//
//=============================================================================


class MultiDeviceLevelAttribute
{
public:
	MultiDeviceLevelAttribute();
	~MultiDeviceLevelAttribute();

	std::vector<Tango::Attr *> &get_attr_list() {return attr_list;}
	Attr &get_attr(std::string &attr_name);
	void remove_attr(const std::string &);

protected:
	std::vector<Tango::Attr *>			attr_list;
};


//=============================================================================
//
//			A binary function object
//
//
// description :	This binary function object is used by the find_if
//			std C++ find_if algorithm. It checks if the
//			DeviceLevelAttribute object passed as argument (A1) stored
//			all the properties for the atribute name passed as
//			second argument (A2).
//			This function object is a predicate and therefore
//			returns a boolean (R)
//
//=============================================================================

template <class A1, class A2, class R>
struct WantedDeviceLevelAttr : public  std::binary_function<A1,A2,R>
{
	R operator() (A1 att,A2 name_str) const
	{
		return att->get_name() == name_str;
	}
};

} // End of Tango namespace

#endif // _LOCAL_ATTRIBUTE_H
