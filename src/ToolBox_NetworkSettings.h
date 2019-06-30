#pragma once

#include "Arduino.h"

#include <DNSServer.h>

namespace ToolBox
{
	class EEPROMStorage;
	
	/**
	 * Netzwork settings
	 */
	class NetworkSettings final
	{
	public:
								NetworkSettings();  
								~NetworkSettings();

		bool                	operator == (NetworkSettings const&) const;
		bool                	operator != (NetworkSettings const&) const;
		
		void					write(EEPROMStorage&) const;
		void					read(EEPROMStorage&);		
		
		//! Hostname
		String              	m_sHostName;

		//! WLAN-SSID
		String              	m_sSSID;

		//! WLAN password
		String              	m_sPassword;

		//! Flag "connect with WLAN"
		bool                	m_bConnectToWlan = true;

		//! Name Access-Point
		String              	m_sAccessPoint;

		//! Passwort Access-Point
		String              	m_sAccessPointPassword;

		//! NTP server
		String              	m_sNtpServer;
		
		//! Flag "use fixed IP"
		bool					m_bUseFixedIP = false;
		
		//! fixed IP
		IPAddress				m_FixedIP;
		
		//! gateway
		IPAddress				m_Gateway;
		
		//! DNSServer
		IPAddress				m_DNS;
		
		//! Subnet
		IPAddress				m_Subnet;
		
	private:
		// required by read() and write()
		static uint16_t const	cm_uiEEPROMVersion;
	};
	
	bool						connectToWiFi(NetworkSettings const&);
	bool						createAccessPoint(NetworkSettings const&,
												  DNSServer*);
	
}
