#pragma once

#include <Arduino.h>

namespace ToolBox
{
	/**
	 * Verwaltung zeitgesteuerter Aufgaben
	 */
	template<typename TEnum, uint32_t TCount = (static_cast<uint32_t>(TEnum::Last) - static_cast<uint32_t>(TEnum::First) + 1)>
	class EnumTranslator
	{
	public:
		/**
		 * get text for enum
		 */
		String					getText(TEnum eEnum) const
		{
			uint32_t const uiIndex = static_cast<uint32_t>(eEnum);
			if (uiIndex < TCount)
				return this->m_Strings[uiIndex];
			return String();
		}
		
		/**
		 * getenum for text
		 */
		TEnum					getEnum(String const& rsText)
		{
			for (uint32_t uiIndex = 0; uiIndex < TCount; ++uiIndex)
			{
				if (this->m_Strings[uiIndex] == rsText)
					return static_cast<TEnum>(uiIndex);
			};
			return TEnum::First;
		}
		
	protected:
		/**
		 * ctor
		 */
								EnumTranslator()
		{			
		}
		
		/**
		 * dtor
		 */
								~EnumTranslator()
		{			
		}
		
		/**
		 * cstore a text for an enum
		 */
		void					store(TEnum eEnum,
									  String const& rsText)
		{
			uint32_t const uiIndex = static_cast<uint32_t>(eEnum);
			if (uiIndex < TCount)
				this->m_Strings[uiIndex] = rsText;
		}
		
	private:
		//! translations for enums
		String					m_Strings[TCount];
	};
}
