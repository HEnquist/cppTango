//+=================================================================================================================
//
// file :               DeviceLevelAttribute.cpp
//
// description :        C++ source code for the
//				DeviceLevelAttribute and
//				MultiDeviceLevelAttribute
//			classes. These classes are used to manage attribute properties defined at the device level. A Tango
//			Device instance has one MultiDeviceLevelAttribute object which is an aggregate of
//			DeviceLevelAttribute objects
//
// project :            TANGO
//
// author(s) :          E.Taurel
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
// of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License along with Tango.
// If not, see <http://www.gnu.org/licenses/>.
//
//
//-==================================================================================================================

#if HAVE_CONFIG_H
#include <ac_config.h>
#endif

#include <tango.h>
#include <devicelevelattribute.h>
#include <algorithm>

namespace Tango
{


//+------------------------------------------------------------------------------------------------------------------
//
// method :
//		MultiDeviceLevelAttribute::MultiDeviceLevelAttribute
//
// description :
//		constructor for the MultiDeviceLevelAttribute class
//
//-------------------------------------------------------------------------------------------------------------------

MultiDeviceLevelAttribute::~MultiDeviceLevelAttribute()
{
	long nb_attr = attr_list.size();
	for (int i = 0;i < nb_attr;i++)
		delete attr_list[i];
}


//+-------------------------------------------------------------------------------------------------------------------
//
// method :
//		MultiClassAttribute::MultiClassAttribute
//
// description :
//		Constructor for the MultiClassAttribute class from the device class name
//
//--------------------------------------------------------------------------------------------------------------------

MultiDeviceLevelAttribute::MultiDeviceLevelAttribute()
{
	cout4 << "Entering MultiDeviceLevelAttribute constructor" << std::endl;
}


//+-------------------------------------------------------------------------------------------------------------------
//
// method :
//		MultiClassAttribute::get_attr
//
// description :
//		Get the Attr object for the attribute with name passed as parameter
//
// argument :
// 		in :
//			- attr_name : The attribute name
//
// return :
//		Reference to the ClassAttribute object or throw an exceptionif the attribute is not found
//
//--------------------------------------------------------------------------------------------------------------------


Attr &MultiDeviceLevelAttribute::get_attr(std::string &attr_name)
{
//
// Search for the wanted attribute in the attr_list vector from its name
//

	std::vector<Attr *>::iterator pos;

	pos = find_if(attr_list.begin(),attr_list.end(),
		      std::bind2nd(WantedDeviceLevelAttr<Attr *,std::string,bool>(),attr_name));

	if (pos == attr_list.end())
	{
		TangoSys_OMemStream o;
		o << "Attribute " << attr_name << " not found in local attribute(s)" << std::ends;

		Except::throw_exception((const char *)API_AttrOptProp,o.str(),
				      (const char *)"MultiDeviceLevelAttribute::get_attr");
	}

	return *(*pos);
}

//+------------------------------------------------------------------------------------------------------------------
//
// method :
//		MultiClassAttribute::remove_attr
//
// description :
//		Remove the Attr object for the attribute with name passed as parameter
//
// argument :
// 		in :
//			- attr_name : The attribute name
//			- cl_name : The attribute class name
//
//--------------------------------------------------------------------------------------------------------------------


void MultiDeviceLevelAttribute::remove_attr(const std::string &attr_name)
{
	std::vector<Tango::Attr *>::iterator ite;
	for (ite = attr_list.begin();ite != attr_list.end();++ite)
	{
		if (((*ite)->get_name() == attr_name))
		{
			attr_list.erase(ite);
			break;
		}
	}
}


} // End of Tango namespace
