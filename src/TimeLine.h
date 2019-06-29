#pragma once

#include "EllapsedTimer.h"

#include <functional>

namespace ToolBox
{
	/**
	 * template to shedule tasks
	 */
	template<uint32_t SLOTS>
	class Timeline final
	{
	public:
		using TTimerFunc = std::function<void ()>;
		
								Timeline();  
								~Timeline();

		void                	update();

		uint32_t            	addTimerFunction(uint32_t,
												 TTimerFunc const&,
												 bool);

		void                	clear();

		void                	setEnabled(uint32_t,
										   bool);
		bool                	isEnabled(uint32_t) const;
		
		void					setDelay(uint32_t,
										 uint32_t);
		uint32_t				getDelay(uint32_t) const;

	private:
		/**
		 * Einzelner Eintrag in der Timeline
		 */
		struct Entry final
		{
			//! Flag "Eintrag ist aktiv
			bool            	m_bActive = false;

			//! aufzurufende Funktion
			TTimerFunc      	m_Function;

			//! Timer, der zum Warten verwendet wird
			EllapsedTimer   	m_Timer;

			//! Flag "nur einmal ausführen, dannach deaktivieren"
			bool            	m_bSingleShot = false;
		};

		//! Liste der Einträge in der Timeline
		Entry               	m_Entries[SLOTS];

		//! nächster freier Index in der Liste
		uint32_t            	m_uiNextFree = 0;
	};
	
	/**
	 * ctor
	 */
	template<uint32_t SLOTS>
	Timeline<SLOTS>::Timeline()
	{
	}

	/**
	 * dtor
	 */
	template<uint32_t SLOTS>
	Timeline<SLOTS>::~Timeline()
	{
	}

	/**
	 * Ruft alle Funktionen auf, die gemäß der abgelaufenen Zeit wieder dran sind
	 */
	template<uint32_t SLOTS>
	void
	Timeline<SLOTS>::update()
	{    
		for (uint32_t uiIndex = 0; uiIndex < m_uiNextFree; ++uiIndex)
		{
			if ((m_Entries[uiIndex].m_bActive) && (m_Entries[uiIndex].m_Function))
			{
				// die abgelaufenen Einträge zünden lassen
				if (m_Entries[uiIndex].m_Timer.isEllapsed())
				{
					m_Entries[uiIndex].m_Function();
					m_Entries[uiIndex].m_Timer.restart();
					if (m_Entries[uiIndex].m_bSingleShot)
						m_Entries[uiIndex].m_bActive = false; 
				};
			};
		};
	}

	/**
	 * Fügt der Timeline eine Funktion hinzu
	 * @param uiDelay Millisekunden zwischen zwei Funktionsaufrufen
	 * @param rFunction aufzurufende Funktion
	 * @param bSingleShot true: Funktion nur einmal ausführen, dann deaktivieren; false: Funktion wiederholt ausführen
	 * @return Index des Eintrages (damit kann der Eintrag später geändert werden)
	 */
	template<uint32_t SLOTS>
	uint32_t
	Timeline<SLOTS>::addTimerFunction(uint32_t uiDelay,
									  TTimerFunc const& rFunction,
							          bool bSingleShot)
	{
		if (m_uiNextFree >= SLOTS)
			return SLOTS;
			
		uint32_t const uiResult = m_uiNextFree;
		++m_uiNextFree;

		// Eintrag füllen
		m_Entries[uiResult].m_Function = rFunction;
		m_Entries[uiResult].m_Timer = EllapsedTimer(uiDelay);
		m_Entries[uiResult].m_bSingleShot = bSingleShot;
		m_Entries[uiResult].m_bActive = true;    

		return uiResult;    
	}

	/**
	 * Löscht alle Einträge in der Timeline
	 */
	template<uint32_t SLOTS>
	void
	Timeline<SLOTS>::clear()
	{
		m_uiNextFree = 0;
	}

	/**
	 * Aktiviert/deaktiviert einen Eintrag in der Timeline
	 */
	template<uint32_t SLOTS>
	void
	Timeline<SLOTS>::setEnabled(uint32_t uiEntry,
								bool bEnabled)
	{
		if (uiEntry >= m_uiNextFree)
			return;
		if (bEnabled)
			m_Entries[uiEntry].m_Timer.restart();
		m_Entries[uiEntry].m_bActive = bEnabled;
	}

	/**
	 * Überprüft, ob ein Eintrag in der Timeline aktiv ist
	 */
	template<uint32_t SLOTS>
	bool
	Timeline<SLOTS>::isEnabled(uint32_t uiEntry) const
	{
		if (uiEntry >= m_uiNextFree)
			return false;
		return m_Entries[uiEntry].m_bActive;
	}
	
	/**
	 * Ändert die Verzögerungszeit des angegebenen Eintrages
	 */
	template<uint32_t SLOTS>
	void
	Timeline<SLOTS>::setDelay(uint32_t uiEntry,
							  uint32_t uiDelay)
	{
		if (uiEntry >= m_uiNextFree)
			return;
		return m_Entries[uiEntry].m_Timer.setMillisToEllapse(uiDelay);
	}
	
	/**
	 * Ermittelt die Verzögerungszeit des angegebenen Eintrages
	 */
	template<uint32_t SLOTS>
	uint32_t
	Timeline<SLOTS>::getDelay(uint32_t uiEntry) const
	{
		if (uiEntry >= m_uiNextFree)
			return 0;
		return m_Entries[uiEntry].m_Timer.getMillisToEllapse();
	}
}
