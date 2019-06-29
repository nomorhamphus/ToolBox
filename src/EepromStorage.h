#pragma once

#include <Arduino.h>

class IPAddress;

namespace ToolBox
{
	class Time;
	class Date;
	class DateTime;
	
	/**
	 * EEPROM storage
	 */
	class EEPROMStorage final
	{
	public:
		/**
		 * storage mode
		 */
		enum class EMode
		{
			First,
			Write = First,      	///< write to storage
			Read,               	///< read from storage
			Last = Read
		};
							EEPROMStorage(uint32_t,
										  uint32_t,
										  uint32_t,
										  EMode);  
							~EEPROMStorage();

		bool                isValid() const;
		
		static void			begin();
		static void			wipe();

		uint8_t             readUInt8() const;
		void                writeUInt8(uint8_t);
		int8_t              readInt8() const;
		void                writeInt8(int8_t);

		uint16_t            readUInt16() const;
		void                writeUInt16(uint16_t);
		int16_t             readInt16() const;
		void                writeInt16(int16_t);

		uint32_t            readUInt32() const;
		void                writeUInt32(uint32_t);
		int32_t             readInt32() const;
		void                writeInt32(int32_t);
		
		uint64_t            readUInt64() const;
		void                writeUInt64(uint64_t);
		int64_t             readInt64() const;
		void                writeInt64(int64_t);

		bool              	readBool() const;
		void                writeBool(bool);

		String              readString() const;
		void                writeString(String const&);
		
		IPAddress           readIP() const;
		void                writeIP(IPAddress const&);

		Time 				readTime() const;
		void				writeTime(Time const&);

		Date 				readDate() const;
		void				writeDate(Date const&);

		DateTime 			readDateTime() const;
		void				writeDateTime(DateTime const&);

		/**
		 * Aufzählungswert lesen
		 */
		template<typename TEnumType>
		TEnumType           readEnum(TEnumType eDefault) const
		{
			uint32_t const uiDummy = readUInt32();
			if ((uiDummy >= static_cast<uint32_t>(TEnumType::First)) &&
				(uiDummy <= static_cast<uint32_t>(TEnumType::Last)))
				return static_cast<TEnumType>(uiDummy);
			return eDefault;
		}

		/**
		 * Aufzählungswert schreiben
		 */
		template<typename TEnumType>
		void                writeEnum(TEnumType eValue)
		{
			writeUInt32(static_cast<uint32_t>(eValue));
		}

	private:
		void                readBuffer(void*,
									   size_t) const;

		void                writeBuffer(void*,
										size_t);

		bool                checkStorage(uint32_t,
										 uint32_t,
										 uint32_t) const;
										
		//! Mode
		EMode const         m_eMode;

		//! current address
		mutable uint32_t    m_uiAddress = 0;

		//! flag "Settings valid"
		bool                m_bValid = false;

		//! flag "init has been called"
		static bool         cm_bInitCalled;
	};
}

ToolBox::EEPROMStorage&	operator << (ToolBox::EEPROMStorage&, uint8_t const&);
ToolBox::EEPROMStorage&	operator << (ToolBox::EEPROMStorage&, int8_t const&);
ToolBox::EEPROMStorage&	operator << (ToolBox::EEPROMStorage&, uint16_t const&);
ToolBox::EEPROMStorage&	operator << (ToolBox::EEPROMStorage&, int16_t const&);
ToolBox::EEPROMStorage&	operator << (ToolBox::EEPROMStorage&, uint32_t const&);
ToolBox::EEPROMStorage&	operator << (ToolBox::EEPROMStorage&, int32_t const&);
ToolBox::EEPROMStorage&	operator << (ToolBox::EEPROMStorage&, uint64_t const&);
ToolBox::EEPROMStorage&	operator << (ToolBox::EEPROMStorage&, int64_t const&);
ToolBox::EEPROMStorage&	operator << (ToolBox::EEPROMStorage&, bool const&);
ToolBox::EEPROMStorage&	operator << (ToolBox::EEPROMStorage&, String const&);
ToolBox::EEPROMStorage&	operator << (ToolBox::EEPROMStorage&, IPAddress const&);
ToolBox::EEPROMStorage&	operator << (ToolBox::EEPROMStorage&, ToolBox::Time const&);
ToolBox::EEPROMStorage&	operator << (ToolBox::EEPROMStorage&, ToolBox::Date const&);
ToolBox::EEPROMStorage&	operator << (ToolBox::EEPROMStorage&, ToolBox::DateTime const&);

ToolBox::EEPROMStorage&	operator >> (ToolBox::EEPROMStorage&, uint8_t&);
ToolBox::EEPROMStorage&	operator >> (ToolBox::EEPROMStorage&, int8_t&);
ToolBox::EEPROMStorage&	operator >> (ToolBox::EEPROMStorage&, uint16_t&);
ToolBox::EEPROMStorage&	operator >> (ToolBox::EEPROMStorage&, int16_t&);
ToolBox::EEPROMStorage&	operator >> (ToolBox::EEPROMStorage&, uint32_t&);
ToolBox::EEPROMStorage&	operator >> (ToolBox::EEPROMStorage&, int32_t&);
ToolBox::EEPROMStorage&	operator >> (ToolBox::EEPROMStorage&, uint64_t&);
ToolBox::EEPROMStorage&	operator >> (ToolBox::EEPROMStorage&, int64_t&);
ToolBox::EEPROMStorage&	operator >> (ToolBox::EEPROMStorage&, bool&);
ToolBox::EEPROMStorage&	operator >> (ToolBox::EEPROMStorage&, String&);
ToolBox::EEPROMStorage&	operator >> (ToolBox::EEPROMStorage&, IPAddress&);
ToolBox::EEPROMStorage&	operator >> (ToolBox::EEPROMStorage&, ToolBox::Time&);
ToolBox::EEPROMStorage&	operator >> (ToolBox::EEPROMStorage&, ToolBox::Date&);
ToolBox::EEPROMStorage&	operator >> (ToolBox::EEPROMStorage&, ToolBox::DateTime&);
