#include "MimeTypes.h"

namespace ToolBox
{
	//! MIME-Types
	static const char* const PROGMEM g_pszMimeTypeTextHtml        = "text/html";
	static const char* const PROGMEM g_pszMimeTypeTextCss         = "text/css";
	static const char* const PROGMEM g_pszMimeTypeTextJavascript  = "text/javascript";
	static const char* const PROGMEM g_pszMimeTypeGIF             = "image/gif";
	static const char* const PROGMEM g_pszMimeTypeTextJPEG        = "image/jpeg";
	static const char* const PROGMEM g_pszMimeTypePNG             = "image/png";
	static const char* const PROGMEM g_pszMimeTypeSVG             = "image/svg+xml";
	static const char* const PROGMEM g_pszMimeTypeICO             = "image/x-icon";
	static const char* const PROGMEM g_pszMimeTypeText            = "text/plain";
	
	/**
	 * hidden ctor
	 */
	MimeTypes::MimeTypes()
	{		
	}

	/**
	 * return the requested mime type
	 */
	String
	MimeTypes::getMimeType(EType eType)
	{
		switch (eType)
		{
			case EType::HTML:
				return g_pszMimeTypeTextHtml;
			case EType::CSS:
				return g_pszMimeTypeTextCss;
			case EType::JAVASCRIPT:
				return g_pszMimeTypeTextJavascript;
			case EType::GIF:
				return g_pszMimeTypeGIF;
			case EType::JPEG:
				return g_pszMimeTypeTextJPEG;
			case EType::PNG:
				return g_pszMimeTypePNG;
			case EType::SVG:
				return g_pszMimeTypeSVG;
			case EType::ICO:
				return g_pszMimeTypeICO;
			case EType::PLAIN:
				return g_pszMimeTypeText;
		};		
		return g_pszMimeTypeText;
	}
	
	/**
	 * try to find the mime type for the given URI
	 */
	String
	MimeTypes::getMimeType(String const& rsUri)
	{
		if ((rsUri.endsWith(".html")) || (rsUri.endsWith("htm")))
			return g_pszMimeTypeTextHtml;

		if (rsUri.endsWith(".js"))
			return g_pszMimeTypeTextJavascript;

		if (rsUri.endsWith(".css"))
			return g_pszMimeTypeTextCss;

		if (rsUri.endsWith(".ico"))
			return g_pszMimeTypeICO;

		if (rsUri.endsWith(".gif"))
			return g_pszMimeTypeGIF;

		if ((rsUri.endsWith(".jpeg")) || (rsUri.endsWith("jpg")) || (rsUri.endsWith("jpe")))
			return g_pszMimeTypeTextJPEG;

		if (rsUri.endsWith(".gif"))
			return g_pszMimeTypePNG;

		if ((rsUri.endsWith(".svg")) || (rsUri.endsWith("svgz")))
			return g_pszMimeTypeSVG;

		if ((rsUri.endsWith(".txt")) || (rsUri.endsWith("log")))
			return g_pszMimeTypeText;

		return g_pszMimeTypeTextHtml;		
	}
}
