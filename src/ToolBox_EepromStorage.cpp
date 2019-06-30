#include "ToolBox_EepromStorage.h"
#include "ToolBox_DateTime.h"

#include <EEPROM.h>
#include <IPAddress.h>

#ifndef SPI_FLASH_SEC_SIZE
#   define SPI_FLASH_SEC_SIZE      4096
#endif

//! used EEPROM size
#define EEPROM_SIZE SPI_FLASH_SEC_SIZE

/**
 * Generate read function for POD
 */
#define READ_POD(ANAME, ATYPE)\
  ATYPE\
  EEPROMStorage::ANAME() const\
  {\
      ATYPE result = 0;\
      readBuffer(&result, sizeof(ATYPE));\
      return result;\
  }

/**
 * Generate write function for POD
 */
#define WRITE_POD(ANAME, ATYPE)\
  void\
  EEPROMStorage::ANAME(ATYPE value)\
  {\
      writeBuffer(&value, sizeof(ATYPE));\
  }

namespace ToolBox
{
	//! Flag "EEPROMStorage::begin() has been called"
	bool EEPROMStorage::cm_bInitCalled = false;

	/**
	 * ctor 
	 */
	EEPROMStorage::EEPROMStorage(uint32_t uiMagic1,
								 uint32_t uiMagic2,
								 uint32_t uiVersion,
								 EMode eMode) :
		m_eMode(eMode)
	{
		if (!cm_bInitCalled)
			begin();
		
		switch (m_eMode)
		{
			// prepare writing
			case EMode::Write:
				m_bValid = true;
				writeUInt32(uiMagic1);
				writeUInt32(uiMagic2);
				writeUInt32(uiVersion);
				break;

			case EMode::Read:
				m_bValid = checkStorage(uiMagic1, uiMagic2, uiVersion);
				break;
		};
	}

	/**
	 * dtor
	 */
	EEPROMStorage::~EEPROMStorage()
	{	
		switch (m_eMode)
		{
			// commit written data
			case EMode::Write:
				EEPROM.commit();
				break;

			case EMode::Read:
				break;
		};
	}

	/**
	 * @see m_bValid
	 */
	bool
	EEPROMStorage::isValid() const
	{
		return m_bValid;
	}

	/**
	 * init settings class 
	 */
	void
	EEPROMStorage::begin()
	{
		if (!cm_bInitCalled)
		{
			EEPROM.begin(EEPROM_SIZE);
			cm_bInitCalled = true;
		};
	}

	/**
	 * wipe EEPROM
	 */
	void
	EEPROMStorage::wipe()
	{
		begin();
		uint32_t uiAddress = 0;
		for (size_t uiIndex = 0; uiIndex < EEPROM_SIZE; ++uiIndex)
			EEPROM.write(uiAddress++, 0);
		EEPROM.commit();
	}

	READ_POD(readUInt8, uint8_t)
	WRITE_POD(writeUInt8, uint8_t)
	READ_POD(readInt8, int8_t)
	WRITE_POD(writeInt8, int8_t)

	READ_POD(readUInt16, uint16_t)
	WRITE_POD(writeUInt16, uint16_t)
	READ_POD(readInt16, int16_t)
	WRITE_POD(writeInt16, int16_t)

	READ_POD(readUInt32, uint32_t)
	WRITE_POD(writeUInt32, uint32_t)
	READ_POD(readInt32, int32_t)
	WRITE_POD(writeInt32, int32_t)

	READ_POD(readUInt64, uint64_t)
	WRITE_POD(writeUInt64, uint64_t)
	READ_POD(readInt64, int64_t)
	WRITE_POD(writeInt64, int64_t)

	READ_POD(readBool, bool)
	WRITE_POD(writeBool, bool)

	/**
	 * read String
	 */
	String
	EEPROMStorage::readString() const
	{
		String result;
		
		if (m_eMode != EMode::Read)
			return result;
	  
		uint32_t const uiBytes = readUInt32();
		result.reserve(uiBytes + 1);
		for (size_t uiByte = 0; uiByte < uiBytes; ++uiByte)
		{
			result += ' ';
			result.setCharAt(uiByte, readUInt8());
		};
		return result;
	}

	/**
	 * write string
	 */
	void
	EEPROMStorage::writeString(String const& rsString)
	{
		uint32_t const uiBytes = rsString.length();
		writeUInt32(uiBytes);
		for (size_t uiByte = 0; uiByte < uiBytes; ++uiByte)
			writeUInt8(rsString.charAt(uiByte));
	}
	
	/**
	 * read IP
	 */
	IPAddress
	EEPROMStorage::readIP() const
	{
		IPAddress result;
		result[0] = readUInt8();
		result[1] = readUInt8();
		result[2] = readUInt8();
		result[3] = readUInt8();
		return result;
	}
	
	/**
	 * write IP
	 */
	void
	EEPROMStorage::writeIP(IPAddress const& rIP)
	{
		writeUInt8(rIP[0]);
		writeUInt8(rIP[1]);
		writeUInt8(rIP[2]);
		writeUInt8(rIP[3]);
	}
	
	/**
	 * read Time
	 */
	Time
	EEPROMStorage::readTime() const
	{
		Time result;
		
		if (m_eMode != EMode::Read)
			return result;
	  
		result.m_bValid = readBool();
		result.m_uiMilliSeconds = readUInt32();
		return result;
	}

	/**
	 * write Time
	 */
	void
	EEPROMStorage::writeTime(Time const& rTime)
	{
		writeBool(rTime.m_bValid);
		writeUInt32(rTime.m_uiMilliSeconds);
	}	
	
	/**
	 * read Date
	 */
	Date
	EEPROMStorage::readDate() const
	{
		Date result;
		
		if (m_eMode != EMode::Read)
			return result;
	  
		result.m_bCacheClean = false;
		result.m_bValid = readBool();
		result.m_uiDays = readUInt32();
		return result;
	}

	/**
	 * write Date
	 */
	void
	EEPROMStorage::writeDate(Date const& rDate)
	{
		writeBool(rDate.m_bValid);
		writeUInt32(rDate.m_uiDays);
	}	
	
	/**
	 * read DateTime
	 */
	DateTime
	EEPROMStorage::readDateTime() const
	{
		DateTime result;
		
		if (m_eMode != EMode::Read)
			return result;
	  
		result.m_bValid = readBool();
		result.m_uiMilliSeconds = readUInt64();
		return result;
	}

	/**
	 * write DateTime
	 */
	void
	EEPROMStorage::writeDateTime(DateTime const& rDateTime)
	{
		writeBool(rDateTime.m_bValid);
		writeUInt64(rDateTime.m_uiMilliSeconds);
	}

	/**
	 * read multiple bytes
	 */
	void
	EEPROMStorage::readBuffer(void* pBuffer,
							  size_t uiBytes) const
	{
		if (m_eMode != EMode::Read)
			return;

		uint8_t* pDummy = reinterpret_cast<uint8_t*>(pBuffer);
		for (size_t uiIndex = 0; uiIndex < uiBytes; ++uiIndex)
		{
			*pDummy = EEPROM.read(m_uiAddress);
			++m_uiAddress;
			++pDummy;      
		};
	}

	/**
	 * write multiple bytes
	 */
	void
	EEPROMStorage::writeBuffer(void* pBuffer,
							   size_t uiBytes)
	{
		if (m_eMode != EMode::Write)
			return;

		uint8_t* pDummy = reinterpret_cast<uint8_t*>(pBuffer);
		for (size_t uiIndex = 0; uiIndex < uiBytes; ++uiIndex)
		{
			EEPROM.write(m_uiAddress, *pDummy);
			++m_uiAddress;
			++pDummy;      
		};
	}

	/**
	 * check wether settings exist in EEPROM or not
	 */
	bool
	EEPROMStorage::checkStorage(uint32_t uiMagic1,
								uint32_t uiMagic2,
								uint32_t uiVersion) const
	{
		if (readUInt32() != uiMagic1)
			return false;
		if (readUInt32() != uiMagic2)
			return false;
		return (readUInt32() == uiVersion);  
	}
}

/**
 * Ausgabeoperatoren
 */
#define MAKE_WRITE_OP(ATYPE, AFUNC)\
	ToolBox::EEPROMStorage&\
	operator << (ToolBox::EEPROMStorage& rStorage,\
				 ATYPE const& rValue)\
	{\
		rStorage.AFUNC(rValue);\
		return rStorage;\
	}

MAKE_WRITE_OP(uint8_t, writeUInt8)
MAKE_WRITE_OP(int8_t, writeInt8)
MAKE_WRITE_OP(uint16_t, writeUInt16)
MAKE_WRITE_OP(int16_t, writeInt16)
MAKE_WRITE_OP(uint32_t, writeUInt32)
MAKE_WRITE_OP(int32_t, writeInt32)
MAKE_WRITE_OP(uint64_t, writeUInt64)
MAKE_WRITE_OP(int64_t, writeInt64)
MAKE_WRITE_OP(bool, writeBool)
MAKE_WRITE_OP(String, writeString)
MAKE_WRITE_OP(IPAddress, writeIP)
MAKE_WRITE_OP(ToolBox::Time, writeTime)
MAKE_WRITE_OP(ToolBox::Date, writeDate)
MAKE_WRITE_OP(ToolBox::DateTime, writeDateTime)

/**
 * Eingabeoperatoren
 */
#define MAKE_READ_OP(ATYPE, AFUNC)\
	ToolBox::EEPROMStorage&\
	operator >> (ToolBox::EEPROMStorage& rStorage,\
				 ATYPE& rValue)\
	{\
		rValue = rStorage.AFUNC();\
		return rStorage;\
	}

MAKE_READ_OP(uint8_t, readUInt8)
MAKE_READ_OP(int8_t, readInt8)
MAKE_READ_OP(uint16_t, readUInt16)
MAKE_READ_OP(int16_t, readInt16)
MAKE_READ_OP(uint32_t, readUInt32)
MAKE_READ_OP(int32_t, readInt32)
MAKE_READ_OP(uint64_t, readUInt64)
MAKE_READ_OP(int64_t, readInt64)
MAKE_READ_OP(bool, readBool)
MAKE_READ_OP(String, readString)
MAKE_READ_OP(IPAddress, readIP)
MAKE_READ_OP(ToolBox::Time, readTime)
MAKE_READ_OP(ToolBox::Date, readDate)
MAKE_READ_OP(ToolBox::DateTime, readDateTime)
	