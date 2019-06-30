#include "ToolBox_NetworkSettings.h"
#include "ToolBox_EepromStorage.h"

#if defined(ESP8266)
#	include <ESP8266WiFi.h>
#elif defined(ESP32)
#   include <WiFi.h>
#else
#   error "no WiFi.h"    
#endif


namespace ToolBox
{
	//! current EEPROM version
	uint16_t const NetworkSettings::cm_uiEEPROMVersion = 0;
	
	/**
	 * ctor 
	 */
	NetworkSettings::NetworkSettings()
	{
	}

	/**
	 * dtor
	 */
	NetworkSettings::~NetworkSettings()
	{
	}

	/**
	 * Vergleichsoperator
	 */
	bool
	NetworkSettings::operator == (NetworkSettings const& rOther) const
	{
		return (m_sHostName == rOther.m_sHostName) &&
			   (m_sSSID == rOther.m_sSSID) &&
			   (m_sPassword == rOther.m_sPassword) &&
			   (m_bConnectToWlan == rOther.m_bConnectToWlan) &&
			   (m_sAccessPoint == rOther.m_sAccessPoint) &&
			   (m_sAccessPointPassword == rOther.m_sAccessPointPassword) &&
			   (m_sNtpServer == rOther.m_sNtpServer) &&
			   (m_bUseFixedIP == rOther.m_bUseFixedIP) &&
			   (m_FixedIP == rOther.m_FixedIP) &&
			   (m_Gateway == rOther.m_Gateway) &&
			   (m_DNS == rOther.m_DNS) &&
			   (m_Subnet == rOther.m_Subnet);
	}

	/**
	 * Vergleichsoperator
	 */
	bool
	NetworkSettings::operator != (NetworkSettings const& rOther) const
	{
		return !operator == (rOther);  
	}

	/**
	 * save settings to EEPROM
	 */
	void
	NetworkSettings::write(ToolBox::EEPROMStorage& rStorage) const
	{
		rStorage << cm_uiEEPROMVersion
				 << m_sHostName						// since Version 0
				 << m_sSSID							// since Version 0
				 << m_sPassword						// since Version 0
				 << m_bConnectToWlan				// since Version 0
				 << m_sAccessPoint					// since Version 0
				 << m_sAccessPointPassword			// since Version 0
				 << m_sNtpServer					// since Version 0
				 << m_bUseFixedIP					// since Version 0
				 << m_FixedIP						// since Version 0
				 << m_Gateway						// since Version 0
				 << m_DNS							// since Version 0
				 << m_Subnet;						// since Version 0
	}

	/**
	 * load settings from EEPROM
	 */
	void
	NetworkSettings::read(ToolBox::EEPROMStorage& rStorage)
	{
		*this = NetworkSettings();
		uint16_t uiVersion = 0;
		rStorage >> uiVersion
				 >> m_sHostName						// since Version 0
				 >> m_sSSID							// since Version 0
				 >> m_sPassword						// since Version 0
				 >> m_bConnectToWlan				// since Version 0
				 >> m_sAccessPoint					// since Version 0
				 >> m_sAccessPointPassword			// since Version 0
				 >> m_sNtpServer					// since Version 0
				 >> m_bUseFixedIP					// since Version 0
				 >> m_FixedIP						// since Version 0
				 >> m_Gateway						// since Version 0
				 >> m_DNS							// since Version 0
				 >> m_Subnet;						// since Version 0
	}
	
	/**
	 * connect to WLAN
	 * @return true, when successfull; false, else
	 */
	bool
	connectToWiFi(NetworkSettings const& rSettings)
	{
		// no SSID?
		if (rSettings.m_sSSID.length() == 0)
			return false;      

		// try to connect to WiFi, timeout after 10 Seconds
		unsigned int uiDelays = 0;
#if defined(ESP8266)        
		WiFi.hostname(rSettings.m_sHostName);
#else
        WiFi.setHostname(rSettings.m_sHostName.c_str());
#endif    
		WiFi.mode(WIFI_STA);
		if (rSettings.m_bUseFixedIP)
			WiFi.config(rSettings.m_FixedIP, rSettings.m_DNS, rSettings.m_Gateway, rSettings.m_Subnet);
		WiFi.begin(rSettings.m_sSSID.c_str(), rSettings.m_sPassword.c_str());
		while ((WiFi.status() != WL_CONNECTED) &&
			   (uiDelays < 20))
		{
			++uiDelays;
			delay(500);
		};

		if (WiFi.status() != WL_CONNECTED)
			return false;
		
		return true;
	}

	/**
	 * create access point
	 * @return true, when successfull; false, else
	 */
	bool
	createAccessPoint(NetworkSettings const& rSettings,
				      DNSServer* pDNSServer)
	{
		// create access point
#if defined(ESP8266)        
		WiFi.hostname(rSettings.m_sHostName);
#else
        WiFi.setHostname(rSettings.m_sHostName.c_str());
#endif    
		WiFi.mode(WIFI_AP);
		if (!WiFi.softAP(rSettings.m_sAccessPoint.c_str(), rSettings.m_sAccessPointPassword.c_str()))
			return false;

		// setup DNS server when requested
		if (pDNSServer)
		{
			pDNSServer->setTTL(300);
			pDNSServer->setErrorReplyCode(DNSReplyCode::ServerFailure);
			IPAddress const serverIP = WiFi.softAPIP();
			pDNSServer->start(53, rSettings.m_sHostName, serverIP);
		};
		
		return true;
	}	
}
