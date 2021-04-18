#ifndef _CWIFISERVER_H_
#define _CWIFISERVER_H_

#include "csocketserver.h"
#include "cinfowifi.h"
#include "cwifi.h"

class CWifiServer : public CSocketServer, public CWifi
{
		friend class CCTRLServer;

		TIndex MaxClientDeconnected;
		bool PacketLoss;

		CListInfo<CInfoWifi>* InfoWifis;
		CListInfo<CInfoWifi>* InfoWifisDeconnected;

		bool RecoverCoordinateOfInfoWifiDeconnected(TCID cid, CCoordinate& coo);

		bool RecoverCoordinateOfInfoWifi(TCID cid, CCoordinate& coo);

	public :

		CWifiServer();

		CWifiServer(CListInfo<CInfoSocket>* infoSockets, CListInfo<CInfoWifi>* infoWifis, CListInfo<CInfoWifi>* infoWifisDeconnected);

		CWifiServer(TSocket type);

		CWifiServer(TSocket type, CListInfo<CInfoSocket>* infoSockets, CListInfo<CInfoWifi>* infoWifis, CListInfo<CInfoWifi>* infoWifisDeconnected);

		~CWifiServer();

		bool Listen(TIndex maxClientDeconnected);

		TDescriptor Accept();

		void ShowInfoWifi(TIndex index);

		void CloseClient(TIndex index);

		void CloseAllClient();

		void SendAllOtherClients(TIndex index,TPower power, const char* data, ssize_t sizeOfData);

		void SendAllClients(CCoordinate cooSource,TPower power, const char* data, ssize_t sizeOfData);

		void SendAllClientsWithoutLoss(TPower power, const char* data, ssize_t sizeOfData);

		CInfoWifi* GetReferenceOnInfoWifiByCID(TCID cid);

		CInfoWifi* GetReferenceOnInfoWifiDeconnectedByCID(TCID cid);

		CInfoWifi* GetReferenceOnInfoWifiByIndex(TIndex index);

		void AddInfoWifiDeconnected(CInfoWifi infoWifi);

		void SetPacketLoss(bool enable);

		bool CanLostPackets();

};

#endif
