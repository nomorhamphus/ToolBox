#pragma once

#include <Arduino.h>

namespace ToolBox
{
	/**
	 * mime types
	 */
	class MimeTypes final
	{
	public:
		/**
		 * known types so far...
		 */
		enum class EType
		{
			First,
			HTML = First,
			CSS,
			JAVASCRIPT,
			GIF,
			JPEG,
			PNG,
			SVG,
			ICO,
			PLAIN,
			Last = PLAIN
		};
		
		static String			getMimeType(EType);
		static String			getMimeType(String const&);
	
	private:
								MimeTypes();
	};
}
