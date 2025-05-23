/**
 * \file cwirelessdevicelist.cc
 * \brief manage std::list of WirelessDevice objects
 * \author
 * \version
 */

#include "cwirelessdevicelist.h"
#include <cstring>
#include <algorithm> // std::transform

WirelessDeviceList::WirelessDeviceList(){

}

WirelessDeviceList::~WirelessDeviceList(){

}

bool WirelessDeviceList::get_device_by_mac(WirelessDevice & wdev , struct ether_addr macaddr) {

	_listaccess.lock();
	for (auto & wd : _wdevices_list){

		struct ether_addr mac  = wd.second.getMacaddr() ;
		if(std::memcmp(&mac,&macaddr,ETH_ALEN) == 0){
			wdev = wd.second ;
			_listaccess.unlock();
			return true ;
		}
	}
	_listaccess.unlock();

	return false ;
}

void WirelessDeviceList::add_device(const WirelessDevice & wdevice){

	_listaccess.lock();

	_wdevices_list[wdevice.getIndex()] = wdevice ;

	_listaccess.unlock();
}

void WirelessDeviceList::delete_device(const WirelessDevice & wdevice){

	_listaccess.lock();

	_wdevices_list.erase(wdevice.getIndex()) ;

	_listaccess.unlock();
}

void WirelessDeviceList::delete_device(int index){

	_listaccess.lock();

	_wdevices_list.erase(index);

	_listaccess.unlock();
}

std::vector<WirelessDevice> & WirelessDeviceList::list_devices()  {

	std::vector<WirelessDevice> * list_wd = new std::vector<WirelessDevice>();
	list_wd->reserve(_wdevices_list.size());

	_listaccess.lock();

	std::transform (_wdevices_list.begin(),
					_wdevices_list.end(),
					back_inserter(*list_wd),
					[] (std::pair<int, WirelessDevice> const & pair)
						{
							return pair.second;
						}
	);

	_listaccess.unlock();

	return *(list_wd) ;

}

/** friend functions */

std::ostream &   operator<< ( std::ostream & os , WirelessDeviceList & wdlist ){

	wdlist._listaccess.lock();

	for (const auto & wd : wdlist._wdevices_list){

		os << wd.second;
		os << std::endl ;
	}

	wdlist._listaccess.unlock();

	return os ;
}

