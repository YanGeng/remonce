#ifndef __XMLCONF_H
#define __XMLCONF_H
#include <map>
#include <string>
#include <libxml/parser.h>  
#include <libxml/tree.h> 

// This class is used for read the xml config file of each web servive
class XmlConf {
	public:
		XmlConf();
		XmlConf(int depth, int depthLimit);

		// read the xml service config info, and store into the map url2Service
		bool readXmlConf(const char *fileName);
		// Recursive read the children node of the xml
		bool readChildrenNode(xmlDocPtr doc, xmlNodePtr cur);

		// get the map url2Service
		std::map<std::string, std::string> getXmlConf() const;

		// Get & Set the limit of the xmlDepth
		void setXmlDepthLimit(int depthLimit);
		int getXmlDepthLimit() const;

	public:
		// root node of the xml config-file: only web-app is supported
/*		enum rootNode {
			web-app
		};

		// 1 depth node: now, servlet is supported
		enum depth1Node {
			servlet
		};

		// 2 depth node: now, sevlet-name & url-pattern is supported which will be used for the service factory to
		// create the exact service for the http request
		enum depth2Node {
			servlet-name,
			url-pattern
		};
*/
	private:
		std::map<std::string, std::string> url2Service;		
		// xmlDepth will be used to control the depth of the xml. now the depth is 2
		int xmlDepth;
		int xmlDepthLimit;
};

#endif // end of the __XMLCONF_H
